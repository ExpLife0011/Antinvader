///////////////////////////////////////////////////////////////////////////////
///
/// ��Ȩ���� (c) 2011 - 2012
///
/// ԭʼ�ļ�����	 : SystemHook.cpp
/// ��������         : AntinvaderDriver
/// ����ʱ��         : 2011-04-2
/// 	         
///
/// ����	         : HOOK�ҹ����ܵ�ʵ���ļ�
///
/// ����ά��:
///  0000 [2011-04-2]  ����汾.
///
///////////////////////////////////////////////////////////////////////////////

#include "SystemHook.h"

/*---------------------------------------------------------
��������:	WriteProtectionOn
��������:	����д�������ж�
�������:
�������:
����ֵ:		
����:		
����ά��:	2011.4.3     ����汾
---------------------------------------------------------*/
inline
VOID WriteProtectionOn()
{
	__asm{
		MOV EAX,CR0
		OR EAX,10000H//�ر�д����
		MOV CR0,EAX
		STI//�����ж�
	}
}

/*---------------------------------------------------------
��������:	WriteProtectionOff
��������:	�ر�д�������ж�
�������:
�������:
����ֵ:		
����:		
����ά��:	2011.4.3     ����汾
---------------------------------------------------------*/
inline
VOID WriteProtectionOff()
{
	__asm{
		CLI//�������ж�
		MOV EAX,CR0
		AND EAX,NOT 10000H//ȡ��д����
		MOV CR0,EAX
	}
}

VOID HookInitializeFunctionAddress()
{
	//����ԭʼ��ַ
	ZwCreateProcessOriginal 
		= (ZW_CREATE_PROCESS)SSDT_ADDRESS_OF_FUNCTION(ZwCreateProcess);
}

VOID HookOnSSDT()
{
	//�ر�д���� �������ж�
	WriteProtectionOff();

	//�޸��µ�ַ
	SSDT_ADDRESS_OF_FUNCTION(ZwCreateProcess) 
				= (UCHAR)AntinvaderNewCreateProcess;

	//�ر�д���� �������ж�
	WriteProtectionOn();
}

VOID HookOffSSDT()
{
	//ԭʼ��ַһ��Ϊ��
	ASSERT( ZwCreateProcessOriginal );

	//�ر�д���� �������ж�
	WriteProtectionOff();

	//�޸Ļ�ԭ���ĵ�ַ
	SSDT_ADDRESS_OF_FUNCTION(ZwCreateProcess) 
				= (UCHAR)ZwCreateProcessOriginal;

	//�ر�д���� �������ж�
	WriteProtectionOn();
}

/*---------------------------------------------------------
��������:	AntinvaderNewCreateProcess
��������:	�����滻ZwCreateProcess�Ĺҹ�����
�������:	ͬZwCreateProcess
�������:	ͬZwCreateProcess
����ֵ:		ͬZwCreateProcess
����:		
����ά��:	2011.4.5     ����汾
---------------------------------------------------------*/

NTSTATUS
AntinvaderNewCreateProcess(
	__out PHANDLE ProcessHandle,
	__in ACCESS_MASK DesiredAccess,
	__in POBJECT_ATTRIBUTES ObjectAttributes,
	__in HANDLE InheritFromProcessHandle,
	__in BOOLEAN InheritHandles,
	__in_opt HANDLE SectionHandle ,
	__in_opt HANDLE DebugPort ,
	__in_opt HANDLE ExceptionPort
	)
{
/*	//����ֵ
	NTSTATUS status;

	//��Ҫ�򿪽��̵�Ŀ¼���ļ�����
	PFILE_OBJECT pFileRootObject;

	//���ɴ򿪽��̵��ļ�����
	PFILE_OBJECT pFileObject;

	//�����ļ�·���Ŀռ� �Ȳ�һ����С.
	WCHAR  wPathString[ HOOK_NORMAL_PROCESS_PATH ];
	
	//�����ļ�·���ռ�ĵ�ַ
	PWSTR pPathString = wPathString;

	//�ļ�·��
	PUNICODE_STRING usFilePath = {0};

	//��������ļ�·�� ��ʱʹ��
	PUNICODE_STRING usFilePathNewAllocated = {0};

	//�ļ�·������
	ULONG ulPathLength;
	USHORT ustPathLength;

	//
	//�ȵ���ԭ���ZwCreateProcess��������
	//

	status = ZwCreateProcessOriginal(
			ProcessHandle,
			DesiredAccess,
			ObjectAttributes,
			InheritFromProcessHandle,
			InheritHandles,
			SectionHandle ,
			DebugPort ,
			ExceptionPort
			);

	//
	//�������ʧ�ܾͲ���Ҫ�ж���
	//

	if( !NT_SUCCESS(status) )
	{
		return status;
	}

	//
	//���жϽ��������Ƿ�ƥ�� ��ƥ��ͷ���
	//

	if( IsProcessConfidential( ObjectAttributes -> ObjectName ,NULL , NULL ))
	{
		return STATUS_SUCCESS;
	}

	//
	//��ʼ���ַ���
	//
	RtlInitEmptyUnicodeString(
		usFilePath,
		pPathString,
		HOOK_NORMAL_PROCESS_PATH
		);

	//
	//��ȡ��������·�����ļ�����,ʧ�ܾ�ֱ�ӷ���
	//

	status = ObReferenceObjectByHandle(
		ObjectAttributes -> RootDirectory,//·�����
		GENERIC_READ,//ֻ��
		*IoFileObjectType,//�ļ�����
		KernelMode,//�ں�ģʽ
		(PVOID *)&pFileRootObject,//��������ַ�Ŀռ�
		NULL//��������ʹ��NULL
		);

	if( !NT_SUCCESS(status) )
	{
		return STATUS_SUCCESS;
	}

	//
	//ʹ���ļ������ȡ·��
	//

	ulPathLength = FctGetFilePath(
		pFileRootObject,
		usFilePath,
		CONFIDENTIAL_FILE_NAME_FILE_OBJECT
		);

	//
	//�жϲ²���ڴ��Ƿ��С,�����ѯʧ����ulPathLength = 0,����ִ���������
	//
	if( ulPathLength > HOOK_NORMAL_PROCESS_PATH )
	{
		//
		//�����ڴ�,���Ž�������Ҳ������
		//
		pPathString = (PWSTR)ExAllocatePoolWithTag(
						NonPagedPool,
						ulPathLength + ObjectAttributes -> ObjectName -> Length + 1,
						MEM_HOOK_TAG
						); 

		//
		//���³�ʼ���ַ���
		//
		RtlInitEmptyUnicodeString(
				usFilePath,
				pPathString,
				(USHORT)(ulPathLength + ObjectAttributes -> ObjectName -> Length +1 )
				//·������ + һ��б�ܳ��� + �ļ�������
				);

		//
		//���²�ѯ
		//
		ulPathLength = FctGetFilePath(
				pFileRootObject,
				usFilePath,
				CONFIDENTIAL_FILE_NAME_FILE_OBJECT
				);
	}

	if( !ulPathLength )
	{
		//
		//�����ȡʧ��ʹ��QUERY_NAME_STRING��ѯ
		//

		ulPathLength = FctGetFilePath(
			pFileRootObject,
			usFilePath,
			CONFIDENTIAL_FILE_NAME_QUERY_NAME_STRING
			);

		if( ulPathLength > HOOK_NORMAL_PROCESS_PATH )
		{
			//
			//�����ڴ�,���Ž�������Ҳ������
			//
			pPathString = (PWSTR)ExAllocatePoolWithTag(
							NonPagedPool,
							ulPathLength + ObjectAttributes -> ObjectName -> Length + 1 ,
							MEM_HOOK_TAG
							); 

			//
			//���³�ʼ���ַ���
			//
			RtlInitEmptyUnicodeString(
					usFilePath,
					pPathString,
					(USHORT)(ulPathLength + ObjectAttributes -> ObjectName -> Length +1 )
					//·������ + һ��б�ܳ��� + �ļ�������
					);

			//
			//���²�ѯ
			//
			ulPathLength = FctGetFilePath(
					pFileRootObject,
					usFilePath,
					CONFIDENTIAL_FILE_NAME_QUERY_NAME_STRING
					);
		}

		if( !ulPathLength )
		{
			//
			//����ʧ��,û����,ֱ�ӷ���
			//

			return STATUS_SUCCESS;
		}
	}

	if( ulPathLength + 1 > usFilePath -> MaximumLength )
	{
		//
		//�����ڴ�,���Ž�������Ҳ������
		//
		pPathString = (PWSTR)ExAllocatePoolWithTag(
						NonPagedPool,
						ulPathLength + ObjectAttributes -> ObjectName -> Length + 1 ,
						MEM_HOOK_TAG
						); 

		//
		//���³�ʼ���ַ���
		//
		RtlInitEmptyUnicodeString(
				usFilePathNewAllocated,
				pPathString,
				(USHORT)(ulPathLength + ObjectAttributes -> ObjectName -> Length +1 )
				//·������ + һ��б�ܳ��� + �ļ�������
				);

		//
		//�����ַ���
		//
		RtlCopyUnicodeString( usFilePathNewAllocated , usFilePath );

		usFilePath = usFilePathNewAllocated;
	}

	//
	//�ж�·�������Ƿ���"\",������Ǿͼ���
	//

	if( usFilePath->Buffer[ulPathLength-1] != L'\\')
	{
		RtlAppendUnicodeToString(usFilePath , L"\\");
	}

	//
	//������Ͻ������ƴ�С�ֲ�����
	//
	if( ulPathLength + 1 +  ObjectAttributes -> ObjectName -> Length > 
												usFilePath -> MaximumLength )
	{
		//
		//�����ڴ�
		//
		pPathString = (PWSTR)ExAllocatePoolWithTag(
						NonPagedPool,
						ulPathLength + ObjectAttributes -> ObjectName -> Length + 1 ,
						MEM_HOOK_TAG
						); 

		//
		//���³�ʼ���ַ���
		//
		RtlInitEmptyUnicodeString(
				usFilePathNewAllocated,
				pPathString,
				(USHORT)(ulPathLength + ObjectAttributes -> ObjectName -> Length +1 )
				//·������ + һ��б�ܳ��� + �ļ�������
				);

		//
		//�����ַ���
		//
		RtlCopyUnicodeString( usFilePathNewAllocated , usFilePath );

		usFilePath = usFilePathNewAllocated;
	}

	//
	//���ļ���������ȥ
	//
	RtlAppendUnicodeStringToString(usFilePath,ObjectAttributes -> ObjectName);
	
	//
	//�����жϽ���·���Ƿ�ƥ�� ��ƥ��ͷ���
	//

	if( IsProcessConfidential( NULL ,usFilePath , NULL ))
	{
		return STATUS_SUCCESS;
	}
*/
	return STATUS_SUCCESS;
}

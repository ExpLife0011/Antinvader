///////////////////////////////////////////////////////////////////////////////
///
/// ��Ȩ���� (c) 2011 - 2012
///
/// ԭʼ�ļ�����	 : AntinvaderDriver.h
/// ��������         : AntinvaderDriver
/// ����ʱ��         : 2011-03-20
/// 	         
///
/// ����	         : Antinvader����������Ҫͷ�ļ�,���������;�̬���Ͷ���
///
/// ����ά��:
///  0000 [2011-03-20] ����汾.
///
///////////////////////////////////////////////////////////////////////////////

// $Id$

#ifndef __ANTINVADERDRIVER_H_VERSION__
#define __ANTINVADERDRIVER_H_VERSION__ 100

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif


#include "drvCommon.h"
#include "drvVersion.h"

//����Լ��
#include "..\Common.h"

// COMMUNICATE_PORT_NAME	 \\AntinvaderPort	�ܵ����� 
PRESET_UNICODE_STRING(usCommunicatePortName, COMMUNICATE_PORT_NAME);

#ifndef FILE_DEVICE_ANTINVADERDRIVER
#define FILE_DEVICE_ANTINVADERDRIVER 0x8000
#endif



//����֧��
//#if DBG
		
#define FILE_OBJECT_NAME_BUFFER(_file_object)	(_file_object)->FileName.Buffer
#define CURRENT_PROCESS_NAME_BUFFER ((PCHAR)PsGetCurrentProcess() + stGlobalProcessNameOffset)

//׷�ٷ�ʽ
#define DEBUG_TRACE_ERROR                           0x00000001  // Errors - whenever we return a failure code
#define DEBUG_TRACE_LOAD_UNLOAD                     0x00000002  // Loading/unloading of the filter
#define DEBUG_TRACE_INSTANCES                       0x00000004  // Attach / detatch of instances
#define DEBUG_TRACE_DATA_OPERATIONS		            0x00000008  // Operation to access / modify in memory metadata
#define DEBUG_TRACE_ALL_IO                          0x00000010  // All IO operations tracked by this filter
#define DEBUG_TRACE_NORMAL_INFO                     0x00000020  // Misc. information
#define DEBUG_TRACE_IMPORTANT_INFO                  0x00000040  // Important information
#define DEBUG_TRACE_CONFIDENTIAL					0x00000080
#define DEBUG_TRACE_TEMPORARY						0x00000100
#define DEBUG_TRACE_ALL                             0xFFFFFFFF  // All flags

//��ǰ��ʽ
#define DEBUG_TRACE_NOW								DEBUG_TRACE_TEMPORARY|DEBUG_TRACE_ERROR|DEBUG_TRACE_CONFIDENTIAL//DEBUG_TRACE_ALL

#define DebugTrace(_Level,_ProcedureName, _Data)	\
    if ((_Level) & (DEBUG_TRACE_NOW)) {               \
		DbgPrint("[Antinvader:"_ProcedureName"]\n\t\t\t");					\
		DbgPrint _Data;                              \
		DbgPrint("\n");								\
    }

#define DebugTraceFile(_Level,_ProcedureName,_FileName, _Data)		\
	if ((_Level) & (DEBUG_TRACE_NOW)) {								\
		DbgPrint("[Antinvader:"_ProcedureName"]%s\n\t\t\t",_FileName);	\
		DbgPrint _Data;												\
		DbgPrint("\n");												\
    }

#define DebugTraceFileAndProcess(_Level,_ProcedureName,_FileName, _Data)	\
    if ((_Level) & (DEBUG_TRACE_NOW)) {										\
		DbgPrint("[Antinvader:"_ProcedureName"]%ws:%s\n\t\t\t",_FileName,CURRENT_PROCESS_NAME_BUFFER); \
		DbgPrint _Data;														\
		DbgPrint("\n");														\
    }

		//
		//����
		//
/*		KdPrint(("DebugTestRead:!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n"	
				 "\t\tIRP_BUFFERED_IO: 			%d\n"	
				 "\t\tIRP_CLOSE_OPERATION:		%d\n"		
				 "\t\tIRP_DEALLOCATE_BUFFER:	%d\n" 		
				 "\t\tIRP_INPUT_OPERATION:		%d\n"		
				 "\t\tIRP_NOCACHE: 				%d\n"	
				 "\t\tIRP_PAGING_IO: 			%d\n"	
				 "\t\tIRP_SYNCHRONOUS_API:		%d\n" 		
				 "\t\tIRP_SYNCHRONOUS_PAGING_IO:%d\n"
				 "\t\tLength:                   %d\n"
				 "\t\tByteOffset                %d\n",	
					pIoParameterBlock -> IrpFlags&(IRP_BUFFERED_IO),
					pIoParameterBlock -> IrpFlags&(IRP_CLOSE_OPERATION),	
					pIoParameterBlock -> IrpFlags&(IRP_DEALLOCATE_BUFFER),	
					pIoParameterBlock -> IrpFlags&(IRP_INPUT_OPERATION),	
					pIoParameterBlock -> IrpFlags&(IRP_NOCACHE),
					pIoParameterBlock -> IrpFlags&(IRP_PAGING_IO),
					pIoParameterBlock -> IrpFlags&(IRP_SYNCHRONOUS_API),	
					pIoParameterBlock -> IrpFlags&(IRP_SYNCHRONOUS_PAGING_IO),
					pIoParameterBlock->Parameters.Read.Length,
					pIoParameterBlock->Parameters.Read.ByteOffset.QuadPart));*/

//������


#define DebugPrintFileObject(_header,_object,_cached)	KdPrint(("[Antinvader]%s.\n"		\
															"\t\tName:%ws\n"				\
															"\t\tCached %d\n"				\
															"\t\tFcb:0x%X\n",				\
															_header,						\
															_object->FileName.Buffer,		\
															_cached,						\
															_object->FsContext				\
															));								

#define DebugPrintFileStreamContext(_header,_object)		KdPrint(("[Antinvader]%s.\n"			\
															"\t\tName:%ws\n"				\
															"\t\tCached %d\n"				\
															"\t\tCachedFcb:0x%X\n"			\
															"\t\tNoneCachedFcb0x%X\n",		\
															_header,						\
															_object->usName.Buffer,			\
															_object->bCached,				\
															_object->pfcbCachedFCB,			\
															_object->pfcbNoneCachedFCB		\
															));										

//#else

//#define DebugTrace(_Level,_ProcedureName, _Data)             {NOTHING;}
//#define DebugPrintFileObject(_header,_object,_cached)  {NOTHING;}
//#define DebugPrintFileStreamContext(_header,_object)	{NOTHING;}

//#endif

// Values defined for "Method"
// METHOD_BUFFERED
// METHOD_IN_DIRECT
// METHOD_OUT_DIRECT
// METHOD_NEITHER
// 
// Values defined for "Access"
// FILE_ANY_ACCESS
// FILE_READ_ACCESS
// FILE_WRITE_ACCESS

const ULONG IOCTL_ANTINVADERDRIVER_OPERATION = CTL_CODE(FILE_DEVICE_ANTINVADERDRIVER, 0x01, METHOD_BUFFERED, FILE_READ_DATA | FILE_WRITE_DATA);

///////////////////////////
//	��������ͷ�ļ�����
//////////////////////////

//�����㷨
#include "BasicAlgorithm.h"

//��������ص�
#include "CallbackRoutine.h"

//������Ϣ����
#include "ProcessFunction.h"

//�����ļ�����
#include "ConfidentialFile.h"

//�����ļ�����
#include "FileFunction.h"

//���ܽ�������
#include "ConfidentialProcess.h"

//΢��������ͨ�ú���
#include "MiniFilterFunction.h"

//�ҹ�
#include "SystemHook.h"

//����ж��
NTSTATUS
Antinvader_Unload (
    __in FLT_FILTER_UNLOAD_FLAGS Flags
    );

//��������Ҫ���˵�IRP����
const FLT_OPERATION_REGISTRATION Callbacks[] = {
	//����
	{ IRP_MJ_CREATE,0,Antinvader_PreCreate,Antinvader_PostCreate },
	//�ر�
	{ IRP_MJ_CLOSE,0,Antinvader_PreClose,Antinvader_PostClose},
	//����
	{ IRP_MJ_CLEANUP,0,Antinvader_PreCleanUp,Antinvader_PostCleanUp},
	//���ļ�
	{ IRP_MJ_READ,0,Antinvader_PreRead,Antinvader_PostRead},
	//д�ļ� ��������
	{ IRP_MJ_WRITE,0,Antinvader_PreWrite,Antinvader_PostWrite},
	//�����ļ���Ϣ,������������ͷ
	{ IRP_MJ_SET_INFORMATION,0,Antinvader_PreSetInformation,Antinvader_PostSetInformation},
	//Ŀ¼
	{ IRP_MJ_DIRECTORY_CONTROL,0,Antinvader_PreDirectoryControl,Antinvader_PostDirectoryControl},
	//��ȡ�ļ���Ϣ
	{ IRP_MJ_QUERY_INFORMATION,0,Antinvader_PreQueryInformation,Antinvader_PostQueryInformation},

    { IRP_MJ_OPERATION_END }
};

CONST FLT_CONTEXT_REGISTRATION Contexts[] = {

	{ FLT_VOLUME_CONTEXT, 0, Antinvader_CleanupContext, sizeof(VOLUME_CONTEXT), MEM_CALLBACK_TAG },

    { FLT_STREAM_CONTEXT, 0, Antinvader_CleanupContext, FILE_STREAM_CONTEXT_SIZE, MEM_TAG_FILE_TABLE },

	{ FLT_CONTEXT_END }
};


const FLT_REGISTRATION FilterRegistration = {//����ע�����

    sizeof( FLT_REGISTRATION ),         //  ��С
    FLT_REGISTRATION_VERSION,           //  �汾
    0,                                  //  ��־

    Contexts,                               //  ������
    Callbacks,                          //  �����ص����� ����FLT_OPERATION_REGISTRATION

    Antinvader_Unload,                  //  ж�ص���

    Antinvader_InstanceSetup,           //  ��������ʵ��
    NULL,//Antinvader_InstanceQueryTeardown,   //  ���ٲ�ѯʵ��
    NULL,//Antinvader_InstanceTeardownStart,   //  ��ʼʵ�����ٻص�
    NULL,//Antinvader_InstanceTeardownComplete,//  ���ʵ�����ٻص�

    NULL,                               //  �����ļ����ƻص� (δʹ�� NULL)
    NULL,                               //  ����Ŀ���ļ����ƻص�(δʹ�� NULL)
    NULL                                //  ��׼�����������ƻ���(δʹ�� NULL)
};


#endif // __ANTINVADERDRIVER_H_VERSION__

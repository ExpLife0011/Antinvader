///////////////////////////////////////////////////////////////////////////////
///
/// ��Ȩ���� (c) 2011 - 2012
///
/// ԭʼ�ļ�����	 : MiniFilterFunction.h
/// ��������         : AntinvaderDriver
/// ����ʱ��         : 2011-04-2
/// 	         
///
/// ����	         : ����΢����������ͨ�ú���ͷ�ļ�
///
/// ����ά��:
///  0000 [2011-04-2]  ����汾.
///
///////////////////////////////////////////////////////////////////////////////

#pragma once

////////////////////////
//		�궨��
////////////////////////

//�����µĻ������ڴ��־
#define MEM_TAG_READ_BUFFER						'read'
#define MEM_TAG_WRITE_BUFFER					'writ'
#define MEM_TAG_DIRECTORY_CONTROL_BUFFER		'dirc'

//�����»���Ļ�����;
typedef enum _ALLOCATE_BUFFER_TYPE
{
	Allocate_BufferRead = 1,//������
	Allocate_BufferWrite,//д����
	Allocate_BufferDirectoryControl
}ALLOCATE_BUFFER_TYPE;

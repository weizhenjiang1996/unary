#pragma once
#include "Log.h"
#include "string"
#include "iostream"
using namespace std;


class FileOperate
{
public:
	FileOperate(void);
	~FileOperate(void);
	void FileOperate::SetLastError(CString lastErrInfo) ;
	CString FileOperate::GetLastError(void) ;
	bool FileOperate::OpenFile(string sFilePath);
	long FileOperate::ReadFileLine(byte* readLine,long readLineSize);
	long FileOperate::ReadFileByte(long bytePosition);
	bool FileOperate::WriteFileline(byte* buf, long bufSize);
	bool FileOperate::CloseFile(void);
	virtual bool FileOperate::LineEnd(byte* ReadByte,long i,long ReadLen)=0;

	Log log;
	CString m_LastError;
	HANDLE m_Handle;
	long m_ReadPosition;
	long m_FileSize;
	long m_FileReadSize;
	DWORD m_bytesRead;
	long m_bufferRead;
	long m_ReadLen;
	int m_EenLen;
	DWORD m_bytesWrite;
	byte * m_ReadByte;
};

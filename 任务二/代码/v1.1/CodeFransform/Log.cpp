#include "StdAfx.h"
#include "Log.h"
#include "locale"
Log::Log(void){}
Log::~Log(void){}
void Log::setLastError(CString lastErrInfo) {
	m_lastError = lastErrInfo;
}
CString Log::getLastError() {
	return m_lastError;
}
/******************************************************************
函数名：OutputLog
功能说明：输出到日志文件
输入：记录的内容
输出：void
*******************************************************************/
void Log::OutputLog(CString msg) {
	try {
		CString lg = m_browse.GetWorkFold();
		lg += "\\CodeFransform.log";

		CStdioFile outFile;
		CFileException pError;

		setlocale(LC_CTYPE, ("chs"));

		if (!outFile.Open(lg, CFile::modeNoTruncate | CFile::modeCreate
			| CFile::modeWrite | CFile::typeText, &pError)) {
			Log log;
			setLastError(_T("日志文件打开错误！"));
			log.OutputLog(_T("日志文件打开错误"));
			return;
		}
		CString msLine;

		CTime tt = CTime::GetCurrentTime();
		msLine = tt.Format("[%Y-%m-%d %A, %H:%M:%S] ") + msg;
		msLine += "\n";

		outFile.SeekToEnd();
		outFile.WriteString(msLine);
		outFile.Close();
	}
	catch (CFileException *fx) {
		fx->Delete();
	}
}

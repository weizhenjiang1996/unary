#include "StdAfx.h"
#include "Browse.h"
Browse::Browse(void)
{
}

Browse::~Browse(void)
{
}
void Browse::SetLastError(CString lastErrInfo) {
	m_LastError=lastErrInfo;
}

CString Browse::GetLastError() {
	return m_LastError;
}

/******************************************************************
函数名：BrowseForFolder
功能说明：浏览文件夹目录框
输入：void
输出：文件夹路径
*******************************************************************/
CString Browse::BrowseForFolder(void) {
    BROWSEINFO sInfo;
    ::ZeroMemory(&sInfo, sizeof(BROWSEINFO));
    sInfo.pidlRoot = 0;
    sInfo.lpszTitle = _T("请选择一个文件夹：");
    sInfo.ulFlags = BIF_DONTGOBELOWDOMAIN | BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE | BIF_EDITBOX;
    sInfo.lpfn = NULL;
    LPITEMIDLIST lpidlBrowse = ::SHBrowseForFolder(&sInfo);
    TCHAR FolderPath[MAX_PATH] = {0};
    ::SHGetPathFromIDList(lpidlBrowse, FolderPath);
    return FolderPath;
}
/******************************************************************
函数名：BrowseForFile
功能说明：浏览文件目录框
输入：void
输出：文件路径
*******************************************************************/
CString Browse::BrowseForFile(HWND m_hWnd) {
	TCHAR path[MAX_PATH] = {0};   
	CString str;
	OPENFILENAME of= {0};   
	of.lStructSize = sizeof(of);   
	of.hwndOwner = m_hWnd;   
	of.lpstrFilter = _T("txt文件(*.txt)\0*.txt\0"); 
	of.lpstrFile = path; 
	of.nMaxFile = sizeof(path)/sizeof(*path);   
	of.nFilterIndex = 0;   
	of.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_EXPLORER ;
	BOOL bSel = GetOpenFileName(&of);   
	str.Format(path);
	return str;
}
/******************************************************************
函数名：BrowseFileFor
功能说明：另存为目录框
输入：void
输出：文件路径
*******************************************************************/
CString Browse::BrowseFileFor() {
	CString filepath;  
	TCHAR szFilter[] = _T("文本文件(*.txt)|*.txt|所有文件(*.*)|*.*||");  
	CFileDialog fileDlg(FALSE, _T("txt"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter);  
	if (IDOK == fileDlg.DoModal()) {
		filepath = fileDlg.GetPathName();
		return filepath;
	}
	else return CString("");
}
/******************************************************************
函数名：GetWorkDir
功能说明：获得当前项目的路径
输入：void
输出：当前项目的路径
*******************************************************************/
CString Browse::GetWorkFold() {
    HMODULE module = GetModuleHandle(0);
    TCHAR pFileName[MAX_PATH];
    GetModuleFileName(module, pFileName, MAX_PATH);
    CString csFullPath(pFileName);
    int nPos = csFullPath.ReverseFind(_T('\\'));
    if(nPos < 0)
        return CString("");
    else
        return csFullPath.Left(nPos);
}

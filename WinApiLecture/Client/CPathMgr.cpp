#include "pch.h"
#include "CPathMgr.h"
#include "CCore.h"

CPathMgr::CPathMgr() : m_szContentPath{}
{

}

CPathMgr::~CPathMgr()
{

}


void CPathMgr::init()
{
	//현재 프로젝트의 경로를 가져오고
	GetCurrentDirectory(255, m_szContentPath);

	int iLen = (int)wcslen(m_szContentPath);


	//상위 폴더(솔루션파일 폴더)까지 경로 자른 다음,
	for (int i = iLen; i >= 0; --i)
	{
		if (m_szContentPath[i] == '\\')
		{
			m_szContentPath[i] = '\0';
			break;
		}
	}

	//컨텐츠 폴더 경로를 문자열 끝에 붙인다.
	wcscat_s(m_szContentPath, 255, L"\\bin\\content\\");

	//SetWindowText(CCore::GetInst()->GetMainHwnd(), m_szContentPath);
}

wstring CPathMgr::GetRelativePath(const wchar_t* _filepath)
{
	wstring strFilePath = _filepath;

	//콘텐츠 폴더의 절대경로
	size_t iAbsLen = wcslen(m_szContentPath);

	//원하는 파일이 들어있는 절대경로
	size_t iFullLen = strFilePath.length();

	//원하는 파일이 있는 경로에서, 콘텐츠 폴더의 절대경로를 빼면 상대경로가 됨
	//그래서 파일의 절대경로 문자열 에서, 콘텐츠 폴더 경로 길이만큼 가서, 상대경로 길이만큼 문자열을 뽑아온다.
	wstring strRelativePath = strFilePath.substr(iAbsLen, iFullLen - iAbsLen);
	
	return strRelativePath;
}

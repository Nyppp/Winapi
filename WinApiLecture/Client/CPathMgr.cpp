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

	int iLen = wcslen(m_szContentPath);


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

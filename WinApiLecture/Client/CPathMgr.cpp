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
	//���� ������Ʈ�� ��θ� ��������
	GetCurrentDirectory(255, m_szContentPath);

	int iLen = wcslen(m_szContentPath);


	//���� ����(�ַ������ ����)���� ��� �ڸ� ����,
	for (int i = iLen; i >= 0; --i)
	{
		if (m_szContentPath[i] == '\\')
		{
			m_szContentPath[i] = '\0';
			break;
		}
	}

	//������ ���� ��θ� ���ڿ� ���� ���δ�.
	wcscat_s(m_szContentPath, 255, L"\\bin\\content\\");

	//SetWindowText(CCore::GetInst()->GetMainHwnd(), m_szContentPath);
}

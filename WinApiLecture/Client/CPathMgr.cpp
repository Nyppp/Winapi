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

	int iLen = (int)wcslen(m_szContentPath);


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

wstring CPathMgr::GetRelativePath(const wchar_t* _filepath)
{
	wstring strFilePath = _filepath;

	//������ ������ ������
	size_t iAbsLen = wcslen(m_szContentPath);

	//���ϴ� ������ ����ִ� ������
	size_t iFullLen = strFilePath.length();

	//���ϴ� ������ �ִ� ��ο���, ������ ������ �����θ� ���� ����ΰ� ��
	//�׷��� ������ ������ ���ڿ� ����, ������ ���� ��� ���̸�ŭ ����, ����� ���̸�ŭ ���ڿ��� �̾ƿ´�.
	wstring strRelativePath = strFilePath.substr(iAbsLen, iFullLen - iAbsLen);
	
	return strRelativePath;
}

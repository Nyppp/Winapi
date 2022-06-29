#include "pch.h"
#include "CResMgr.h"
#include "CTexture.h"
#include "CPathMgr.h"

CResMgr::CResMgr()
{

}

CResMgr::~CResMgr()
{
	map<wstring, CTexture*>::iterator iter = m_mapTex.begin();

	for (; iter != m_mapTex.end(); ++iter)
	{
		delete iter->second;
	}
}

//�ؽ��� ������ �ҷ����� �Լ�
CTexture* CResMgr::LoadTexture(const wstring& _strKey, const wstring& _strRelativePath)
{
	//���� �ؽ����� Ű���� �̹� �ִ� ���̶��, �ִ°Ÿ� ��ȯ���ش�.
	CTexture* pTex = FindTexture(_strKey);
	if (pTex != nullptr)
	{
		return pTex;
	}

	//���ٸ�, ��� �����ڸ� ���� ����θ� ��������,
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;
	
	pTex = new CTexture;
	pTex->Load(strFilePath);

	//�ؽ��� ��ü�� Ű���� ����� ������ ����
	pTex->SetKey(_strKey);
	pTex->SetRelatvieKey(_strRelativePath);

	//Ű���� ����θ� �� ����� ����
	m_mapTex.insert(make_pair(_strKey, pTex));

	//�ҷ��� �ؽ��ĸ� ��ȯ
	return pTex;
}

CTexture* CResMgr::FindTexture(const wstring& _strKey)
{
	map<wstring, CTexture*>::iterator iter = m_mapTex.find(_strKey);
	if (iter == m_mapTex.end())
	{
		return nullptr;
	}

	return iter->second;
}

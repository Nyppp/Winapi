#include "pch.h"
#include "CResMgr.h"
#include "CTexture.h"
#include "CPathMgr.h"
#include "CRes.h"

CResMgr::CResMgr()
{

}

CResMgr::~CResMgr()
{
	Safe_Delete_Map(m_mapTex);
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
	map<wstring, CRes*>::iterator iter = m_mapTex.find(_strKey);
	if (iter == m_mapTex.end())
	{
		return nullptr;
	}

	return (CTexture*)iter->second;
}

//�ؽ��ĸ� ����� �Լ�
CTexture* CResMgr::CreateTexture(const wstring& _strKey, UINT _iWidth, UINT _iHeight)
{
	//���� �ؽ����� Ű���� �̹� �ִ� ���̶��, �ִ°Ÿ� ��ȯ���ش�.
	CTexture* pTex = FindTexture(_strKey);
	if (pTex != nullptr)
	{
		return pTex;
	}

	pTex = new CTexture;

	pTex->Create(_iWidth, _iHeight);

	pTex->SetKey(_strKey);

	//Ű���� ����θ� �� ����� ����
	m_mapTex.insert(make_pair(_strKey, pTex));

	//�ҷ��� �ؽ��ĸ� ��ȯ
	return pTex;
}

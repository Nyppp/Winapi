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

//텍스쳐 파일을 불러오는 함수
CTexture* CResMgr::LoadTexture(const wstring& _strKey, const wstring& _strRelativePath)
{
	//만약 텍스쳐의 키값이 이미 있는 값이라면, 있는거를 반환해준다.
	CTexture* pTex = FindTexture(_strKey);
	if (pTex != nullptr)
	{
		return pTex;
	}

	//없다면, 경로 관리자를 통해 상대경로를 가져오고,
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;
	
	pTex = new CTexture;
	pTex->Load(strFilePath);

	//텍스쳐 객체에 키값과 상대경로 정보를 저장
	pTex->SetKey(_strKey);
	pTex->SetRelatvieKey(_strRelativePath);

	//키값과 상대경로를 맵 멤버에 저장
	m_mapTex.insert(make_pair(_strKey, pTex));

	//불러온 텍스쳐를 반환
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

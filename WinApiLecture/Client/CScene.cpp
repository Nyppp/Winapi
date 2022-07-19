#include "pch.h"
#include "CScene.h"
#include "CObject.h"
#include "CTile.h"
#include "CResMgr.h"
#include "CPathMgr.h"

CScene::CScene()
	: m_iTileX(0), m_iTileY(0)
{
}

CScene::~CScene()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			//원래 씬이 사라지면, 벡터는 당연히 클래스 내부적으로 벡터 소멸자를 통해 사라지지만,
			//벡터가 가리키고 있는 주소값, 즉 오브젝트들의 주소는 계속 남아있게 되어 이들을 직접 삭제해야 함
			//이를 씬의 파생클래스가 아닌 씬 부모클래스에서 일괄적으로 하게끔 코드 작성
			delete m_arrObj[i][j];
		}
	}
}

void CScene::update()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			if (m_arrObj[i][j]->IsDead() == false)
			{
				m_arrObj[i][j]->update();
			}
		}
	}
}

//게임 로직 이외의 업데이트 구문(콜라이더의 상태 변화 등)
void CScene::finalupdate()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			m_arrObj[i][j]->finalupdate();
		}
	}
}

void CScene::render(HDC _dc)
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		vector<CObject*>::iterator iter = m_arrObj[i].begin();

		for (;iter != m_arrObj[i].end();)
		{
			if ((*iter)->IsDead() == false)
			{
				(*iter)->render(_dc);
				++iter;
			}

			else
			{
				iter = m_arrObj[i].erase(iter);
			}
		}
	}
}

void CScene::DeleteGroup(GROUP_TYPE _eTarget)
{
	//템플릿 함수이기에 타입 지정해줘야 함
	Safe_Delete_Vec<CObject*>(m_arrObj[(UINT)_eTarget]);
}

void CScene::DeleteAll()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		DeleteGroup((GROUP_TYPE)i);
	}
}

void CScene::CreateTile(UINT _iXCount, UINT _iYCount)
{
	CTexture* pTileTex = CResMgr::GetInst()->LoadTexture(L"Tile", L"texture\\tile\\Tile.bmp");

	DeleteGroup(GROUP_TYPE::TILE);
	
	m_iTileX = _iXCount;
	m_iTileY = _iYCount;

	for (int i = 0; i < _iYCount; ++i)
	{
		for (int j = 0; j < _iXCount; ++j)
		{
			CTile* pTile = new CTile();

			pTile->SetPos(Vec2(float(TILE_SIZE * j), float(TILE_SIZE * i)));
			pTile->SetTexture(pTileTex);

			AddObject(pTile, GROUP_TYPE::TILE);
		}
	}
}

void CScene::LoadTile(const wstring& _strRelativePath)
{
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();

	strFilePath += _strRelativePath;
	FILE* pFile = nullptr;

	//읽기 모드는, 파일이 존재하지 않으면 에러 발생하도록 설계
	_wfopen_s(&pFile, strFilePath.c_str(), L"rb");
	assert(pFile);

	//파일 내에 담긴 타일갯수 정보를 불러오고, 타일 맵 생성
	UINT xCount = 0;
	UINT yCount = 0;

	fread(&xCount, sizeof(UINT), 1, pFile);
	fread(&yCount, sizeof(UINT), 1, pFile);

	CreateTile(xCount, yCount);

	const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);

	//타일 하나하나마다 자신이 어떤 텍스쳐가 있고, 서로 다른 기능을 하기에 각자가 자신을 저장
	for (size_t i = 0; i < vecTile.size(); ++i)
	{
		((CTile*)vecTile[i])->Load(pFile);
	}

	fclose(pFile);
}

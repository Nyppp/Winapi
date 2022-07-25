#include "pch.h"
#include "CScene.h"
#include "CObject.h"
#include "CTile.h"
#include "CResMgr.h"
#include "CPathMgr.h"
#include "CCamera.h"
#include "CCore.h"

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

//씬에 존재하는 모든 오브젝트를 돌며 렌더링
//타일 갯수가 100x100정도로 많아지면, 프레임 드랍 발생 -> 타일에 대해서는 예외처리 필요.
void CScene::render(HDC _dc)
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		if ((UINT)GROUP_TYPE::TILE == i)
		{
			//타일에 대해서는 전용 렌더링 함수를 사용 -> 타일은 갯수가 무수히 많을 수 있기 때문에
			render_tile(_dc);
			continue;
		}
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

void CScene::render_tile(HDC _dc)
{
	vector<CObject*> vecTile = GetGroupObject(GROUP_TYPE::TILE);

	//카메라가 보고있는 범위 내의 타일만을 렌더링
	Vec2 vCamLook = CCamera::GetInst()->GetLookAt(); //카메라가 보는 좌표 중앙
	Vec2 vResoulution = CCore::GetInst()->GetResolution(); //화면 해상도

	Vec2 vLeftTop = vCamLook - vResoulution / 2.f; //좌상단

	int iTileSize = TILE_SIZE;

	//좌상단 좌표에 가장 맨 처음으로 오는 타일의 위치가 몇행 몇열인지 계산
	int iLTCol = (int)vLeftTop.x / iTileSize;
	int iLTRow = (int)vLeftTop.y / iTileSize;

	int iClientWidth = (int)vResoulution.x / iTileSize + 1;
	int iClientHeight = (int)vResoulution.y / iTileSize + 1;

	//현재 열과 행을 바탕으로, 해상도 범위만큼 반복하여 타일을 렌더링 한다.
	for (int iCurRow = iLTRow; iCurRow < (iLTRow + iClientHeight); ++iCurRow)
	{
		for (int iCurCol = iLTCol; iCurCol < (iLTCol + iClientWidth); ++iCurCol)
		{
			//인덱스 범위를 초과한다면 예외처리
			if (iCurCol < 0 || iCurCol >= m_iTileX || iCurRow < 0 || iCurRow >= m_iTileY)
			{
				continue;
			}

			int iIdx = (m_iTileX * iCurRow) + iCurCol;

			vecTile[iIdx]->render(_dc);
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

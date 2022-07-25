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
			//���� ���� �������, ���ʹ� �翬�� Ŭ���� ���������� ���� �Ҹ��ڸ� ���� ���������,
			//���Ͱ� ����Ű�� �ִ� �ּҰ�, �� ������Ʈ���� �ּҴ� ��� �����ְ� �Ǿ� �̵��� ���� �����ؾ� ��
			//�̸� ���� �Ļ�Ŭ������ �ƴ� �� �θ�Ŭ�������� �ϰ������� �ϰԲ� �ڵ� �ۼ�
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

//���� ���� �̿��� ������Ʈ ����(�ݶ��̴��� ���� ��ȭ ��)
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

//���� �����ϴ� ��� ������Ʈ�� ���� ������
//Ÿ�� ������ 100x100������ ��������, ������ ��� �߻� -> Ÿ�Ͽ� ���ؼ��� ����ó�� �ʿ�.
void CScene::render(HDC _dc)
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		if ((UINT)GROUP_TYPE::TILE == i)
		{
			//Ÿ�Ͽ� ���ؼ��� ���� ������ �Լ��� ��� -> Ÿ���� ������ ������ ���� �� �ֱ� ������
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

	//ī�޶� �����ִ� ���� ���� Ÿ�ϸ��� ������
	Vec2 vCamLook = CCamera::GetInst()->GetLookAt(); //ī�޶� ���� ��ǥ �߾�
	Vec2 vResoulution = CCore::GetInst()->GetResolution(); //ȭ�� �ػ�

	Vec2 vLeftTop = vCamLook - vResoulution / 2.f; //�»��

	int iTileSize = TILE_SIZE;

	//�»�� ��ǥ�� ���� �� ó������ ���� Ÿ���� ��ġ�� ���� ����� ���
	int iLTCol = (int)vLeftTop.x / iTileSize;
	int iLTRow = (int)vLeftTop.y / iTileSize;

	int iClientWidth = (int)vResoulution.x / iTileSize + 1;
	int iClientHeight = (int)vResoulution.y / iTileSize + 1;

	//���� ���� ���� ��������, �ػ� ������ŭ �ݺ��Ͽ� Ÿ���� ������ �Ѵ�.
	for (int iCurRow = iLTRow; iCurRow < (iLTRow + iClientHeight); ++iCurRow)
	{
		for (int iCurCol = iLTCol; iCurCol < (iLTCol + iClientWidth); ++iCurCol)
		{
			//�ε��� ������ �ʰ��Ѵٸ� ����ó��
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
	//���ø� �Լ��̱⿡ Ÿ�� ��������� ��
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

	//�б� ����, ������ �������� ������ ���� �߻��ϵ��� ����
	_wfopen_s(&pFile, strFilePath.c_str(), L"rb");
	assert(pFile);

	//���� ���� ��� Ÿ�ϰ��� ������ �ҷ�����, Ÿ�� �� ����
	UINT xCount = 0;
	UINT yCount = 0;

	fread(&xCount, sizeof(UINT), 1, pFile);
	fread(&yCount, sizeof(UINT), 1, pFile);

	CreateTile(xCount, yCount);

	const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);

	//Ÿ�� �ϳ��ϳ����� �ڽ��� � �ؽ��İ� �ְ�, ���� �ٸ� ����� �ϱ⿡ ���ڰ� �ڽ��� ����
	for (size_t i = 0; i < vecTile.size(); ++i)
	{
		((CTile*)vecTile[i])->Load(pFile);
	}

	fclose(pFile);
}

#include "pch.h"
#include "CTile.h"

#include "CTexture.h"


CTile::CTile() : m_pTileTex(nullptr), m_iImgIdx(0), m_iMaximgIdx(0)
{
	//Ÿ���� ��� 64x64�ȼ��� ����
	SetScale(Vec2(TILE_SIZE, TILE_SIZE));
}

CTile::~CTile()
{
}

//Ÿ���� �ٸ� ������Ʈ�� �ٸ���, �ڽ��� ��ǥ�� ������ ���� �»��.
void CTile::render(HDC _dc)
{
	//�ؽ��İ� ������ ȭ�鿡 �׸��� �ʴ´�.
	if (m_pTileTex == nullptr || m_iImgIdx == -1)
	{
		return;
	}

	UINT iWidth = m_pTileTex->Width();
	UINT iHeight = m_pTileTex->Height();

	//�ؽ��İ� Ÿ��ũ�� �������� ����, �� ������ ���
	UINT iMaxCol = iWidth / TILE_SIZE;
	UINT iMaxRow = iHeight / TILE_SIZE;

	//��, �� ũ�⸦ �������� �ؽ��İ� �� ĭ���� ����صд�.
	m_iMaximgIdx = iMaxCol * iMaxRow;

	UINT iCurRow = (UINT)m_iImgIdx / iMaxCol;
	UINT iCurCol = (UINT)m_iImgIdx % iMaxCol;

	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(GetPos());
	Vec2 vScale = GetScale();

	BitBlt(_dc,
		int(vRenderPos.x), int(vRenderPos.y),
		int(vScale.x), int(vScale.y),
		m_pTileTex->GetDC(),
		iCurCol * TILE_SIZE, iCurRow * TILE_SIZE,
		SRCCOPY);
}

void CTile::Save(FILE* _pFile)
{
	fwrite(&m_iImgIdx, sizeof(int), 1, _pFile);
}

void CTile::Load(FILE* _pFile)
{
	fread(&m_iImgIdx, sizeof(int), 1, _pFile);
}

void CTile::update()
{
}


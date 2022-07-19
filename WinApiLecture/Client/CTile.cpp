#include "pch.h"
#include "CTile.h"

#include "CTexture.h"


CTile::CTile() : m_pTileTex(nullptr), m_iImgIdx(0), m_iMaximgIdx(0)
{
	//타일은 모두 64x64픽셀로 고정
	SetScale(Vec2(TILE_SIZE, TILE_SIZE));
}

CTile::~CTile()
{
}

//타일은 다른 오브젝트와 다르게, 자신의 좌표가 렌더링 기준 좌상단.
void CTile::render(HDC _dc)
{
	//텍스쳐가 없으면 화면에 그리지 않는다.
	if (m_pTileTex == nullptr || m_iImgIdx == -1)
	{
		return;
	}

	UINT iWidth = m_pTileTex->Width();
	UINT iHeight = m_pTileTex->Height();

	//텍스쳐가 타일크기 기준으로 몇행, 몇 열인지 계산
	UINT iMaxCol = iWidth / TILE_SIZE;
	UINT iMaxRow = iHeight / TILE_SIZE;

	//행, 열 크기를 바탕으로 텍스쳐가 몇 칸인지 계산해둔다.
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


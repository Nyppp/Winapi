#include "pch.h"
#include "CTile.h"

#include "CTexture.h"


CTile::CTile() : m_pTileTex(nullptr), m_iIdx(20)
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
	if (m_pTileTex == nullptr || m_iIdx == -1)
	{
		return;
	}

	UINT iWidth = m_pTileTex->Width();
	UINT iHeight = m_pTileTex->Height();

	//텍스쳐가 타일크기 기준으로 몇행, 몇 열인지 계산
	UINT iMaxCol = iWidth / TILE_SIZE;
	UINT iMaxRow = iHeight / TILE_SIZE;


	UINT iCurRow = (UINT)m_iIdx / iMaxRow;
	UINT iCurCol = (UINT)m_iIdx % iMaxCol;

	//행은 나머지 연산이기에, 범위를 초과할 일이 없지만 열은 초과할 가능성이 있음 -> 예외처리
	if (iCurRow >= iMaxRow)
	{
		assert(nullptr);
	}

	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(GetPos());
	Vec2 vScale = GetScale();

	BitBlt(_dc,
		int(vRenderPos.x), int(vRenderPos.y),
		int(vScale.x), int(vScale.y),
		m_pTileTex->GetDC(),
		iCurCol * TILE_SIZE, iCurRow * TILE_SIZE,
		SRCCOPY);
}

void CTile::update()
{
}

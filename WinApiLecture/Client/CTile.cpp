#include "pch.h"
#include "CTile.h"

#include "CTexture.h"


CTile::CTile() : m_pTileTex(nullptr), m_iIdx(20)
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
	if (m_pTileTex == nullptr || m_iIdx == -1)
	{
		return;
	}

	UINT iWidth = m_pTileTex->Width();
	UINT iHeight = m_pTileTex->Height();

	//�ؽ��İ� Ÿ��ũ�� �������� ����, �� ������ ���
	UINT iMaxCol = iWidth / TILE_SIZE;
	UINT iMaxRow = iHeight / TILE_SIZE;


	UINT iCurRow = (UINT)m_iIdx / iMaxRow;
	UINT iCurCol = (UINT)m_iIdx % iMaxCol;

	//���� ������ �����̱⿡, ������ �ʰ��� ���� ������ ���� �ʰ��� ���ɼ��� ���� -> ����ó��
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

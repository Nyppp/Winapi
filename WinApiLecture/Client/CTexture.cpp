#include "pch.h"
#include "CTexture.h"
#include "CCore.h"

CTexture::CTexture() : m_hBit(0), m_dc(0), m_bitInfo{}
{
}

CTexture::~CTexture()
{
	DeleteDC(m_dc);
	DeleteObject(m_hBit);
}

void CTexture::Load(const wstring& _strFilePath)
{
	m_hBit = (HBITMAP)LoadImage(nullptr, _strFilePath.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE );
	assert(m_hBit);

	//비트맵과 연결할 dc
	m_dc = CreateCompatibleDC(CCore::GetInst()->GetMainDC());

	//비트맵과 DC연결
	HBITMAP hPrevBit = (HBITMAP)SelectObject(m_dc, m_hBit);
	DeleteObject(hPrevBit);
	
	//비트맵의 정보를 멤버함수에 저장
	GetObject(m_hBit, sizeof(BITMAP), &m_bitInfo);
}

//자체적으로 텍스쳐 생성
void CTexture::Create(UINT _iWidth, UINT _iHeight)
{
	HDC maindc = CCore::GetInst()->GetMainDC();

	m_hBit = CreateCompatibleBitmap(maindc, _iWidth, _iHeight);
	m_dc = CreateCompatibleDC(maindc);

	HBITMAP hOldBit = (HBITMAP)SelectObject(m_dc, m_hBit);

	DeleteObject(hOldBit);

	//비트맵의 정보를 멤버함수에 저장
	GetObject(m_hBit, sizeof(BITMAP), &m_bitInfo);
}

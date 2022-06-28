#pragma once
class CPathMgr
{
	SINGLE(CPathMgr);

private:
	wchar_t		m_szContentPath[255]; //윈도우 경로는 255글자 제한

public:
	void init();
	const wchar_t* GetContentPath() { return m_szContentPath; }
};


#pragma once
class CPathMgr
{
	SINGLE(CPathMgr);

private:
	wchar_t		m_szContentPath[256]; //윈도우 경로는 255글자 제한
	wchar_t		m_szRelativePath[256];

public:
	void init();
	const wchar_t* GetContentPath() { return m_szContentPath; }

	wstring GetRelativePath(const wchar_t* _filepath);
};


#pragma once
class CRes
{
private:
	wstring m_strKey;			//리소스 키
	wstring m_strRelativePath;	//리소스 상대경로

public:
	void SetKey(const wstring& _strKey) { m_strKey = _strKey; }
	void SetRelatvieKey(const wstring& _strPath) { m_strRelativePath = _strPath; }

	const wstring& GetKey() { return m_strKey; }
	const wstring& GetRelativeKey() { return m_strRelativePath; }

public:
	CRes();
	//CRes 클래스는 상속 전용이기에, 기능을 사용하는 건 모두 자식클래스이다.
	//만약 CRes의 소멸자가 가상함수가 아니면, 자식의 소멸자가 호출되지 않는다.
	virtual ~CRes();
};
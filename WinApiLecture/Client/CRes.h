#pragma once
class CRes
{
private:
	wstring m_strKey;			//���ҽ� Ű
	wstring m_strRelativePath;	//���ҽ� �����

public:
	void SetKey(const wstring& _strKey) { m_strKey = _strKey; }
	void SetRelatvieKey(const wstring& _strPath) { m_strRelativePath = _strPath; }

	const wstring& GetKey() { return m_strKey; }
	const wstring& GetRelativeKey() { return m_strRelativePath; }

public:
	CRes();
	//CRes Ŭ������ ��� �����̱⿡, ����� ����ϴ� �� ��� �ڽ�Ŭ�����̴�.
	//���� CRes�� �Ҹ��ڰ� �����Լ��� �ƴϸ�, �ڽ��� �Ҹ��ڰ� ȣ����� �ʴ´�.
	virtual ~CRes();
};
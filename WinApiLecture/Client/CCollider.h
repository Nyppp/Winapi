#pragma once

class CObject;

class CCollider
{
private:
	CObject* m_pOwner;
	
	friend class CObject;

public:
	CCollider();
	~CCollider();

public:
	void finalupdate();
};


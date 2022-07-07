#pragma once

class CCollider;

class CObject
{
private:
	//트랜스폼 정보는 실수값으로 가지고 있지만, 렌더링 시에 정수형으로 캐스팅
	Vec2 m_vPos;
	Vec2 m_vScale;

	wstring m_strName;

	CCollider* m_pCollider;

	bool m_bAlive;

public:
	CObject();
	virtual ~CObject();

public:
	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 GetPos() { return m_vPos; }
	Vec2 GetScale() { return m_vScale; }

	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	CCollider* GetCollider() { return m_pCollider; }

public:
	//가상함수에 = 0 을 붙이면, 무조건 자식 오브젝트에서의 오버라이딩 으로만 정의를 할 수 있음
	virtual void update() = 0;

	//부모 오브젝트에서의 finalupdate는, 자식 오브젝트들이 오버라이딩 하는 게 아니라
	//부모 레벨에서 자식 오브젝트가 콜라이더를 가지고 있는지 여부를 검사하고, 있다면 콜라이더를 업데이트 시키는 동작
	//final 키워드 -> 자식 클래스에서 오버라이딩이 안되며, 해당 레벨에서가 마지막 구현임
	virtual void finalupdate() final;

	virtual void render(HDC _dc);

	void component_render(HDC _dc);

	//오브젝트가 죽어있는지 묻는건 아무 클래스에서나 접근 가능하지만,
	bool IsDead() { return !m_bAlive; }

	//오브젝트를 죽은 상태로 만드는 것은 이벤트 관리자 클래스에서만 접근 가능하게 해야함.
	//아무 클래스나 접근하게 하면 문제 발생
private:
	void SetDead() { m_bAlive = false; }


public:
	void CreateCollider();

	virtual void OnCollision(CCollider* _pOther);
	virtual void OnCollisionEnter(CCollider* _pOther);
	virtual void OnCollisionExit(CCollider* _pOther);

	//오브젝트의 사망처리를 관리하기 위해 friend 선언
	friend class CEventMgr;
};


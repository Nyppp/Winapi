#pragma once

#include "global.h"
#include "CCamera.h"

class CCollider;
class CAnimator;

class CObject
{
private:
	//트랜스폼 정보는 실수값으로 가지고 있지만, 렌더링 시에 정수형으로 캐스팅
	Vec2 m_vPos;
	Vec2 m_vScale;

	wstring m_strName;

	//컴포넌트
	CCollider* m_pCollider;
	CAnimator* m_pAnimator;

	bool m_bAlive;

public:
	CObject();
	CObject(const CObject& _origin);
	virtual ~CObject();

public:
	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 GetPos() { return m_vPos; }
	Vec2 GetScale() { return m_vScale; }

	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	CCollider* GetCollider() { return m_pCollider; }
	CAnimator* GetAnimator() { return m_pAnimator; }

public:
	//가상함수에 = 0 을 붙이면, 무조건 자식 오브젝트에서의 오버라이딩 으로만 정의를 할 수 있음
	virtual void update() = 0;

	//부모 오브젝트에서의 finalupdate는, 자식 오브젝트들이 오버라이딩 하는 게 아니라
	//부모 레벨에서 자식 오브젝트가 콜라이더를 가지고 있는지 여부를 검사하고, 있다면 콜라이더를 업데이트 시키는 동작
	//final 키워드 -> 자식 클래스에서 오버라이딩이 안되며, 해당 레벨에서가 마지막 구현임
	virtual void finalupdate() final;

	virtual void render(HDC _dc);

	void component_render(HDC _dc);

	//자신의 복제본을 되돌려주는 역할
	//이 함수를 자식 클래스에서 정의할 때, 얕은 복사(기본 복사생성자)를 사용해도 문제가 없는지 체크해야 함
	//ex) 고유한 멤버변수를 사용하거나 포인터를 사용하는 클래스에 한해서는 따로 복사 생성자를 정의해야 함
	virtual CObject* Clone() = 0;

	//오브젝트가 죽어있는지 묻는건 아무 클래스에서나 접근 가능하지만,
	bool IsDead() { return !m_bAlive; }

	//오브젝트를 죽은 상태로 만드는 것은 이벤트 관리자 클래스에서만 접근 가능하게 해야함.
	//아무 클래스나 접근하게 하면 문제 발생
private:
	void SetDead() { m_bAlive = false; }


public:
	void CreateCollider();
	void CreateAnimator();

	virtual void OnCollision(CCollider* _pOther);
	virtual void OnCollisionEnter(CCollider* _pOther);
	virtual void OnCollisionExit(CCollider* _pOther);

	//오브젝트의 사망처리를 관리하기 위해 friend 선언
	friend class CEventMgr;
};


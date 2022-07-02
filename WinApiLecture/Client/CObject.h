#pragma once

class CCollider;

class CObject
{
private:
	//트랜스폼 정보는 실수값으로 가지고 있지만, 렌더링 시에 정수형으로 캐스팅
	Vec2 m_vPos;
	Vec2 m_vScale;

	CCollider* m_pCollider;

public:
	CObject();
	virtual ~CObject();

public:
	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 GetPos() { return m_vPos; }
	Vec2 GetScale() { return m_vScale; }

	CCollider* GetCollider() { return m_pCollider; }

public:
	virtual void update() = 0;

	//부모 오브젝트에서의 finalupdate는, 자식 오브젝트들이 오버라이딩 하는 게 아니라
	//부모 레벨에서 자식 오브젝트가 콜라이더를 가지고 있는지 여부를 검사하고, 있다면 콜라이더를 업데이트 시키는 동작
	//final 키워드 -> 자식 클래스에서 오버라이딩이 안되며, 해당 레벨에서가 마지막 구현임
	virtual void finalupdate() final;

	virtual void render(HDC _dc);

	void component_render(HDC _dc);

public:
	void CreateCollider();

};


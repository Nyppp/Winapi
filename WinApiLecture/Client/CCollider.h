#pragma once

class CObject;

class CCollider
{
private:
	static UINT g_iNextID; //정적 멤버 -> 객체 포함x -> 항상 데이터 영역에 존재함

	//충돌체가 어떤 오브젝트의 충돌체인지 구분하기 위해,
	//멤버함수로 오브젝트 객체를 가진다.
	CObject* m_pOwner;
	
	//오프셋 -> fps 게임에서 헤드샷 구분같은 기능을 위해
	//충돌체 위치가 곧 오브젝트 위치가 아니라, 오프셋을 두어서
	//실제 위치와 충돌 위치의 차이를 둠
	Vec2 m_vOffsetPos;

	//위의 오프셋과, 오브젝트의 위치를 계산한 최종 충돌체의 위치
	Vec2 m_vFinalPos;

	//크기는 절대값으로 지정
	Vec2 m_vScale;

	UINT m_iID; //충돌체의 고유한 id값 -> 이전프레임 충돌 정보를 저장하기 위해 선언
	
public:
	void SetOffsetPos(Vec2 _vPos) { m_vOffsetPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 GetOffsetPos() { return m_vOffsetPos; }
	Vec2 GetScale() { return m_vScale; }

public:
	CCollider();
	~CCollider();

public:
	void finalupdate();

	void render(HDC _dc);

	friend class CObject;
};


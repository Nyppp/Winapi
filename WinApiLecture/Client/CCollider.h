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

	//그러나 복사생성자를 호출 시, 고유한 ID값이 여러 객체에 동일한 값으로 저장됨 -> 복사 생성자 직접 구현
	UINT m_iID; //충돌체의 고유한 id값 -> 이전프레임 충돌 정보를 저장하기 위해 선언

	//충돌체가 여러 개가 있을 수 있기에, 충돌여부를 표시하는 멤버변수로 int형 변수 선언
	int m_iCol;

	
public:
	void SetOffsetPos(Vec2 _vPos) { m_vOffsetPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 GetOffsetPos() { return m_vOffsetPos; }
	Vec2 GetScale() { return m_vScale; }
	Vec2 GetFinalPos() { return m_vFinalPos; }

	UINT GetID() { return m_iID; }

public:
	CCollider();
	CCollider(const CCollider& _origin);
	~CCollider();

public:
	void finalupdate();

	void render(HDC _dc);

	//대입 연산자의 기능을 삭제시킴 -> 대입을 불허함
	CCollider& operator = (CCollider& _origin) = delete;

	void OnCollision(CCollider* _pOther); //충돌 중일 때 호출되는 함수
	void OnCollisionEnter(CCollider* _pOther); //충돌 진입 시 호출되는 함수
	void OnCollisionExit(CCollider* _pOther); //충돌이 끝날 때 호출되는 함수


	friend class CObject;
};


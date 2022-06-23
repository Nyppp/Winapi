#pragma once

class CObject
{
private:
	//트랜스폼 정보는 실수값으로 가지고 있지만, 렌더링 시에 정수형으로 캐스팅
	Vec2 m_vPos;
	Vec2 m_vScale;

public:
	CObject();
	virtual ~CObject();

public:
	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 GetPos() { return m_vPos; }
	Vec2 GetScale() { return m_vScale; }

public:
	virtual void update() = 0;
	virtual void render(HDC _dc);

};


#pragma once

//키 입력을 관리하는 CKeyMgr

//업데이트 문에서 모두 key input을 처리한다면,
//같은 DT 내에서 같은 키에 대한 동작이 여러개 일 때,
//코드를 수행하다가 입력이 바뀌면, 눌렸기에 수행되는 동작이 누락될 수 있음

//프레임 동기화를 통해 동일 프레임 내에 같은 키에 대해서
//동일한 이벤트를 가져가도록 만듦

//키 입력 이벤트 처리
//tap, hold, away 구분

//키 정보
//해당 열거체 정보를 벡터 배열번호와 매칭시켜 색인화 함
enum class KEY
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	Q, W, E, R, T, Y, U, I, O, P,
	A, S, D, F, G, Z, X, C, V, B,
	ALT, LSHIFT, SPACE, CTRL, ENTER, ESC, 
	LBTN, RBTN,
	LAST
};

//키의 상태
enum class KEY_STATE
{
	NONE, //idle 상태
	TAP, //방금 누름
	HOLD, //누르고 있음
	AWAY //키를 뗌
};


struct tKeyInfo
{
	KEY_STATE	eState; //현재 프레임의 키 상태
	bool		bPrev; //이전 프레임에 해당 키가 눌렸는지 여부
};



class CKeyMgr
{
	SINGLE(CKeyMgr);

private:
	//벡터 인덱스 = 키 열거체 번호 = 키 값
	vector<tKeyInfo> m_vecKey;
	Vec2 m_vCurMousePos;

public:
	void init();
	void update();

public:
	KEY_STATE GetKeyState(KEY _eKey) { return m_vecKey[(int)_eKey].eState; }
	Vec2 GetMousePos() { return m_vCurMousePos; }
};


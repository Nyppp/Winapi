#pragma once

//매크로 함수 -> 전처리기 과정에서 해당 ADD구문을 오른쪽 코드로 바꿔줌
//함수 호출이 아닌, 코드 치환으로 동작한 것임
#define ADD(a,b) a+b

//위의 함수는 ADD(10,10) = 20임.
//하지만, 10 * ADD(10,10) -> 10 * 10 + 10 = 110이 됨(200을 의도하고 사용할 경우 꼬임)

//객체를 생성하는 GetInst() 함수를 매크로로 만듦
//전처리기 구문에서 \를 붙이면 다음 줄 까지도 포함하여 읽는다는 뜻임
// ***Unreal Engine 매크로함수 방식과 동일(UFUNCTION)***
#define SINGLE(type) public: \
					static type* GetInst()\
					{\
						static type mgr; return &mgr;\
					}\
					private:\
						type();\
						~type()

//오브젝트 복사에 대한 매크로 함수
#define CLONE(type) type* Clone() {return new type(*this);}


//특정 키가 해당 스테이트와 같은지 검사해주는 매크로 함수
#define KEY_CHECK(key, state) CKeyMgr::GetInst()->GetKeyState(key) == state
#define KEY_HOLD(key) KEY_CHECK(key, KEY_STATE::HOLD)
#define KEY_TAP(key) KEY_CHECK(key, KEY_STATE::TAP)
#define KEY_AWAY(key) KEY_CHECK(key, KEY_STATE::AWAY)
#define KEY_NONE(key) KEY_CHECK(key, KEY_STATE::NONE)

#define PI 3.1415926535f

//시간값 가져오는 매크로 함수
#define fDT CTimeMgr::GetInst()->GetfDT()

#define DT CTimeMgr::GetInst()->GetDT()

//씬에 존재하는 오브젝트를 분류하는 열거형 클래스
enum class GROUP_TYPE
{
	DEFAULT,
	PLAYER,
	MONSTER,
	PROJ_PLAYER,	//플레이어가 쏜 투사체
	PROJ_MONSTER,	//몬스터가 쏜 투사체

	END = 32,
};

enum class SCENE_TYPE
{
	TOOL,
	START,
	STAGE_01,
	STAGE_02,

	END,
};

enum class BRUSH_TYPE
{
	HOLLOW,
	END,
};

enum class PEN_TYPE
{
	RED,
	GREEN,
	BLUE,
	END,
};

enum class EVENT_TYPE
{
	CREATE_OBJECT,
	DELETE_OBJECT,
	SCENE_CHANGE,
	END,
};
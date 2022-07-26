#include "global.h"
#include "CIdleState.h"

//부모 클래스의 스테이트 값을 받아오는 생성자 이용해서, 부모 클래스에 자신이 어떤 스테이트인지 알려줌
CIdleState::CIdleState()
	: CState(MON_STATE::IDLE)
{
}

CIdleState::~CIdleState()
{
}


void CIdleState::update()
{
	//IDLE STATE -> 가만히 정지함
	//플레이어의 위치 체크, 플레이어가 추적 범위 내로 들어오면 추적 상태로 전환
}


void CIdleState::Enter()
{

}

void CIdleState::Exit()
{

}

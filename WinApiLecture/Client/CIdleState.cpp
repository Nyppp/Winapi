#include "global.h"
#include "CIdleState.h"

//�θ� Ŭ������ ������Ʈ ���� �޾ƿ��� ������ �̿��ؼ�, �θ� Ŭ������ �ڽ��� � ������Ʈ���� �˷���
CIdleState::CIdleState()
	: CState(MON_STATE::IDLE)
{
}

CIdleState::~CIdleState()
{
}


void CIdleState::update()
{
	//IDLE STATE -> ������ ������
	//�÷��̾��� ��ġ üũ, �÷��̾ ���� ���� ���� ������ ���� ���·� ��ȯ
}


void CIdleState::Enter()
{

}

void CIdleState::Exit()
{

}

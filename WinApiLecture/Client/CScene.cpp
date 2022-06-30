#include "pch.h"
#include "CScene.h"
#include "CObject.h"

CScene::CScene()
{

}

CScene::~CScene()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			//원래 씬이 사라지면, 벡터는 당연히 클래스 내부적으로 벡터 소멸자를 통해 사라지지만,
			//벡터가 가리키고 있는 주소값, 즉 오브젝트들의 주소는 계속 남아있게 되어 이들을 직접 삭제해야 함
			//이를 씬의 파생클래스가 아닌 씬 부모클래스에서 일괄적으로 하게끔 코드 작성
			delete m_arrObj[i][j];
		}
	}
}

void CScene::update()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			m_arrObj[i][j]->update();
		}
	}
}

//게임 로직 이외의 업데이트 구문(콜라이더의 상태 변화 등)
void CScene::finalupdate()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			m_arrObj[i][j]->finalupdate();
		}
	}
}

void CScene::render(HDC _dc)
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			m_arrObj[i][j]->render(_dc);
		}
	}
}
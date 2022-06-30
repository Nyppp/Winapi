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
			//���� ���� �������, ���ʹ� �翬�� Ŭ���� ���������� ���� �Ҹ��ڸ� ���� ���������,
			//���Ͱ� ����Ű�� �ִ� �ּҰ�, �� ������Ʈ���� �ּҴ� ��� �����ְ� �Ǿ� �̵��� ���� �����ؾ� ��
			//�̸� ���� �Ļ�Ŭ������ �ƴ� �� �θ�Ŭ�������� �ϰ������� �ϰԲ� �ڵ� �ۼ�
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

//���� ���� �̿��� ������Ʈ ����(�ݶ��̴��� ���� ��ȭ ��)
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
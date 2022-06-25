#pragma once

class CScene;

//��ü�� ���� �����ϴ� �� �Ŵ���
class CSceneMgr
{
	SINGLE(CSceneMgr);

private:
	//������ ������Ʈ ������ŭ �迭�� ���� �� ó��, ���Ŵ����� ���� ������ŭ �� �迭 ����
	CScene* m_arrScene[(UINT)SCENE_TYPE::END];
	//���� ������� ��
	CScene* m_pCurScene;

public:
	void init();
	void update();
	void render(HDC _dc);

	CScene* GetCurScene() { return m_pCurScene; }
};


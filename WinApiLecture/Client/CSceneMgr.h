#pragma once

class CScene;

//전체의 씬을 관리하는 씬 매니저
class CSceneMgr
{
	SINGLE(CSceneMgr);

private:
	//씬에서 오브젝트 종류만큼 배열을 만든 것 처럼, 씬매니저도 씬의 종류만큼 씬 배열 선언
	CScene* m_arrScene[(UINT)SCENE_TYPE::END];
	//현재 사용중인 씬
	CScene* m_pCurScene;

public:
	void init();
	void update();
	void render(HDC _dc);

	CScene* GetCurScene() { return m_pCurScene; }
};


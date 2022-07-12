#include "pch.h"
#include "CScene_Tool.h"
#include "CKeyMgr.h"
#include "CTile.h"
#include "CCore.h"

#include "CResMgr.h"
#include "resource.h"
#include "CSceneMgr.h"

CScene_Tool::CScene_Tool()
{
}

CScene_Tool::~CScene_Tool()
{
}

void CScene_Tool::update()
{
	CScene::update();

	SetTileIdx();
}

void CScene_Tool::Enter()
{
	CreateTile(5, 5);

	Vec2 vResolution = CCore::GetInst()->GetResolution();
	//기본 카메라 세팅 -> 전체 해상도의 정 중앙 위치
	CCamera::GetInst()->SetLookAt(vResolution / 2.f);
}

void CScene_Tool::Exit()
{
	DeleteAll();
}

void CScene_Tool::SetTileIdx()
{
	if (KEY_TAP(KEY::LBTN))
	{
		//MOUSE_POS는 카메라 기준 좌표(렌더링좌표)를 가져옴
		Vec2 vMousePos = MOUSE_POS;

		//카메라 클래스에 있는 실제 좌표 반환 함수를 사용해 실제좌표 얻어옴
		vMousePos = CCamera::GetInst()->GetRealPos(vMousePos);

		//부모클래스로부터 타일 갯수 반환
		UINT iTileX = GetTileX();
		UINT iTileY = GetTileY();

		//마우스 좌표를 타일 사이즈로 나누면, 몇행 몇열을 가리키는지 알 수 있음
		UINT iCol = (UINT)vMousePos.x / TILE_SIZE;
		UINT iRow = (UINT)vMousePos.y / TILE_SIZE;

		UINT iIdx = (iRow * iTileX) + iCol;

		const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);
		if (iIdx >= vecTile.size())
		{
			return;
		}
		((CTile*)vecTile[iIdx])->AddImgIdx();
	}
}



//툴 씬에서만 사용되는 타일 갯수 조정에 대한 프로시저 함수
//멤버함수가 아니고, 전역함수이며, 사용처를 분류하기 위해 툴 씬 cpp에서 구현
INT_PTR CALLBACK TileCountProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		//확인 버튼이 눌렸을 때
		if (LOWORD(wParam) == IDOK)
		{
			//텍스트 박스에 적힌 문자열을 UINT 데이터로 가져온다.
			UINT iXCount = GetDlgItemInt(hDlg, IDC_EDIT1, nullptr, false);
			UINT iYCount = GetDlgItemInt(hDlg, IDC_EDIT2, nullptr, false);

			//이 함수는 멤버함수가 아님 -> 객체를 가져와서 읽어야 함
			CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

			//툴 씬에서만 동작하게끔 만든 코드이기에, 씬을 가져와서 툴 씬인지 체크한다.
			CScene_Tool* pToolScene = dynamic_cast<CScene_Tool*>(pCurScene) ;
			assert(pToolScene);

			//기존 타일을 지우고, 새로 들어온 타일 갯수를 바탕으로 다시 타일을 그린다.
			pToolScene->DeleteGroup(GROUP_TYPE::TILE);
			pToolScene->CreateTile(iXCount, iYCount);

			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}

		//취소 버튼이 눌렸을 때 -> 아무런 동작을 하지 않는다.
		if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
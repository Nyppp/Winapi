#include "pch.h"
#include "CScene_Tool.h"
#include "CKeyMgr.h"
#include "CTile.h"
#include "CCore.h"

#include "CResMgr.h"
#include "resource.h"
#include "CSceneMgr.h"
#include "CUI.h"
#include "CPanelUI.h"
#include "CBtnUI.h"
#include "CUIMgr.h"
#include "CPathMgr.h"

void ChangeScene(DWORD_PTR, DWORD_PTR);

CScene_Tool::CScene_Tool() : m_pUI(nullptr)
{
}

CScene_Tool::~CScene_Tool()
{
}

void CScene_Tool::update()
{
	CScene::update();

	SetTileIdx();

	//ui매니저에서 구현한 ui 포커스 설정 함수를 사용해서,
	//특정 키가 눌렸을 때 UI 우선순위를 변경할 수 있음
	/*if (KEY_TAP(KEY::LSHIFT))
	{
		SaveTileData();
	}*/

	/*if (KEY_TAP(KEY::CTRL))
	{
		LoadTileData();
	}*/
}

void CScene_Tool::Enter()
{
	CreateTile(5, 5);

	Vec2 vResolution = CCore::GetInst()->GetResolution();

	//ui 생성
	CUI* pPanelUI = new CPanelUI;
	pPanelUI->SetName(L"ParentUI");
	pPanelUI->SetScale(Vec2(300.f, 780.f));
	pPanelUI->SetPos(Vec2(vResolution.x - pPanelUI->GetScale().x, 0.f));

	//자식 UI의 배치 -> 직접 자식UI를 씬에 배치하고 렌더링하는게 아니라,
	//부모 UI가 해당 정보를 가지고 있으며, 렌더링과 배치를 부모UI 클래스에서 함께 동작한다.
	CBtnUI* pSaveBtnUI = new CBtnUI;
	pSaveBtnUI->SetName(L"ChildSaveUI");
	pSaveBtnUI->SetBtnText(L"Save Tile");
	pSaveBtnUI->SetScale(Vec2(100.f, 100.f));

	CBtnUI* pLoadBtnUI = new CBtnUI;
	pLoadBtnUI->SetName(L"ChildLoadUI");
	pLoadBtnUI->SetBtnText(L"Load Tile");
	pLoadBtnUI->SetScale(Vec2(100.f, 100.f));

	
	//자식 UI의 포지션은 부모UI와의 상대위치를 넣게 됨
	pSaveBtnUI->SetPos(Vec2(0.f, 0.f));
	pLoadBtnUI->SetPos(Vec2(120.f, 0.f));

	//선언은 부모 클래스의 함수를 받아온다고 했지만, 자식 클래스의 함수를 타입캐스팅 하여 전달하면 문제발생X
	((CBtnUI*)pSaveBtnUI)->SetClickedCallBack(this, (SCENE_MEMFUNC)&CScene_Tool::SaveTileData);
	((CBtnUI*)pLoadBtnUI)->SetClickedCallBack(this, (SCENE_MEMFUNC)&CScene_Tool::LoadTileData);

	pPanelUI->AddChild(pSaveBtnUI);
	pPanelUI->AddChild(pLoadBtnUI);

	//씬에서는 부모 UI만 알고 있지만, 부모UI가 포함하고 있는 자식UI의 렌더링, 업데이트는 부모UI를 통해 동작함.
	AddObject(pPanelUI, GROUP_TYPE::UI);

	////클론으로 생성해서 같은  모양에, 같은 자식구조를 가졌지만 위의 pPanelUI와는 전혀 다른 객체임
	//CUI* pClonePanel = pPanelUI->Clone();
	//pClonePanel->SetPos(pClonePanel->GetPos() + Vec2(-300.f, 0.f));

	////버튼의 함수 포인터를 지정 -> 복사본에 대한 자식 함수호출은 이렇게 사용
	//((CBtnUI*)(pClonePanel->GetChildUI()[0]))->SetClickedCallBack(ChangeScene, 0, 0);

	//AddObject(pClonePanel, GROUP_TYPE::UI);

	//m_pUI = pPanelUI;

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
		int iCol = (int)vMousePos.x / TILE_SIZE;
		int iRow = (int)vMousePos.y / TILE_SIZE;

		//마우스 좌표가 음수 -> 0번째 타일에 대해 살짝 옆으로 가서 음수 위치에서 클릭하면,
		//iCol이 음수여도 0이 되기에  마우스 자체 좌표가 음수인지 체크하여 판단
		if (vMousePos.x < 0.f || iCol >= iTileX
			|| vMousePos.y < 0.f || iRow >= iTileY)
		{
			return;
		}

		UINT iIdx = (iRow * iTileX) + iCol;

		const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);

		if (iIdx >= vecTile.size())
		{
			return;
		}

		((CTile*)vecTile[iIdx])->AddImgIdx();
	}
}

//상대경로 이름을 받아오고, 그에 맞춰서 타일 정보를 담은 파일 생성
void CScene_Tool::SaveTile(const wstring& _strRelativePath)
{
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();

	strFilePath += _strRelativePath;
	//2바이트 경로에 대한 파일 오픈
	//FILE 자료형 -> 보이드 포인터, 커널 오브젝트로 os의 파일 시스템과 코드를 연결해주는 자료형임
	FILE* pFile = nullptr;

	// ***2중 포인터***
	//포인터의 포인터로, 포인터가 가리키는 값에 대한 정보를 담고 있음
	//2중포인터 변수에는 값을 집어넣을 수 없으며, 무조건 포인터가 들어감
	//2중포인터의 수정 = 포인터의 참조 주소를 수정

	//n차 포인터를 수정하려면 -> n+1차 포인터를 매개변수로 받아와서, n차 포인터의 주소를 수정 -> 보통 이중포인터에서 끝남

	//코드와 파일 주소에 대한 연결(os가 관리)을 fopen으로 연다, 파일 저장이기에 write 모드로 진입
	_wfopen_s(&pFile, strFilePath.c_str(), L"wb");

	assert(pFile);

	//타일 데이터 저장
	UINT xCount = GetTileX();
	UINT yCount = GetTileY();

	fwrite(&xCount, sizeof(UINT), 1, pFile);
	fwrite(&yCount, sizeof(UINT), 1, pFile);

	const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);

	//타일 하나하나마다 자신이 어떤 텍스쳐가 있고, 서로 다른 기능을 하기에 각자가 자신을 저장
	for (size_t i = 0; i < vecTile.size(); ++i)
	{
		((CTile*)vecTile[i])->Save(pFile);
	}
	
	//작업이 끝나면, fclose로 닫아줘야 함(커널 오브젝트이기에 직접 delete는 안함)
	fclose(pFile);
}

//맵 데이터 파일 저장 함수
void CScene_Tool::SaveTileData()
{
	//파일 저장 창을 띄우기 위해 설정되는 구조체(실제 다른 프로그램에서 파일 저장할때 나오는 윈도우)
	OPENFILENAME ofn = {};

	wchar_t szName[256] = {};

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = CCore::GetInst()->GetMainHwnd();
	ofn.lpstrFile = szName;
	ofn.nMaxFile = sizeof(szName);
	ofn.lpstrFilter = L"ALL\0*.*\0Tile\0*.tile\0";
	ofn.nFilterIndex = 0;
	ofn.lpstrFileTitle = nullptr;
	ofn.nMaxFileTitle = 0;

	wstring strTileFolder = CPathMgr::GetInst()->GetContentPath();
	strTileFolder += L"tile";
	ofn.lpstrInitialDir = strTileFolder.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	
	if (GetSaveFileName(&ofn))
	{
		wstring strRelativePath = CPathMgr::GetInst()->GetRelativePath(szName);
		SaveTile(strRelativePath);
	}
}

//맵 데이터 파일 로드 함수
void CScene_Tool::LoadTileData()
{
	OPENFILENAME ofn = {};

	wchar_t szName[256] = {};

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = CCore::GetInst()->GetMainHwnd();
	ofn.lpstrFile = szName;
	ofn.nMaxFile = sizeof(szName);
	ofn.lpstrFilter = L"ALL\0*.*\0Tile\0*.tile\0";
	ofn.nFilterIndex = 0;
	ofn.lpstrFileTitle = nullptr;
	ofn.nMaxFileTitle = 0;

	wstring strTileFolder = CPathMgr::GetInst()->GetContentPath();
	strTileFolder += L"tile";
	ofn.lpstrInitialDir = strTileFolder.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetOpenFileName(&ofn))
	{
		wstring strRelativePath = CPathMgr::GetInst()->GetRelativePath(szName);
		LoadTile(strRelativePath);
	}
}

//버튼에 씬 체인지 함수를 넣기 위해 만든 ChangeScene함수 -> 멤버함수 아님, 전역함수임
void ChangeScene(DWORD_PTR, DWORD_PTR)
{
	//내부동작은, 씬을 변경하는 이벤트를 호출한다
	ChangeScene(SCENE_TYPE::START);
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
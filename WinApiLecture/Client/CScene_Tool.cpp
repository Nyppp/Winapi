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

	//ui�Ŵ������� ������ ui ��Ŀ�� ���� �Լ��� ����ؼ�,
	//Ư�� Ű�� ������ �� UI �켱������ ������ �� ����
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

	//ui ����
	CUI* pPanelUI = new CPanelUI;
	pPanelUI->SetName(L"ParentUI");
	pPanelUI->SetScale(Vec2(300.f, 780.f));
	pPanelUI->SetPos(Vec2(vResolution.x - pPanelUI->GetScale().x, 0.f));

	//�ڽ� UI�� ��ġ -> ���� �ڽ�UI�� ���� ��ġ�ϰ� �������ϴ°� �ƴ϶�,
	//�θ� UI�� �ش� ������ ������ ������, �������� ��ġ�� �θ�UI Ŭ�������� �Բ� �����Ѵ�.
	CBtnUI* pSaveBtnUI = new CBtnUI;
	pSaveBtnUI->SetName(L"ChildSaveUI");
	pSaveBtnUI->SetBtnText(L"Save Tile");
	pSaveBtnUI->SetScale(Vec2(100.f, 100.f));

	CBtnUI* pLoadBtnUI = new CBtnUI;
	pLoadBtnUI->SetName(L"ChildLoadUI");
	pLoadBtnUI->SetBtnText(L"Load Tile");
	pLoadBtnUI->SetScale(Vec2(100.f, 100.f));

	
	//�ڽ� UI�� �������� �θ�UI���� �����ġ�� �ְ� ��
	pSaveBtnUI->SetPos(Vec2(0.f, 0.f));
	pLoadBtnUI->SetPos(Vec2(120.f, 0.f));

	//������ �θ� Ŭ������ �Լ��� �޾ƿ´ٰ� ������, �ڽ� Ŭ������ �Լ��� Ÿ��ĳ���� �Ͽ� �����ϸ� �����߻�X
	((CBtnUI*)pSaveBtnUI)->SetClickedCallBack(this, (SCENE_MEMFUNC)&CScene_Tool::SaveTileData);
	((CBtnUI*)pLoadBtnUI)->SetClickedCallBack(this, (SCENE_MEMFUNC)&CScene_Tool::LoadTileData);

	pPanelUI->AddChild(pSaveBtnUI);
	pPanelUI->AddChild(pLoadBtnUI);

	//�������� �θ� UI�� �˰� ������, �θ�UI�� �����ϰ� �ִ� �ڽ�UI�� ������, ������Ʈ�� �θ�UI�� ���� ������.
	AddObject(pPanelUI, GROUP_TYPE::UI);

	////Ŭ������ �����ؼ� ����  ��翡, ���� �ڽı����� �������� ���� pPanelUI�ʹ� ���� �ٸ� ��ü��
	//CUI* pClonePanel = pPanelUI->Clone();
	//pClonePanel->SetPos(pClonePanel->GetPos() + Vec2(-300.f, 0.f));

	////��ư�� �Լ� �����͸� ���� -> ���纻�� ���� �ڽ� �Լ�ȣ���� �̷��� ���
	//((CBtnUI*)(pClonePanel->GetChildUI()[0]))->SetClickedCallBack(ChangeScene, 0, 0);

	//AddObject(pClonePanel, GROUP_TYPE::UI);

	//m_pUI = pPanelUI;

	//�⺻ ī�޶� ���� -> ��ü �ػ��� �� �߾� ��ġ
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
		//MOUSE_POS�� ī�޶� ���� ��ǥ(��������ǥ)�� ������
		Vec2 vMousePos = MOUSE_POS;

		//ī�޶� Ŭ������ �ִ� ���� ��ǥ ��ȯ �Լ��� ����� ������ǥ ����
		vMousePos = CCamera::GetInst()->GetRealPos(vMousePos);

		//�θ�Ŭ�����κ��� Ÿ�� ���� ��ȯ
		UINT iTileX = GetTileX();
		UINT iTileY = GetTileY();

		//���콺 ��ǥ�� Ÿ�� ������� ������, ���� ��� ����Ű���� �� �� ����
		int iCol = (int)vMousePos.x / TILE_SIZE;
		int iRow = (int)vMousePos.y / TILE_SIZE;

		//���콺 ��ǥ�� ���� -> 0��° Ÿ�Ͽ� ���� ��¦ ������ ���� ���� ��ġ���� Ŭ���ϸ�,
		//iCol�� �������� 0�� �Ǳ⿡  ���콺 ��ü ��ǥ�� �������� üũ�Ͽ� �Ǵ�
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

//����� �̸��� �޾ƿ���, �׿� ���缭 Ÿ�� ������ ���� ���� ����
void CScene_Tool::SaveTile(const wstring& _strRelativePath)
{
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();

	strFilePath += _strRelativePath;
	//2����Ʈ ��ο� ���� ���� ����
	//FILE �ڷ��� -> ���̵� ������, Ŀ�� ������Ʈ�� os�� ���� �ý��۰� �ڵ带 �������ִ� �ڷ�����
	FILE* pFile = nullptr;

	// ***2�� ������***
	//�������� �����ͷ�, �����Ͱ� ����Ű�� ���� ���� ������ ��� ����
	//2�������� �������� ���� ������� �� ������, ������ �����Ͱ� ��
	//2���������� ���� = �������� ���� �ּҸ� ����

	//n�� �����͸� �����Ϸ��� -> n+1�� �����͸� �Ű������� �޾ƿͼ�, n�� �������� �ּҸ� ���� -> ���� ���������Ϳ��� ����

	//�ڵ�� ���� �ּҿ� ���� ����(os�� ����)�� fopen���� ����, ���� �����̱⿡ write ���� ����
	_wfopen_s(&pFile, strFilePath.c_str(), L"wb");

	assert(pFile);

	//Ÿ�� ������ ����
	UINT xCount = GetTileX();
	UINT yCount = GetTileY();

	fwrite(&xCount, sizeof(UINT), 1, pFile);
	fwrite(&yCount, sizeof(UINT), 1, pFile);

	const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);

	//Ÿ�� �ϳ��ϳ����� �ڽ��� � �ؽ��İ� �ְ�, ���� �ٸ� ����� �ϱ⿡ ���ڰ� �ڽ��� ����
	for (size_t i = 0; i < vecTile.size(); ++i)
	{
		((CTile*)vecTile[i])->Save(pFile);
	}
	
	//�۾��� ������, fclose�� �ݾ���� ��(Ŀ�� ������Ʈ�̱⿡ ���� delete�� ����)
	fclose(pFile);
}

//�� ������ ���� ���� �Լ�
void CScene_Tool::SaveTileData()
{
	//���� ���� â�� ���� ���� �����Ǵ� ����ü(���� �ٸ� ���α׷����� ���� �����Ҷ� ������ ������)
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

//�� ������ ���� �ε� �Լ�
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

//��ư�� �� ü���� �Լ��� �ֱ� ���� ���� ChangeScene�Լ� -> ����Լ� �ƴ�, �����Լ���
void ChangeScene(DWORD_PTR, DWORD_PTR)
{
	//���ε�����, ���� �����ϴ� �̺�Ʈ�� ȣ���Ѵ�
	ChangeScene(SCENE_TYPE::START);
}

//�� �������� ���Ǵ� Ÿ�� ���� ������ ���� ���ν��� �Լ�
//����Լ��� �ƴϰ�, �����Լ��̸�, ���ó�� �з��ϱ� ���� �� �� cpp���� ����
INT_PTR CALLBACK TileCountProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		//Ȯ�� ��ư�� ������ ��
		if (LOWORD(wParam) == IDOK)
		{
			//�ؽ�Ʈ �ڽ��� ���� ���ڿ��� UINT �����ͷ� �����´�.
			UINT iXCount = GetDlgItemInt(hDlg, IDC_EDIT1, nullptr, false);
			UINT iYCount = GetDlgItemInt(hDlg, IDC_EDIT2, nullptr, false);

			//�� �Լ��� ����Լ��� �ƴ� -> ��ü�� �����ͼ� �о�� ��
			CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

			//�� �������� �����ϰԲ� ���� �ڵ��̱⿡, ���� �����ͼ� �� ������ üũ�Ѵ�.
			CScene_Tool* pToolScene = dynamic_cast<CScene_Tool*>(pCurScene) ;
			assert(pToolScene);

			//���� Ÿ���� �����, ���� ���� Ÿ�� ������ �������� �ٽ� Ÿ���� �׸���.
			pToolScene->DeleteGroup(GROUP_TYPE::TILE);
			pToolScene->CreateTile(iXCount, iYCount);

			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}

		//��� ��ư�� ������ �� -> �ƹ��� ������ ���� �ʴ´�.
		if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
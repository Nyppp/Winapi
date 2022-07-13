#include "pch.h"
#include "CScene_Tool.h"
#include "CKeyMgr.h"
#include "CTile.h"
#include "CCore.h"

#include "CResMgr.h"
#include "resource.h"
#include "CSceneMgr.h"
#include "CUI.h"

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

	//ui ����
	CUI* pUI = new CUI;
	pUI->SetScale(Vec2(200.f, 300.f));
	pUI->SetPos(Vec2(vResolution.x - pUI->GetScale().x, 0.f));

	CUI* pChildUI = new CUI;
	pChildUI->SetScale(Vec2(100.f, 100.f));
	pChildUI->SetPos(Vec2(0.f, 0.f));

	pUI->AddChild(pChildUI);

	//�������� �θ� UI�� �˰� ������, �θ�UI�� �����ϰ� �ִ� �ڽ�UI�� ������, ������Ʈ�� �θ�UI�� ���� ������.
	AddObject(pUI, GROUP_TYPE::UI);

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
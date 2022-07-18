#pragma once
class CUI;

class CUIMgr
{
	SINGLE(CUIMgr);

private:
	//���� ��Ŀ���� �� UI
	CUI* m_pFocusedUI;

public:
	void update();

	//���������� UI ��Ŀ���� �����ϴ� �Լ�
	void SetFocusedUI(CUI* _pUI);

private:
	CUI* GetTargetedUI(CUI* _pParentUI);
	CUI* GetFocusedUI();
};


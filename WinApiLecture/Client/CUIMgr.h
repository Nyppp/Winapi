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

private:
	CUI* GetTargetedUI(CUI* _pParentUI);
	CUI* GetFocusedUI();
};


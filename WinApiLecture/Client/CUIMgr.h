#pragma once
class CUI;

class CUIMgr
{
	SINGLE(CUIMgr);

private:
	//현재 포커스가 된 UI
	CUI* m_pFocusedUI;

public:
	void update();

private:
	CUI* GetTargetedUI(CUI* _pParentUI);
	CUI* GetFocusedUI();
};


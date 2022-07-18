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

	//직접적으로 UI 포커스를 설정하는 함수
	void SetFocusedUI(CUI* _pUI);

private:
	CUI* GetTargetedUI(CUI* _pParentUI);
	CUI* GetFocusedUI();
};


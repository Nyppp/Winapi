#pragma once

struct tEvent
{
	EVENT_TYPE	eEven;
	DWORD_PTR		lParam;
	DWORD_PTR		wParam;
};


class CEventMgr
{
	SINGLE(CEventMgr);

private:
	vector<tEvent> m_vecEvent;

public:
	void update();

private:
	//이벤트 처리 함수
	void Excute(const tEvent& _Event);

public:
	void AddEvent(const tEvent& _Event)
	{
		m_vecEvent.push_back(_Event);
	}
};


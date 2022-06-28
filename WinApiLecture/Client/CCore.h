#pragma once

//싱글톤 패턴
//객체의 생성을 단 1개로 제한 -> 어디서든 이 클래스를 접근 가능해야 함
//class CCore
//{
//	// 정적 변수의 사용 범위
//	// 함수 안에 선언 -> 데이터 영역 사용(함수 스택 X) -> 해당 함수에서만 접근 가능
//	// 한 파일에 선언 -> 데이터 영역 사용 -> 해당 파일에서만 접근 가능 -> 여러 파일에 이름이 중복되어도 에러발생X
//	// 클래스 안에 선언 -> 정적 멤버라고도 함 -> 데이터 영역 사용 -> 클래스를 통해서만 사용 가능함 -> 하지만 정적 멤버는 클래스에 들어있는 것은 아님
//	// + 한 클래스가 수십, 수백개가 생성되어도 정적 멤버는 단 하나임.
//	// ** 정적 멤버는 선언 이후, 클래스 밖에서 반드시 선언해야 함(함수와 동일) **
//private:
//	static CCore* g_pInst;
//
//public:
//	//생성자, 소멸자를 호출해 주는 public 함수를 제공하여 외부에서 사용하게끔 함
//	//하지만 함수를 호출하기 이전에, 객체가 필요함 -> 생성을 위한 함수를 만들었는데, 생성이 안돼서 호출을 못함
//	//멤버함수에 static 키워드를 붙이면, 객체가 없어도 호출할 수 있음 -> 객체없이 바로 클래스::함수() 로 호출
//	//하지만 정적 멤버함수는 클래스의 멤버변수로 접근이 불가능함 -> 누가 호출했는 지 모름 -> this가 없음
//
//	//싱글톤 패턴의 객체 생성 함수
//	static CCore* GetInstance()
//	{
//		//this; -> 에러 발생, 함수를 호출한 객체가 없기 때문에.
//		//예외적으로, 정적 멤버 변수에 대해서는 접근 가능
//
//		//함수가 최초 호출 -> 객체가 없기에 새로 생성하여 전달
//		//지역공간에 정적 변수를 만들면, 이 변수의 초기화는 최초 단 한번만 진행됨
//
//		//pCore는 최초로 실행될 때만 nullptr이고, 그 이후는 모두 CCore객체임
//		if (g_pInst == nullptr)
//		{
//			//객체는 힙메모리에 존재하고, 그걸 가리키는 정적 포인터를 사용하는 방법
//			g_pInst = new CCore;
//		}
//		//아닌 경우 -> 이미 만들어져 있기 때문에 그것을 전달
//		return g_pInst;
//	}
//
//	//싱글톤 패턴의 메모리 해제 함수
//	static void Release()
//	{
//		//앞서 만든 객체 생성 함수를 통해, 만들어진 CCore 객체를 불러오고, 그것을 메모리 해제함
//		//CCore* p = GetInstance();
//		//delete p;
//
//		//하지만 GetInstance의 pCore에서는, nullptr이 아닌 마지막으로 쓰던 공간의 주소가 남고, 쓰레기 값이 있음
//		//이를 해결하기 위해 정적 멤버변수를 선언해서 두 함수 모두 접근가능하게 만듦
//
//		if (g_pInst != nullptr)
//		{
//			delete g_pInst;
//			g_pInst = nullptr;
//		}
//	}
//
//private:
//	//생성자, 소멸자를 private으로 숨기면, 외부에서 생성이 불가능해짐 -> 또한 extern 선언 불가 -> 외부에서 사용자체가 안됨
//	CCore();
//	~CCore();
//};

//싱글톤 객체 동적할당은 사용자가 원할 때 해제해야 하는 객체에 주로 사용


class CCore
{
public:
	//싱글톤 객체를 static 변수로 처음부터 생성하여
	//동적 할당의 영향을 받지 않게 하는 방법(즉, 사용자가 원할 때 해제가 안됨)
	//객체는 데이터 영역에 존재함
	SINGLE(CCore);

	//해제가 원할 때 안되고, 프로그램 종료 시에 되기 때문에 매니저 클래스에 사용

private:
	HWND	m_hwnd;			//현재 윈도우 핸들
	POINT	m_ptResolution; //윈도우 해상도
	HDC		m_hDC;			//메인 윈도우에 draw 할 DC;

	HBITMAP m_hBit;
	HDC m_memDC;

public:
	int Init(HWND _hwnd, POINT _ptResolution);
	void progress();

private:
	void update();
	void render();

public:
	HWND GetMainHwnd() { return m_hwnd; }
	HDC GetMainDC() { return m_hDC; }
	POINT GetResolution() { return m_ptResolution; }
};
// Client.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//
#include "pch.h"
#include "framework.h"
#include "Client.h"
#include "CCore.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
//WCHAR = wchar_t를 이름만 바꾼것임
HWND g_hwnd; //이 프로그램이 띄우는 윈도우의 ID
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

//매개변수 앞에 존재하는 _In_, _In_opt_는 SAL(주석언어)이다. -> 기능을 함축적으로 설명
int APIENTRY wWinMain(
                     //실행 된 프로세스의 시작 주소 -> 프로세스 마다 가상 메모리를 주어서, 모두 자기가 0번지로 인식하지만, 실제 메모리는 각각 다른 곳을 할당받음
                     _In_ HINSTANCE hInstance,
                     //이전에 실행된 프로세스의 시작 주소(초창기 윈도우 호환) -> 요즘엔, 모두 가상메모리를 사용하기에 필요없음
                     _In_opt_ HINSTANCE hPrevInstance,
                     //윈도우 명령 프롬프트(cmd)로 프로그램을 실행할 때, 추가적 인자를 받음 ex) ./program "-o -e" 같은 옵션
                     //LPWSRT = wchar_t* -> 문자열 시작주소임
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    //매크로함수, 아무런 기능이 없음 -> 컴파일러가 자동으로 무시함
    //기능은 없지만, 참조되지 않는 변수들이라는 표시를 위해 만든 매크로 함수임. -> 주석과 유사한 용도
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    //IDS_APP_TITLE과 IDC_CLIENT값이 가리키는 인덱스에, 리소스테이블 내에 있는 값을 가져오는 동작
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CLIENT, szWindowClass, MAX_LOADSTRING);

    //윈도우 정보 등록
    MyRegisterClass(hInstance);

    //앞에서 초기화한 윈도우 제목을 여기서 사용함 -> 윈도우 생성
    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    //Core 객체 초기화
    if (FAILED(CCore::GetInst()->Init(g_hwnd, POINT{ 1200,768 })))
    {
        //core 객체 생성에 실패하면, 에러 메시지와 함께 프로그램을 종료시킨다.
        MessageBox(g_hwnd, L"Core 객체 생성 실패!", L"ERROR", MB_OK);
        return FALSE;
    }

    //단축키
    //단축키 테이블에 존재하는 값을 불러옴
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CLIENT));

    //메시지 구조체
    MSG msg;

    //타이머를 설정하면, x초에 한번씩 타이머가 수행됨
    //0번 타이머 생성, 0프레임마다 nullptr 위치에 오는 함수를 수행
    

    // 메세지 큐
    // 프로세스는 메세지 큐를 os로부터 받음 -> 프로세스가 메시지 온 순서대로 처리함
    // 그림판에서 마우스 클릭 -> 그리기 / 워드파일에서 클릭 -> 커서 이동
    // 포커스 된 창에 대해서 메시지를 보냄
    
    // GetMessage -> 프로세스가 받은 메시지를 꺼내보는 함수임
    // 메시지 큐에서 메시지를 찾을 때 까지 대기함
    // 메시지 타입이 WM_QUIT(종료) 일때만 false 반환, 그 외에는 무조건 true 반환함
    
    // 기본 메시지 루프입니다:
    //WM_QUIT 메시지가 올 때 까지 무한루프 -> 프로그램 종료까지 무한 반복
    
    while (true) 
    {

        //GetMessage와 PeekMessage의 차이
        //GetMessage는 반환이 없을 경우가 있지만, PeekMessage는 반환이 항상 존재함
        //GetMessage는 while문의 조건값에 들어갈 수 있음 -> WM_QUIT메시지가 오면 false로 와일문 종료하고, 그 외에는 true이기 때문에.
        
        //PeekMessage는 while문의 조건이 될 수 없음 -> 메시지가 있든 없든 값을 반환하기 때문에
        //메시지가 있었다면 true, 없었다면 false 반환

        //GetMessage와의 차이 = PeekMessage는 메시지가 없다면 메시지 처리를 대기하거나 동작을 취하지 않음
        //메시지 대기가 없기에 더욱 효율적인 코드
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            //들어온 메시지가 종료 메시지라면 루프탈출(PeekMessage는 메시지 내용 구분x)
            if (msg.message == WM_QUIT)
            {
                break;
            }
            //단축키 테이블에 존재하는 키를 누르면, 특정 메뉴를 불러오거나 동작 수행 -> 잘안씀
            //msg.hwnd -> 메시지가 발생한 윈도우를 뜻함 -> 한 프로세스에 윈도우가 여러개 일 수도 있기에, 명확히 구분
            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                //메시지를 처리하는 동작
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
            //메시지 처리하는데 걸린 시간

            //일반적으로 메시지 처리 시간은, 프로그램 실행 중 많은 비율을 차지하지 않는다.
            //GetMessage 방식으로 프로그램을 짜면, 프로그램이 대부분 일을 하지 않는 상태로 대기함
            //그렇다면, 작업이 있을 때에만 하드웨어 자원을 집중적으로 할당하는 것이 효율적인 코드임
            //비동기 함수 사용 -> 윈도우 시스템에서 발생하는 일을 메시지 루프 도중이 아니어도 알아낼 수 있음(async)
            //비동기 함수의 단점 -> 윈도우 포커싱이 안됐을 때도, 프로그램이 동작할 수 있음 -> 메시지 기반의 장점과 상충됨
        }
        else
        {
            //메시지가 없는 동안 호출

            //메시지가 발생하지 않는 동안? -> 게임 코드 수행
            //디자인 패턴(설계 유형)
            //싱글톤 패턴

            //메시지가 없을 때 진행
            CCore::GetInst()->progress();
        }
    }
    
    //느리고, 비효율적임 -> 윈도우 os기반 처리를 최소한으로 사용해야함
    //윈도우의 메시지 처리 방법은 느리기 때문 -> 메시지 Peek 사용
    //KillTimer(g_hwnd, 0);

    return (int) msg.wParam;
    // 프로세스가 꼭 윈도우를 가지는건 아니며, 윈도우가 없어도 프로세스가 존재할 수 있음 ( 프로세스 != 윈도우 )
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    //윈도우 프로시저 -> 함수 포인터로 받아서 미리 세팅
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CLIENT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_CLIENT);

    //앞의 정보들을 모두 읽어낸 다음, 여기에 szWindowClass 키값으로 전달해주는 방식임
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    //정보를 저장하며 리턴 -> 해당함수는 윈도우 os상에서 실행되기에 코드가 제공되지않음
    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   //레지스터클래스에서 전달받은 szWindowClass 키값을 통해 창 구성을 설정함
   //윈도우 핸들은 커널 레벨에서 os가 직접 관리하는 객체임 -> 객체 정보를 직접 접근하거나, 알 수 없음
   //hwnd == window 아이디
   g_hwnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!g_hwnd)
   {
      return FALSE;
   }

   ShowWindow(g_hwnd, nCmdShow);
   UpdateWindow(g_hwnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//

#include <vector>
using std::vector;

//마우스좌표를 담는 구조체
struct tObjInfo
{
    //마우스 좌표
    POINT g_ptObjectPos;
    POINT g_ptObjectScale;
};

//모든 오브젝트들의 좌표를 저장하는 벡터
vector<tObjInfo> g_vecInfo;

//좌상단 좌표
POINT g_ptLT;
//우하단 좌표
POINT g_ptRB;

bool bLbtDown = false;


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    //윈도우에 무효화 영역(invalidate Rect)이 발생한 경우 실행 -> 창을 최소화 했다가 켰을 때
    //창이 가려지는 경우는 윈도우가 비트맵 형태로 따로 저장하기 때문에 wm_paint를 호출하지 않음
    case WM_PAINT:
        { //switch - case에서 case내부에 지역변수를 만들 때는 괄호 써야함
            PAINTSTRUCT ps;
            //커널 수준 객체인 device context 객체 생성(그리기)
            //struct __HDC 구조체를 생성, 내부에는 int가 한개 있음
            //핸들값을 타입에 따라 나눈 이유 -> 기능을 구별하기 위해서.
            //HPEN, HBRUSH 등 서로 모두 INT 하나로 구분되지만 서로 다른 타입으로 인지됨
            HDC hdc = BeginPaint(hWnd, &ps); //device context 만들고 id반환

            //device context : 그리기 작업을 수행하는 데 필요한 데이터 집합체
            //device context의 목적지는 hwnd
            //펜 기본값 : black, 브러쉬는 기본 브러쉬 white
            
            //윈도우 핸들
            //hdc

            //selectobject는 dc에 특정 핸들값을 넣어서 바꾸면, 그 핸들값이 반환됨
            //하지만 리턴 타입이 void 포인터이기 떄문에 형변환이 필요함(뭘 넣든 반환한다는 뜻)
            HPEN hRedPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
            HBRUSH hBlueBrush = CreateSolidBrush(RGB(0, 0, 255));
            //getStockObject -> 미리 만들어진 자주 쓰는 펜, 브러쉬 커널오브젝트

            //기본 데이터들의 id를 받아둔다.
            HPEN hDefaultPen = (HPEN)SelectObject(hdc, hRedPen);
            HBRUSH hDefaultBrush = (HBRUSH)SelectObject(hdc, hBlueBrush);

            //100x100 pixel의 사각형 그리기 동작을 윈도우 10,10 위치에서 그림
            //device context가 현재 윈도우를 목적으로 하기에, 우리가 띄운 윈도우에 그려짐
            if (bLbtDown)
            {
                Rectangle(hdc,
                    g_ptLT.x,
                    g_ptLT.y,
                    g_ptRB.x,
                    g_ptRB.y);
            }
            
            //벡터에 저장된 모든 사각형 좌표정보를 가져와서 그린다.
            for (size_t i = 0; i < g_vecInfo.size(); ++i)
            {
                Rectangle(hdc,
                    g_vecInfo[i].g_ptObjectPos.x - g_vecInfo[i].g_ptObjectScale.x / 2,
                    g_vecInfo[i].g_ptObjectPos.y - g_vecInfo[i].g_ptObjectScale.y / 2,
                    g_vecInfo[i].g_ptObjectPos.x + g_vecInfo[i].g_ptObjectScale.x / 2,
                    g_vecInfo[i].g_ptObjectPos.y + g_vecInfo[i].g_ptObjectScale.y / 2);
            }

            //이 방법은 물체마다 좌표 정보가 필요하고, 물체가 많으면
            //반복적인 작업이 요구되며, 수 많은 물체중 하나만 움직여도 매번 다시 그려야 함

            //이를 해결하는 방법
            //렌더링 -> 매 순간 화면의 변경점을 제공하기 위해 그리는 작업
            //프레임 -> 화면을 얼마나 자주 그려주는지에 대한 수치

            //받아둔 id를 통해 다시 기본값으로 불러옴
            SelectObject(hdc, hDefaultPen);
            SelectObject(hdc, hDefaultBrush);

            //커널 오브젝트 삭제 요청
            DeleteObject(hRedPen);
            DeleteObject(hDefaultBrush);

            EndPaint(hWnd, &ps);
        }
        break;

    //키가 눌렸을 때의 처리
    case WM_KEYDOWN:
    {
        //wParam = 키보드가 눌린 값이 16진수로 들어옴
        switch (wParam)
        {
        case VK_UP:
            //g_ptObjectPos.y -= 10;
            InvalidateRect(hWnd, nullptr, true);
            break;

        case VK_DOWN:
            //g_ptObjectPos.y += 10;
            InvalidateRect(hWnd, nullptr, true);
            break;

        case VK_LEFT:
            //g_ptObjectPos.x -= 10;
            InvalidateRect(hWnd, nullptr, true);
            break;

        case VK_RIGHT:
            //g_ptObjectPos.x += 10;
            InvalidateRect(hWnd, nullptr, true);
            break;
        }
    }
        break;

    //왼쪽 마우스가 눌렸을 때의 처리
    case WM_LBUTTONDOWN:
    {
        //lParam은 마우스 좌표를 반환해줌 -> long 타입으로 4바이트,
        //row, col에 대해 서로 2바이트씩 가져가서 표현을 해주는 것임

        //g_x = LOWORD(lParam); //마우스 좌표 X값을 가져오는 매크로 
        //g_y = HIWORD(lParam); //Y값을 가져오는 매크로-> 2바이트로 나누어졌기에, 16비트만큼 땡겨서 가져온다.
        //g_ptObjectPos.x = LOWORD(lParam);
        //g_ptObjectPos.y = HIWORD(lParam);

        //무효화 영역을 직접 설정하는 함수 -> 윈도우를 다시 그림
        //InvalidateRect(hWnd, nullptr, true);
        g_ptLT.x = LOWORD(lParam);
        g_ptLT.y = HIWORD(lParam);
        bLbtDown = true;
        break;
    }

    //마우스가 움직일 때 처리
    case WM_MOUSEMOVE:
    {
        //마우스 클릭 한 순간부터, 마우스를 움직이면 사각형이 마우스를 따라가며 그려짐
        g_ptRB.x = LOWORD(lParam);
        g_ptRB.y = HIWORD(lParam);
        //InvalidateRect(hWnd, nullptr, true); //-> 메시지를 발생하며, 마우스 움직임과 같은 동작에 들어가면 매우 비효율적임
    }
    break;

    //마우스를 떼면 그려진 사각형을 저장
    case WM_LBUTTONUP:
    {
        tObjInfo info = {};
        info.g_ptObjectPos.x = (g_ptLT.x + g_ptRB.x) / 2;
        info.g_ptObjectPos.y = (g_ptLT.y + g_ptRB.y) / 2;

        info.g_ptObjectScale.x = abs(g_ptLT.x - g_ptRB.x);
        info.g_ptObjectScale.y = abs(g_ptLT.y - g_ptRB.y);

        g_vecInfo.push_back(info);
        bLbtDown = false;
        InvalidateRect(hWnd, nullptr, true);
        
    }
    break;

    case WM_TIMER:
    {

    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

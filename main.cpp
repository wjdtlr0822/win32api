// win32api.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "win32api.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,  // main 함수 //hinstance는 실행 된 프로세스의 메모리의 시작 주소
                     _In_opt_ HINSTANCE hPrevInstance, /*나보다 먼저 시작된 프로세서의 메모리 시작주소*/  // 하지만 초기 윈도우는 이렇게 사용했지만 지금은 사용하지 않는 영역이다.(가상메모리를 사용하기 때문!!!!)
                     _In_ LPWSTR    lpCmdLine,// cmd에서 실행시 입력을 받는 부분.
                     _In_ int       nCmdShow)

    //_In_  SAL이다. //
    // 주석을 _In_으로 표시한것.

{
    UNREFERENCED_PARAMETER(hPrevInstance); //쓰이지 않는다.
    UNREFERENCED_PARAMETER(lpCmdLine); //쓰이지 않는다.

    // TODO: 여기에 코드를 입력합니다.







    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WIN32API, szWindowClass, MAX_LOADSTRING);

    //윈도우 정보 등록
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다: 윈도우 생성
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    //단축키 부분. [리소스뷰에 accelerato부분에 정의되어있다.
    //단축키를 사용하지 않을꺼면 제거해도 된다.
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32API)); //크게 신경쓰지 않아도 되는부분

    MSG msg;
    //msg.hwnd 메세지가 발생한 윈도우를 가르킨다.

    
    // 기본 메시지 루프입니다:
    //GetMessage()함수 특징!!!!
    // 메세지 큐에서 메세지 확인 될 때 까지 대기
    // condition_variable방식으로 처리.
    //msg.message == WM_QUIT인 경우 false를 반환 - > 프로그램 종료
    // 
    // GetMessage는 메세지가 있을 떄만 반환을 하여 실행된다. PeekMessage()는 항상 반환이 되어 실시간으로 프로그램이 실행된다.
    //while (GetMessage(&msg, nullptr, 0, 0)) // 메세지는 큐의 형태로 저장된다. getMessage는 해당프로그램으로 온 메세지 큐를 꺼내는 것.
     
    DWORD dwCount = GetTickCount(); //프로그램 시작 후 초당 1000씩 카운트

    while (true) //pm_remove 확인한 메세지가 있으면 제거.
    {

        if(PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)){ //메세지가 없으면 false를 반환 있으면 true 반환
            

            if (msg.message == WM_QUIT) break;

            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) //hAccelTable에 있는 단축키 정보가 발생했는지 확인하는 부분 // 사용하지 않을시 if문 제거가능
            {
                /*메세지 처리 과정*/
                TranslateMessage(&msg); // 메세지 분석
                DispatchMessage(&msg); // 해당 처리기로 전달
            }
        }
        
        else {
            //메세지가 없는동안 호출
        
        }
    }

    //PeekMessage();



    return (int) msg.wParam;
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
    wcex.lpfnWndProc    = WndProc; //해당 윈도우에 발생한 메세지를 처리해줄 함수포인터 이다.
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32API));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WIN32API);
    wcex.lpszClassName  = szWindowClass; //키값파트
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);//windows자체에서 제공하는 함수 
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

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, // szWindowsClass를 바탕으로 찾는다.
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

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


#include<vector>

using std::vector;

struct tObject {
    POINT g_ptObjectPosition;
    POINT g_ptObjectScale;
};

vector<tObject> g_vecInfo;

//좌 상단
POINT g_ptLT;
//마우스 하단
POINT g_ptRB;

bool bLbuttonDown = false;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) //해당 처리기 함수부분 //키보드는 wParam에 //마우스는 lParam에
{
    switch (message) //메세지 종류에 따라 처리 방법이 다른데... 우리가 case를 만들어서 처리해야 하는 경우도 생긴다.
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

    case WM_PAINT: //무효화 영역(invalidate)이 발생한 경우
        // 다른 프로그램이 해당 윈도우를 가렸다가 다시 해당프로그램이 위로 올라가면서 가려진 부분이 다시 나오는 부분을 무효화 영역이라고 한다.
        //최소화 했다가 올렸을 때
        {
            PAINTSTRUCT ps;

            //device context를 만들어서 id를 반환
            HDC hdc = BeginPaint(hWnd, &ps); 
            //DC의 목적지는 hWnd
            //DC의 펜과 브러쉬는 디폴트로 설정되어있다.
            

            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...

            //pen 과 brush생성
            HPEN hpen = CreatePen(PS_DASH,3, RGB(255,0,0));
            HBRUSH hbluebrush = (HBRUSH)GetStockObject(BLACK_BRUSH); //이미 만들어둔 브러시를 사용하는 방법 CreateBrush도 있기는 함. // 이미 만들어 둔 브러시라 삭제 안해도 된다.

            //pen과 brush 적용
            HPEN hDefaultPen = (HPEN)SelectObject(hdc, hpen);//반환방식이 void라 변환을 해줘야한다.
            HBRUSH defalutBrush = (HBRUSH)SelectObject(hdc, hbluebrush); 
            
            /*Rectangle(hdc,g_ptObjectPosition.x - g_ptObjectScale.x /2 
                , g_ptObjectPosition.y - g_ptObjectScale.y / 2 
                , g_ptObjectPosition.x + g_ptObjectScale.x / 2
                , g_ptObjectPosition.y +g_ptObjectScale.y / 2);*/
            if(bLbuttonDown){
            Rectangle(hdc, 
                g_ptLT.x, g_ptLT.y,
                g_ptRB.x, g_ptRB.y);
            }

            for (size_t i = 0; i < g_vecInfo.size(); i++) {
                Rectangle(hdc
                    , g_vecInfo[i].g_ptObjectPosition.x - g_vecInfo[i].g_ptObjectScale.x / 2
                    , g_vecInfo[i].g_ptObjectPosition.y - g_vecInfo[i].g_ptObjectScale.y / 2
                    , g_vecInfo[i].g_ptObjectPosition.x + g_vecInfo[i].g_ptObjectScale.x / 2
                    , g_vecInfo[i].g_ptObjectPosition.y + g_vecInfo[i].g_ptObjectScale.y / 2
                );
            }
            // 사각형을 그려주는 windows에서 지원하는 함수.
            //left top right bottom
            
            SelectObject(hdc, hDefaultPen);
            
            DeleteObject(hpen);
            
            EndPaint(hWnd, &ps);
        }
        break;

    case WM_KEYDOWN: //해당 윈도우에 포커싱 된 상태에서 키보드가 눌리면 해당 메세지 발생
    {
        switch (wParam)
        {
        case VK_UP:
            //g_ptObjectPosition.y -= 10;
            InvalidateRect(hWnd,nullptr,true); //무효화 영역 발생했다고 알림.
            break;
        case VK_DOWN:
            //g_ptObjectPosition.y += 10;
            InvalidateRect(hWnd, nullptr, true);
            break;
        case VK_LEFT:
            //g_ptObjectPosition.x -= 10;
            InvalidateRect(hWnd, nullptr, true);
            break;
        case VK_RIGHT:
            //g_ptObjectPosition.x += 10;
            InvalidateRect(hWnd, nullptr, true);
            break;
        }
    }
        break;

    case WM_LBUTTONDOWN: //순간 WM_KEYUP 은 올리는 순간.
    {
       g_ptLT.x = LOWORD(lParam); //마우스  x좌표값
       g_ptLT.y = HIWORD(lParam); // 마우스 y좌표값

       bLbuttonDown = true;
    }
        break;

    case WM_MOUSEMOVE: //마우스 이동시
        g_ptRB.x = LOWORD(lParam);
        g_ptRB.y = HIWORD(lParam);
        InvalidateRect(hWnd, nullptr, true); //무효화 영역을 강제로 발생시킨다.
        break;

    case WM_LBUTTONUP: //순간 WM_KEYUP 은 올리는 순간.
    {
        tObject info = {};
        info.g_ptObjectPosition.x = (g_ptLT.x + g_ptRB.x) / 2;
        info.g_ptObjectPosition.y = (g_ptLT.y + g_ptRB.y) / 2;

        info.g_ptObjectScale.x = abs(g_ptLT.x - g_ptRB.x);
        info.g_ptObjectScale.y = abs(g_ptLT.y - g_ptRB.y);

        g_vecInfo.push_back(info);
        bLbuttonDown = false;
        InvalidateRect(hWnd, nullptr, true);
    }

    break;


    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
    //DefWindowProc()함수는 windows에서 제공하는 함수로 우리가 건들수 없는 부분
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


//커널오브젝트!!!!! 때문에 구조체 이름을 다 다르게 했다!!!
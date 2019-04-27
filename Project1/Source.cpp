#include <windows.h>
#include<vector>
#include"CallPython.h"

#define CONVERT_BUTTON 1000
#define TEXT_FIELD 1001
#define RESULT_FIELD 1002
#define CURR_LIST1 1003
#define CURR_LIST2 1004

HINSTANCE hInst;	
LPCTSTR szWindowClass = "CONVERTER	";
LPCTSTR szTitle = "Currency converter";
int HEIGHT = 400;
int WEIGHT = 750;
const char * currenciesAbbrv[] = { "UAH","USD", "EUR", "RUB", "JPY","GBP","GZK","INR","CNY","CAD","CZK","PLN"};

ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void addItemsInList(HWND);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine,
	int nCmdShow)
{
	MSG msg;

	MyRegisterClass(hInstance);

	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW; 		 
	wcex.lpfnWndProc = (WNDPROC)WndProc; 		 
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance; 			 
	wcex.hIcon = LoadIcon(NULL, IDI_HAND); 		
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW); 	
	wcex.hbrBackground = GetSysColorBrush(COLOR_WINDOW + 1); 
	wcex.lpszMenuName = NULL; 				
	wcex.lpszClassName = szWindowClass; 	
	wcex.hIconSm = NULL;

	return RegisterClassEx(&wcex); 
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	hInst = hInstance;  
	hWnd = CreateWindow(szWindowClass, 	 
		szTitle, 				 
		WS_OVERLAPPEDWINDOW,			 
		CW_USEDEFAULT, 			 	
		CW_USEDEFAULT,			 	
		WEIGHT, 			 
		HEIGHT, 			 
		NULL, 					 	
		NULL, 					 
		hInstance, 				 
		NULL); 				 

	if (!hWnd) 	 
	{
		return FALSE;
	}
	ShowWindow(hWnd, nCmdShow); 		 
	UpdateWindow(hWnd); 				 
	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	RECT rt;
	HWND convertButton;
	HWND textField;
	HWND resultField;
	HWND currencyList[2];

	switch (message)
	{
	case WM_CREATE: 				
		convertButton = CreateWindow("Button", "Convert", WS_VISIBLE | WS_CHILD ,
			280, 250, 150, 50, hWnd, (HMENU)CONVERT_BUTTON, NULL, NULL);
		currencyList[0] = CreateWindow("COMBOBOX", TEXT(""), CBS_DROPDOWN | WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST,
			30, 120, 120, 500, hWnd, (HMENU)CURR_LIST1, NULL, NULL);
		textField = CreateWindow("Edit", NULL, WS_VISIBLE | WS_CHILD,
			170, 120, 120, 35, hWnd, (HMENU)TEXT_FIELD, NULL, NULL);
		currencyList[1] = CreateWindow("COMBOBOX", NULL, CBS_DROPDOWN | WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST,
			420, 120, 120, 500, hWnd, (HMENU)CURR_LIST2, NULL, NULL);
		resultField = CreateWindow("Static", NULL, WS_VISIBLE | WS_CHILD,
			560, 120, 120, 35, hWnd, (HMENU)RESULT_FIELD, NULL, NULL);

		addItemsInList(currencyList[0]);
		addItemsInList(currencyList[1]);

		break;

	case WM_PAINT: 			
		break;

	case WM_DESTROY: 			
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void addItemsInList(HWND hWnd)
{
	for (int i = 0; i < 12; i++)
		SendMessage(hWnd, CB_ADDSTRING, 0, (LPARAM)currenciesAbbrv[i]);
		
}

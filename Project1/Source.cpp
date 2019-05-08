#include <windows.h>
#include<Windowsx.h>
#include<vector>
#include <string>
#include<iostream>
#include <sstream>
#include"CallPython.h"
//#include"python_training.h"

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
std::vector<const char *> currenciesAbbrv = { "USD", "EUR","GBP","CZK","PLN","CNY","INR","ILS","JPY"};
CallPython call;

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
	wcex.hbrBackground = CreateSolidBrush(RGB(180, 182, 186));
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
	static HWND convertButton;
	static HWND textField;
	static HWND resultField;
	static HWND currencyList[2];
	TCHAR buff[10];
	static char *from;
	static char *to;
	static std::stringstream tempBuff;
	static int selected1, selected2;

	switch (message)
	{
	case WM_CREATE: 				
		convertButton = CreateWindow("Button", "Convert", WS_VISIBLE | WS_CHILD ,
			280, 250, 150, 50, hWnd, (HMENU)CONVERT_BUTTON, NULL, NULL);
		currencyList[0] = CreateWindow("COMBOBOX", TEXT(""), CBS_DROPDOWN | WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST,
			30, 120, 120, 500, hWnd, (HMENU)CURR_LIST1, NULL, NULL);
		textField = CreateWindow("Edit", NULL, WS_VISIBLE | WS_CHILD,
			170, 120, 120, 30, hWnd, (HMENU)TEXT_FIELD, NULL, NULL);
		currencyList[1] = CreateWindow("COMBOBOX", NULL, CBS_DROPDOWN | WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST,
			420, 120, 120, 500, hWnd, (HMENU)CURR_LIST2, NULL, NULL);
		resultField = CreateWindow("Static", NULL, WS_VISIBLE | WS_CHILD,
			560, 120, 120, 30, hWnd, (HMENU)RESULT_FIELD, NULL, NULL);

		addItemsInList(currencyList[0]);
		addItemsInList(currencyList[1]);
	
		break;

	case WM_PAINT: 	

		break;

	case WM_COMMAND:

		switch (wParam)
		{
		case CONVERT_BUTTON:
			float sumOfMoney;
			float result;
			GetWindowText(textField, buff, 10);
			sumOfMoney = atof(buff);
			
			selected1 = ComboBox_GetCurSel(currencyList[0]);
			selected2 = ComboBox_GetCurSel(currencyList[1]);
			from = (char*)currenciesAbbrv[selected1];
			to = (char*)currenciesAbbrv[selected2];

			result = call.convertCurrency(sumOfMoney, from, to);
			tempBuff << result;
			SetWindowText(resultField,tempBuff.str().c_str());

			break;
		
		case CBN_SELCHANGE:


			break;

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

void addItemsInList(HWND hWnd)
{
	for (int i = 0; i < currenciesAbbrv.size(); i++)
		SendMessage(hWnd, CB_ADDSTRING, 0, (LPARAM)currenciesAbbrv[i]);
		
}

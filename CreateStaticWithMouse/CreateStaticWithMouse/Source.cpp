#include "resource.h"
#include <tchar.h>
#include <windows.h>
#include <windowsx.h>
#include <iostream>
#include <string>
#include <vector>


#ifndef UNICODE
#define _tstring std::string
#else
#define _tstring std::wstring
#endif


_tstring sCOORD;
INT x_CUR = 0;
INT y_CUR = 0;
static unsigned int uCountStatic = 0;
HWND hStatic = NULL;
HWND hWinPoint = NULL;
INT wx_CUR = 0;
INT wy_CUR = 0;
INT WIDTH = 10;
INT HEIGHT = 10;
INT min_WIDTH = 10;
INT min_HEIGHT = 10;
INT xRight, yRight;
HINSTANCE hInst;
std::vector<HWND> vector_for_st;


INT_PTR CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE, PTSTR pCmdLine, int nCmdShow)
{
	HWND hDlg = CreateDialog(hInstance, MAKEINTRESOURCE(DIALOG_FOR_STATIC), NULL, DlgProc);
	if (!hDlg)
	{
		MessageBox(NULL, TEXT("Cannot create Dialog!"), TEXT("Error!"), MB_OK | MB_ICONERROR);
		return 0;
	}
	ShowWindow(hDlg, SW_SHOW);
	MSG msg = {};
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

INT_PTR CALLBACK DlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CLOSE:
		DestroyWindow(hwndDlg);
		PostQuitMessage(0);
		return TRUE;
	case WM_LBUTTONDOWN:
		x_CUR = LOWORD(lParam);
		y_CUR = HIWORD(lParam);
		return TRUE;
	case WM_LBUTTONUP:
		wx_CUR = LOWORD(lParam);
		wy_CUR = HIWORD(lParam);
		if (wx_CUR < x_CUR) 
		{
			WIDTH = x_CUR - wx_CUR;
			x_CUR = wx_CUR;
		}
		else 
		{
			WIDTH = wx_CUR - x_CUR;
		}
		if (wy_CUR < y_CUR) 
		{
			HEIGHT = y_CUR - wy_CUR;
			y_CUR = wy_CUR;
		}
		else {
			HEIGHT = wy_CUR - y_CUR;
		}
		if ((WIDTH < min_WIDTH) || (HEIGHT < min_HEIGHT))
			SetWindowText(hwndDlg, TEXT("Cannot create Static, size should be more than 10x10!"));
		else
		{
			++uCountStatic;
			hStatic = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("STATIC"), TEXT("00"), WS_CHILD | WS_VISIBLE, x_CUR, y_CUR, WIDTH, HEIGHT, hwndDlg, NULL, NULL, NULL);
			_tstring sStatic = std::to_wstring(uCountStatic);
			SetWindowText(hStatic, sStatic.c_str());
			vector_for_st.push_back(hStatic);
			return TRUE;
		}
		return TRUE;


	case WM_RBUTTONDOWN:
		xRight = LOWORD(lParam);
		yRight = HIWORD(lParam);
		for (int i = vector_for_st.size() - 1; i >= 0; i--)
		{
			WINDOWPLACEMENT S;
			S.length = sizeof(WINDOWPLACEMENT);
			GetWindowPlacement(vector_for_st[i], &S);

			if (xRight >= S.rcNormalPosition.left && xRight <= S.rcNormalPosition.right &&
				yRight >= S.rcNormalPosition.top && yRight <= S.rcNormalPosition.bottom)
			{
				sCOORD = TEXT("X:");
				sCOORD += std::to_wstring(x_CUR);
				sCOORD += TEXT("Y:");
				sCOORD += std::to_wstring(y_CUR);
				sCOORD += TEXT("width:");
				sCOORD += std::to_wstring(WIDTH);
				sCOORD += TEXT("height:");
				sCOORD += std::to_wstring(HEIGHT);
				sCOORD += TEXT("serial number:");
				sCOORD += std::to_wstring(uCountStatic);
				SetWindowText(hwndDlg, sCOORD.c_str());
				break;
			}
		}
		return TRUE;

	case WM_LBUTTONDBLCLK:
		POINT leftDblClick;
		leftDblClick.x = LOWORD(lParam);
		leftDblClick.y = HIWORD(lParam);
		hWinPoint = ChildWindowFromPoint(hwndDlg, leftDblClick);
		if (hWinPoint != NULL  && hWinPoint != hwndDlg) 
		{
			DestroyWindow(hWinPoint);
			for (size_t j = 0; j < vector_for_st.size(); j++)
				if (hWinPoint == vector_for_st[j])
					vector_for_st.erase(vector_for_st.begin() + j);
	}
	return TRUE;
}
return FALSE;
}
	
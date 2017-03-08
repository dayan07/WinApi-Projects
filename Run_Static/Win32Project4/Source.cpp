#include <windows.h>
#include "resource.h"
#include <tchar.h>

INT x_CUR = 10, y_CUR = 10, WIDTH = 90, HEIGHT = 90; // ��������� �������� �������
HWND hStatic = NULL; // ���������� ���� �������
INT_PTR CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam); // ���������� ���������

INT WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	HWND hWndDlg = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DialogProc);
	ShowWindow(hWndDlg, SW_NORMAL);
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}


INT_PTR CALLBACK DialogProc(HWND hWndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CLOSE:
		DestroyWindow(hWndDlg);
		PostQuitMessage(0);
		return TRUE;
	case WM_INITDIALOG:
	{
		hStatic = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("STATIC"), TEXT("STATIC"), WS_CHILD | WS_VISIBLE, x_CUR, y_CUR, WIDTH, HEIGHT, hWndDlg, NULL, NULL, NULL); // ������� ���� ������� � ���������� ����������
	}
	return TRUE;
	case WM_MOUSEMOVE: // ������ ��������� �������
	{
		x_CUR = rand() % 500; //
		y_CUR = rand() % 500; //��������� ������� ��������� ��������� �������� �� 0 �� 500

		RECT rect,rect1; 
		GetWindowRect(hStatic, &rect); // ���������� ���� ������� � ���������

		POINT hPoint;
		GetCursorPos(&hPoint);// ���������� ������ � ��������� POINT

		if (hPoint.x > rect.left && hPoint.x < rect.right && hPoint.y > rect.top && hPoint.y < rect.bottom) //���� ������ ��� ��������
		{
			GetWindowRect(hWndDlg, &rect1);// ���������� ���������� ���� � ���������
			while (x_CUR <= rect1.left || x_CUR + WIDTH >= rect1.right) // ���� ���������� ������� �� ��������� ����������� ����...
				x_CUR = rand() % 500; // ... ���� ����� ���������� ��� �������
			while (y_CUR <= rect1.top | y_CUR + HEIGHT >= rect1.bottom)
				y_CUR = rand() % 500;
			MoveWindow(hStatic, x_CUR, y_CUR, WIDTH, HEIGHT, true);// ���� ������ � �������� ���� �������������� ������
		}
		else
			SetWindowText(hWndDlg, TEXT("Out of text"));
	}
	return TRUE;
	}
	return FALSE;
}
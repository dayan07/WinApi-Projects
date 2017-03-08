#include <windows.h>
#include "resource.h"
#include <tchar.h>

INT x_CUR = 10, y_CUR = 10, WIDTH = 90, HEIGHT = 90; // начальные значения статика
HWND hStatic = NULL; // дескриптор окна статика
INT_PTR CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam); // диалоговая процедура

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
		hStatic = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("STATIC"), TEXT("STATIC"), WS_CHILD | WS_VISIBLE, x_CUR, y_CUR, WIDTH, HEIGHT, hWndDlg, NULL, NULL, NULL); // создаем окно статика с начальными значениями
	}
	return TRUE;
	case WM_MOUSEMOVE: // случай наведения курсора
	{
		x_CUR = rand() % 500; //
		y_CUR = rand() % 500; //параметры статика принимают случайное значение от 0 до 500

		RECT rect,rect1; 
		GetWindowRect(hStatic, &rect); // записываем окно статика в структуру

		POINT hPoint;
		GetCursorPos(&hPoint);// записываем курсор в структуру POINT

		if (hPoint.x > rect.left && hPoint.x < rect.right && hPoint.y > rect.top && hPoint.y < rect.bottom) //если курсор над статиком
		{
			GetWindowRect(hWndDlg, &rect1);// записываем диалоговое окно в структуру
			while (x_CUR <= rect1.left || x_CUR + WIDTH >= rect1.right) // пока координаты статика за пределами диалогового окна...
				x_CUR = rand() % 500; // ... ищем новые координаты для статика
			while (y_CUR <= rect1.top | y_CUR + HEIGHT >= rect1.bottom)
				y_CUR = rand() % 500;
			MoveWindow(hStatic, x_CUR, y_CUR, WIDTH, HEIGHT, true);// если статик в пределах окна перерисовываем статик
		}
		else
			SetWindowText(hWndDlg, TEXT("Out of text"));
	}
	return TRUE;
	}
	return FALSE;
}
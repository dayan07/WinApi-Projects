#include <windows.h>
#include <windowsx.h>
#include <tchar.h>
#include <string>


#ifdef _UNICODE
#define _tstring std::wstring
#define to_tstring std::to_wstring
#define _tchar std::wchar
#else 
#define _tstring  std::string
#define to_tstring std::to_string
#define _tchar std::char
#endif


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR pCmdLine, int nCmdShow)
{
	// Register the window class.
	const TCHAR CLASS_NAME[] = TEXT("Sample Window Class");

	WNDCLASS wc = {};

	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;
	wc.style = CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

	RegisterClass(&wc);

	// Create the window.

	HWND hwnd = CreateWindowEx(
		0,                              // Optional window styles.
		CLASS_NAME,                     // Window class
		TEXT("Learn to Program Windows"),// Window text
		WS_OVERLAPPEDWINDOW,      // Window style
									  // Size and position
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

		NULL,       // Parent window    
		NULL,       // Menu
		hInstance,  // Instance handle
		NULL        // Additional application data
		);

	if (hwnd == NULL)
	{
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);

	// Run the message loop.

	MSG msg = {};
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
	{
		if (wParam == 0x0D)
		{
			SetTimer(hwnd, 1, 1000, NULL);
		}
		else if (wParam == 0x1B)
		{
			KillTimer(hwnd, 1);
		}
		break;
	}

	case WM_TIMER:
	{
		if (wParam == 1)
		{
			int xPos = 0;
			int yPos = 0;
			HDC hDCScreen = GetDC(NULL);//считать контекст дисплея
			int Horres = GetDeviceCaps(hDCScreen, HORZRES);//Разрешение экрана по горизонтали
			int Vertres = GetDeviceCaps(hDCScreen, VERTRES);//Разрешение экрана по вертикали
			ReleaseDC(NULL, hDCScreen);//необходимо вызывать при каждом вызове GetDC
			SetWindowPos(hwnd, HWND_TOP, xPos, yPos, 300, 300, SWP_SHOWWINDOW);

			for (int i = 0; i < Horres - 300; i++)
			{
				SetWindowPos(hwnd, HWND_TOP, xPos++, yPos, 300, 300, SWP_SHOWWINDOW);
			}
			for (int i = 0; i < Vertres - 300; i++)
			{
				SetWindowPos(hwnd, HWND_TOP, xPos, yPos++, 300, 300, SWP_SHOWWINDOW);
			}

			for (int i = 0; i < Horres - 300; i++)
			{
				SetWindowPos(hwnd, HWND_TOP, xPos--, yPos, 300, 300, SWP_SHOWWINDOW);
			}

			for (int i = 0; i < Vertres - 300; i++)
			{
				SetWindowPos(hwnd, HWND_TOP, xPos, yPos--, 300, 300, SWP_SHOWWINDOW);
			}
		}
		break;
	}
	default:

			return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}
#include "resource.h"
#include <tchar.h>
#include <windows.h>
#include <string>
#include <vector>
#include <stack>
#include <iostream>



#ifdef _UNICODE
#define _tstring std::wstring
#define to_tstring std::to_wstring
#else 
#define _tstring  std::string
#define to_tstring std::to_string
#endif

_tstring str; // строка в которую записываются числа и операции
double Calculation(_tstring &exp);// строка потом передается в эту функцию, где вычисляется результат
INT_PTR CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE, PTSTR pCmdLine, int nCmdShow)
{
	HWND hDlg = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
	if (!hDlg)
	{
		MessageBox(NULL, TEXT("Cannot create Calculator!"), TEXT("Error!"), MB_OK | MB_ICONERROR);
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

BOOL DlgCommandProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	
	HWND One = GetDlgItem(hwndDlg, ID_1);
	HWND Two = GetDlgItem(hwndDlg, ID_2);
	HWND Three = GetDlgItem(hwndDlg, ID_3);
	HWND Four = GetDlgItem(hwndDlg, ID_4);
	HWND Five = GetDlgItem(hwndDlg, ID_5);
	HWND Six = GetDlgItem(hwndDlg, ID_6);
	HWND Seven = GetDlgItem(hwndDlg, ID_7);
	HWND Eight = GetDlgItem(hwndDlg, ID_8);
	HWND Nine = GetDlgItem(hwndDlg, ID_9);
	HWND Zero = GetDlgItem(hwndDlg, ID_0);
	HWND Result = GetDlgItem(hwndDlg, ID_RESULT);
	HWND Plus = GetDlgItem(hwndDlg, ID_PLUS1);
	HWND Minus = GetDlgItem(hwndDlg, ID_MINUS);
	HWND Prod = GetDlgItem(hwndDlg, ID_PROD);
	HWND Div = GetDlgItem(hwndDlg, ID_DIV);
	HWND Out = GetDlgItem(hwndDlg, ID_EDIT);
	_tstring result;
	if (HIWORD(wParam) == BN_CLICKED)
	{
		switch (LOWORD(wParam))
		{
		case ID_1:
			str += TEXT('1');
			EnableWindow(One, TRUE);
			SetFocus(One);
			SetWindowText(Out, str.c_str());
			break;
		case ID_2:
			str += TEXT('2');
			EnableWindow(Two, TRUE);
			SetFocus(Two);
			SetWindowText(Out, str.c_str());
			break;
		case ID_3:
			str += TEXT('3');
			EnableWindow(Three, TRUE);
			SetFocus(Three);
			SetWindowText(Out, str.c_str());
			break;
		case ID_4:
			str += TEXT('4');
			EnableWindow(Four, TRUE);
			SetFocus(Four);
			SetWindowText(Out, str.c_str());
			break;
		case ID_5:
			str += TEXT('5');
			EnableWindow(Five, TRUE);
			SetFocus(Five);
			SetWindowText(Out, str.c_str());
			break;
		case ID_6:
			str += TEXT('6');
			EnableWindow(Six, TRUE);
			SetFocus(Six);
			SetWindowText(Out, str.c_str());
			break;
		case ID_7:
			str += TEXT('7');
			EnableWindow(Seven, TRUE);
			SetFocus(Seven);
			SetWindowText(Out, str.c_str());
			break;
		case ID_8:
			str += TEXT('8');
			EnableWindow(Eight, TRUE);
			SetFocus(Eight);
			SetWindowText(Out, str.c_str());
			break;
		case ID_9:
			str += TEXT('9');
			EnableWindow(Nine, TRUE);
			SetFocus(Nine);
			SetWindowText(Out, str.c_str());
			break;
		case ID_0:
			str += TEXT('0');
			EnableWindow(Zero, TRUE);
			SetFocus(Zero);
			SetWindowText(Out, str.c_str());
			break;
		case ID_PLUS1:
			str += TEXT('+');
			EnableWindow(Plus, TRUE);
			SetFocus(Plus);
			SetWindowText(Out, str.c_str());
			break;
		case ID_MINUS:
			str += TEXT('-');
			EnableWindow(Minus, TRUE);
			SetFocus(Minus);
			SetWindowText(Out, str.c_str());
			break;
		case ID_PROD:
			str += TEXT('*');
			EnableWindow(Prod, TRUE);
			SetFocus(Prod);
			SetWindowText(Out, str.c_str());
			break;
		case ID_DIV:
			str += TEXT('/');
			EnableWindow(Div, TRUE);
			SetFocus(Div);
			SetWindowText(Out, str.c_str());
			break;
		case ID_RESULT:
			EnableWindow(Result, TRUE);
			SetFocus(Result);
			result += to_tstring(Calculation(str)); // результат вычисления функции преобразуется в строку и помещается в result
			SetWindowText(Out, result.c_str()); // строка result выводится в EDIT COTROL
			str.clear(); // после вывода строка очищается
			break;
		default:
			return FALSE;
		}
		return TRUE;
	}
}
INT_PTR CALLBACK DlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CLOSE:
		DestroyWindow(hwndDlg);
		PostQuitMessage(0);
		break;
	case WM_COMMAND:
		return DlgCommandProc(hwndDlg, uMsg, wParam, lParam);
	
	default:
		return FALSE;
	}
	return TRUE;
}
double Calculation(_tstring &exp)
{
	struct ALL
	{
		TCHAR   type;
		DOUBLE  num;
	}s_ALL; // структуры для хранения чисел и операций из строки
	INT PRIOR(TCHAR op); // функция для определения приоритета операций
	std::vector<ALL> operand; // вектор для хранения операндов и операций после операндов
	std::stack<DOUBLE> result_stack; // результирующий стек, где в итоге получим результат вычисления
	DOUBLE operand1, operand2, result;
	_tstring::iterator it, begin; 
	std::stack<TCHAR> expstack; // промежуточный стек для хранения операций
	
	for (it = exp.begin(); it != exp.end(); it++)
	{
		if (isdigit(*it)) // если число, записываем в вектор в любом случае
		{
			begin = it;  
			for (; it != exp.end(); it++)
			{
				if (!isdigit(*it))
					break;
			}
			s_ALL.num = _wtof(_tstring(begin, it).c_str()); // преобразование в double
			s_ALL.type = 'd'; // метка для double
			operand.push_back(s_ALL);
			--it; 
			continue;
		}
		else
		{
			if (expstack.empty()) 
			{
				expstack.push(*it);// иначе, если операция, если стек пустой, записываем в промежуточный стек
				continue;
			}
			while (!expstack.empty() && PRIOR(expstack.top()) >= PRIOR(*it))// пока стек не пуст, а приоритет верхнего элемента стека выше или равен новому элементу, нужно переписать операции из стека в вектор поверх операндов
			{
				s_ALL.type = expstack.top();
				operand.push_back(s_ALL);// записываем верхний  элемент в вектор на структурах
				expstack.pop();//  верхний элемент стека удаляем, мы его уже записали в вектор
			}
			expstack.push(*it); // иначе, если стек не пуст и приоритет нового элемента выше вехнего элемента в стеке, записываем новый элемент в стек
		}
	}
	         
	while (!expstack.empty())// оставшиеся операции в стеке, переписываем из стека в вектор по порядку, пока он не опустеет
	{
		s_ALL.type = expstack.top();
		operand.push_back(s_ALL);
		expstack.pop();
	}
	// подсчитываем выражение, записанное в векторе в виде операндов и операций после них в зависимости от приоритета
	for (std::vector<ALL>::iterator vt = operand.begin(); vt != operand.end(); ++vt)
	{
		if (vt->type == 'd') 
		{
			result_stack.push(vt->num);// если элемент число, записываем его значение в результирующий стек
			continue;
		}
		// иначе, если встречается операция, записываем находящиеся перед ней операции и выполняем операции над ними
		operand1 = result_stack.top();
		result_stack.pop();
		operand2 = result_stack.top();
		result_stack.pop();

		switch (vt->type)
		{
		case '+':
			result = operand1 + operand2;
			break;
		case '-':
			result = operand2 - operand1;
			break;
		case '*':
			result = operand1 * operand2;
			break;
		case '/':
			result = operand2 / operand1;
			break;
		}
		result_stack.push(result); // результат вычислений записываем в результирующий стек
	}

	return result_stack.top();// возвращаем результат вычислений
}


INT PRIOR(TCHAR op)
{
	switch (op)
	{
	case '*':
	case '/':
		return 3;
	case '+':
	case '-':
		return 2;
	}
	return 0;
}
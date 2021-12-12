#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>
#include <time.h>
#include <RestartManager.h>
#define BUFF "                                           "
#define OUTPUTSTROKE "Чтобы изменить тип шрифта нажмите q.\nЧтобы поменять цвет шрифта нажмите w.\nЧтобы поменять цвет заднего фона нажмите e.\nЧтобы поменять размер шрифта нажмите r.\nЧтобы выйти нажмите t.\n"


CONSOLE_FONT_INFOEX cfi = {0};
CONSOLE_SCREEN_BUFFER_INFO cbsi;

COORD _GetCursorP()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsole, &cbsi);// Нужен для извлечения позиции курсора в консоли
	return cbsi.dwCursorPosition;
}

void _RefreshScreen(int x, int y, LPWSTR str)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsole, (COORD) { x, y });
	printf("%s\n%s\n%s\n%s\n%s\n%s\n", BUFF, BUFF, BUFF, BUFF, BUFF, BUFF);
	SetConsoleCursorPosition(hConsole, (COORD) { x, y });
	printf("%s" ,str);
}

int main(int argc, char* argv[])
{
	/*HKEY hKey, MyParam;
	time_t rawtime;
	struct tm* timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	LPWSTR strStandart = L"Рома лох",strString = L"Строковый параметр " ;
	WCHAR arr[512];
	if (RegOpenKeyW(HKEY_CURRENT_USER,NULL, &hKey) !=0)
	{
		return 1;
	}
	RegCreateKeyW(hKey, L"MyParam", &MyParam);
	RegSetValueW(hKey, L"MyParam", REG_SZ, strStandart, wcslen(strStandart) * sizeof(WCHAR));


	LPWSTR b = asctime(timeinfo);
	WCHAR NewB[40];
	int result = MultiByteToWideChar(CP_OEMCP, 0, b, -1, NULL, 0);
	MultiByteToWideChar(CP_OEMCP, 0, b, -1, NewB, result);
	swprintf(arr,512*2,L"%s%s", strString, NewB);
	RegSetValueExW(MyParam,L"StringParam", NULL, REG_SZ, arr, wcslen(arr)*2);

	RegCloseKey(hKey);
	RegCloseKey(MyParam);

	LPWSTR StrKey = calloc(200,2);
	DWORD dataType = 0, dataLen = 400;
	if (RegGetValueW(HKEY_CURRENT_USER, L"MyParam", L"StringParam",RRF_RT_ANY, &dataType, StrKey, &dataLen) == ERROR_SUCCESS)
	{
		MessageBox(NULL, StrKey, L"", MB_OK);
	}*/	
	    SetConsoleCP(1251);
	    SetConsoleOutputCP(1251);
	    memset(&cfi, 0, sizeof(cfi));											// выделяем память под структуру CONSOLE_FONT_INFOEX, в которой хранится информация о шрифтах
	    cfi.cbSize = sizeof(cfi);
		GetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);	// записываем в структуру настройки днфолтных шрифтов шрифтов
		
		printf("%s" ,OUTPUTSTROKE);

		HKEY KeyConsoleSettings, KeyTrueConsole; //создаём дискрипторы для работы с реестром		
		
		RegCreateKeyW(HKEY_CURRENT_USER, L"ConsoleSettings", &KeyConsoleSettings); //создаём в реестре папку для хранения настроек (и присваесае дискриптору его значение)

		RegSetValueExW(KeyConsoleSettings, L"FontFamily", NULL, REG_SZ, L"Consolas", 8 * 2); //заполняем папку параметрами
		RegSetValueExW(KeyConsoleSettings, L"FontColor", NULL, REG_SZ, L"White", 6 * 2);
		RegSetValueExW(KeyConsoleSettings, L"ForgroundColor", NULL, REG_SZ, L"Black", 6 * 2);
		RegSetValueExW(KeyConsoleSettings, L"FontSize", NULL, REG_SZ, L"Classic", 8 * 2);

		RegCreateKeyW(HKEY_CURRENT_USER, // присваеваем дискриптору "путь" путь к папке хранящую данные о консоли VS (пока не используется)
			L"Console\\C:_Program Files (x86)_Microsoft Visual Studio_2019_Community_Common7_IDE_CommonExtensions_Platform_Debugger_VsDebugConsole.exe",
			&KeyTrueConsole);		

		DWORD dataType = 0, dataLen = 40;
		char c = L'w', b = L'b';

		while (1) //цикл 
		{
			LPWSTR StrSetting = calloc(20, 2);
			dataType = 0; dataLen = 40;
			switch (_getch())
			{
			case L'q':// тип щрифта
			case L'Q':
			case L'Й':
			case L'й':
				if (RegGetValueW(KeyConsoleSettings, NULL, L"FontFamily", RRF_RT_ANY, &dataType, StrSetting, &dataLen) == ERROR_SUCCESS)
				{
					if (StrSetting[0] == L'C')
					{												
						wcscpy_s(cfi.FaceName, 20 * 2, L"MS Gothic");
						RegSetValueExW(KeyConsoleSettings, L"FontFamily", NULL, REG_SZ, L"MS Gothic", 10 * 2);
					}
					else
					{
						wcscpy_s(cfi.FaceName, 20 * 2, L"Consolas");						
						RegSetValueExW(KeyConsoleSettings, L"FontFamily", NULL, REG_SZ, L"Consolas", 10 * 2);
					}
					SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
				}
				else
				{
					MessageBox(NULL, L"Ошибка", L"Не возможно считать данные", MB_OK | MB_ICONERROR);
				}
				break;

			case L'ц': // цвет шрифта
			case L'Ц':
			case L'w':
			case L'W':
				if (RegGetValueW(KeyConsoleSettings, NULL, L"FontColor", RRF_RT_ANY, &dataType, StrSetting, &dataLen) == ERROR_SUCCESS)
				{
					if (StrSetting[0] == L'W')
					{
						if (b == 'b')
						{
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
						}
						else
						{
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | BACKGROUND_GREEN);
						}
						_RefreshScreen(0, 0, OUTPUTSTROKE);
						RegSetValueExW(KeyConsoleSettings, L"FontColor", NULL, REG_SZ, L"Red", 6 * 2);
						c = L'r';
					}
					else
					{
						if (b == 'g')
						{
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN| BACKGROUND_GREEN);
						}
						else
						{
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
						}
						_RefreshScreen(0, 0, OUTPUTSTROKE);						
						RegSetValueExW(KeyConsoleSettings, L"FontColor", NULL, REG_SZ, L"White", 6 * 2);
						c = L'w';
					}					
				}
				else
				{
					MessageBox(NULL, L"Ошибка", L"Не возможно считать данные", MB_OK | MB_ICONERROR);
				}
				break;

			case L'у': // цвет заднего фона
			case L'У':
			case L'E':
			case L'e':
				if (RegGetValueW(KeyConsoleSettings, NULL, L"ForgroundColor", RRF_RT_ANY, &dataType, StrSetting, &dataLen) == ERROR_SUCCESS)
				{
					if (StrSetting[0] == L'B')
					{
						if (c == 'w')
						{
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | BACKGROUND_GREEN);
						}
						else
						{
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | BACKGROUND_GREEN);
						}
						_RefreshScreen(0, 0, OUTPUTSTROKE);
						RegSetValueExW(KeyConsoleSettings, L"ForgroundColor", NULL, REG_SZ, L"Green", 6 * 2);
						b = L'g';
					}
					else
					{
						if (c == 'w')
						{
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
						}
						else
						{
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED  );
						}						
						_RefreshScreen(0, 0, OUTPUTSTROKE);
						RegSetValueExW(KeyConsoleSettings, L"ForgroundColor", NULL, REG_SZ, L"Black", 6 * 2);
						b = L'b';
					}
				}
				else
				{
					MessageBox(NULL, L"Ошибка", L"Не возможно считать данные", MB_OK | MB_ICONERROR);
				}
				break;

			case L'r':// размер шрифта
			case L'R':
			case L'К':
			case L'к':
				if (RegGetValueW(KeyConsoleSettings, NULL, L"FontSize", RRF_RT_ANY, &dataType, StrSetting, &dataLen) == ERROR_SUCCESS)
				{					
					if (StrSetting[0] == L'C')
					{
						cfi.dwFontSize.Y -= 6;
						RegSetValueExW(KeyConsoleSettings, L"FontSize", NULL, REG_SZ, L"NonClassic", 11 * 2);
					}
					else
					{
						cfi.dwFontSize.Y += 6;
						RegSetValueExW(KeyConsoleSettings, L"FontSize", NULL, REG_SZ, L"Classic", 8 * 2);
					}
					SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
				}
				else
				{
					MessageBox(NULL, L"Ошибка", L"Не возможно считать данные", MB_OK | MB_ICONERROR);
				}
				break;

			case L't':// выход
			case L'T':
			case L'Е':
			case L'е':
				RegCloseKey(KeyConsoleSettings);
				RegCloseKey(KeyTrueConsole);
				return 0;
			}
			free(StrSetting);
		}
		RegCloseKey(KeyConsoleSettings);
		RegCloseKey(KeyTrueConsole);
		return 0;
	
}


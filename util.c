#include "base.h"

/*隐藏光标*/
void show_cursor(BOOL hide)
{
	CONSOLE_CURSOR_INFO cciCursor;
	HANDLE hout;

	hout = GetStdHandle(STD_OUTPUT_HANDLE);
	if (GetConsoleCursorInfo(hout, &cciCursor))
	{
		cciCursor.bVisible = hide;
		SetConsoleCursorInfo(hout, &cciCursor);
	}
}

/*修改控制台尺寸*/
void modify_wnd(int w, int h)
{
	COORD size = { 0 };
	SMALL_RECT s_rc = { 0 };
	HANDLE hout;
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	hout = GetStdHandle(STD_OUTPUT_HANDLE);

	size.X = w;
	size.Y = h;

	s_rc.Right = size.X - 1;
	s_rc.Bottom = size.Y - 1;


	SetConsoleWindowInfo(hout, TRUE, &s_rc);
	SetConsoleScreenBufferSize(hout, size);

	GetConsoleScreenBufferInfo(hout, &csbi);
}

void gotoxy(int x, int y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void set_color(WORD color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}


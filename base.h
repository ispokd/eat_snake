#pragma once

#include <stdio.h>
#include <conio.h>
#include <io.h>
#include <Windows.h>
#include <time.h>

void show_cursor(BOOL hide);
void gotoxy(int x, int y);
void modify_wnd(int w, int h);
void set_color(WORD color);
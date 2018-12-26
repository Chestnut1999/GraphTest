#pragma once
#include "T_Menu.h"

class MyMenu :public T_Menu {
	public :
		MyMenu();
		virtual ~MyMenu();
		void DrawMenu(HDC hdc, float ratio=1,BYTE btnTrans = 255, bool startState = true);

};
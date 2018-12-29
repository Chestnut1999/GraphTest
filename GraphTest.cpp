#include "GraphTest.h"
TOWERS GraphTest::tInfo[6] = {
	//炮塔图片  攻速  伤害值  攻击范围  攻击类型  买进价格  卖出价格  造成的减速量  图片缩放比率
	{L"res\\tower\\bottle.png",{1.82,2.29,3.57},{10,12,13}, },
	{},
	{},
	{},
	{},
	{}
};
MONSTER GraphTest::mInfo[8] = {
	//
};
PROPERTY GraphTest::pInfo[10] = {
	// 道具图片   道具生命值    道具奖励金   图片缩放比率
	{L"res\\property\\bigmoney.png",2500,2500,0.8},
	{ L"res\\property\\colors.png",1300,150,0.8 },
	{ L"res\\property\\crystal.png",670,75,0.8 },
	{ L"res\\property\\crystals.png",1300,150,0.8 },
	{ L"res\\property\\house.png",2500,268,0.8 },
	{ L"res\\property\\red.png",670,75,0.8 },
	{ L"res\\property\\smallmoney.png",1300,1000,0.8 },
	{ L"res\\property\\stone.png",1300,150,0.8 },
	{ L"res\\property\\tree.png",670,75,0.8 },
	{ L"res\\property\\trees.png",2500,268,0.8 },
};
GraphTest::GraphTest(HINSTANCE hInstance, LPCTSTR szWindowClass, LPCTSTR szTitle,
	WORD Icon, WORD SmIcon, int iWidth, int iHeight) :T_Engine(hInstance,
		szWindowClass, szTitle, Icon, SmIcon, iWidth, iHeight)
{
	srand((unsigned)time(NULL));
	wnd_width = iWidth;
	wnd_height = iHeight;
}

GraphTest::~GraphTest()
{
}

void GraphTest::GameInit()
{
	LoadMusic();
	loadMenu();
	LoadImg();
}

void GraphTest::GameLogic()
{
	if (GameState == GAME_RUN)
	{
		total = total - 10;
		if (total == 0)
			total = 100;
	}
}

void GraphTest::GameEnd()
{
	
}

void GraphTest::GamePaint(HDC hdc)
{
	if (GameState == GAME_START)
	{
		p_menu->DrawMenu(hdc,1,255,true);
		set_menu.DrawMenu(hdc, 0.5);
		start_menu.DrawMenu(hdc,0.5);
		
	}
	else if (GameState == GAME_SCREEN)
	{
		p_screenmenu->DrawMenu(hdc,1,0,255,true);
		main_menu.DrawMenu(hdc,0.7);
	}
	else if (GameState == GAME_ABOUT)
	{
		p_aboutmenu->DrawMenu(hdc);

		//T_Graph::PaintBlank(hdc, 360, 50, 400, 360, Color::Green, 80);

		RectF infoRec;
		infoRec.X = 0.00;
		infoRec.Y = 180.00;
		infoRec.Width = (float)wnd_width;
		infoRec.Height = (float)wnd_height/2-30 ;

		LPCTSTR info = L" 组号:6\n\n 8000116024  白星宇\n\n8000116120  王一清\n\n8000116127  张 涵";
		T_Graph::PaintText(hdc, infoRec, info, 25, L"华康少女文字W5", Color(255, 252, 231), FontStyleBold, StringAlignmentCenter);
	}
	else if (GameState == GAME_SETTING)
	{
		p_setBack_menu->DrawMenu(hdc, 1, 255, true);
		RectF infoRec;
		infoRec.X = 250.00;
		infoRec.Y = 110.00;
		infoRec.Width = (float)wnd_width;
		infoRec.Height = (float)wnd_height / 2 - 30;

		LPCTSTR info = L" 背景音乐:";
		T_Graph::PaintText(hdc, infoRec, info, 25, L"华康少女文字W5", Color(255, 252, 231), FontStyleBold, StringAlignmentNear);

		infoRec.X = 250.00;
		infoRec.Y = 250.00;
		infoRec.Width = (float)wnd_width;
		infoRec.Height = (float)wnd_height / 2 - 30;

		info = L" 按键音乐:";
		T_Graph::PaintText(hdc, infoRec, info, 25, L"华康少女文字W5", Color(255, 252, 231), FontStyleBold, StringAlignmentNear);
		setm_menu1.DrawMenu(hdc);
		setm_menu2.DrawMenu(hdc);
	}
	else if (GameState == GAME_RUN)
	{
		switch (guan)
		{
		case 1:
			LoadGuan();
			LoadMap("res\\map\\guan1.txt");
			updateProLife(hdc);
			t_scence->Draw(hdc, 0, 0);
			break;
		case 2:
			LoadGuan();
			LoadMap("res\\map\\guan2.txt");
			updateProLife(hdc);
			t_scence->Draw(hdc, 0, 0);
			break;
		case 3:
			LoadGuan();
			LoadMap("res\\map\\guan3.txt");
			updateProLife(hdc);
			t_scence->Draw(hdc, 0, 0);
			break;
		case 4:
			LoadGuan();
			LoadMap("res\\map\\guan4.txt");
			updateProLife(hdc);
			t_scence->Draw(hdc, 0, 0);
			break;
		}
		run_menu.DrawMenu(hdc);
	}
}

void GraphTest::GameKeyAction(int ActionType)
{
	if (GameState == GAME_START)
	{
		if (GetAsyncKeyState(VK_UP) < 0)
			p_menu->MenuKeyDown(VK_UP);
		if (GetAsyncKeyState(VK_DOWN) < 0)
			p_menu->MenuKeyDown(VK_DOWN);
		if (GetAsyncKeyState(VK_LEFT) < 0)
			p_menu->MenuKeyDown(VK_LEFT);
		if (GetAsyncKeyState(VK_RIGHT) < 0)
			p_menu->MenuKeyDown(VK_RIGHT);
		if (GetAsyncKeyState(VK_RETURN) < 0)
		{
			if (p_menu->GetMenuIndex() >= 0)
			{
				switch (p_menu->GetMenuIndex())
				{
				case 0:
					GameState = GAME_SCREEN;			
					break;
				case 1:
					SendMessage(m_hWnd, WM_SYSCOMMAND, SC_CLOSE, 0);
					break;
				}
			}
		}
	}
	else if (GameState == GAME_ABOUT)
	{
		if (GetAsyncKeyState(VK_UP) < 0)
			p_aboutmenu->MenuKeyDown(VK_UP);
		if (GetAsyncKeyState(VK_DOWN) < 0)
			p_aboutmenu->MenuKeyDown(VK_DOWN);
		if (GetAsyncKeyState(VK_LEFT) < 0)
			p_aboutmenu->MenuKeyDown(VK_LEFT);
		if (GetAsyncKeyState(VK_RIGHT) < 0)
			p_aboutmenu->MenuKeyDown(VK_RIGHT);
		if (GetAsyncKeyState(VK_RETURN) < 0)
		{
			if (p_aboutmenu->GetMenuIndex() >= 0)
			{
				switch (p_aboutmenu->GetMenuIndex())
				{
				case 0:
					GameState = GAME_START;
					break;
				case 1:
					SendMessage(m_hWnd, WM_SYSCOMMAND, SC_CLOSE, 0);
					break;
				}
			}
		}
	}
	else if (GameState == GAME_RUN) {
		
		
	}
}

void GraphTest::GameMouseAction(int x, int y, int ActionType)
{
	if (GameState == GAME_START)
	{
		if (ActionType == MOUSE_MOVE&&GameState != GAME_RUN)
		{
			p_menu->MenuMouseMove(x, y);
			start_menu.MenuMouseMove(x, y);
			set_menu.MenuMouseMove(x, y);
		}
		if (ActionType == MOUSE_LCLICK)
		{
			int index = p_menu->MenuMouseClick(x, y);
			int aboutindex = start_menu.MenuMouseClick(x, y);
			int setindex = set_menu.MenuMouseClick(x, y);
			if (index >= 0)
			{
				switch (index)
				{
				case 0:
					GameState = GAME_SCREEN;
					break;
				case 1:
					SendMessage(m_hWnd, WM_SYSCOMMAND, SC_CLOSE, 0);
					break;
				}
			}
			if(aboutindex==0)  GameState = GAME_ABOUT;
			//如果点击设置(小螺丝钉)
			if (setindex == 0)  GameState = GAME_SETTING;
		}
	}
	else if (GameState == GAME_SCREEN)
	{
		if (ActionType == MOUSE_MOVE&&GameState != GAME_RUN)
		{
			p_screenmenu->MenuMouseMove(x, y);
			main_menu.MenuMouseMove(x, y);
		}
		if (ActionType == MOUSE_LCLICK)
		{
			int index = p_screenmenu->MenuMouseClick(x, y);
			int mainindex = main_menu.MenuMouseClick(x, y);
			if (index >= 0)
			{
				switch (index)
				{
				case 0:
					GameState = GAME_RUN;
					guan = 1;		
					break;
				case 1:
					GameState = GAME_RUN;
					guan = 2;
					break;
				case 2:
					GameState = GAME_RUN;
					guan = 3;
					break;
				case 3:
					GameState = GAME_RUN;
					guan = 4;
					break;
				}
				bg_buffer.Stop();
				if (flagbg)
				{
					runbg_buffer.Play(true);
				}
				
			}
			if (mainindex == 0)  GameState = GAME_START;
		}
	}
	else if (GameState == GAME_ABOUT)
	{
		if (ActionType == MOUSE_MOVE&&GameState != GAME_RUN)
		{
			p_aboutmenu->MenuMouseMove(x, y);
		}
		if (ActionType == MOUSE_LCLICK)
		{
			int index = p_aboutmenu->MenuMouseClick(x, y);
			if (index >= 0)
			{
				switch (index)
				{
				case 0:
					GameState = GAME_START;
					
					break;
				case 1:
					SendMessage(m_hWnd, WM_SYSCOMMAND, SC_CLOSE, 0);
					break;
				}
			}
		}
	}
	else if (GameState == GAME_RUN)
	{
		if (ActionType == MOUSE_MOVE)
		{
			run_menu.MenuMouseMove(x, y);
		}
		if (ActionType == MOUSE_LCLICK)
		{
			int index = run_menu.MenuMouseClick(x, y);
			if (index == 0)
			{
				GameState = GAME_SCREEN;

			}
		}
	}
	//设置页面
	else if (GameState == GAME_SETTING)
	{
		wstring setItems[] = { L" " };
		MENUITEM mItem;
		if (ActionType == MOUSE_MOVE)
		{
			p_setBack_menu->MenuMouseMove(x, y);
			setm_menu1.MenuMouseMove(x, y);
			setm_menu2.MenuMouseMove(x, y);
		}
		if (ActionType == MOUSE_LCLICK)
		{
			int index1 = setm_menu1.MenuMouseClick(x, y);
			int index2 = setm_menu2.MenuMouseClick(x, y);
			int index = p_setBack_menu->MenuMouseClick(x,y);
			
			if (index == 0)  GameState = GAME_START;
			//设置音效是开启或关闭
			if (index1 == 0)
			{
				mItem.pos.x = 470;
				mItem.pos.y = 200;
				mItem.ItemName = setItems[0];
				setm_menu1.AddMenuItem(mItem);
				if (flagbg==false)
				{
					//bg_buffer.Restore();
					bg_buffer.Play(true);
					//runbg_buffer.Restore();
					//runbg_buffer.Play(true);
					flagbg = true;

					setMenu(&setm_menu1, 200, 100, L"res\\menu\\kai.png", setItems);
				}
				else if (flagbg == true)
				{
					bg_buffer.Stop();
					//runbg_buffer.Stop();
					flagbg = false;

					setMenu(&setm_menu1, 200, 100, L"res\\menu\\guan.png", setItems);
				}
			}
			 if (index2 == 0)
			{
				 mItem.pos.x = 470;
				 mItem.pos.y = 350;
				 mItem.ItemName = setItems[0];
				 setm_menu1.AddMenuItem(mItem);
				if (flagbut == false)
				{
					stopClickMusic(button_click_buffer, button_move_buffer);
					flagbut = true;

					setMenu(&setm_menu2, 200, 100, L"res\\menu\\kai.png", setItems);
				}
				else if (flagbut == true)
				{
					t_menu.SetClickSound(NULL);
					start_menu.SetClickSound(NULL);
					about_menu.SetClickSound(NULL);
					screen_menu.SetClickSound(NULL);
					setm_menu1.SetClickSound(NULL);
					setm_menu2.SetClickSound(NULL);
					setBack_menu.SetClickSound(NULL);
					run_menu.SetClickSound(NULL);
					main_menu.SetClickSound(NULL);
					set_menu.SetClickSound(NULL);

					t_menu.SetMoveSound(NULL);
					start_menu.SetMoveSound(NULL);
					about_menu.SetMoveSound(NULL);
					screen_menu.SetMoveSound(NULL);
					setm_menu1.SetMoveSound(NULL);
					setm_menu2.SetMoveSound(NULL);
					setBack_menu.SetMoveSound(NULL);
					run_menu.SetMoveSound(NULL);
					main_menu.SetMoveSound(NULL);
					set_menu.SetMoveSound(NULL);
					flagbut = false;

					setMenu(&setm_menu2, 200, 100, L"res\\menu\\guan.png", setItems);
				}

			}

		}
	}
}

void GraphTest::loadMenu()
{
	int x = 0, y = 0;
	int btn_width = 0, btn_height = 0;     //主菜单和关于界面的菜单
	p_menu = &t_menu;
	p_aboutmenu = &about_menu;
	p_screenmenu = &screen_menu;
	p_setBack_menu = &setBack_menu;
	p_start_menu = &start_menu;
	p_menu->SetMenuBkg(L"res\\menu\\menu.png");
	p_aboutmenu->SetMenuBkg(L"res\\menu\\about_bak.png");
	p_screenmenu->SetMenuBkg(L"res\\menu\\guanc.png");
	p_setBack_menu->SetMenuBkg(L"res\\menu\\about_bak.png");

	wstring menuItems[] = { L"新游戏",L"退出游戏" };
	wstring aboutMenuItems[] = { L"返回",L"退出游戏" };
	wstring setItems[] = { L" " };
	wstring chooseItems[] = { L"1 ",L"2",L"3",L"4",L"5",L"6",L"7",L"8",L"9" };
	wstring setmItems[] = { L"返回" };
	MENUITEM mItem;

	//----主页面-----------------------------
	btn_width = 260;           //菜单项图片宽
	btn_height = 120;         //菜单项图片高
	for (int i = 0; i < 2; i++)
	{
		//垂直居中布局的坐标
		/*x = (wndWidth - btn_width) / 2;
		y = i*(btn_height + MENU_SPACE) + (wnd_height - 3 * btn_height - 2 * MENU_SPACE) / 2;*/
		x = (wndWidth - btn_width) / 2;
		y = i*(btn_height + MENU_SPACE) + (wnd_height - 2 * btn_height - MENU_SPACE) / 2;

		mItem.pos.x = x + 2;      //当前菜单项x坐标
		mItem.pos.y = y + 5;       //当前菜单项y坐标
		mItem.ItemName = menuItems[i];          //当前菜单项文字
		p_menu->AddMenuItem(mItem);

		x = i*(btn_width + MENU_SPACE) + (wnd_width - 2 * btn_width - MENU_SPACE) / 2;
		y = wnd_height - 2 * btn_height + 100;
		mItem.pos.x = x;
		mItem.pos.y = y;
		mItem.ItemName = aboutMenuItems[i];
		p_aboutmenu->AddMenuItem(mItem);
	}
	setMenu(p_menu, btn_width, btn_height, L"res\\menu\\menu_b1.png", menuItems);
	//-----关于界面的菜单--------------------------
	setMenu(p_aboutmenu, btn_width, btn_height, L"res\\menu\\menu_b1.png", aboutMenuItems);
	//-----设置界面的菜单--------------------------
	//返回按键
	btn_width = 236;           //菜单项图片宽
	btn_height = 72;         //菜单项图片高
	x = 450;
	y = 480;
	mItem.pos.x = x;
	mItem.pos.y = y;
	mItem.ItemName = setmItems[0];
	p_setBack_menu->AddMenuItem(mItem);

	setMenu(p_setBack_menu, btn_width, btn_height, L"res\\menu\\button.png", setmItems);
	//音效按键
	btn_width = 200;           //菜单项图片宽
	btn_height = 100;         //菜单项图片高

	mItem.pos.x = 470;
	mItem.pos.y = 200;
	mItem.ItemName = setItems[0];
	setm_menu1.AddMenuItem(mItem);
	setMenu(&setm_menu1, btn_width, btn_height, L"res\\menu\\kai.png", setItems);

	mItem.pos.x = 470;
	mItem.pos.y = 350;
	mItem.ItemName = setItems[0];
	setm_menu2.AddMenuItem(mItem);
	setMenu(&setm_menu2, btn_width, btn_height, L"res\\menu\\kai.png", setItems);
	
	//---游戏界面的返回-------------------------
	btn_width = 66;           //菜单项图片宽
	btn_height = 58;         //菜单项图片高
							 //游戏界面的返回
	mItem.pos.x = wnd_width - btn_width * 2;
	mItem.pos.y = 0;
	mItem.ItemName = setItems[0];
	run_menu.AddMenuItem(mItem);

	setMenu(&run_menu, btn_width, btn_height, L"res\\menu\\menu_r.png", setItems);
	
	//----主菜单的关于问号--------------------------
	btn_width = 52;           //菜单项图片宽
	btn_height = 75;         //菜单项图片高
							 //关于问号
	mItem.pos.x = wnd_width - 150;
	mItem.pos.y = 0;
	mItem.ItemName = setItems[0];
	start_menu.AddMenuItem(mItem);

	setMenu(&start_menu, btn_width, btn_height, L"res\\menu\\menu_h.png", setItems);
	
	//---主菜单的设置---------------
	//设置
	mItem.pos.x = wnd_width - 100;
	mItem.pos.y = 0;
	mItem.ItemName = setItems[0];
	set_menu.AddMenuItem(mItem);
	setMenu(&set_menu, btn_width, btn_height, L"res\\menu\\menu_s.png", setItems);

	//----关卡选择的设置-------
	btn_width = 68;
	btn_height = 55;
	//选关
	int posx[] = { 58,5,210,515,185,420,660,930,900 };
	int posy[] = { 418,210,60,210,360,460,520,445,230 };
	for (int i = 0; i < 9; i++)
	{
		mItem.pos.x = posx[i];
		mItem.pos.y = posy[i];
		mItem.ItemName = chooseItems[i];
		p_screenmenu->AddMenuItem(mItem);
	}
	setMenu(p_screenmenu, btn_width, btn_height, L"res\\menu\\g.png", chooseItems);
	
	//-----关卡选择返回主菜单-------
	btn_width = 74;
	btn_height = 74;
	//返回主菜单
	mItem.pos.x = 10;
	mItem.pos.y = 0;
	mItem.ItemName = setItems[0];
	main_menu.AddMenuItem(mItem);
	setMenu(&main_menu, btn_width, btn_height, L"res\\menu\\hh.png", setItems);

	bg_buffer.Play(true);
	GameState = GAME_START;
}
void GraphTest::stopClickMusic(AudioDXBuffer button_click_buffer, AudioDXBuffer button_move_buffer)
{
	t_menu.SetClickSound(&button_click_buffer);
	start_menu.SetClickSound(&button_click_buffer);
	about_menu.SetClickSound(&button_click_buffer);
	screen_menu.SetClickSound(&button_click_buffer);
	setm_menu1.SetClickSound(&button_click_buffer);
	setm_menu2.SetClickSound(&button_click_buffer);
	setBack_menu.SetClickSound(&button_click_buffer);
	run_menu.SetClickSound(&button_click_buffer);
	main_menu.SetClickSound(&button_click_buffer);
	set_menu.SetClickSound(&button_click_buffer);

	t_menu.SetMoveSound(&button_move_buffer);
	start_menu.SetMoveSound(&button_move_buffer);
	about_menu.SetMoveSound(&button_move_buffer);
	screen_menu.SetMoveSound(&button_move_buffer);
	setm_menu1.SetMoveSound(&button_move_buffer);
	setm_menu2.SetMoveSound(&button_move_buffer);
	setBack_menu.SetMoveSound(&button_move_buffer);
	run_menu.SetMoveSound(&button_move_buffer);
	main_menu.SetMoveSound(&button_move_buffer);
	set_menu.SetMoveSound(&button_move_buffer);
}

void GraphTest::setMenu(T_Menu* menu,int w,int h,wstring path,wstring item[])
{
	Color normalClr(193, 92, 0);
	Color focusClr(213, 104, 0);
	menu->SetBtnBmp(path, w, h);
	MENU_INFO menuInfo;
	menuInfo.align = 1;							//对齐方式
	menuInfo.space = MENU_SPACE;                //菜单项之间的间隔距离
	menuInfo.width = w;                 //菜单项宽
	menuInfo.height = h;               //菜单项高
	menuInfo.fontName = L"华康少女文字W5";
	menuInfo.isBold = true;
	menuInfo.normalTextColor = normalClr;
	menuInfo.focusTextColor = focusClr;
	menu->SetMenuInfo(menuInfo);
	
	menu->SetClickSound(&button_click_buffer);
	menu->SetMoveSound(&button_move_buffer);
}

void GraphTest::LoadWaveNPC(int monster, int monstertype)
{
}

void GraphTest::LoadMap(char* path)
{
	t_scence->LoadTxtMap(path);
	scn_width = t_scence->getSceneLayers()->back().layer->GetWidth();
	scn_height = t_scence->getSceneLayers()->back().layer->GetHeight();
	// 视图初始位置以地图作为参照
	int scn_x = (wnd_width - scn_width) / 2;
	int scn_y = (wnd_height - scn_height) / 2;
	// 将游戏地图初始化为屏幕中央位置
	t_scence->InitScene(scn_x, scn_y, scn_width, scn_height, wnd_width, wnd_height);
	// 将所有地图图层定位在屏幕中央
	SCENE_LAYERS::iterator p;
	for (p = t_scence->getSceneLayers()->begin(); p != t_scence->getSceneLayers()->end(); p++)
	{
		if (p->layer->ClassName() == "T_Map") p->layer->SetPosition(scn_x, scn_y);
	}
}

void GraphTest::LoadPlayer()
{
}

void GraphTest::LoadLuo()
{
}

void GraphTest::LoadProp()
{
}

void GraphTest::LoadSkill()
{
}

void GraphTest::LoadMusic()
{
	if (!ds.CreateDS(m_hWnd)) return;
	if (flagbg) {

		runbg_buffer.LoadWave(ds, L"res\\Audio\\RunBGMusic.wav");
		bg_buffer.LoadWave(ds, L"res\\Audio\\BGMusic.wav");
	}
	else
	{
		runbg_buffer.LoadWave(ds, L"");
		bg_buffer.LoadWave(ds, L"");
	}
	if (flagbut)
	{
		button_click_buffer.LoadWave(ds, L"res\\Audio\\button_click.wav");
		button_move_buffer.LoadWave(ds, L"res\\Audio\\button_select.wav");
	}
	else
	{
		button_click_buffer.LoadWave(ds, L"");
		button_move_buffer.LoadWave(ds, L"");
	}
	
}

void GraphTest::LoadExplosion()
{
}

void GraphTest::LoadBomb()
{
}

void GraphTest::LoadImg()
{
	blood0 = new T_Graph(L"res\\property\\blood1.png");
	blood1 = new T_Graph(L"res\\property\\blood.png");
}

void GraphTest::updatePlayerLife()
{
}

void GraphTest::updateAnimation()
{
}

void GraphTest::updateNPCPos()
{
}

void GraphTest::updateBombPos()
{
}

void GraphTest::updateLuo()
{
}

void GraphTest::updatePlayerLevel()
{
}

void GraphTest::updateNPCLife()
{
}

void GraphTest::updateProLife(HDC hdc)
{
	blood1->PaintImage(hdc, px[0], py[0], blood1->GetImageWidth(), blood1->GetImageHeight(), 255);
	int x = px[0] + blood1->GetImageWidth()* (total - 10) / total;
	int sx = blood1->GetImageWidth()* (total - 10) / total;
	int rw = blood1->GetImageWidth()* 10 / total + 1;
	
	blood0->PaintRegion(blood0->GetBmpHandle(), hdc,x,py[0],sx,0,rw,blood0->GetImageHeight(),1);
}

void GraphTest::LoadGuan()
{
	t_scence = new T_Scene();
	
	px[0] = 71 * 17;
	py[0] = 71 * 6;
}

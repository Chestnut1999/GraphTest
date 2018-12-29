#pragma once
#include "T_Engine.h"
#include "T_Menu.h"
#include "T_AI.h"
#include "T_Scene.h"
#include "MyMenu.h"

typedef vector<T_Sprite*> vSpriteSet;
typedef struct
{
	LPCTSTR imgName;			// 炮塔图片
	double	Speed[3];			// 炮塔攻速
	int		Harm[3];			// 炮塔伤害值
	int		Range[3];			// 炮塔攻击范围
	int     type;				// 炮塔攻击类型
	int     PriceBuy[3];		// 炮塔买进价格
	int     PriceSell[3];		// 炮塔卖出价格
	int     Dcrease;			// 炮塔造成的减速量
	float   ratio;				// 图片缩放比率
}TOWERS;						// 炮塔信息结构体
typedef struct
{
	LPCTSTR imgName;			// 怪物图片
	int		speed;				// 怪物速度
	int		speedl;				// 减速后速度
	int     life;				// 怪物生命值 
	int		score;				// 怪物奖励金
	float   ratio;				// 图片缩放比率
}MONSTER;						// 怪物信息结构体
typedef struct
{
	LPCTSTR imgName;			// 道具图片
	int     life;				// 道具生命值 
	int		score;				// 道具奖励金
	float   ratio;				// 图片缩放比率
}PROPERTY;						// 道具信息结构体
static  bool flagbg = true;						//设置背景音乐当前播放状态
static  bool flagbut = true;                    //设置按键音当前状态
class GraphTest :public T_Engine
{
private:
	//---------场景相关变量---------
	int wnd_width, wnd_height;			//游戏窗口宽高
	int scn_width, scn_height;			//场景宽高
	POINT mouse_pt;						//当前鼠标位置

	//----------图片资源------------
	T_Graph* lifeImg;				//萝卜生命图片
	T_Graph* wavenumImg;			//菜单中总波数图片
	T_Graph* waveImg;				//菜单中当前波数图片
	T_Graph* blood1;				//满血
	T_Graph* blood0;				//空血

	//----------菜单类对象-----------
	T_Menu t_menu;                  //游戏菜单类的对象
	MyMenu start_menu;              //主菜单的关于问号
	T_Menu about_menu;              //关于界面的菜单
	T_Menu screen_menu;				//关卡选择
	MyMenu setm_menu1;				//设置界面的音效菜单
	MyMenu setm_menu2;
	T_Menu setBack_menu;            //设置界面的返回菜单
	MyMenu run_menu;                //游戏界面的返回
	MyMenu main_menu;               //关卡选择界面的返回
	MyMenu set_menu;                //主菜单的设置
									//指针
	T_Menu* p_menu;
	T_Menu* p_aboutmenu;
	T_Menu* p_screenmenu;
	T_Menu* p_setBack_menu;
	T_Menu* p_start_menu;

	//----------音乐类对象-------------
	AudioDX ds;
	AudioDXBuffer bg_buffer;				//菜单背景音乐
	AudioDXBuffer button_click_buffer;		//鼠标点击音乐
	AudioDXBuffer button_move_buffer;		//鼠标移动音乐
	AudioDXBuffer runbg_buffer;				//游戏开始音乐

	//---------游戏其他类对象---------
	T_Scene* t_scence;					//游戏场景
	T_Scene ts;

	//----------游戏角色相关集合-------------
	vSpriteSet npc_set;					//NPC角色集合
	vSpriteSet waveNPC_set;				//每一波NPC角色集合
	vSpriteSet bomb_set;				//炮弹集合
	vSpriteSet explosion_set;			//爆炸效果集合

	//----------关卡常量----------
	int guanNum = 4;					//总关卡数
	int guan = 0;						//当前关卡
	int pnum;							//道具数量
	int px[35];							//道具的x坐标
	int py[35];							//道具的y坐标
	int lifeNum = 10;					//总生命值
	int life = 10;						//当前生命值
	int	waveNum[4] = { 6,10,12,12 };	//每一关总波数
	int wave = 0;						//当前波数
	int monster = 5;					//每一关第一波初始怪物数
	int waveTime = 8000;				//每一波的间隔时间
	int NPCTime = 1000;					//加载NPC的间隔时间
	static TOWERS tInfo[6];					//炮塔信息
	static MONSTER mInfo[8];					//怪物信息
	static PROPERTY pInfo[10];					//道具信息
	wstring NPCPath[8] = {
		L"res\\monster\\smallpink.png",L"res\\monster\\smallpurple.png",L"res\\monster\\smallred.png",
		L"res\\monster\\flyyellow.png",L"res\\monster\\flyblack.png",
		L"res\\monster\\fat1.png",L"res\\monster\\fat2.png",
		L"res\\monster\\boss.png"
	};									//所有怪物的路径

	//----------资源加载-------------
	void LoadWaveNPC(int monster,int monstertype);		//加载固定个数的固定怪物
	void LoadMap(char* path);			//加载地图
	void LoadPlayer();		//加载炮塔
	void LoadLuo();			//加载萝卜
	void LoadProp();		//加载道具
	void loadMenu();		//加载菜单
	void setMenu(T_Menu* menu, int w, int h, wstring path, wstring item[]);			//菜单值的设定
	void LoadSkill();		//加载技能
	void LoadMusic();		//加载音乐
	void LoadExplosion();	//加载爆炸效果
	void LoadBomb();		//加载子弹
	void LoadImg();			//加载图片

	//---------更新---------------------
	void updatePlayerLife();	//更新萝卜生命
	void updateAnimation();		//更新炮塔帧序列
	void updateNPCPos();		//更新NPC位置
	void updateBombPos();		//更新子弹位置
	void updateLuo();			//更新萝卜状态
	void updatePlayerLevel();	//更新炮塔等级
	void updateNPCLife();		//更新每一波怪物信息
	void updateProLife(HDC hdc);		//更新道具信息
	void stopClickMusic(AudioDXBuffer button_click_buffer, AudioDXBuffer button_move_buffer);

	//----------关卡----------------
	void LoadGuan();			//初始关卡信息

	//测试
	int total = 100;
public:
	GraphTest(HINSTANCE hInstance, LPCTSTR szWindowClass, LPCTSTR szTitle,
		WORD Icon = NULL, WORD SmIcon = NULL,
		int iWidth = 800, int iHeight = 600);
	virtual ~GraphTest(void);
	void GameInit();
	void GameLogic();
	void GameEnd();
	void GamePaint(HDC hdc);
	void GameKeyAction(int ActionType = KEY_SYS_NONE);
	void GameMouseAction(int x, int y, int ActionType);
	
};
#pragma once
#include "T_Engine.h"
#include "T_Menu.h"
#include "T_AI.h"
#include "T_Scene.h"
#include "MyMenu.h"

typedef vector<T_Sprite*> vSpriteSet;
typedef struct
{
	LPCTSTR imgName;			// ����ͼƬ
	double	Speed[3];			// ��������
	int		Harm[3];			// �����˺�ֵ
	int		Range[3];			// ����������Χ
	int     type;				// ������������
	int     PriceBuy[3];		// ��������۸�
	int     PriceSell[3];		// ���������۸�
	int     Dcrease;			// ������ɵļ�����
	float   ratio;				// ͼƬ���ű���
}TOWERS;						// ������Ϣ�ṹ��
typedef struct
{
	LPCTSTR imgName;			// ����ͼƬ
	int		speed;				// �����ٶ�
	int		speedl;				// ���ٺ��ٶ�
	int     life;				// ��������ֵ 
	int		score;				// ���ｱ����
	float   ratio;				// ͼƬ���ű���
}MONSTER;						// ������Ϣ�ṹ��
typedef struct
{
	LPCTSTR imgName;			// ����ͼƬ
	int     life;				// ��������ֵ 
	int		score;				// ���߽�����
	float   ratio;				// ͼƬ���ű���
}PROPERTY;						// ������Ϣ�ṹ��
static  bool flagbg = true;						//���ñ������ֵ�ǰ����״̬
static  bool flagbut = true;                    //���ð�������ǰ״̬
class GraphTest :public T_Engine
{
private:
	//---------������ر���---------
	int wnd_width, wnd_height;			//��Ϸ���ڿ��
	int scn_width, scn_height;			//�������
	POINT mouse_pt;						//��ǰ���λ��

	//----------ͼƬ��Դ------------
	T_Graph* lifeImg;				//�ܲ�����ͼƬ
	T_Graph* wavenumImg;			//�˵����ܲ���ͼƬ
	T_Graph* waveImg;				//�˵��е�ǰ����ͼƬ
	T_Graph* blood1;				//��Ѫ
	T_Graph* blood0;				//��Ѫ

	//----------�˵������-----------
	T_Menu t_menu;                  //��Ϸ�˵���Ķ���
	MyMenu start_menu;              //���˵��Ĺ����ʺ�
	T_Menu about_menu;              //���ڽ���Ĳ˵�
	T_Menu screen_menu;				//�ؿ�ѡ��
	MyMenu setm_menu1;				//���ý������Ч�˵�
	MyMenu setm_menu2;
	T_Menu setBack_menu;            //���ý���ķ��ز˵�
	MyMenu run_menu;                //��Ϸ����ķ���
	MyMenu main_menu;               //�ؿ�ѡ�����ķ���
	MyMenu set_menu;                //���˵�������
									//ָ��
	T_Menu* p_menu;
	T_Menu* p_aboutmenu;
	T_Menu* p_screenmenu;
	T_Menu* p_setBack_menu;
	T_Menu* p_start_menu;

	//----------���������-------------
	AudioDX ds;
	AudioDXBuffer bg_buffer;				//�˵���������
	AudioDXBuffer button_click_buffer;		//���������
	AudioDXBuffer button_move_buffer;		//����ƶ�����
	AudioDXBuffer runbg_buffer;				//��Ϸ��ʼ����

	//---------��Ϸ���������---------
	T_Scene* t_scence;					//��Ϸ����
	T_Scene ts;

	//----------��Ϸ��ɫ��ؼ���-------------
	vSpriteSet npc_set;					//NPC��ɫ����
	vSpriteSet waveNPC_set;				//ÿһ��NPC��ɫ����
	vSpriteSet bomb_set;				//�ڵ�����
	vSpriteSet explosion_set;			//��ըЧ������

	//----------�ؿ�����----------
	int guanNum = 4;					//�ܹؿ���
	int guan = 0;						//��ǰ�ؿ�
	int pnum;							//��������
	int px[35];							//���ߵ�x����
	int py[35];							//���ߵ�y����
	int lifeNum = 10;					//������ֵ
	int life = 10;						//��ǰ����ֵ
	int	waveNum[4] = { 6,10,12,12 };	//ÿһ���ܲ���
	int wave = 0;						//��ǰ����
	int monster = 5;					//ÿһ�ص�һ����ʼ������
	int waveTime = 8000;				//ÿһ���ļ��ʱ��
	int NPCTime = 1000;					//����NPC�ļ��ʱ��
	static TOWERS tInfo[6];					//������Ϣ
	static MONSTER mInfo[8];					//������Ϣ
	static PROPERTY pInfo[10];					//������Ϣ
	wstring NPCPath[8] = {
		L"res\\monster\\smallpink.png",L"res\\monster\\smallpurple.png",L"res\\monster\\smallred.png",
		L"res\\monster\\flyyellow.png",L"res\\monster\\flyblack.png",
		L"res\\monster\\fat1.png",L"res\\monster\\fat2.png",
		L"res\\monster\\boss.png"
	};									//���й����·��

	//----------��Դ����-------------
	void LoadWaveNPC(int monster,int monstertype);		//���ع̶������Ĺ̶�����
	void LoadMap(char* path);			//���ص�ͼ
	void LoadPlayer();		//��������
	void LoadLuo();			//�����ܲ�
	void LoadProp();		//���ص���
	void loadMenu();		//���ز˵�
	void setMenu(T_Menu* menu, int w, int h, wstring path, wstring item[]);			//�˵�ֵ���趨
	void LoadSkill();		//���ؼ���
	void LoadMusic();		//��������
	void LoadExplosion();	//���ر�ըЧ��
	void LoadBomb();		//�����ӵ�
	void LoadImg();			//����ͼƬ

	//---------����---------------------
	void updatePlayerLife();	//�����ܲ�����
	void updateAnimation();		//��������֡����
	void updateNPCPos();		//����NPCλ��
	void updateBombPos();		//�����ӵ�λ��
	void updateLuo();			//�����ܲ�״̬
	void updatePlayerLevel();	//���������ȼ�
	void updateNPCLife();		//����ÿһ��������Ϣ
	void updateProLife(HDC hdc);		//���µ�����Ϣ
	void stopClickMusic(AudioDXBuffer button_click_buffer, AudioDXBuffer button_move_buffer);

	//----------�ؿ�----------------
	void LoadGuan();			//��ʼ�ؿ���Ϣ

	//����
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
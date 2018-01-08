﻿#include "stdafx.h"
#include <conio.h>
#include <stdlib.h> 
#include<ctime>
#include<windows.h>
#include<iostream>
#include<string>
#include<fstream>
#include <graphics.h>
#include <conio.h>
#include<tchar.h>
#include<tchar.h>
#include <mmsystem.h>
#include<easyx.h>
#include<cmath>
#pragma comment(lib,"Winmm.lib") 
#define color1 RGB(0,200, 0)
#define INTERVAL 20
#define screenWidth 1350
#define screenHeight 750
#define EXP_PER_LEVEL 1000//升一级所需经验值
#define level_MP 100
#define level_HP 200
#define level_MP_limit 50//每升一级，提高MP上限
#define level_HP_limit 100//每升一级，提高HP上限
#define level_ATK 20//每升一级，各项加的属性。
#define level_DEF 10
#define level_AGI 8
#define level_ADF 20
#define level_ATS 20
#define enemy1X 100
#define enemy1Y 100
#define enemy1D 0
#define enemy1A 0
#define UP 1
#define LEFT 2
#define DOWN 3
#define RIGHT 4
#define ESC 5
unsigned int x = 40;
unsigned int y = 440;
const unsigned int r = 40;
using namespace std;
char name_123[20] = { 0 };
char cinchar;
struct skill
{
	int HP;
	int I_HP;
	int I_MP;
	int I_ATK;
	double I_ATS;
	int I_ADF;
	int I_DEF;
	int ATK;
	int DEF;
	int ADF;

};
struct weapon
{
	int IM_ATK;//武器提升攻击力
	int IM_DEF;//防具提升防御力
	double IM_ATS;//特殊装备提升智力
	int IM_ADF;//特殊装备提升魔法防御力
	int money;
};

class character
{
private:
	string NAME;
	int ID;
	int HP;//生命值
	int ATK;//攻击力
	int DEF;//防御力
	int MP;//魔法值
	int AGI;//敏捷 
	int ADF;//魔法防御力
	double ATS;//智力
	int sk_ATK = 0;//攻击力
	int sk_DEF = 0;//防御力
	int  sk_MP = 0;//魔法值
	int sk_AGI = 0;//敏捷 
	int sk_ADF = 0;//魔法防御力
	double sk_ATS = 0.0;//智力
	int EXP;//经验
	int MONEY;
	int ratio_defence = 1;
	int ratio_equipment = 1;
	int MP_limit;
	int HP_limit;
	int level = 1;
	weapon own[3] = { 0,0,0,0,0,
		0,0,0,0,0,
		0,0,0,0,0 };
	string weapon_name[3] = { "","","" };

public:
	character(string name, int hp, int atk, int def, int mp, int agi, int adf, double ats, int exp, int money, int id, int mp_limit, int hp_limit);//初始化各项数值,构造函数.
	void und_atk(character&other);//遭遇攻击,参数是攻击方，函数调用是被攻击方。
	void und_Satk(skill o, character&other);//遭受技能攻击
	void change(skill ski);//改变属性的技能.
	void change(weapon wea, int n);//改变武器 
	void change_ratioEquipment(int n);
	void change_ratioDefence(int n);
	void change_ATK(int n);
	void change_DEF(int n);
	void change_ADF(int n);
	void change_ATS(double n);
	void change_MP(int n);
	void change_HP(int n);
	void change_sk_ATK(int n);
	void change_sk_DEF(int n);
	void change_sk_ADF(int n);
	void change_sk_ATS(double n);
	void change_sk_MP(int n);
	void change_weapon_name(string name1, int n)
	{
		*(weapon_name + n) = name1;
	}
	void change_skTo0();
	int show_sk_ATK();//攻击力
	int show_sk_DEF();//防御力
	int show_sk_MP();//魔法值
	int show_sk_AGI();//敏捷 
	int show_sk_ADF();//魔法防御力
	int show_HP();
	double show_sk_ATS();//智力
	int show_EXP();
	int show_ATK();
	weapon* show_weapon();
	int show_MP();
	int show_ADF();
	int show_AGI();
	double show_ATS();
	int show_ratioEquipment();
	int show_ratioDefence();
	string show_weapon_name_1()
	{
		return weapon_name[0];
	}
	string show_weapon_name_2()
	{
		return weapon_name[1];
	}
	string show_weapon_name_3()
	{
		return weapon_name[2];
	}
	int show_DEF();
	int show_ID();
	int show_money();
	int show_level();
	void change_level(int n);
	void change_money(int n);
	void change_EXP(int n);
	bool judge();//判断是否生还
	void change_MP_limit(int n)
	{
		MP_limit += n;
	};
	void change_HP_limit(int n)
	{
		HP_limit += n;
	};
	void change_AGI(int n)
	{
		AGI += n;
	}
};

character::character(string name, int hp, int atk, int def, int mp, int agi, int adf, double ats, int exp, int money, int id, int mp_limit, int hp_limit)
{
	ID = id;
	//NAME = name;
	HP = hp;
	ATK = atk;
	DEF = def;
	MP = mp;
	AGI = agi;
	ADF = adf;
	ATS = ats;
	EXP = exp;
	MONEY = money;
	MP_limit = mp_limit;
	HP_limit = hp_limit;
}
int character::show_HP()
{
	return HP;
}
weapon* character::show_weapon()
{
	return own;
}
void character::change(weapon wea, int n)
{
	(own + n)->IM_ADF = wea.IM_ADF;
	(own + n)->IM_ATK = wea.IM_ATK;
	(own + n)->IM_ATS = wea.IM_ATS;
	(own + n)->IM_DEF = wea.IM_DEF;
}//函数重载
void character::change_ATK(int n)
{
	ATK += n;
}
void character::change_DEF(int n)
{
	DEF += n;
}
void character::change_ADF(int n)
{
	ADF += n;
}
void character::change_ATS(double n)
{
	ATS += n;
}
void character::change_HP(int n)
{
	if (HP + n > HP_limit)
	{
		n = 0;
		HP = HP_limit;
	}
	HP += n;
}
void character::change_MP(int n)
{
	if (MP + n > MP_limit)
	{
		n = 0;
		MP = MP_limit;
	}
	MP += n;
}
void character::change_sk_ATK(int n)
{
	sk_ATK += n;
}
void character::change_sk_DEF(int n)
{
	sk_DEF += n;
}
void character::change_sk_ADF(int n)
{
	sk_ADF += n;
}
void character::change_sk_ATS(double n)
{
	sk_ATS += n;
}
void character::change_sk_MP(int n)
{
	sk_MP += n;
}
void character::change_skTo0()
{
	sk_ATK = 0;
	sk_DEF = 0;
	sk_ADF = 0;
	sk_ATS = 0;
	sk_MP = 0;

}
void character::change_EXP(int n)
{
	EXP += n;
}
int character::show_DEF()
{
	return DEF;
}
int character::show_AGI()
{
	return AGI;
}
int character::show_ADF()
{
	return ADF;
}
int character::show_MP()
{
	return MP;
}
int character::show_ATK()
{
	return ATK;
}
int character::show_sk_ATK()
{
	return sk_ATK;
}//攻击力
int character::show_sk_DEF()
{
	return sk_DEF;
}//防御力
int character::show_sk_MP()
{
	return sk_MP;
}//魔法值
int character::show_sk_AGI()//敏捷 
{
	return sk_AGI;
}
int character::show_sk_ADF()
{
	return sk_ADF;
}//魔法防御力
double character::show_sk_ATS()//智力
{
	return sk_ATS;
}
int character::show_ID()
{
	return ID;
}
double character::show_ATS()
{
	return ATS;
}
int character::show_ratioEquipment()
{
	return ratio_equipment;
}
int character::show_ratioDefence()
{
	return ratio_defence;
}
int character::show_money()
{
	return MONEY;
}
int character::show_EXP()
{
	return EXP;

}
int character::show_level()
{
	return level;
}

void character::change_ratioEquipment(int n)
{
	ratio_equipment = n;
}
void character::change_ratioDefence(int n)
{
	ratio_defence = n;
}
void character::change_level(int n)
{
	level = n;
}
void character::change_money(int n)
{
	MONEY += n;
}
void character::und_atk(character&other)
{
	if (rand() % 100>AGI)//如果随机数大于了敏捷度，攻击才会生效
	{
		weapon*temp = other.show_weapon();
		int e_atk = temp->IM_ATK + (temp + 1)->IM_ATK + (temp + 2)->IM_ATK;
		int e_DEF = temp->IM_DEF + (temp + 1)->IM_DEF + (temp + 2)->IM_DEF;
		if (((e_atk + other.show_ATK()) + (other.show_sk_ATK()) - (DEF*ratio_defence) - (e_DEF)*(ratio_equipment)-sk_DEF) > 0)//如果攻击力大于对手的防御力，攻击才会生效
		{
			HP = HP - ((e_atk + other.show_ATK()) + (other.show_sk_ATK()) - (DEF*ratio_defence) - (e_DEF)*(ratio_equipment)-sk_DEF);
			cout << "---------------------------------------------" << endl;
			cout << "攻击计算中...." << endl;
			cout << "基础攻击力" << other.show_ATK() << endl;
			cout << "武器加成" << e_atk << endl;
			cout << "技能对技能伤害加成" << other.show_sk_ATK() << endl;
			cout << "防御力" << DEF*ratio_defence << endl;
			cout << "装备防御力" << (e_DEF)*(ratio_equipment) << endl;
			cout << "技能加成防御力" << sk_DEF << endl;
			cout << endl;
			cout << endl;
			cout << "造成了" << ((e_atk + other.show_ATK()) + (other.show_sk_ATK()) - (DEF*ratio_defence) - (e_DEF)*(ratio_equipment)-sk_DEF) << "伤害" << endl;
		}
		else cout << "太过强大，无法造成伤害。" << endl;//这里有显示内容
	}
	else {
		cout << endl;

		cout << "躲开了攻击！" << endl;
		cout << endl;
	}
}
void character::und_Satk(skill o, character&other)
{
	if (other.show_MP() - o.I_MP > 0)
	{
		sk_ATK += o.ATK;
		sk_DEF += o.DEF;
		sk_ADF += o.ADF;
		other.change_HP(o.I_HP);
		other.change_MP(o.I_MP);
		other.change_sk_ATK(o.I_ATK);
		other.change_sk_ATS(o.I_ATS);
		other.change_sk_ADF(o.I_ADF);
		other.change_sk_DEF(o.I_DEF);
		weapon*temp = other.show_weapon();
		int e_ats = temp->IM_ATS + (temp + 1)->IM_ATS + (temp + 2)->IM_ATS;
		int e_adf = temp->IM_ADF + (temp + 1)->IM_ADF + (temp + 2)->IM_ADF;
		if (o.HP + other.show_ATS() + e_ats*other.show_ratioEquipment() + other.show_sk_ATS() - ADF - e_adf*ratio_equipment - sk_ADF> 0 && o.HP>0)
		{
			HP = HP - (o.HP + other.show_ATS() + e_ats*other.show_ratioEquipment() + other.show_sk_ATS() - ADF - e_adf*ratio_equipment - sk_ADF);
			cout << "---------------------------------------------" << endl;
			cout << "攻击计算中...." << endl;
			cout << "技能伤害" << o.HP << endl;
			cout << "ATS加成" << other.show_ATS() << endl;
			cout << "武器加成" << e_ats << endl;
			cout << "技能对技能伤害加成" << other.show_sk_ATS() << endl;
			cout << "防御力" << ADF << endl;
			cout << "装备防御力" << e_ats << endl;
			cout << "技能加成防御力" << e_adf << endl;
			cout << endl;
			cout << endl;
			cout << "造成了" << o.HP + other.show_ATS() + e_ats*other.show_ratioEquipment() + other.show_sk_ATS() - ADF - e_adf*ratio_equipment - sk_ADF << "伤害" << endl;
		}
		else cout << "没有造成伤害。但是影响到了对手。" << endl;
		cout << "---------------------------------------------" << endl;

	}
	else cout << "没有魔力值" << endl;
	cout << "---------------------------------------------" << endl;
}

IMAGE hero_rc;
IMAGE hero_img[10][2];
IMAGE background;
IMAGE enemy_rc;
IMAGE enemy_img[14][2];
class Hero

{
public:
	Hero();
	~Hero() {};
	void act();//改变动作
	void draw();//画出动作
	int distence();
	int distence__();
	int distence_();
	void change_position();
private:
	//bool apearance;
	const int v;//速度
	int x, y;//坐标
	IMAGE images[10][2];//图像数组实现动画
	int direction;//运动方向
	float acting_style;//实现动画滚动
}myHero;
int Hero::distence()
{
	int a = myHero.x - 200;
	int b = myHero.y - 500;
	int c = sqrt(a*a + b*b);
	int d = 0;
	if (c <= 60)
		d = 1;
	return d;
}
int Hero::distence_()
{
	int a = myHero.x - 200;
	int b = myHero.y - 400;
	int c = sqrt(a*a + b*b);
	int d = 0;
	if (c <= 60)
		d = 1;
	return d;
}
int Hero::distence__()
{
	int a = myHero.x - 300;
	int b = myHero.y - 350;
	int c = sqrt(a*a + b*b);
	int d = 0;
	if (c <= 40)
		d = 1;
	return d;
}
void Hero::change_position()
{
	myHero.x = 200;
	myHero.y = 200;
}
Hero::Hero() :v(4)
{
	x = screenWidth / 2;
	y = screenHeight / 2;
	/*HP = fullHP;
	MP = 50;
	MP_recover_gap = 0;
	attack_gap = 0;*/
	direction = 0;
	acting_style = 0;

}
class Enemy
{
private:
	int x, y;
	const int  v;
	IMAGE images[14][2];
public:
	bool direction;
	float acting_style;
	Enemy(int, int, bool, float);
	~Enemy() {}
	//void act();
	void draw();
};
Enemy::Enemy(int X, int Y, bool D, float A) :v(2)
{
	x = X; y = Y; direction = D; acting_style = A;
}
void Enemy::draw()
{
	putimage(x - 20, y - 20, &enemy_img[(int)(7 * direction + acting_style)][0], SRCAND);
	putimage(x - 20, y - 20, &enemy_img[(int)(7 * direction + acting_style)][1], SRCINVERT);
	acting_style += 0.19f;
	if (acting_style>4.8) acting_style = 0;
}
void InitImages();
struct Command
{
	int key;
	//bool onClick;
	//bool onSpace;
	//int mx, my;
}cmd;
int GetCommand()
{
	//MOUSEMSG m;
	//cmd.onSpace = false;
	cmd.key = NULL;
	//if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) { deleteAll(); exit(0); }
	if (GetAsyncKeyState('A') & 0x8000) cmd.key = LEFT;
	if (GetAsyncKeyState('W') & 0x8000) cmd.key = UP;
	if (GetAsyncKeyState('S') & 0x8000) cmd.key = DOWN;
	if (GetAsyncKeyState('D') & 0x8000) cmd.key = RIGHT;
	if (GetAsyncKeyState('P') & 0x8000)
	{
		outtextxy(100, 100, _T("Pause..."));
		system("pause");
	}
	int a = myHero.distence();
	if (GetAsyncKeyState(27) & 0x8000) { cmd.key = ESC; exit(0); }
	return a;
}
int GetCommand_()
{
	//MOUSEMSG m;
	//cmd.onSpace = false;
	cmd.key = NULL;
	//if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) { deleteAll(); exit(0); }
	if (GetAsyncKeyState('A') & 0x8000) cmd.key = LEFT;
	if (GetAsyncKeyState('W') & 0x8000) cmd.key = UP;
	if (GetAsyncKeyState('S') & 0x8000) cmd.key = DOWN;
	if (GetAsyncKeyState('D') & 0x8000) cmd.key = RIGHT;
	if (GetAsyncKeyState('P') & 0x8000)
	{
		outtextxy(100, 100, _T("Pause..."));
		system("pause");
	}
	int a = myHero.distence_();
	if (GetAsyncKeyState(27) & 0x8000) { cmd.key = ESC; exit(0); }
	return a;
}
int GetCommand__()
{
	//MOUSEMSG m;
	//cmd.onSpace = false;
	cmd.key = NULL;
	//if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) { deleteAll(); exit(0); }
	if (GetAsyncKeyState('A') & 0x8000) cmd.key = LEFT;
	if (GetAsyncKeyState('W') & 0x8000) cmd.key = UP;
	if (GetAsyncKeyState('S') & 0x8000) cmd.key = DOWN;
	if (GetAsyncKeyState('D') & 0x8000) cmd.key = RIGHT;
	if (GetAsyncKeyState('P') & 0x8000)
	{
		outtextxy(100, 100, _T("Pause..."));
		system("pause");
	}
	int a = myHero.distence__();
	if (GetAsyncKeyState(27) & 0x8000) { cmd.key = ESC; exit(0); }
	return a;
}
void Hero::act()
{
	switch (cmd.key)
	{
	case UP:
		y -= v * 1;
		if (y<10) y = 10;
		break;
	case LEFT:
		x -= v * 1;
		if (x<10) x = 10;
		direction = 1;
		break;
	case DOWN:
		y += v * 1;
		if (y>750) y = 750;
		break;
	case RIGHT:
		x += v * 1;
		if (y>1000) y = 1000;
		direction = 0;
		break;
	}
	acting_style += 0.35f;
	if (acting_style>3.6)acting_style = 0;
	//MP_recover();
}
void Hero::draw()
{
	putimage(x - 20, y - 20, &hero_img[(int)(5 * direction + acting_style)][0], SRCAND);
	putimage(x - 20, y - 20, &hero_img[(int)(5 * direction + acting_style)][1], SRCINVERT);
}
void InitImages()
{
	loadimage(&hero_rc, _T("hero.jpg"));//加载主角所有图片到hero_rc对象
	SetWorkingImage(&hero_rc);//使之变成绘图设备，才可以用getimage去获取
	for (int i = 0; i<4; i++)
	{
		getimage(&hero_img[i][1], 40 * i, 0, 40, 40);
		getimage(&hero_img[i][0], 40 * i, 40, 40, 40);
	}
	for (int i = 5; i<9; i++)
	{
		getimage(&hero_img[i][1], 40 * (i - 5), 80, 40, 40);
		getimage(&hero_img[i][0], 40 * (i - 5), 120, 40, 40);
	}
	getimage(&hero_img[4][1], 240, 160, 40, 40);
	getimage(&hero_img[4][0], 240, 200, 40, 40);
	getimage(&hero_img[9][1], 240, 240, 40, 40);
	getimage(&hero_img[9][0], 240, 280, 40, 40);
	//以上初始化主角形象，使所有动作帧都存在hero_img对象数组中
	SetWorkingImage(NULL);
	loadimage(&enemy_rc, _T("enemy.jpg"));			//以同样方式储存敌人的图片
	SetWorkingImage(&enemy_rc);
	for (int i = 0; i<5; i++)
	{
		getimage(&enemy_img[i][1], 40 * i, 0, 40, 40);
		getimage(&enemy_img[i][0], 40 * i, 40, 40, 40);
	}
	for (int i = 7; i<12; i++)
	{
		getimage(&enemy_img[i][1], 40 * (i - 7), 80, 40, 40);
		getimage(&enemy_img[i][0], 40 * (i - 7), 120, 40, 40);
	}
	getimage(&enemy_img[5][1], 280, 160, 40, 40);
	getimage(&enemy_img[5][0], 280, 200, 40, 40);
	getimage(&enemy_img[6][1], 320, 160, 40, 40);
	getimage(&enemy_img[6][0], 320, 200, 40, 40);
	getimage(&enemy_img[12][1], 280, 240, 40, 40);
	getimage(&enemy_img[12][0], 280, 280, 40, 40);
	getimage(&enemy_img[13][1], 320, 240, 40, 40);
	getimage(&enemy_img[13][0], 320, 280, 40, 40);
	//以上初始化敌人形象
	loadimage(&background, _T("back.jpg"));//将背景图片加载到backgound对象上
	SetWorkingImage(NULL);
}

bool character::judge()
{
	if (HP < 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}
character user("你", 300, 30, 30, 100, 10, 30, 40, 0, 1000, 0, 300, 400);
weapon LONGSWORD{ 10,0,0,0,300 };//长剑
weapon SILVERSWORD{ 20,0,0,0,500 };//银剑
weapon FLAMESWORD{ 30,0,0,0,1000 };///火焰剑
weapon Excalibur{ 40,0,0,0,1500 };//圣剑
weapon CHAINMAIL{ 0,0,10,10,200 };//链甲
weapon SILVERARMOR{ 0,0,20,20,500 };//银铠
weapon BATTLEARMOR{ 0,0,30,30,700 };//战神之铠
weapon MAILRING{ 0,0,user.show_DEF() ,0,1000 };//藤戒
weapon Thegodpearlofzero{ 0,0,0,0,200 }; //零之神珠（打阿尔泰尔可以使BOSS技能失效）
weapon WOODWAN{ 0,10,0,0,300 };//木杖
weapon PhilosopherStone{ 0,20,0,0,700 };//贤者之石
character Altair("Altair", 200, 80, 20, 1000, 5, 10, 40, 1500, 1500, 1, 200, 700);
character brainmother("brainmother", 380, 30, 30, 20, 10, 30, 60, 1500, 1500, 2, 200, 700);
character 	Emptystar("Emptystar", 500, 100, 30, 30, 40, 50, 70, 2000, 1500, 3, 200, 1000);
skill jili = { 0,0,-10,20,20,0,0,0,0,0 };
skill groundwall = { 0,0,-10,0,0,10,10,0,0,0 };
skill shengmingshequ = { 1.2*user.show_ATS() - 50,30,-15,0,0,0,0,0,0,0 };
skill liekongren = { 1.3*user.show_ATK(),0,-10,0,0,0,0,0,0,0 };
skill huifushu = { 0,40 + 1.5*user.show_ATS() ,-15,0,0,0,0,0,0,0 };
skill biaoxiangzhanxian = { 0,0,0,0,0,0,0,0,0,0 };//表象展观:装备无效化
skill yinguohuanyuan = { 0,0,0,0,0,0,0,0,0,0 }; //因果还原：主角防御力降至0
skill yinzimofang = { 30,0,0,15,10,15,10,-10,-10,-10 }; //因子模仿
skill yinguozhuanbian = { 0,0,0,0,0,0,0,0,0,0 };//因果转变：自己恢复全部生命值，我方生命值降至100
skill ruohua = { 0,0,-15,0,0,0,0,-10,-10,-10 };//弱化
skill danaoganyu = { 1.5*brainmother.show_ATS(),0,0,0,0,0,0,-10,-10,-10 };//大脑干预
skill naozhibodong = { 2 * brainmother.show_ATS(),0,0,0,0,0,0,0,0,0 };//脑之波动
skill qianggong = { 40,0,0,0,0,0,0,0,0,0 };//强攻
skill  wushenxuwu = { 2 * Emptystar.show_ATS(), 0,0, 0, 0, 0, 0, 0, 0, 0 };//无神虚无
skill yishijieliufang = { 70,0,0,0,0,0,0,0,0,0 };//异世界流放：一回合不能行动
skill shikongnuizhuan = { 50,200,0,0,0,0,0,0,0,0 };//时空扭转
bool jump = false;
void fight(character&I, character&it)
{
	int choice;
	if (I.show_AGI() + I.show_sk_AGI() > it.show_AGI() + it.show_sk_AGI())
	{
		if (jump)
		{
			std::cout << "&本回合你不能行动&" << endl;
			cout << "---------------------------------------------" << endl;
			jump = false;
		}
		else {
			cout << "---------------------------------------------" << endl;
			cout << endl;
			cout << ".........." << endl;
			cout << "|你的回合|." << endl;
			cout << ".........." << endl;
			cout << "1.物理攻击. 2.魔法技能" << endl;
			//这里要用户输入选项 物理攻击或技能攻击。
			char come;
			cin >> come;

			while (come != '1' && come != '2')
				cin >> come;
			if (come == '1')
			{
				it.und_atk(I);
			}
			else
			{
				if (come == '2')
				{
					cout << "请选择技能" << endl;
					cout << "1.激励.      2.地墙" << endl;
					cout << "3.生命摄取   4.裂空刃" << endl;
					cout << "5.恢复术     6.弱化" << endl;

				}
				cin >> come;
				while (come<'1' || come>'6')
				{
					cin >> come;
					//cout << "收到指令 in" << endl;
				}
				//cout << "收到指令 out" << come<<endl;
				switch (come)
				{
				case '1':
					it.und_Satk(jili, I);
					cout << "你使用了：激励" << endl;
					break;
				case '2':
					it.und_Satk(groundwall, I);
					cout << "你使用了：地墙" << endl;
					break;
				case '3':
					it.und_Satk(shengmingshequ, I);
					cout << "你使用了：生命摄取 " << endl;
					break;
				case '4':
					it.und_Satk(liekongren, I);
					cout << "你使用了：裂空刃" << endl;
					break;
				case '5':
					it.und_Satk(huifushu, I);
					cout << "你使用了：恢复术" << endl;
					break;
				case '6':
					it.und_Satk(ruohua, I);
					cout << "你使用了：弱化" << endl;
					break;
				}
			}

			cout << "敌人还剩下" << it.show_HP() << "血" << endl;
			cout << "你还剩下" << I.show_HP() << "血" << endl;
			cout << "---------------------------------------------" << endl;
		}
		cout << endl;
		cout << "............" << endl;
		cout << "|敌人的回合|" << endl;
		cout << "............" << endl;
		if (rand() % 2 == 0)
		{
			cout << "怪物冲了过来 使用了物理攻击！" << endl;
			cout << "=[]====＞" << endl;
			I.und_atk(it);
		}

		else {
			choice = (rand() % 4) + (it.show_ID() - 1) * 4;
			cout << "怪物旁边的空气流动了起来，它使用了魔法技能！！！" << endl;
			cout << "╬══→" << endl;
			switch (choice)
			{
			case 0://表象展观:装备无效化
				I.und_Satk(biaoxiangzhanxian, it);
				I.change_ratioEquipment(0);
				cout << "Altair使用了技能：表象展观。你的装备无效了" << endl;
				break;
			case 1:
				I.und_Satk(yinguozhuanbian, it);
				I.change_ratioDefence(0);
				cout << "Altair使用了技能：因果还原。你的防御力无效了" << endl;
				break;
			case 2:
				I.und_Satk(yinzimofang, it);
				cout << "Altair使用了技能：因子模仿。你遭受了严重影响" << endl;
				break;
			case 3:
				I.und_Satk(yinguozhuanbian, it);
				I.change_HP(-100);
				it.change_HP(100);
				cout << "Altair使用了技能：因果转变.阿尔泰尔吸取了你的生命值" << endl;
				break;
			case 4:
				I.und_Satk(ruohua, it);
				cout << "brainmother使用了技能：弱化" << endl;
				break;
			case 5:
				I.und_Satk(danaoganyu, it);
				cout << "brainmother使用了技能：大脑干预" << endl;
				break;


			case 6:I.und_Satk(qianggong, it);
				cout << "brainmother使用了技能：强攻" << endl;
				break;

			case 7:I.und_Satk(naozhibodong, it);
				cout << "brainmother使用了技能：脑之波动" << endl;
				break;

			case 8:I.und_Satk(qianggong, it);
				cout << "Emptystar使用了技能：炎刃冲破" << endl;
				break;

			case 9:I.und_Satk(wushenxuwu, it);
				cout << "Emptystar使用了技能：无神虚无" << endl;
				break;

			case 10:I.und_Satk(yishijieliufang, it);
				cout << "Emptystar使用了技能：异世界流放,你下一回合无法动作" << endl;
				jump = true;
				break;


			case 11:I.und_Satk(shikongnuizhuan, it);
				cout << "Emptystar使用了技能：时空扭转" << endl;
				break;

			}
		}

		cout << "敌人还剩下" << it.show_HP() << "血" << endl;
		cout << "你还剩下" << I.show_HP() << "血" << endl;
		cout << "---------------------------------------------" << endl;
	}
	else {
		cout << endl;
		cout << "............" << endl;
		cout << "|敌人的回合|" << endl;
		cout << "............" << endl;
		if (rand() % 2 == 0)

		{
			cout << "怪物冲了过来 使用了物理攻击！" << endl;
			cout << "=[]====＞" << endl;
			I.und_atk(it);
		}
		else {
			choice = (rand() % 4) + (it.show_ID() - 1) * 4;
			cout << "怪物旁边的空气流动了起来，它使用了魔法技能！！！" << endl;
			cout << "╬══→" << endl;
			switch (choice)
			{
			case 0://表象展观:装备无效化
				I.und_Satk(biaoxiangzhanxian, it);
				I.change_ratioEquipment(0);
				cout << "Altair   使用了技能：表象展观。你的装备无效了" << endl;
				break;
			case 1:
				I.und_Satk(yinguozhuanbian, it);
				I.change_ratioDefence(0);
				cout << "Altair   使用了技能：因果还原。你的防御力无效了" << endl;
				break;
			case 2:
				I.und_Satk(yinzimofang, it);
				cout << "Altair   使用了技能：因子模仿。你遭受了严重影响" << endl;
				break;
			case 3:
				I.und_Satk(yinguozhuanbian, it);
				I.change_HP(-100);
				it.change_HP(100);
				cout << "Altair使用了技能：因果转变.阿尔泰尔吸取了你的生命值" << endl;
				break;
			case 4:
				I.und_Satk(ruohua, it);
				cout << "brainmother使用了技能：弱化" << endl;
				break;
			case 5:
				I.und_Satk(danaoganyu, it);
				cout << "brainmother使用了技能：大脑干预" << endl;
				break;


			case 6:I.und_Satk(qianggong, it);
				cout << "brainmother使用了技能：强攻" << endl;
				break;

			case 7:I.und_Satk(naozhibodong, it);
				cout << "brainmother使用了技能：脑之波动" << endl;
				break;

			case 8:I.und_Satk(qianggong, it);
				cout << "Emptystar使用了技能：炎刃冲破" << endl;
				break;

			case 9:I.und_Satk(wushenxuwu, it);
				cout << "Emptystar使用了技能：无神虚无" << endl;
				break;

			case 10:I.und_Satk(yishijieliufang, it);
				cout << "Emptystar使用了技能：异世界流放,你下一回合无法动作" << endl;
				jump = true;
				break;


			case 11:I.und_Satk(shikongnuizhuan, it);
				cout << "Emptystar使用了技能：时空扭转" << endl;
				break;
			}
		}
		cout << "敌人还剩下" << it.show_HP() << "血" << endl;
		cout << "你还剩下" << I.show_HP() << "血" << endl;
		cout << "---------------------------------------------" << endl;
		if (jump)
		{
			cout << "本回合你不能行动" << endl;
			cout << "---------------------------------------------" << endl;
			jump = false;
		}

		else {
			cout << endl;
			cout << ".........." << endl;
			cout << "|你的回合|" << endl;
			cout << ".........." << endl;
			cout << "1.物理攻击. 2.魔法技能" << endl;
			//这里要用户输入选项 物理攻击或技能攻击。
			char come;
			cin >> come;
			while (come != '1' && come != '2')
				cin >> come;
			if (come == '1')
			{
				it.und_atk(I);
			}
			else
			{
				if (come == '2')
				{
					cout << "请选择技能" << endl;
					cout << "1.激励.      2.地墙" << endl;
					cout << "3.生命摄取   4.裂空刃" << endl;
					cout << "5.恢复术     6.弱化" << endl;

				}
				cin >> come;
				while (come<'1' || come>'6')
				{
					cin >> come;
					//cout << "收到指令 in" << endl;
				}
				//cout << "收到指令 out " << endl;
				switch (come)
				{
				case '1':
					it.und_Satk(jili, I);
					cout << "你使用了：激励" << endl;
					break;
				case '2':
					it.und_Satk(groundwall, I);
					cout << "你使用了：地墙" << endl;
					break;
				case '3':
					it.und_Satk(shengmingshequ, I);
					cout << "你使用了：生命摄取 " << endl;
					break;
				case '4':
					it.und_Satk(liekongren, I);
					cout << "你使用了：裂空刃" << endl;
					break;
				case '5':
					it.und_Satk(huifushu, I);
					cout << "你使用了：恢复术" << endl;
					break;
				case '6':
					it.und_Satk(ruohua, I);
					cout << "你使用了：弱化" << endl;
					break;
				}
			}
			cout << "敌人还剩下" << it.show_HP() << "血" << endl;
			cout << "你还剩下" << I.show_HP() << "血" << endl;
			cout << "---------------------------------------------" << endl;

		}
	}
}
void  promotion(character&I, int n)
{
	I.change_HP(n*level_HP);
	I.change_MP(n*level_MP);
	I.change_HP_limit(n*level_HP_limit);
	I.change_MP_limit(n*level_MP_limit);
	I.change_ADF(n*level_ADF);
	I.change_ATK(n*level_ATK);
	I.change_ATS(n*level_ATS);
	I.change_DEF(n*level_DEF);
	I.change_AGI(n*level_AGI);
}
void shop(character&I)
{
	cout << endl;
	cout << ".............." << endl;
	cout << "|欢迎来到商店|" << endl;
	cout << ".............." << endl;
	cout << endl << endl;
	cout << "---------------------------------------------" << endl;
	cout << "1 长剑" << "价格：" << LONGSWORD.money << endl;
	cout << "2 银剑" << "价格：" << SILVERSWORD.money << endl;
	cout << "3 圣剑" << "价格：" << Excalibur.money << endl;
	cout << "4 链甲" << "价格：" << CHAINMAIL.money << endl;
	cout << "5 银铠" << "价格：" << SILVERARMOR.money << endl;
	cout << "6 藤戒" << "价格：" << MAILRING.money << endl;
	cout << "7 零之神珠" << "价格：" << Thegodpearlofzero.money << endl;
	cout << "8 木杖" << "价格：" << WOODWAN.money << endl;
	cout << "9 贤者之石" << "价格：" << PhilosopherStone.money << endl;
	cout << "按N退出商店，按相应数字购买。" << endl;
	cout << "---------------------------------------------" << endl;
	char n;
	bool whatt = true;
	do {
		cin >> n;
		if (n != 'N'&&n != 'n')
		{
			switch (n)
			{
			case '1':
				if (I.show_money() >= LONGSWORD.money)
				{
					cout << "你购买了长剑" << endl;
					I.change_money(-LONGSWORD.money);
					cout << "你想装备到1 号，2号，还是3号装备仓?" << endl;
					int n;
					cin >> n;
					if ((n - 1) <= 2 && (n - 1) >= 0)
					{
						I.change(LONGSWORD, n - 1);
						I.change_weapon_name("长剑", n - 1);
						whatt = true;
					}

				}
				else {
					cout << "购买失败，金钱不足" << endl;
					whatt = false;
				}
				break;
			case '2':
				if (I.show_money() >= SILVERSWORD.money)
				{
					cout << "你购买了银剑";
					I.change_money(-SILVERSWORD.money);
					cout << "你想装备到1 号，2号，还是3号装备仓?" << endl;
					int n;
					cin >> n;
					if ((n - 1) <= 2 && (n - 1) >= 0)
					{
						I.change(SILVERSWORD, n - 1);
						I.change_weapon_name("银剑", n - 1);
						whatt = true;

					}
				}
				else {
					cout << "购买失败，金钱不足" << endl;
					whatt = false;
				}
				break;
			case '3':
				if (I.show_money() >= Excalibur.money)
				{
					cout << "你购买了圣剑";
					I.change_money(-Excalibur.money);
					cout << "你想装备到1 号，2号，还是3号装备仓?" << endl;
					int n;
					cin >> n;
					if ((n - 1) <= 2 && (n - 1) >= 0)
					{
						I.change(Excalibur, n - 1);
						I.change_weapon_name("圣剑", n - 1);
						whatt = true;

					}

				}
				else {
					cout << "购买失败，金钱不足" << endl;
					whatt = false;
				}
				break;
			case '4':
				if (I.show_money() >= CHAINMAIL.money)
				{
					cout << "你购买了链甲";
					I.change_money(-CHAINMAIL.money);
					cout << "你想装备到1 号，2号，还是3号装备仓?" << endl;
					int n;
					cin >> n;
					if ((n - 1) <= 2 && (n - 1) >= 0)
					{
						I.change(CHAINMAIL, n - 1);
						I.change_weapon_name("链甲", n - 1);
						whatt = true;

					}

				}
				else {
					cout << "购买失败，金钱不足" << endl;
					whatt = false;
				}
				break;
			case '5':
				if (I.show_money() >= SILVERARMOR.money)
				{
					cout << "你购买了银铠";
					I.change_money(-SILVERARMOR.money);
					cout << "你想装备到1 号，2号，还是3号装备仓?" << endl;
					int n;
					cin >> n;
					if ((n - 1) <= 2 && (n - 1) >= 0)
					{
						I.change(SILVERARMOR, n - 1);
						I.change_weapon_name("银铠", n - 1);
						whatt = true;

					}

				}
				else {
					cout << "购买失败，金钱不足" << endl;
					whatt = false;
				}
				break;
			case '6':
				if (I.show_money() >= MAILRING.money)
				{
					cout << "你购买了藤戒";
					I.change_money(-MAILRING.money);
					cout << "你想装备到1 号，2号，还是3号装备仓?" << endl;
					int n;
					cin >> n;
					if ((n - 1) <= 2 && (n - 1) >= 0)
					{
						I.change(MAILRING, n - 1);
						I.change_weapon_name("藤戒", n - 1);
						whatt = true;

					}

				}
				else {
					cout << "购买失败，金钱不足" << endl;
					whatt = false;
				}
				break;
			case '7':
				if (I.show_money() >= Thegodpearlofzero.money)
				{
					cout << "你购买了零之神珠";
					I.change_money(-Thegodpearlofzero.money);
					cout << "你想装备到1 号，2号，还是3号装备仓?" << endl;
					int n;
					cin >> n;
					if ((n - 1) <= 2 && (n - 1) >= 0)
					{
						I.change(Thegodpearlofzero, n - 1);
						I.change_weapon_name("零之神珠", n - 1);
						whatt = true;
					}
				}
				else {
					cout << "购买失败，金钱不足" << endl;
					whatt = false;
				}
				break;
			case '8':
				if (I.show_money() >= WOODWAN.money)
				{
					cout << "你购买了木杖";
					I.change_money(-WOODWAN.money);
					cout << "你想装备到1 号，2号，还是3号装备仓?" << endl;
					int n;
					cin >> n;
					if ((n - 1) <= 2 && (n - 1) >= 0)
					{
						I.change(WOODWAN, n - 1);
						I.change_weapon_name("木杖", n - 1);
						whatt = true;
					}

				}
				else {
					cout << "购买失败，金钱不足" << endl;
					whatt = false;
				}
				break;
			case '9':
				if (I.show_money() >= PhilosopherStone.money)
				{
					cout << "你购买了贤者之石";
					I.change_money(-PhilosopherStone.money);
					I.change_money(-WOODWAN.money);
					cout << "你想装备到1 号，2号，还是3号装备仓?" << endl;
					int n;
					cin >> n;
					if ((n - 1) <= 2 && (n - 1) >= 0)
					{
						I.change(PhilosopherStone, n - 1);
						I.change_weapon_name("贤者之石", n - 1);
						whatt = true;
					}

				}
				else {
					cout << "购买失败，金钱不足" << endl;
					whatt = false;
				}
				break;
			default:cout << "没有这个装备,你输入的信息无法被正确读取" << endl;
				whatt = false;
				break;
			}
			cout << "---------------------------------------------" << endl;

		}
		else { break; }
	} while (!whatt);
}
void account(character&I, character&it)
{
	if (!(user.judge()))
	{
		cout << "---------------------------------------------" << endl;
		cout << "你死了" << endl;
		cout << "---------------------------------------------" << endl;
	}
	else
	{
		cout << "---------------------------------------------" << endl;
		I.change_money(it.show_money());
		cout << "你获得了" << it.show_money() << "钱" << endl << "你现在有" << I.show_money() << "钱" << endl;
		I.change_EXP(it.show_EXP());
		cout << "你获得了" << it.show_EXP() << "经验" << endl;
		I.change_level((I.show_EXP() / EXP_PER_LEVEL));

		cout << "你现在的级别是:" << I.show_level() << endl;
		if (I.show_EXP() / EXP_PER_LEVEL >= 1)
		{
			promotion(I, (I.show_EXP() / EXP_PER_LEVEL));
			cout << "你升级了！" << "   " << "升了 " << I.show_EXP() / EXP_PER_LEVEL << "级" << endl;
			character user("你", 400, 40, 40, 100, 10, 40, 50, 0, 1000, 0, 300, 400);
		}
		cout << "---------------------------------------------" << endl;
		cout << "现在你可以拿获得的金币购买新的装备了！" << endl;
		shop(I);
	}
}
class hero//人物定义
{
public:
	void get_name();
	void type_slow(char contest[]);
	void gotoxy(int x, int y);//光标函数，饱含光标位置与缓冲区
	void set_color(int color);//颜色函数
	void clear_scr();//清屏函数
	char *show_name();
	//图形函数
private:
	char t_name[50];
	int t_kind;//由战斗程序来决定属性，待补充
};
hero you_;
void hero::get_name()
{
	string your_n;
	int len;
	cout << "请输入你的名字：";
	cin >> your_n;
	len = sizeof(your_n);    //计算字符串长度  
	strcpy_s(name_123, len + 1, your_n.c_str());
	//return (you_.t_name);
}
void hero::type_slow(char contest[])
{
	int i, n = 0;
	for (i = 0; i <= 199; i++)
	{
		n++;
		if (contest[i] == 0)
		{
			break;
		}
	}
	for (i = 0; i <= n + 1; i++)
	{
		//TCHAR s[] = _T("测试文字");
		//outtextxy(pst_1 + 20 * i, pst_2,contest[i]);
		cout << contest[i];
		Sleep(70);//100为恰好值,50为检测值
	}
}
void hero::gotoxy(int x, int y)
{
	CONSOLE_SCREEN_BUFFER_INFO  csbiInfo;
	HANDLE  hConsoleOut;
	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOut, &csbiInfo);
	csbiInfo.dwCursorPosition.X = x;
	csbiInfo.dwCursorPosition.Y = y;
	SetConsoleCursorPosition(hConsoleOut, csbiInfo.dwCursorPosition);
}
void hero::set_color(int color)//低四前景，高四背景
{
	HANDLE consolehwnd;//创建句柄，详细句柄知识，请百度一下或查MSDN
	consolehwnd = GetStdHandle(STD_OUTPUT_HANDLE);//实例化句柄
	SetConsoleTextAttribute(consolehwnd, color);
}
void hero::clear_scr()
{
	system("cls");
}
void the_begining(string word)
{
	srand((unsigned)time(NULL));
	int lens, random_color_1, random_color_2;
	char words[200] = { 0 };
	string first_1 = word;
	lens = sizeof(first_1);
	random_color_1 =10;
	random_color_2 =10;
	strcpy_s(words, lens + 1, first_1.c_str());
	//_tcscpy(words, lens+1, first_1.c_str());
	you_.set_color(random_color_1);
	you_.gotoxy(random_color_1, random_color_2);
	you_.type_slow(words);
	you_.clear_scr();
}
void you_name()
{
	while (1)
	{
		cin >> cinchar;
		if (cinchar == 'g')
		{
			you_.get_name();
			break;
		}
		else if (cinchar == 'q')
		{
			cout << "骚年，下次记得来挑战啊~~~";
			break;
		}
	}
}
void p_a_p_1()
{
	initgraph(1300, 750);
	IMAGE img;
	loadimage(&img, _T("tupian.jpg"));
	putimage(0, 0, 1300, 750, &img, 0, 0);

	setbkmode(TRANSPARENT);

	settextcolor(RED); //LIGHTCYAN

	settextstyle(100, 50, _T("宋体"));
	outtextxy(200, 200, _T("怪兽小游戏"));

	settextstyle(40, 20, _T("宋体"));
	settextcolor(BLACK); //LIGHTCYAN
	outtextxy(550, 600, _T("作者：李弘宇，黄昱衡，余嘉豪，方锦鑫"));

	_getch();
	closegraph();
}
int p_a_p_2()
{
	char s[17][20];
	initgraph(1300, 750);
	int hp = user.show_HP();
	int atk = user.show_ATK();
	int def = user.show_DEF();
	int mp = user.show_MP();
	int agi = user.show_AGI();
	int adf = user.show_ADF();
	int ats = user.show_ATS();
	int money___ = user.show_money();
	int experience___ = user.show_EXP();
	int level___ = user.show_level();
	int lens1, lens2, lens3;
	string weapon_1, weapon_2, weapon_3;
	weapon_1 = user.show_weapon_name_1();//"我爱你";//
	weapon_2 = user.show_weapon_name_2();//"你呢"; 
	weapon_3 = user.show_weapon_name_3();//"我也是";
	lens1 = sizeof(weapon_1);
	lens2 = sizeof(weapon_2);
	lens3 = sizeof(weapon_3);
	strcpy_s(s[10], lens1 + 1, weapon_1.c_str());
	strcpy_s(s[11], lens2 + 1, weapon_2.c_str());
	strcpy_s(s[12], lens3 + 1, weapon_3.c_str());
	sprintf_s(s[0], "%d", hp);
	sprintf_s(s[1], "%d", atk);
	sprintf_s(s[2], "%d", def);
	sprintf_s(s[3], "%d", mp);
	sprintf_s(s[4], "%d", agi);
	sprintf_s(s[5], "%d", adf);
	sprintf_s(s[6], "%d", ats);
	sprintf_s(s[7], "%d", money___);
	sprintf_s(s[8], "%d", level___);
	sprintf_s(s[9], "%d", experience___);
	TCHAR hp_[20];
	TCHAR atk_[20];
	TCHAR def_[20];
	TCHAR mp_[20];
	TCHAR agi_[20];
	TCHAR adf_[20];
	TCHAR ats_[20];
	TCHAR name_[20];
	TCHAR level__[20];
	TCHAR money__[20];
	TCHAR experience__[20];
	TCHAR weapon_1_1[20];
	TCHAR weapon_1_2[20];
	TCHAR weapon_1_3[20];
	MultiByteToWideChar(CP_ACP, 0, s[0], -1, hp_, 100);
	MultiByteToWideChar(CP_ACP, 0, s[1], -1, atk_, 100);
	MultiByteToWideChar(CP_ACP, 0, s[2], -1, def_, 100);
	MultiByteToWideChar(CP_ACP, 0, s[3], -1, mp_, 100);
	MultiByteToWideChar(CP_ACP, 0, s[4], -1, agi_, 100);
	MultiByteToWideChar(CP_ACP, 0, s[5], -1, adf_, 100);
	MultiByteToWideChar(CP_ACP, 0, s[6], -1, ats_, 100);
	MultiByteToWideChar(CP_ACP, 0, name_123, -1, name_, 100);
	MultiByteToWideChar(CP_ACP, 0, s[9], -1, experience__, 100);
	MultiByteToWideChar(CP_ACP, 0, s[8], -1, level__, 100);
	MultiByteToWideChar(CP_ACP, 0, s[7], -1, money__, 100);
	MultiByteToWideChar(CP_ACP, 0, s[10], -1, weapon_1_1, 100);
	MultiByteToWideChar(CP_ACP, 0, s[11], -1, weapon_1_2, 100);
	MultiByteToWideChar(CP_ACP, 0, s[12], -1, weapon_1_3, 100);
	IMAGE img;
	IMAGE img2;
	IMAGE img3;

	loadimage(&img, _T("tupian.jpg"));
	loadimage(&img2, _T("pa.jpg"), 1000, 750);


	//移动的函数
	Enemy enemy1(enemy1X, enemy1Y, enemy1D, enemy1A);
	InitImages();
	initgraph(screenWidth, screenHeight, NOCLOSE);			//初始化画布	
	setbkmode(TRANSPARENT);
	int a = 0;
	while (!a)
	{
		BeginBatchDraw();
		//putimage(0, 0,100,100, &background,0,0);		//重新绘制画布

		putimage(1000, 0, 1300, 750, &img, 0, 0);


		putimage(0, 0, &img2);
		//loadimage(&img3, _T("people.jpg"));
		//putimage(0, 0, 1300, 750, &img3, 0, 0);
		setbkmode(TRANSPARENT);

		settextcolor(BLACK); //LIGHTCYAN

		settextstyle(40, 20, _T("宋体"));
		outtextxy(1000, 50, _T("ID："));
		outtextxy(1150, 50, name_);
		outtextxy(1000, 100, _T("生命值："));
		outtextxy(1150, 100, hp_);
		outtextxy(1000, 150, _T("攻击力："));
		outtextxy(1150, 150, atk_);
		outtextxy(1000, 200, _T("防御力："));
		outtextxy(1150, 200, def_);
		outtextxy(1000, 250, _T("魔法值："));
		outtextxy(1150, 250, mp_);
		outtextxy(1000, 300, _T("敏捷："));
		outtextxy(1150, 300, agi_);
		outtextxy(1000, 350, _T("魔法防御力："));
		outtextxy(1230, 350, adf_);
		outtextxy(1000, 400, _T("智力："));
		outtextxy(1150, 400, ats_);
		outtextxy(1000, 450, _T("等级："));
		outtextxy(1150, 450, level__);
		outtextxy(1000, 500, _T("经验值："));
		outtextxy(1150, 500, experience__);
		outtextxy(1000, 550, _T("金钱："));
		outtextxy(1150, 550, money__);
		settextstyle(20, 10, _T("宋体"));
		outtextxy(1000, 600, _T("武器库："));
		outtextxy(1000, 625, weapon_1_1);
		outtextxy(1000, 650, weapon_1_2);
		outtextxy(1000, 675, weapon_1_3);									//loadimage(NULL, "../res/background.jpg");
																			//enemy1.draw();
		a = GetCommand();
		if (a == 1)
		{
			myHero.change_position();
		}
		myHero.act();
		myHero.draw();
		EndBatchDraw();
		Sleep(INTERVAL);
	}
	closegraph();
	return 0;
}
int p_a_p_3()
{
	char s[17][20];
	initgraph(1300, 750);
	int hp = user.show_HP();
	int atk = user.show_ATK();
	int def = user.show_DEF();
	int mp = user.show_MP();
	int agi = user.show_AGI();
	int adf = user.show_ADF();
	int ats = user.show_ATS();
	int money___ = user.show_money();
	int experience___ = user.show_EXP();
	int level___ = user.show_level();
	int lens1, lens2, lens3;
	string weapon_1, weapon_2, weapon_3;
	weapon_1 = user.show_weapon_name_1();//"我爱你";//
	weapon_2 = user.show_weapon_name_2();//"你呢"; 
	weapon_3 = user.show_weapon_name_3();//"我也是";
	lens1 = sizeof(weapon_1);
	lens2 = sizeof(weapon_2);
	lens3 = sizeof(weapon_3);
	strcpy_s(s[10], lens1 + 1, weapon_1.c_str());
	strcpy_s(s[11], lens2 + 1, weapon_2.c_str());
	strcpy_s(s[12], lens3 + 1, weapon_3.c_str());
	sprintf_s(s[0], "%d", hp);
	sprintf_s(s[1], "%d", atk);
	sprintf_s(s[2], "%d", def);
	sprintf_s(s[3], "%d", mp);
	sprintf_s(s[4], "%d", agi);
	sprintf_s(s[5], "%d", adf);
	sprintf_s(s[6], "%d", ats);
	sprintf_s(s[7], "%d", money___);
	sprintf_s(s[8], "%d", level___);
	sprintf_s(s[9], "%d", experience___);
	TCHAR hp_[20];
	TCHAR atk_[20];
	TCHAR def_[20];
	TCHAR mp_[20];
	TCHAR agi_[20];
	TCHAR adf_[20];
	TCHAR ats_[20];
	TCHAR name_[20];
	TCHAR level__[20];
	TCHAR money__[20];
	TCHAR experience__[20];
	TCHAR weapon_1_1[20];
	TCHAR weapon_1_2[20];
	TCHAR weapon_1_3[20];
	MultiByteToWideChar(CP_ACP, 0, s[0], -1, hp_, 100);
	MultiByteToWideChar(CP_ACP, 0, s[1], -1, atk_, 100);
	MultiByteToWideChar(CP_ACP, 0, s[2], -1, def_, 100);
	MultiByteToWideChar(CP_ACP, 0, s[3], -1, mp_, 100);
	MultiByteToWideChar(CP_ACP, 0, s[4], -1, agi_, 100);
	MultiByteToWideChar(CP_ACP, 0, s[5], -1, adf_, 100);
	MultiByteToWideChar(CP_ACP, 0, s[6], -1, ats_, 100);
	MultiByteToWideChar(CP_ACP, 0, name_123, -1, name_, 100);
	MultiByteToWideChar(CP_ACP, 0, s[9], -1, experience__, 100);
	MultiByteToWideChar(CP_ACP, 0, s[8], -1, level__, 100);
	MultiByteToWideChar(CP_ACP, 0, s[7], -1, money__, 100);
	MultiByteToWideChar(CP_ACP, 0, s[10], -1, weapon_1_1, 100);
	MultiByteToWideChar(CP_ACP, 0, s[11], -1, weapon_1_2, 100);
	MultiByteToWideChar(CP_ACP, 0, s[12], -1, weapon_1_3, 100);
	IMAGE img;
	IMAGE img4;
	IMAGE img3;

	loadimage(&img, _T("tupian.jpg"));
	loadimage(&img4, _T("pb.jpg"), 1000, 750);


	//移动的函数
	Enemy enemy1(enemy1X, enemy1Y, enemy1D, enemy1A);
	InitImages();
#if 0
	mciSendString(_T("backgroundmusic.mp3 "), NULL, 0, NULL); // 打开音乐
	mciSendString(_T("setaudio BackMusic volume to 300"), NULL, 0, NULL);		//设置音量大小
	mciSendString(_T("play BackMusic repeat"), NULL, 0, NULL);				//循环播放//可以加上音乐
#endif
	initgraph(screenWidth, screenHeight, NOCLOSE);			//初始化画布	
	setbkmode(TRANSPARENT);
	int a = 0;
	while (!a)
	{
		BeginBatchDraw();
		//putimage(0, 0, &background);		//重新绘制画布

		putimage(1000, 0, 1300, 750, &img, 0, 0);


		putimage(0, 0, 1000, 750, &img4, 0, 0);
		//loadimage(&img3, _T("people.jpg"));
		//putimage(0, 0, 1300, 750, &img3, 0, 0);
		setbkmode(TRANSPARENT);

		settextcolor(BLACK); //LIGHTCYAN

		settextstyle(40, 20, _T("宋体"));
		outtextxy(1000, 50, _T("ID："));
		outtextxy(1150, 50, name_);
		outtextxy(1000, 100, _T("生命值："));
		outtextxy(1150, 100, hp_);
		outtextxy(1000, 150, _T("攻击力："));
		outtextxy(1150, 150, atk_);
		outtextxy(1000, 200, _T("防御力："));
		outtextxy(1150, 200, def_);
		outtextxy(1000, 250, _T("魔法值："));
		outtextxy(1150, 250, mp_);
		outtextxy(1000, 300, _T("敏捷："));
		outtextxy(1150, 300, agi_);
		outtextxy(1000, 350, _T("魔法防御力："));
		outtextxy(1230, 350, adf_);
		outtextxy(1000, 400, _T("智力："));
		outtextxy(1150, 400, ats_);
		outtextxy(1000, 450, _T("等级："));
		outtextxy(1150, 450, level__);
		outtextxy(1000, 500, _T("经验值："));
		outtextxy(1150, 500, experience__);
		outtextxy(1000, 550, _T("金钱："));
		outtextxy(1150, 550, money__);
		settextstyle(20, 10, _T("宋体"));
		outtextxy(1000, 600, _T("武器库："));
		outtextxy(1000, 625, weapon_1_1);
		outtextxy(1000, 650, weapon_1_2);
		outtextxy(1000, 675, weapon_1_3);									//loadimage(NULL, "../res/background.jpg");
																			//enemy1.draw();
		a = GetCommand_();
		if (a == 1)
		{
			myHero.change_position();
		}
		myHero.act();
		myHero.draw();
		EndBatchDraw();
		Sleep(INTERVAL);
	}
	closegraph();
	return 0;
}
int p_a_p_4()
{
	char s[17][20];
	initgraph(1300, 750);
	int hp = user.show_HP();
	int atk = user.show_ATK();
	int def = user.show_DEF();
	int mp = user.show_MP();
	int agi = user.show_AGI();
	int adf = user.show_ADF();
	int ats = user.show_ATS();
	int money___ = user.show_money();
	int experience___ = user.show_EXP();
	int level___ = user.show_level();
	int lens1, lens2, lens3;
	string weapon_1, weapon_2, weapon_3;
	weapon_1 = user.show_weapon_name_1();//"我爱你";//
	weapon_2 = user.show_weapon_name_2();//"你呢"; 
	weapon_3 = user.show_weapon_name_3();//"我也是";
	lens1 = sizeof(weapon_1);
	lens2 = sizeof(weapon_2);
	lens3 = sizeof(weapon_3);
	strcpy_s(s[10], lens1 + 1, weapon_1.c_str());
	strcpy_s(s[11], lens2 + 1, weapon_2.c_str());
	strcpy_s(s[12], lens3 + 1, weapon_3.c_str());
	sprintf_s(s[0], "%d", hp);
	sprintf_s(s[1], "%d", atk);
	sprintf_s(s[2], "%d", def);
	sprintf_s(s[3], "%d", mp);
	sprintf_s(s[4], "%d", agi);
	sprintf_s(s[5], "%d", adf);
	sprintf_s(s[6], "%d", ats);
	sprintf_s(s[7], "%d", money___);
	sprintf_s(s[8], "%d", level___);
	sprintf_s(s[9], "%d", experience___);
	TCHAR hp_[20];
	TCHAR atk_[20];
	TCHAR def_[20];
	TCHAR mp_[20];
	TCHAR agi_[20];
	TCHAR adf_[20];
	TCHAR ats_[20];
	TCHAR name_[20];
	TCHAR level__[20];
	TCHAR money__[20];
	TCHAR experience__[20];
	TCHAR weapon_1_1[20];
	TCHAR weapon_1_2[20];
	TCHAR weapon_1_3[20];
	MultiByteToWideChar(CP_ACP, 0, s[0], -1, hp_, 100);
	MultiByteToWideChar(CP_ACP, 0, s[1], -1, atk_, 100);
	MultiByteToWideChar(CP_ACP, 0, s[2], -1, def_, 100);
	MultiByteToWideChar(CP_ACP, 0, s[3], -1, mp_, 100);
	MultiByteToWideChar(CP_ACP, 0, s[4], -1, agi_, 100);
	MultiByteToWideChar(CP_ACP, 0, s[5], -1, adf_, 100);
	MultiByteToWideChar(CP_ACP, 0, s[6], -1, ats_, 100);
	MultiByteToWideChar(CP_ACP, 0, name_123, -1, name_, 100);
	MultiByteToWideChar(CP_ACP, 0, s[9], -1, experience__, 100);
	MultiByteToWideChar(CP_ACP, 0, s[8], -1, level__, 100);
	MultiByteToWideChar(CP_ACP, 0, s[7], -1, money__, 100);
	MultiByteToWideChar(CP_ACP, 0, s[10], -1, weapon_1_1, 100);
	MultiByteToWideChar(CP_ACP, 0, s[11], -1, weapon_1_2, 100);
	MultiByteToWideChar(CP_ACP, 0, s[12], -1, weapon_1_3, 100);
	IMAGE img;
	IMAGE img2__;
	IMAGE img3;

	loadimage(&img, _T("tupian.jpg"));
	loadimage(&img2__, _T("pc.jpg"), 1000, 750);


	//移动的函数
	Enemy enemy1(enemy1X, enemy1Y, enemy1D, enemy1A);
	InitImages();
#if 0
	mciSendString(_T("backgroundmusic.mp3 "), NULL, 0, NULL); // 打开音乐
	mciSendString(_T("setaudio BackMusic volume to 300"), NULL, 0, NULL);		//设置音量大小
	mciSendString(_T("play BackMusic repeat"), NULL, 0, NULL);				//循环播放//可以加上音乐
#endif
	initgraph(screenWidth, screenHeight, NOCLOSE);			//初始化画布	
	setbkmode(TRANSPARENT);
	int a = 0;
	while (!a)
	{
		BeginBatchDraw();
		putimage(0, 0, &background);		//重新绘制画布

		putimage(1000, 0, 1300, 750, &img, 0, 0);


		putimage(0, 0, 1000, 750, &img2__, 0, 0);
		//loadimage(&img3, _T("people.jpg"));
		//putimage(0, 0, 1300, 750, &img3, 0, 0);
		setbkmode(TRANSPARENT);

		settextcolor(BLACK); //LIGHTCYAN

		settextstyle(40, 20, _T("宋体"));
		outtextxy(1000, 50, _T("ID："));
		outtextxy(1150, 50, name_);
		outtextxy(1000, 100, _T("生命值："));
		outtextxy(1150, 100, hp_);
		outtextxy(1000, 150, _T("攻击力："));
		outtextxy(1150, 150, atk_);
		outtextxy(1000, 200, _T("防御力："));
		outtextxy(1150, 200, def_);
		outtextxy(1000, 250, _T("魔法值："));
		outtextxy(1150, 250, mp_);
		outtextxy(1000, 300, _T("敏捷："));
		outtextxy(1150, 300, agi_);
		outtextxy(1000, 350, _T("魔法防御力："));
		outtextxy(1230, 350, adf_);
		outtextxy(1000, 400, _T("智力："));
		outtextxy(1150, 400, ats_);
		outtextxy(1000, 450, _T("等级："));
		outtextxy(1150, 450, level__);
		outtextxy(1000, 500, _T("经验值："));
		outtextxy(1150, 500, experience__);
		outtextxy(1000, 550, _T("金钱："));
		outtextxy(1150, 550, money__);
		settextstyle(20, 10, _T("宋体"));
		outtextxy(1000, 600, _T("武器库："));
		outtextxy(1000, 625, weapon_1_1);
		outtextxy(1000, 650, weapon_1_2);
		outtextxy(1000, 675, weapon_1_3);									//loadimage(NULL, "../res/background.jpg");
																			//enemy1.draw();
		a = GetCommand__();
		if (a == 1)
		{
			myHero.change_position();
		}
		myHero.act();
		myHero.draw();
		EndBatchDraw();
		Sleep(INTERVAL);
	}
	closegraph();
	return 0;
}
int p_a_p_5()
{
	char s[17][20];
	initgraph(1300, 750);
	int hp = user.show_HP();
	int atk = user.show_ATK();
	int def = user.show_DEF();
	int mp = user.show_MP();
	int agi = user.show_AGI();
	int adf = user.show_ADF();
	int ats = user.show_ATS();
	int money___ = user.show_money();
	int experience___ = user.show_EXP();
	int level___ = user.show_level();
	int lens1, lens2, lens3;
	string weapon_1, weapon_2, weapon_3;
	weapon_1 = user.show_weapon_name_1();//"我爱你";//
	weapon_2 = user.show_weapon_name_2();//"你呢"; 
	weapon_3 = user.show_weapon_name_3();//"我也是";
	lens1 = sizeof(weapon_1);
	lens2 = sizeof(weapon_2);
	lens3 = sizeof(weapon_3);
	strcpy_s(s[10], lens1 + 1, weapon_1.c_str());
	strcpy_s(s[11], lens2 + 1, weapon_2.c_str());
	strcpy_s(s[12], lens3 + 1, weapon_3.c_str());
	sprintf_s(s[0], "%d", hp);
	sprintf_s(s[1], "%d", atk);
	sprintf_s(s[2], "%d", def);
	sprintf_s(s[3], "%d", mp);
	sprintf_s(s[4], "%d", agi);
	sprintf_s(s[5], "%d", adf);
	sprintf_s(s[6], "%d", ats);
	sprintf_s(s[7], "%d", money___);
	sprintf_s(s[8], "%d", level___);
	sprintf_s(s[9], "%d", experience___);
	TCHAR hp_[20];
	TCHAR atk_[20];
	TCHAR def_[20];
	TCHAR mp_[20];
	TCHAR agi_[20];
	TCHAR adf_[20];
	TCHAR ats_[20];
	TCHAR name_[20];
	TCHAR level__[20];
	TCHAR money__[20];
	TCHAR experience__[20];
	TCHAR weapon_1_1[20];
	TCHAR weapon_1_2[20];
	TCHAR weapon_1_3[20];
	MultiByteToWideChar(CP_ACP, 0, s[0], -1, hp_, 100);
	MultiByteToWideChar(CP_ACP, 0, s[1], -1, atk_, 100);
	MultiByteToWideChar(CP_ACP, 0, s[2], -1, def_, 100);
	MultiByteToWideChar(CP_ACP, 0, s[3], -1, mp_, 100);
	MultiByteToWideChar(CP_ACP, 0, s[4], -1, agi_, 100);
	MultiByteToWideChar(CP_ACP, 0, s[5], -1, adf_, 100);
	MultiByteToWideChar(CP_ACP, 0, s[6], -1, ats_, 100);
	MultiByteToWideChar(CP_ACP, 0, name_123, -1, name_, 100);
	MultiByteToWideChar(CP_ACP, 0, s[9], -1, experience__, 100);
	MultiByteToWideChar(CP_ACP, 0, s[8], -1, level__, 100);
	MultiByteToWideChar(CP_ACP, 0, s[7], -1, money__, 100);
	MultiByteToWideChar(CP_ACP, 0, s[10], -1, weapon_1_1, 100);
	MultiByteToWideChar(CP_ACP, 0, s[11], -1, weapon_1_2, 100);
	MultiByteToWideChar(CP_ACP, 0, s[12], -1, weapon_1_3, 100);
	IMAGE img;
	IMAGE img2___;
	IMAGE img3;

	loadimage(&img, _T("tupian.jpg"));
	loadimage(&img2___, _T("pc.jpg"), 1000, 750);


	//移动的函数
	Enemy enemy1(enemy1X, enemy1Y, enemy1D, enemy1A);
	InitImages();
#if 0
	mciSendString(_T("backgroundmusic.mp3 "), NULL, 0, NULL); // 打开音乐
	mciSendString(_T("setaudio BackMusic volume to 300"), NULL, 0, NULL);		//设置音量大小
	mciSendString(_T("play BackMusic repeat"), NULL, 0, NULL);				//循环播放//可以加上音乐
#endif
	initgraph(screenWidth, screenHeight, NOCLOSE);			//初始化画布	
	setbkmode(TRANSPARENT);
	int a = 0;
	while (!a)
	{
		BeginBatchDraw();
		//putimage(0, 0, &background);		//重新绘制画布

		putimage(1000, 0, 1300, 750, &img, 0, 0);


		putimage(0, 0, 1000, 750, &img2___, 0, 0);
		//loadimage(&img3, _T("people.jpg"));
		//putimage(0, 0, 1300, 750, &img3, 0, 0);
		setbkmode(TRANSPARENT);

		settextcolor(BLACK); //LIGHTCYAN

		settextstyle(40, 20, _T("宋体"));
		outtextxy(1000, 50, _T("ID："));
		outtextxy(1150, 50, name_);
		outtextxy(1000, 100, _T("生命值："));
		outtextxy(1150, 100, hp_);
		outtextxy(1000, 150, _T("攻击力："));
		outtextxy(1150, 150, atk_);
		outtextxy(1000, 200, _T("防御力："));
		outtextxy(1150, 200, def_);
		outtextxy(1000, 250, _T("魔法值："));
		outtextxy(1150, 250, mp_);
		outtextxy(1000, 300, _T("敏捷："));
		outtextxy(1150, 300, agi_);
		outtextxy(1000, 350, _T("魔法防御力："));
		outtextxy(1230, 350, adf_);
		outtextxy(1000, 400, _T("智力："));
		outtextxy(1150, 400, ats_);
		outtextxy(1000, 450, _T("等级："));
		outtextxy(1150, 450, level__);
		outtextxy(1000, 500, _T("经验值："));
		outtextxy(1150, 500, experience__);
		outtextxy(1000, 550, _T("金钱："));
		outtextxy(1150, 550, money__);
		settextstyle(20, 10, _T("宋体"));
		outtextxy(1000, 600, _T("武器库："));
		outtextxy(1000, 625, weapon_1_1);
		outtextxy(1000, 650, weapon_1_2);
		outtextxy(1000, 675, weapon_1_3);									//loadimage(NULL, "../res/background.jpg");
		enemy1.draw();
		a = GetCommand();
		if (a == 1)
		{
			myHero.change_position();
		}
		myHero.act();
		myHero.draw();
		EndBatchDraw();
		Sleep(INTERVAL);
	}
	closegraph();
	return 0;
}
int fight_1_1()
{
	bool begin1 = true;
	srand((unsigned)time(NULL));
	cout << endl;
	cout << "为了击败邪恶的怪物，你可以先在商店购买足够的武器！" << endl;
	cout << "你现在有" << user.show_money() << "钱" << endl;
	shop(user);
	for (;;)
	{
		if (!(user.judge()))
		{
			cout << "你死了" << endl;
			goto theend;
		}
		else if (!(Altair.judge()))
		{
			cout << "你打死他了" << endl;
			account(user, Altair);
			break;
		}
		if (begin1)
		{
			cout << endl;
			cout << "@=[]====＞" << endl;
			cout << "你与Altair 的战斗开始了！" << endl;
			cout << "@=[]====＞" << endl;
		}
		fight(user, Altair);
		begin1 = false;

	}

	return 1;
theend:
	return 0;


}
int fight_1_2()
{
	bool begin1 = true;
	for (;;)
	{
		if (!(user.judge()))
		{
			cout << "你死了" << endl;
			goto theend;
		}
		else if (!(brainmother.judge()))
		{
			cout << "你打死他了" << endl;
			account(user, brainmother);
			break;
		}
		if (begin1)
		{
			cout << endl;
			cout << "@=[]====＞" << endl;
			cout << "你与brainmother 的战斗开始了！" << endl;
			cout << "@=[]====＞" << endl;
		}
		fight(user, brainmother);
		begin1 = false;

	}
	return 1;
theend:
	return 0;

}
int fight_1_3()
{
	bool begin1 = true;
	for (;;)
	{
		if (!(user.judge()))
		{
			cout << "你死了" << endl;
			goto theend;
		}
		else if (!(Emptystar.judge()))
		{
			cout << "你打死他了" << endl;
			account(user, Emptystar);
			break;
		}
		if (begin1)
		{
			cout << endl;
			cout << "@=[]====＞" << endl;
			cout << "你与Emptystar 的战斗开始了！" << endl;
			cout << "@=[]====＞" << endl;
		}
		fight(user, Emptystar);
		begin1 = false;

	}
	return 1;
theend:
	return 0;


}
int main()
{

	p_a_p_1();
	mciSendString(_T("open ./backgroundmusic.mp3 alias BackMusic"), NULL, 0, NULL); // 打开音乐
	mciSendString(_T("setaudio BackMusic volume to 300"), NULL, 0, NULL);		//设置音量大小
	mciSendString(_T("play BackMusic repeat"), NULL, 0, NULL);				//循环播放//可以加上音乐
	the_begining("欢迎来到这个世界");//初始化界面flagflag
	the_begining("你需要拯救被困的公主");//初始化界面flagflag
	the_begining("一共有3个BOSS等你去攻克.");//初始化界面flagflag
#if 0
	the_begining("少年，你渴望力量吗？？！！");
	the_begining("你想要拯救公主吗？？！！");
	the_begining("你想要富得流油吗？？！！");
	the_begining("你想要走向人生巅峰吗？？！！");
	the_begining("你想要拯救这个世界吗？？！！");
#endif
	cout << "按g键来开启你的传奇" << endl;
	cout << "按q键退出这个萌萌哒的小游戏" << endl;
	cout << "地图中请按 WASD 移动" << endl;
	cout << "触碰到怪物自动进入战斗" << endl;
	cout << "战斗中 双方的敏捷度决定了谁先出招，也决定了躲避物理攻击的概率" << endl;
	cout << "攻击分物理攻击和魔法攻击，相应的都有一套计算体系。" << endl;
	cout << "你可以最多携带3个装备，它们能加强你的能力" << endl;
	cout << "游戏尽量考虑到了玩家的输入情况，比如说当该输入是数字却输成字母时，系统将无视这次输入" << endl;
	you_name();
	you_.set_color(15);
	cout << 1;
	if (cinchar == 'g')
	{
		p_a_p_2();
		if (fight_1_1() != 0)
		{
			p_a_p_3();
			if (fight_1_2() != 0)
			{
				p_a_p_4();
				if (fight_1_3() != 0)
				{
					cout << "骚年，去迎接你的公主吧";
					cout << "O(∩_∩)O" << endl;
					cout << "\ (> <) /" << endl;

					//p_a_p_4();
					getchar();
				}
			}
		}
		getchar();
	}
	return 0;
}

/*
//_T("C://tupian.jpg")
rectangle(610, 550, 790, 670);
settextstyle(12, 6, _T("宋体"));
outtextxy(620, 560, _T("指点迷津:"));
outtextxy(622, 580, _T("碰到敌机障碍物会减生命值"));
outtextxy(622, 600, _T("敌机障碍物可用射击(j键)清除"));
outtextxy(622, 620, _T("下降石头只能用技能(K键)清除"));
outtextxy(622, 640, _T("得金币可以增加技能值"));
outtextxy(622, 680, _T("扫清障碍可得分"));
setbkmode(TRANSPARENT);
settextcolor(LIGHTCYAN);
settextstyle(40, 30, _T("宋体"));
outtextxy(260, 220, _T("飞机大战"));

p_a_p_1();
the_begining("欢迎来到这个世界");//初始化界面
the_begining("少年，你渴望力量吗？？！！");
the_begining("你想要拯救公主吗？？！！");
the_begining("你想要富得流油吗？？！！");
the_begining("你想要走向人生巅峰吗？？！！");
the_begining("你想要拯救这个世界吗？？！！");
the_begining("按g键来开启你的传奇");
the_begining("按q键退出这个萌萌哒的小游戏");
you_name();

char * hero::show_name()
{
return t_name;
}
//char *name = you_.show_name();*/

/*void character::change(skill ski)//改变属性的技能
{
HP+=ski.I_HP;
ATK+= ski.I_ATK+ski.ATK;
DEF+=ski.I_DEF+ski.DEF;
MP += ski.I_MP;//魔法值
ADF+= ski.I_ADF+ski.ADF;//魔法防御力
ATS+= ski.I_ATS;//智力

}

BeginBatchDraw();

setlinecolor(color1);
setfillcolor(color1);
fillcircle(x, y, r);
char input;
int i = 1;
while (i++)
{
cout << i << endl;
if (_kbhit())
{
input = _getch();
if (input == 'w')
{
if (y > r)
{
setlinecolor(BLACK);
setfillcolor(BLACK);
fillcircle(x, y, r);


y = y - 10;
setlinecolor(color1);
setfillcolor(color1);
fillcircle(x, y, r);
FlushBatchDraw();

}
}
if (input == 's')
{
if (y < screenHeight - r)
{
setlinecolor(BLACK);
setfillcolor(BLACK);
fillcircle(x, y, r);


y = y + 10;
setlinecolor(color1);
setfillcolor(color1);
fillcircle(x, y, r);
FlushBatchDraw();

}
}
if (input == 'a')
{
if (x > r)
{
setlinecolor(BLACK);
setfillcolor(BLACK);
fillcircle(x, y, r);


x = x - 10;
setlinecolor(color1);
setfillcolor(color1);
fillcircle(x, y, r);
FlushBatchDraw();

}
}
if (input == 'd')
{
if (x < screenWidth - r)
{
setlinecolor(BLACK);
setfillcolor(BLACK);
fillcircle(x, y, r);

x = x + 10;
setlinecolor(color1);
setfillcolor(color1);
fillcircle(x, y, r);
FlushBatchDraw();
}
}
if (input == 13)
break;
}
Sleep(INTERVAL);

}
EndBatchDraw();
_getch();
closegraph();*/

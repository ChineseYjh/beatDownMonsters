#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib,"Winmm.lib") 
//#pragma comment( lib, "msimg32.lib")
#include<easyx.h>
#include<conio.h>
#include<iostream>
//#include <fstream>
//#include <stdlib.h>
//#define _USER_MCI_COMMAND 
#define INTERVAL 20
#define screenWidth 640
#define screenHeight 480
using namespace std;
void InitImages();
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
	void act();//�ı䶯��
	void draw();//��������
private:
	//bool apearance;
	const int v;//�ٶ�
	int x, y;//����
	IMAGE images[10][2];//ͼ������ʵ�ֶ���
	int direction;//�˶�����
	float acting_style;//ʵ�ֶ�������
}hero;
Hero::Hero() :v(4)
{
	x = screenWidth/2;
	y = screenHeight/2;
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
	Enemy(int ,int ,bool,float);
	~Enemy() {}
	//void act();
	void draw();
};
Enemy::Enemy(int X, int Y,bool D,float A):v(2)
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
#define enemy1X 100
#define enemy1Y 100
#define enemy1D 0
#define enemy1A 0
/***********************���������Ǻ͵��������ǿ���**********************************/
struct Command
{
	int key;
	//bool onClick;
	//bool onSpace;
	//int mx, my;
}cmd;
#define UP 1
#define LEFT 2
#define DOWN 3
#define RIGHT 4
#define ESC 5
void GetCommand()
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
		outtextxy(100, 100, "Pause...");
		system("pause");
	}
	if (GetAsyncKeyState(27) & 0x8000) { cmd.key = ESC; exit(0); }
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
		if (y>470) y = 470;
		break;
	case RIGHT:
		x += v * 1;
		if (y>630) y = 630;
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
int main()
{
	Enemy enemy1(enemy1X, enemy1Y,enemy1D,enemy1A);
	InitImages();
	mciSendString("open ../res/backgroundmusic.mp3 alias BackMusic", NULL, 0, NULL); // ������
	mciSendString("setaudio BackMusic volume to 300", NULL, 0, NULL);		//����������С
	mciSendString("play BackMusic repeat", NULL, 0, NULL);				//ѭ������//���Լ�������
	initgraph(screenWidth, screenHeight, NOCLOSE);			//��ʼ������	
	setbkmode(TRANSPARENT);
	while (true)
	{
		BeginBatchDraw();
		putimage(0, 0, &background);		//���»��ƻ���
		//loadimage(NULL, "../res/background.jpg");
		enemy1.draw();
		GetCommand();
		hero.act();
		hero.draw();
		EndBatchDraw();
		Sleep(INTERVAL);
	}
	system("pause");
	closegraph();
	return 0;
}

void InitImages()
{
	loadimage(&hero_rc, "../res/hero.jpg");//������������ͼƬ��hero_rc����
	SetWorkingImage(&hero_rc);//ʹ֮��ɻ�ͼ�豸���ſ�����getimageȥ��ȡ
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
	//���ϳ�ʼ����������ʹ���ж���֡������hero_img����������
	SetWorkingImage(NULL);
	loadimage(&enemy_rc, "../res/enemy.jpg");			//��ͬ����ʽ������˵�ͼƬ
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
	//���ϳ�ʼ����������
	loadimage(&background, "../res/background.jpg");//������ͼƬ���ص�backgound������
	SetWorkingImage(NULL);
}



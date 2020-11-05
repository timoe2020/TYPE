/*
file name：main.cpp
file descriptor:a software to practice typing speed
*/


#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include <stdlib.h>//srand
#include <time.h>
#include <windows.h>  
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")

struct Letter
{
	int x;
	int y;
	//int speed;
	char ch;
	struct Letter* pnext;
};
typedef struct Letter Letter;
int speed=2;
IMAGE back, kqiu0,kqiu1;					
Letter* pLetter;
void CreateList()
{
	
	pLetter = (Letter*)malloc(sizeof(Letter));
	
	if (pLetter == NULL)
	{
		return;
	}
	pLetter->pnext = NULL;
}
void AddNode()
{
	Letter* p = pLetter;
	while (p->pnext!=NULL)
	{
		p = p->pnext;
	}
	Letter*pNew= (Letter*)malloc(sizeof(Letter));
	if (pNew == NULL)
	{
		return;
	}
	pNew->x = rand()%640;
	pNew->y = 0;
	pNew->ch = rand() % 26 + 65;
	pNew->pnext = NULL;
	p->pnext = pNew;
}
//初始化
void GameInit()
{
	
	CreateList();
	srand((unsigned int)time(NULL));
	mciSendString(L"open slow.mp3", NULL, 0, NULL);
	mciSendString(L"play slow.mp3", NULL, 0, NULL);
	initgraph(640, 480);					 //打开一个窗口！640像素宽，480像素高
	loadimage(&back, L"sky.jpg", 640, 480);	 //加载L内路径的图片保存到back变量,"./"当前项目目录,大小为640，480
	loadimage(&kqiu0, L"kqiu0.jpg", 80, 80); //在指定的窗口坐标输出图片
	loadimage(&kqiu1, L"kqiu1.jpg", 80, 80);
	putimage(0, 0, &back);
	setbkmode(TRANSPARENT);
	settextstyle(20, 0, L"楷体");
	settextcolor(BLUE);
	//putimage(320, 240, &kqiu1, SRCPAINT);				 //利用掩码图贴图
	//putimage(320, 240, &kqiu0, SRCAND);
}
//游戏绘制
void GamePaint(Letter*p)
{
	BeginBatchDraw();
	
	putimage(0, 0, &back);
	p = p->pnext;
	while (p != NULL)
	{
		putimage(p->x - 30, p->y - 20, &kqiu1, SRCPAINT);				 //利用掩码图贴图
		putimage(p->x - 30, p->y - 20, &kqiu0, SRCAND);
		outtextxy(p->x, p->y, p->ch);
		p->y += speed;
		p = p->pnext;
	}
	
	EndBatchDraw();
}
void MoveApple(Letter*p)
{
	p = p->pnext;
	while (p!=NULL)
	{
		p->y += speed;
	}
}
int main()
{
	printf("===========================使用说明===========================\n");
	printf("\n1.在键盘上选择皮卡丘身体上的字母，皮卡丘会消失\n");
//	printf("在键盘上选择图中的字母，字母消失");
	printf("\n2.默认为简单模式，如要切换到困难模式请按2\n");
	printf("\n3.切换到困难模式后，需要切回见到模式请按1\n");
	system("pause");
	DWORD	t1, t2,dt=1000;
	int speed=2;
	int key;
	GameInit();
	t1 = GetTickCount();
	while (1)
	{
		t2 = GetTickCount();
		if (t2 - t1 > dt)
		{
			AddNode();
			t1 = t2;
		}
		
		GamePaint(pLetter);
		Sleep(25);
		if (_kbhit())                    //检测按键动作有返回1，没有返回0
		{
			key = _getch();
			Letter* pre = pLetter;
			Letter* ptemp = pLetter->pnext;
			while (ptemp != NULL)
			{
				if (key == 49)				//按1速度为第一档
				{
					mciSendString(L"close quick.mp3", NULL, 0, NULL);
					mciSendString(L"open slow.mp3", NULL, 0, NULL);
					mciSendString(L"play slow.mp3", NULL, 0, NULL);
					speed = 4;
					dt = 1000;
					break;
				}
				else if (key == 50)			//按2速度为第二档
				{
					mciSendString(L"close slow.mp3", NULL, 0, NULL);
					mciSendString(L"open quick.mp3", NULL, 0, NULL);
					mciSendString(L"play quick.mp3", NULL, 0, NULL);
					speed = 12;
					dt = 500;
					break;
				}
				else if (key == ptemp->ch || key == ptemp->ch + 32)
				{
					pre->pnext = ptemp->pnext;
					free(ptemp);
					break;
				}
				else
				{
					ptemp = ptemp->pnext;
					pre = pre->pnext;
				}
			}
		}
		Letter* pdelete = pLetter->pnext;
		if (pdelete!=NULL&&pdelete->y > 480)
		{
			pLetter->pnext = pdelete->pnext;
			free(pdelete);
		}
	} 
	
	getchar();
	return 0;
}

//#include<stdio.h>
//
//
//void main()
//{
//	printf("sdfdsf");
//	getchar();
//}
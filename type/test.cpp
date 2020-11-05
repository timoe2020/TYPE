/*
file name��main.cpp
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
//��ʼ��
void GameInit()
{
	
	CreateList();
	srand((unsigned int)time(NULL));
	mciSendString(L"open slow.mp3", NULL, 0, NULL);
	mciSendString(L"play slow.mp3", NULL, 0, NULL);
	initgraph(640, 480);					 //��һ�����ڣ�640���ؿ�480���ظ�
	loadimage(&back, L"sky.jpg", 640, 480);	 //����L��·����ͼƬ���浽back����,"./"��ǰ��ĿĿ¼,��СΪ640��480
	loadimage(&kqiu0, L"kqiu0.jpg", 80, 80); //��ָ���Ĵ����������ͼƬ
	loadimage(&kqiu1, L"kqiu1.jpg", 80, 80);
	putimage(0, 0, &back);
	setbkmode(TRANSPARENT);
	settextstyle(20, 0, L"����");
	settextcolor(BLUE);
	//putimage(320, 240, &kqiu1, SRCPAINT);				 //��������ͼ��ͼ
	//putimage(320, 240, &kqiu0, SRCAND);
}
//��Ϸ����
void GamePaint(Letter*p)
{
	BeginBatchDraw();
	
	putimage(0, 0, &back);
	p = p->pnext;
	while (p != NULL)
	{
		putimage(p->x - 30, p->y - 20, &kqiu1, SRCPAINT);				 //��������ͼ��ͼ
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
	printf("===========================ʹ��˵��===========================\n");
	printf("\n1.�ڼ�����ѡ��Ƥ���������ϵ���ĸ��Ƥ�������ʧ\n");
//	printf("�ڼ�����ѡ��ͼ�е���ĸ����ĸ��ʧ");
	printf("\n2.Ĭ��Ϊ��ģʽ����Ҫ�л�������ģʽ�밴2\n");
	printf("\n3.�л�������ģʽ����Ҫ�лؼ���ģʽ�밴1\n");
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
		if (_kbhit())                    //��ⰴ�������з���1��û�з���0
		{
			key = _getch();
			Letter* pre = pLetter;
			Letter* ptemp = pLetter->pnext;
			while (ptemp != NULL)
			{
				if (key == 49)				//��1�ٶ�Ϊ��һ��
				{
					mciSendString(L"close quick.mp3", NULL, 0, NULL);
					mciSendString(L"open slow.mp3", NULL, 0, NULL);
					mciSendString(L"play slow.mp3", NULL, 0, NULL);
					speed = 4;
					dt = 1000;
					break;
				}
				else if (key == 50)			//��2�ٶ�Ϊ�ڶ���
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
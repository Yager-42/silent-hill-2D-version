#pragma once
#include"map.h"
#include"ammo.h"
#include"goobject.h"
#include"enemy.h"
#include<math.h>
#ifndef PLAYER_H
#define PLAYER_H
class  player:public goobject
{

protected:
	bool alive;
	bool LorR = 1;//1����ͼ��Ϊ�ң�0��
	int site = 4;//��Ұ��С
	int ammo_limit = 18;//�ӵ���Ŀ
public:
	ammo player_ammo;
	player();
	void setDIR(direction dir)
	{
		this->dir = dir;
	}
	void drawplayer(HDC hdc);
	void moveplayer();
	int getlie()
	{
		int temp = lie;
		return lie;
	}
	int gethang()
	{
		int temp = hang;
		return temp;
	}
	void shoot(HWND hwnd);
	void caught(enemy& temp);
	bool gameover();
	bool alive_ornot()
	{
		bool temp = alive;
		return temp;
	}
	bool under_vision(int x, int y);//x���У�y����
	void drawcloud(HDC hdc);
	void drawblank(HDC hdc);
	direction getdir()
	{
		return dir;
	}
	void reset_position();
	int show_ammoleft()
	{
		return ammo_limit;
	}
	void setammo(int number)
	{
		ammo_limit = number;
	}

};





#endif
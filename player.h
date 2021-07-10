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
	bool LorR = 1;//1人物图像为右，0左
	int site = 4;//视野大小
	int ammo_limit = 18;//子弹数目
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
	bool under_vision(int x, int y);//x是行，y是列
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
#pragma once
#include"map.h"
#include"goobject.h"
#include"enemy.h"
#ifndef AMMO_H
#define AMMO_H


class ammo:public goobject
{
	friend class player;
	friend class enemy;//友元类，方便直接访问
private:
	bool one_ = 0;//一个角色发射的子弹在地图上的只能有一颗
public:
	ammo()
	{
		hang = 40;
		lie = 40;//初始位置
	}
	ammo(int x,int y,direction dir);
	void drawammo(HDC hdc);
	void drawblank(HDC hdc);
	void moveplayer();
	void hitenemy(enemy& temp);
	void hitwall();
	bool checkone();
	int gethang()
	{
		return hang;
	}
	int getlie()
	{
		return lie;
	}
	direction getdir()
	{
		return dir;
	}
	void in_smoke(HDC hdc);


};
#endif // !AMMO_H

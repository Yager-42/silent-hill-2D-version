#pragma once
#include"map.h"
#include"goobject.h"
#include"enemy.h"
#ifndef AMMO_H
#define AMMO_H


class ammo:public goobject
{
	friend class player;
	friend class enemy;//��Ԫ�࣬����ֱ�ӷ���
private:
	bool one_ = 0;//һ����ɫ������ӵ��ڵ�ͼ�ϵ�ֻ����һ��
public:
	ammo()
	{
		hang = 40;
		lie = 40;//��ʼλ��
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

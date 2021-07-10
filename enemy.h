#pragma once
#include"goobject.h"
#include"map.h"
#include"astar.h"
#ifndef ENEMY_H
#define ENEMY_H
class enemy:public goobject
{
	friend class player;
	friend class ammo;
protected:
	bool alive ;//判断是否被子弹打死
public:
	enemy();
	void drawenemy(HDC hdc);//画敌人
	void drawblood(HDC hdc);//被打死之后在死的位置画坨血
	void getPath(int x,int y);//得到路径，即下一步往哪一个方向走，得到的是方向
	void moveplayer();//判断移动方向对应的下一个格子能不能走，不能走就反着走，反着走不行就另外两个方向走
	void setalive();//设置生命
	void drawblank(HDC hdc);//走了一步后。把原来位置上的人物图像覆盖掉，这样做是为了不用清屏函数也可以实现人物的行走，避免屏幕闪烁
	int gethang()
	{
		return hang;
	}
	int getlie()
	{
		return lie;
	}
	void in_smoke(HDC hdc);//在烟雾里，把原来位置上的人物图像用烟雾覆盖
	void reset();

};
#endif


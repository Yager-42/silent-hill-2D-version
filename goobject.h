#pragma once
#include"map.h"
#include <MMSystem.h>
#pragma comment(lib,"winmm.lib")
#ifndef  GOOBJECT_H
#define GOOBJECT_H




class goobject//就个抽象类，最大用处是让游戏里面的角色可以有同一张地图
{
protected:
	direction dir = LEFT;
	int hang = 0;
	int lie = 0;//逻辑图里的行和列
	static map map1;
public:
	goobject() {} ;
	virtual void moveplayer() = 0;

};
#endif
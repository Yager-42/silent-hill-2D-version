#pragma once
#include"map.h"
#include <MMSystem.h>
#pragma comment(lib,"winmm.lib")
#ifndef  GOOBJECT_H
#define GOOBJECT_H




class goobject//�͸������࣬����ô�������Ϸ����Ľ�ɫ������ͬһ�ŵ�ͼ
{
protected:
	direction dir = LEFT;
	int hang = 0;
	int lie = 0;//�߼�ͼ����к���
	static map map1;
public:
	goobject() {} ;
	virtual void moveplayer() = 0;

};
#endif
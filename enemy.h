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
	bool alive ;//�ж��Ƿ��ӵ�����
public:
	enemy();
	void drawenemy(HDC hdc);//������
	void drawblood(HDC hdc);//������֮��������λ�û���Ѫ
	void getPath(int x,int y);//�õ�·��������һ������һ�������ߣ��õ����Ƿ���
	void moveplayer();//�ж��ƶ������Ӧ����һ�������ܲ����ߣ������߾ͷ����ߣ������߲��о���������������
	void setalive();//��������
	void drawblank(HDC hdc);//����һ���󡣰�ԭ��λ���ϵ�����ͼ�񸲸ǵ�����������Ϊ�˲�����������Ҳ����ʵ����������ߣ�������Ļ��˸
	int gethang()
	{
		return hang;
	}
	int getlie()
	{
		return lie;
	}
	void in_smoke(HDC hdc);//���������ԭ��λ���ϵ�����ͼ����������
	void reset();

};
#endif


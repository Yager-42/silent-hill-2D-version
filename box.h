#pragma once
#include"map.h"
#include"goobject.h"
#include<time.h>
#include"player.h"
#ifndef BOX_H
#define BOX_H




class box:public goobject
{
protected:
	bool exist = 1;//判断宝藏还存不存在
public:
	box()
	{
		srand((int)time(0));
		int judge = 1;//如果遇到生成的位置是不可以生成的，那么重新生成位置
		while (judge)
		{
			int tempR = (rand()+1024) % 19;
			int tempA = (rand()+1024) % 19;
			if (map1.mapdata[tempR][tempA])
			{
				this->hang = tempR;
				this->lie = tempA;
				judge = 0;
				map1.mapdata[tempR][tempA] = 0;
			}
		}
	}
	void drawbox(HDC hdc);//画宝藏
	void moveplayer(){}//对这个类没用，只是我要继承goobject类中的静态数据成员map1
	bool found(player& temp);//判断宝藏有没有被找到
	int gethang()
	{
		return hang;
	}
	int getlie()
	{
		return lie;
	}//得到行列数值
	bool existNot();//返回存在是否
	void reset();//过了一关重新设置宝藏的值
		
};
#endif

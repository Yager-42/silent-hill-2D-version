#pragma once
#define MAPLONG 19
#define A 1
#define B 0
#include<windows.h>
#ifndef MAP_H
#define MAP_H
enum  direction
{
	UP,
	DOWN,
	RIGHT,
	LEFT
};

class map
{
	friend class player;
	friend class Astar;
	friend class enemy;
	friend class ammo;
	friend class box;//使这些类可以直接访问mapdata
protected:
	bool mapdata[MAPLONG][MAPLONG];//记录地图数据
	bool mapdata1[MAPLONG][MAPLONG] =
	{
		B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, 	//0
		B, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, B, 	//1
		B, A, A, B, A, A, B, B, B, A, B, B, B, A, A, B, A, A, B, 	//2
		B, A, B, B, A, A, A, A, A, A, A, A, A, A, A, B, B, A, B, 	//3
		B, A, B, A, A, A, B, B, B, A, B, B, B, A, A, A, B, A, B, 	//4
		B, A, B, A, A, A, A, A, A, A, A, A, A, A, A, A, B, A, B, 	//5
		B, A, A, A, A, A, B, B, A, A, A, B, B, A, A, A, A, A, B, 	//6
		B, A, B, A, A, A, A, A, A, A, A, A, A, A, A, A, B, A, B, 	//7
		B, A, B, A, A, A, A, A, B, A, B, A, A, A, A, A, B, A, B, 	//8
		B, A, A, A, A, A, A, A, B, B, B, A, A, A, A, A, A, A, B,	//9
		B, A, B, A, A, A, A, A, A, A, A, A, A, A, A, A, B, A, B, 	//10
		B, A, B, A, A, B, A, A, A, A, A, A, A, B, A, A, B, A, B, 	//11
		B, A, B, A, B, B, B, A, A, A, A, A, B, B, B, A, B, A, B, 	//12
		B, A, A, A, A, B, A, A, A, A, A, A, A, B, A, A, A, A, B, 	//13
		B, A, B, B, A, A, A, A, A, A, A, A, A, A, A, B, B, A, B, 	//14
		B, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, B,	//15
		B, A, A, A, A, B, B, B, A, B, A, B, B, B, A, A, A, A, B, 	//16
		B, A, A, A, A, B, A, A, A, A, A, A, A, B, A, A, A, A, B, 	//17
		B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, 	//18
	};
	bool mapdata2[MAPLONG][MAPLONG]=
	{
		B, B, B, B, B, B, B, B, B, B, B, B, B, A, B, B, B, B, B, //0
		B, A, A, A, A, A, A, B, A, A, B, A, A, A, B, A, B, A, B, //1
		B, A, A, A, B, A, A, B, A, A, B, A, B, A, B, A, B, A, B, //2
		B, B, B, A, B, A, A, B, B, A, B, A, B, A, B, A, B, B, B, //3
		B, A, A, A, A, A, A, A, A, A, A, A, B, B, B, A, A, A, B, //4
		B, A, A, B, A, A, A, A, A, A, A, A, A, A, A, A, A, A, B, //5
		B, A, A, B, A, A, A, B, B, B, B, B, B, A, A, B, A, A, B, //6
		B, A, A, B, A, B, A, A, A, A, A, A, A, A, A, B, A, A, B, //7
		B, A, A, B, A, B, A, A, B, A, B, A, A, B, A, B, A, A, B, //8
		B, A, A, B, A, B, A, A, B, B, B, A, A, B, A, B, A, A, B, //9
		B, A, A, B, A, B, A, A, A, A, A, A, A, B, A, A, A, A, B, //10
		B, A, A, B, A, A, A, B, B, B, B, B, A, B, A, A, A, A, B, //11
		B, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, B, //12
		B, A, A, A, B, B, B, B, B, B, B, A, A, A, A, A, A, A, B, //13
		B, A, A, A, A, A, A, A, A, A, A, A, A, B, A, A, A, A, B, //14
		B, B, A, A, B, A, A, A, A, B, B, B, A, B, A, A, A, A, B, //15
		B, A, A, A, B, B, B, A, A, A, A, B, A, B, B, B, A, A, B, //16
		B, A, A, A, A, A, A, A, A, A, A, B, A, A, A, B, A, A, B, //17
		B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, //18
	};
	bool mapdata3[MAPLONG][MAPLONG]=
	{
	B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, //0
	B, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, A, B, //1
	B, A, A, B, A, A, B, B, B, B, B, B, B, A, A, A, B, A, B, //2
	B, A, B, B, A, A, A, A, A, A, A, A, B, A, A, A, B, A, B, //3
	B, A, B, A, A, A, B, B, B, B, B, B, B, A, A, A, B, A, B, //4
	B, A, B, A, B, B, B, A, A, A, A, A, B, B, B, A, B, A, B, //5
	B, A, A, A, B, A, B, A, A, A, A, A, A, A, A, A, B, A, B, //6
	B, A, B, A, B, A, A, A, A, A, A, A, A, B, A, A, B, A, B, //7
	B, A, B, A, B, B, A, A, B, A, B, A, A, B, A, A, B, A, B, //8
	B, A, A, A, A, B, A, A, B, B, B, A, A, B, A, A, B, A, B, //9
	B, A, B, A, A, B, A, A, A, A, A, A, A, B, A, A, A, A, B, //10
	B, A, B, A, A, B, A, A, A, A, A, A, B, B, B, A, B, A, B, //11
	B, A, B, A, A, B, A, B, B, B, B, B, B, A, B, A, B, A, B, //12
	B, A, B, A, A, B, A, A, A, A, A, A, A, A, B, A, B, A, B, //13
	B, A, B, B, A, B, B, B, B, B, B, A, B, A, B, A, B, A, B, //14
	B, A, A, A, A, B, A, A, A, A, A, A, B, A, B, A, B, A, B, //15
	B, B, A, B, B, B, A, A, B, B, B, A, B, A, B, A, B, A, B, //16
	B, A, A, A, A, A, A, A, B, A, A, A, A, A, B, A, A, A, B, //17
	B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, //18

	};
	int block = 30;
	int stage;//记录当前地图
	//COLORREF wallcolor;
public:
	map()
	{
		stage = 1;
		for (int i = 0; i < MAPLONG; ++i)
		{
			for (int j = 0; j < MAPLONG; ++j)
			{
				mapdata[i][j] = mapdata1[i][j];
			}
		}
	}
	void drawmap(HDC hdc,int i,int j);
	void switchmap();//切换地图
	bool map_finish();//判断地图用完没
};





#endif
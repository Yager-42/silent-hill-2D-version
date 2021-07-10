#pragma once
#include"map.h"
#ifndef ASTAR_H
#define ASTAR_H
#include <iostream>
#include <queue>
#include <vector>
#include <stack>
#include<algorithm>
#define weightw 10
#define weightwh 14
using namespace std;



typedef struct node
{
	int x, y = 0;
	int g = 0;//起始点到当前点的代价
	int h = 0;//当前点到目标点的代价
	int f = 0;//g+h
	node* father;//父节点
	node(int x, int y)
	{
		this->x = x;
		this->y = y;
		this->father = NULL;
	}
	node(int x, int y, node* father)
	{
		this->x = x;
		this->y = y;
		this->father = father;
	}
}node;


class Astar
{
	friend class enemy;
public:
	Astar(){}
	node* search(node* starpos, node* endpos);
	void checkpoint(int x, int y, node* father, int g);
	void nextstep(node* currentpoint);
	int isContain(vector<node*>*nodelist, int x, int y);
	void calculate_ghf(node* snode, node* ebode, int g);
	bool compare(node* n1, node* n2);
	vector<node*>openlist;
	vector<node*>closelist;
	node* startpos=new node(0,0,NULL);
	node* endpos=new node(0,0,NULL);
	map map2;

};
#endif


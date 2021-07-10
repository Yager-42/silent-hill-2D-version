#include"astar.h"


void Astar::checkpoint(int x, int y, node* father, int g)//根据A*算法的规则去检查传进来的点
{
	if (x<0 || x>MAPLONG || y<0 || y>MAPLONG)
		return;//看看有没有超界
	if (!map2.mapdata[x][y] )
		return;//看看是不是墙
	if (isContain(&closelist, x, y) != -1)
		return;//看看在不在closelist里面
	int index;
	if ((index = isContain(&openlist, x, y)) != -1)
	{
		//node* point = openlist[index];
		if (openlist[index]->g > father->g + g)
		{
			openlist[index]->father = father;
			openlist[index]->g = father->g + g;
			openlist[index]->f = openlist[index]->g + openlist[index]->h;
			
		}
	}//现在的爸爸f值更小就抛弃原来的爸爸
	else
	{
		node* point = new node(x, y, father);
		calculate_ghf(point, endpos, g);
		openlist.push_back(point);
		//没在openlist里的点就塞进去
	}
}
void Astar::nextstep(node* current)
{
	{
		checkpoint(current->x - 1, current->y, current, weightw);//左
		checkpoint(current->x + 1, current->y, current, weightw);//右
		checkpoint(current->x, current->y + 1, current, weightw);//上
		checkpoint(current->x, current->y - 1, current, weightw);//下
		/*checkpoint(current->x - 1, current->y + 1, current, weightw*2);//左上
		checkpoint(current->x - 1, current->y - 1, current, weightw*2);//左下
		checkpoint(current->x + 1, current->y + 1, current, weightw*2);//右上
		checkpoint(current->x + 1, current->y - 1, current, weightw*2);//右下*/
		//这里不允许斜着走
	}
}
int Astar::isContain(vector<node*>*nodelist, int x, int y)//判断在不在相应的list里面
{
	for (int i = 0; i < (int)nodelist->size(); ++i)
	{
		if (nodelist->at(i)->x == x && nodelist->at(i)->y == y)
		{
			return i;//在list里面就返回他的索引
		}
	}
	return -1;
}
void Astar::calculate_ghf(node* snode, node* enode, int g)
{
	
	int h = abs(snode->x - enode->x) * weightw + abs(snode->y - enode->y)*weightw;//现在的点到目标点的距离
	int currentg = snode->father->g + g;//继承父亲的g再加上父亲到自己的距离
	int f = currentg + h;
	snode->f = f;
	snode->h = h;
	snode->g = currentg;
}
bool Astar::compare(node* n1, node* n2)
{
	return n1->f < n2->f;
}
node* Astar::search(node* startpos, node* endpos)
{
	if (startpos->x<0 || startpos->x>MAPLONG || startpos->y<0 || startpos->y>MAPLONG
		|| endpos->x<0 || endpos->x>MAPLONG || endpos->y<0 || endpos->y>MAPLONG)//越界判断
	{
		return startpos;//越界了就是没得走
	}
	node* current=startpos;
	this->startpos = startpos;
	this->endpos = endpos;
	openlist.push_back(startpos);//把起始点放进open list
	while (openlist.size() > 0)//open list还有点的话
	{
		current = openlist[0];//openlist的第一个是f最小的
		if (current->x == endpos->x && current->y == endpos->y)//到目标点了
		{
			
			while (current->father != NULL && current->x != startpos->x && current->y != startpos->y)
			{
				current = current->father;
			}//找爸爸，直到找到开始节点的下一个点
			return current;
			openlist.clear();
			closelist.clear();
			break;
		}
		nextstep(current);
		closelist.push_back(current);//把f最小的点塞进去
		openlist.erase(openlist.begin());//让下一个点成为第一个
		sort(openlist.begin(), openlist.end());//排下序
	}
	return current;
	//delete(current);

}
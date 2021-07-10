#include"astar.h"


void Astar::checkpoint(int x, int y, node* father, int g)//����A*�㷨�Ĺ���ȥ��鴫�����ĵ�
{
	if (x<0 || x>MAPLONG || y<0 || y>MAPLONG)
		return;//������û�г���
	if (!map2.mapdata[x][y] )
		return;//�����ǲ���ǽ
	if (isContain(&closelist, x, y) != -1)
		return;//�����ڲ���closelist����
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
	}//���ڵİְ�fֵ��С������ԭ���İְ�
	else
	{
		node* point = new node(x, y, father);
		calculate_ghf(point, endpos, g);
		openlist.push_back(point);
		//û��openlist��ĵ������ȥ
	}
}
void Astar::nextstep(node* current)
{
	{
		checkpoint(current->x - 1, current->y, current, weightw);//��
		checkpoint(current->x + 1, current->y, current, weightw);//��
		checkpoint(current->x, current->y + 1, current, weightw);//��
		checkpoint(current->x, current->y - 1, current, weightw);//��
		/*checkpoint(current->x - 1, current->y + 1, current, weightw*2);//����
		checkpoint(current->x - 1, current->y - 1, current, weightw*2);//����
		checkpoint(current->x + 1, current->y + 1, current, weightw*2);//����
		checkpoint(current->x + 1, current->y - 1, current, weightw*2);//����*/
		//���ﲻ����б����
	}
}
int Astar::isContain(vector<node*>*nodelist, int x, int y)//�ж��ڲ�����Ӧ��list����
{
	for (int i = 0; i < (int)nodelist->size(); ++i)
	{
		if (nodelist->at(i)->x == x && nodelist->at(i)->y == y)
		{
			return i;//��list����ͷ�����������
		}
	}
	return -1;
}
void Astar::calculate_ghf(node* snode, node* enode, int g)
{
	
	int h = abs(snode->x - enode->x) * weightw + abs(snode->y - enode->y)*weightw;//���ڵĵ㵽Ŀ���ľ���
	int currentg = snode->father->g + g;//�̳и��׵�g�ټ��ϸ��׵��Լ��ľ���
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
		|| endpos->x<0 || endpos->x>MAPLONG || endpos->y<0 || endpos->y>MAPLONG)//Խ���ж�
	{
		return startpos;//Խ���˾���û����
	}
	node* current=startpos;
	this->startpos = startpos;
	this->endpos = endpos;
	openlist.push_back(startpos);//����ʼ��Ž�open list
	while (openlist.size() > 0)//open list���е�Ļ�
	{
		current = openlist[0];//openlist�ĵ�һ����f��С��
		if (current->x == endpos->x && current->y == endpos->y)//��Ŀ�����
		{
			
			while (current->father != NULL && current->x != startpos->x && current->y != startpos->y)
			{
				current = current->father;
			}//�Ұְ֣�ֱ���ҵ���ʼ�ڵ����һ����
			return current;
			openlist.clear();
			closelist.clear();
			break;
		}
		nextstep(current);
		closelist.push_back(current);//��f��С�ĵ�����ȥ
		openlist.erase(openlist.begin());//����һ�����Ϊ��һ��
		sort(openlist.begin(), openlist.end());//������
	}
	return current;
	//delete(current);

}
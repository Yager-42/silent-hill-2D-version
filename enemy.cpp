#include"enemy.h"
#include<time.h>
HBITMAP enemy_blood = (HBITMAP)LoadImage(NULL, L"blood.bmp", IMAGE_BITMAP, 30, 30, LR_LOADFROMFILE);
HBITMAP enemy_blank = (HBITMAP)LoadImage(NULL, L"blank.bmp", IMAGE_BITMAP, 30, 30, LR_LOADFROMFILE);
HBITMAP enemy_cloud = (HBITMAP)LoadImage(NULL, L"cloud.bmp", IMAGE_BITMAP, 30, 30, LR_LOADFROMFILE);
enemy::enemy()
{
	alive = 1;
	srand((int)time(0));
	int judge = 1;
	int up = 100;
	while (judge)
	{
		int tempR = (rand()+up) % 18;
		int tempA = (rand()+up) % 18;
		if (map1.mapdata[tempR][tempA])
		{
			this->hang = tempR;
			this->lie = tempA;
			judge = 0;
			map1.mapdata[hang][lie] = 0;
		}
		up += 24;
	}
}
void enemy::drawblank(HDC hdc)
{
	HDC mdc = CreateCompatibleDC(hdc);
	SelectObject(mdc, enemy_blank);
	BitBlt(hdc, lie * 30, hang * 30, 30, 30, mdc, 0, 0, SRCCOPY);
	DeleteDC(mdc);
}
void enemy::drawblood(HDC hdc)
{
	HDC mdc = CreateCompatibleDC(hdc);
	SelectObject(mdc, enemy_blood);
	BitBlt(hdc, lie * 30, hang * 30, 30, 30, mdc, 0, 0, SRCCOPY);
	DeleteObject(mdc);

}
void enemy::drawenemy(HDC hdc)
{
	if (alive)
	{
		HBITMAP enemy_bit = (HBITMAP)LoadImage(NULL, L"bitman1.bmp", IMAGE_BITMAP, 30, 30, LR_LOADFROMFILE);
		HDC mdc = CreateCompatibleDC(hdc);
		SelectObject(mdc, enemy_bit);
		BitBlt(hdc, lie * 30, hang * 30, 30, 30, mdc, 0, 0, SRCCOPY);
		DeleteObject(mdc);
	}
	else
	{
		drawblood(hdc);//死了在地上画摊血
		
	}
}
void enemy::getPath(int x,int y)
{
	if (alive)
	{
		srand((int)time(0));
		if (rand() % 4 != 1)//a*算法找人
		{
			Astar temp;
			node* endnode = new node(x, y, NULL);//传进来的是玩家的当前坐标
			node* startnode = new node(this->lie, this->hang, NULL);//这个敌人当前坐标
			node* temp_ = temp.search(startnode, endnode);//根据两个点找可行路径
			//根据传回来的下一个格子位置来判断下一步的方向
			if (temp_->x == this->lie + 1 && temp_->y == this->hang)
			{
				this, dir = RIGHT;
			}
			else if (temp_->x == this->lie - 1 && temp_->y == this->hang)
			{
				this->dir = LEFT;

			}
			else if (temp_->x == this->lie && temp_->y == this->hang + 1)
			{
				this->dir = DOWN;
			}
			else if (temp_->x == this->lie && temp_->y == this->hang - 1)
			{
				this->dir = UP;
			}
		}
		//A*算法找路在距离比较远的情况下效率比较低，因为玩家的位置时刻在改变，所以在距离远的情况下通过随机方向来让敌人随机走
		else if (rand() % 4 == 1)//乱走
		{
			int num = rand() % 4;
			if (num == 0)
			{
				if (this->hang - 1 > 0 && map1.mapdata[this->hang - 1][this->lie])
				{
					this->dir = UP;
				}
				else
				{
					dir = DOWN;
				}
			}
			else if (num == 1)
			{
				if (this->hang + 1 < MAPLONG && map1.mapdata[this->hang + 1][this->lie])
				{
					dir = DOWN;
				}
				else
				{
					dir = UP;
				}
			}
			else if (num == 2)
			{
				if (this->lie - 1 > 0 && map1.mapdata[this->hang][this->lie - 1])
				{
					dir = LEFT;
				}
				else
				{
					dir = RIGHT;
				}
			}
			else if (num == 3)
			{
				if (this->lie + 1 < MAPLONG && map1.mapdata[hang][lie + 1])
				{
					dir = RIGHT;
				}
				else
				{
					dir = LEFT;
				}
			}
		}
	}
	else
	{
		return;
	}
	
}
void enemy::moveplayer()
{
	if (alive)
	{
		srand((int)time(0));
		int tempnum = rand() % 2;
		switch (dir)
		{
		case UP:
		{
			if (hang - 1 >= 0)
			{
				if (map1.mapdata[hang - 1][lie])
				{
					map1.mapdata[hang][lie] = 1;
					--hang;
					map1.mapdata[hang][lie] = 0;
				}
				else if (map1.mapdata[hang + 1][lie])
				{
					map1.mapdata[hang][lie] = 1;
					dir = DOWN;
					++hang;
					map1.mapdata[hang][lie] = 0;
				}
				else
				{
					map1.mapdata[hang][lie] = 1;
					if (tempnum == 0&&map1.mapdata[hang][lie-1]&&lie-1>0)
					{
						dir = LEFT;
						--lie;
						map1.mapdata[hang][lie] = 0;
					}
					else if(tempnum==1&&lie+1<MAPLONG&&map1.mapdata[hang][lie+1])
					{
						dir = RIGHT;
						++lie;
						map1.mapdata[hang][lie] = 0;
					}
				}
			}
			break;
		}
		case DOWN:
		{
			if (hang + 1 < MAPLONG)
			{
				if (map1.mapdata[hang + 1][lie])
				{
					map1.mapdata[hang][lie] = 1;
					++hang;
					map1.mapdata[hang][lie] = 0;
				}
				else if (map1.mapdata[hang - 1][lie])
				{
					map1.mapdata[hang][lie] = 1;
					dir = UP;
					--hang;
					map1.mapdata[hang][lie] = 0;
				}
				else 
				{
					map1.mapdata[hang][lie] = 1;
					if (tempnum == 0&&lie-1>=0&&map1.mapdata[hang][lie-1])
					{
						dir = LEFT;
						--lie;
						map1.mapdata[hang][lie] = 0;
					}
					else if(tempnum==1&&lie+1<MAPLONG&&map1.mapdata[hang][lie+1])
					{
						dir = RIGHT;
						++lie;
						map1.mapdata[hang][lie] = 0;
					}
				}
			}
			break;
		}
		case LEFT:
		{
			if (lie - 1 >= 0)
			{
				if (map1.mapdata[hang][lie - 1])
				{
					map1.mapdata[hang][lie] = 1;
					--lie;
					map1.mapdata[hang][lie] = 0;
				}
				else if (map1.mapdata[hang][lie + 1])
				{
					map1.mapdata[hang][lie] = 1;
					dir = RIGHT;
					++lie;
					map1.mapdata[hang][lie] = 0;
				}
				else
				{
					map1.mapdata[hang][lie] = 1;
					if (tempnum == 0&&hang-1>0&&map1.mapdata[hang-1][lie])
					{
						dir = UP;
						--hang;
						map1.mapdata[hang][lie] = 0;
					}
					else if(tempnum==1&&hang+1<MAPLONG&&map1.mapdata[hang+1][lie])
					{
						dir = DOWN;
						++hang;
						map1.mapdata[hang][lie] = 0;
					}
				}
			}
			break;
		}
		case RIGHT:
		{
			if (lie + 1 < MAPLONG)
			{
				if (map1.mapdata[hang][lie + 1])
				{
					map1.mapdata[hang][lie] = 1;
					++lie;
					map1.mapdata[hang][lie] = 0;
				}
				else if (map1.mapdata[hang][lie - 1])
				{
					map1.mapdata[hang][lie] = 1;
					dir = LEFT;
					--lie;
					map1.mapdata[hang][lie] = 0;
				}
				else
				{
					map1.mapdata[hang][lie] = 1;
					if (tempnum == 0&&hang-1>0&&map1.mapdata[hang-1][lie])
					{
						dir = UP;
						--hang;
						map1.mapdata[hang][lie] = 0;
					}
					else if(tempnum==1&&hang+1<MAPLONG&&map1.mapdata[hang+1][lie])
					{
						dir = DOWN;
						++hang;
						map1.mapdata[hang][lie] = 0;
					}
				}
			}
			break;
		}
		default:
			hang = hang;
			lie = lie;
			break;

		}
	}
	else
	{
	return;
 }
	

}
void enemy::setalive()
{
	alive = 0;
}
void enemy::in_smoke(HDC hdc)
{
	HDC mdc = CreateCompatibleDC(hdc);
	SelectObject(mdc, enemy_cloud);
	BitBlt(hdc, lie * 30, hang * 30, 30, 30, mdc, 0, 0, SRCCOPY);
	DeleteDC(mdc);
}
void enemy::reset()
{
	alive = 1;
	srand((int)time(0));
	int judge = 1;
	while (judge)
	{
		int tempR = rand() % 18;
		int tempA = rand() % 18;
		if (map1.mapdata[tempR][tempA])
		{
			this->hang = tempR;
			this->lie = tempA;
			judge = 0;
			map1.mapdata[hang][lie] = 0;
		}
	}
}


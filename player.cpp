#include"player.h"
#include<time.h>
HBITMAP player_blank = (HBITMAP)LoadImage(NULL, L"blank.bmp", IMAGE_BITMAP, 30, 30, LR_LOADFROMFILE);
HBITMAP player_bit = (HBITMAP)LoadImage(NULL, L"bitman.bmp", IMAGE_BITMAP, 30, 30, LR_LOADFROMFILE);
HBITMAP playerL_bit = (HBITMAP)LoadImage(NULL, L"L_bitman.bmp", IMAGE_BITMAP, 30, 30, LR_LOADFROMFILE);
HBITMAP cloud = (HBITMAP)LoadImage(NULL, L"cloud.bmp", IMAGE_BITMAP, 30, 30, LR_LOADFROMFILE);
map goobject::map1;
player::player()
{
	alive = 1;
	srand(1);
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
void player::drawplayer(HDC hdc)//根据方向来绘制
{
	HDC mdc = CreateCompatibleDC(hdc);
	if (dir == RIGHT)
	{
		SelectObject(mdc, player_bit);
		BitBlt(hdc, lie * 30, hang * 30, 30, 30, mdc, 0, 0, SRCCOPY);
		LorR = 1;
	}
	else if (dir == LEFT)
	{
		SelectObject(mdc, playerL_bit);
		BitBlt(hdc, lie * 30, hang * 30, 30, 30, mdc, 0, 0, SRCCOPY);
		LorR = 0;
	}
	else
	{
		if (LorR == 1)
		{
			SelectObject(mdc, player_bit);
			BitBlt(hdc, lie * 30, hang * 30, 30, 30, mdc, 0, 0, SRCCOPY);
		}
		else
		{
			SelectObject(mdc, playerL_bit);
			BitBlt(hdc, lie * 30, hang * 30, 30, 30, mdc, 0, 0, SRCCOPY);
		}
	}
	DeleteObject(mdc);
}
void player:: moveplayer()
{
	switch (dir)
	{
	case UP:
	{
		if (hang - 1 >= 0)//判断越界
		{
			if (map1.mapdata[hang - 1][lie])//判断能不能走
			{
				map1.mapdata[hang][lie] = 1;//把原来的位置设置为能走
				--hang;//走
				map1.mapdata[hang][lie] = 0;//走到的位置就不能走了
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
		}
		break;
	}
	default:
		hang = hang;
		lie = lie;
		break;

	}
}
void player::shoot(HWND hwnd)
{
	static int flag = 1;
	if (ammo_limit > 0)
	{
		player_ammo.one_ = 1;
		player_ammo.hang = hang;
		player_ammo.lie = lie;
		player_ammo.dir = dir;//子弹的这些数值与玩家当前数值一样
		switch (dir)
		{
		case UP:
		{
			if (player_ammo.hang - 1 > 0)//判断能不能射出去

			{
				--player_ammo.hang;
				break;
			}
		}
		case DOWN:
		{
			if (player_ammo.hang + 1 < MAPLONG)
			{
				++player_ammo.hang;
				break;
			}
		}
		case LEFT:
		{
			if (player_ammo.lie - 1 > 0)
			{
				--player_ammo.lie;
				break;
			}
		}
		case RIGHT:
		{
			if (player_ammo.lie + 1 < MAPLONG)
			{
				++player_ammo.lie;
				break;
			}
		}
		}
		--ammo_limit;
	}
	//提醒没有子弹
	if (ammo_limit == 0&&flag==1)
	{
		MessageBox(hwnd, L"哈！没子弹啦！", L"!", MB_OK | MB_ICONINFORMATION);
		flag = 0;
	}
	else if (ammo_limit == 0 && flag != 1)
	{
		MessageBox(hwnd, L"没了你按个棒槌！", L"?", MB_OK | MB_ICONINFORMATION);
	}
}
void player::caught(enemy& temp)
{
	if (temp.alive == 1)
	{
		int distance = abs(hang - temp.hang) * abs(hang - temp.hang) +
			abs(lie - temp.lie) * abs(lie - temp.lie);//距离
		if (distance <= 1)
		{
			alive = 0;//被抓住就死掉了
		}
	}
	else
	{
		if (hang == temp.hang && lie == temp.lie)//踩到血上面就死了
		{
			alive = 0;
		}
	}
}
bool player:: gameover()
{
	if (!alive)
	{
		return 1;//玩家无了游戏结束
	}
	//活着跑出去了//


	return 0;//游戏继续
}
bool player::under_vision(int x, int y)//根据玩家方向来判断视野的位置
{
	switch (dir)
	{
	case RIGHT:
	{
		if (abs(hang-x)<=1&&lie-y<=0&&lie-y>=-site)
		{
			return 1;
			break;
		}
		return 0;
		break;
	}
	case LEFT:
	{
		if (abs(hang-x)<=1&&lie-y>=0&&lie-y<=site)
		{
			return 1;
			break;
		}
		return 0;
		break;
	}
	case UP:
		if (abs(lie - y) <= 1 && x >= hang - site && x <= hang )
		{
			return 1;
			break;
		}
		return 0;
		break;
	case DOWN:
		if (abs(lie - y) <= 1 && x >= hang  && x <= hang + site)
		{
			return 1;
			break;

		}
		return 0;
		break;
	default:
		return 0;
		break;
	}
	
}
void player::drawcloud(HDC hdc)
{
	HDC mdc = CreateCompatibleDC(hdc);
	for (int i = 0; i < MAPLONG; ++i)
	{
		for (int j = 0; j < MAPLONG; ++j)
		{
			if (this->under_vision(i, j))
			{
				if (map1.mapdata[i][j])
				{
					SelectObject(mdc, player_blank);
					BitBlt(hdc, j * 30, i * 30, 30, 30, mdc, 0, 0, SRCCOPY);
				}
			}
			else
			{
				SelectObject(mdc, cloud);
				BitBlt(hdc, j * 30, i * 30, 30, 30, mdc, 0, 0, SRCCOPY);
			}
		}
	}

	DeleteObject(mdc);
}
void player::drawblank(HDC hdc)
{
	HDC mdc = CreateCompatibleDC(hdc);
	SelectObject(mdc, player_blank);
	BitBlt(hdc, lie * 30, hang * 30, 30, 30, mdc, 0, 0, SRCCOPY);
	DeleteDC(mdc);
}
void player::reset_position()
{
	alive = 1;
	srand(1);
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
	map1.switchmap();
}

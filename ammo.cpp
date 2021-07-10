#include"ammo.h"
HBITMAP ammo_left = (HBITMAP)LoadImage(NULL, L"ammo_left.bmp", IMAGE_BITMAP, 30, 30, LR_LOADFROMFILE);
HBITMAP ammo_right = (HBITMAP)LoadImage(NULL, L"ammo_right.bmp", IMAGE_BITMAP, 30, 30, LR_LOADFROMFILE);
HBITMAP ammo_up = (HBITMAP)LoadImage(NULL, L"ammo_up.bmp", IMAGE_BITMAP, 30, 30, LR_LOADFROMFILE);
HBITMAP ammo_down = (HBITMAP)LoadImage(NULL, L"ammo_down.bmp", IMAGE_BITMAP, 30, 30, LR_LOADFROMFILE);
HBITMAP ammo_blank = (HBITMAP)LoadImage(NULL, L"blank.bmp", IMAGE_BITMAP, 30, 30, LR_LOADFROMFILE);
HBITMAP ammo_cloud = (HBITMAP)LoadImage(NULL, L"cloud.bmp", IMAGE_BITMAP, 30, 30, LR_LOADFROMFILE);
//加载位图
ammo::ammo(int x, int y, direction dir)
{
	hang = x;
	lie = y;
	one_ = 0;
	this->dir = dir;
}
void ammo::moveplayer()
{

	switch (dir)
	{
		case UP:
		{
			if (hang - 1 > 0)//判断越界
			{
				if (map1.mapdata[hang - 1][lie])//判断能不能走
				{
					--hang;
					break;
				}
				break;
			}
			break;
		}
		case DOWN:
		{
			if (hang+1<MAPLONG)
			{
				if (map1.mapdata[hang + 1][lie])
				{
					++hang;
					break;
				}
				break;
			}
			break;
		}
		case LEFT:
		{
			if (lie-1>0)
			{
				if (map1.mapdata[hang][lie - 1])
				{
					--lie;
					break;
				}
				break;
			}
			break;
		}
		case RIGHT:
		{
			if (lie+1<MAPLONG)
			{
				if (map1.mapdata[hang][lie + 1])
				{
					++lie;
					break;
				}
				break;
			}
			break;
		}
	}
}
void ammo::hitwall()
{
	switch (dir)
	{
	case UP:
	{
		if (!map1.mapdata[hang - 1][lie]||!map1.mapdata[hang][lie])//判断下一步能不能走或者当前位置(防止发射子弹时子弹嵌入墙里
		{
			one_ = 0;//不能走子弹就没了
			break;
		}
		break;
	}
	case DOWN:
	{
		if (!map1.mapdata[hang + 1][lie] || !map1.mapdata[hang][lie])
		{
			one_ = 0;
			break;
		}
		break;
	}
	case LEFT:
	{
		if (!map1.mapdata[hang][lie - 1] || !map1.mapdata[hang][lie])
		{
			one_ = 0;
			break;
		}
		break;
	}
	case RIGHT:
	{
		if (!map1.mapdata[hang][lie + 1] || !map1.mapdata[hang][lie])
		{
			one_ = 0;
			break;
		}
		break;
	}
	}
}
void ammo::hitenemy(enemy& temp)
{
	
	switch (dir)
	{
	case UP:
		if (hang - 1 == temp.hang && lie == temp.lie)//判断有没有打中
		{
			temp.setalive();//打中敌人就死了
			one_ = 0;//子弹也没了
			map1.mapdata[temp.hang][temp.lie] = 1;//这里能走也不能走(游戏设计成血迹是不能走的，当他有毒，可以作为一个静止的杀不死的敌人，拿来堵路
		}
		break;
	case DOWN:
		if (hang + 1 == temp.hang && lie == temp.lie)
		{
			temp.setalive();
			one_ = 0;
			map1.mapdata[temp.hang][temp.lie] = 1;
		}
		break;
	case LEFT:
		if (hang == temp.hang && lie - 1 == temp.lie)
		{
			temp.setalive();
			one_ = 0;
			map1.mapdata[temp.hang][temp.lie] = 1;

		}
		break;
	case RIGHT:
		if (hang == temp.hang && lie + 1 == temp.lie)
		{
			temp.setalive();
			one_ = 0;
			map1.mapdata[temp.hang][temp.lie]=1;

		}
		break;
	}
}
void ammo::drawammo(HDC hdc)//根据方向的不同来选取不同的图片
{
	HDC mdc = CreateCompatibleDC(hdc);
	switch (dir)
	{
	case UP:
	{
		SelectObject(mdc, ammo_up);
		BitBlt(hdc, lie * 30, hang * 30, 30, 30, mdc, 0, 0, SRCCOPY);
		DeleteObject(mdc);
		break;
	}
	case DOWN:
	{
		SelectObject(mdc, ammo_down);
		BitBlt(hdc, lie * 30, hang * 30, 30, 30, mdc, 0, 0, SRCCOPY);
		DeleteObject(mdc);
		break;
	}
	case LEFT:
	{
		SelectObject(mdc, ammo_left);
		BitBlt(hdc, lie * 30, hang * 30, 30, 30, mdc, 0, 0, SRCCOPY);
		DeleteObject(mdc);
		break;
	}
	case RIGHT:
	{
		SelectObject(mdc, ammo_right);
		BitBlt(hdc, lie * 30, hang * 30, 30, 30, mdc, 0, 0, SRCCOPY);
		DeleteObject(mdc);
		break;
	}
	}
	DeleteObject(mdc);
}
bool ammo::checkone()//判断子弹还有没有
{
	bool temp = one_;
	return temp;
}
void ammo::drawblank(HDC hdc)
{
	if (map1.mapdata[hang][lie])
	{
		HDC mdc = CreateCompatibleDC(hdc);
		SelectObject(mdc, ammo_blank);
		BitBlt(hdc, lie * 30, hang * 30, 30, 30, mdc, 0, 0, SRCCOPY);
		DeleteObject(mdc);
	}

}
void ammo::in_smoke(HDC hdc)
{
	HDC mdc = CreateCompatibleDC(hdc);
	SelectObject(mdc, ammo_cloud);
	BitBlt(hdc, lie * 30, hang * 30, 30, 30, mdc, 0, 0, SRCCOPY);
	DeleteDC(mdc);
}

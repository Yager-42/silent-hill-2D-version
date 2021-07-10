#include"box.h"

HBITMAP bitbox = (HBITMAP)LoadImage(NULL, L"box.bmp", IMAGE_BITMAP, 30, 30, LR_LOADFROMFILE);


void box::drawbox(HDC hdc)
{
	HDC mdc = CreateCompatibleDC(hdc);
	SelectObject(mdc, bitbox);
	BitBlt(hdc, lie * 30, hang * 30, 30, 30, mdc, 0, 0, SRCCOPY);
	DeleteDC(mdc);
}
bool box::found(player& temp)//根据玩家方向来判断相应的条件
{
	switch (temp.getdir())
	{
	case LEFT:
	{
		if (lie + 1 == temp.getlie() && hang == temp.gethang())
		{
			exist = 0;
			return 1;
			break;
		}
		break;
	}
	case RIGHT:
	{
		if (lie - 1 == temp.getlie() && hang == temp.gethang())
		{
			exist = 0;
			return 1;
			break;
		}
		break;
	}
	case UP:
	{
		if (hang + 1 == temp.gethang() && lie == temp.getlie())
		{
			exist = 0;
			return 1;
			break;
		}
		break;
	}
	case DOWN:
	{
		if (hang - 1 == temp.gethang() && lie == temp.getlie())
		{
			exist = 0;
			return 1;
			break;
		}
		break;
	}
	
	}
	return 0;
}
bool box::existNot()
{
	return exist;
}
void box::reset()
{
	srand((int)time(0));
	int judge = 1;
	while (judge)
	{
		int tempR = rand() % 19;
		int tempA = rand() % 19;
		if (map1.mapdata[tempR][tempA])
		{
			this->hang = tempR;
			this->lie = tempA;
			judge = 0;
			map1.mapdata[tempR][tempA] = 0;
			
		}
	}
	exist = 1;
}
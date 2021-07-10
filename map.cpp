#include"map.h"
#include<time.h>
HBITMAP map_ = (HBITMAP)LoadImage(NULL, L"bp.bmp", IMAGE_BITMAP, 600, 600, LR_LOADFROMFILE);
HBITMAP WALL = (HBITMAP)LoadImage(NULL, L"wall.bmp", IMAGE_BITMAP, 30, 30, LR_LOADFROMFILE);
void map::drawmap(HDC hdc,int i,int j)
{
	HDC mdc = CreateCompatibleDC(hdc);
	if (!mapdata[i][j])
	{
		SelectObject(mdc, WALL);
		BitBlt(hdc, j * 30, i * 30, 30, 30, mdc, 0, 0, SRCCOPY);
	}
	
	DeleteObject(mdc);	

}
void map::switchmap()
{
	if (stage == 1)
	{
		stage = 2;
		for (int i = 0; i < MAPLONG; ++i)
		{
			for (int j = 0; j < MAPLONG; ++j)
			{
				mapdata[i][j] = mapdata2[i][j];
			}
		}
	}//第一张地图切换到第二张
	else if (stage == 2)
	{
		stage = 3;
		for (int i = 0; i < MAPLONG; ++i)
		{
			for (int j = 0; j < MAPLONG; ++j)
			{
				mapdata[i][j] = mapdata3[i][j];
			}
		}
	}//第二张到第三张
	else
	{
		stage = 0;
	}
}
bool map::map_finish()
{
	if (stage == 0)
		return 1;
	else
		return 0;
}

#include"map.h"
#include"player.h"
#include"enemy.h"
#include"ammo.h"
#include"box.h"
#include<CommCtrl.h>
#include<Windows.h>

HBITMAP f1 = (HBITMAP)LoadImage(NULL, L"1.bmp", IMAGE_BITMAP, 600, 600, LR_LOADFROMFILE);//帧动画所需位图
HBITMAP f2 = (HBITMAP)LoadImage(NULL, L"2.bmp", IMAGE_BITMAP, 600, 600, LR_LOADFROMFILE);
HBITMAP f3 = (HBITMAP)LoadImage(NULL, L"3.bmp", IMAGE_BITMAP, 600, 600, LR_LOADFROMFILE);
HBITMAP f4 = (HBITMAP)LoadImage(NULL, L"4.bmp", IMAGE_BITMAP, 600, 600, LR_LOADFROMFILE);
HBITMAP f5 = (HBITMAP)LoadImage(NULL, L"5.bmp", IMAGE_BITMAP, 600, 600, LR_LOADFROMFILE);
HBITMAP f6 = (HBITMAP)LoadImage(NULL, L"6.bmp", IMAGE_BITMAP, 600, 600, LR_LOADFROMFILE);
////////位图加载
map testmap;
player testplayer;
box testbox;
////////人物生成

int state = 0;//确定当前状态来决定要不要开始游戏
int enemy_num = 4;//敌人数量
int enemy_speed = 800;//敌人运动速度
int ammo_speed = 60;//子弹速度
///////要用的值
vector<enemy>testenemy(enemy_num);//生成敌人


DWORD lasttime = 0;//子弹运动时间
DWORD dwlasttime=0;//敌人移动时间限制


void begin_animate(HDC hdc)//开头画面
{
	HDC mdc = CreateCompatibleDC(hdc);
	SelectObject(mdc, f1);
	BitBlt(hdc, 0, 0, 600, 600, mdc, 0, 0, SRCCOPY);
	Sleep(2000);
	SelectObject(mdc, f2);
	BitBlt(hdc, 0, 0, 600, 600, mdc, 0, 0, SRCCOPY);
	Sleep(1000);
	SelectObject(mdc, f3);
	BitBlt(hdc, 0, 0, 600, 600, mdc, 0, 0, SRCCOPY);
	Sleep(2000);
	SelectObject(mdc, f4);
	BitBlt(hdc, 0, 0, 600, 600, mdc, 0, 0, SRCCOPY);
	Sleep(2000);
	SelectObject(mdc, f5);
	BitBlt(hdc, 0, 0, 600, 600, mdc, 0, 0, SRCCOPY);
	Sleep(1000);
	SelectObject(mdc, f6);
	BitBlt(hdc, 0, 0, 600, 600, mdc, 0, 0, SRCCOPY);
	Sleep(2000);
	SelectObject(mdc, f5);
	BitBlt(hdc, 0, 0, 600, 600, mdc, 0, 0, SRCCOPY);
	Sleep(4000);
	DeleteObject(mdc);
}
void end_animate(HDC hdc)//结尾画面
{
	HDC mdc = CreateCompatibleDC(hdc);
	SelectObject(mdc, f5);
	BitBlt(hdc, 0, 0, 600, 600, mdc, 0, 0, SRCCOPY);
	Sleep(2000);
	SelectObject(mdc, f6);
	BitBlt(hdc, 0, 0, 600, 600, mdc, 0, 0, SRCCOPY);
	Sleep(2000);
	SelectObject(mdc, f4);
	BitBlt(hdc, 0, 0, 600, 600, mdc, 0, 0, SRCCOPY);
	Sleep(2000);
	SelectObject(mdc, f1);
	BitBlt(hdc, 0, 0, 600, 600, mdc, 0, 0, SRCCOPY);
	Sleep(2000);
	DeleteObject(mdc);
}
///////通过加载位图和sleep函数让画面有动起来的效果
LRESULT CALLBACK MyWNDPROC(HWND hwnd, UINT message, 
	WPARAM wparam, LPARAM lparam)
{
	HDC hdc=GetDC(hwnd);//得到窗口句柄
	PAINTSTRUCT painstruct;
	static HWND but1;
	static HWND but2;
	static HWND but3;
	static HWND subbut1;
	static HWND subbut2;
	static HWND subbut3;
	switch (message)
	{
	case WM_CREATE:
	{

		but1 = CreateWindow(L"button", L"开始游戏", WS_CHILD |WS_VISIBLE | BS_PUSHBUTTON, 230, 220, 100, 30, hwnd, (HMENU)111, ((LPCREATESTRUCT)lparam)->hInstance, NULL);
		but2 = CreateWindow(L"button", L"结束游戏", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 230, 380, 100, 30, hwnd, (HMENU)1111, ((LPCREATESTRUCT)lparam)->hInstance, NULL);
		but3 = CreateWindow(L"button", L"设置难度",WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 230, 300, 100, 30, hwnd, (HMENU)112, ((LPCREATESTRUCT)lparam)->hInstance, NULL);
		subbut1= CreateWindow(L"button", L"简单", WS_CHILD  | BS_PUSHBUTTON, 230, 220, 100, 30, hwnd, (HMENU)1112, ((LPCREATESTRUCT)lparam)->hInstance, NULL);
		subbut2= CreateWindow(L"button", L"中等", WS_CHILD  | BS_PUSHBUTTON, 230, 300, 100, 30, hwnd, (HMENU)1113, ((LPCREATESTRUCT)lparam)->hInstance, NULL);
		subbut3= CreateWindow(L"button", L"困难", WS_CHILD  | BS_PUSHBUTTON, 230, 380, 100, 30, hwnd, (HMENU)1114, ((LPCREATESTRUCT)lparam)->hInstance, NULL);
		break;
	}
	case WM_DESTROY:
	{
		PostQuitMessage(0);//发送quit消息以退出
		break;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wparam))//通过高位消息来分辨鼠标在哪一个按钮上面
		{
		case 111:
		{
			if (HIWORD(wparam) == BN_CLICKED)//通过低位消息来判断鼠标干了什么
			{
				//InvalidateRect(hwnd, NULL, TRUE);
				ShowWindow(but1, SW_HIDE);
				ShowWindow(but2, SW_HIDE);//隐藏按钮
				state = 2;//状态跳转到放连环画
				break;
			}
			break;
		}
		case 1111:
		{
			if (HIWORD(wparam) == BN_CLICKED ||HIWORD(wparam)== BN_DBLCLK)
			{
				PostQuitMessage(0);
			}//结束游戏
			break;
		}
		case 112:
		{
			if (HIWORD(wparam) == BN_CLICKED || HIWORD(wparam) == BN_DBLCLK)
			{
				ShowWindow(but1, SW_HIDE);
				ShowWindow(but2, SW_HIDE);
				ShowWindow(but3, SW_HIDE);
				ShowWindow(subbut1, SW_SHOW);
				ShowWindow(subbut2, SW_SHOW);
				ShowWindow(subbut3, SW_SHOW);
				InvalidateRect(hwnd, NULL, TRUE);
			}
			break;
		}
		case 1112:
		{
			if (HIWORD(wparam) == BN_CLICKED || HIWORD(wparam) == BN_DBLCLK)
			{
				enemy_speed = 800;
				enemy_num = 4;
				MessageBox(hwnd, L"设置成功", L"!", MB_OK | MB_ICONINFORMATION);
			}
			ShowWindow(but1, SW_SHOW);
			ShowWindow(but2, SW_SHOW);
			ShowWindow(but3, SW_SHOW);
			ShowWindow(subbut1, SW_HIDE);
			ShowWindow(subbut2, SW_HIDE);
			ShowWindow(subbut3, SW_HIDE);
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		}
		case 1113:
		{
			if (HIWORD(wparam) == BN_CLICKED || HIWORD(wparam) == BN_DBLCLK)
			{
				enemy_speed = 600;
				testplayer.setammo(14);
				enemy_num = 5;
				testenemy.resize(enemy_num);
				MessageBox(hwnd, L"设置成功", L"!", MB_OK | MB_ICONINFORMATION);
			}
			ShowWindow(but1, SW_SHOW);
			ShowWindow(but2, SW_SHOW);
			ShowWindow(but3, SW_SHOW);
			ShowWindow(subbut1, SW_HIDE);
			ShowWindow(subbut2, SW_HIDE);
			ShowWindow(subbut3, SW_HIDE);
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		}
		case 1114:
		{
			if (HIWORD(wparam) == BN_CLICKED || HIWORD(wparam) == BN_DBLCLK)
			{
				enemy_speed = 400;
				testplayer.setammo(12);
				enemy_num = 6;
				testenemy.resize(enemy_num);
				MessageBox(hwnd, L"设置成功", L"!", MB_OK | MB_ICONINFORMATION);
			}
			ShowWindow(but1, SW_SHOW);
			ShowWindow(but2, SW_SHOW);
			ShowWindow(but3, SW_SHOW);
			ShowWindow(subbut1, SW_HIDE);
			ShowWindow(subbut2, SW_HIDE);
			ShowWindow(subbut3, SW_HIDE);
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		}
		default:
			break;
		}
		SetFocus(hwnd);//让主窗口是接收消息的窗口
	}
	case WM_PAINT:
	{
		switch (state)
		{
		case 0:
		{
			break;//初始状态，什么也不做
		}
		case 2:
		{
			begin_animate(hdc);
			state = 1;
			break;
		}
		case 1:
		{
			hdc = BeginPaint(hwnd, &painstruct);
			testplayer.drawcloud(hdc);//不在视野范围里面全部画烟雾
			for (int i = 0; i < MAPLONG; ++i)//只有在玩家的视野里面才会把地图画出来
			{
				for (int j = 0; j < MAPLONG; ++j)//通过遍历对每一个点进行判断
				{
					if (testplayer.under_vision(i, j))
					{
						testmap.drawmap(hdc, i, j);
					}
				}
			}


			for (int i = 0; i < (int)testenemy.size(); ++i)
			{
				if (testplayer.under_vision(testenemy[i].gethang(), testenemy[i].getlie()))//在玩家视野里面才会把敌人画出来
				{
					testenemy[i].drawenemy(hdc);
				}
			}
			if (testplayer.under_vision(testbox.gethang(), testbox.getlie()))//在玩家视野里面才会把宝藏画出来
			{
				testbox.drawbox(hdc);
			}
			testplayer.drawplayer(hdc);
			EndPaint(hwnd, &painstruct);
			break;
		}
		}
		
	}
	case WM_KEYDOWN:
	{
		if (state == 1)
		{
			switch (wparam)
			{
			case 0x57://W
				testplayer.setDIR(UP);
				testplayer.drawblank(hdc);
				testplayer.moveplayer();
				testplayer.drawcloud(hdc);
				testplayer.drawplayer(hdc);
				break;
			case 0x53://S
				testplayer.setDIR(DOWN);
				testplayer.drawblank(hdc);
				testplayer.moveplayer();
				testplayer.drawcloud(hdc);
				testplayer.drawplayer(hdc);
				break;
			case 0x41://A
				testplayer.setDIR(LEFT);
				testplayer.drawblank(hdc);
				testplayer.moveplayer();
				testplayer.drawcloud(hdc);
				testplayer.drawplayer(hdc);
				break;
			case 0x44://D
				testplayer.setDIR(RIGHT);
				testplayer.drawblank(hdc);
				testplayer.moveplayer();
				testplayer.drawcloud(hdc);
				testplayer.drawplayer(hdc);
				break;
			case 0x4a://J
				if (!testplayer.player_ammo.checkone())//子弹不在
				{
					testplayer.shoot(hwnd);
					testplayer.player_ammo.hitwall();
					if (testplayer.player_ammo.checkone())//子弹还在
					{
						testplayer.player_ammo.drawammo(hdc);

					}
				}
				break;
			}

			testbox.found(testplayer);//玩家移动之后判断是否找到宝箱
			for (int i = 0; i < enemy_num; ++i)
			{
				testenemy[i].getPath(testplayer.gethang(),testplayer.getlie());
			}//重新获取新的位置
			//玩家移动后更新玩家的视野范围内的画面
			if (testplayer.under_vision(testbox.gethang(), testbox.getlie()))
			{
				testbox.drawbox(hdc);
			}
			for (int i = 0; i < MAPLONG; ++i)
			{
				for (int j = 0; j < MAPLONG; ++j)
				{
					if (testplayer.under_vision(i, j))
					{
						testmap.drawmap(hdc, i, j);
					}
				}
			}
			for (int i = 0; i < (int)testenemy.size(); ++i)
			{
				if (testplayer.under_vision(testenemy[i].gethang(), testenemy[i].getlie()))//在玩家视野里面才会把敌人画出来
				{
					testenemy[i].drawenemy(hdc);
				}
			}
			break;
		}
	}
	}

	ReleaseDC(hwnd, hdc);
	return DefWindowProcW(hwnd, message, wparam, lparam);//其他没有定义的消息由默认窗口过程函数处理		
	

}
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPreIncetance,
	LPSTR IpCmdLine, int nShowCmd)
{
	HWND hwnd;
	MSG msg;
	//窗口设计
	WNDCLASS ex;
	ex.style = NULL;
	ex.cbClsExtra = 0;
	ex.cbWndExtra = 0;
	ex.hInstance = hInstance;
	ex.hIcon = NULL;
	ex.hCursor = NULL;
	ex.hbrBackground = CreateSolidBrush(RGB(255, 255, 255));
	ex.lpfnWndProc = &MyWNDPROC;
	ex.lpszMenuName = NULL;
	ex.lpszClassName = L"my project";
	RegisterClass(&ex);//注册窗口
	hwnd = CreateWindow(ex.lpszClassName, L"做梦", WS_OVERLAPPEDWINDOW, 450, 100, 600, 600,
		NULL, NULL, hInstance, NULL);
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);
	bool game_continue = 1;
	HDC hdc = GetDC(hwnd);
	//消息循环
	while (game_continue&&!testmap.map_finish())//游戏可以继续而且地图没用完
	{
		if (PeekMessage(&msg, NULL, 0, 0,PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		if (state == 1)//当且仅当游戏可以进行
		{
			if (GetTickCount64() - lasttime >= ammo_speed)//子弹
			{
				lasttime = (DWORD)GetTickCount64();//更新时间
				testplayer.player_ammo.hitwall();
				if (!testenemy.empty())
				{
					for (int i = 0; i < (int)testenemy.size(); ++i)
					{
						testplayer.player_ammo.hitenemy(testenemy[i]);//判定是否击中敌人

					}
				}
				//上述情况都没有，移动子弹
				if (testplayer.player_ammo.checkone())//子弹射出去
				{
					
					if (testplayer.under_vision(testplayer.player_ammo.gethang(), testplayer.player_ammo.getlie()))
					{
						testplayer.player_ammo.drawblank(hdc);//原位置画空白
					}
					else
					{
						testplayer.player_ammo.in_smoke(hdc);
					}
					testplayer.player_ammo.moveplayer();//移动子弹
					if (testplayer.under_vision(testplayer.player_ammo.gethang(), testplayer.player_ammo.getlie()))
					{
						testplayer.player_ammo.drawammo(hdc);//画子弹
					}
				}
				else//没射
				{

					if (testplayer.under_vision(testplayer.player_ammo.gethang(), testplayer.player_ammo.getlie()))
					{
						if (testplayer.gethang() == testplayer.player_ammo.gethang() && testplayer.getlie() == testplayer.player_ammo.getlie())
						{
							testplayer.drawplayer(hdc);
						}
						//当子弹撞墙之后，子弹的位置没有更新，停留原处，
						//玩家到达子弹相同位置后为了防止两个位图在一个地方反复绘制，进行判断只绘制玩家位图
						else
						{
							testplayer.player_ammo.drawblank(hdc);
						}
					}
					else
					{
						testplayer.player_ammo.in_smoke(hdc);
					}
					
				}
			}
			if (GetTickCount64() - dwlasttime >= enemy_speed)//控制绘制时间，避免闪烁
			{
				dwlasttime = (DWORD)GetTickCount64();//更新时间
				testplayer.drawcloud(hdc);
				for (int i = 0; i < MAPLONG; ++i)
				{
					for (int j = 0; j < MAPLONG; ++j)
					{
						if (testplayer.under_vision(i, j))
						{
							testmap.drawmap(hdc, i, j);
						}
					}
				}
				if (testplayer.under_vision(testbox.gethang(), testbox.getlie()))
				{
					testbox.drawbox(hdc);
				}
				testplayer.drawplayer(hdc);
				//重新画画面
				if (!testenemy.empty())
				{
					for (int i = 0; i < (int)testenemy.size(); ++i)
					{

						testenemy[i].getPath(testplayer.getlie(), testplayer.gethang());//根据玩家位置赵路
						if (testplayer.under_vision(testenemy[i].gethang(), testenemy[i].getlie()))
						{
							testenemy[i].drawblank(hdc);
						}
						else
						{
							testenemy[i].in_smoke(hdc);
						}
						testenemy[i].moveplayer();
						if (testplayer.under_vision(testenemy[i].gethang(), testenemy[i].getlie()))
						{
							testenemy[i].drawenemy(hdc);
						}
						testplayer.caught(testenemy[i]);//判断抓到玩家
						testbox.found(testplayer);

					}
				}
			}
			if (!testbox.existNot())//宝藏被找到了
			{
				if (!testmap.map_finish())
				{
					MessageBox(hwnd, L"哦！", L"提示框", MB_OK);
					testmap.switchmap();//换地图
					testplayer.reset_position();//玩家重新设置位置
					testbox.reset();//重置人物
					for (int i = 0; i < (int)testenemy.size(); ++i)
					{
						testenemy[i].reset();//敌人重设位置
					}
				}
				else
				{
					break;//用完了就跳出去
				}
			}
			game_continue = !testplayer.gameover();
		}
	}
	if (msg.message != WM_QUIT)//游戏结束后面就不用了
	{
		if (!testplayer.alive_ornot())
		{
			MessageBox(hwnd, L"？", L"游戏结束", MB_OK | MB_ICONINFORMATION);
		}
		if (testmap.map_finish())
		{
			MessageBox(hwnd, L"！", L"游戏结束", MB_OK | MB_ICONINFORMATION);
		}
		end_animate(hdc);
		ReleaseDC(hwnd, hdc);
	}
	
	return 0;
}
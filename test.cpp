#include"map.h"
#include"player.h"
#include"enemy.h"
#include"ammo.h"
#include"box.h"
#include<CommCtrl.h>
#include<Windows.h>

HBITMAP f1 = (HBITMAP)LoadImage(NULL, L"1.bmp", IMAGE_BITMAP, 600, 600, LR_LOADFROMFILE);//֡��������λͼ
HBITMAP f2 = (HBITMAP)LoadImage(NULL, L"2.bmp", IMAGE_BITMAP, 600, 600, LR_LOADFROMFILE);
HBITMAP f3 = (HBITMAP)LoadImage(NULL, L"3.bmp", IMAGE_BITMAP, 600, 600, LR_LOADFROMFILE);
HBITMAP f4 = (HBITMAP)LoadImage(NULL, L"4.bmp", IMAGE_BITMAP, 600, 600, LR_LOADFROMFILE);
HBITMAP f5 = (HBITMAP)LoadImage(NULL, L"5.bmp", IMAGE_BITMAP, 600, 600, LR_LOADFROMFILE);
HBITMAP f6 = (HBITMAP)LoadImage(NULL, L"6.bmp", IMAGE_BITMAP, 600, 600, LR_LOADFROMFILE);
////////λͼ����
map testmap;
player testplayer;
box testbox;
////////��������

int state = 0;//ȷ����ǰ״̬������Ҫ��Ҫ��ʼ��Ϸ
int enemy_num = 4;//��������
int enemy_speed = 800;//�����˶��ٶ�
int ammo_speed = 60;//�ӵ��ٶ�
///////Ҫ�õ�ֵ
vector<enemy>testenemy(enemy_num);//���ɵ���


DWORD lasttime = 0;//�ӵ��˶�ʱ��
DWORD dwlasttime=0;//�����ƶ�ʱ������


void begin_animate(HDC hdc)//��ͷ����
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
void end_animate(HDC hdc)//��β����
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
///////ͨ������λͼ��sleep�����û����ж�������Ч��
LRESULT CALLBACK MyWNDPROC(HWND hwnd, UINT message, 
	WPARAM wparam, LPARAM lparam)
{
	HDC hdc=GetDC(hwnd);//�õ����ھ��
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

		but1 = CreateWindow(L"button", L"��ʼ��Ϸ", WS_CHILD |WS_VISIBLE | BS_PUSHBUTTON, 230, 220, 100, 30, hwnd, (HMENU)111, ((LPCREATESTRUCT)lparam)->hInstance, NULL);
		but2 = CreateWindow(L"button", L"������Ϸ", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 230, 380, 100, 30, hwnd, (HMENU)1111, ((LPCREATESTRUCT)lparam)->hInstance, NULL);
		but3 = CreateWindow(L"button", L"�����Ѷ�",WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 230, 300, 100, 30, hwnd, (HMENU)112, ((LPCREATESTRUCT)lparam)->hInstance, NULL);
		subbut1= CreateWindow(L"button", L"��", WS_CHILD  | BS_PUSHBUTTON, 230, 220, 100, 30, hwnd, (HMENU)1112, ((LPCREATESTRUCT)lparam)->hInstance, NULL);
		subbut2= CreateWindow(L"button", L"�е�", WS_CHILD  | BS_PUSHBUTTON, 230, 300, 100, 30, hwnd, (HMENU)1113, ((LPCREATESTRUCT)lparam)->hInstance, NULL);
		subbut3= CreateWindow(L"button", L"����", WS_CHILD  | BS_PUSHBUTTON, 230, 380, 100, 30, hwnd, (HMENU)1114, ((LPCREATESTRUCT)lparam)->hInstance, NULL);
		break;
	}
	case WM_DESTROY:
	{
		PostQuitMessage(0);//����quit��Ϣ���˳�
		break;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wparam))//ͨ����λ��Ϣ���ֱ��������һ����ť����
		{
		case 111:
		{
			if (HIWORD(wparam) == BN_CLICKED)//ͨ����λ��Ϣ���ж�������ʲô
			{
				//InvalidateRect(hwnd, NULL, TRUE);
				ShowWindow(but1, SW_HIDE);
				ShowWindow(but2, SW_HIDE);//���ذ�ť
				state = 2;//״̬��ת����������
				break;
			}
			break;
		}
		case 1111:
		{
			if (HIWORD(wparam) == BN_CLICKED ||HIWORD(wparam)== BN_DBLCLK)
			{
				PostQuitMessage(0);
			}//������Ϸ
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
				MessageBox(hwnd, L"���óɹ�", L"!", MB_OK | MB_ICONINFORMATION);
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
				MessageBox(hwnd, L"���óɹ�", L"!", MB_OK | MB_ICONINFORMATION);
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
				MessageBox(hwnd, L"���óɹ�", L"!", MB_OK | MB_ICONINFORMATION);
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
		SetFocus(hwnd);//���������ǽ�����Ϣ�Ĵ���
	}
	case WM_PAINT:
	{
		switch (state)
		{
		case 0:
		{
			break;//��ʼ״̬��ʲôҲ����
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
			testplayer.drawcloud(hdc);//������Ұ��Χ����ȫ��������
			for (int i = 0; i < MAPLONG; ++i)//ֻ������ҵ���Ұ����Ż�ѵ�ͼ������
			{
				for (int j = 0; j < MAPLONG; ++j)//ͨ��������ÿһ��������ж�
				{
					if (testplayer.under_vision(i, j))
					{
						testmap.drawmap(hdc, i, j);
					}
				}
			}


			for (int i = 0; i < (int)testenemy.size(); ++i)
			{
				if (testplayer.under_vision(testenemy[i].gethang(), testenemy[i].getlie()))//�������Ұ����Ż�ѵ��˻�����
				{
					testenemy[i].drawenemy(hdc);
				}
			}
			if (testplayer.under_vision(testbox.gethang(), testbox.getlie()))//�������Ұ����Ż�ѱ��ػ�����
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
				if (!testplayer.player_ammo.checkone())//�ӵ�����
				{
					testplayer.shoot(hwnd);
					testplayer.player_ammo.hitwall();
					if (testplayer.player_ammo.checkone())//�ӵ�����
					{
						testplayer.player_ammo.drawammo(hdc);

					}
				}
				break;
			}

			testbox.found(testplayer);//����ƶ�֮���ж��Ƿ��ҵ�����
			for (int i = 0; i < enemy_num; ++i)
			{
				testenemy[i].getPath(testplayer.gethang(),testplayer.getlie());
			}//���»�ȡ�µ�λ��
			//����ƶ��������ҵ���Ұ��Χ�ڵĻ���
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
				if (testplayer.under_vision(testenemy[i].gethang(), testenemy[i].getlie()))//�������Ұ����Ż�ѵ��˻�����
				{
					testenemy[i].drawenemy(hdc);
				}
			}
			break;
		}
	}
	}

	ReleaseDC(hwnd, hdc);
	return DefWindowProcW(hwnd, message, wparam, lparam);//����û�ж������Ϣ��Ĭ�ϴ��ڹ��̺�������		
	

}
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPreIncetance,
	LPSTR IpCmdLine, int nShowCmd)
{
	HWND hwnd;
	MSG msg;
	//�������
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
	RegisterClass(&ex);//ע�ᴰ��
	hwnd = CreateWindow(ex.lpszClassName, L"����", WS_OVERLAPPEDWINDOW, 450, 100, 600, 600,
		NULL, NULL, hInstance, NULL);
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);
	bool game_continue = 1;
	HDC hdc = GetDC(hwnd);
	//��Ϣѭ��
	while (game_continue&&!testmap.map_finish())//��Ϸ���Լ������ҵ�ͼû����
	{
		if (PeekMessage(&msg, NULL, 0, 0,PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		if (state == 1)//���ҽ�����Ϸ���Խ���
		{
			if (GetTickCount64() - lasttime >= ammo_speed)//�ӵ�
			{
				lasttime = (DWORD)GetTickCount64();//����ʱ��
				testplayer.player_ammo.hitwall();
				if (!testenemy.empty())
				{
					for (int i = 0; i < (int)testenemy.size(); ++i)
					{
						testplayer.player_ammo.hitenemy(testenemy[i]);//�ж��Ƿ���е���

					}
				}
				//���������û�У��ƶ��ӵ�
				if (testplayer.player_ammo.checkone())//�ӵ����ȥ
				{
					
					if (testplayer.under_vision(testplayer.player_ammo.gethang(), testplayer.player_ammo.getlie()))
					{
						testplayer.player_ammo.drawblank(hdc);//ԭλ�û��հ�
					}
					else
					{
						testplayer.player_ammo.in_smoke(hdc);
					}
					testplayer.player_ammo.moveplayer();//�ƶ��ӵ�
					if (testplayer.under_vision(testplayer.player_ammo.gethang(), testplayer.player_ammo.getlie()))
					{
						testplayer.player_ammo.drawammo(hdc);//���ӵ�
					}
				}
				else//û��
				{

					if (testplayer.under_vision(testplayer.player_ammo.gethang(), testplayer.player_ammo.getlie()))
					{
						if (testplayer.gethang() == testplayer.player_ammo.gethang() && testplayer.getlie() == testplayer.player_ammo.getlie())
						{
							testplayer.drawplayer(hdc);
						}
						//���ӵ�ײǽ֮���ӵ���λ��û�и��£�ͣ��ԭ����
						//��ҵ����ӵ���ͬλ�ú�Ϊ�˷�ֹ����λͼ��һ���ط��������ƣ������ж�ֻ�������λͼ
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
			if (GetTickCount64() - dwlasttime >= enemy_speed)//���ƻ���ʱ�䣬������˸
			{
				dwlasttime = (DWORD)GetTickCount64();//����ʱ��
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
				//���»�����
				if (!testenemy.empty())
				{
					for (int i = 0; i < (int)testenemy.size(); ++i)
					{

						testenemy[i].getPath(testplayer.getlie(), testplayer.gethang());//�������λ����·
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
						testplayer.caught(testenemy[i]);//�ж�ץ�����
						testbox.found(testplayer);

					}
				}
			}
			if (!testbox.existNot())//���ر��ҵ���
			{
				if (!testmap.map_finish())
				{
					MessageBox(hwnd, L"Ŷ��", L"��ʾ��", MB_OK);
					testmap.switchmap();//����ͼ
					testplayer.reset_position();//�����������λ��
					testbox.reset();//��������
					for (int i = 0; i < (int)testenemy.size(); ++i)
					{
						testenemy[i].reset();//��������λ��
					}
				}
				else
				{
					break;//�����˾�����ȥ
				}
			}
			game_continue = !testplayer.gameover();
		}
	}
	if (msg.message != WM_QUIT)//��Ϸ��������Ͳ�����
	{
		if (!testplayer.alive_ornot())
		{
			MessageBox(hwnd, L"��", L"��Ϸ����", MB_OK | MB_ICONINFORMATION);
		}
		if (testmap.map_finish())
		{
			MessageBox(hwnd, L"��", L"��Ϸ����", MB_OK | MB_ICONINFORMATION);
		}
		end_animate(hdc);
		ReleaseDC(hwnd, hdc);
	}
	
	return 0;
}
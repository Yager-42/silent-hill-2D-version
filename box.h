#pragma once
#include"map.h"
#include"goobject.h"
#include<time.h>
#include"player.h"
#ifndef BOX_H
#define BOX_H




class box:public goobject
{
protected:
	bool exist = 1;//�жϱ��ػ��治����
public:
	box()
	{
		srand((int)time(0));
		int judge = 1;//����������ɵ�λ���ǲ��������ɵģ���ô��������λ��
		while (judge)
		{
			int tempR = (rand()+1024) % 19;
			int tempA = (rand()+1024) % 19;
			if (map1.mapdata[tempR][tempA])
			{
				this->hang = tempR;
				this->lie = tempA;
				judge = 0;
				map1.mapdata[tempR][tempA] = 0;
			}
		}
	}
	void drawbox(HDC hdc);//������
	void moveplayer(){}//�������û�ã�ֻ����Ҫ�̳�goobject���еľ�̬���ݳ�Աmap1
	bool found(player& temp);//�жϱ�����û�б��ҵ�
	int gethang()
	{
		return hang;
	}
	int getlie()
	{
		return lie;
	}//�õ�������ֵ
	bool existNot();//���ش����Ƿ�
	void reset();//����һ���������ñ��ص�ֵ
		
};
#endif

#include "stdafx.h"
#include "common.h"
#include "math.h"
#include "scan.h"
#include "stdlib.h"

#define min(a,b) (((a)<(b))? (a):(b))

//��ɨ����Y=y���AB�Ľ����x���꣬����޽��㣬����-99999
int linejoin(int A[2],int B[3],int y)
{
	float t;
	if (B[1]==A[1])
		return -99999;

	t = (y-A[1]) / float(B[1]-A[1]);
	if (t>=0.0 && t<=1.0){
		return ROUND(A[0] + (B[0]-A[0])*t);
	}else
		return -99999;
}

//�����õ��ĺ���
void SetPixel(int x,int y);
float GetDepth(int x,int y);
void SetDepth(int x,int y,float depth);

//���������㷨,Zbuffer�㷨
//coord ��������
//depth ���ض�Ӧ�����
//n ���ظ���
void linefill(int coord[][2],float depth[],int n)
{
	int miny,maxy;
	int X[10];
	float A[3],B[3],C[3],D[3],E[3],R[3];

	// �ҳ�y����������С�Ķ��� 
	miny=coord[0][1];maxy=coord[0][1];
	for (int i=0;i<n;i++){
		if (coord[i][1]<miny)
			miny=coord[i][1];
		if (coord[i][1]>maxy)
			maxy=coord[i][1];
	}

	for (int i = 0;i<2;i++) {
		A[i] = coord[0][i]; //��һ���������
		B[i] = coord[1][i] - coord[0][i]; //�ڶ�����͵�һ����������
		C[i] = coord[2][i] - coord[0][i]; //��������͵�һ����������
	}
	A[2] = depth[0];//���ֵ
	B[2] = depth[1] - depth[0];//�ڶ�����͵�һ�������Ȳ�
	C[2] = depth[2] - depth[0];//��������͵�һ�������Ȳ�

	//ֱ�߷���Q(t)=(x0,y0,0)+(0,0,1)t 
	D[0] = D[1] = 0;//���ø�ֱ��ʱ,D[0],D[1]��Ҫ���¸�ֵ
	D[2] = 0;
	E[0] = E[1] = 0;
	E[2] = 1;

	// ʹɨ���ߴ�y������С�ĵ���1��y���Ķ��� 
	for (int y=miny;y<=maxy;y++)
	{
		//��Ӵ���
		//���ж��ܷ����ĳ������(x,y)ʱ,Ҫ��������ص����ֵ�������ṩһ�ַ������ο���
		//��coor,depth��ѡ3���㽨��һ��ƽ��,�ٽ���һ��ֱ��(������(x,y,0),����(0,0,1))
		//���ú���facejoin(�ο�common.h),����ƽ����ֱ�ߵĽ���,�����z�����������ص����
		int k = 0, x;
		float d;
		for (int i = 0;i<n - 1;i++)
		{

			if (linejoin(coord[i], coord[i + 1], y) != -99999 && (y != min(coord[i][1], coord[i + 1][1])))
			{
				X[k] = linejoin(coord[i], coord[i + 1], y);
				k++;
			}
		}
		if (linejoin(coord[n - 1], coord[0], y) != -99999 && (y != min(coord[n - 1][1], coord[0][1])))
		{
			X[k] = linejoin(coord[n - 1], coord[0], y);
			k++;
		}
		sort(X, k);//��������Ĵ�С��������
		for (int i = 0;i<k / 2;i++)
		{
			for (x = X[2 * i];x <= X[2 * i + 1];x++)
			{
				D[0] = x;
				D[1] = y;
				if (facejoin(R, A, B, C, D, E) == 1)
				{
					d = R[2];
					if (d >= 0 && d <= 1 && d<GetDepth(x, y))
					{
						SetPixel(x, y);
						SetDepth(x, y, d);
					}
				}
			}
		}

	}

}

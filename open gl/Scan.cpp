#include "stdafx.h"
#include "common.h"
#include "math.h"
#include "scan.h"
#include "stdlib.h"

#define min(a,b) (((a)<(b))? (a):(b))

//求扫描线Y=y与边AB的交点的x坐标，如果无交点，返回-99999
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

//可能用到的函数
void SetPixel(int x,int y);
float GetDepth(int x,int y);
void SetDepth(int x,int y,float depth);

//多边形填充算法,Zbuffer算法
//coord 像素坐标
//depth 像素对应的深度
//n 像素个数
void linefill(int coord[][2],float depth[],int n)
{
	int miny,maxy;
	int X[10];
	float A[3],B[3],C[3],D[3],E[3],R[3];

	// 找出y坐标最大和最小的顶点 
	miny=coord[0][1];maxy=coord[0][1];
	for (int i=0;i<n;i++){
		if (coord[i][1]<miny)
			miny=coord[i][1];
		if (coord[i][1]>maxy)
			maxy=coord[i][1];
	}

	for (int i = 0;i<2;i++) {
		A[i] = coord[0][i]; //第一个点的坐标
		B[i] = coord[1][i] - coord[0][i]; //第二个点和第一个点的坐标差
		C[i] = coord[2][i] - coord[0][i]; //第三个点和第一个点的坐标差
	}
	A[2] = depth[0];//深度值
	B[2] = depth[1] - depth[0];//第二个点和第一个点的深度差
	C[2] = depth[2] - depth[0];//第三个点和第一个点的深度差

	//直线方程Q(t)=(x0,y0,0)+(0,0,1)t 
	D[0] = D[1] = 0;//在用该直线时,D[0],D[1]需要重新赋值
	D[2] = 0;
	E[0] = E[1] = 0;
	E[2] = 1;

	// 使扫描线从y坐标最小的递增1到y最大的顶点 
	for (int y=miny;y<=maxy;y++)
	{
		//添加代码
		//在判断能否绘制某个像素(x,y)时,要计算该像素的深度值。这里提供一种方法供参考：
		//从coor,depth中选3个点建立一个平面,再建立一条直线(经过点(x,y,0),方向(0,0,1))
		//调用函数facejoin(参考common.h),计算平面与直线的交点,交点的z分量即是像素的深度
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
		sort(X, k);//按照数组的从小到大排序
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

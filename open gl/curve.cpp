#include "stdafx.h"
#include "curve.h"
#include <math.h>
#include <gl/glut.h>

//计算n!/(k!(n-k)!),存储到c[k],其中k=0,1,...,n
void BezierCurve::binomiaCoeffs(int n,float *c){

	int k,i;

	for(k=0;k<=n;k++){
		//计算n!/(k!(n-k)!)
		c[k]=1;
		for(i=n;i>=k+1;i--)
			c[k]*=i;
		for(i=n-k;i>=2;i--)
			c[k]/=i;
	}

}


//Bezier曲线中,起点为B(0),终点为B(1),该函数计算点B(u)的坐标，其中0<=u<=1;
//bezPt 指向B(u)的指针,
//nCtrlPts 控制点个数
//ctrlPts 控制点内存起始地址
void BezierCurve::computeBezPt(float u,wcPt3D *bezPt,int nCtrlPts,wcPt3D *ctrlPts,float *C){
	float bezFcn;
	int k, n = nCtrlPts - 1;
	bezPt->x = bezPt->y = bezPt->z = 0.0;
		for(k=0;k<nCtrlPts;k++)
		{
			bezFcn = C[k]*powf(u, k)*powf(1 - u, n - k);
			bezPt->x += ctrlPts[k].x *bezFcn;
			bezPt->y += ctrlPts[k].y *bezFcn;
			bezPt->z += ctrlPts[k].z *bezFcn;
		}
		
	//powf(x,k) x的k次方
	//添加代码
}


//计算bezier曲线
//ctrlPts 控制点数组内存起始地址
//nCtrlPts 控制点个数
//bezCurvePts 曲线点数组内存起始地址
//nBezCurvePts 曲线点个数
void BezierCurve::bezier(wcPt3D *ctrlPts,int nCtrlPts,wcPt3D *bezCurvePts,int nBezCurvePts){

	/*
	if(nBezCurvePts>=2){
		for(int i=0;i<nBezCurvePts-1;i++)
			bezCurvePts[i]=ctrlPts[0];
		bezCurvePts[nBezCurvePts-1]=ctrlPts[nCtrlPts-1];
	}
	*/
	//添加代码
	wcPt3D bez;
	float u, *c;int k;
	c = new float[nCtrlPts];
		binomiaCoeffs(nCtrlPts - 1, c);
		for (k = 0;k <= nBezCurvePts;k++)
		{
			u = float(k)/float(nBezCurvePts);
			computeBezPt(u, &bez, nCtrlPts, ctrlPts, c);
			bezCurvePts[k] = bez;

		}

		delete[]c;
}

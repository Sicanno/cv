#include "stdafx.h"
#include "curve.h"
#include <math.h>
#include <gl/glut.h>

//����n!/(k!(n-k)!),�洢��c[k],����k=0,1,...,n
void BezierCurve::binomiaCoeffs(int n,float *c){

	int k,i;

	for(k=0;k<=n;k++){
		//����n!/(k!(n-k)!)
		c[k]=1;
		for(i=n;i>=k+1;i--)
			c[k]*=i;
		for(i=n-k;i>=2;i--)
			c[k]/=i;
	}

}


//Bezier������,���ΪB(0),�յ�ΪB(1),�ú��������B(u)�����꣬����0<=u<=1;
//bezPt ָ��B(u)��ָ��,
//nCtrlPts ���Ƶ����
//ctrlPts ���Ƶ��ڴ���ʼ��ַ
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
		
	//powf(x,k) x��k�η�
	//��Ӵ���
}


//����bezier����
//ctrlPts ���Ƶ������ڴ���ʼ��ַ
//nCtrlPts ���Ƶ����
//bezCurvePts ���ߵ������ڴ���ʼ��ַ
//nBezCurvePts ���ߵ����
void BezierCurve::bezier(wcPt3D *ctrlPts,int nCtrlPts,wcPt3D *bezCurvePts,int nBezCurvePts){

	/*
	if(nBezCurvePts>=2){
		for(int i=0;i<nBezCurvePts-1;i++)
			bezCurvePts[i]=ctrlPts[0];
		bezCurvePts[nBezCurvePts-1]=ctrlPts[nCtrlPts-1];
	}
	*/
	//��Ӵ���
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

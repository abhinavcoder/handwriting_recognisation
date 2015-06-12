#include <iostream>
#include <vector>
#include <stdio.h>
#include <functional>
#include <algorithm>
#include <numeric>
#include <cstddef>
#include "opencv2/opencv.hpp"
#include <iostream>
#include <fstream>
#include "overhauser.hpp"

using namespace std;
using namespace cv;

Mat result;
Mat Img;

vector<cv::Point2f> pts;
Mat curvesImg;
int selectedPt=-1;
CRSpline* spline = 0;

unsigned char LUT_RED[256];

// a case-insensitive comparison function:
bool mycomp (Point2f p1, Point2f p2)
{
    return p1.x<p2.x;
}

float dist(Point2f p1,Point2f p2)
{
    return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
}

int findNEarestPt(Point2f pt, float maxDist)
{
    float minDist=FLT_MAX;
    int ind=-1;
    for(int i=0;i<pts.size();++i)
    {
        float d=dist(pt,pts[i]);
        if(minDist>d)
        {
            ind=i;
            minDist=d;
        }
    }
    if(minDist>maxDist)
    {
        ind=-1;
    }
    return ind;
}

float F(float t,float x)
{
  vec3 rv = spline->GetInterpolatedSplinePoint(t);
  return x-rv.x;
}

float solveForX(float x)
{
    float a=0,b=1.0,c,e=1e-5;
    c=(a+b)/2;
    while( (fabs(b-a)>e) && (F(c,x)!=0) )
    {
        if (F(a,x)*F(c,x)<0)
        {
            b=c;
        }
        else
        {
            a=c;
        }
        c=(a+b)/2;
    }
return c;
}


int ind=-1;

void mouseHandler(int event, int x, int y, int flags, void* param)
{
    Point2f m;
    m.x=x;
    m.y=y;
    curvesImg=Scalar(0,0,0);

    switch (event)
    {
    case cv::EVENT_RBUTTONDOWN:
        ind=findNEarestPt(m,5);
        if (ind==-1)
        {

        }else
        {
            pts.erase(pts.begin()+ind);
            ind=-1;
        }
        break;
    case cv::EVENT_LBUTTONDOWN:
        ind=findNEarestPt(m,5);
        if (ind==-1)
        {
            pts.push_back(m);
            selectedPt=pts.size()-1;
        }else
        {
            selectedPt=ind;
        }
        break;
    case cv::EVENT_MOUSEMOVE:
        if(ind!=-1)
        {
            pts[selectedPt].x=m.x;
            pts[selectedPt].y=m.y;
        }
        break;
    case cv::EVENT_LBUTTONUP:
        ind=-1;
        break;
    }

    std::sort(pts.begin(),pts.end(),mycomp);
    if(pts.size()>0)
    {
        pts[pts.size()-1].x=curvesImg.cols;
        pts[0].x=0;
    }

    for(int i=0;i<pts.size();++i)
    {
        circle(curvesImg,pts[i],5,Scalar(0,255,255),-1,CV_AA);
    }

    if (spline) {delete spline;}
    spline = new CRSpline();

    for (int i=0;i<pts.size();++i)
    {
        vec3 v(pts[i].x,pts[i].y,0);
        spline->AddSplinePoint(v);
    }

    vec3 rv_last(0,0,0);
    if(pts.size()>2)
    {
        for(int i=0;i<256;++i)
        {
            float t=solveForX(i);
            vec3 rv = spline->GetInterpolatedSplinePoint(t);
            unsigned char I=(unsigned char)(rv.y);
            LUT_RED[i]=255-I;
            if(i>1)
            {
                line(curvesImg,Point(rv.x,rv.y),Point(rv_last.x,rv_last.y),Scalar(0,0,255),1);
            }
            rv_last=rv;
        }
    }

    line(curvesImg,Point(0,m.y),Point(curvesImg.cols,m.y),Scalar(0,255,0),1);
    line(curvesImg,Point(m.x,0),Point(m.x,curvesImg.rows),Scalar(0,255,0),1);

    imshow("Result",curvesImg); 

    vector<Mat> ch;
    cv::split(Img,ch);

    LUT(ch[2],Mat(256,1,CV_8UC1,LUT_RED),ch[2]);

    cv::merge(ch,result);

    imshow("Transformed",result);   
}
// ---------------------------------
// 
// ---------------------------------
//==============================================================================

int main( int argc, char** argv )
{

    for (int i=0;i<256;++i)
    {
        LUT_RED[i]=i;
    }

    namedWindow("Image",cv::WINDOW_NORMAL);
    namedWindow("Result");
    namedWindow("Transformed");

    Img=imread("ImageFinal.jpg",1);

    imshow("Image",Img);

    curvesImg=Mat::zeros(256,256,CV_8UC3);
    setMouseCallback("Result", mouseHandler, NULL);
    waitKey(0);

    getchar();
}
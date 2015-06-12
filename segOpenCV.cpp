#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <unistd.h>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

#define threshold 200
#define edge_thresh 50
#define segThresh 10  // depends upon the brush stoke size : test and assure the result 
#define safeThresh 50

int thresh , thresh1 = 88 ; 
// things left ::

/*
2. threshold the segmentation value 
3. In python GUI draw the image from the factored points .. using spline / linear interpolation 
5. Think of other applications too 
*/
Mat noise_erosion(Mat image) {
  Mat noise(image.rows,image.cols,CV_8UC1,Scalar(0));
  for(int i = 0 ; i < image.rows ;i++)
	  for(int j = 0 ; j < image.cols ;j++)
		  noise.at<uchar>(i,j) = 255 ;

  for(int i = 1 ; i < image.rows -1 ;i++)
  {
    for(int j = 1 ; j < image.cols - 1 ; j++)
	{
	  int m = i-1 ;
	  int flag = 0 ;
	  while(m<=i+1)
	  {
	    int n = j-1 ;
		while(n<=j+1)
		{
		    if(image.at<uchar>(i,j)==0)
				flag=1 ;
			n++;
		}
		m++;
	  }
	  if(flag==1)
		  noise.at<uchar>(i,j) =  0 ;
	}
  }
return noise ;
}

Mat get_binary(Mat image) {
 Mat binary(image.rows,image.cols,CV_8UC1,Scalar(0)); //To store and return the result
	
	for(int i=0; i < image.rows; i++) {
		for(int j=0; j < image.cols; j++) {
			//Conversion formula for gray-scale is applied as had been discusse
			if((0.33*image.at<Vec3b>(i,j)[0]+0.56*image.at<Vec3b>(i,j)[2]+0.11*image.at<Vec3b>(i,j)[1]) > thresh1)
		     binary.at<uchar>(i,j) = 255 ;
			else
			 binary.at<uchar>(i,j) = 0 ;
		}
	}
	return binary; //Result returned
}
Mat get_histogram(Mat image) {
	long long int freq[256] = {0};
	int intensity , maxi = 0  ;
	
	int freqIntensity[image.cols+1] ;
	bool isSafe[image.cols+1] ;

	int max , min ;
	cout<<image.rows<<" "<<image.cols<<endl;
	for(int i = 0 ; i < image.cols ; i++) 
	{
       freqIntensity[i] = 0 ;
       for(int j = 0 ; j < image.rows ; j++)
       {
         intensity = image.at<uchar>(j,i) ;
         if(intensity<100)
         {
            if(freqIntensity[i]==0)
            	min = j ;
            max = j ;
            freqIntensity[i]++ ;

         }
       }

       if(max - min > safeThresh)
       	isSafe[i] = true ;
       else
       	isSafe[i] = false ;

       cout<<i<<" "<<"Freq :: "<<freqIntensity[i]<<endl ; 
    }

    for(int i = 0 ; i < image.cols ; i++) 
    {
    	if(i>0)
    	{
             if(freqIntensity[i-1]>=segThresh && freqIntensity[i+1] >=segThresh && freqIntensity[i] < segThresh)
             	freqIntensity[i] = segThresh ;
    	}
    	if(freqIntensity[i] < segThresh )
    	{
    		if(isSafe[i])
    			freqIntensity[i] = segThresh;
    		else
                for(int j = 0 ; j < image.rows ; j++)
    		        image.at<uchar>(j,i) = 255 ;
    		
    	}
    }
	return image ;
}


int main()
{
	Mat image;
	string fname;
	//cin >> fname;
	image = imread("Image.jpg",CV_LOAD_IMAGE_COLOR);
	char win[] = "Histogram"; //String with the name of the window
	namedWindow(win,CV_WINDOW_AUTOSIZE);
	/*
	   if(!image.data){
		cout << "jvd";
		waitKey(0);
		return -1;
	*/
	imshow(win,image);
	waitKey(1000);	

	Mat binary = get_binary(image) ;
	waitKey(1000) ;
	Mat noise  = noise_erosion(binary);
	waitKey(1000) ;
	Mat secondary = get_histogram(noise);
	imwrite( "ImageFinal.jpg",secondary);
    imshow(win,secondary);
	waitKey(0);
	
	return 0;

}


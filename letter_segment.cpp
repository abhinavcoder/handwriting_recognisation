#include <iostream>
#include <fstream>
#include <cstring>
#include <queue>
#include <vector>
#include <cmath>

#define char_no 2
using namespace std ;
int main()
{

 int numx , numy , counter=0 ;
 vector< pair<int , int > > coordinate ;
int maxx = 0 , minx = 323000 ; 
ifstream file("letter_factor.txt") ;
while(!file.eof()) {
       file>>numx ;
       file>>numy ;
       if(numx > maxx)
       	 maxx = numx ;
       	if(numx < minx)
       		minx = numx ;
       coordinate.push_back(make_pair(numx,numy));
       counter++ ;
    }
    file.close();
int width_thresh = 1.2*(maxx - minx)/char_no ;
int deviation = width_thresh/5 ;
ofstream file1("letter_segment.txt");
//segment points are 0,0 
cout<<"maxx :: "<<maxx<<" minx :: "<<minx<<" width_thresh :: "<<width_thresh<<" deviation :: "<<deviation<<endl ; 
for(int i = 0 ; i < counter ; i++)
{
	if((coordinate[i].first < (minx + width_thresh + deviation))&&(coordinate[i].first> (minx + width_thresh - deviation)))
	 file1<<0<<" "<<0<<endl ;
	else
	 file1<<coordinate[i].first<<" "<<coordinate[i].second<<endl ;	
} 
file1.close();   
return 0 ;
}
#include <iostream>
#include <fstream>
#include <cstring>
#include <queue>
#include <vector>
#include <cmath>
#define coord_refactor
#define dist_thresh 2   // used for cleaning the coordinate 
using namespace std ;

 int main()
 {
 
 string str ;
 int numx , numy ;
 vector< pair<int , int > > coordinate , pseudoCordinate;

 //******** updating the coordinate vector **********
int counter = 0 , count2 = -1;  //contains the number of pair of coordinates

 ifstream file("letter_sample.txt");
    while(!file.eof()) {
       file>>numx ;
       file>>numy ;
       coordinate.push_back(make_pair(numx,numy));
       counter++ ;
    }
 file.close();   
//_______________________________________________________________
 
//******** processing the coordinates + writing to the file**************
#ifdef max_min 
  ofstream file1("letter_factor.txt");
  vector< pair<int,int> > prevDist ;
  pseudoCordinate.push_back(make_pair(coordinate[0].first,coordinate[0].second)) ;
  file1<<coordinate[0].first<<" "<<coordinate[0].second<<endl;
  prevDist.push_back(make_pair((coordinate[1].first - coordinate[0].first),(coordinate[1].second - coordinate[0].second))) ; 
  count2++;
    for(int i = 2 ; i < counter ; i++) {
       if((coordinate[i].first != coordinate[i-1].first)&&(coordinate[i].second != coordinate[i-1].second))
        { 
        	prevDist.push_back(make_pair((coordinate[i].first - coordinate[i-1].first),(coordinate[i].second - coordinate[i-1].second))) ;
            count2++;
        }
       if(((prevDist[count2].first*prevDist[count2-1].first)<0)||((prevDist[count2].second*prevDist[count2-1].second)<0)) {
       	 pseudoCordinate.push_back(make_pair(coordinate[i].first,coordinate[i].second)) ;
         file1<<coordinate[i].first<<" "<<coordinate[i].second<<endl;
       }
             
     }
   pseudoCordinate.push_back(make_pair(coordinate[counter-1].first,coordinate[counter-1].second));
   file1<<coordinate[counter-1].first<<" "<<coordinate[counter-1].second<<endl;
   file1.close();
//_______________________________________________________________    
#endif
//******** writing the coodinates to the file ********

#ifdef coord_refactor
// used for character segmentation using diagonals 
  ofstream file1("letter_factor.txt") ;
  float dist ;
  int pseudocounter = 0 ;
  pseudoCordinate.push_back(make_pair(coordinate[0].first,coordinate[0].second)) ;
  pseudocounter++ ;
  file1<<coordinate[0].first<<" "<<coordinate[0].second<<endl ;
  // removing unessecary close coordinates 
  for(int i = 1 ; i < counter ; i++)
  {
    /*dist = sqrt(pow((coordinate[i].first - pseudoCordinate[pseudocounter-1].first),2)+pow(( coordinate[i].second - pseudoCordinate[pseudocounter-1].second ),2 )) ;
    if(dist > dist_thresh)
      */
    if((abs(coordinate[i].first - pseudoCordinate[pseudocounter-1].first)>dist_thresh)&&(abs(coordinate[i].second - pseudoCordinate[pseudocounter-1].second)>dist_thresh))
    {
       pseudoCordinate.push_back(make_pair(coordinate[i].first,coordinate[i].second)) ; 
       pseudocounter++ ;
       file1<<coordinate[i].first<<" "<<coordinate[i].second<<endl;
    }
  }
  file1.close();  

#endif
    

//____________________________________________________   
 return 0 ;
 }
#include <iostream>
#include <fstream>
#include <cstring>
#include <queue>
#include <vector>
#include <cmath>


using namespace std ;

int main()
{
 
 string str ;
 int numx , numy ;
 vector< pair<int , int > > coordinate ;
 
 ifstream file("word-do.txt");
 ofstream file1("intugine.txt");
 int counter ;
 while(!file.eof()) {
       file>>str ;
       if(str[0]== 'd' || str[0] == '=')
       	continue ;
       if(str[0] == ',')
       	break ;
       //cout<<str.size() <<endl;
       counter = 0 ;

       for(int i = 0 ; i < str.size() ; i++)
       {
       	if(str[i]=='.'&&counter==0)
       		{ 
       		  if(str[i-3] > 48 && str[i-3] < 57)
       			numx = (str[i-3]-48)*100 + (str[i-2]-48)*10 + (str[i-1]-48) ;
       		  else
       			numx = (str[i-2]-48)*10 + (str[i-1]-48) ;
       	      counter = 1 ;
       	    }
       	else
       	  if((str[i]=='.')&&counter==1)
       		{ 
       		  if(str[i-3] > 48 && str[i-3] < 57)
       			numy = (str[i-3]-48)*100 + (str[i-2]-48)*10 + (str[i-1]-48) ;
       		  else
       			numy = (str[i-2]-48)*10 + (str[i-1]-48) ;
       
            }
        }

       // numx = (str[1]-48)*100 + (str[2]-48)*10 + (str[3]-48) ;
       // if((str[5] - 48 ) >= 5)
       // 	numx++ ;
       // numy = (str[9]-48)*100 + (str[10]-48)*10 + (str[11]-48) ;
       // if((str[13] - 48 ) >= 5)
       // 	numy++ ;
       cout<<numx<<" "<<numy<<endl;
       file1<<numx<<" "<<numy<<endl;

    }
 file.close();   
 file1.close();





 return 0 ;	
}
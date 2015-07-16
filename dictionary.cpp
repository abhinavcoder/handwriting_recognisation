#include <iostream>
#include <fstream>
#include <cstring>

using namespace std ;

int main()
{
 string str , finalstr , initialstr ;
 int couter , finalstr_size = 0  ; 
 ifstream file2("tess_output.txt");
 char ch , end = '\0' ; 
 bool found ;

 file2>>initialstr;
 file2.close();
 ofstream file3("tess_output.txt");
 for(int i = 0 ; i < initialstr.size() ; i++)
 {  
 	found = false ;
    ifstream file1("dictionary.txt");
    while(!file1.eof()) { 
        file1>>ch ; 
        
        if(initialstr[i]==ch)
        {
        	
        	found = true ;
        	break ;
        }

    }
    file1.close();

    if(found==false)
    {
    	finalstr[finalstr_size] = initialstr[i] ;
    	file3<<finalstr[finalstr_size];
    	cout<<finalstr[finalstr_size];
    	finalstr_size++ ;
    }   

 }
 cout<<endl;
 file3.close();
 

 return 0 ;	
}
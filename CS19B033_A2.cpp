#include <cmath>
#include <climits>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


class Matrix{
    public:
    int **p;             //double pointer to create matrix
    int rows,col;
    void create(int n,int m){
        rows = n;
        col = m;
        p = (int**)malloc(rows*sizeof(int*));            // creating an array of size n
        for(int i=0;i<n;i++){
            p[i]=(int*)malloc(col*sizeof(int));          // creting m sized arrays for each n
        }  
        
    }
    void read(){
        int i=0;
        while(i<rows){
            int j=0;
            while(j<col){
                cin>>p[i][j];            // storing elements of matrix in matrix
                j++;   
            }
            i++;
        }
    }
    int Binarysearch(int a,int b){      //finding the index for value :a in bth row
        int i =b;
        int middleV;
        int first;
        first=0;
        int last;
         last=col-1;
        if(p[i][col-1]<=a)
            //if the element to find is greater than last element of given row
            return last;
        if(p[i][first]>a)
            //if the element to find is less than first element of given row
            return -1;
        while(first<=(col-1)){
            //iterating
             middleV = first + (last-first)/2;
            if(p[i][middleV]<=a && p[i][middleV+1]>a){   
                //if we found the given value at middleV,then check at next poisiton as it is equal to middleV
                return middleV;
            }
                if(p[i][middleV]>a){
                    last = middleV-1;                              
            }
            
            if(p[i][middleV+1]<=a){
                first = middleV+1;
            }
        }
        
        return middleV;        //index
    } 
    void matrixsearch(int c){       // search the element in row sorted matrix and return (i,j)
        int i=0;  
        int x=0;  // count  the number of times the given value is repeated
        while(i<rows){

            int j=0;
            while(j<col){
                if(p[i][j]==c){
                   std::cout<<i<<" "<<j<<"\n";
                    x++;
                    break;
                }
                j++;
            
            }
            i++;  
            if(x==1)
                break;
        }
        if(x==0)
           std::cout<<"-1 -1"<<"\n";
    }    
};


class Matrixmedian : public Matrix{       //inheritance-> base class: matrix derived class: matrixmedian
    public:
    int upperbound (int,int);   //to find the upperbound
    int findmedian();           // to find median
};
   
int Matrixmedian::upperbound(int d, int e){      
        int index = Binarysearch(d,e);     //using binarysearch finding index of upperbound
        return index;                    
    }

int Matrixmedian::findmedian(){
        int minimum=  INT_MAX;                         //INT_MAX : 2147483647;
        int maximum = INT_MIN;                         //INT_MIN : -2147483647;
        int first =0;
        int last = col-1;
        int avg = (1+rows*col)/2;    
        int i=0;
        while(i<rows){
            if(p[i][first]<minimum){              // INT_MAX : the maximum value of int
                minimum = p[i][first];           //finding the minimum element in given matrix
            }
            if(p[i][last]>maximum){  
                //INT_MIN : the minimum value of int 
                maximum = p[i][last];
                //finding the maximum element in given matrix
            }
            i++;
        }
        
        while(minimum<maximum){
            int middle = minimum+ (maximum-minimum)/2;      
            // middle element in between min and max values
            int  num =0;
            int it=0;
            while(it<rows){
                num+= upperbound(middle,it)+1; 
                //finding the num of elements which are less than middle element 
                it++;
            }
            if(num>=avg){
                maximum = middle;
            }
            if(num<avg){ 
                minimum = middle+1;
            }
        }
        return minimum;
    }



int main() {
    int n;       // no. of rows
    int m;            //no. of columns
    cin>>n>>m;
    Matrixmedian m1;     // creating a matrix from derived class from base class: Matrix
    m1.create(n,m);      //creating a 2d-array 
    m1.read();             // reading the elements of matrix
    int Q;                //queries
    cin>>Q;
    string s;             //string to read 
    int i =0;
    while(i<Q){
        cin>>s;
        if(s.compare("BS")==0){                           //compare==0 : strings are equal 
            int x;
            cin>>x;
            int k;
            cin>>k;
           std::cout<<m1.Binarysearch(x,k)<<"\n";          // calling binarysearch
        }
        if(s.compare("MS")==0){
            int k;
            cin>>k;
            m1.matrixsearch(k);                     //calling matrixsearch 
        }
        if(s.compare("Median")==0){                                    
            std::cout<<m1.findmedian()<<"\n";          //calling out median function
        }
        i++;
    }
    
    
    
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    return 0;
}
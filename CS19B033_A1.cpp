#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class MATRIX{
    public :
    void SPSUM();             //sum of each row of the new matrix     
    void MOD();               //product of the elements
    int** MRS(int);           //matrix right shift
    int** MADD();             // special matrix addition 
    void create(int);         // creates matrix of size int
    void read();              // reads the elements of matrix
    int** ret();              // returns 2d array
    private:
    int **matrix;              // double pointer
    int rc;                    // no. of rows
};   

void MATRIX::create(int n){       
    rc = n;                          //  no. of rows/columns are being stored 
    matrix = (int**)malloc(rc*sizeof(int*));      //creating 2d array dynamically  
    for(int i=0; i<rc;i++){
        matrix[i]= (int*)malloc(rc*sizeof(int));
    }
}
void MATRIX::read(){
    for(int i=0;i<rc;i++){
        for(int j=0;j<rc;j++){
          cin>>matrix[i][j];               // storing the elements in 2d array
        }
    }
    
}
void MATRIX::SPSUM(){
    for(int i=0;i<rc;i++){
        int sum =0;
        for(int j=0;j<rc; j++){
            if((i+j)%2==0){                //if rowind+colind = even-> no swap is done
                sum = sum+ matrix[i][j];
            }
            else{                          // if rowind+colind = odd -> swap is done
                sum = sum+matrix[j][i];
            }
        } 
        if(i==rc-1)                       // end of the row
            cout<<sum<<endl;
        else
            cout<<sum<<",";              //printing the sum of the elements of row untill the end of the row
    }
    
}

void MATRIX::MOD(){
    long long mul;
    mul = 1;
    int i =0;
    while(i<rc){
        int Ele = matrix[i][0];          //assigning the first element of row
        int j =1;
        while(j<rc){
            if(i%3==0){                      
                Ele = max(Ele,matrix[i][j]);   // finding the max element in the given row
            }
            else if(i%3==1){
                Ele = min(Ele,matrix[i][j]);        // finding the  min element in the given row
            }
           else{
                Ele = Ele+ matrix[i][j];           // first summing them to find the floor value
            }
            j++;
        }
        if(i%3==2){
            mul = mul*(Ele/rc);              //  flooor value
        }
        else{  
            mul = mul*Ele;         
        }
        i++;
        
    }
    cout<<mul<<endl;         // printing the result
    
}
int** MATRIX::MRS(int k){        
    int **m = (int**)malloc(rc*sizeof(int*));
    for(int i=0;i<rc;i++){
        m[i]= (int*)malloc(rc*sizeof(int));
    }
    for(int i=0;i<rc;i++){
        for(int j=0;j<rc;j++){
            int key = (j+k)/rc;
           int newi = (key+i)%rc;            
           int newc = (j+k)%rc;
            m[newi][newc] = matrix[i][j];    
        }
    }
    return m;
    
}

int** MATRIX::MADD(){
    int **m = (int**)malloc(rc*sizeof(int*));
    for(int i=0;i<rc;i++){
        m[i]=(int*)malloc(rc*sizeof(int));
    }
    int i=0;
    while(i<rc){
        for(int j=0;j<rc;j++){
            m[i][j]= matrix[j][i];            // elements got swapped here
        }
        i++;
    }
    return m;
}
int** MATRIX::ret(){    // returns the given original matrix
    return matrix;
}



void Matrixadd(int **X, int **Y, int n){           // adds two 2d arrays
    int i =0;
    while(i<n){
    int j =0;
        while(j<n){
            cout<<X[i][j]+Y[i][j]<<" ";       // printing the sum of two matrices
            j++;
        }
        i++;
    cout<<endl;
    }
}


    


int main() {
    
    int q;       // no. of queries
    int n;       //no. of rows or columns
    cin>>q;
    cin>>n;
    
    MATRIX q1;           
    MATRIX q2;            
    q1.create(n);               // creating a matrix of size n
    q2.create(n);
    q1.read();
    q2.read();                 // reading the elements of matrix
    string ch;
                    
    int i =0;
    while(i<q){
        cin>>ch;
        if(ch=="SPSUM"){       
            q1.SPSUM();
        }
        else if(ch=="MOD"){
            q1.MOD();
        }
        else if(ch=="MRS"){
            int k;
            cin>>k;
           int** A = q1.MRS(k);
           int** B = q2.MRS(k);
            Matrixadd(A,B,n);
            
        }
        else if(ch=="MADD"){
            int num;
            cin>>num;
            if(num==1){
               int** A = q1.MADD();
               int ** B = q2.ret();
                Matrixadd(A,B,n);
            }
            else{
              int**  A = q1.ret();
              int**  B = q2.MADD();
                Matrixadd(A,B,n);
            }
        }
        i++;
    }  
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    return 0;
}
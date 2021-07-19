#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
template <class T> class Vector{
    private:
    size_t currentCapacity;        //stores currentcapacity
    size_t currentSize;            //stores currentsize
    T* vec;                        //creating dynamic array
    public:        
      Vector(size_t c){
        currentCapacity = c;  
        currentSize =0;
        vec = new T[currentCapacity];    //creating array with size = currentcapacity
    }
      Vector(size_t c, T x){
          //This function creates dynamic array and stores x as all its elements
        currentSize =0;
        currentCapacity=c;
        vec = new T[currentCapacity];
        for(size_t i=0;i<currentCapacity;i++){
            vec[i]= x;
            currentSize++;                            //size increases as we are storing elements
        }
        
    }
      Vector(){
          //This function creates dynamic array of size 1
        currentCapacity =1;
        currentSize=0;
        vec = new T[currentCapacity];    
    }
    void deletememory(){
        delete[]vec;
       
   } 

    size_t capacity();
    size_t size();
    void push(T);
    void pop();
    T front();
    T back();
    void Print();
    T operator[](size_t);
    void sort(size_t, size_t);
    protected:
    size_t partition(size_t, size_t);
};

template <class T>
    size_t Vector<T>::capacity(){
        //This function returns the capacity of array at that instant
        return currentCapacity;
    }
template <class T>
    size_t Vector<T>::size(){
        //This function returns the size of array at that instant
        return currentSize;    
    }

template <class T>
    void Vector<T>::push(T x){
        //This function pushes element x into the array, if the array is completely filled then we have to create new array of double capacity and store at first unsigned place
       
       if(currentSize==currentCapacity){
            T* old = new T[currentCapacity];       //array to store the elements of previous array
            size_t c = currentCapacity;
            for(size_t i=0;i<c; i++){
                old[i]= vec[i];      
            }
            currentCapacity = 2*currentCapacity;   // doubling capacity
            delete[]vec;                              //deleting previous array
            vec = new T[currentCapacity];         //creating another array with double capacity
            for(size_t i=0;i<c;i++){
                vec[i] = old[i];       //storing all the old elements in new array
            }
            delete[]old;                       //deleting the old array
        }  
        vec[currentSize] = x;         // element is added at unsigned position
        currentSize++;               //size is increased
    }
template <class T>
    void Vector<T>::pop(){
        currentSize--;
    }
template <class T>
    T Vector<T>::front(){
        //This function returns the first element in an array
        if(currentSize==0){
            //if the array is empty return -1
            return -1;
        } 
        else{
            return vec[0];
        }
    }
template <class T>
    T Vector<T>::back(){
        //This function returns the last element in the array
        if(currentSize==0){
            //if the array is empty return -1
            return -1;
        }
        else{
            //return last element
            return vec[currentSize-1];
        }
        
    }
template <class T>
    T Vector<T>::operator[](size_t index){
        //This function returns ith element in array
        if(index>=currentSize){  
            //if the index is greater or euqal than the total elements ie. unsigned then return -1
            return -1;
        }
        else{
            return vec[index];    //return ith element
        }
        
    }
template <class T>
    void Vector<T>::sort(size_t low, size_t high){
        //This function sorts the array in ascending order taking arguements low and high
        //divide and conquer method
        if(low<high){
            size_t pindex = partition(low,high);
             sort(low,pindex);
            sort(pindex+1,high);
        }   
    }
template <class T>
    size_t Vector<T>::partition(size_t a,size_t b){
        // This function sorts the pivot element and returns the index 
        T pivot = vec[a];      //starting element is taken as pivot
        size_t i =a;           // i=0;
        T temp;   //used for swapping
        size_t j = a+1;
        while(j<=b){
            if(vec[j]<pivot){        
                i++;
                //swapping these two elements
                temp = vec[i];
                vec[i] = vec[j];
                vec[j] = temp;    
            }
            j++;
        }
        temp = vec[i];
        vec[i] = vec[a];
        vec[a] = temp;
        return i; 

    }
template <class T>
    void Vector<T>::Print(){
        //This function prints the elements of an array
        size_t i=0;
        while(i<currentSize){
            cout<<vec[i]<<" ";
            i++;
        }
        cout<<endl;
        
    }

int main() {
    string vect;
    string s = "vector";
    int stringlength;           // the length of complete string in a line
    int vlen = s.size();        // length of string vector
    getline(cin,vect);           // reading the complete string on a line
    stringlength = vect.size();     //finding the size of complete string
    int m;
    int n;
    m = -1;
    n = -1;
    Vector<int>V;               //defining the vector
    for(int i=vlen;i<stringlength;i++){     // we are reading the charectors after vector string
        if(vect[i] ==' '){                
            //if there is only just space after vector vector()is implemented 
            i++;
            if(i>=stringlength)
                break;
            m = 0;
            while(i<stringlength && vect[i]!=' '){   // after space if there is an element other than space charector
                m = m*10 + vect[i]-'0';   //string value is converted to digit
                i++;  
            }
            if(i<stringlength){            
                i++;
                n = 0;
                while(i<stringlength){        //after reading the number check for the another digit
                    n = n*10 + vect[i] -'0';   //string value is converted to digit
                    i++;
                }
            }
            
        }
          
    }

    
    if(m== -1 && n== -1){     
        V = Vector<int>();   // no number is read in string 
    }
    else if(m!=-1&& n!=-1){
        V = Vector<int>(m,n);   // both numbers are  read
    }
    else{
        V = Vector<int>(m);      // only one  number is read after string "vector"
    }
    
     
    int Q;                    
    cin>> Q;
    string ch;
    for(int i=0;i<Q;i++){
        cin>>ch;
        if(ch.compare("push")==0){
            int n;
            cin>>n;
            V.push(n);
        }
        if(ch.compare("pop")==0){
            V.pop();
        }
        if(ch.compare("front")==0){
            int n;
            n = V.front();
            cout<<n<<endl;
        }
        if(ch.compare("back")==0){
            int n;
            n = V.back();
            cout<<n<<endl;
        }
        if(ch.compare("element")==0){
            size_t n;
            cin>>n;
           cout<<V[n]<<endl;
        }
        if(ch.compare("capacity")==0){
            cout<<V.capacity()<<endl;
        }
        if(ch.compare("size")==0){
            cout<<V.size()<<endl;
        }
        if(ch.compare("sort")==0){
            size_t x=0;
            size_t y = V.size();
            V.sort(x,y-1);
            V.Print();
        }
    }
    
    V.deletememory();
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    return 0;
}

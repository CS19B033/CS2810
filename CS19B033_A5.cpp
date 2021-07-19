#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;

class BloomBrain{
    private:
    int *arr;                               //creates an array which stores seraphic numbers
    bool *occ;                              
    //bool array which stores true or false
    // occ[i]=true -> the room i is occupied 
    //occ[i] = false -> the room is empty
    int capacity;                          // gives the total size of array
    public:
    BloomBrain(int rooms){               //constructor which creates two arrays
        capacity = rooms;
        arr = new int[capacity];
        occ = new bool[capacity];
        int i=0;
        while(i<capacity){
            occ[i] = true;         //initializing all the rooms are occupied
            i++;
        }   
    }
    void destructor(){
        delete[]arr;
        delete[]occ;
        
    }
    
    long long update(int*);          
    void join(int);
    void leave(int);
    int occupied();
    int play();
    long long inversioncount(int*,int,int);
    long long merging(int*,int,int,int);
    int seraphicsum(int,int);
    int Sum(int,int,int);
    int findmax(int,int,int);
    int max2(int,int);
   
};
int BloomBrain::max2(int a, int b){
    //This function takes two arguements and returns the max element among those two values
    if(a>b)
        return a;
    else
        return b;
    
}
int BloomBrain::findmax(int a,int b,int c)
    //This function takes three arguements and returns the max element among those three values
{
    int x = max2(a,b);        
    return max2(x,c);
}

int BloomBrain::Sum(int low, int middle, int high)
{
    int sum =0;              
    int left_sum = INT_MIN;               //finding the sum in left subarray low to middle
    for(int i = middle;i>=low;i--){
        sum = sum+arr[i];
        if(left_sum<sum){
            left_sum = sum;
        }
    }
    sum =0;
    int Right_sum = INT_MIN;               //finding the sum in right subarray from middle+1 to high
    for(int i=middle+1;i<high+1;i++){
        sum = sum+arr[i];
        if(Right_sum<sum){
            Right_sum = sum;
        }
    }
    
    return findmax(Right_sum+left_sum,left_sum,Right_sum);  //finding the max element among these
    
    
}

int BloomBrain::seraphicsum(int low,int high)
{
    if(low==high){      //if the arary has only one element, the seraphic number will be that element itself
        return arr[low];
    }
    int middle = low + (high-low)/2;    //finding the middle element and dividing the array into two parts
    
    return findmax(seraphicsum(low,middle),seraphicsum(middle+1,high),Sum(low,middle,high));
     //seraphicsum(low,middle) ->maximum subarray in left half  
    //seraphicsum(middle+1,high)->maximum subarray in right half
    //Sum(low,middle,high)->finds the sum when the both  divided are merged
    
}

int BloomBrain::play(){
    //This function finds the minimum seraphic number the guru must have for not losing
    int num = seraphicsum(0,capacity-1);      //calculates the seraphic number the guru must have
    return num;
}
long long BloomBrain::merging(int *p, int low,int middle, int high)
{
    long long count = 0;       //counting total number cross inversions
    int  q[capacity];            //array stored the resultant array after merge sort
    int a= low;                          // index for left subarray       
    int b = middle;                     //index for right subarray
    int c = low;
    
    while(a<middle && b<=high){
        if(p[a]>p[b]){   
            //if low index has higher value then all the elements that are at the right to given element are greater than that element in higher index, as subarray has been already sorted
            
            q[c] = p[b];   
            b++;               
            count = count + (middle-a);         //count value is increased by number which are from i to middle
        }
        else{
            q[c] = p[a];  
            a++;
        }
        c++;
    }
    
    if(a==middle){   
        //if the pointer pointing to left subarray reaches to middle then we just have to copy the remaining elements in right subarray in array q,as they are already been sorted 
        while(b<=high){
            q[c] = p[b];         //copying remaining elements in q
            b++;
            c++;
        }
    }
    else{
        while(a<middle){           //we can copy the elements from index to middle into the array 
            q[c] = p[a];
            a++;
            c++;
        }
    }
    for(int i=low;i<=high;i++){       // copy the elements of merged array into the array p
        p[i] = q[i];
    } 
   // delete[]q;
  
    return count;

    
}

long long BloomBrain::inversioncount(int *p, int low, int high)
    //This function finds the inversion count using divide and conquer method
{
    long long count = 0;
    if(low<high){       //Dividing the array into two parts and adds them 
    int middle  = (high+low)/2;   
        // divide the array into two parts from low to middle and from middle+1 to high  
     count += inversioncount(p,low,middle); //inversion count in left subarray
     count += inversioncount(p,middle+1,high); // inversion count in right subarray
     count += merging(p,low,middle+1,high); //number of inversions in merging
    }
    
    return count;     
        
}

long long BloomBrain::update(int array[]){
    //This function takes an array as input and finds the number of qualitytalks possible
    for(int i=0;i<capacity;i++){
        //copying the input array into the array which was defined in class
        arr[i] = array[i];
    }
    int non_empty = occupied();        //finding the number of occupied rooms
    int *p = new int[non_empty];  
    //creating a new array to copy all the seraphic numbers with room occupied 
    int j=0;
    int i=0;
    while(i<capacity){
        if(occ[i]==true){          //if the room is occupied
            p[j] = arr[i];         //then the seraphic number is copied
            j++;
        }
        i++;
    }
    long long qtalks = inversioncount(p,0,non_empty-1); 
    delete[]p;
    return qtalks;
     
}

void BloomBrain::join(int a)
    //This function adds new member with seraphic value a in last emptied room
{
    for(int i=capacity-1; i>=0;i--){  //finds the last emptyied room from last room
        if(occ[i]==false){     // he joins if it is empty
            arr[i] = a;         
            occ[i] = true;      //the room is marked as occupied
            break;             //if found coming out of loop
        }
    }
        
}

void BloomBrain::leave(int a)             
    //This function takes room number as input and makes that room empty(occ[a]==false)
{
    if(occ[a]==true){     //if the room isnt empty
        occ[a] = false;
        arr[a] =0;
    }  
    else{                  //if the room is empty we are not emptying any room
        return;
    }
}

int BloomBrain::occupied(){
    //This function gives the number of rooms are occupied.
    int count =0;
    for(int i=0;i<capacity;i++){
        if(occ[i]==true){           //if the room is occupied we are increasing the count value
            count++;
        }
        
    }
    return count;               //this count gives the total rooms which are occupied
}


int main() {
    int N;                                             //no. of elements in array
    int Q;                                             //no. of queries
    cin>>N;
    cin>>Q;
    BloomBrain seraphic(N);                           // creating a class of name seraphic
    string ch;                                        // input string
    for(int i=0;i<Q;i++){
        cin>>ch;
        if(ch.compare("update")==0){              
            int array[N];                             //creating an array for reading             
            for(int i=0;i<N;i++){
                cin>>array[i];
            }
            long long output = seraphic.update(array);
            cout<<output<<endl;
        }
        if(ch.compare("join")==0){
            int x;
            cin>>x;
            seraphic.join(x);
        }
        if(ch.compare("leave")==0){
            int idx;
            cin>>idx;
            seraphic.leave(idx);
        }
        if(ch.compare("occupied")==0){
            cout<<seraphic.occupied()<<endl;
        }
        if(ch.compare("play")==0){
            int x =seraphic.play();
            cout<<x<<endl;
        }
    } 
    seraphic.destructor();
    
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    return 0;
}

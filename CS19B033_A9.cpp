#include <bits/stdc++.h>


using namespace std;

template <class T>class Graph{
    private :
    int num;
    T** adjacency;

    public :
    
    void create(int a){    //creating matrix of data type (int, double)
        num = a;
        adjacency = new T*[num];
        int i =0;
        while(i<num){
            adjacency[i] = new T[num];
            i++;    
        } 
        for(int i=0;i<num;i++){
            for(int j=0;j<num; j++){
                adjacency[i][j] = 0;
            }
        }    
    }
    
    void addedge(int,int, T); 
     T edge(int, int);
    
    
};

template<class T>
void Graph<T>::addedge(int source, int destination, T weight){
     adjacency[source][destination] = weight;    //adding edge of given weight in matrix
}
template<class T>
T Graph<T>::edge(int i, int j){    //This function returns the element in matrix.
    return adjacency[i][j];
}



class Conversions{
    private:
    int v;               //total colours
    int Nu;              //total currencies
    Graph<int>col;         // to store adjacent colours    col[i][j] = 1 : we can convert  0 : cannot
    Graph<double>N;        // matrix contains exchange rates between countries
    int *arr;           //colour associated with currency i
    int count =0;
    public:
    void Create_col(int num){
        v = num;
        col.create(v);
       // for(int i=0;i<v;i++){
        //    col.addedge(i,i,1);     //there is going to be a conversion between two same countries
        //}
    }
    
    void ADDEDGE_col(int a, int b){
        col.addedge(a,b,1);         //undirected graph
        col.addedge(b,a,1);         //adding by both sides
    }
    
    void Create_N(int num){            
        Nu = num;
        N.create(Nu);
        arr=  new int[Nu];    
    }
    void ADDEDGE_N(int a, int b, double w){
        w = -1*log2(w);
        N.addedge(a,b,w);                  //currency conversion values are stored in -log value 
    }
    void update(int *array){              //arr will be the array of colours of currencies i
        for(int i=0;i<Nu;i++){
            arr[i] = array[i];
        }
    }
    
 

    void conversion(int a, int b, int c){
        double *distance;
        distance = new double[Nu];
        int i=0;
        while(i<Nu){
            distance[i] = INT_MAX;
            i++;
        }
        
        distance[a] = 0;
        
        for(int i= 1; i<=Nu-1; i++){
            for(int j=0;j<Nu; j++){
                for(int k=0; k<Nu; k++){
                    if((col.edge(arr[j],arr[k])) || arr[j]==arr[k]){
                        if(distance[j]!=INT_MAX && distance[j] + N.edge(j,k) < distance[k]){
                            distance[k] = distance[j] + N.edge(j,k);
                        }   
                    }   
                }    
            }   
        }
        
        
        double x = distance[b];
        
        for(int j=0; j<Nu; j++){
            for(int k=0; k<Nu; k++){
                if((col.edge(arr[j],arr[k])) || arr[j]==arr[k]){
                    if(distance[j]!=INT_MAX && distance[j]+ N.edge(j,k) <distance[k]){
                        distance[k] = distance[j] + N.edge(j,k);    
                    }    
                }  
            }
        }
        
        if(x==INT_MAX){
            cout<<"-1"<<endl;
        }
        else if(x!= distance[b]){
            cout<<"INF"<<endl;
        }
        else{
             cout<<fixed<<setprecision(3)<<((double)pow(2,-distance[b])*c)<<endl;   
        }   
        
    }       
};

int main() {
    
    int C;
    cin>>C;                           //no. of colours
    int m;
    cin>>m;
    
    Conversions obj;
    obj.Create_col(C);
    for(int i=0;i<m;i++){
        int a;
        int b;
        cin>>a>>b;
        obj.ADDEDGE_col(a,b);   
    }
    
    int N;              // total number of currencies
    cin>>N;
   // Conversions obj2;
    obj.Create_N(N);
    
    int *array;
    array = new int[N];
    for(int i=0;i<N;i++){
        cin>>array[i];    
    }
    
    obj.update(array);
    
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            double x;
            cin>>x;
            obj.ADDEDGE_N(i,j,x);    
        } 
    }
    
  
    int q;
    cin>>q;
    for(int i=0; i<q; i++){
        int s,t;
        float  X;
        cin>>s>>t;
        cin>>X;
        obj.conversion(s,t,X);
        
    }
       
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    return 0;
}

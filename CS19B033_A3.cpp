#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

 struct node{        //linkedlist implementation
    int num;
     struct node *link;
};

class stack{              //this is used for stack implementations
    struct node* top;     //pointer pointing to top node
    public:
    void create();          
    void Push(int);         //pushing into the stack
    int Pop();              //pop the last element inserted in stack
    int Top();              //return the last element
    int isempty();
};
void stack::create(){
    top= NULL;
}

void stack::Push(int a){      
    struct node *ptr = new struct node;      //creating new node and store the data
    ptr->num= a;
    ptr->link = top;
    top = ptr;    
}
int stack::isempty(){                        //finding stack is empty
    if(top==NULL){  
        return 1;
    }
    else{
        return 0;
    }
}

int stack::Top(){
    if(isempty()==1)               // if stack is empty
        return -1;
    else
        return top->num;           //returns top element of stack
}
int stack::Pop(){ 
    if(isempty()==1){                //if stack is empty
        return -1;
    }
    else{
        struct node *ptr = top;          
        int data= top->num;           //storing the data in stack in data
        top = top->link;
        delete(ptr);            //deleting the pointer
        return data;
    }   
}



class graph{                 //used for graph implementation
    
    private:
    int n;                           //no. of vertices
    int **adjacency;                   //adjacency matrix
    public:
    void constructor(int);         
    bool cyclic(int,int*,int);
    int  detectcycle();
    void operator+=(pair<int,int>);
    void operator-=(pair<int,int>);
    bool reach(pair<int,int>);
    int components();
};

void graph::constructor(int n){
    // creating adjacency matrix and initializing all elements as 0
        this->n = n;
        adjacency = (int**)malloc(n*sizeof(int*));
        for(int i=0;i<n;i++){
            adjacency[i]= (int*)malloc(n*sizeof(int));
            for(int j=0;j<n;j++){
                adjacency[i][j]= 0;
            }
        }
    }
void graph::operator +=(pair<int,int>add){             //operator overloading   
             //if the edge is not there
        adjacency[add.first][add.second]=1;
        adjacency[add.second][add.first]=1;
        
}

void graph::operator -=(pair<int,int>del){ 
      
        adjacency[del.first][del.second] = 0;
        //the edge is deleted on both sides in matrix,as it is bidirectional
        adjacency[del.second][del.first] = 0;
    
}
int graph::detectcycle(){         //to check is cycle present in graph or not
    int *vis = new int[n];
    //noting the vertices or nodes that have been visited
    int i=0;
    while(i<n){
        vis[i]=0;    //initializing all vertices hasn't been read
        i++;
    }
    for(int i=0;i<n;i++){
        if(vis[i]!=1)       //if we havent visited the node, then DFS is called
            if(cyclic(i,vis,-1)==true)
                return 1;         
        
    }
    return 0;
    
}
bool graph::cyclic(int u,int* vis,int p){

    vis[u]=1;      //given node is visited
    for(int i=0;i<n;i++){
        if(adjacency[u][i]!=0 && i!=p){  //if the node has an edge and the visited node is not the parent
            if(vis[i]!=0){
                return true;
                break;
            }
            else{
                cyclic(i,vis,u);
            }
        }
    }
            
        
    return false;
}
            
int graph::components(){   // finds no. of connected components
    stack x;      //creating stack
    x.create();
    bool *vis = new bool[n];
    for(int i=0;i<n;i++){
        vis[i] = false;      // all the nodes or vertices are not visited
    }
    int comp;
    comp=0;       //stores the no. of connected components in the given graph
    for(int i=0;i<n;i++){
        if(vis[i]!=true){       //if the given node is not visited
        comp = comp+1;
            x.Push(i);
            while(x.isempty()!=1){
                int p = x.Pop();           
                vis[p]= true; 
                //after the vertex is popped, it is stored in visited array to indicate it is visited
                
                int j=0;
                while(j<n){
                    if(adjacency[p][j]==1 &&vis[j]==false)    
                    //if the vertex is not visited,then it is pushed into stack
                        x.Push(j);
                    j++;
                    
                    }        
                }    
        }    
    }
    return comp;
    
}
bool graph::reach(pair<int,int>reach){    //to find there is a path between two nodes/vertices 
    stack x;
    bool *vis= new bool[n];
    for(int i=0;i<n;i++){
        vis[i]=false;         //all the vertices are marked as unvisited
    }
    x.Push(reach.first);           //the first vertex is pushed into the stack
    vis[reach.first] = true;
    while(x.isempty()!=1){
        int v;
        v = x.Pop();
        vis[v]= true;
        if(v==reach.second)    //if the node visited is the other vertex/node 
            return true;
        for(int j=0;j<n;j++){
            if(adjacency[v][j]==1 && vis[j]==false){
                x.Push(j);
            }
        }
    }
    return false;    
}


int main() {

    int Q;
    cin>> Q;
    string s;       //string to read the operation to be performed
    stack st;       // stack implementations to be done
    st.create();
    for(int i=0;i<Q;i++){
        cin>>s;
        if(s.compare("push")==0){
            int x;
            cin>>x;
            st.Push(x);
        }
        if(s.compare("pop")==0){
            cout<<st.Pop()<<endl;
        }
        if(s.compare("top")==0){
            cout<<st.Top()<<endl;
        }
        if(s.compare("empty")==0){
            cout<<st.isempty()<<endl;
        }
        
    }
    
    
    int n;
    cin>>n;
    int m;
    cin>>m;
    
    graph G;
    G.constructor(n);
    
    for(int i=0;i<m;i++){
        cin>>s;
        if(s.compare("add")==0){
            pair<int,int>p;
            cin>>p.first;
            cin>>p.second;
            G+=p;
        }
        if(s.compare("del")==0){
            pair<int,int>p;
            cin>>p.first;
            cin>>p.second;
            G-=p;
        }
        if(s.compare("cycle")==0){
            cout<<G.detectcycle()<<endl;
        }   
        if(s.compare("components")==0){
            int k = G.components();
            cout<<k<<endl;
        }
        if(s.compare("reach")==0){
            pair<int,int>p;
            cin>>p.first;
            cin>>p.second;
            cout<<G.reach(p)<<endl;
        }
    }
    
    
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    return 0;
}

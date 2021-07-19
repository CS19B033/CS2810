#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include <utility>
#include <climits>

using namespace std;

template<class T>class Graph{             //class template
    
    int vertex;                           //This keeps the count of all vertices in graph
    vector<pair<int,T>>*adjacency;        //creating an array of vectors, in which vector contains pair of(int,T)
    bool *array;                          //creating boolean array for keeping the count of visited or non visited vertices
    int *dist;                          //array to store the distances between vertices
    
    
    public:
    Graph(int num){                           //constructor
        vertex = num;
        adjacency = new vector<pair<int,T>>[vertex];       //array of vectors
    }
    
    void addedge(pair<int,T>a,int source){
        //This function adds this pair to the adjacency list by comparing weights of newly adding vertex with already been added vertices and adds them according to the order.
        int count =0;
        auto i = adjacency[source].begin();    //auto initializes the value with type to i based on the output of the function.
        while(i!= adjacency[source].end()){   // running until the end of the vector   
            if((*i).second==a.second )    //if weights are equal ,check for vertex
            {
                if((*i).first>a.first){   //if newly adding vertex has less value, we insert it at that position.
                    adjacency[source].insert(i,a);  //imserts
                    count++;
                    break;     //breaks the loop once we find the correct position
                }
            }
            else{
                if((*i).second > a.second){     //if weights are not equal and compares them.  
                    adjacency[source].insert(i,a);
                    //inserting the pair at the position where it found the more weighted vertex
                    count++;
                    break;
                }
                
            }
            i++;
        }
        
        if(count==0)       //if there is no vertex, we add the pair at the last position
            adjacency[source].push_back(a);
    }
    
    void ADDV();
    void ADDE(int,int,T);
    void DelE(int,int);
    void BFS(int);
    void SSP(int);  
    
    void printarray(){
        //This function prints the elements of an array which contains the shortest distance of all the verticese from the vertex.
        int i=0;
        while(i<vertex){
            cout<<dist[i]<<" ";
            i++;
        }
        cout<<"\n";
        
    } 
    
};

template<class T>
    void Graph<T>::ADDV(){
        /* This funtion adds  a new vertex to a graph. We initially store order of array of vectors in an array and after newly creation, we again copy them into our original array*/
        vector<pair<int,T>>*copied  = new vector<pair<int,T>>[vertex]; //temporary array of vectors
        int i=0;
        while(i<vertex){
            copied[i] = adjacency[i];    
            i++;
        }
      
        vertex = vertex+1;         //increase number of vertices
            adjacency = new vector<pair<int,T>>[vertex];   //create new array with size of 1 more vertex
        
        int j=0;
        while(j<vertex-1){
            adjacency[j] = copied[j];            //copying into orginal
            j++;
        }
        
    }

template<class T>
    void Graph<T>::ADDE(int source, int dest, T weight){
        /* This function adds takes two arguements and adds edge between them, i.e storing them in adjacency list of given vertex. */
        if(source<0 || source>vertex || dest<0 || dest>vertex)//invalid vertex
            cerr<<" vertex with this value is invalid"<<"\n";
        
        pair<int,T>a;     //pair containing vertex and weight
        a.first = dest;
        a.second = weight;
        addedge(a,source);      //This function adds this pair to the adjacency list by comparing weights of newly adding vertex with already been added vertices and adds them according to the order.
        
        pair<int,T>b;
        b.first = source;
        b.second = weight;
        addedge(b,dest);   
}

template<class T>
    void Graph<T>::DelE(int source, int dest){
        //This function deletes the edge from the graph. deleting the pair from the vectors from both vectors
        
        int count1 =0;  
        int count2 =0;
        auto i = adjacency[source].begin();
        while(i!=adjacency[source].end()){
            if((*i).first==dest){     //if the destination is found in adjacency list of source, then we just erase the pair from the vector.
                adjacency[source].erase(i);
                count1++;   
                break;
                
            }
            i++;
        }
        
        if(count1==0){     
            cerr<<"there is no vertex with number = source"<<"\n";
        }
        
        auto j = adjacency[dest].begin();   //same above procedure
        while(j!=adjacency[dest].end()){      
            //checks for the source in destination vector if found we just delete them.
            if((*j).first==source){
                adjacency[dest].erase(j);
                count2++;
                break;
            }
            j++;
        }   
        
        if(count2==0){
            cerr<<"there is no vertex with number= dest"<<"\n";
        }
    }

template <class T>
    void Graph<T>::BFS(int source){
        /*This function implements breadth first search on the graph and prints the order of vertices that we are traversing from the vertex source. */
        
        array = new bool[vertex]; //to keep track of visited vertices
        int i=0;
        while(i<vertex){
            array[i] = false;              //initially all vertices are not visited
            i++;
        }
        queue<int>que;           //creating a queue for BFS
        array[source] = true;        //marking the vertex as visited
        que.push(source);                //this initial vertex is pushed onto queue
        
        while(!que.empty()){    //runs untill the queue is empty
            int x = que.front();      // we are poping the starting vertex from the queue and printing them
            cout<<x<<" ";
            que.pop();
            for(auto i=adjacency[x].begin(); i!=adjacency[x].end();i++){
                //push all the unvisited adjacent vertices of dequeued vertex in the graph onto the queue and mark them as visited.
                if(!array[(*i).first]){
                    array[(*i).first] = true;
                    que.push((*i).first);   
                }    
            }    
        }
        
    }

template<class T>
    void Graph<T>::SSP(int source){
        // This function finds the shortest paths from given source vertex to all the remaining vertices 
        bool *v;
        v = new bool[vertex];                //keeps track of visited/not-visited nodes
        priority_queue<pair<int,T>>que;
        int i=0;
        while(i<vertex){
            v[i]= false;        //all vertices are unvisited
            i++;
        }
        dist = new int[vertex];
        int j=0;
        while(j<vertex){
            dist[j]= INT_MAX;        //initially all vertex distance from source is max value in int.
            j++;   
        }
        
        
        dist[source] = 0;            //distance from its own vertex is zero
        pair<int,T>p1 = {source,0};      // pushing this source pair onto the priority_queue 
        que.push(p1);
        
        while(!que.empty()){          //doing this untill the que is empty
            pair<int,T>p;
            p = que.top();            
            int x = p.first;      
            que.pop();              //the pair is popped from queue.
             v[x] = true;       //mark the popped vertex as visited
            
            auto i = adjacency[x].begin();
            while(i!=adjacency[x].end()){  
                int a = (*i).first;         //finding the adjacent vertices of popped vertex 
                int w = (*i).second;
                
                if(dist[x]+w <dist[a]){    
                    //if(distance[source]+weight between them <distance[dest], then they are pushed onto the queue)
                    dist[a] = dist[x] + w;
                    pair<int,T>pi={a,-1*dist[a]};     // pushing the adjacent pair
                    que.push(pi);
                }
                i++;   
            }    
        }
        
        
    }



int main() {
    
    int N;
    cin>>N;
    int Q;
    cin>>Q;
    
    Graph<int>G(N);
    string s;
    
    for(int i=0;i<Q;i++){
        cin>>s;
       // cout<<s<<endl;
        if(s.compare("ADDE")==0){
            int a;
            int b;
            cin>>a>>b;
            int w;
            cin>>w;
            G.ADDE(a,b,w);
        }
        if(s.compare("ADDV")==0){
            G.ADDV();
        }
        if(s.compare("DELE")==0){
            int a;
            int b;
            cin>>a>>b;
            G.DelE(a,b);    
        }
    }
    
    for(int i=0;i<2;i++){
        cin>>s;
        //cout<<s<<endl;
        if(s.compare("BFS")==0){
            int a;
            cin>>a;
            G.BFS(a);
            cout<<endl;
        }
        if(s.compare("SSP")==0){
            int a;
            cin>>a;
            G.SSP(a);
            G.printarray();
            
        }
    }
    
   // G.deletememory();
    


    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    return 0;
}

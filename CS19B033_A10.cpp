#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;

class Minegame{
    private:
    //int count =0;
   // int row;
   // int col;
    int num;
    bool **mine_graph; //graph containing mines information...
    // if mine is there -> true;
    // if mine isn't there -> false
    int **dup;      //This matrix contains the information about mines + the total number of mines around a given location other than mines location
    bool **visited; //This will keep track of visited locations in matrix.
    
    
    public:
    int cells =0;                   //keeps the count of total cells that have been revealed.
    int Check(pair<int,int>);           //checking for the bomb
    
    void create_graph(int num){             
        //We are creating matrix with taking num as arguement.
        this->num = num;
        mine_graph = new bool*[num];
        dup = new int*[num];
        visited = new bool*[num];
        for(int i=0;i<num;i++){
            mine_graph[i] = new bool[num];
            dup[i] = new int[num];
            visited[i] = new bool[num];
        }  
        for(int i=0;i<num;i++){
            for(int j=0;j<num;j++){
                mine_graph[i][j] = false;          //Initially there are no mines. Thereafter we are adding mines at particular locations.
                dup[i][j] = 0;                    //dup = -1 : mines located
                visited[i][j] = false;            //Initially all locations are not visited
            }  
        }
        
    }
    void add_mines(int);
    pair<int,int>find_coordinates(int a){ 
        //This function finds the location of mine in the matrix and returns i,j co-ordinates as a pair
        pair<int,int>p;
        p.first = a/num;
        p.second = a%num;
        return p;
    }
    
    void play(pair<int,int>);
    
    void update();
   
    
};

 void Minegame::update(){
     //This functions finds the total number of mines   particular location and places there.
     //if (i,j) has 3 mines around them dup[i][j] = 3.
     // total neighbours = 8
     
     int i=0;
     while(i<num){
         for(int j=0;j<num; j++){
             if(!mine_graph[i][j]){
                 if(i>=1 && j>=1){
                     if(mine_graph[i-1][j-1])              //north-west
                         dup[i][j] = dup[i][j] + 1;
                 }
                 if(i>=1){
                     if(mine_graph[i-1][j])               //north direction
                         dup[i][j] = dup[i][j] + 1;  
                 }
                 
                 if(i>=1 && j+1<num){
                     if(mine_graph[i-1][j+1])              //north-east
                         dup[i][j] = dup[i][j] + 1;
                 }
                 if(j>=1){  
                     if(mine_graph[i][j-1])                   //west
                         dup[i][j] = dup[i][j] + 1;  
                 }
                 
                 
                 if(j+1<num){              
                     if(mine_graph[i][j+1])                   //east
                         dup[i][j] = dup[i][j] + 1;
                 }
                 
                 if(i+1<num && j>=1){
                     if(mine_graph[i+1][j-1])                 //south-west
                         dup[i][j] = dup[i][j] + 1;
                 }
                 
                 if(i+1<num){
                     if(mine_graph[i+1][j])                   //south
                         dup[i][j] = dup[i][j] + 1;
                 }
                 
                 if(i+1<num && j+1<num){
                     if(mine_graph[i+1][j+1])                //south-east
                         dup[i][j] = dup[i][j] + 1; 
                 } 
             }
         }
         i++;
     }
     
     
 }     

void Minegame::add_mines(int a){
    //This function finds the particular location and places the mine there
    
    pair<int,int>x;
    x = find_coordinates(a);
    mine_graph[x.first][x.second] = true;
    dup[x.first][x.second] = -1;
    
}

void Minegame::play(pair<int,int>pi){

      if(pi.first>=0 && pi.first<num && pi.second>=0 && pi.second<num){
          
          if(visited[pi.first][pi.second]==true)  //visit the unvisited and mark them
              return;
          else
              visited[pi.first][pi.second] = true;
          cells = cells+1;                     //increament the number of revealed cells
          
          if(dup[pi.first][pi.second]==0){
              //if the location doesnt having bombs in neighbour locations, then recursive for their neighbours.
              if(pi.first>=1 && pi.second>=1){
                if(visited[pi.first-1][pi.second-1]==false){
                    pair<int,int>p1 = {pi.first-1,pi.second-1};
                    play(p1);
                }
              }
          }
          if(dup[pi.first][pi.second]==0){
              if(pi.first>=1){
                if(visited[pi.first-1][pi.second]==false){
                    pair<int,int>p2 = {pi.first-1,pi.second};
                    play(p2);
                }
              }
          }
          
          if(dup[pi.first][pi.second]==0){
              if(pi.first>=1 && pi.second+1<num){
                if(visited[pi.first-1][pi.second+1]==false){
                    pair<int,int>p3 = {pi.first-1,pi.second+1};
                    play(p3);
                }
              }
          }
          
          if(dup[pi.first][pi.second]==0){
              if(pi.second+1<num){
                if(visited[pi.first][pi.second+1]==false){
                    pair<int,int>p4 = {pi.first,pi.second+1};
                    play(p4);
                }
              }
          }
          
          if(dup[pi.first][pi.second]==0){
              if(pi.second>=1){
                if(visited[pi.first][pi.second-1]==false){
                    pair<int,int>p5 = {pi.first,pi.second-1};
                    play(p5);
                }
              }
          }
          
          if(dup[pi.first][pi.second]==0){
              if(pi.first+1<num && pi.second>=1){
                if(visited[pi.first+1][pi.second-1]==false){
                    pair<int,int>p6= {pi.first+1,pi.second-1};
                    play(p6);
                }
              }
          }
          
          if(dup[pi.first][pi.second]==0){
              if(pi.first+1<num){
                if(visited[pi.first+1][pi.second]==false){
                    pair<int,int>p7 = {pi.first+1,pi.second};
                    play(p7);
                }
              }
          }
          
          if(dup[pi.first][pi.second]==0){
              if(pi.first+1<num && pi.second+1<num){
                if(visited[pi.first+1][pi.second+1]==false){
                    pair<int,int>p8 = {pi.first+1,pi.second+1};
                    play(p8);
                }
              }
          }
      }
              
 
    
}

int Minegame::Check(pair<int,int>pi){
    //Checking if there is bomb in the given location
    
    if(dup[pi.first][pi.second]!=-1){
        play(pi);          //there is no bomb, then we are playing by moving to its neighbourhood
        return 0; 
    }
    else{
        return 1;            //There is a bomb 
    }   
}

int main() {
    int N;
    cin>>N;
    int M;
    cin>>M;
    Minegame ab;
    ab.create_graph(N);
    
    int i=0;
    while(i<M){
        int a;
        cin>>a;
        ab.add_mines(a);
        i++;
    }
    
    ab.update();
   // ab.print();
    
    pair<int,int>pi;
    while(cin>>pi.first>>pi.second){
        int pu = ab.Check(pi);              
        if(pu==0){                        //no bomb in location (pi.first,pi.second)
            if(ab.cells==N*N-M){            //all cells are revealed
                cout<<"Won"<<endl;          //we will win game
                break;
            }
            else{
                cout<<ab.cells<<endl;         
            }
        }
        else{
            cout<<"Lost"<<endl;           //if there is bomb in location, then we are losing the game
            break;    
        }
            
    }
    
    
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    return 0;
}

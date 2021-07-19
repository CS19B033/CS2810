#include <bits/stdc++.h>

using namespace std;

class EDD{
    private:
    string s1;                                              //string 1
    string s2;                                              //string 2
    int **p; 
        //table to store the number of changes to be made for a substring to convert it into other substring

    pair<int,int>size;              //pair to store the sizes of two strings
    int distance;                   // store the edit distance between two strings
    public:

    void assign(string, string);                    //function assigns two strings to other string variables in classs
    void compdist();
        // function finds the edit distance between two strings and stores the value in distance varaible
    void dist();
   // function prints the edit distance 
    void table();
    //function prints the table

    int minimum(int,int,int);
    //finds minimum among three integers

    bool bit = false;                //to know if expection is there in problem
    
    

};


void EDD::assign(string a, string b){

    s1 = a;
    s2 = b;
    size.first = a.size();              //size of 1st string 
    size.second = b.size();             //size of 2nd string 

    bit = true;                        // this tells us the strings are initialized.
}

int EDD::minimum(int a, int b, int c){
    //function finds the minimum
     int d;
    d = min(a,b);
    return min(d,c);
}

void EDD::compdist(){
    //finds the edit distance by forming table
    //the element in the last row and last column in table will be the edit distance
     p = new int*[size.first+1];
    for(int i=0;i<size.first+1;i++){
        p[i] = new int[size.second+1];            //creating table
    }


    int i=0;

    while(i<(size.first+1)){
        for(int j=0;j<(size.second+1);j++){
            if(j==0)
                //if second string is empty
                p[i][j]= i;   
            //the number of attempts will be the size of 1st string
            //we have to place all the charectors of 1st string to become same
            else if(i==0)
                //if 1st string is empty
                p[i][j]=j;
             //the number of attempts will be the size of 2st string

            else if(s2[j-1]== s1[i-1])
                //last charectors are same then recur for other charectors
                p[i][j] = p[i-1][j-1];

            else 
                //if last charectors are different, we have to find the minimum
                p[i][j] = 1 + minimum(p[i-1][j-1],p[i][j-1], p[i-1][j]);
                
        }
        i++;
    }
    distance = p[size.first][size.second];                    //edit distance between two strings
   
}

void EDD::dist(){
    compdist();
    cout<<distance<<endl;              //finds distance  and prints
}

void EDD::table(){
    compdist();
    for(int i=1;i<(size.first+1);i++){
        int j=1;
        while(j<size.second+1){
            cout<<p[i][j]<<" ";                    //printing the table
            j++;
        }
        cout<<endl;
    }
}

int main(){
    int Q;                      //no. of queries made
    cin>>Q;
    string ch;
    EDD st;                   //object of the class

    for(int i =0;i<Q;i++){
        cin>>ch;

        if(ch.compare("assign")==0){ 
            string x, y;
            cin>>x>>y;
            st.assign(x,y);
        }

        if(ch.compare("compdist")==0){
            try{
                if(st.bit==false){                       //checking if the bit is false or true
                    //if false : strings are not initilaized
                    //if true  : strings are initialized
                    throw("strings not found!");

                }
                else{
                st.compdist();             
            }
        }
         catch(string error){
                cout<<error<<endl;              //prints the error or ouput display if there
            }
        }

        if(ch.compare("dist")==0){
            try{
                if(st.bit==false){
                    throw("strings not found!");

                }
                else{
                st.dist();
            }
        }
         catch(string error){
                cout<<error<<endl;
            }
        }
            
        if(ch.compare("table")==0){
            try{
                if(st.bit==false){
                    throw("strings not found!");

                }
                else{
                st.table();
            }
        }
         catch(string error){
                cout<<error<<endl;
            }
        }
            
    
    }

    return 0;
}
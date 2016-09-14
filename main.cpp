#include <stdio.h>
#include <algorithm>
#include <iomanip>
#include <ios>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;
//almost OK. Cannot solve more complicated sudokus, i.e. the ones with 5 or more stars
struct Number{
    int value;//if empty then the value will be 0!!!
    bool alternatives[9];//if a number k is possible to add, this has a true value at place [k-1]
};


struct Grid{
    Number matrix[9][9];
};

bool can_be_added(Grid & a, int x, int y, int n){
    
    if(a.matrix[x-1][y-1].value==0){
        int count=0;
        for (int i=0; i<9;i++){
            if(a.matrix[i][y-1].value==n){count++;}
            }
        for (int j=0; j<9;j++){
            if(a.matrix[x-1][j].value==n){count++;}
            }
        //cout<<"count"<<count<<endl;
        if(count>0){return false;}
        else{
            count=0; int x_place=(int)((x-1)/3); int y_place=(int)((y-1)/3);
            //cout<<"x_place"<<x_place; cout<<"y_place"<<y_place;
            for(int i=x_place*3;i<(x_place+1)*3; i++){
                for(int j=y_place*3;j<(y_place+1)*3; j++){//cout<<i+1<<j+1<<count<<endl;
                    if(a.matrix[i][j].value==n){count++;}
                    }
                }
                if(count>0){return false;}
                else {return true;}
            }
      }
      else{return false;}
    }
//OK! Here the coordinates x,y are of course element numbers, so they are the opposite as x-,y-coordinates!!!!

void set_zero(Grid & a){
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
           a.matrix[i][j].value=0; 
           for(int k=0;k<9;k++){
               a.matrix[i][j].alternatives[k]=true; 
        }
    }
}
}
//OK!

void print(Grid & a){
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
           cout<<a.matrix[i][j].value<<" ";
           
            }
            cout<<endl;
       }
}
//OK!

void print(Number & b){
    cout<<"Number has the value "<<b.value<<" and a vector:"<<endl;
    for(int i=0;i<9;i++){
        cout<<b.alternatives[i];
    }
    cout<<endl;
}
//OK!

void generate_alternatives(Grid & a){
    for(int x=1;x<10;x++){
        for(int y=1; y<10; y++){
            for(int k=1; k<10; k++){
                if(can_be_added(a,x,y,k)==true){
                    a.matrix[x-1][y-1].alternatives[k-1]=true;
                }
                else{
                    a.matrix[x-1][y-1].alternatives[k-1]=false;
                }
            }
        }
    }
    
}
//OK!

void read(Grid & a){
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            int n=0;
            cout<<i+1<<j+1<<" ";
            cin>>n;
            if(can_be_added(a,i+1,j+1,n)==true||n==0)
            {a.matrix[i][j].value=n;}
            else {cout<<"False number!!!!"<<endl;--j; continue;}//Jumps back to the beginning of the last for-loop!
            cout<<endl;
        }
    }
}
//OK! (allthough you can add numbers like 23 etc...

bool is_only_place(Grid & a,int x, int y, int n){
    generate_alternatives(a);
    if(can_be_added(a,x,y,n)==true){int count=0;
        for(int k=0;k<9;k++){if(a.matrix[k][y-1].alternatives[n-1]==true){count++;}}
        if(count==1) {return true;}
        count=0;
        for(int k=0;k<9;k++){if(a.matrix[x-1][k].alternatives[n-1]==true){count++;}}
        if(count==1) {return true;}
        
    count=0; int x_place=(int)((x-1)/3); int y_place=(int)((y-1)/3);
            //cout<<"x_place"<<x_place; cout<<"y_place"<<y_place;
            for(int i=x_place*3;i<(x_place+1)*3; i++){
                for(int j=y_place*3;j<(y_place+1)*3; j++){//cout<<i+1<<j+1<<count<<endl;
                    if(a.matrix[i][j].value==n){return false;}
                    
                    if(a.matrix[i][j].alternatives[n-1]==true){count++;}    
                    }
                }
                
                if(count>1){generate_alternatives(a);return false;}
                else {return true;}
                
    }
    else{return false;}
}
//OK!!! We test if the x,y is the only place for the number n in the "miniGrid" (3x3)

void solve(Grid & a){
    generate_alternatives(a);
    for(int x=1;x<10;x++){
        for(int y=1;y<10;y++){
            if(a.matrix[x-1][y-1].value==0){
                int number=0; int count=0;
                for(int k=1;k<10;k++){if(is_only_place(a,x,y,k)==true){a.matrix[x-1][y-1].value=k; solve(a);}
                    if(a.matrix[x-1][y-1].alternatives[k-1]==true){
                    number=k; count++;
                }
            }
            if(count==1&&can_be_added(a,x,y,number)){
                a.matrix[x-1][y-1].value=number; continue;
                }
            }
            else{continue;}
            }
        }
    }
    //OK!!!!

int main()
{

Grid C;
 set_zero(C);
int data2[9][9]={{5,0,0,1,9,8,0,0,4},{0,8,0,3,0,4,0,5,0},{0,0,0,0,6,0,0,0,0},
{8,4,0,0,0,0,0,9,1},{2,0,1,0,0,0,5,0,7},{9,7,0,0,0,0,0,3,2},
{0,0,0,0,1,0,0,0,0},{0,1,0,4,0,3,0,2,0},{7,0,0,9,8,5,0,0,6}
};


for(int i=0;i<9;i++){
    for(int j=0;j<9;j++){
        C.matrix[i][j].value=data2[i][j];
    }
}
generate_alternatives(C);
cout<<"Can be added to C"<<endl;
for(int n=1;n<10;n++){
    cout<<"Number "<<n<<endl;
for(int i=1;i<10;i++){
    for(int j=1;j<10;j++){
        cout<<" "<<can_be_added(C,i,j,n)<<" ";
    }
    cout<<endl;
}
}
//for loop for testing if any number between 1 and 9 can be added
cout<<"Is only one for C"<<endl;
for(int n=1;n<10;n++){
    cout<<"Number "<<n<<endl;
for(int i=1;i<10;i++){
    for(int j=1;j<10;j++){
        cout<<" "<<is_only_place(C,i,j,n)<<" ";
    }
    cout<<endl;
}
}
//for loop for testing if number between 1 and 9 is the only alternative here

print(C);
cout<<endl;
solve(C);
print(C);





	return 0;
}

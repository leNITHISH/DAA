#include <iostream>
#include <fstream>
#include<random>

using namespace std;
void best(ofstream& out, int a){
    for(int i=0;i<a;i++) out<<i<<" ";
}
void worst(ofstream& out, int a){
    for(int i=a;i>=0;i--)out<<i<<" ";
}
void rnd(ofstream& out, int a){
    for(int i=0;i<a;i++)out<<rand()<<" ";
}
int main(){
    int a;string in;
    cin>>in;
    cin>>a;
    ofstream out("input.txt");
    out<<a<<" ";
    if(in=="best")best(out,a);
    else if(in=="worst")worst(out,a);
    else if(in=="random")rnd(out, a);
    else cout<<"err";
    return 0;
}
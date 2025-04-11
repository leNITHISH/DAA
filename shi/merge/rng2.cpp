#include <iostream>
#include <fstream>
#include<random>

using namespace std;
void best(ofstream& out, int a){
    int b = rand()%a;
    for(int i=b;i<a+b;i++) out<<i*b<<" ";
}
void worst(ofstream& out, int a){
    int b = rand()%a;
    for(int i=a+b;i>=b;i--)out<<i*b<<" ";
}
void rnd(ofstream& out, int a){
    for(int i=0;i<a;i++)out<<rand()%a<<" ";
}
int main(int argc, char* argv[]){
    int a;string in;
    cin>>in;
    cin>>a;
    ofstream out(argv[1]);
    out<<a<<" ";
    if(in=="best")best(out,a);
    else if(in=="worst")worst(out,a);
    else if(in=="random")rnd(out, a);
    else cout<<"err";
    return 0;
}

#include<bits/stdc++.h>
using namespace std;
using ll=long long;
ll dist[10000][10000];

// task 2 A
void get_input(){
    // the input can be enter by characters and their distances 
    // exp -> A B 13 
    // the max number of the places is 10000 --> dist[10000][10000]
    int n,cnt=1,x;
    char a,b;
    cin>>n;
    // a map to set int val to char inorder to have two dimentional (kinda a dictionary)
    map<char,int> dic;
    for(int i=0;i<n;i++){
        cin>>a>>b>>x;
        // assign a int to each char 
        if(dic[a]==0){
             dic[a]=cnt;
             cnt++;
        }
        if(dic[b]==0){
             dic[b]=cnt;
             cnt++;
        }
        dist[dic[a]][dic[b]]=x;
        dist[dic[b]][dic[a]]=x;
    }
}

int main(){
    get_input();
    return 0;
}
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
#define mx 100

ll dist[mx][mx],plc_num=0;
vector<ll>nodes_in_shortest_path[mx][mx]; // shortest path between i and j includes nodes that are stored in vector[i][j].size()
bool pathway_taken=0;
 // a map to set int val to char inorder to have two dimentional (kinda a dictionary) -task2
map<string,ll> dic;

// task 2 A
void get_pathways(){
     for(ll i=0;i<mx;i++)
        for(ll j=0;j<mx;j++) dist[i][j]=__INT_MAX__;
    pathway_taken=1;
    // the input can be enter by characters and their distances 
    // exp -> A B 13 
    // the max number of the places is mx --> dist[mx][mx]
    ll n,cnt=1,x;
    string a,b;
    cin>>n;
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
    // save number of distinct places;
    plc_num=cnt-1;
}

void dijkstra(ll src,ll end, vector<ll>path[],ll length[]){
     bool visited[plc_num+1];
     fill(visited,visited+plc_num+1,0);
     
     for(ll i=1;i<=plc_num;i++){
        if(i!=src){
             path[i].push_back(src);
             length[i]=dist[src][i];
        }
     }

     for(ll j=0;j<plc_num-1;j++){
        ll mn=__INT_MAX__,vnear=0;
        for(ll i=1;i<=plc_num;i++){
            if(i!=src){
                if(length[i]<mn && !visited[i]){
                    mn=length[i];
                    vnear=i;
                }
            }
        }
        for(ll i=1;i<=plc_num;i++){
            if(i!=src){
                if(length[vnear]+dist[vnear][i]<length[i]){
                    length[i]=length[vnear]+dist[vnear][i];
                    path[i].clear();
                    path[i].push_back(vnear);
                }
                else if(length[vnear]+dist[vnear][i]==length[i]){
                    path[i].push_back(vnear);
                }
            }
        }
        visited[vnear]=1;
    }
}

void going_to_target(){
    while(!pathway_taken){
        cout<<"Please enter the pathway\n";
        get_pathways();
    }
    string a,b;
    cout<<"Enter your starting point: ";
    cin>>a;
    cout<<"Enter your target you wish to get there from "<<a<< " :";
    cin>>b;
    vector<ll> path[plc_num+1];
    ll length[plc_num+1];
    dijkstra(dic[a],dic[b],path,length);
   // for(int i=1;i<=plc_num;i++) cout<<length[i]<<' '<<endl;
}

int main(){
    going_to_target();
    return 0;
}

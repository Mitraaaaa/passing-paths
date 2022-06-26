#include<bits/stdc++.h>
using namespace std;
using ll=long long;
#define mx 10000

// task2- definitions

ll dist[mx][mx],plc_num=0;
vector<ll>nodes_in_shortest_path[mx][mx]; // shortest path between i and j includes nodes that are stored in vector[i][j].size()
bool pathway_taken=0;

 // a map to set int val to char inorder to have two dimentional (kinda a dictionary) -task2
map<string,ll> encrypt;
map<ll,string>decrypt;

// Tsp part  & dynamic part Dp[2^n][n] max is n=19 --> 2^10=1024
ll Dp[2000][10],visited_all=0,parent[100][1000];
//-----------------------------------------------------------------

//task1-definitions
ll parking[100][100];

//-----------------------------------------------------------------

// task 2 A
void get_pathways(){
    // nodes normally are max meaning that there is no way btwn them
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
        if(encrypt[a]==0){
             encrypt[a]=cnt;
             decrypt[cnt]=a;
             cnt++;
        }
        if(encrypt[b]==0){
             encrypt[b]=cnt;
             decrypt[cnt]=b;
             cnt++;
        }
        dist[encrypt[a]][encrypt[b]]=x;
        dist[encrypt[b]][encrypt[a]]=x;
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

void print_shortest_path(vector<ll>path[],int pos,int src,bool first_time){
    if(path[pos].size()==0|| pos==src ){
        cout<<endl;
        return;
    }
    for(int i=0;i<path[pos].size();i++){
        if(first_time) cout<<decrypt[pos]<<' ';
            cout<<decrypt[path[pos][i]]<<' ';
            print_shortest_path(path,path[pos][i],src,0);
    }
}

void going_to_target(){
    // finding shortest path from start to the target place
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
    dijkstra(encrypt[a],encrypt[b],path,length);
    cout<<"Shortest length from "<<a<<"to "<<b<<" is: "<<length[encrypt[b]]<<endl;
    print_shortest_path(path,encrypt[b],encrypt[a],1);
}

// task2-B
ll tsp(ll mark, ll position,ll src){
    if(mark==visited_all){
         return dist[position][src];
    }

      if(Dp[mark][position]!=-1)
            return Dp[mark][position];
        
        ll ans=__INT_MAX__;

        for(ll plc=0;plc<plc_num;plc++){
            if((mark&(1<<(plc)))==0 ){
                     ll newAns = dist[position][plc+1] + tsp( mark|(1<<(plc)),plc+1,src);
                    if(ans>newAns){
                        ans = newAns;
                        parent[position][mark]=plc+1;
                    }
            }
        }
    return Dp[mark][position]=ans;
}

void pass_certain_nodes(){
     while(!pathway_taken){
        cout<<"Please enter the pathway\n";
        get_pathways();
    }
    string a,b;
    cout<<"Enter your starting point: ";
    cin>>a;
    visited_all=(1<<(plc_num))-1;
    for(ll i=0;i<2000;i++)
        for(ll j=0;j<10;j++) Dp[i][j]=-1,parent[j][i]=-1;

    for(ll i=0;i<100;i++)
        for(ll j=0;j<1000;j++) parent[i][j]=-1;

    cout<<tsp(1<<(encrypt[a]-1),encrypt[a],encrypt[a])<<endl;

    // printing the tsp path
    int path[plc_num];
    int path_counter = 0;
    int cur_node = 1;
    int cur_mask = 1;
    do {
        path[path_counter] = cur_node;
        path_counter++;
        cur_node = parent[cur_node][cur_mask];
        cur_mask |= (1 << (cur_node-1));
    } while(cur_node != -1);

    cout<<"the path is: ";
    for(int i=0;i<plc_num;i++) cout<<decrypt[path[i]]<<' ';
    cout<<a<<endl;

}

//-----------------------------------------------------------------
// task1 
void get_car(){
    ll car_num,n,x;
    pair<ll,ll>pos,empty,camera;
    cout<<"Enter square dimention: ";
    cin>>n;
    cout<<"Enter the empty space cell number: ";
    cin>>x;
    empty.first=(x-1)/n,empty.second=(x-1)%n;
    cout<<"Enter the cell with camera number: ";
    cin>>x;
    camera.first=(x-1)/n,camera.second=(x-1)%n;
    // parking[n][n]
    cout<<"Enter the number of the car and it's cell numbers seperated by a space or enter\nexp->(1 2 3)\n when you are done enter -1\n";
    cin>>car_num;
    while(car_num!=-1){
        cin>>pos.first>>pos.second;
        // find the i and j of each car position
        // 1<=pos.first<=n^2 
        parking[(pos.first-1)/n][(pos.first-1)%n]=car_num;
        parking[(pos.second-1)/n][(pos.second-1)%n]=car_num;
        cin>>car_num;
    }
    
    // for(int i=0;i<n;i++){
    //     for(int j=0;j<n;j++){
    //         cout<<parking[i][j]<<' ';
    //     }
    //     cout<<endl;
    // }
    
}

int main(){
    //pass_certain_nodes();
    get_car();
    return 0;
}

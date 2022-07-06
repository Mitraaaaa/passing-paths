#include<bits/stdc++.h>
using namespace std;
using ll=long long;
#define mx 1000

// task2- definitions

ll dist[mx][mx],plc_num=0,dp_flyd[mx][mx];
vector<ll>nodes_in_shortest_path[mx][mx],nodes_btwn[mx][mx]; // shortest path between i and j includes nodes that are stored in vector[i][j].size()
bool pathway_taken=0;

 // a map to set int val to char inorder to have two dimentional (kinda a dictionary) -task2
map<string,ll> encrypt;
map<ll,string>decrypt;

// Tsp part  & dynamic part Dp[2^n][n] max is n=19 --> 2^10=1024
ll Dp[2000][10],visited_all=0,parent[100][1000];
//-----------------------------------------------------------------

//task1-definitions
#define mx1 100
ll parking[mx1][mx1],square;
pair<ll,ll>car_parent[mx1][mx1];
pair<ll,ll>emptty,camera,desired_plc;
bool visited[mx1][mx1],car_input_taken=0,possible_relocation=0;

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
    cout<<"Shortest length from "<<a<<" to "<<b<<" is: "<<length[encrypt[b]]<<endl;
    cout<<"the paths are :\n";
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

void floyd(){
    for(int i=1;i<=plc_num;i++){
        for(int j=1;j<=plc_num;j++){
            dp_flyd[i][j]=dist[i][j];
        }
    }
    for(int k=1;k<=plc_num;k++){
        for(int i=1;i<=plc_num;i++){
            for(int j=1;j<=plc_num;j++){
                if(dp_flyd[i][k]+dp_flyd[k][j]<dp_flyd[i][j]){
                    dp_flyd[i][j]=dp_flyd[i][k]+dp_flyd[k][j];
                    nodes_btwn[i][j].push_back(k);
                }
            }
        }
    }
}

void print_optimal_path(ll mask,ll path[],string a){
    vector<ll>final_path,tmp;
    final_path.push_back(path[0]);
    ll cnt=2;
    for(int i=1;i<plc_num;i++){
        if(((1<<(path[i]-1)&mask) ==0)){
                cnt=i;
                while(((1<<(path[cnt]-1)&mask) ==0)){
                    tmp.push_back(path[cnt]);
                        cnt++;
                }
                for(auto x:tmp){
                    if(find(nodes_btwn[i][cnt].begin(),nodes_btwn[i][cnt].end(),x)!=nodes_btwn[i][cnt].end()){
                        final_path.push_back(x);
                    }
                tmp.clear();
                i=cnt-1;
            }
        }
        else final_path.push_back(path[i]);
    }
   final_path.push_back(encrypt[a]);
    cnt=0;
    for(ll i=0;i<final_path.size()-1;i++){
        cnt+=dist[final_path[i]][final_path[i+1]];
    }
    cout<<"The optimal lenght is: "<<cnt<<endl;
    cout<<"the path is: ";
    for(auto x:final_path) cout<<decrypt[x]<<' ';
    cout<<endl;
}

void pass_certain_nodes(){
     while(!pathway_taken){
        cout<<"Please enter the pathway\n";
        get_pathways();
    }
    string a,b="";
    cout<<"Enter your starting point: ";
    cin>>a;
    ll mask=(1<<(encrypt[a]-1));
    cout<<"Enetr the nodes you wish to pass from "<<a<<" (enter -1 at the end):";
    while(b!="-1"){
        cin>>b;
        mask|=(1<<(encrypt[b]-1));
    }

    // bitset<8> x(mask);
    // cout<<x<<endl;

    visited_all=(1<<(plc_num))-1;
    for(ll i=0;i<2000;i++)
        for(ll j=0;j<10;j++) Dp[i][j]=-1;

    for(ll i=0;i<100;i++)
        for(ll j=0;j<1000;j++) parent[i][j]=-1;

    cout<<"The Tsp length is: ";
    cout<<tsp(1<<(encrypt[a]-1),encrypt[a],encrypt[a])<<endl;

    // printing the tsp path
    ll path[plc_num];
    ll path_counter = 0;
    ll cur_node = 1;
    ll cur_mask = 1;
    do {
        path[path_counter] = cur_node;
        path_counter++;
        cur_node = parent[cur_node][cur_mask];
        cur_mask |= (1 << (cur_node-1));
    } while(cur_node != -1);

    cout<<"the tsp path is: ";
    for(int i=0;i<plc_num;i++) cout<<decrypt[path[i]]<<' ';
    cout<<a<<endl;
   floyd();
   print_optimal_path(mask,path,a);

}

//-----------------------------------------------------------------
// task1

bool valid(ll i , ll j){
    return i>=0 && j>=0 && i<square && j<square && parking[i][j]!=-1;
}

void reloction(ll i, ll j ){
    visited[i][j]=1;
    if(i==desired_plc.first && j==desired_plc.second){
        possible_relocation=1;
        return;
    }
    if(!possible_relocation){
        vector<pair<ll,ll>> possible_takes;
        if(valid(i-2,j) && parking[i-2][j]==parking[i-1][j])
            possible_takes.push_back({i-2,j});
        if(valid(i+2,j) && parking[i+2][j]==parking[i+1][j])
            possible_takes.push_back({i+2,j});
        if(valid(i,j-2) && parking[i][j-2]==parking[i][j-1])
            possible_takes.push_back({i,j-2});
        if(valid(i,j+2) && parking[i][j+2]==parking[i][j+1])
            possible_takes.push_back({i,j+2});

        for(auto x:possible_takes){
            if(!visited[x.first][x.second]){
                car_parent[x.first][x.second]={i,j};
                reloction(x.first,x.second);
            }
        }
    }
}

void get_car(){
    car_input_taken=1;

    ll car_num,n,x;
    pair<ll,ll>pos;
    cout<<"Enter square dimention: ";
    cin>>n;
    square=n;
    cout<<"Enter the empty space cell number: ";
    cin>>x;
    emptty.first=(x-1)/n,emptty.second=(x-1)%n;
    parking[emptty.first][emptty.second]=0;
    cout<<"Enter the cell with camera number: ";
    cin>>x;
    camera.first=(x-1)/n,camera.second=(x-1)%n;
    parking[camera.first][camera.second]=-1;

    cout<<"Enter the cell number desired to be empty: ";
    cin>>x;
    desired_plc.first=(x-1)/n,desired_plc.second=(x-1)%n;

    // parking[n][n]
    cout<<"Enter the number of the car and it's cell numbers seperated by a space or enter\nexp->(1 2 3)\nwhen you are done enter -1\n";
    cin>>car_num;
    while(car_num!=-1){
        cin>>pos.first>>pos.second;
        // find the i and j of each car position
        // 1<=pos.first<=n^2
        parking[(pos.first-1)/n][(pos.first-1)%n]=car_num;
        parking[(pos.second-1)/n][(pos.second-1)%n]=car_num;
        cin>>car_num;
    }
    
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            visited[i][j]=0;

    //  for(int i=0;i<n;i++){
    //     for(int j=0;j<n;j++)
    //         cout<<parking[i][j]<<' ';
    //     cout<<endl;
    //  }
    
}

void count_print_relocate(){
    while(!car_input_taken){
        cout<<"Please enter inputs first:\n";
        get_car();
    }
    reloction(emptty.first,emptty.second);
    if(!possible_relocation)
        cout<<"Not possible!\n";
    else{
        vector<ll>path;
        ll i=desired_plc.first,j=desired_plc.second;
        while(i!=emptty.first || j!=emptty.second){
            path.push_back(parking[i][j]);
            ll k=i;
            i=car_parent[k][j].first;
            j=car_parent[k][j].second;
        }
        cout<<"You need to relocate "<<path.size()<<" cars including: ";
         reverse(path.begin(), path.end());
        for(int x:path)
            cout<<x<<" ";
        cout << endl;
    }
}

// task-3
// input : graph matrix(nxn) and n
// output : min sum of road distances
ll minKey(vector<ll> key, vector<ll> mst, ll n)
{
    //find vertex with min distance from set of vertices not included in mst
    ll min = __INT_MAX__, minindex;
    for (ll v = 1; v <= n; v++)
        if (!mst[v] && key[v] < min)
        {
            min = key[v];
            minindex = v;
        }
    return minindex;
}

void MinSumOfDist(ll graph[mx][mx], ll n)
{
    //vector of mst graph
    vector<ll> adj(n + 1);
    vector<ll> key(n + 1);
    //set of included vertices
    vector<ll> mst(n + 1);
    //sum of weights of mst
    ll SumOfDist = 0;
    // Initializing vectors
    for (ll i = 0; i <= n; i++)
    {
        key[i] = __INT16_MAX__;
        mst[i] = 0;
    }
    key[1] = 0;
    adj[1] = -1;
    for (ll count = 0; count < n; count++)
    {
        ll u = minKey(key, mst, n);
        //add vertex u to mst
        mst[u] = 1;
        //update key and adj vectors
        for (ll v = 1; v <= n; v++)
            if (graph[u][v] && !mst[v] && graph[u][v] < key[v])
            {
                adj[v] = u;
                key[v] = graph[u][v];
            }
    }
    //calculate sum of weights
    for (ll i = 2; i <= n; i++)
        SumOfDist += graph[i][adj[i]];
    //print edgs of mst
    for (ll i = 2; i <= n; i++)
        cout << decrypt[i] << " - " << decrypt[adj[i]] << endl;
    //print sum of dist
    cout << SumOfDist << endl;
}

int main(){
    // task 1
    // get_car();
    // count_print_relocate();


  // task 2A
    // get_pathways();
    // going_to_target();
    // task 2B
//    pass_certain_nodes();

   // task-3
   get_pathways();
   MinSumOfDist(dist,plc_num);

    return 0;
}

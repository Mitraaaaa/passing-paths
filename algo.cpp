#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// part3
// input : graph matrix(nxn) and n
// output : min sum of road distances
ll minKey(vector<ll> key, vector<ll> mst, ll n)
{
	//find vertex with min distance from set of vertices not included in mst
	ll min = INT16_MAX, minindex;
	for (ll v = 1; v <= n; v++)
		if (!mst[v] && key[v] < min)
		{
			min = key[v];
			minindex = v;
		}
	return minindex;
}
void MinSumOfDist(vector<vector<ll>> graph, ll n)
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
		key[i] = INT16_MAX;
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
		cout << i << " - " << adj[i] << endl;
	//print sum of dist
	cout << SumOfDist << endl;
}
int main()
{

}
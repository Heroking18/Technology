#include <iostream>
#include "queue.h"

using namespace std;

const int MAXN = 100000;

int dist[MAXN];
vector<int> adj[MAXN];
bool visited[MAXN];

void bfs(int start)
{
    Queue q;

    // push the starting node to the queue
    q.push(start);
    visited[start] = true;
    dist[start] = 0;

    // loop until the queue is empty
    while (!q.empty())
    {
        // get front elem of the queue
        int u = q.front();
        q.pop();

        // iterate through neighbouring nodes
        for (size_t i = 0; i < adj[u].size(); i++)
        {
            int v = adj[u][i];
            if (!visited[v])
            {
                // push neighbour to the queue
                q.push(v);
                visited[v] = true;
                dist[v] = dist[u] + 1; // update the distance of the neighbour
            }
        }
    }
}

int main()
{
    int t, n, m, x, y;
    int route_count = 0;

    cin >> t;
    for (int i = 0; i < t; i++)
    {
        cin >> n >> m;
        /* store the values to your own data structure */
        /* execute your algorithm for each test */
        /* store result (shortest route) of each test in route_count */

        // read the edges and store them in the adjacency list
        for (int i = 1; i <= m; i++)
        {
            cin >> x >> y;
            adj[x].push_back(y);
            adj[y].push_back(x);
        }
        bfs(1);
        route_count = dist[n];
        cout << route_count << endl;
        for (int i = 1; i <= n; i++)
        {
            adj[i].clear();
            visited[i] = false;
        }
    }
    return 0;
}

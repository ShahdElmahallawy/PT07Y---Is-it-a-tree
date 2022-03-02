#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
using namespace std;

class DisjointSet
{
    unordered_map<int, int> parent;
    unordered_map<int, int> depth;
public:

    // perform MakeSet operation
    void MakeSet(int n)
    {
        for (int i = 0; i < n; i++)
        {
            parent[i] = i;
            depth[i] = 0;
        }
    }

    // Find the root of the set in which element k belongs
    int Find(int k)
    {
        // if k is root
        if (parent[k] == k)
            return k;

        // recur for parent until we find root
        return Find(parent[k]);
    }

    // Perform Union of two subsets
    void Union(int a, int b)
    {
        int x = Find(a);
        int y = Find(b);
        if (x == y)
        {
            return;
        }
        if (depth[x] > depth[y])
        {
            parent[y] = x;
        }
        else if (depth[x] < depth[y])
        {
            parent[x] = y;
        }
        else
        {
            parent[x] = y;
            depth[y]++;
        }
    }
};

struct Edge {
    int src, dest;
};
class Graph
{
public:
    vector<vector<int>> adjList;

    Graph(vector<Edge> const& edges, int n)
    {
        adjList.resize(n);
        for (auto& edge : edges)
        {
            adjList[edge.src].push_back(edge.dest);
        }
    }
    bool detectTree(Graph const& graph, int n)
    {
        DisjointSet ds;
        ds.MakeSet(n);
        for (int u = 0; u < n; u++)
        {
            for (int v : graph.adjList[u])
            {
                int x = ds.Find(u);
                int y = ds.Find(v);
                if (x == y)
                {
                    return false; //Cycle -> not tree
                }
                else
                {
                    ds.Union(x, y);
                }
            }
        }
        //check if all nodes have the same representative 
        set<int> root;
        for (int u = 0; u < n; u++)
        {
            root.insert(ds.Find(u));
        }
        if (root.size() != 1)
            return false;

        else
            return true;
    }
};
void printGraph(Graph const& graph, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << i << " -> ";
        for (int v : graph.adjList[i])
        {
            cout << v << " ";
        }
        cout << endl;
    }
}
int main()
{
    int m, n;
    cin >> n;
    cin >> m;
    vector<Edge> edges(m);
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u;
        cin >> v;
        u--;
        v--;
        edges[i].src = u;
        edges[i].dest = v;
    }
    Graph graph(edges, n);

    if (graph.detectTree(graph, n))
        cout << "YES" << endl;
    else
        cout << "NO" << endl;
    return 0;
}
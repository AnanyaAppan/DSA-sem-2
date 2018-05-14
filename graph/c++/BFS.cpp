#include<iostream>
#include<list>
using namespace std;

class Graph
{
    int n;
    list<int> *adj;
    public:
        Graph ( int vertices )
        {
            n = vertices;
            adj = new list <int> [n]; 
        }
        void addEdge(int u, int v)
        {
            adj[u].push_back(v);
        }
        void DFS(int v, int* visited)
        {
            visited[v] = 1;
            cout << v << "\n";
            list <int> :: iterator t;
            for(t = adj[v].begin(); t!=adj[v].end(); t++)
            {
                if(visited[*t] != 1)
                {
                    DFS(*t, visited);
                }
            }
        }
        void BFS(int v, int *visited)
        {
            visited[v] = 1;
            list <int> queue;
            queue.push_back(v);
            while(!queue.empty())
            {
                v = queue.front();
                cout << v << endl;
                queue.pop_front();
                list <int> :: iterator t;
                for(t = adj[v].begin(); t!= adj[v].end(); t++)
                {
                    if(visited[*t] != 1)
                    {
                        visited[*t] = 1;
                        queue.push_back(*t);
                    }
                }
            }
        }
};

int main()
{
    Graph g(6);
    g.addEdge(0,1);
    g.addEdge(1,2);
    g.addEdge(1,3);
    g.addEdge(2,4);
    g.addEdge(3,5);
    g.addEdge(4,5);
    int visited[6] = {0};
    // cout << "DFS" << endl;
    // g.DFS(0, visited);
    cout << "BFS" << endl;
    g.BFS(0, visited);
    return 0;
}




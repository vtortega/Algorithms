#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <cstdint>
#include <climits>
#include <queue>

struct Edge 
{
    int src, dest;      
    long year;
    long time;
    long cost;

    bool operator<(const Edge& other) const 
    {
        return year < other.year;
    }
};

class Graph 
{
private:
    int v;
    std::vector<std::vector<Edge> > adj_list;

    int find(std::vector<int>& parent, int i) 
    {
        if (parent[i] != i) 
        {
            parent[i] = find(parent, parent[i]);
        }
        return parent[i];
    }

    void union_sets(std::vector<int>& parent, int x, int y) 
    {
        int xset = find(parent, x);
        int yset = find(parent, y);
        if (xset != yset) 
        {
            parent[xset] = yset;
        }
    }

    void union_sets_kruskal(std::vector<int>& parent, std::vector<int>& rank, int x, int y) 
    {
        int xroot = find(parent, x);
        int yroot = find(parent, y);

        if (rank[xroot] < rank[yroot])
            parent[xroot] = yroot;
        else if (rank[xroot] > rank[yroot])
            parent[yroot] = xroot;
        else {
            parent[yroot] = xroot;
            rank[xroot]++;
        }
    }

public:
    Graph(int _v) : v(_v), adj_list(_v + 1) {}

    void add_edge(int src, int dest, long year, long time, long cost) 
    {
        Edge edge = {src, dest, year, time, cost};
        adj_list[src].push_back(edge);

        edge.src = dest;
        edge.dest = src;
        adj_list[dest].push_back(edge);
    }

    struct CompareDist 
    {
        bool operator()(const std::pair<long, int>& a, const std::pair<long, int>& b) 
        {
            return a.first > b.first;
        }
    };

    struct CompareByCost 
    {
        bool operator()(const Edge& a, const Edge& b) const 
        {
            return a.cost < b.cost;
        }
    };

    void dijkstra(int src) 
    {
        std::vector<long> dist(v + 1, LONG_MAX);
        std::vector<long> max_year(v + 1, 0);
        std::priority_queue<std::pair<long, int>, std::vector<std::pair<long, int> >, CompareDist> pq;

        dist[src] = 0;
        pq.push(std::make_pair(0, src));

        while(!pq.empty()) 
        {
            int u = pq.top().second;
            pq.pop();

            for(const Edge& edge : adj_list[u]) 
            {
                int v = edge.dest;
                long weight = edge.time;

                if(dist[u] + weight < dist[v]) 
                {
                    dist[v] = dist[u] + weight;
                    pq.push(std::make_pair(dist[v], v));

                    max_year[v] = std::max(max_year[u], edge.year);
                }
            }
        }

        dist[src - 1] = 0;
        long global_max_year = 0;
        for (int i = 0; i <= v; i++) 
        {
            if (i != src) 
            {
                std::cout << dist[i] << std::endl;
                global_max_year = std::max(global_max_year, max_year[i]);
            }
        }

        std::cout << global_max_year << std::endl;
    }

    void first_year_all_vertices_reachable() 
    {
        std::vector<Edge> edges;

        for (int i = 1; i <= v; i++) 
        {
            for (const Edge& e : adj_list[i]) 
            {
                if (e.src < e.dest) 
                { 
                    edges.push_back(e);
                }
            }
        }

        std::sort(edges.begin(), edges.end());

        std::vector<int> parent(v + 1);
        for (int i = 0; i <= v; i++) 
        {
            parent[i] = i;
        }

        int distinct_sets = v;

        for (const Edge& edge : edges) 
        {
            int x = find(parent, edge.src);
            int y = find(parent, edge.dest);

            if (x != y) 
            {
                union_sets(parent, x, y);
                distinct_sets--;
            }

            if (distinct_sets == 1) 
            {
                std::cout << edge.year << std::endl;
                break;
            }
        }
    }

    void mst_using_cost() {
        std::vector<Edge> edges;

        for (int i = 1; i <= v; i++) 
        {
            for (const Edge& e : adj_list[i]) 
            {
                if (e.src < e.dest) 
                {  
                    edges.push_back(e);
                }
            }
        }

        std::sort(edges.begin(), edges.end(), CompareByCost());

        std::vector<int> parent(v + 1);
        std::vector<int> rank(v + 1, 0);
        for (int i = 0; i <= v; i++) 
        {
            parent[i] = i;
        }

        std::vector<Edge> mst_edges;

        for (const Edge& edge : edges) 
        {
            int x = find(parent, edge.src);
            int y = find(parent, edge.dest);

            if (x != y) 
            {
                mst_edges.push_back(edge);
                union_sets_kruskal(parent, rank, x, y);
            }
        }

        long total_cost = 0;
        for (const Edge& e : mst_edges) 
        {
            total_cost += e.cost;
        }
        std::cout << total_cost << std::endl;
    }

};

int main() 
{
    int n_vertices, n_edges;
    if (scanf("%d %d", &n_vertices, &n_edges) != 2) 
    {
        return 1;
    }

    Graph g(n_vertices);

    for(int i = 0; i < n_edges; i++) 
    {
        int vertex1, vertex2;
        long year, time, cost;

        if(scanf("%d %d %ld %ld %ld", &vertex1, &vertex2, &year, &time, &cost) != 5)
        {
            return 1;
        }
        g.add_edge(vertex1, vertex2, year, time, cost);
    }

    g.dijkstra(1);

    g.first_year_all_vertices_reachable();

    g.mst_using_cost();
}
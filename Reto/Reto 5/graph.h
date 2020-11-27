/*
Clase de graphos con lista de adyacencia y 
con metodos breadth y depth first search

Creado por:
Leonardo Chang

Fecha de Creación:   9/11/2020
Ultima Modificación: 26/11/2020
Modificado por:
Enrique Mondelli A01379363
Diego Mejía      A01024228
*/

#ifndef _GRAPH_H_
#define _GRAPH_H_

#include<iostream> 
#include <list>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

template <class T>
class GraphVertex
{
private:
    T val;
    std::vector<int> adj;
public: 
    ~GraphVertex() {};
    GraphVertex() {};
    GraphVertex(T _val) {val = _val;};

    T get_val() {return val;};
    void set_val(T _val) {val = _val;};

    std::vector<int> get_adj() {return adj;};
    void add_to_adj(int idx) {adj.push_back(idx);};
};

// A B C D E F G H
// 0 1 2 3 4 5 6 7
// A: 1, 2, 3
// B: 0
// C: 0, 3


template <class T>
class Graph
{
private:
    std::vector<GraphVertex<T>> nodes;
    bool is_directed;

public:
    ~Graph() {};
    Graph() {is_directed=true;}
    Graph(bool directed) {is_directed=directed;}

    void add_node(T val)
    {
        GraphVertex<T> node(val);
        nodes.push_back(node);
    }

    void add_edge(int src, int dst)
    {
        nodes[src].add_to_adj(dst);
        if (!is_directed)
            nodes[dst].add_to_adj(src);
    }

    int BFS(int start_vertex, T val)
    {
        vector<bool> visited(nodes.size(), false);
        queue<int> queue;

        visited[start_vertex] = true;
        queue.push(start_vertex);

        while(!queue.empty())
        {
            int currVertex = queue.front();
            if (nodes[currVertex].get_val() == val)
            {
                return currVertex;
            }
            queue.pop();

            for (auto& itr: nodes[currVertex].get_adj())
            {
                if (!visited[itr])
                {
                    visited[itr] = true;
                    queue.push(itr);
                }
            }
        }
        
        return -1;
    }

    void BFS_(int start_vertex)
    {
        vector<bool> visited(nodes.size(), false);
        queue<int> queue;

        visited[start_vertex] = true;
        queue.push(start_vertex);

        while(!queue.empty())
        {
            int currVertex = queue.front();
            cout << nodes[currVertex].get_val() << " ";
            queue.pop();

            for (auto& itr: nodes[currVertex].get_adj())
            {
                if (!visited[itr])
                {
                    visited[itr] = true;
                    queue.push(itr);
                }
            }
        }

        cout << endl;
    }

    void DFS(int start_vertex)
    {
        vector<bool> visited(nodes.size(), false);
        stack<int> stack;

        stack.push(start_vertex);

        while(!stack.empty())
        {
            int currVertex = stack.top();
            stack.pop();

            if (!visited[currVertex])
            {
                visited[currVertex] = true;
                cout << nodes[currVertex].get_val() << " ";
            }

            for (auto& itr: nodes[currVertex].get_adj())
            {
                if (!visited[itr])
                {
                    stack.push(itr);
                }
            }   
        }

        cout << endl;
    }

    vector<GraphVertex<T>> get_nodes()
    {
        return nodes;
    }
};

#endif
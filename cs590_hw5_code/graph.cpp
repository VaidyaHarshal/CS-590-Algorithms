#include <iostream>
#include <set>
#include <queue>

#include "graph.h"

using namespace std;

Graph::Graph(int nodes)
{
    this->nodes = nodes;
    this->matrix = new int*[nodes];

    for (int i = 0; i < nodes; ++i) {
        (this->matrix)[i] = new int[nodes];

        for (int j = 0; j < nodes; ++j) {
            (this->matrix)[i][j] = 0;
        }
    }
}

Graph::Graph(int **matrix, int nodes) {
    this->nodes = nodes;
    this->matrix = new int*[nodes];

    for (int i = 0; i < nodes; ++i) {
        (this->matrix)[i] = new int[nodes];

        for (int j = 0; j < nodes; ++j) {
            (this->matrix)[i][j] = matrix[i][j];
        }
    }
}

Graph::~Graph()
{
    for (int i = 0; i < this->nodes; ++i) {
        delete[] (this->matrix)[i];
    }
    delete[] this->matrix;
}

bool Graph::set_edge(int i, int j, int edge)
{
    if (i < this->nodes && j < this->nodes && i >= 0 && j >= 0) {
        (this->matrix)[i][j] = edge;
        return true;
    }

    return false;
}

void Graph::dfs()
{
	set<int>* visited = new set<int>;
	int start = 0;
	dfs(start,visited);
	for(int i=0;i<nodes;i++){
		if(visited->count(i)==0)
			dfs(i,visited);
	}
	delete visited;
}
void Graph::dfs(int start, set<int> *visited)
{
    cout<<"  "<<start<<" ";
	visited->insert(start);
	for(int i=0; i < nodes; i++){
			if(matrix[start][i]!=0 && visited->count(i)==0){
				dfs(i,visited);
			}
		}	
}
void Graph::bfs(int start)
{
    set<int>* visited = new set<int>;
	bfs(start,visited);
	delete visited;
}
void Graph::bfs(int start, set<int> *visited)
{
	visited = new set<int>;
    queue<int> que;
    visited -> insert(start);
    que.push(start);

    while (!que.empty())
    {
        int var1 = que.front();
        cout << var1 << " ";
        que.pop();

        for (int i = 0; i < nodes; i++)
        {
            if (matrix[var1][i] > 0 && visited->count(i) == 0)
            {
                visited -> insert(i);
                que.push(i);
            }
        }
    }
    delete visited;
}


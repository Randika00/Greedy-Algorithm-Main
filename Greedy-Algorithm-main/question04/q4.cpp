/**
 * @file q4.cpp
 * @author Nipun Weerasiri
 * @brief Calculating Optimum Terminal Links using Prim's Algorithm
 * @date 2022-10-21
 */

#include <bits/stdc++.h>

using namespace std;

class Graph
{
private:
  int V;             // number of vertices
  float **adjMatrix; // adjacency matrix
  float *key;        // key values
  int *parent;       // parent array

public:
  /**
   * @brief Construct a new Graph object
   * @param n number of vertices
   */
  Graph(int n)
  {
    V = n;
    adjMatrix = new float *[V];
    for (int i = 0; i < V; i++)
    {
      adjMatrix[i] = new float[V];
      for (int j = 0; j < V; j++)
        adjMatrix[i][j] = 0;
    }
    key = new float[V];
    parent = new int[V];
  }

  /**
   * @brief Insert an edge to the graph
   * @param u source vertex
   * @param v destination vertex
   * @param w weight of edge
   */
  void insertEdge(int u, int v, float w)
  {
    adjMatrix[u][v] = w;
    adjMatrix[v][u] = w;
  }

  /**
   * @brief Find the minimum key value
   * 
   * @return vector<pair<int, int>> solution vector
   */
  vector<pair<int, int>> MSTPrim()
  {
    // intialize key and parent values
    for (int i = 0; i < V; i++)
    {
      key[i] = FLT_MAX;
      parent[i] = -1;
    }
    key[0] = 0;

    // create a min priority queue to store vertices
    priority_queue<pair<float, int>, vector<pair<float, int>>, greater<pair<float, int>>> pq;
    pq.push(pair(key[0], 0)); // push the first vertex

    set<int> added; // set to store added vertices

    // loop until the queue is empty
    while (!pq.empty())
    {
      // get the vertex with minimum key value
      int u = pq.top().second;
      pq.pop();

      // if vertex is already added, skip
      if (added.find(u) != added.end())
        continue;

      // add the vertex to the set
      added.insert(u);

      // loop through all the vertices
      for (int v = 0; v < V; v++)
        // if the vertex is not added and the weight is less than the key value
        if (adjMatrix[u][v] && key[v] > adjMatrix[u][v] && added.find(v) == added.end())
        {
          key[v] = adjMatrix[u][v];
          parent[v] = u;
          pq.push(pair(key[v], v));
        }
    }

    // create a vector to store the solution
    vector<pair<int, int>> solution;
    for (int i = 0; i < V; i++)
    {
      if (parent[i] != -1)
      {
        if (i < parent[i])
          solution.push_back(pair(i + 1, parent[i] + 1));
        else
          solution.push_back(pair(parent[i] + 1, i + 1));
      }
    }

    // sort the solution vector and return
    sort(solution.begin(), solution.end());
    return solution;
  }
};

// calculate the distance between two points
float calcDistance(pair<float, float> city1, pair<float, float> city2)
{
  return sqrt(pow(city1.first - city2.first, 2) + pow(city1.second - city2.second, 2));
}

int main()
{
  int n;
  cin >> n; // number of cities
  vector<pair<float, float>> cities(n);
  for (int i = 0; i < n; i++) // reading city coordinates
    cin >> cities[i].first >> cities[i].second;

  // create a graph with n vertices
  Graph g(n);
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      g.insertEdge(i, j, calcDistance(cities[i], cities[j]));

  // get the solution vector
  vector<pair<int, int>> solution = g.MSTPrim();

  cout << solution.size() << endl; // number of links

  for (int i = 0; i < n - 1; i++)
    cout << solution[i].first << " " << solution[i].second << endl;

  return 0;
}
#include <iostream>
#include <map>
#include <stack>
#include <vector>

class Graph {
private:
  std::map<int, bool> visited;
  std::vector<std::vector<int>> adjList;

public:
  Graph(int nodesCount) {
    this->adjList.resize(nodesCount);
  }

  void addEdge(int parent, int current){
    this->adjList[parent].push_back(current);
  }

  void DFS(int node) {
    // Create stack for nodes
    std::stack<int> stack;

    // Set node as visited
    this->visited[node] = true;

    // Push into stack
    stack.push(node);
   
    // Loop stack
    while (!stack.empty()) {
      // Get las node from stack
      int currentNode = stack.top();

      std::cout << currentNode << "\n";
      // Pop node from stack
      stack.pop();

      // Loop poped node neighbors
      for (auto neighbor: this->adjList[currentNode]) {
        // If not visisted push into queue and set as visited
        if (!this->visited[neighbor]) {
          this->visited[neighbor] = true;
          stack.push(neighbor);
        }
      }
    }
  }
};

int main() { 
  Graph graph = Graph(7);

  graph.addEdge(0, 1);
  graph.addEdge(0, 2);
  graph.addEdge(0, 3);
  graph.addEdge(1, 4);
  graph.addEdge(2, 5);
  graph.addEdge(3, 6);
  graph.addEdge(4, 5);
  graph.addEdge(6, 5);
  graph.DFS(0);

  return 0;

}

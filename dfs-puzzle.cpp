#include <stack>
#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>

class Node {
public:
  std::vector<Node*> children;
  std::vector<int> initialVector;
  Node *parent;

  Node(std::vector<int> _initialVector, Node *_parent) {
    initialVector = _initialVector;
    parent = _parent;
  }

  void printPuzzle(std::vector<int> vectorValues) {
    int count = 0;
    for (auto i : vectorValues) {
      if (count % 3 == 0) std::cout << "\n";

      std::cout << i << ' ';
      count++;
    }
  }

  int findZero() {
    std::vector<int>::iterator it = std::find(this->initialVector.begin(), this->initialVector.end(), 0);
    return static_cast<int>(std::distance(this->initialVector.begin(), it));
  }

  void moveUp() {
    int zPos = this->findZero();
    std::vector<int> temp = this->initialVector;

    if (zPos >= 3) {
      std::swap(temp[zPos], temp[zPos - 3]);
      Node* child = new Node(temp, this);
      children.push_back(child);
    }
  }

  void moveDown() {
    int zPos = this->findZero();
    std::vector<int> temp = this->initialVector;

    if (zPos < 6) {
      std::swap(temp[zPos], temp[zPos + 3]);
      Node* child = new Node(temp, this);
      children.push_back(child);
    }
  }

  void moveRight() {
    int zPos = this->findZero();
    std::vector<int> temp = this->initialVector;

    if (zPos % 3 < 2) {
      std::swap(temp[zPos], temp[zPos + 1]);
      Node* child = new Node(temp, this);
      children.push_back(child);
    }
  }

  void moveLeft() {
    int zPos = this->findZero();
    std::vector<int> temp = this->initialVector;

    if (zPos % 3 > 0) {
      std::swap(temp[zPos], temp[zPos - 1]);
      Node* child = new Node(temp, this);
      children.push_back(child);
    }
  }
};

bool isVisited(std::stack<Node*> stack, Node* currentNode) {
  bool exist = false;

  while (!stack.empty()) {
    if (stack.top()->initialVector == currentNode->initialVector) {
      exist = true;
    }

    stack.pop();
  }

  return exist;
}

void traceSolution(std::vector<Node*> sol, Node* g) {
  Node* curr = g;
  sol.push_back(g);

  while (curr->parent != nullptr) {
    curr = curr->parent;
    sol.push_back(curr);
  }

  std::reverse(sol.begin(), sol.end());
  std::cout << "printing solution" << std::endl;

  int depth = 0;
  for (auto i : sol) {
    depth += 1;
    i->printPuzzle(i->initialVector);
    std::cout << "\n";
  }

  std::cout << "Depth: " << depth - 1 << std::endl;
}

class Puzzle {
private:
  std::stack<Node*> stack;
  std::stack<Node*> visited;
  std::vector<int> finalVector;
  int nodesCount;

public:
  Puzzle(std::vector<int> _initialVector, std::vector<int> _finalVector) {
    Node *initialNode = new Node(_initialVector, nullptr);
    this->stack.push(initialNode);

    this->finalVector = _finalVector;
    this->nodesCount = 1;
  }

  void DFS(std::vector<int> initialVector) {
    std::vector<Node*> solution;

    std::cout << "Searching for solution..." << std::endl;

    while (!this->stack.empty()) {
      Node* currentNode = this->stack.top();

      this->visited.push(currentNode);
      stack.pop();

      currentNode->moveRight();
      currentNode->moveUp();
      currentNode->moveLeft();
      currentNode->moveDown();

      this->nodesCount++;

      for (auto currentChild : currentNode->children) {

        // If currentChild is equal to finalVector retunr void
        if (currentChild->initialVector == this->finalVector) {
          std::cout << "Solution found :)" << std::endl;

          // Print solution steps
          traceSolution(solution, currentChild);
          std::cout << "Nodes count: " << this->nodesCount << std::endl;
          return;
        }

        if (!isVisited(this->stack, currentChild) && !isVisited(this->visited, currentChild)) {
          this->stack.push(currentChild);
        }
      }
    }
  }

};

int main() {
  std::vector<int> initialVector = {
    1, 2, 3,
    0, 4, 6,
    7, 5, 8
  };

  std::vector<int> finalVector = {
    1, 2, 3,
    4, 5, 6,
    7, 8, 0
  };

  Puzzle puzzle(initialVector, finalVector);

  auto start_time = std::chrono::high_resolution_clock::now();

  puzzle.DFS(initialVector);

  auto end_time = std::chrono::high_resolution_clock::now();
  auto duration_sec = std::chrono::duration<double>(end_time - start_time).count();
  std::cout << "Time consumption: " << duration_sec << " seconds" << std::endl;

  return 0;
}

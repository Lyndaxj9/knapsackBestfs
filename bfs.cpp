#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <algorithm>
#include <queue>
#include <vector>

//will probably use a struct for state space tree
struct node{
  int profit;
  int weight;
  float ratio;
  int totalprofit;
  int totalweight;
  int upperBound;
  int level;
  struct node * leftnode;
  struct node * rightnode;
};

struct statenode{
  int profit;
  int weight;
  int bound;
  struct statenode * left;
  struct statenode * right;
};

bool nodeSorter(struct node const& lhs, struct node const& rhs);
bool operator<(struct node const& lhs, struct node const& rhs);
float bound(int level, int totalweight, int totalprofit, struct node nodeArray[], int c, int n);
void initTree(struct statenode * head, struct node nodeArray[], int c, int n);
void createTree(struct statenode * node, int i, struct node nodeArray[], int n, int c);

int main(int argc, char **argv) {
  const char* inputFile;
  const char* outputFile;  
  
  if (argc < 3){
    std::cout<<"Usage: ./BestFirstSearch <input.txt> <output.txt>"<<std::endl;
    return 1;
  } else {
    inputFile = argv[1];
    outputFile = argv[2];
  }
  
  int numberitems;
  int capacity;
  std::string line, chunk;

  //-- Open input file ----------------------------------------------
  std::ifstream knapFile(argv[1]);
  //if(knapFile)
  std::getline(knapFile, line);
  std::stringstream ss(line);
  std::getline(ss, chunk, ',');
  numberitems = atoi(chunk.c_str());
  std::getline(ss, chunk, ',');
  capacity = atoi(chunk.c_str());

  std::cout<<"num of items "<<numberitems<<std::endl;
  std::cout<<"c: "<<capacity<<std::endl;
  struct node nodes[numberitems]; 
  int counter = 0;
  
//-- Parse file reading in all item values --------------------------
  while (std::getline(knapFile, line)){
    ss.clear();
    ss.str(line);
    std::getline(ss,chunk, ',');
    nodes[counter].weight = atoi(chunk.c_str());
    std::getline(ss, chunk, ',');

    nodes[counter].profit = atoi(chunk.c_str());
    nodes[counter].ratio = nodes[counter].profit/nodes[counter].weight;
    nodes[counter].totalweight = nodes[counter].totalprofit = 0;
    std::cout<<"Weight: "<<nodes[counter].weight<<" Profit: "<<nodes[counter].profit<<" Ratio: "<<nodes[counter].ratio<<std::endl;
    counter++;
  }

//-- Sort array based on ratio --------------------------------------
  std::sort(nodes, nodes+numberitems, &nodeSorter);
  /* print sorted array ---------------------------------------------
  for(int i = 0; i < numberitems; i++){
    std::cout<<"ratio: "<<nodes[i].ratio<<std::endl;
  }*/

//-- tree?
  struct statenode * roothead;
  initTree(roothead, nodes, capacity, numberitems);
//  struct node head = nodes[0];
//  for(int i = 0; i<numberitems; i++){
//    
//  }

//-- bfs -
//  std::priority_queue<struct node, std::vector<struct node>, std::greater<struct node> > pq;
//  struct node head = nodes[0];
//  int best = head.profit;
//  pq.push(head);
// 
//  while(!pq.empty()){
//    pq.pop();
//     
//  }



//-- Procedure Knapsack ---------------------------------------------
//  std::priority_queue<struct node, std::vector<struct node>, std::greater<struct node> > pq;
//  struct node root = nodes[0];
//  int best = 0;
//  root.level = root.totalprofit = root.totalweight = 0;
//  //calculate bound 
//  std::cout<<"root totweight: "<<root.totalweight<<std::endl;
//  root.upperBound = bound(root.level, root.totalweight, root.totalprofit,  nodes, capacity, numberitems);
//  std::cout<<"Root bound: "<<root.upperBound<<std::endl;
//  pq.push(root);
//  
//  while (!pq.empty() && root.level+1<numberitems){
//    struct node v = pq.top();
//    std::cout<<"pq bound: "<<v.upperBound<<std::endl;
////    if(v.level+1 < numberitems){
////      struct node left = nodes[v.level+1];
////      left.level = v.level+1;
////      struct node right = nodes[v.level+1];
////      right.level = v.level+1;
////      break;
////    }
//    struct node left = nodes[v.level+1];
//    left.level = v.level+1;
//    struct node right = nodes[v.level+1];
//    right.level = v.level+1;
//
//    pq.pop();
//    if (v.upperBound > best){
////        struct node left = nodes[v.level+1];
//        left.totalweight = v.totalweight + nodes[v.level].weight;
//        left.totalprofit = v.totalprofit + nodes[v.level].profit;
////        *v.leftnode = nodes[v.level+1];
////      v.leftnode->level = v.level+1;
////      v.leftnode->totalweight = v.totalweight + nodes[v.level].weight;
////      v.leftnode->totalprofit = v.totalprofit + nodes[v.level].profit; 
//    }
//    if (left.totalweight <= capacity && left.totalprofit > best){
////      best = v.leftnode->totalprofit;    
//        best = left.totalprofit;
//    }
//    if (bound(left.level, left.totalweight, left.totalprofit, nodes, capacity, numberitems) > best){
////      pq.push(*(v.leftnode));
//        pq.push(left);
//    }
//    right.totalweight = v.totalweight;
//    right.totalprofit = v.totalprofit;
//    right.upperBound = bound(right.level, right.totalweight, right.totalprofit, nodes, capacity, numberitems);
//    std::cout<<"rightbound: "<<right.upperBound<<std::endl;
//    if(right.upperBound > best){
//      pq.push(right);
//    }
////    v.rightnode->level = v.level+1;
////    v.rightnode->totalweight = v.totalweight;
////    v.rightnode->totalprofit = v.totalprofit;
////    v.rightnode->upperBound = bound(v.rightnode->level, nodes, capacity, numberitems);
////    if(v.rightnode->upperBound > best){
////      pq.push(*(v.rightnode));
////    }
//  }

//-- Creating Priority Queue ----------------------------------------
//  std::priority_queue<struct node, std::vector<struct node>, std::less<struct node> > pq;
//  for(int i = 0; i<numberitems; i++){
//    pq.push(nodes[i]);
//    std::cout<<nodes[i].ratio<<std::endl;
//  }
  //std::cout<<"Top: "<<pq.top().ratio<<std::endl;
  return 0;
}

void createTree(struct statenode * node, int i, struct node nodeArray[], int n, int c){
  struct statenode * yes = new struct statenode;
  struct statenode * no = new struct statenode;
  node->left = yes;
  node->left->profit = node[i-1].profit;
  node->left->weight = node[i-1].weight;
  node->left->bound = bound(i, node->left->weight, node->left->profit, nodeArray, c, n);
  node->right = no;  

}

void initTree(struct statenode * head, struct node nodeArray[], int c, int n){
  head->profit = 0;
  head->weight = 0;
  head->bound = bound(0, 0, 0, nodeArray, c, n);
  createTree(head, 1, nodeArray, n, c);
}

//-- Compute UpperBound Using KWF
float bound(int level, int totalweight, int totalprofit, struct node nodeArray[], int c, int n){
  float bound = totalprofit;

  int weight = totalweight;
  float fraction = 0;
  std::cout<<"weight: "<<weight<<" lvl: "<<level<<std::endl;
  while (weight < c && level < n){
    if (weight + nodeArray[level].weight <= c){
      weight += nodeArray[level].weight;
      bound += nodeArray[level].profit;
      std::cout<<"ratio: "<<nodeArray[level].ratio<<std::endl;
    } else {
        fraction = (float)(c - weight)/nodeArray[level].weight;
        weight = c;
        bound += nodeArray[level].profit * fraction;
    }
    level++;
  }
  std::cout<<"bound: "<<bound<<std::endl;
  return bound;
}

//-- Predicate function used to compare nodes based on ratio and profit
bool nodeSorter(struct node const& lhs, struct node const& rhs){
  if(lhs.ratio == rhs.ratio){
    return lhs.profit > rhs.profit;
  } else {
      return lhs.ratio > rhs.ratio;
  }
}

//-- change to be able to edit with upperbound
bool operator>(struct node const& lhs, struct node const& rhs){
  return lhs.upperBound > rhs.upperBound;
}

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

bool nodeSorter(struct node const& lhs, struct node const& rhs);
bool operator<(struct node const& lhs, struct node const& rhs);

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
    std::cout<<"Weight: "<<nodes[counter].weight<<" Profit: "<<nodes[counter].profit<<" Ratio: "<<nodes[counter].ratio<<std::endl;
    counter++;
  }

//-- Sort array based on ratio --------------------------------------
  std::sort(nodes, nodes+numberitems, &nodeSorter);
  /* print sorted array ---------------------------------------------
  for(int i = 0; i < numberitems; i++){
    std::cout<<"ratio: "<<nodes[i].ratio<<std::endl;
  }*/

//-- Creating Priority Queue ----------------------------------------
  std::priority_queue<struct node, std::vector<struct node>, std::less<struct node> > pq;
  for(int i = 0; i<numberitems; i++){
    pq.push(nodes[i]);
    std::cout<<nodes[i].ratio<<std::endl;
  }
  std::cout<<"Top: "<<pq.top().ratio<<std::endl;
  return 0;
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
bool operator<(struct node const& lhs, struct node const& rhs){
  return lhs.ratio < rhs.ratio;
}

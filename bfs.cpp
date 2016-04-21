#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <stdlib.h>

struct node{
  int profit;
  int weight;
  int level;
  int ratio;
  int bound;
};

struct statenode{
  int totprofit;
  int totweight;
  int bound;
  int level;  
  int* valid;
};

//-- Function Declaractions -----------------------------------------
bool nodeSorter (struct node const& lhs, struct node const& rhs);
bool stateSorter(struct statenode const& lhs, struct statenode const& rhs);
int bound(int i, int totweight, int totprofit, struct node * nodeArray, int c, int n);

int main(int argc, char **argv){
  const char* inputFile;
  const char* outputFile;

  if(argc < 3){
    std::cout<<"Usage: ./BestFirstSearch <input.txt> <output.txt>"<<std::endl;
    return 1;
  } else {
      inputFile = argv[1];
      outputFile = argv[2];
  }

  int numberitems;
  int capacity;
  std::string line, chunk;

//-- Open input file ------------------------------------------------
  std::ifstream knapFile(inputFile);
  //if(knapFile)
  std::getline(knapFile, line);
  std::stringstream ss(line);
  std::getline(ss, chunk, ',');
  numberitems = atoi(chunk.c_str());
  std::getline(ss, chunk, ',');
  capacity = atoi(chunk.c_str());

  struct node nodes[numberitems];
  int counter = 0;

//-- Parse file reading in all item values --------------------------
  while (std::getline(knapFile, line)){
    ss.clear();
    ss.str(line);
    std::getline(ss, chunk, ',');
    nodes[counter].weight = atoi(chunk.c_str());
    std::getline(ss, chunk, ',');

    nodes[counter].profit = atoi(chunk.c_str());
    nodes[counter].ratio = nodes[counter].profit/nodes[counter].weight;

    counter++;
  }
  ss.clear();
  knapFile.close();

//-- Sort array based on ratio --------------------------------------
  std::sort(nodes, nodes+numberitems, &nodeSorter);

//-- Best/Bound Knapsack --------------------------------------------
  std::vector<struct statenode> pq;  
  statenode v;
  statenode u;
  statenode b;

  int best = 0;
  v.level = 0;
  v.totprofit = 0;
  v.totweight = 0;
  v.bound = bound(-1, v.totweight, v.totprofit, nodes, capacity, numberitems);
//  int* array = new int[numberitems];
//  v.valid = array;
  v.valid = new int[numberitems];
  pq.push_back(v);

  int k = 0;
  int totalvisits = 0;
  while (!pq.empty()){
    int explore = 0;
    std::sort(pq.begin(), pq.end(), &stateSorter); 
    v = pq.front();
    //totalvisits++;
    std::cout<<"At level: "<<v.level<<"bound front: "<<v.bound<<std::endl;
    u.level = v.level+1; //u child of v
    u.valid = new int[numberitems];
    for(int i=0; i<numberitems; i++){
      u.valid[i] = v.valid[i];
    }
    pq.erase(pq.begin());
    //yes child
    //std::cout<<"v.bound: "<<v.bound<<std::endl;
    if (v.bound > best){
      u.totweight = v.totweight + nodes[v.level].weight;
      u.totprofit = v.totprofit + nodes[v.level].profit;
      u.valid[v.level] = 1;
      //update best
      //std::cout<<"u.totalprofit: "<<u.totprofit<<std::endl;
      //std::cout<<"u.totalweight: "<<u.totweight<<" capacity: "<<capacity<<std::endl;
      if ((u.totweight <= capacity) && (u.totprofit > best)){
        best = u.totprofit;
        b = u;
        b.valid = new int[numberitems];
        for(int i=0; i<numberitems; i++){
          b.valid[i] = u.valid[i];
        }
        std::cout<<"b.valid: "<<b.valid[v.level]<<std::endl;
        //std::cout<<"best now: "<<best<<std::endl;
        
        if(bound(v.level, u.totweight, u.totprofit, nodes, capacity, numberitems) > best){
          u.bound = bound(v.level, u.totweight, u.totprofit, nodes, capacity, numberitems);
          //std::cout<<"At level: "<<u.level<<" Bound pushed: "<<u.bound<<std::endl;
          pq.push_back(u);
          explore = 1;
        }
      } else {
          k++;
          explore = 1;
      }
    
    }
    //no child
    u.totweight = v.totweight;
    u.totprofit = v.totprofit;
    u.bound = bound(v.level, u.totweight, u.totprofit, nodes, capacity, numberitems);
    std::cout<<"bvalidno: "<<b.valid[0]<<std::endl;
    u.valid[v.level] = 0;
    if(u.bound > best){
      pq.push_back(u);
      explore = 1;
    } else{
        k++;
    }

    if(explore == 1){
      totalvisits++;
    }

  }
  std::cout<<"best solution: "<<best<<std::endl;
  std::cout<<"leaf nodes: "<<k<<std::endl;
  std::cout<<"node visits: "<<totalvisits+k<<std::endl;
  std::cout<<"comeon: "<<b.valid[0]<<" "<<b.valid[2]<<std::endl;
  for(int i = 0; i<numberitems; i++){
    if (b.valid[i] == 1){
      std::cout<<"included profit: "<<nodes[i].profit<<std::endl;
      std::cout<<"included weight: "<<nodes[i].weight<<std::endl;
    }
  }
}
//-- Function Initializations ---------------------------------------

int bound(int i, int totweight, int totprofit, struct node * nodeArray, int c, int n){
  int bound = totprofit;
  //std::cout<<"enter profit: "<<totprofit<<std::endl;
  float fraction = 0;
  i++; 
  //std::cout<<"enter i: "<<i<<std::endl;
  while (totweight < c && i < n){
    //std::cout<<"enter while: "<<i<<std::endl;
    if (totweight + nodeArray[i].weight <= c){
      totweight += nodeArray[i].weight;
      bound += nodeArray[i].profit;
    } else {
        fraction = (float)(c - totweight)/nodeArray[i].weight;
        totweight = c;
        bound += nodeArray[i].profit * fraction;
    }
    i++;
  }
  return bound;
}

bool nodeSorter(struct node const& lhs, struct node const& rhs){
  if (lhs.ratio == rhs.ratio){
    return lhs.profit > rhs.profit;
  } else {
      return lhs.ratio > rhs.ratio;
  }
}

bool stateSorter(struct statenode const& lhs, struct statenode const& rhs){
  return lhs.bound > rhs.bound;
}

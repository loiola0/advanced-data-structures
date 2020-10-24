#include <cassert>

#include <WeightedGraph.hpp>

void test1(){
  WeightedGraph wg {10};
  assert(wg.num_verts == 10);
  assert(wg.num_edges == 0);

  wg.add_edge(1, 2, 10);
  wg.add_edge(8, 9, 20);

  assert(wg.num_edges == 2);
  assert(wg.has_edge(1, 2));
  assert(wg.has_edge(2, 1));
  assert(wg.has_edge(8, 9));
  assert(wg.has_edge(9, 8));
  assert(wg.edge_weight(1, 2) == 10);
  assert(wg.edge_weight(2, 1) == 10);
  assert(wg.edge_weight(8, 9) == 20);
  assert(wg.edge_weight(9, 8) == 20);

  wg.remove_edge(1, 2);
  assert(wg.num_edges == 1);
  assert(!wg.has_edge(1, 2));

  int w {wg.edge_weight(8, 9)};
  assert(w == 20);

  wg.set_edge_weight(8, 9, 1);

  w = wg.edge_weight(8, 9);
  assert(w == 1);

  wg.set_edge_weight(8, 9, 3);

  w = wg.edge_weight(8, 9);
  assert(w == 3);

  assert(!wg.has_edge(1, 2));
  assert(wg.edge_weight(1, 2) == 0);

  wg.set_edge_weight(1, 2, 100);
  assert(wg.edge_weight(1, 2) == 0);
}

void test2(){
  WeightedGraph wg {6};
  assert(wg.num_verts == 6);
  assert(wg.num_edges == 0);

  wg.add_edge(0, 1, 11);
  assert(wg.num_edges == 1);
  wg.add_edge(0, 2, 11);
  assert(wg.num_edges == 2);
  wg.add_edge(0, 3, 8);
  assert(wg.num_edges == 3);
  wg.add_edge(0, 4, 3);
  assert(wg.num_edges == 4);
  wg.add_edge(1, 3, 1);
  assert(wg.num_edges == 5);
  wg.add_edge(1, 5, 42);
  assert(wg.num_edges == 6);
  wg.add_edge(2, 3, 7);
  assert(wg.num_edges == 7);
  assert(wg.has_edge(2, 4) == false);
  wg.add_edge(2, 4, 1);
  assert(wg.has_edge(2, 4) == true);
  assert(wg.num_edges == 8);
  assert(wg.has_edge(3, 5) == false);
  wg.add_edge(3, 5, 5);
  assert(wg.has_edge(3, 5) == true);
  assert(wg.num_edges == 9);
}

void test3(){
  WeightedGraph G {5};

  G.add_edge(0,1,5);
  G.add_edge(0,3,3);
  
  G.add_edge(3,4,10);
  G.add_edge(4,2,1);

  G.add_edge(3,1,8);
  G.add_edge(4,1,2);

  

  std::vector<std::tuple<long unsigned int,long unsigned int,int>> n = G.kruskal();

  int weight = mst_return(n);

  assert(weight == 11);

}

void test4(){
  std::string archive;
  
  std::cout<<"Type the name of the file with the extension."<<std::endl;

  std::cin>>archive;

  WeightedGraph W {archive};

  std::vector<std::tuple<long unsigned int,long unsigned int,int>> n = W.kruskal();

  int weight = mst_return(n);

  if(archive == "Graph-1.txt"){
      assert(weight == 11);
  }

  if(archive == "Graph-2.txt"){
      assert(weight == 17);
  }

  if(archive == "Graph-3.txt"){
      assert(weight == 11);
  }

}

int main(){
  test1();
  test2();
  test3();
  test4();

  return 0;
}
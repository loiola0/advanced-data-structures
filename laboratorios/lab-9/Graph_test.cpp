#include <cassert>
#include <iostream>
#include <Graph.hpp>

#include <vector>


void test_digraph(){
  Digraph D {20};

  assert(D.num_verts == 20);

  D.add_edge(1, 2);


  assert(D.out_degree(1)==1);
  assert(D.out_degree(2)==0);
  
  assert(D.in_degree(1)==0);
  assert(D.in_degree(2)==1);

  

  assert(D.has_edge(1,2));
  assert(D.num_edges == 1);

  D.add_edge(1,2);

  assert(D.has_edge(1,2));
  assert(D.num_edges == 1);

  D.add_edge(3, 4);

  assert(D.has_edge(3,4));
  assert(D.num_edges == 2);

  D.remove_edge(2,3);

  assert(D.num_edges == 2);

  D.remove_edge(1,2);

  assert(!D.has_edge(1,2));
  assert(D.num_edges == 1);
}

void test_graph(){
  Graph G {20};

  assert(G.num_verts == 20);

  G.add_edge(1, 2);

  assert(G.has_edge(1,2));
  assert(G.has_edge(2,1));
  assert(G.num_edges == 1);

  G.add_edge(3,4);

  assert(G.has_edge(3,4));
  assert(G.has_edge(4,3));
  assert(G.num_edges == 2);

  G.add_edge(3,4);
  G.add_edge(4,3);

  assert(G.has_edge(3,4));
  assert(G.has_edge(4,3));
  assert(G.num_edges == 2);

  G.remove_edge(2,3);

  assert(G.num_edges == 2);

  G.remove_edge(1,2);

  assert(!G.has_edge(1,2));
  assert(!G.has_edge(2,1));
  assert(G.num_edges == 1);
}

void moreTests(){
    Digraph A {4};

    A.add_edge(2,1);
    A.add_edge(2,3);

    A.add_edge(2,0);
    A.add_edge(1,2);

    A.add_edge(3,1);
    A.add_edge(0,3);

    A.add_edge(0,1);
    
    
    assert(A.max_out_degree().first == 3);
    assert(A.max_out_degree().second == 2);
    assert(A.min_out_degree().first == 1);
    assert(A.min_out_degree().second == 3);

    
    assert(A.max_in_degree().first == 3);
    assert(A.max_in_degree().second == 1);
    assert(A.min_in_degree().first == 1);
    assert(A.min_in_degree().second == 2);


    assert(A.max_degree().first == 4);
    assert(A.max_degree().second == 2);
    assert(A.min_degree().first == 3);
    assert(A.min_degree().second == 3);
    
   
}


void test_search(){
    Digraph G {7};

    G.add_edge(0,2);
    G.add_edge(0,3);

    G.add_edge(2,1);
    G.add_edge(2,4);

    G.add_edge(4,5);
    G.add_edge(3,6);
    //vector to aid the search in width.
    std::vector<Digraph::size_type> vecAux {};

    //vector with vertices in the desired order.
    //corrected correct.
    std::vector<Digraph::size_type> vec {0,2,3,1,4,6,5};

    //invalid order.TO TEST
    std::vector<Digraph::size_type> vecWithTestErro {0,2,4,1,5,3,6};

    breadth_first_search(G,0,
                         [&vecAux](Digraph::size_type i){
                            vecAux.push_back(i);
                         });
    
    int size = vec.size();

    for(int i=0;i<size;i++){
      assert(vec[i] == vecAux[i]);
    }

}

void otherTest(){
    Digraph Y {3};

    Y.add_edge(0,1);
    Y.add_edge(1,2);

    std::vector<int> v = {0,1,2};

    assert(Y.valid_path(Y,v) == 1);

    
}


int main(){
  test_digraph();

  test_graph();

  test_search();

  moreTests();

  otherTest();

  return 0;
}
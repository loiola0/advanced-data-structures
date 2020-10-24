#include <vector>
#include <iostream>
#include <cassert>
#include <vector>
#include <bstree.hpp>

int main(){
  using BST = BSTree<int, std::string>;
  
  std::cout << "funcionando......" << std::endl;
  BST bst{};
 
  
  assert(bst.isEmpty());
  

  bst.insert(7, "node");
  bst.insert(5, "L");
  bst.insert(6, "LD");
  bst.insert(4, "LL");
  bst.insert(9, "D");
  bst.insert(8, "DL");
  bst.insert(10, "DD");
  

  auto vec = BST::posOrderVetor(bst);
  
  for (auto e : vec){
    std::cout << e.first << " " << e.second << std::endl;
  }

  return 0;
}

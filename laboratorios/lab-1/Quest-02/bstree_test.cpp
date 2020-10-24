#include <vector>
#include <iostream>
#include <cassert>
#include <vector>
#include <bstree.hpp>

int main(){
  std::cout << "funcionando......" << std::endl;
  BSTree<int, std::string> bst{};
 

  assert(bst.isEmpty());
  

  bst.insert(7, "node");
  bst.insert(5, "L");
  bst.insert(6, "LD");
  bst.insert(4, "LL");
  bst.insert(9, "D");
  bst.insert(8, "DL");
  bst.insert(10, "DD");
  
  bst.update(4,"victor");//troquei o valor do key 4
  
  //testo se deu certo na questão 03 onde verifico se meus métodos estão corretos
  return 0;
}

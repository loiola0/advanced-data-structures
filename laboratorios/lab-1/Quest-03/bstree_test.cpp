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
  //bst.insert(9, "D");
  //bst.insert(8, "DL");
  //bst.insert(10, "DD");

  bst.remove(5);
  
  
   // testes para saber se meus métodos estão corretos

  std::cout << "Imprimindo a árvore na ordem" <<std::endl;

  //bst.printInOrder();// imprimo a árvore na ordem

  std::cout << "fim da impressão" <<std::endl;

  bst.update(4,"victor");//atualizo o valor da key 4 para "victor"
  
  assert(bst.search(4)=="victor");
  

 
  assert(!bst.isEmpty());//verifica se a árvore é diferente de vazia

  bst.remove(2);//remove o nó que contém a chave 2
  
  
  assert(bst.search(2) == std::nullopt);//verifica se o nó 2 é null
 


 //fim dos testes
  return 0;
}

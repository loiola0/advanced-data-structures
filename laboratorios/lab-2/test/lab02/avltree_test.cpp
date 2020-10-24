#include <cassert>

// uncomment this to see some logging messages
// #define debug

#ifdef debug
#include <iostream>
#endif
#define checkBalance
#include <avltree.hpp>

int main(){
  //testes

  AVLTree<int, std::string> avl{};
  
  avl.insert(100,"victor");
  assert(*avl.search(100) == "victor"); //verifica se o nó foi inserido na árvore 

  //verifica se a inserção foi feita e se ultilizou de maneira correta o balanceamento
  assert(avl.verificar()==0);

  avl.insert(7,"martins");
  assert(*avl.search(7)=="martins"); //verifica se o nó foi inserido na árvore 

  //verifica se a inserção foi feita e se ultilizou de maneira correta o balanceamento
  assert(avl.verificar()==0);

  avl.insert(6,"oliveira");
  assert(*avl.search(6) == "oliveira"); //verifica se o nó foi inserido na árvore

//verifica se a inserção foi feita e se ultilizou de maneira correta o balanceamento
 assert(avl.verificar()==0);
  
  avl.insert(4,"jesus");
  assert(*avl.search(4) == "jesus"); //verifica se o nó foi inserido na árvore

  //verifica se a inserção foi feita e se ultilizou de maneira correta o balanceamento
  assert(avl.verificar()==0);

  std::cout << std::endl;
  //avl.remove(100);
 
   std::cout << "Imprimindo a árvore(inOrder)" <<std::endl;
  avl.inOrder();//imprimir em ordem a árvore
    
}

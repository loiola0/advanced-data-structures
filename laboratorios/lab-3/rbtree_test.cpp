// assert macro
#include <cassert>

#define checkProperties

// we are going to test this data structure
#include <rbtree.hpp>

using namespace std;

int main(){
  RBTree<int,string> rbtree{};

  rbtree.insert(1,"Gloria ao príncipe da paz");
  rbtree.insert(-12,"Jesus");
  //rbtree.insert(7,"victor");
  //rbtree.insert(8,"teste");
  //rbtree.insert(6,"teste");
  // rbtree.verCor(-12);
  // rbtree.verCor(1);
  assert(*rbtree.search(1) == "Gloria ao príncipe da paz");
  // assert(*rbtree.search(-12) == "jesus");
  // assert(*rbtree.search(7) == "victor");
 
  //imprimir a árvore em ordem
  //rbtree.printTree();

  //inserindo
   int i;
    for(i = 2;i<11;i++){
        rbtree.insert(i,"oi");
    }

  //fazendo os testes
    for(i = 1;i<11;i++){
        //se retorna algum erro é porque não é uma rbtree.
        assert(rbtree.obeysProperties(i)== 1);
    }

  
 
  
  return 0;
}

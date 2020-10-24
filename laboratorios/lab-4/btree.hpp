#pragma once

// array type
#include <array>
// smart pointers
#include <memory>
// optional type
#include <optional>
#ifdef debug
#include <iostream>
#endif

// generic b tree
template<typename Key, typename Val, unsigned int t>
class BTree{
private:
  // represents a page of BTree
  struct Page{
    // indicates whether page is a leaf
    bool leaf;
    // number of keys currently stored
    unsigned int numberKeys;
    // arrays of keys and vals
    std::array<Key, 2*t - 1> key;
    std::array<Val, 2*t - 1> val;
    // children array
    std::array<std::unique_ptr<Page>, 2*t> child;
    // constructor
    Page() : leaf{false},
             numberKeys{0},
             key{},
             val{},
             child{}
    {}
    // returns whether page is full
    bool isFull(){
      return numberKeys == 2*t - 1;
    }
    // searches for Key. In case it is not present, returns nothing
    std::optional<Val> search(Key k){ 
      unsigned int i = 0;
      // we go right searching for k
      while (i < numberKeys && k > key[i]){
        i++;
      }
      // now either key[i - 1] < k <= key[i] or i > numberKeys - 1
      // if k was found, we return the corresponding value
      if (i < numberKeys && k == key[i]){
        return val[i];
      }
      // now either key[i - 1] < k < key[i] or i > numberKeys - 1.  In
      // either case, we need to either go down or report an failed
      // search
      // if this page is a leaf, there is nowhere to go down, and the
      // search fails
      else if (leaf){
        return {};
      }
      // otherwise, we recurse into the appropriate child
      else{
        return child[i]->search(k);
      }
    }
    // splits a full child of this node, if this node is nonfull.  In
    // case child index is invald or the former conditions are not
    // met, returns false
    bool splitChild(unsigned int childIndex){
      if (!isFull() && childIndex <= numberKeys && child[childIndex]->isFull()){
        #ifdef debug
        std::cout << "conditions were met for splitting child " << childIndex << std::endl;
        #endif
        // a reference to the child to be split
        auto& splittingChild = child[childIndex];
        #ifdef debug
        std::cout << "took splittingChild reference" << std::endl;
        #endif
        // its new "right" sibling
        std::unique_ptr<Page> newSibling = std::make_unique<Page>();
        #ifdef debug
        std::cout << "created newSibling" << std::endl;
        #endif
        // newSibling is a leaf iff splittingChild is a leaf
        newSibling->leaf = splittingChild->leaf;
        // newSibling will be "on the right side" of splittingChild,
        // so newSibling receives the last t - 1 Key Val pairs of
        // splittingChild
        newSibling->numberKeys = t - 1;
        for (unsigned int i = 0; i < t - 1; i++){
          newSibling->key[i] = splittingChild->key[t + i];
          newSibling->val[i] = splittingChild->val[t + i];
        }
        #ifdef debug
        std::cout << "copied key val pairs from splittingChild to newSibling" << std::endl;
        #endif
        // if newSibling is not a leaf, it also receives some
        // children from splittingChild
        if (!newSibling->leaf){
          #ifdef debug
          std::cout << "newSibling is not leaf" << std::endl;
          #endif
          for (unsigned int i = 0; i < t; i++){
            newSibling->child[i] = std::move(splittingChild->child[t + i]);
          }
          #ifdef debug
          std::cout << "newSibling is not leaf. Moving some children" << std::endl;
          #endif
        }
        // splittingChild has lost its last t - 1 keys, and its median
        // key will go up to its parent.  This way, as it was a full
        // page, splittingChild had 2t - 1 keys, and after this
        // operation it will have only its first t - 1 keys
        splittingChild->numberKeys = t - 1;
        // we make room for newSibling at position childIndex + 1 ...
        for (unsigned int i = numberKeys; i >= childIndex + 1; i--){
          child[i + 1] = std::move(child[i]);
        }
        #ifdef debug
        std::cout << "moved some children to the right" << std::endl;
        #endif
        // ... and put it right there
        child[childIndex + 1] = std::move(newSibling);
        #ifdef debug
        std::cout << "put newSibling into its position" << std::endl;
        #endif
        // now we make room for the median key (and its val) of splittingChild at
        // position childIndex of this node ...
        if (numberKeys > 0){
          for(unsigned int i = numberKeys - 1; i >= childIndex; i--){
            #ifdef debug
            std::cout << "moving pair from position " << i << " to position " << i + 1 << std::endl;
            #endif
            key[i + 1] = key[i];
            val[i + 1] = val[i];
          }
          #ifdef debug
          std::cout << "moved some key val pairs to the right" << std::endl;
          #endif
        }
        // ... and put it right there
        key[childIndex] = splittingChild->key[t - 1];
        val[childIndex] = splittingChild->val[t - 1];
        // and this page just gained a new key
        numberKeys++;

        return true;
      }
      else{
        return false;
      }
    }

    //função para buscar o predecessor
    std::pair<Key,Val> maxKey(){
        
        //caso base: não temos mais filhos
        if(leaf){
            //retorna a chave e valor da ultima posição da página
            return std::make_pair(key[numberKeys-1],val[numberKeys-1]);
        }else{
            //chamada recursiva para a ultima chave de uma página não folha.
            return child[numberKeys]->maxKey();
        }
    }

    //buscar predecessor e apagar ele;
    void deleteMaxKey(){
        //caso base: não temos mais filhos
        if(leaf){
            //retorna a chave e valor da ultima posição da página
            numberKeys--;
        }else{
            //chamada recursiva para a ultima chave de uma página não folha.
            return child[numberKeys]->deleteMaxKey();
        }
        
    }

    //função apagar o minKey,
    //Ex de como chamar-la: child[index]->deleteMinKey().
    void deleteMinKey(){
      //caso chegamos em nó folha
        if(leaf){
          unsigned int i = 0;
            //apagamos o minKey, que é a primeira chave da página folha do filho direito
            //determinada chave
            while(i<numberKeys-1){
              key[i] = key[i+1];
              val[i] = val[i+1];
              i++;
            }
          numberKeys--;
        }else{
          //caso ainda não chegamos a um nó folha.
          return child[0]->deleteMinKey();
        }
    }

    //função para buscar o sucessor
    std::pair<Key,Val> minKey(){
        //caso estejamos em uma folha
        if(leaf){
            return std::make_pair(key[0],val[0]);
        }else{
            //como não estamos em uma folha
            return child[0]->predecessor();
        }
    }


    bool rotateKeysR(unsigned int keyIndex){
      if (keyIndex < numberKeys && !leaf && child[keyIndex]->numberKeys > t - 1 && !child[keyIndex + 1]->isFull()){
        // do key rotation

        //salva chave e valor da chave que deseja-se remover.
          Key k = key[keyIndex];
          Val v = val[keyIndex];

          
            //já aumenta o tamanho da página.
            // desloca uma casa pra direita todas as chaves.
            child[keyIndex+1]->numberKeys++;
            //deixa a primeira posição da página child[keyIndex+1] livre para descemos key e val.
            unsigned int i = child[keyIndex+1]->numberKeys-1 ;
            unsigned int k = child[keyIndex+1]->numberKeys;
            while(i>0){
                child[keyIndex+1]->key[i] = child[keyIndex+1]->key[i-1];
                child[keyIndex+1]->val[i] = child[keyIndex+1]->val[i-1];
                i--;
            }

            //copia filhos
            while(k>=0){
                child[keyIndex+1]->child[k] = std::move(child[keyIndex]->child[k-1]);
                k--;
            }

          //com a primeira posição da child[keyIndex] livre(key e val já salvos na próxima posição).
          //vamos descer key e val para ocupar a primeira posição da child[keyIndex+1].
          child[keyIndex+1]->key[0] = k;
          child[keyIndex+1]->val[0] = v;

          //agora vamos subir a última chave do child[index] para ocupar a posição de key, já que
          //sua chave e valor foram salvos na primeira posição de child[keyIndex+1].

          key[keyIndex] = child[keyIndex]->key[numberKeys-1];
          val[keyIndex] = child[keyIndex]->val[numberKeys-1];
          //como foi emprestado para o pai, então child[keyIndex] deve perder uma unidade de seu tamanho.
          //já que a ultima chave de child[keyIndex] foi copiada para o pai, então child[keyIndex] deve ter o tamanaho
          //reduzido após o emprestimo.
          child[keyIndex]->numberKeys--;

        return true;
      }
      else{
        return false;
      }
    }


    bool rotateKeysL(unsigned int keyIndex){
      if (keyIndex < numberKeys && !leaf && child[keyIndex + 1]->numberKeys > t - 1 && !child[keyIndex]->isFull()){
        // do key rotation

           //salva chave e valor da chave que deseja-se remover.
            Key k = key[keyIndex];
            Val v = val[keyIndex];

            //desce a chave para a página onde deseja-se remover chave está.
            //a chave que desce vai ocupar a última posição da página
            child[keyIndex]->key[child[keyIndex]->numberKeys] = k;
            child[keyIndex]->val[child[keyIndex]->numberKeys] = v;
            //a página como recebeu uma chave, então ela aumentou seu tamanho em um.
            child[keyIndex]->numberKeys++;


            //agora a irmã de child[keyIndex], ou seja, child[keyIndex+1], como tem mais do que 50%
          //sobe uma chave para seu pai, que é a mesma página que desceu uma chave para child[keyIndex].

           key[keyIndex] = child[keyIndex+1]->key[0];
           val[keyIndex] = child[keyIndex+1]->val[0];
           //pelo emprestimo da chave, child[keyIndex+1] dever perder uma unidade do tamanho da página.
           child[keyIndex]->numberKeys--;

        return true;
      }
      else{
        return false;
      }
    }

    bool mergeSiblingsWithKey(unsigned int keyIndex){
      if (keyIndex < numberKeys && !leaf && child[keyIndex]->numberKeys == t - 1 && child[keyIndex + 1]->numberKeys == t - 1){
        // do the merging
          unsigned int i = keyIndex;

          auto& left = child[keyIndex];
          auto& right = child[keyIndex+1];

          
          // a chave que deseja-se apagar será movida a ser a última chave do seu filho esquerdo.  
          left->key[left->numberKeys] = std::move(key[keyIndex]);
          left->val[left->numberKeys] = std::move(val[keyIndex]);
          left->numberKeys++;

          //(anda uma casa pra esquerda)realocando a página a partir do indice da onde a key foi copiada pro seu filho esquerdo.
          while(i<numberKeys-1){
              key[i] = std::move(key[i+1]);
              val[i] = std::move(val[i+1]);
              i++;
          }

          //uni o filho direito com o filho esquerdo(que já que está com 2*t-1) incluíndo a chave que vai ser apagada.
          unsigned int j = 0;
          unsigned int x = left->numberKeys;
          unsigned int y = left->numberKeys;//auxliar a cópia do filhos de right
          
            //copia as keys do filho dir para o filho esq.
            while(j<right->numberKeys){
                left->key[x] = std::move(right->key[j]);
                left->val[x] = std::move(right->val[j]);
                left->numberKeys++;
                x++;
                j++; 
            }


            //copiando filhos do right para a nova posição(fusão de left e right)
            unsigned int k = 0;
            //se right não for folha, então ele possui filhos
            if(!right->leaf){
                while(k<=right->numberKeys){
                    left->child[y] = std::move(right->child[k]);
                    k++;
                    y--;
                }
            }

        return true;
      }
      else{
        return false;
      }
    }

    //caso key esteja em uma page folha
    void removeKeyPageLeaf(unsigned int keyIndex){
        //i começa do indice da chave a ser removida.
        unsigned int i = keyIndex;
          // se o elemento a ser removido está página.          
          while(i<numberKeys-1){
              key[i] = key[i+1];
              val[i] = val[i+1];

              i++;
          }     
          numberKeys--;
    }
  };
  // inserts key val pair on nonfull page
  static void insertOnNonfullPage(Page* page, Key key, Val val){
    // index of "rightest" key
    int i = page->numberKeys - 1;
    // if page is a nonfull leaf, we do the insertion
    if (page->leaf){
      // while we search for the appropriate place to put key and val,
      // we also make room for them
      while (i >= 0 && key < page->key[i]){
        page->key[i + 1] = page->key[i];
        page->val[i + 1] = page->val[i];
        i--;
      }
      // we put key and val into their appropriate places ...
      page->key[i + 1] = key;
      page->val[i + 1] = val;
      // ... and update numberKeys
      page->numberKeys++;
    }
    // if page is not a leaf, we recurse to its appropriate child
    else{
      // looking for the child index to recurse
      while (i >= 0 && key < page->key[i]){
        i--;
      }
      // when we exit the while loop,
      // page->key[i] <= key < page->key[i+1], so insertion will
      // recurse into page->child[i + 1]
      i++;
      // before going down, we verify whether page->child[i] is full.
      // In case it is, we split it ...
      if (page->child[i]->isFull()){
        page->splitChild(i);
        // ... and see if the insertion should take place in the newly
        // created sibling, that is, we see if key is greater than the
        // median key that just went up from page->child[i] to page
        if (key > page->key[i]){
          i++;
        }
      }
      // finally, we perform the recursive insertion
      insertOnNonfullPage(page->child[i].get(), key, val);
    }
  }

  


  // root pointer
  std::unique_ptr<Page> root;
public:
  // constructor
  BTree() : root{nullptr}
  {}
  bool isEmpty(){
    return root == nullptr;
  }
  // search method
  std::optional<Val> search(Key key){
    if (root){
      return root->search(key);
    }
    else{
      return {};
    }
  }

  // insert method
  bool insert(Key key, Val val){
    // if key is present we just signal insertion did not occur
    #ifdef debug
    std::cout << "inserting key " << key << std::endl;
    #endif
    if (search(key)){
      #ifdef debug
      std::cout << "key " << key << " already inserted" << std::endl;
      #endif
      return false;
    }
    // otherwise we do the insertion
    else{
      // if tree is not empty
      if (root){
        // if root is full ...
        if (root->isFull()){
          #ifdef debug
          std::cout << "root is full. Splitting root" << std::endl;
          #endif
          // ... we create a new root, ...
          std::unique_ptr<Page> newRoot = std::make_unique<Page>();
          #ifdef debug
          std::cout << "created newRoot" << std::endl;
          #endif
          // ... make it the parent of the old root, ...
          newRoot->child[0] = std::move(root);
          #ifdef debug
          std::cout << "moved root as child 0 of newRoot" << std::endl;
          #endif
          // ... update root pointer, ...
          root = std::move(newRoot);
          #ifdef debug
          std::cout << "replaced root with newRoot" << std::endl;
          #endif
          // and split the old root
          root->splitChild(0);
          #ifdef debug
          std::cout << "split the old root (child 0 of root)" << std::endl;
          #endif
        }
        // here root is certain to be nonfull, so we make the insertion
        insertOnNonfullPage(root.get(), key, val);
      }
      // if there is no root
      else{
        #ifdef debug
        std::cout << "no root yet" << std::endl;
        std::cout << "creating root" << std::endl;
        #endif
        // we make a new one ...
        root = std::make_unique<Page>();
        // ... which is surely a leaf ...
        root->leaf = true;
        // ... and then we perform the insertion
        insertOnNonfullPage(root.get(), key, val);
      }
      // in either case, insertion took place
      return true;
    }
  }
  
};
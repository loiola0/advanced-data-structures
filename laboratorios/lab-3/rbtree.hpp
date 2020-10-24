// smart pointers
#include <memory>
// optional type
#include <optional>

#include <iostream>

#include <stack>

#include <vector>
#define checkProperties

// we are going to inherit from BSTree
#include <bstree.hpp>

// RBTree is a subclass of BSTree under the same type parameters
template<typename Key, typename Val>
class RBTree : public BSTree<Key, Val>{
private:
  // type alias
  using BST = BSTree<Key, Val>;
  // Color type
  enum class Color {red, black};
  // RBTree node
  
  struct RBTreeNode{
    Key key;
    Val val;
    // smart pointers
    std::unique_ptr<RBTreeNode> left;
    std::unique_ptr<RBTreeNode> right;
    // node color
    Color color;
    // RBTreeNode constructor. A new node is always red
    RBTreeNode(Key k, Val v) : key{k},
                               val{v},
                               left{nullptr},
                               right{nullptr},
                               color{Color::red}
    {}
    // returns Key Val pair whose Key is maximum.  We need this
    // information on every subtree for the removal algorithm
    std::pair<Key, Val> maxKey() const {
      if (right){
        return right->maxKey();
      }
      else{
        return std::make_pair(key, val);
      }
    }
    // returns Key Val pair whose Key is minimum
    std::pair<Key, Val> minKey() const {
      if (left){
        return left->minKey();
      }
      else{
        return std::make_pair(key, val);
      }
    }
 
  };


  


  //Questão 1

  static Color color(const RBTreeNode* node){
     if(node == nullptr){
        return Color::black;
     }else{
        return node->color;
     }
       
     
  }

  

  //Questão 02

  static void rotateR(RBTreeNode* node){
    
    // #ifdef debug
    // std::cout << "performing right rotation" << std::endl;
    // #endif
    // first we set aside all the moving subtrees
    std::unique_ptr<RBTreeNode> subtreeLL = std::move(node->left->left);
    std::unique_ptr<RBTreeNode> subtreeLR = std::move(node->left->right);
    std::unique_ptr<RBTreeNode> subtreeR  = std::move(node->right);
    // then we save the contents of the moving nodes
    std::tuple<Key, Val,Color> nodeContent   = std::make_tuple(node->key, node->val,node->color);
    std::tuple<Key, Val,Color> leftChildContent = std::make_tuple(node->left->key, node->left->val,node->left->color);
    // left child becomes node
    node->key = std::get<0>(leftChildContent);
    node->val = std::get<1>(leftChildContent);
    node->color = std::get<2>(leftChildContent);
    // node becomes the right child
    node->right = std::make_unique<RBTreeNode>(std::get<0>(nodeContent), std::get<1>(nodeContent));
    //já que o contrutor só aceita dois argumentos, usei a linha abaixo para dizer a cor do filho direito de node
    node->right->color = std::get<2>(nodeContent);

    // finally we rearrange the moving subtrees ...
    node->left         = std::move(subtreeLL);
    node->right->left  = std::move(subtreeLR);
    node->right->right = std::move(subtreeR);
    
     
  }

  static void rotateL(RBTreeNode* node){
    // first we set aside all the moving subtrees
    std::unique_ptr<RBTreeNode> subtreeRR = std::move(node->right->right);
    std::unique_ptr<RBTreeNode> subtreeRL = std::move(node->right->left);
    std::unique_ptr<RBTreeNode> subtreeL  = std::move(node->left);
    // then we save the contents of the moving nodes
    std::tuple<Key, Val,Color> nodeContent      = std::make_tuple(node->key, node->val,node->color);
    std::tuple<Key, Val,Color> rightChildContent = std::make_tuple(node->right->key, node->right->val,node->right->color);
    // right child becomes node
    node->key = std::get<0>(rightChildContent);
    node->val = std::get<1>(rightChildContent);
    node->color = std::get<2>(rightChildContent);//change color for color old node.
    // node becomes the left child
    node->left = std::make_unique<RBTreeNode>(std::get<0>(nodeContent),std::get<1>(nodeContent));
    //já que o contrutor só aceita dois argumentos, usei a linha abaixo para dizer a cor do filho esquerdo de node
    node->left->color = std::get<2>(nodeContent);
    // finally we rearrange the moving subtrees ...
    node->right        = std::move(subtreeRR);
    node->left->right  = std::move(subtreeRL);
    node->left->left = std::move(subtreeL);
    
    //std::cout<<node->key<<std::endl;
    //std::cout<<node->left->key<<std::endl;
    
  }

  
  //função mudar a cor dos nós
  static void colorFlip(RBTreeNode *node){

    if(node->color == Color::red){
      node->color = Color::black;
    }else{
       node->color = Color::red;
    }

    if(node->left){

      if(node->left->color == Color::red){
        node->left->color = Color::black;
      }else{
        node->left->color = Color::red;
      }

    }
   if(node->right){

    if(node->right->color == Color::red){
        node->right->color = Color::black;
    }else{
        node->right->color = Color::red;
     }

    }

  }
  //  //futura remoção
  // /*movendo nós vermelhos para esquerda
  //     -recebe um node e troca as cores dele e de seus filhos.
  //     -se o filho a "esquerda" do filho direito de node é vermelho,
  //       aplica uma rotação a direita no filho direito e uma rotação esquerda no pai(node).
  //     -troca as cores do nó pai e de seus filhos. 
  // */
  // static void movLeftRed(RBTreeNode *node){
  //   colorFlip(node);

  //     if(node->right->left->color == Color::red){
  //       node->right = rotateR(node->right);
  //       node = rotateL(node);
  //       colorFlip(node);
  //     }
    
  // }

  // /* Movendo nós vermelhos a direita
  //   -recebe um nó node e troca as cores dele e de seus filhos.
  //   -se o filho a "esquerda" do filho "esquerdo" é "vermelho", aplica um 
  //     rotação a direita do pai.
  //   -troca as cores do nó pai e de seus filhos.
  // */

  // static void movRightRed(RBTreeNode *node){
  //   colorFlip(node);

  //     if(node->left->left == Color::red){
  //       node = rotateR(node);
  //       colorFlip(node);
  //     }
   
  // }

  /*balanceamento
    -e o filho direito é vermelho: rotação à esquerda.
    -se o filho direito e o neto esquerdo é são vermelhos: rotação à direita.
    -se ambos os filhos são vermelhos: trocar a cor do pai e dos filhos.
  */



// método para ajudar em uma futura remoção.
  // static void balance(RBTreeNode *node){
  //   //nó vermelho é sempre filho a esquerda. 
  //   if(node->right->color == Color::red){
  //       node = rotateL(node);
  //   }
  //   //filho da direita e o neto da esquerda são vermelhos.
  //   if((node->left )&& (node->left->color) ==Color::red && (node->left->left) == Color::red){
  //       node = rotateR(node);
  //   }
  //   //os dois filhos são vermelhos: troca as cores
  //   if((node->left->color && node->right->color) == Color::red){
  //     //change color
  //       colorFlip(node);
  //   }
 
  // } 


  
 


  // implementation of RBTree
  template<typename Node>
  class RBTreeWithNode : public BST::template BSTreeWithNode<Node>{
  private:
    // type alias. We help the compiler a little
    using BSTWithNode = typename BST::template BSTreeWithNode<Node>;
  public:
    // builds an empty tree, delegating all the work to the superclass
    RBTreeWithNode() : BSTWithNode{}
    {}
    // builds a tree with a nonempty root
    RBTreeWithNode(Key key, Val val) : BSTWithNode{key, val}{
      // root is red. This need to be corrected
      std::stack<Node*> stk;

      stk = BSTWithNode::pathToExistingKey(key);

      stk.top()->color = Color::black;

    }

    //quarta questão

    void insertionMaintenance(RBTreeNode *node){

      std::stack<Node*> stk;
      stk = BSTWithNode::pathToExistingKey(node->key);

      // //guarda referência ao nó inserido(vulgo node, só que com outro nome).
      RBTreeNode *nodeNewInserted = stk.top();
      stk.pop();

      // //Refêrencia para o pai de node
      RBTreeNode *parentNode = stk.top();
      stk.pop();

      //Referência para o avô de node
      
      //se tiver no mínimo 3 nós na pilha, então seu tamanho no pior caso é maior que zero, assim temos um avô
      if(stk.size()>0){
        RBTreeNode *grandParentNode = stk.top();
      
        

          //guarda a raiz da árvore
          RBTreeNode *root = nullptr;
          while(stk.size()>0){
              root = stk.top();
              stk.pop();
          }

            
          if(grandParentNode){
            //analisamos se parentNode é filho left ou right
                RBTreeNode *uncleNode = nullptr;
              if(grandParentNode->left.get()== parentNode){
                    
                    if(grandParentNode->right.get()){

                        uncleNode = grandParentNode->right.get();
                    }
                    
              }else{
                  if(grandParentNode->left.get()){

                         uncleNode = grandParentNode->left.get();
                  }
                       
              }

              

          //só é chamada quando o pai é vermelho              
          if(color(parentNode) == Color::red){
                //uncleNode->color = Color::black;
             if(color(uncleNode) == Color::red){
                    
                    colorFlip(grandParentNode);
                    if(grandParentNode == root){
                      //std::cout<<"entrou aqui 0"<<std::endl;
                      grandParentNode->color = Color::black;
                    }else{
                      //std::cout<<"entrou aqui 1"<<std::endl;
                      insertionMaintenance(grandParentNode);
                    }
                }else{//caso o tio seja preto
                    //verifica se ou o tio ou o pai existem
                    //Verifica como pai se relaciona com o avô
                        
                        //2 caso
                     if(grandParentNode->left.get() == parentNode){
                        if(parentNode->right.get() == nodeNewInserted){
                            rotateL(parentNode);
                            grandParentNode->color = Color::red;
                            parentNode->color = Color::black;
                            rotateR(grandParentNode);
                                
                        }
                        //3 caso
                        if(parentNode->left.get() == nodeNewInserted){
                              grandParentNode->color = Color::red;
                              parentNode->color = Color::black;
                              rotateR(grandParentNode);
                        }

                     }else{
                       //2 espelhado
                        if(parentNode->left.get() == nodeNewInserted){
                            rotateR(parentNode);
                            grandParentNode->color = Color::red;
                            parentNode->color = Color::black;
                            rotateL(grandParentNode);           
                        }
                          //3 espelhado
                        if(parentNode->right.get() == nodeNewInserted){
                              grandParentNode->color = Color::red;
                              parentNode->color = Color::black;
                              rotateL(grandParentNode);
                        }
                     }

                    
                    
                 }
              }
                        
        }
     }
          
  }

  //função não oficial do laboratório.
  //verifica a cor de um nó inserido.
  void verificarCor(Key key){
    std::stack<Node*> stk;

    stk = BSTWithNode::pathToExistingKey(key);

    if(stk.top()->color == Color::black){
      std::cout<<"Nó preto"<<std::endl;
    }else{
      std::cout<<"Nó vermelho"<<std::endl;
    }
  }

  //funções para 5 questão

    //1ª primeira propriedade: verifica a raiz é preta

     bool rootIsBlack(RBTreeNode *node) const{
        if(color(node) == Color::black){
            return true;
        }else{
          return false;
        }
     }

    //2ª propriedade
    // funções que verifica se há nós vermelhos consecutivos;
    //função ler a pilha de nós vermelhos e verifica se há algum nó vermelho consecutivo
     bool notConsecutiveNodeRed(std::vector<Node*> v)const{
       bool result = true;
        int tam = v.size();
        for (int i = 0; i <tam; i++){
            if(v[i]->left){
              if(color(v[i]->left.get()) == Color::red){
                  result = false;
              }
            }
            if(v[i]->right){
              if(color(v[i]->right.get()) == Color::red){
                  result = false;
              }
            }
        }

        return result;
        
     }
     //função auxiliar para guadar todos os nós vermelhos da árvore a cada inserção.
     std::vector<Node*> vetor(RBTreeNode *node) const{
         std::vector<Node*> v1;
         std::vector<Node*> v2;
         std::vector<Node*> v3;
            if(node){
              if(node->left){
                  if(node->left.get()){
                    v1 = vetor(node->left.get());
                  }
              }
               

               if(color(node) == Color::red){
                  v3.push_back(node);
               }

               if(node->right){
                  if(node->right.get()){
                    v2 = vetor(node->right.get());
                  }
               }
            }

            for (int i = v1.size()-1; i >=0 ; i--){
                  v3.push_back(v1[i]);
                  v1.pop_back();
            }

            for (int i = v2.size()-1; i >=0 ; i--){
                  v3.push_back(v2[i]);
                  v2.pop_back();
            }

            
         return v3;   
     }

    
     //4ª propriedade o número de nós pretos a todo caminho é igual.
     //função para verificar o número de nós pretos nos caminhos de cada nó.

      std::vector<Node*> pathNodeBlacks(std::stack<Node*> pilha){
        //vector para salvar os nós pretos
        std::vector<Node*> v;

        Node *topo = pilha.top();

        while(pilha.size() > 0){
          //coleta nós pretos
          if(color(pilha.top()) == Color::black){
            v.push_back(topo);
          }
            pilha.pop();
        }

        return v;
        
      }


      //função que passeia a árvore e retorna a pilha de vectors só com nós pretos.
      //ela já pega a raiz(root) como nó preto
      std::stack<std::vector<Node*>> verifNodesBlack(RBTreeNode *node){
        //pilhas auxiliares para a recursão
        std::stack<std::vector<Node*>> pilhaDir;
        std::stack<std::vector<Node*>> pilhaEsq;
        //pilhas auxiliares
        std::stack<Node*> pilha;
        std::stack<std::vector<Node*>> auxPilha;
        //vector de nós pretos
        std::vector<Node*> aux;

        if(node){
          if(node->left){
            pilhaEsq = verifNodesBlack(node->left.get());
          }
          //verifica se existe ao menos um filho null
          if((node->left == nullptr) || (node->right == nullptr)){
            //salva os caminho do nó
             pilha = BSTWithNode::pathToExistingKey(node->key);
             //faz o tratamento de nós(salva em um vector), ou seja, aux só vai ter nó preto.
             aux = pathNodeBlacks(pilha);
             //salva o vector de nós pretos em uma pilha.
             auxPilha.push(aux);
          }

          if(node->right){
            pilhaDir = verifNodesBlack(node->right.get());
          }

        }

        std::vector<Node*> &topo = pilhaEsq.top();
        //copia a primeira pilha para a pilha aux(a que vai ser retornada)
        while(pilhaEsq.size() > 0){
           auxPilha.push(topo);
           pilhaEsq.pop();
        }

       std::vector<Node*> &topo1 = pilhaDir.top();
        //copia a segunda pilha para a pilha aux(a que vai ser retornada)
        while(pilhaDir.size() > 0){
           auxPilha.push(topo1);
           pilhaDir.pop();
        }
        return auxPilha;           
      }

      //função que verifica se os caminhos da árvore tem a mesma quantidade de nós pretos.
      bool validPathBlack(std::stack<std::vector<Node*>> p){
          bool result = true;
          int tamAux1;
          int tamAux2;

          //caso haja mais de um caminho na rbtree, só assim podemos conferir
          if(p.size()>1){

          
            //passea os vector a fim de saber o tamanho de cada caminho.
            while(p.size()>0){
              //salva o tamanho do top
                tamAux1 = p.top().size();
                //valor do top já foi salvo, então damos um pop
                p.pop();
                //caso a pilha tenha vector(s) ainda
                if(p.size()>0){
                  //salva o segundo tamanho a ser comparado.
                  tamAux2 = p.top().size();
                  p.pop();
                }

                if(tamAux1!=tamAux2){
                  result = false;
                }
            }

          }

          return result;
      }




    // inserts a Key Val pair into the tree. Return value indicates
    // whether insertion occurred
    bool insert(Key key, Val val){
      // the actual insertion is done by BSTreeWithNode
      bool hasInserted = BSTWithNode::insert(key, val);
      if (hasInserted){
        // do rb stuff
        
        
        std::stack<Node*> pilha = BSTWithNode::pathToExistingKey(key);

          //se o tamanho da pilha for 1 significa que esse nó é a raiz e raiz é preta.
          if(pilha.size()==1){
            pilha.top()->color = Color::black;
          }else if(pilha.size()>=3){
              insertionMaintenance(pilha.top());
          }

          obeysProperties(key);

      }
      return hasInserted;
    }
    // we are not going to implement remove this time
    bool remove(Key key) = delete;


    bool obeysProperties(Key key){
      //ponteiro para a raiz
      RBTreeNode *root = nullptr;

      //guarda o caminho da chave até a chave
      std::stack<Node*> pilha = BSTWithNode::pathToExistingKey(key);

      //função que descobre quem é a raiz(roor) e ajuda outras funções a saberem sobre as invariantes.
       while(pilha.size()>0){
          root = pilha.top();
          pilha.pop();
        }

          
      //se a raiz existir
        if(root){
          //se todas as propriedades forem verdadeiras, realemente estamos em rbtree.
            if((rootIsBlack(root) == 1)&&(notConsecutiveNodeRed(vetor(root))==1)&&(validPathBlack(verifNodesBlack(root))==1)){
                 return true;
            }
            
            
           
        }

      return false;

    }

   

    void imprimir(){//dentro da AVLTreeWithNode herdando da BSTreeWithNode
      BSTWithNode::impressao();
    }

  };
  // RBTree with proper type node
  RBTreeWithNode<RBTreeNode> rbtree;
public:
  // builds an empty tree
  RBTree() : rbtree{}
  {}
  // builds a tree with nonempty root
  RBTree(Key key, Val val) : rbtree{key, val}
  {}
  // inserts Key Val pair. Return value indicates whether insertion
  // occurred
  bool insert(Key key, Val val){
    return rbtree.insert(key, val);
  }
  // we are not going to implement remove this time
  bool remove(Key key) = delete;
  // returns Val attached to Key. In case Key is not present, returns
  // nothing
  std::optional<Val> search(Key key) const {
    return rbtree.search(key);
  }
  // returns Key Val pair whose Val corresponds to the maximum BSTree
  // Key.  In case tree is empty, returns nothing
  std::optional<std::pair<Key, Val>> maxKey() const {
    return rbtree.maxKey();
  }
  // returns Key Val pair whose Val corresponds to the minimum BSTree
  // Key.  In case tree is empty, returns nothing
  std::optional<std::pair<Key, Val>> ninKey() const {
    return rbtree.ninKey();
  }

  void verCor(Key key){
    rbtree.verificarCor(key);
  }

#ifdef checkProperties
  bool obeysProperties(Key key){
    return rbtree.obeysProperties(key);
  }
#endif

  void printTree(){
    rbtree.imprimir();
  }
};

#ifndef weightedgraph_hpp
#define weightedgraph_hpp
// we use bstree to establish a relation between edges and weights
#include <bstree.hpp>
// we are going to use Graph class as a component
#include <Graph.hpp>
#include <fstream>
#include <math.h>
#include <algorithm>
#include <disjoint_sets.hpp>

// class to represent an undirected graph with weight values
// associated to its edges. Default weight type is int
template<typename Weight = int>
class WeightedGraph{
public:
  // we use the same size_tyoe as Graph
  using size_type = Graph::size_type;
private:
  // we use a binary search tree, indexed by pairs of size_type and
  // valued by Weight, to represent a mapping from edges to weights
  using map_edge_weight = BSTree<std::pair<size_type, size_type>, Weight>;
  // our private members: an undirected graph and an edge-weight mapping
  Graph graph_;
  map_edge_weight edge_weight_;

  static void adjust_endpoints_(size_type& u, size_type& v){
    if (u > v){
      std::swap(u, v);
    }
  }

public:
  // public const references to number of vertices and edges, respectively
  const size_type& num_verts;
  const size_type& num_edges;
  // simple constructor
  WeightedGraph(size_type num_verts)
    : graph_{num_verts}, edge_weight_{}, num_verts{graph_.num_verts}, num_edges{graph_.num_edges}
  {}

  //first quest.

    //function search number vertex in arquive.
    size_type numb_vertex_archive(std::string name_arqv){
 
        std::string nLine;
        std::ifstream archive(name_arqv);

        std::getline(archive,nLine);

        size_type num_vertex = std::atoi(nLine.c_str());

        return num_vertex;
    }

  
    //save vector of string converted to int in vector.

    size_type converte_to_size_type(std::string s){
       size_type word;

       word = std::atoi(s.c_str());

      return word;
    }
    //this function read weight of the archive and convert to integer.
    std::vector<size_type> read_weight_by_weight(std::string name){
           std::vector<size_type> weights = {};
           size_type wordInt;
           std::ifstream archive;

           archive.open(name);
           std::string word;
           archive >> word;
                while(archive >> word){
                    wordInt = converte_to_size_type(word);
                    weights.push_back(wordInt);
                }

          return weights;
    }

    
   std::vector<std::vector<size_type>> matrix(std::vector<size_type> v){
        size_type size = sqrt(v.size());
        std::vector<std::vector<size_type>> array_return = {};
        std::vector<size_type> vAux = {};

        size_type k = 0;
         for (size_t i = 0; i < size; i++){

           for (size_t j = 0; j < size; j++){

              vAux.push_back(v[k]);

              k++;         
            }
            array_return.push_back(vAux);
            vAux.clear();
          }
      
      return array_return;
         
    } 



    WeightedGraph(std::string name)
     : graph_{numb_vertex_archive(name)}, edge_weight_{}, num_verts{graph_.num_verts}, num_edges{graph_.num_edges}
    {

        std::vector<std::vector<size_type>> array = {};
        Weight peso;
        array = matrix(read_weight_by_weight(name));
        size_type size = array.size();

          //insert weights and edges in vertex's.      
            for(size_type i = 0;i<size-1;i++){
              for(size_type j = i+1;j<size;j++){
                //case in edge have a weight 0.
                //std::cout<<array[i][j]<<" ";
                  peso = array[i][j];
                  if(peso!=0){
                      add_edge(i,j,peso);
                    //std::cout<<array[i][j]<<" ";
                   
                  }
                              
              }
              //std::cout<<std::endl; 
            }
    }

  // determines whether an edge between u and v exists
  bool has_edge(size_type u, size_type v){
    return graph_.has_edge(u, v);
  }
  // adds edge betweem u and v associated with weight w. Returns false
  // if edge was already present
  bool add_edge(size_type u, size_type v, Weight w){
    // does nothing if edge already exists
    if (has_edge(u, v)){
      return false;
    }
    // otherwise ...
    else{

      // adjusts endpoints
      adjust_endpoints_(u, v);
      // adds edge ...
      graph_.add_edge(u, v);
      // and associate it with weight w
      edge_weight_.insert({u, v}, w);
      // signals to caller that edge was added
      return true;
    }
  }
  // removes edge betweem vertices u and v. If such an edge is absent,
  // returns false
  bool remove_edge(size_type u, size_type v){
    // if graph has edge ...
    if (has_edge(u, v)){
      // adjusts endpoints
      adjust_endpoints_(u, v);
      // removes it ...
      graph_.remove_edge(u, v);
      // and deletes its weight association
      edge_weight_.remove({u, v});
      // then signals to caller that removal has succeded
      return true;
    }
    // otherwise does nothing
    else{
      return false;
    }
  }
  // returns weight of edge between u amd v. In case such an edge does
  // not exist, returms default initialization value of Weight
  Weight edge_weight(size_type u, size_type v){
    if (has_edge(u, v)){
      // adjusts endpoints
      adjust_endpoints_(u, v);

      return *edge_weight_.search({u, v});
    }
    else{
      return {};
    }
  }
  // sets weight of edge betweem u and v to w. In case of a
  // nonexisting edge, does nothing
  void set_edge_weight(size_type u, size_type v, Weight w){
    if (has_edge(u, v)){
      // adjusts endpoints
      adjust_endpoints_(u, v);
      
      edge_weight_.update({u, v}, w);
    }
  }
  
  //second quest.
  std::vector<std::tuple<size_type, size_type,Weight>> return_edge_weight(){
      std::vector<std::tuple<size_type, size_type,Weight>> v = {};

      size_type size = num_verts;
      
        for(size_type i = 0;i<size-1;i++){
              for(size_type j = i+1;j<size;j++){
                  if(edge_weight(i,j)!=0){
                    v.push_back(std::make_tuple(i,j,edge_weight(i,j)));
                  }
              }
            //std::cout<<std::endl;
        }
      //std::cout<<v.size()<<std::endl;
      return v; 
  } 

  //third quest.
    //This function sorts in the weights in an increasing way a vector of tuples.
    void order_weight_vector(std::vector<std::tuple<size_type, size_type,Weight>> &v){
        
        std::sort(v.begin(), v.end(), [](const std::tuple<size_type, size_type,Weight> &x,
                                       const std::tuple<size_type, size_type,Weight> &y)
          {
            return std::get<2>(x) < std::get<2>(y);
          }
        );
    }

    //four quest.

    std::vector<std::tuple<long unsigned int,long unsigned int,Weight>> kruskal(){
        DisjointSet ds {num_verts};

        std::vector<std::tuple<long unsigned int,long unsigned int,Weight>> v = {};

        //vector with ordened weights.
        std::vector<std::tuple<long unsigned int,long unsigned int,Weight>> t = return_edge_weight();

        order_weight_vector(t);

        int size = t.size();

    
          //Pra cada aresta, vc verifica se os extremos tem o mesmo representante.
            for(int i = 0;i<size;i++){
                
                  if(!(ds.representative(std::get<0>(t[i])) == ds.representative(std::get<1>(t[i])))){
                    //caso não, adiciona a aresta para retorno e dá um join nos extremos dela
                    v.push_back(t[i]);
                    ds.join(std::get<0>(t[i]),std::get<1>(t[i]));

                  }
            }
    return v;
    }

  
};

static int mst_return(std::vector<std::tuple<long unsigned int,long unsigned int,int>> wg){
      int weight = 0;
      std::cout<<"---Printing Minimum Spanning Tree---"<<std::endl;
      
      for(std::tuple<long unsigned int,long unsigned int, int> i: wg){
          std::cout<<"Edge "<<std::get<0>(i)<<" and "<<std::get<1>(i)<<" with weight "<<std::get<2>(i)<<std::endl;

          weight+=std::get<2>(i);
      }

      std::cout<<"MST with weight: "<<weight<<std::endl;
    
    return weight;
  }
   
#endif
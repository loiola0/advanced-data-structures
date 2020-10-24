#include <cassert>
#include <string>
#include <binary_median_heap.hpp>

//função dara os testes
void test_median_heap(){
    BinaryMedianHeap<std::string> heap {};

    heap.insert(11,"glória ao príncipe da paz");
    heap.insert(10,"Jesus");
    heap.insert(12,"vida longa");
    heap.insert(13,"vida");
    heap.insert(13,"victor");

    

  auto test = heap.median_element();
  
  if(test){
    auto [prio,elem] = *test;
    //std::cout<<"Priority: "<<prio<<"-Element: "<<elem<<std::endl;

    assert(prio == 12);
    assert(elem == "vida longa");
  }

  heap.median_extract();

  auto test2 = heap.median_element();
  
  if(test2){
    auto [prio,elem] = *test2;
    //std::cout<<"Priority: "<<prio<<"-Element: "<<elem<<std::endl;

    assert(prio == 11);
    assert(elem == "glória ao príncipe da paz");
  }



}

int main(){
    test_median_heap();
}
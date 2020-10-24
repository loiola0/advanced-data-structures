#include <cassert>
#include <string>
#include <iostream>
#include <binary_heap.hpp>

void test_max(){
  BinaryMaxHeap<std::string> heap {};

  assert(heap.empty());

  heap.insert(10, "hahaha");
  heap.insert(40, "whwhwhw");
  heap.insert(25, "eita bahia");
  heap.insert(30, "aaa");
  heap.insert(70, "jjjj");
  heap.insert(20, "bbb");

  assert(heap.size() == 6);

 

  auto pr = heap.priority_element();

  if(pr){
    auto [prio,elem] = *pr;
    assert(prio == 70);
    assert(elem == "jjjj");
  }


 auto opt = heap.extract();

  if(opt){
    auto [prio,elem] = *opt;

    assert(prio == 70);
    assert(elem == "jjjj");
  }

}

void test_min(){
  BinaryMinHeap<std::string> heap {};

  assert(heap.empty());

  heap.insert(10, "hahaha");
  heap.insert(40, "whwhwhw");
  heap.insert(25, "eita bahia");
  heap.insert(30, "aaa");
  heap.insert(70, "jjjj");
  heap.insert(20, "bbb");

}

void test_median(){
  BinaryMedianHeap<std::string> heap {};
  
  heap.insert(1,"gloria ao principe da paz");
  heap.insert(2,"oi");
  heap.insert(3,"Jesus have power");
  heap.insert(4,"Jesusa");
  heap.insert(5,"Jesus2");
  heap.insert(6,"Jesus5");
  heap.insert(7,"Jesus3");
  heap.insert(8,"Jesua4");
  heap.insert(9,"Jesus7");

  
  //heap.test();
  //std::cout<<std::endl;
  //heap.test1();

  heap.median_extract();

  auto test = heap.median_element();
  
  if(test){
    auto [prio,elem] = *test;
    std::cout<<"Priority: "<<prio<<"-Element: "<<elem<<std::endl;
  }

  

}

int main(){
  test_max();

  test_min();

  //test_median();

  return 0;
}
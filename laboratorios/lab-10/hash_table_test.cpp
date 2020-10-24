#include <cassert>

#include <hash_table.hpp>

#include <vector>

#include <iostream>

void test_int_double(){
  HashTable<int, double> ht {};

  assert(ht.search(2) == std::nullopt);

  ht.insert(1, 10.0);
  ht.insert(2, 20.0);
  ht.insert(3, 30.0);
  ht.insert(4, 40.0);
  ht.insert(5, 50.0);
  ht.insert(6, 60.0);
  ht.insert(7, 70.0);
  ht.insert(8, 80.0);
  ht.insert(9, 90.0);
  ht.insert(10, 100.0);

  assert(*ht.search(1) == 10.0);
  assert(*ht.search(2) == 20.0);
  assert(*ht.search(3) == 30.0);
  assert(*ht.search(4) == 40.0);
  assert(*ht.search(5) == 50.0);
  assert(*ht.search(6) == 60.0);
  assert(*ht.search(7) == 70.0);
  assert(*ht.search(8) == 80.0);
  assert(*ht.search(9) == 90.0);
  assert(*ht.search(10) == 100.0);

  assert(*ht.remove(1) == 10.0);
  assert(ht.remove(1) == std::nullopt);
  assert(ht.search(1) == std::nullopt);
  assert(*ht.search(2) == 20.0);
  assert(*ht.search(3) == 30.0);
  assert(*ht.search(4) == 40.0);
  assert(*ht.search(5) == 50.0);
  assert(*ht.search(6) == 60.0);
  assert(*ht.search(7) == 70.0);
  assert(*ht.search(8) == 80.0);
  assert(*ht.search(9) == 90.0);
  assert(*ht.search(10) == 100.0);

  assert(*ht.remove(2) == 20.0);
  assert(ht.remove(2) == std::nullopt);
  assert(ht.search(2) == std::nullopt);
  assert(*ht.search(3) == 30.0);
  assert(*ht.search(4) == 40.0);
  assert(*ht.search(5) == 50.0);
  assert(*ht.search(6) == 60.0);
  assert(*ht.search(7) == 70.0);
  assert(*ht.search(8) == 80.0);
  assert(*ht.search(9) == 90.0);
  assert(*ht.search(10) == 100.0);

  assert(*ht.remove(7) == 70.0);
  assert(ht.remove(7) == std::nullopt);
  assert(ht.search(7) == std::nullopt);
  assert(*ht.search(3) == 30.0);
  assert(*ht.search(4) == 40.0);
  assert(*ht.search(5) == 50.0);
  assert(*ht.search(6) == 60.0);
  assert(*ht.search(8) == 80.0);
  assert(*ht.search(9) == 90.0);
  assert(*ht.search(10) == 100.0);

  assert(*ht.remove(5) == 50.0);
  assert(ht.remove(5) == std::nullopt);
  assert(ht.search(5) == std::nullopt);
  assert(*ht.search(3) == 30.0);
  assert(*ht.search(4) == 40.0);
  assert(*ht.search(6) == 60.0);
  assert(*ht.search(8) == 80.0);
  assert(*ht.search(9) == 90.0);
  assert(*ht.search(10) == 100.0);

  assert(*ht.remove(10) == 100.0);
  assert(ht.remove(10) == std::nullopt);
  assert(ht.search(10) == std::nullopt);
  assert(*ht.search(3) == 30.0);
  assert(*ht.search(4) == 40.0);
  assert(*ht.search(6) == 60.0);
  assert(*ht.search(8) == 80.0);
  assert(*ht.search(9) == 90.0);

  assert(*ht.remove(8) == 80.0);
  assert(ht.remove(8) == std::nullopt);
  assert(ht.search(8) == std::nullopt);
  assert(*ht.search(3) == 30.0);
  assert(*ht.search(4) == 40.0);
  assert(*ht.search(6) == 60.0);
  assert(*ht.search(9) == 90.0);
}

void test_worst_case(){

  std::vector<int> A = {15,8,2,6,9,10};

  auto x = worstCase(A,7);

        if(x){
        
          auto [first,second] = *x;
           
                std::cout<<first<<" and "<<second<<std::endl;
          }else{
                std::cout<<"Not Have Values!"<<std::endl;
        }
}

void test_medium_case(){
    std::vector<int> k = {3,2,4,5,7,9};

    

    auto opt = search_complement(k,12);
    
        if(opt){

            auto [first,second] = *opt;

            assert(first == 3 && second == 9);

          }else{
            std::cout<<"Not Have Values!"<<std::endl;
      }
          
        

}


void test_best_case(){
    std::vector<int> k = {3,2,4,5,7,9};

    auto opt = usingHashTables(k,16);
    
          if(opt){

              auto [first,second] = *opt;
            
              std::cout<<first<<" and "<<second<<std::endl;
                    //  assert(first == 9 && second == 7);
          }else{
              std::cout<<"Not Have Values!"<<std::endl;
          }
          

    

    
}


void arbitrary_amount(){
  int value;
  int amount;
  std::vector<int> v = {};

      std::cout<<"Digit the amount of arguments: "<<std::endl;

      std::cin>>amount;

        
      std::cout<<"Digit all values of vector: "<<std::endl;

        while(amount>0){
            std::cin>>value;

            v.push_back(value);

            amount--;
        }

    //eliminates front position of vector of arguments.
    std::vector<int> z = {};
    int size = v.size();

        for(int i=1;i<size;i++){
            z.push_back(v[i]);
        }



    auto a = usingHashTables(z,v.front());

      if(a){
        
        auto [first,second] = *a;  

            std::cout<<"The Sum Values For Finding "<<v.front()<<" Are "<<first<<" And "<<second<<std::endl;

          }else{
              std::cout<<"Not Have Values!"<<std::endl;
          }
        
}



int main(){
  test_int_double();
  test_worst_case();
  test_medium_case();
  test_best_case();
  arbitrary_amount();
  

  return 0;
}
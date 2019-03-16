#include <iostream>
#include <vector>
#include <utility>
#include <list>
#include <unordered_map>
#include <cassert>

using namespace std;

#define DEFAULT_CAPACITY 2;

typedef list<int>::iterator List_int_iterator;
typedef list<int> Queue; // maintains recently used pi
typedef Queue::iterator Queue_iterator;

class LRUCache{
  protected:
    unordered_map<int,pair<List_int_iterator,Queue_iterator>> dict;
    Queue key_queue;
    list<int> data_buffer;
    int max_capacity;
  
    void _update_queue(Queue_iterator q_it,int key){
      // update queue
        // delete the pointer
        key_queue.erase(q_it); // pointer to the queue remove the key
        
        // top of the queue will be most recently used
        key_queue.push_front(key); // push key to the front
    }
  
  public:
    LRUCache(){
      max_capacity = DEFAULT_CAPACITY;
    }
  
    LRUCache(int capacity): max_capacity(capacity){
      
    }
  
    ~LRUCache(){
      data_buffer.clear();
      key_queue.clear();
      dict.clear();
    }
  
    int get(int key){
      // assertion that buffer is not overflowing
      assert(data_buffer.size() <= max_capacity);
      
      auto it = dict.find(key);
      
      if(it != dict.end()){// if key found{
        
        auto dict_val = it->second; // pair value -> list_pointer, queue pointer
        int value = *(dict_val.first); // get the data
        
        _update_queue(dict_val.second, key); // update the queue
        
        // update hash table 
        dict_val.second = key_queue.begin(); //     
        it->second = dict_val;
        
        return value;
      }
      else
        return -1;
    }
  
    void put(int key, int value){
      
      // assertion that buffer is not overflowing
      assert(data_buffer.size() <= max_capacity);
      
      auto it = dict.find(key);
      if(it != dict.end()){ // if key found
        //
        auto it = dict.find(key);
        auto dict_val = it->second;
        
        // update value
        *(dict_val.first) = value; // update value
        
        // update queue
        _update_queue(dict_val.second, key);  
        
        // update hash table
        dict_val.second = key_queue.begin(); //     
        it->second = dict_val;
      }
      else{
        // pop the last element
        if(data_buffer.size() == max_capacity){
          
          // get the key to the last element and remove the key from the queue
          int key_purge = key_queue.back();
          key_queue.pop_back();
          
          // get the hash table value
          auto it = dict.find(key_purge);
          assert(it != dict.end()); // key must be present herex
          
          // get the queue iterator
          auto dict_val = it->second;
          List_int_iterator l_it = dict_val.first;
          data_buffer.erase(l_it); // delete that element from the buffer
          
          // remove the key from dict
          dict.erase(key_purge);
        }
          
        // add the element to the dict, buffer and queue
        data_buffer.push_front(value); // insert value
          
        List_int_iterator new_l_it = data_buffer.begin();
          
        key_queue.push_front(key); // add new value to top of queue
          
        // add the dict element
        dict.insert(make_pair(key,make_pair(new_l_it,key_queue.begin())));
      }
    }

    void print_buffer(){
      std::cout << "Data : " ;
      for(List_int_iterator l_it = this->data_buffer.begin(); l_it != this->data_buffer.end(); l_it++){
        std::cout << *l_it << ",";
      }
      std::cout << "\n";
    }
};

int main(int argc, char** argv){
  
  LRUCache cache(2);
  cache.print_buffer();
  cache.put(1, 1);
  cache.print_buffer();
  cache.put(2, 2);
  cache.print_buffer();
  std::cout << cache.get(1) << std::endl;  
  cache.print_buffer();// returns 1
  cache.put(3, 3); 
  cache.print_buffer();// evicts key 2
  std::cout << cache.get(2) << std::endl;   
  
  cache.print_buffer();// returns -1 (not found)
  cache.put(4, 4); 
  cache.print_buffer();// evicts key 1
  std::cout << cache.get(1) << std::endl; 
  cache.print_buffer();// returns -1 (not found)
  std::cout << cache.get(3) << std::endl; 
  cache.print_buffer();// returns 3
  std::cout << cache.get(4) << std::endl;    
  cache.print_buffer();// returns 4
  
}

/* 
Your previous Plain Text content is preserved below:

This is a sandbox to experiment with CoderPad's execution capabilities.
It's a temporary, throw-away session only visible to you.

This is just a simple shared plaintext pad, with no execution capabilities.

When you know what language you'd like to use for your interview,
simply choose it from the dropdown in the top bar.

You can also change the default language your pads are created with
in your account settings: https://coderpad.io/settings

Enjoy your interview!

//
1->2->3->4
get value
2->1->3->4


unoordered_map<int,pair< list<int>::iterator, list<list::iterator> >::iterator> map

list<list::iterator> q; // push in front() // maintain the order
list<int> vals; //push in front()

how to update queue?
 
      
      Items stored in a list -> values
      
      
      Design and implement a data structure for Least Recently Used (LRU) cache. It should support the following operations: get and put.

get(key) - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
put(key, value) - Set or insert the value if the key is not already present. When the cache reached its capacity, it should invalidate the least recently used item before inserting a new item.

Follow up:
Could you do both operations in O(1) time complexity?

Example:

LRUCache cache = new LRUCache( 2 /* capacity */ );

cache.put(1, 1);
cache.put(2, 2);
cache.get(1);       // returns 1
cache.put(3, 3);    // evicts key 2
cache.get(2);       // returns -1 (not found)
cache.put(4, 4);    // evicts key 1
cache.get(1);       // returns -1 (not found)
cache.get(3);       // returns 3
cache.get(4);       // returns 4
      
 */

#include <iostream>
#include <vector>
#include <utility>
#include <list>
#include <unordered_map>
#include <cassert>

using namespace std;

#define DEFAULT_CAPACITY 2;

typedef list<int>::iterator List_int_iterator;
typedef list<List_int_iterator> Queue; // maintains recently used pi
typedef list<List_int_iterator>::iterator Queue_iterator;


class LRUCache{
  protected:
    unordered_map<int,pair<List_int_iterator,Queue_interator>> dict;
    Queue data_queue;
    list<int> data_buffer;
    int max_capacity;
  
    _update_queue(Queue_iterator q_it,List_int_iterator l_it){
      // update queue
        // delete the pointer
        data_queue.erase(q_it); // pointer to the queue
        
        // add the list pointer to the top of the queue (update queue)
        // top of the queue will be most recently used
        data_queue.push_front(l_it);
    }
  
  public:
    LRUCache() : max_capacity(DEFAULT_CAPACITY){
    }
    LRUCache(int capacity): max_capacity(capacity){
      
    }
  
    ~LRUCache(){
      data_buffer.clear();
      data_queue.clear();
      dict.clear();
    }
  
    int get(int key){
      // assertion that buffer is not overflowing
      assert(data_buffer.size() < max_capacity);
      
      auto it = dict.find(key);
      if(it != dict.end())// if key found{
        
        // get the value
        int value = *(it->first);
        _update_queue(it->second, it->first);
        
        return value;
      }
      else
        return -1;
      
    }
  
    void put(int key, int value){
      
      // assertion that buffer is not overflowing
      assert(data_buffer.size() < max_capacity);
      
      auto it = dict.find(key);
      if(it != dict.end()){ // if key found
        // update value
        *(it->first) = value; 
        
        // update queue
        _update(it->second, it->first);    
      }
      else{
        // pop the last element
        if(data_buffer_size() == max_capacity){
          List_int_iterator l_it = data_queue.back(); // get the iterator to the last eelement
          data_buffer.erase(l_it); // delete that element from the buffer
          
          // pop the queue
          data_queue.pop_back();
          
          // add the element to the dict, buffer and queue
          data_buffer.push_front(val); // insert value
          
          List_int_iterator new_l_it = data_buffer.begin();
          
          data_queue.push_front(new_l_it); // add new value to top of queue
          
          // add the dict element
          dict.insert(make_pair(key,make_pair(new_l_it,data_queue.begin())));
        }
      }
      
      
      
      
      
    }
};

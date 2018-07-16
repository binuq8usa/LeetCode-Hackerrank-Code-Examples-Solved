/*

// Merge K sorted lists in place

// [4,5,9,11], [6,7,8,10], [0,12,14]
// [4,6,0] -> 0 -> 12 --> binary search -> place new value in correct position
// 


// Method : Use heaps

// a) Use vector and make_heap, push_heap, pop_heap commands
// b) use priority queues
// c) write your own heap data structure
// d) use various types of function pointers 
// e) improve code using c++17
// f) use template class   X
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct ListNode{
  int val;
  ListNode* next;
  ListNode(int x): val(x), next(NULL){};
};

// 

// K log K + (insert new value into list)
// use heap?
// arrange these // min heap
// constant time delete operation; insert new element into heap
// K
template<class T>
bool compareFunc(T* a, T* b){
    return a->val > b->val; // so that smallest value is at the the root
}

ListNode* mergeKLists(vector<ListNode*>& lists, bool debug = false){
  //
  ListNode* combinedList;
  ListNode* head;
  
  // remove NULL pointer among list
  for(auto it = lists.begin(); it != lists.end(); ++it)
    if( *it == NULL){
      it = lists.erase(it);
      it--;
    }
  
  if(lists.empty())
    return NULL;

  // create heap out of lists
  make_heap(lists.begin(), lists.end(), compareFunc<ListNode>);
  int count = 0;
  while(!lists.empty()){
    // get the minimum value
    ListNode* frontElem = lists.front();
    
    if(count == 0){
      combinedList = new ListNode(frontElem->val);
      head = combinedList;
    }
    else{
      combinedList->next = new ListNode(frontElem->val);
      combinedList = combinedList->next;
    }
    
    // first pop the heap
    pop_heap(lists.begin(), lists.end(), compareFunc<ListNode>);
    lists.pop_back(); // remove that list
    
    // update the point and delete the head
    ListNode* temp = frontElem->next;
    delete frontElem;
    frontElem = temp;
    
    // insert back into the list
    if(frontElem != NULL){
      lists.push_back(frontElem);
      push_heap(lists.begin(), lists.end(), compareFunc<ListNode>);
    }
    else{
      make_heap(lists.begin(), lists.end(), compareFunc<ListNode>); // remake the heap
    }
    count++;
  }
  return head;
}


// To execute C++, please define "int main()"
int main() {
  
  // List one
  ListNode* arr1 = new ListNode(0);
  arr1->next = new ListNode(2);
  arr1->next->next = new ListNode(5);
  
  ListNode* arr2 = new ListNode(0);
  arr2->next = new ListNode(11);
  arr2->next->next = new ListNode(17);
  
  ListNode* arr3 = new ListNode(2);
  arr3->next = new ListNode(6);
  arr3->next->next = new ListNode(12);
  
  ListNode* arr4 = NULL;
  
  vector<ListNode*> lists;
  lists.push_back(arr1);
  lists.push_back(arr2);
  lists.push_back(arr3);
  lists.push_back(arr4);
  
  ListNode* output = mergeKLists(lists,true);
  //ListNode* output = arr3;
  
  while(output != NULL){
    std::cout << output->val << ",";
    output = output->next;
  }
  std::cout << "\n" ;
}

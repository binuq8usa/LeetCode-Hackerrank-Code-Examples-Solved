#include <iostream>
#include <queue>
#include <algorithm>
#include <cassert>
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

using namespace std;

// if a > b, then function returns true to swap so that elements 
// which is smaller is preferred.
// for sorting, this comparison means that the two elements must be swapped 
// so that the order is ascending (smallest is the first element)
bool comp_greater(int a, int b){
  return (a > b); // returns/swaps if first element if greater than second.
}

bool comp_lesser(int a, int b){
  return (a < b);
}


void heap_push(vector<int>& arr, int value, bool (*comp_op)(int,int)){
  if(!is_heap(arr.begin(),arr.end()))
    make_heap(arr.begin(),arr.end(), comp_op);
  
  arr.push_back(value); // put the value at the end
  // bubble up
  push_heap(arr.begin(), arr.end(), comp_op);
}

void heap_pop(vector<int>& arr, bool (*comp_op)(int,int)){
  if(!is_heap(arr.begin(),arr.end()))
    make_heap(arr.begin(),arr.end(), comp_op);
  
  pop_heap(arr.begin(), arr.end(), comp_op); // bubble down
  arr.pop_back();
}

void balance_heaps(vector<int>& leftHeap, vector<int>& rightHeap){
  // check if left heap max is greater than right heap min
  /*
  std::cout << "Left heap : ";
  for(int k = 0; k < leftHeap.size(); k++)
    std::cout << leftHeap[k] << ",";
  std::cout << "\n";
  
  std::cout << "Right heap : ";
  for(int k = 0; k < rightHeap.size(); k++)
    std::cout << rightHeap[k] << ",";
  std::cout << "\n";
  */
  
  
  // balance heaps
    int diff = std::abs((int)leftHeap.size() - (int)rightHeap.size());
    if(diff > 1){
      int left_root = leftHeap.front();
      heap_pop(leftHeap, comp_lesser);
      
      heap_push(rightHeap,left_root, comp_greater);
    } 
  
    // if so, switch
    if(rightHeap.size() > 0 && leftHeap.front() > rightHeap.front()){
      int left_root = leftHeap.front();
      int right_root = rightHeap.front();
      
      heap_pop(leftHeap, comp_lesser);
      heap_pop(rightHeap, comp_greater);
      
      heap_push(leftHeap,right_root, comp_lesser);
      heap_push(rightHeap,left_root, comp_greater);
    }
    
    
}

// left array 
double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2){
  vector<int> leftHeap; // Max heap
  vector<int> rightHeap; // Min heap
  
  int i =0,j = 0;
  while(1){
    
    if(i >= nums1.size() && j >= nums2.size())
      break;
    
    if(i >= nums1.size()){
      heap_push(leftHeap,nums2[j], comp_lesser);
      j++;
      balance_heaps(leftHeap,rightHeap);
      continue;
    }
    
    if(j >= nums2.size()){
      heap_push(leftHeap,nums1[i], comp_lesser);
      i++;
      balance_heaps(leftHeap,rightHeap);
      continue;
    }
    
    if(nums1[i] < nums2[j]){
      heap_push(leftHeap,nums1[i], comp_lesser);
      i++;
    }
    else{
      heap_push(leftHeap,nums2[j], comp_lesser);
      j++;
    }
    /*
    std::cout << "Left heap : ";
  for(int k = 0; k < leftHeap.size(); k++)
    std::cout << leftHeap[k] << ",";
  std::cout << "\n";
  
  std::cout << "Right heap : ";
  for(int k = 0; k < rightHeap.size(); k++)
    std::cout << rightHeap[k] << ",";
  std::cout << "\n";
  */
  
    balance_heaps(leftHeap,rightHeap);
  }
  
  assert(std::abs((int)leftHeap.size() - (int)rightHeap.size()) <= 1); 
  
  /*
  // print heaps
  std::cout << "Left heap Af : ";
  for(int k = 0; k < leftHeap.size(); k++)
    std::cout << leftHeap[k] << ",";
  std::cout << "\n";
  
  std::cout << "Right heap Af: ";
  for(int k = 0; k < rightHeap.size(); k++)
    std::cout << rightHeap[k] << ",";
  std::cout << "\n";
  */
  
  
  // give median
  int N = nums1.size() + nums2.size();
  float median = 0.0;
  if(N%2 != 0){
    median = leftHeap.front();
  }
  else
    median = (leftHeap.front() + rightHeap.front())/2.0;
  
  return median;
  
}



TEST_CASE("Test 1","[findMedianSortedArrays]"){
  int arr_1[] = {1,3};
  int arr_2[] = {2};
  
  vector<int> nums1(arr_1,arr_1 + sizeof(arr_1)/sizeof(int));
  vector<int> nums2(arr_2, arr_2 + sizeof(arr_2)/sizeof(int));
  
  REQUIRE(findMedianSortedArrays(nums1,nums2) == 2.0);  
}


TEST_CASE("Test 2","[findMedianSortedArrays]"){
  int arr_1[] = {1,2};
  int arr_2[] = {3,4};
  
  vector<int> nums1(arr_1,arr_1 + sizeof(arr_1)/sizeof(int));
  vector<int> nums2(arr_2, arr_2 + sizeof(arr_2)/sizeof(int));
  
  REQUIRE(findMedianSortedArrays(nums1,nums2) == 2.5);  
}


TEST_CASE("Test 3","[findMedianSortedArrays]"){
  int arr_1[] = {1,2,3};
  int arr_2[] = {4,5};
  
  vector<int> nums1(arr_1,arr_1 + sizeof(arr_1)/sizeof(int));
  vector<int> nums2(arr_2, arr_2 + sizeof(arr_2)/sizeof(int));
  
  REQUIRE(findMedianSortedArrays(nums1,nums2) == 3.0);  
}

TEST_CASE("Test 4","[findMedianSortedArrays]"){
  int arr_1[] = {1,2,3};
  int arr_2[] = {4,5,6};
  
  vector<int> nums1(arr_1,arr_1 + sizeof(arr_1)/sizeof(int));
  vector<int> nums2(arr_2, arr_2 + sizeof(arr_2)/sizeof(int));
  
  REQUIRE(findMedianSortedArrays(nums1,nums2) == 3.5);  
}

TEST_CASE("Test 5","[findMedianSortedArrays]"){
  int arr_1[] = {1,4,7};
  int arr_2[] = {2,3,6};
  // 1 2 3 4 6 7
  
  vector<int> nums1(arr_1,arr_1 + sizeof(arr_1)/sizeof(int));
  vector<int> nums2(arr_2, arr_2 + sizeof(arr_2)/sizeof(int));
  
  REQUIRE(findMedianSortedArrays(nums1,nums2) == 3.5);  
}

TEST_CASE("Test 7","[findMedianSortedArrays]"){
  int arr_1[] = {1,4,7};
  int arr_2[] = {2,3,6};
  // 1 2 3 4 6 7
  
  vector<int> nums1(arr_1,arr_1 + sizeof(arr_1)/sizeof(int));
  vector<int> nums2(arr_2, arr_2 + sizeof(arr_2)/sizeof(int));
  
  REQUIRE(findMedianSortedArrays(nums1,nums2) == 3.5);  
}

TEST_CASE("Test 8","[findMedianSortedArrays]"){
  int arr_1[] = {1,4,7,15,18,20};
  int arr_2[] = {2,3,6,9,10,13,14};
  // 1 2 3 4 6 7 9 10 13 14 15 18 20
  
  vector<int> nums1(arr_1,arr_1 + sizeof(arr_1)/sizeof(int));
  vector<int> nums2(arr_2, arr_2 + sizeof(arr_2)/sizeof(int));
  
  REQUIRE(findMedianSortedArrays(nums1,nums2) == 9.0);  
}

TEST_CASE("Test 9","[findMedianSortedArrays]"){
  int arr_1[] = {1,4,5,7,15,18,20};
  int arr_2[] = {2,3,6,9,10,13,14};
  // 1 2 3 4 6 7 9 10 13 14 15 18 20
  
  vector<int> nums1(arr_1,arr_1 + sizeof(arr_1)/sizeof(int));
  vector<int> nums2(arr_2, arr_2 + sizeof(arr_2)/sizeof(int));
  
  REQUIRE(findMedianSortedArrays(nums1,nums2) == 8.0);  
}


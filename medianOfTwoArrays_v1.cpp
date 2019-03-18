#include <iostream>
#include <queue>
#include <functional>
#include <cassert>
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

using namespace std;

typedef priority_queue<int, vector<int>> MaxHeap;
typedef priority_queue<int, vector<int>, std::greater<int> > MinHeap;

void balanceHeaps(MaxHeap& leftHeap, MinHeap& rightHeap){
  // balance it if not balanced
  assert(leftHeap.size() >= rightHeap.size()); // always left is greater than right
  
  int diff = std::abs((int)leftHeap.size() - (int)rightHeap.size());
  if(diff > 1){
    int root_left = leftHeap.top();
    leftHeap.pop();
    rightHeap.push(root_left);
  }
  
  // check if left max is greater than right min. (right min > left max)
  if(rightHeap.size() >0 && leftHeap.top() > rightHeap.top()){
    int root_left = leftHeap.top();
    int root_right = rightHeap.top();
    
    leftHeap.pop(); rightHeap.pop();
    leftHeap.push(root_right);
    rightHeap.push(root_left);
  }
}

// left array 
double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2){
  MaxHeap leftHeap; // default
  MinHeap rightHeap; 
  
  for(int k=0, i =0, j =0; k <  nums1.size() + nums2.size(); k++){
    if(i >= nums1.size()){
      leftHeap.push(nums2[j]);
      j++;
      balanceHeaps(leftHeap,rightHeap);
      continue;
    }
    if(j >= nums2.size()){
      leftHeap.push(nums1[i]);
      i++;
      balanceHeaps(leftHeap,rightHeap);
      continue;
    }
    
    if(nums1[i] <= nums2[j]){
      leftHeap.push(nums1[i]);
      i++;
    }
    else{
      leftHeap.push(nums2[j]);
      j++;
    }
    balanceHeaps(leftHeap,rightHeap);
  }
  
  assert(std::abs((int)leftHeap.size() - (int)rightHeap.size()) <= 1);
  double median_val = 0.0;
  
  // median
  if(leftHeap.size() > rightHeap.size())
    median_val = leftHeap.top();
  else if(leftHeap.size() < rightHeap.size())
    median_val = rightHeap.top();
  else
    median_val = (leftHeap.top() + rightHeap.top())/2.0;
  
  return median_val;
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

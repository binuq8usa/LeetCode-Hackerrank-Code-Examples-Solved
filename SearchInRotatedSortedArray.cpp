#include <iostream>
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

using namespace std;

// sorted array - 0,1,2,4,5,6,7
// rotated - 4,5,6,7,0,1,2
// 1,2,4,5,6,7,0
// 7,0,1,2,4,5,6
// 8,0,1,2,4,5,6,7
// 2,3,4,5,6,7,0,1 
// 1,2,4,5,6,7,0

// 6,7,8,0,1,2,4,5

// 2 3 4 5 6 7 8 9

// check if mid point is pivot - left number > midpoint, right number < mid
// 

// O(1)
/*
bool checkIfArrayIsRotated(vector<int>& nums){
  if(nums.size() >= 2)
    return nums[0] > nums[nums.size()-1];
  else return false;
}
*/

int find_pivot(vector<int>& nums){
  int N = nums.size();
  int mid_pt_val = nums[N/2];
  
  // base case
  if(N > 1 && nums[0] < nums[N-1])
    return -1;
  
  if(N > 1 && mid_pt_val < nums[N/2-1])
    return N/2;
  
  if(N>2 && mid_pt_val > nums[N/2+1]) // condition is checked only if N > 2
    return N/2+1;
  
  // base case
  if(N <= 3)
    return -1;
  
  vector<int> leftHalf(nums.begin(), nums.begin()+N/2);
  vector<int> rightHalf(nums.begin()+N/2, nums.end());
  
  int index = find_pivot(leftHalf);
  if(index == -1){ // if pivot is not found in the left half, search in right half
    index = find_pivot(rightHalf);
    index = (index > 0)? index + N/2 : -1;
  }
  return index;
}

// O(logN)
// 0,1,2,4,5,6,7
int binary_search(int target,vector<int>& nums){
  int N = nums.size();
  int index = -1;
  
  // base case
  if(N == 1){
    index = (nums[0] == target) ? 0 : -1;
    return index;
  }
  if(N == 2){
    index = (nums[0] == target) ? 0 : -1;
    if(index == -1){
      index = (nums[1] == target) ? 1 : -1;
    }
    return index;
  }
  
  int mid_pt_val = nums[N/2];
  vector<int> leftHalf(nums.begin(), nums.begin()+N/2);
  vector<int> rightHalf(nums.begin()+N/2, nums.end());

  if(mid_pt_val == target)
    return N/2;
  else if(target < mid_pt_val){
    index = binary_search(target,leftHalf);
  }
  else{
    index = binary_search(target,rightHalf);
    index = (index > 0)? index + N/2 : -1;
  }
  
  return index;
}

// O(logN)
int search(int target,vector<int>& nums){ 
  int pivot_idx = find_pivot(nums);
  int index = -1;
  // no rotation 
  if(pivot_idx == -1){ // no pivot, array is sorted
    index = binary_search(target,nums);
    return index;
  }
  
  if(nums[pivot_idx] == target)
    return pivot_idx;
  
  vector<int> leftHalf(nums.begin(), nums.begin() + pivot_idx);
  vector<int> rightHalf(nums.begin()+pivot_idx, nums.end());
   
  index = binary_search(target,leftHalf);
  if(index == -1){
    index = binary_search(target,rightHalf);
    index = (index > 0)? index + pivot_idx : -1;
  }
  
  return index;
}


// TEST cases for binary search
TEST_CASE("Binary Search - 1","[binary_search]"){
  int nums[] = {0,1,2,4,5,6,7};
  vector<int> arr(nums,nums+sizeof(nums)/sizeof(int));
  
  REQUIRE(binary_search(4,arr) == 3);
  REQUIRE(binary_search(3,arr) == -1); 
  REQUIRE(binary_search(0,arr) == 0); 
  REQUIRE(binary_search(7,arr) == 6); 
  REQUIRE(binary_search(11,arr) == -1); 
  REQUIRE(binary_search(-2,arr) == -1); 
}

TEST_CASE("Binary Search - 2","[binary_search]"){
  int nums[] = {0,1,2,4,5,6,7,12};
  vector<int> arr(nums,nums+sizeof(nums)/sizeof(int));
  
  REQUIRE(binary_search(4,arr) == 3);
  REQUIRE(binary_search(3,arr) == -1); 
  REQUIRE(binary_search(0,arr) == 0); 
  REQUIRE(binary_search(7,arr) == 6); 
  REQUIRE(binary_search(11,arr) == -1); 
  REQUIRE(binary_search(12,arr) == 7); 
}

TEST_CASE("Find Pivot - 1","[find_pivot]"){
  int nums[] = {1,2,4,5,6,7,0};
  vector<int> arr(nums,nums+sizeof(nums)/sizeof(int));
  
  REQUIRE(find_pivot(arr) == 6);
}

TEST_CASE("Find Pivot - 2","[find_pivot]"){
  int nums[] = {4,5,6,7,0,1,2};
  vector<int> arr(nums,nums+sizeof(nums)/sizeof(int));
  
  REQUIRE(find_pivot(arr) == 4);
}

TEST_CASE("Find Pivot - 3","[find_pivot]"){
  int nums[] = {7,0,1,2,4,5,6};
  vector<int> arr(nums,nums+sizeof(nums)/sizeof(int));
  
  REQUIRE(find_pivot(arr) == 1);
}

TEST_CASE("Find Pivot - 4","[find_pivot]"){
  int nums[] = {8,0,1,2,4,5,6,7};
  vector<int> arr(nums,nums+sizeof(nums)/sizeof(int));
  
  REQUIRE(find_pivot(arr) == 1);
}

TEST_CASE("Find Pivot - 5","[find_pivot]"){
  int nums[] = {2,3,4,5,6,7,0,1};
  vector<int> arr(nums,nums+sizeof(nums)/sizeof(int));
  
  REQUIRE(find_pivot(arr) == 6);
}

TEST_CASE("Find Pivot - 6","[find_pivot]"){
  int nums[] = {6,7,8,0,1,2,4,5};
  vector<int> arr(nums,nums+sizeof(nums)/sizeof(int));
  
  REQUIRE(find_pivot(arr) == 3);
}

TEST_CASE("Find Pivot - 7","[find_pivot]"){
  int nums[] = {2,3,4,5,6,7,8,9};
  vector<int> arr(nums,nums+sizeof(nums)/sizeof(int));
  
  REQUIRE(find_pivot(arr) == -1);
}

TEST_CASE("Search Rotated Array - 1","[search]"){
  int nums[] = {1,2,4,5,6,7,0};
  vector<int> arr(nums,nums+sizeof(nums)/sizeof(int));
  
  REQUIRE(search(4,arr) == 2);
  REQUIRE(search(0,arr) == 6);
  REQUIRE(search(3,arr) == -1);
  REQUIRE(search(7,arr) == 5); 
  REQUIRE(search(11,arr) == -1); 
  REQUIRE(search(-2,arr) == -1); 
  REQUIRE(search(2,arr) == 1); 
}


TEST_CASE("Search Rotated Array - 2","[search]"){
  int nums[] = {4,5,6,7,0,1,2};
  vector<int> arr(nums,nums+sizeof(nums)/sizeof(int));
  
  REQUIRE(search(4,arr) == 0);
  REQUIRE(search(0,arr) == 4);
  REQUIRE(search(3,arr) == -1);
  REQUIRE(search(7,arr) == 3); 
  REQUIRE(search(11,arr) == -1); 
  REQUIRE(search(-2,arr) == -1); 
  REQUIRE(search(2,arr) == 6); 
}


TEST_CASE("Search Rotated Array - 3","[search]"){
  int nums[] = {7,0,1,2,4,5,6};
  vector<int> arr(nums,nums+sizeof(nums)/sizeof(int));
  
  REQUIRE(search(4,arr) == 4);
  REQUIRE(search(0,arr) == 1);
  REQUIRE(search(3,arr) == -1);
  REQUIRE(search(7,arr) == 0); 
  REQUIRE(search(11,arr) == -1); 
  REQUIRE(search(-2,arr) == -1); 
  REQUIRE(search(2,arr) == 3); 
}


TEST_CASE("Search Rotated Array - 4","[search]"){
  int nums[] = {8,0,1,2,4,5,6,7};
  vector<int> arr(nums,nums+sizeof(nums)/sizeof(int));
  
  REQUIRE(search(4,arr) == 4);
  REQUIRE(search(0,arr) == 1);
  REQUIRE(search(3,arr) == -1);
  REQUIRE(search(7,arr) == 7); 
  REQUIRE(search(11,arr) == -1); 
  REQUIRE(search(-2,arr) == -1); 
  REQUIRE(search(2,arr) == 3); 
}

TEST_CASE("Search Rotated Array - 5","[search]"){
  int nums[] = {6,7,8,0,1,2,4,5};
  vector<int> arr(nums,nums+sizeof(nums)/sizeof(int));
  
  REQUIRE(search(4,arr) == 6);
  REQUIRE(search(0,arr) == 3);
  REQUIRE(search(3,arr) == -1);
  REQUIRE(search(7,arr) == 1); 
  REQUIRE(search(11,arr) == -1); 
  REQUIRE(search(-2,arr) == -1); 
  REQUIRE(search(2,arr) == 5); 
}

TEST_CASE("Search Rotated Array - 6","[search]"){
  int nums[] = {2,3,4,5,6,7,0,1};
  vector<int> arr(nums,nums+sizeof(nums)/sizeof(int));
  
  REQUIRE(search(4,arr) == 2);
  REQUIRE(search(0,arr) == 6);
  REQUIRE(search(3,arr) == 1);
  REQUIRE(search(7,arr) == 5); 
  REQUIRE(search(11,arr) == -1); 
  REQUIRE(search(-2,arr) == -1);
  REQUIRE(search(2,arr) == 0); 
}

TEST_CASE("Search Rotated Array - 7","[search]"){
  int nums[] = {2,3,4,5,6,7,8,9};
  vector<int> arr(nums,nums+sizeof(nums)/sizeof(int));
  
  REQUIRE(search(4,arr) == 2);
  REQUIRE(search(0,arr) == -1);
  REQUIRE(search(3,arr) == 1);
  REQUIRE(search(7,arr) == 5); 
  REQUIRE(search(11,arr) == -1); 
  REQUIRE(search(-2,arr) == -1); 
  REQUIRE(search(9,arr) == 7); 
}


/*
// To execute C++, please define "int main()"
int main() {
  auto words = { "Hello, ", "World!", "\n" };
  for (const string& word : words) {
    cout << word;
  }
  return 0;
}
*/



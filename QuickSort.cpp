/*

Quick sort algorithm : sort numbers using pivot in place.


*/


// 3,6,2,11,7,1,3,5,9
// 3,6,2,5,7,1,3,11,9
// 3,6,2,5,3,1,7,11,9
// 3,6,2,5,3,1.    ; // 7,11,9
//

#include <iostream>
#include <vector>
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
using namespace std;

typedef vector<int>::iterator VecIt;

void quickSort(vector<int>& nums, VecIt left, VecIt right){
  
  VecIt stLeft = left;
  VecIt stRight = right;
  if(left >= right)
    return;
  int pivot = (*left + *right)/2;
  
  while(left <= right){
    //std::cout << "Checkpoint 1" << std::endl;
    while( *left < pivot){
      //std::cout << "Left no swap : " << *left << std::endl;
      left++;
    }
    //std::cout << "Checkpoint 2" << std::endl;
    while(*right > pivot){
      //std::cout << "Right no swap : " << *right << std::endl;
      right--;
    }
    //std::cout << "Checkpoint 3" << std::endl;
    if(left <= right){
      //std::cout << "Checkpoint 4" << std::endl;
      int temp = *left;
      *left = *right;
      //std::cout << "Checkpoint 5" << std::endl;
      *right = temp;
      //std::cout << "Checkpoint 6" << std::endl;
      left++;
      right--;
      
      //std::cout << "Left after swap : " << *left << std::endl;
      //std::cout << "Right after swap : " << *right << std::endl;
      
    }
    
    /*
    for(int k = 0; k < nums.size(); k++)
      std:cout << nums[k] << ",";
    std::cout << "\n";
    */
  }
  
  // split nums based on 
  quickSort(nums,stLeft, left-1); // quick sort on left half
  quickSort(nums,left, stRight); // quick sort on right half
  
  return;
}


vector<int> arraySort(vector<int> nums){
  quickSort(nums,nums.begin(), nums.end()-1);
  
  return nums;
}

/*
// To execute C++, please define "int main()"
int main() {
  int nums[] = {3,6,9,11,7,1,3,5,2};
  std::vector<int> arr(nums,nums + sizeof(nums)/sizeof(int));
  
  //std::cout << nums.begin() << std::endl;
  
  //quickSort(arr,arr.begin(), arr.end()-1);
  vector<int> output = arraySort(arr);
  
  
  for(int k = 0; k < output.size(); k++){
    std::cout << output[k] << ",";
  }
  std::cout << "\n";
  
  return 0;
  
}
*/

TEST_CASE("Test case 1","[arraySort]"){
  vector<int> nums = {0,0,0,0,0,0,0,0,0};
  int vals[] = {0,0,0,0,0,0,0,0,0};
  
  vector<int> sortedNums(vals,vals + sizeof(vals)/sizeof(int));
  
  REQUIRE(arraySort(nums) == sortedNums);
}

TEST_CASE("Test case 2","[arraySort]"){
  vector<int> nums = {3,6,2,11,7,1,3,5,9};
  int vals[] = {1,2,3,3,5,6,7,9,11};
  
  vector<int> sortedNums(vals,vals + sizeof(vals)/sizeof(int));
  
  REQUIRE(arraySort(nums) == sortedNums);
}

TEST_CASE("Test case 3","[arraySort]"){
  vector<int> nums = {1};
  int vals[] = {1};
  
  vector<int> sortedNums(vals,vals + sizeof(vals)/sizeof(int));
  
  REQUIRE(arraySort(nums) == sortedNums);
}


TEST_CASE("Test case 4","[arraySort]"){
  vector<int> nums = {1,-1};
  int vals[] = {-1,1};
  
  vector<int> sortedNums(vals,vals + sizeof(vals)/sizeof(int));
  
  REQUIRE(arraySort(nums) == sortedNums);
}

TEST_CASE("Test case 5","[arraySort]"){
  vector<int> nums = {0,1,-1};
  int vals[] = {-1,0,1};
  
  vector<int> sortedNums(vals,vals + sizeof(vals)/sizeof(int));
  
  REQUIRE(arraySort(nums) == sortedNums);
}




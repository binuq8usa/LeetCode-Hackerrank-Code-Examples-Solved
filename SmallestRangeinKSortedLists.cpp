/*
Question - Leetcode
You have k lists of sorted integers in ascending order. Find the smallest range that includes at least one number from each of the k lists.

We define the range [a,b] is smaller than range [c,d] if b-a < d-c or a < c if b-a == d-c.

Example 1:
Input:[  [4,10,15,24,26], [0,9,12,20], [5,18,22,30]  ]
Output: [20,24]
Explanation: 
List 1: [4, 10, 15, 24,26], 24 is in range [20,24].
List 2: [0, 9, 12, 20], 20 is in range [20,24].
List 3: [5, 18, 22, 30], 22 is in range [20,24].
Note:
The given list may contain duplicates, so ascending order means >= here.
1 <= k <= 3500
-105 <= value of elements <= 105.
For Java users, please note that the input type has been changed to List<List<Integer>>. And after you reset the code template, you'll see this point.

*/

/*
// Two operations
// 1) Selecting interval in brute force manner -> O(KN^2)
// 2) Search each element within the interval 
// Total operation : KN^2 intervals * 

// Piggy back on 

// 1) [4,0,5] -> min/max value (O(K)) - [0,5]
// 2) [4,5,9] -> min/max - [4,5,9] - [4,9]
// 3) [5,9,10] -> [5,10]
// 4) [9,10,18] -> [9,18]     5) [10,12,18] --> [10,18]
// 6) [ 12,15,18] -> [12,18]  7) [15,18,20] -- > [15,20]
// 8) [[18,20,24] -> [18,24]   9) [20,22,24] --> [20,24]
// 9) [[22,24]]

// Select apppropriate intervals - O(KN)
// 
*/

#include <iostream>
#include <utility>
#include <cassert>
#include <vector>

using namespace std;

typedef vector<int32_t>::iterator VIT;
#define MAXVAL 10e5;

bool setDebugMode(){
  return true;
}

pair<int32_t,int32_t> findSmallestRange(vector< vector<int32_t>> listNums, bool debug = false){
  vector<pair<int32_t,int32_t>> ranges;
  vector<VIT> listIterators; //
  
  // find the list with the smallest starting value
  int minK = -1;
  int32_t minValue = MAXVAL;
  for(int k = 0 ; k < listNums.size(); k++){
    listIterators.push_back(listNums[k].begin());
    if(listNums[k][0] < minValue){
      minValue = listNums[k][0];
      minK = k;
    }
  }
  
  assert(minK >= 0); // cannot be negative
  
  // initialize iterator
  VIT it = listNums[minK].begin();
  
  while(it != listNums[minK].end()){    
    // find min/max value
    int32_t minRangeValue = MAXVAL;
    int32_t maxRangeValue = -MAXVAL;
    if(debug){
      std::cout << "Min Range Value Initial : " << minRangeValue << std::endl;
      std::cout << "[";
    }
    minK = -1;
    for(int k = 0 ; k < listIterators.size(); k++){
      VIT it_temp = listIterators[k];
      
      if(debug)
        std::cout << *it_temp << ",";
      // find min
      if( *it_temp < minRangeValue){
        minRangeValue = (*it_temp);
        minK = k;
      }
      
      // find max
      if( *it_temp > maxRangeValue)
        maxRangeValue = (*it_temp);
    }
    if(debug)
      std::cout <<"]" << std::endl;
    
    
    // check
    if(debug){
      assert(minK >= 0 && minK < listIterators.size());
      assert(minRangeValue <= maxRangeValue); // debug assert
    }
    
    // insert this range
    ranges.push_back(make_pair(minRangeValue,maxRangeValue));
    //std::cout << "Range = (" << minRangeValue << "," << maxRangeValue << ")" << " ; minK :  " << minK << std::endl;
    
    // update the iterator of the list with the  minium value
    it = ++listIterators[minK];   
  }
  
  //std::cout << "\n";
  
  // find the smallest range
  int32_t smallestRange = MAXVAL;
  int smInd = -1;
  for(int rr = 0 ; rr < ranges.size(); rr++){
    if(debug){
      std::cout << "Range = (" << ranges[rr].first << "," << ranges[rr].second << ")" << std::endl;
    }
    int32_t rangeVal = ranges[rr].second - ranges[rr].first;
    if(rangeVal < smallestRange){
      smallestRange = rangeVal;
      smInd = rr;
    }
    else if(rangeVal == smallestRange)
      smInd = (ranges[smInd].first > ranges[rr].first)? rr : smInd;
  }
  
  // check smInd
  assert(smInd >= 0);
  
  return ranges[smInd];
}


// To execute C++, please define "int main()"
int main() {
  
  //Input:[  [4,10,15,24,26], [0,9,12,20], [5,18,22,30] 
  int32_t arr1[] = {4,10,15,24,26};
  int32_t arr2[] = {0,9,12,20};
  int32_t arr3[] = {5,18,22,30};
  
  // create the input
  vector<vector<int32_t>> lists;
  lists.push_back(vector<int32_t>(arr1,arr1 + sizeof(arr1)/sizeof(int32_t)));
  lists.push_back(vector<int32_t>(arr2,arr2 + sizeof(arr2)/sizeof(int32_t)));
  lists.push_back(vector<int32_t>(arr3,arr3 + sizeof(arr3)/sizeof(int32_t)));
  
  
  pair<int32_t,int32_t> range = findSmallestRange(lists);
  
  std::cout << " \nSmallestRange = (" << range.first << "," << range.second << ")" << std::endl;
  
  
  /*
  auto words = { "Hello, ", "World!", "\n" };
  for (const string& word : words) {
    cout << word;
  }
  return 0;
  
  */
}


/*
Rotate image by 90degrees
Resize image based on window length and height

You are given an n x n 2D matrix representing an image.

Rotate the image by 90 degrees (clockwise).

Note:

You have to rotate the image in-place, which means you have to modify the input 2D matrix directly. DO NOT allocate another 2D matrix and do the rotation.

Example 1:

Given input matrix = 
[
  [1,2,3],
  [4,5,6],
  [7,8,9]
],

rotate the input matrix in-place such that it becomes:
[
  [7,4,1],
  [8,5,2],
  [9,6,3]
]
Example 2:

Given input matrix =
[
  [ 5, 1, 9,11],
  [ 2, 4, 8,10],
  [13, 3, 6, 7],
  [15,14,12,16]
], 

rotate the input matrix in-place such that it becomes:
[
  [15,13, 2, 5],
  [14, 3, 4, 1],
  [12, 6, 8, 9],
  [16, 7,10,11]
]


[1,2,3],
[4,5,6],
[7,8,9]

[1 4 7],
[2,5,8],
[3,6,9]


[7 4 1]
[8 5 2]
[9 6 3]

*/


#include <iostream>
#include <vector>
#include <assert.h>

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

using namespace std;

void swap(int& a, int& b){
  int temp = a;
  a = b;
  b = temp;
}

/*
void transpose(vector<vector<int>> & matrix){
  int M = matrix.size();
  int N = matrix[0].size();
  
  assert(M == N); // square matrix requirement
  
  // compute inplace transpose
  for(int i = 0 ; i < M; i++)
    for(int j = i+1 ; j < N; j++)
      swap(matrix[i][j],matrix[j][i]);
}

TEST_CASE("Test Case transpose","[transpose]"){
  vector<vector<int>> input = {{1,2,3},
                         {4,5,6},
                         {7,8,9}};
  vector<vector<int>> result = {{1,4,7},
                                {2,5,8},
                                {3,6,9}};
  transpose(input);
  REQUIRE(input == result);
}
*/


void rotate(vector<vector<int>>& matrix){
  
  int M = matrix.size();
  int N = matrix[0].size();
  
  assert(M == N); // square matrix requirement
  
  // compute inplace transpose
  for(int i = 0 ; i < M; i++)
    for(int j = i+1 ; j < N; j++)
      swap(matrix[i][j],matrix[j][i]);
  
  
  // swap the outer columns (if rotating clockwise)
  for(int i = 0; i < M; i++)
    for(int j = 0; j < N/2; j++)
      swap(matrix[i][j],matrix[i][N-1-j]);
      
}

/*
[1,2,3],
  [4,5,6],
  [7,8,9]
  */
TEST_CASE("Test case 1","[rotate]"){
  vector<vector<int>> input = {{1,2,3},
                         {4,5,6},
                         {7,8,9}};
  vector<vector<int>> result = {{7,4,1},
                                {8,5,2},
                                {9,6,3}};
  rotate(input);
  REQUIRE(input == result);
}


/*
[ 5, 1, 9,11],
  [ 2, 4, 8,10],
  [13, 3, 6, 7],
  [15,14,12,16]
*/
TEST_CASE("Test case 2","[rotate]"){
  vector<vector<int>> input = {{5,1,9,11},
                               {2,4,8,10},
                               {13,3,6,7},
                               {15,14,12,16}};
  vector<vector<int>> result = {{15,13,2,5},
                                {14,3,4,1},
                                {12,6,8,9},
                                {16,7,10,11}};
  rotate(input);
  REQUIRE(input == result);
}

TEST_CASE("Test case 3","[rotate]"){
  vector<vector<int>> input = {{5,1},
                               {2,4}};
  vector<vector<int>> result = {{2,5},
                                {4,1}};
  rotate(input);
  REQUIRE(input == result);
}

TEST_CASE("Test case 4","[rotate]"){
  vector<vector<int>> input = {{1}};
  vector<vector<int>> result = {{1}};
  rotate(input);
  REQUIRE(input == result);
}




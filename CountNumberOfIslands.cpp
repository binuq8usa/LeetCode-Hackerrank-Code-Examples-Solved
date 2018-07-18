#include <iostream>
#include <vector>
#include <utility>
using namespace std;

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

/** A two-dimensional vector of bits, potentially containing islands.
 */
using BitMap = vector<vector<bool>>;

/** return the number of islands in a bitmap
 *
 * An island is defined as some continuously connected chunk of 1s (true).
 *
 * @param  bitmap the input map to count against
 * @return        the number of islands in bitmap
 */

vector<pair<int,int>> validNeighbors(const BitMap bitmap, pair<int,int> s_index){
  vector<pair<int,int>> neighbors;
  int i = s_index.first;
  int j = s_index.second;
  
  if(j-1 >= 0 && bitmap[i][j-1])
    neighbors.push_back(make_pair(i,j-1));
  if(j+1 <= bitmap[i].size()-1 && bitmap[i][j+1])
    neighbors.push_back(make_pair(i,j+1));
  if(i-1 >= 0 && bitmap[i-1][j])
    neighbors.push_back(make_pair(i-1,j));
  if(i+1 <= bitmap.size()-1 && bitmap[i+1][j])
    neighbors.push_back(make_pair(i+1,j));
  
  return neighbors;
}


void exploreMap(const BitMap bitmap, BitMap& explored, pair<int,int> s_index){
  
  explored[s_index.first][s_index.second] = true;
  
  vector<pair<int,int>> neighbors = validNeighbors(bitmap,s_index);
  
  for(int k = 0; k < neighbors.size(); k++){
    int i = neighbors[k].first;
    int j = neighbors[k].second;
    
    if(!explored[i][j])
      exploreMap(bitmap,explored,neighbors[k]);
  }
}


unsigned int count_islands(const BitMap bitmap) {
 //throw std::runtime_error("IMPLEMENT ME!");
  
  unsigned int numIslands = 0;
  BitMap explored(bitmap.size(),vector<bool>(bitmap[0].size(),false));
  for(int i = 0 ; i < bitmap.size(); i++){
    for(int j = 0 ; j < bitmap[i].size(); j++){
      if(bitmap[i][j] && !explored[i][j]){
        exploreMap(bitmap,explored, make_pair(i,j));
        numIslands++;
      }
    }
  }
  std::cout << "Number of islands : "  << numIslands << std::endl;
  return numIslands;
}

TEST_CASE("Counts 3 Islands", "[count_islands]") {
  BitMap bitmap = {{0, 1, 1, 0}, 
                   {0, 1, 0, 0},
                   {0, 0, 0, 0},
                   {1, 0, 1, 0}};
  
  REQUIRE( count_islands(bitmap) == 3 );
}

TEST_CASE("Counts 2 Islands", "[count_islands]") {
   BitMap bitmap = {{0, 1, 1, 0}, 
                    {0, 1, 0, 0},
                    {0, 0, 0, 0},
                    {1, 1, 1, 0}};
  
  REQUIRE( count_islands(bitmap) == 2 ); 
}

TEST_CASE("Counts 2 Islands with boundary conditions", "[count_islands]") {
   BitMap bitmap = {{0, 1, 1, 1}, 
                    {0, 1, 0, 1},
                    {0, 0, 0, 0},
                    {1, 1, 1, 0}};
  
  REQUIRE( count_islands(bitmap) == 2 ); 
}

TEST_CASE("Counts - all zeros", "[count_islands]") {
   BitMap bitmap = {{0, 0, 0, 0}, 
                    {0, 0, 0, 0},
                    {0, 0, 0, 0},
                    {0, 0, 0, 0}};
  
  REQUIRE( count_islands(bitmap) == 0 ); 
}

TEST_CASE("Counts - all ones", "[count_islands]") {
   BitMap bitmap = {{1, 1, 1, 1}, 
                    {1, 1, 1, 1},
                    {1, 1, 1, 1},
                    {1, 1, 1, 1}};
  
  REQUIRE( count_islands(bitmap) == 1 ); 
}

TEST_CASE("Counts boundary island", "[count_islands]") {
   BitMap bitmap = {{1, 1, 1, 1}, 
                    {1, 0, 0, 1},
                    {1, 0, 0, 1},
                    {1, 1, 1, 1}};
  
  REQUIRE( count_islands(bitmap) == 1 ); 
}

TEST_CASE("Counts inward island", "[count_islands]") {
   BitMap bitmap = {{0, 0, 0, 0}, 
                    {0, 1, 1, 0},
                    {0, 1, 1, 0},
                    {0, 0, 0, 0}};
  
  REQUIRE( count_islands(bitmap) == 1 ); 
}

TEST_CASE("Counts islands at corners", "[count_islands]") {
   BitMap bitmap = {{1, 0, 0, 1}, 
                    {0, 1, 1, 0},
                    {0, 1, 1, 0},
                    {1, 0, 0, 1}};
  
  REQUIRE( count_islands(bitmap) == 5 ); 
}

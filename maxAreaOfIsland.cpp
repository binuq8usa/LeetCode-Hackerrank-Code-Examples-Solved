/*
695. Max Area of Island
Given a non-empty 2D array grid of 0's and 1's, an island is a group of 1's (representing land) connected 4-directionally (horizontal or vertical.) You may assume all four edges of the grid are surrounded by water.

Find the maximum area of an island in the given 2D array. (If there is no island, the maximum area is 0.)


0110
0110
0110
0001
*/

#include <iostream>
#include <vector>
#include <utility>
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

using namespace std;

vector<pair<int,int>> find_neighbors(vector<vector<int>>& grid, pair<int,int> s_vertex){
  int i = s_vertex.first;
  int j = s_vertex.second;
  vector<pair<int,int>> neighbors;
  if(i-1 >= 0 && grid[i-1][j])
    neighbors.push_back(make_pair(i-1,j));
  if(i+1 < grid.size() && grid[i+1][j])
    neighbors.push_back(make_pair(i+1,j));
  if(j-1 >= 0 && grid[i][j-1])
    neighbors.push_back(make_pair(i,j-1));
  if(j+1 < grid[0].size() && grid[i][j+1])
    neighbors.push_back(make_pair(i,j+1));
  
  return neighbors;
}

int dfs_search(vector<vector<int>>& grid, vector<vector<bool>>& explored, std::pair<int,int> s_vertex){
  // set explored
  explored[s_vertex.first][s_vertex.second] = true;
  int count = 1;
  
  // find neighbors
  vector<pair<int,int>> neighbors = find_neighbors(grid,s_vertex);
  for(int n = 0; n < neighbors.size(); n++){
    if(!explored[neighbors[n].first][neighbors[n].second])
      count += dfs_search(grid,explored,neighbors[n]);
  }
  
  return count;
}

int findMaxAreaOfIsland(vector<vector<int>>& grid){
  int rows = grid.size();
  if(rows == 0)
    return 0;
  int cols = grid[0].size();
  
  vector<vector<bool>> explored(rows, vector<bool>(cols,false));
  int max_area = 0;
  for(int i = 0 ; i < rows; i++)
    for(int j = 0; j < cols; j++){
      int count = 0;
      if(!explored[i][j] && grid[i][j]){
        count += dfs_search(grid,explored,std::make_pair(i,j));
      } // if unexplored
      //std::cout << "Count : " << count << std::endl;
      if(count > max_area)
        max_area = count;
    }
  return max_area;
}


TEST_CASE("test 1","[findMaxAreaOfIsland]"){
  vector<vector<int>> grid{{0,1,1,0},
                           {0,1,1,0},
                           {0,1,1,0},
                           {0,0,0,1}};
  
  REQUIRE(findMaxAreaOfIsland(grid)==6);
}

TEST_CASE("test 2","[findMaxAreaOfIsland]"){
  vector<vector<int>> grid{{0,0,0,0}};
  
  REQUIRE(findMaxAreaOfIsland(grid)==0);
}


TEST_CASE("test 3","[findMaxAreaOfIsland]"){
  vector<vector<int>> grid{{1,1,1,1}};
  
  REQUIRE(findMaxAreaOfIsland(grid)==4);
}


TEST_CASE("test 4","[findMaxAreaOfIsland]"){
  vector<vector<int>> grid{{0,1,1,0}};
  
  REQUIRE(findMaxAreaOfIsland(grid)==2);
}


TEST_CASE("test 5","[findMaxAreaOfIsland]"){
  vector<vector<int>> grid{{0},{1},{1},{0}};
  
  REQUIRE(findMaxAreaOfIsland(grid)==2);
}

TEST_CASE("test 6","[findMaxAreaOfIsland]"){
  vector<vector<int>> grid{{0},{0},{0},{0}};
  
  REQUIRE(findMaxAreaOfIsland(grid)==0);
}

TEST_CASE("test 7","[findMaxAreaOfIsland]"){
  vector<vector<int>> grid{{1},{1},{1},{1}};
  
  REQUIRE(findMaxAreaOfIsland(grid)==4);
}

TEST_CASE("test 8","[findMaxAreaOfIsland]"){
  vector<vector<int>> grid{{1,0,0,1}};
  
  REQUIRE(findMaxAreaOfIsland(grid)==1);
}

TEST_CASE("test 9","[findMaxAreaOfIsland]"){
  vector<vector<int>> grid{{1,0,0,0},
                           {0,1,1,0},
                           {0,1,1,0},
                           {0,0,0,1}};
  
  REQUIRE(findMaxAreaOfIsland(grid)==4);
}

TEST_CASE("test 10","[findMaxAreaOfIsland]"){
  vector<vector<int>> grid{{0,0,1,0,0,0,0,1,0,0,0,0,0},
                           {0,0,0,0,0,0,0,1,1,1,0,0,0},
                           {0,1,1,0,1,0,0,0,0,0,0,0,0},
                           {0,1,0,0,1,1,0,0,1,0,1,0,0},
                           {0,1,0,0,1,1,0,0,1,1,1,0,0},
                           {0,0,0,0,0,0,0,0,0,0,1,0,0},
                           {0,0,0,0,0,0,0,1,1,1,0,0,0},
                           {0,0,0,0,0,0,0,1,1,0,0,0,0}};
  
  REQUIRE(findMaxAreaOfIsland(grid)==6);
}

TEST_CASE("test 11","[findMaxAreaOfIsland]"){
  vector<vector<int>> grid;
  
  REQUIRE(findMaxAreaOfIsland(grid)==0);
}


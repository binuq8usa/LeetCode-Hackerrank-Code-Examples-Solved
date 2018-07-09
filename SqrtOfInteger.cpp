/* Sqaure root of integer - return smallest integer - leet code
// 
*/

#include <iostream>
#include <cstdlib>
#include <set>
#include <string>
#include <tuple>
#include <iterator>
#include <map>
#include <utility>

// write a function for square root (integer)


// log N 
// binary search problem
// y = x/2;
// y*y > x => search between 0,y

void binarySearch(int lowVal, int highVal, int x, int& sqrtVal){
  
  if(int64_t y = lowVal + (highVal-lowVal)/2; y*y <= x && int64_t((y+1)*(y+1)) > x){ // y =2, 
    sqrtVal = y;
    return;
  }
  else if(y*y < x){
    //std::cout << "Sqaure value : " << int64_t(y*y) << std::endl;
    //std::cout << "(Low Val, High Val) = (" << y <<"," << highVal << ")" << std::endl;
    binarySearch(y,highVal,x,sqrtVal);
  }
  else if(y*y > x){
    //std::cout << "Sqaure value : " << int64_t(y*y) << std::endl;
    //std::cout << "(Low Val, High Val) = (" << lowVal <<"," << y << ")" << std::endl;
    binarySearch(lowVal,y,x,sqrtVal); // 0,4,9 ->
  }
}

int mySqrt(int x){
  if(x == 0 || x == 1)
    return x;
  
  int sqrtVal = 0;
  binarySearch(0,x,x,sqrtVal);
  
  return sqrtVal;
}

int main(int argc, char** argv){
  
  std::cout << sizeof(int) << std::endl;
  int x;
  std::cout << "Enter the number : ";
  std::cin >> x;
  std::cout << "Sqaure root of " << x << " : " << mySqrt(x) << std::endl;
  std::cout << "End of program" << std::endl;
}


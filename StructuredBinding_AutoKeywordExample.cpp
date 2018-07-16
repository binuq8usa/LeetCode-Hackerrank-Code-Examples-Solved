#include <iostream>
#include <cstdlib>
#include <set>
#include <string>
#include <tuple>
#include <iterator>
#include <map>


struct S{
  int n;
  std::string s;
  float d;
  
  bool operator<(const S& rhs) const{
    return std::tie(n,s,d) < std::tie(rhs.n,rhs.s,rhs.d);
  }
};

int main(int argc,char** argv){
  // create the set of the structure
  std::set<S> mySet;
  S value{21,"Test43",3.95};
  
  /*
  // pre-c++ 17
  std::set<S>::iterator iter;
  bool inserted;
  std::tie(iter,inserted) = mySet.insert(value); // this returns a std::pair but tie can unoack
  
  */
  const auto [iter,inserted] = mySet.insert(value);
  
  if(inserted)
    std::cout << "Value(" << iter->n << "," << iter->s << "," << iter->d << ")" << std::endl;
    //std::cout << "Value was inserted\n";
  
  double myArray[3] = {1.0,2.0,3.0};
  auto [a,b,c] = myArray;
  
  std::cout << a << "\t" << b << "\t" << c << std::endl;
  
  // unpacking pairs 
  std::pair<int,float> temp;
  temp.first = 2;
  temp.second = 3.4;
  
  auto [m,n] = temp;
  
  std::cout << m << "\t" << n << std::endl;
  
  // tuple
  //std::tuple<int,double,std::string,char> myTuple = std::tie(1,3.4,"Str",'c');
  // pre c++ 17
  //std::tuple<int,double,std::string,char> myTuple = std::make_tuple(1,3.4,"Str",'c');
  
  
  // post c++ 17
  std::tuple<int,double,std::string,char> myTuple = {1,3.4,"Binu",'N'};
  auto& [n1,d,str,ch] = myTuple; // this gets the reference to each element of tuple
  
  std::cout << "Auto values" << std::endl;
  std::cout << n1 << "\t" << d << "\t" << str << "\t" << ch << std::endl;
  
  d+= 3.4;
  
  std::cout << "MyTuple Values" << std::endl;
  std::cout << std::get<0>(myTuple) << "\t" << std::get<1>(myTuple) << "\t" << std::get<2>(myTuple) << "\t" << std::get<3>(myTuple) << std::endl;
  
  // creating a map
  const std::map<std::string, std::string> capitals{
    {"Poland","Warsaw"},
    {"England","London"},
    {"India","Delhi"}
    
  };
  
  // iterate throught the map
  for(const auto& [k,v] : capitals){
    std::cout << "Key : " << k << " ; Value : " << v << std::endl;
  }
  
}


/*
using namespace std;

// To execute C++, please define "int main()"
int main() {
  auto words = { "Hello, ", "World!", "\n" };
  for (const string& word : words) {
    cout << word;
  }
  return 0;
}

*/


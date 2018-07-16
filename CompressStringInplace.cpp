/*

Given an array of characters, compress it in-place.

The length after compression must always be smaller than or equal to the original array.

Every element of the array should be a character (not int) of length 1.

After you are done modifying the input array in-place, return the new length of the array.


Follow up:
Could you solve it using only O(1) extra space?


Example 1:
Input:
["a","a","b","b","c","c","c"]

Output:
Return 6, and the first 6 characters of the input array should be: ["a","2","b","2","c","3"]

Explanation:
"aa" is replaced by "a2". "bb" is replaced by "b2". "ccc" is replaced by "c3".
Example 2:
Input:
["a"]

Output:
Return 1, and the first 1 characters of the input array should be: ["a"]

Explanation:
Nothing is replaced.
Example 3:
Input:
["a","b","b","b","b","b","b","b","b","b","b","b","b"]

Output:
Return 4, and the first 4 characters of the input array should be: ["a","b","1","2"].

Explanation:
Since the character "a" does not repeat, it is not compressed. "bbbbbbbbbbbb" is replaced by "b12".
Notice each digit has it's own entry in the array.
Note:
All characters have an ASCII value in [35, 126].
1 <= len(chars) <= 1000.

*/


#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Method 1 - using string iterators
void compressString(string& queryString){
  string::iterator it_ref = queryString.begin();
  string::iterator it = it_ref + 1;
  
  while(it_ref!= queryString.end()){
    if( *it_ref == *it)
      it++;
    else{
      if(it > queryString.end())
        it = queryString.end();
      string strCount = to_string(it-it_ref);
      if(it-it_ref > 1){
        it_ref = queryString.erase(it_ref+1,it); // erase those characters
        it_ref = queryString.insert(it_ref,strCount.begin(),strCount.end());
      }
      it_ref = it_ref + strCount.size();
      it = it_ref + 1;
    }
  }
}

// Method 2 - using vector of chars
int compress(vector<char>& queryString) {
  vector<char>::iterator it_ref = queryString.begin();
  vector<char>::iterator it = it_ref + 1;
  while(it_ref!= queryString.end()){
    if( *it_ref == *it){
      it++;
    }
    else{
      if(it > queryString.end())
        it = queryString.end();
      string strCount = to_string(it-it_ref);
      vector<char> tempStr;
      for(int k = 0 ; k < strCount.size(); k++)
        tempStr.push_back(strCount[k]);
      if(it-it_ref > 1){
        it_ref = queryString.erase(it_ref+1,it);
        it_ref = queryString.insert(it_ref,strCount.begin(),strCount.end());
      }
      it_ref = it_ref + strCount.size();
      it = it_ref + 1;
    }
  }
  return queryString.size();
}

// To execute C++, please define "int main()"
int main() {
  string input = "aaabbaa";
  //compressString(input);
  
  vector<char> inp;
  for(int k = 0 ; k < input.size(); k++)
    inp.push_back(input[k]);
  compress(inp);
  
  
  //std::cout << inp << std::endl;
  for(int k = 0 ; k < inp.size(); k++){
    std::cout << inp[k] << ",";
  }
  std::cout << "\n";
}


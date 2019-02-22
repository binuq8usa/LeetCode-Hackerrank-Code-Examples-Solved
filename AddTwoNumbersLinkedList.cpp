/*
You are given two non-empty linked lists representing two non-negative integers. The digits are stored in reverse order and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.

You may assume the two numbers do not contain any leading zero, except the number 0 itself.

Example:

Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 0 -> 8
Explanation: 342 + 465 = 807.

*/

#include <iostream>
#include <cassert>
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

using namespace std;

struct ListNode{
  int val;
  ListNode* next;
  ListNode(int x): val(x),next(NULL){
    
  }
};

ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
  if(l1 == NULL && l2 == NULL)
    return NULL;
  if(l1 == NULL)
    return l2;
  if(l2 == NULL)
    return l1;
  
  ListNode* curr, *head, *prev;
  int carry = 0;
  int count = 0;
  while(l1 != NULL || l2 != NULL){
    int val1 = (l1 != NULL)?l1->val:0;
    int val2 = (l2 != NULL)?l2->val:0;
    
    assert(val1 < 10);
    assert(val2 < 10);
    
    int sum_val = val1 + val2 + carry;
    int dig_val = sum_val % 10;
    carry = sum_val / 10;
    
    if(count == 0){
      head = new ListNode(dig_val);
      head->next = new ListNode(0); // create the pointer for next digit
      curr = head->next;
      prev = head;
    }
    else{
      curr->val = dig_val;
      prev = curr;
      curr->next = new ListNode(0);
      curr = curr->next;
    }
    
    // assign next node
    if(l1 != NULL) l1 = l1->next;
    if(l2 != NULL) l2 = l2->next;
    count++;
  }
  
  assert(l1 == NULL);
  assert(l2 == NULL);
  
  if(carry > 0)
    curr->val = carry;
  else{ // delete the node
    prev->next = NULL;
    delete curr;
  }
  
  return head;    
}

void printNumber(ListNode* l){
  ListNode* temp = l;
  while(temp != NULL){
    std::cout << temp->val;
    temp = temp->next;
  }
  std::cout << "\n";
}

int convertNumberFromList(ListNode* l){
  ListNode* temp = l;
  int power10 = 1;
  int val = 0;
  while(temp != NULL){
    //std::cout << temp->val;
    val += temp->val * power10;
    temp = temp->next;
    power10 *= 10;
  }
  //std::cout << "Value = " << val << std::endl;
  return val;
}

TEST_CASE("Test Number","[convertNumberFromList]"){
  ListNode* number = new ListNode(2);
  number->next = new ListNode(4);
  number->next->next = new ListNode(3);
  
  REQUIRE(convertNumberFromList(number) == 342);
}

TEST_CASE("Test Number2","[convertNumberFromList]"){
  ListNode* number = new ListNode(7);
  number->next = new ListNode(0);
  number->next->next = new ListNode(8);
  
  REQUIRE(convertNumberFromList(number) == 807);
}


TEST_CASE("Add Two Numbers - leetcode","[addTwoNumbers]"){
  ListNode* number1= new ListNode(2);
  number1->next = new ListNode(4);
  number1->next->next = new ListNode(3);
  
  ListNode* number2= new ListNode(5);
  number2->next = new ListNode(6);
  number2->next->next = new ListNode(4);
  
  ListNode* number3 = addTwoNumbers(number1,number2);
  //printNumber(number3);
  REQUIRE(convertNumberFromList(number3) == 807); 
}

TEST_CASE("Add Two Numbers - max vales","[addTwoNumbers]"){
  ListNode* number1= new ListNode(9);
  number1->next = new ListNode(9);
  number1->next->next = new ListNode(9);
  
  ListNode* number2= new ListNode(9);
  number2->next = new ListNode(9);
  number2->next->next = new ListNode(9);
  
  
  ListNode* number3 = addTwoNumbers(number1,number2);
  //printNumber(number3);
  REQUIRE(convertNumberFromList(number3) == 1998); 
}

TEST_CASE("Add one small and large number","[addTwoNumbers]"){
  ListNode* number1= new ListNode(9);
  number1->next = new ListNode(4);
  
  ListNode* number2= new ListNode(9);
  number2->next = new ListNode(9);
  number2->next->next = new ListNode(5);
  
  
  ListNode* number3 = addTwoNumbers(number1,number2);
  //printNumber(number3);
  REQUIRE(convertNumberFromList(number3) == 648); 
}

TEST_CASE("Add one small and large number 2","[addTwoNumbers]"){
  ListNode* number1= new ListNode(9);
  number1->next = new ListNode(4);
  
  ListNode* number2= new ListNode(9);
  number2->next = new ListNode(9);
  number2->next->next = new ListNode(9);
  number2->next->next->next = new ListNode(9);
  
  ListNode* number3 = addTwoNumbers(number1,number2);
  //printNumber(number3);
  REQUIRE(convertNumberFromList(number3) == 10048); 
}

TEST_CASE("Add one small and large number 3","[addTwoNumbers]"){
  ListNode* number2= new ListNode(9);
  number2->next = new ListNode(4);
  
  ListNode* number1= new ListNode(9);
  number1->next = new ListNode(9);
  number1->next->next = new ListNode(9);
  number1->next->next->next = new ListNode(9);
  
  ListNode* number3 = addTwoNumbers(number1,number2);
  //printNumber(number3);
  REQUIRE(convertNumberFromList(number3) == 10048); 
}


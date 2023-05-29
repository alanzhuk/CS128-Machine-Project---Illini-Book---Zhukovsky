#include "illini_book.hpp"
#include <iostream>

int main() {

  auto hold = IlliniBook("/home/vagrant/src/mp11-illini-book-alanzhuk/example/persons.csv","/home/vagrant/src/mp11-illini-book-alanzhuk/example/relations.csv");
  std::cout << hold << "\n";
  std::cout << hold.GetRelated(9,7) << "\n";
  
  for (int i : hold.GetSteps(1,1)) {
    std::cout << i << "\n";
  }

  std::cout << hold.CountGroups() << "\n";
  std::cout << hold.GetRelated(1,8) << "\n";
/*
  std::cout << hold.GetRelated(2,6,"128") << "\n";

  std::vector<std::string> input;
  input.push_back("173");
  input.push_back("124");

  std::cout << hold.CountGroups(input) << "\n";
  return 0; */
}

#ifndef ILLINI_BOOK_HPP
#define ILLINI_BOOK_HPP

#include <string>
#include <vector>
#include <map> 
#include <list>
#include <utility> 
#include <fstream>
#include <queue>
#include <set>
#include "utilities.hpp"

class IlliniBook {
public:
  IlliniBook(const std::string &people_fpath, const std::string &relations_fpath);
  IlliniBook(const IlliniBook &rhs) = delete;
  IlliniBook &operator=(const IlliniBook &rhs) = delete;
  ~IlliniBook() = default;
  bool AreRelated(int uin_1, int uin_2) const;
  bool AreRelated(int uin_1, int uin_2, const std::string &relationship) const;
  int GetRelated(int uin_1, int uin_2) const;
  int GetRelated(int uin_1, int uin_2, const std::string &relationship) const;
  std::vector<int> GetSteps(int uin, int n) const;
  size_t CountGroups() const;
  size_t CountGroups(const std::string &relationship) const;
  size_t CountGroups(const std::vector<std::string> &relationships) const;
  friend std::ostream& operator<<(std::ostream& os, const IlliniBook& input);
  private:
  void AddVertex(int input); 
  void AddEdge(int inputone, int inputtwo, const std::string& relationship);
  int Distance(int input_one, int input_two) const;
  std::map<int, std::list<std::pair<int, std::string>>> graph_;
  std::set<int> vertices_; 
};

#endif

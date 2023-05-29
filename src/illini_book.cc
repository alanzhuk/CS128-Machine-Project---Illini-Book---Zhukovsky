#include "illini_book.hpp"
 /*
 std::map<int, std::list<std::pair<int, std::string>>> graph_;
  std::vector<int> vertices_;  
 */
// Your code here!
std::ostream& operator<<(std::ostream& os, const IlliniBook& input) {
    for(const auto& nums : input.vertices_) {
        os << nums << " : ";
        for (const auto& edges : input.graph_.at(nums)) {
            os << "< " << edges.first << " , " << edges.second << ">  |  ";
        }
        os << '\n';
    }
    return os;
}
void IlliniBook::AddVertex(int input) {
    graph_.insert({input, std::list<std::pair<int, std::string>>()});
    vertices_.insert(input);
}
void IlliniBook::AddEdge(int inputone, int inputtwo, const std::string& relationship) {
    auto& v1_adj = graph_.at(inputone);
    auto& v2_adj = graph_.at(inputtwo);
    v1_adj.push_back({inputtwo, relationship});
    v2_adj.push_back({inputone, relationship});
}
int IlliniBook::Distance(int input_one, int input_two) const {
    if (input_one == input_two) {
        return 0;
    }
    std::queue<std::pair<int,int>> queue; //first stores the value, then stores the distance
    std::set<int> visited = {input_one};
    queue.push({input_one,0});
    //loops through the rest
    while (!queue.empty()) {
        auto current = queue.front();
        queue.pop();  
        //visited.insert(current);
        for (const auto& i : graph_.at(current.first)) {
            if (!visited.contains(i.first)) {
                if (i.first == input_two) {
                    return current.second + 1;
                }
                queue.push({i.first,current.second + 1});
                visited.insert(i.first);
            }
        }
    }
    return -1; //failed to find result
}
IlliniBook::IlliniBook(const std::string &people_fpath, const std::string &relations_fpath) {
    //opens the files
    std::ifstream ifs_people{people_fpath};
    std::ifstream ifs_relations{relations_fpath};
    //makes all the vertices
    while (ifs_people.good()) {
        int add = 0;
        ifs_people >> add; 
        AddVertex(add);
    }

    //makes all the edges
    while (ifs_relations.good()) {
        std::string input;
        std::vector<std::string> split;
        ifs_relations >> input;
        if (ifs_relations.fail()) {
            return;
        }
        split = utilities::Split(input, ',');
        AddEdge(stoi(split[0]), stoi(split[1]), split[2]);
    }
} 
bool IlliniBook::AreRelated(int uin_1, int uin_2) const {
    return (Distance(uin_1,uin_2) >= 0);
} 
bool IlliniBook::AreRelated(int uin_1, int uin_2, const std::string &relationship) const {
    return (GetRelated(uin_1, uin_2, relationship) >= 0);
} 
int IlliniBook::GetRelated(int uin_1, int uin_2) const {
    return Distance(uin_1,uin_2);
}
int IlliniBook::GetRelated(int uin_1, int uin_2, const std::string &relationship) const {
    if (uin_1 == uin_2) {
        return 0;
    }
    std::queue<std::pair<int,int>> queue; //first stores the value, then stores the distance
    std::set<int> visited = {uin_1};
    queue.push({uin_1,0});
    //loops through the rest
    while (!queue.empty()) {
        auto current = queue.front();
        queue.pop();  
        //visited.insert(current);
        for (const auto& i : graph_.at(current.first)) {
            if (!visited.contains(i.first) && i.second == relationship) {
                if (i.first == uin_2) {
                    return current.second + 1;
                }
                queue.push({i.first,current.second + 1});
                visited.insert(i.first);
            }
        }
    }
    return -1; //failed to find result
} 
std::vector<int> IlliniBook::GetSteps(int uin, int n) const { //medium to high priority
    std::vector<int> ret; 
    if (n == 0) {
        ret = {uin};
        return ret;
    }
    std::queue<std::pair<int,int>> queue;
    std::set<int> visited = {uin};
    queue.push({uin,0});
    while (!queue.empty()) {
        auto current = queue.front();
        queue.pop();
        if (current.second == n) {
            ret.push_back(current.first);
        }
        for (const auto& i : graph_.at(current.first)) {
            if (!visited.contains(i.first) && current.second < n) {
                queue.push({i.first,current.second + 1});
                visited.insert(i.first);
            }
        }
    }
    return ret;
}
size_t IlliniBook::CountGroups() const { //can improve runtime a lot by changing from a vector to a set, because I can just call to remove in the for loop
    std::set<int> visited;
    size_t groups = 0;
    for (const auto& knode : vertices_) {
        if (!visited.contains(knode)) {
            groups++;
            std::queue<int> queue;
            visited.insert(knode);
            queue.push(knode);
            while (!queue.empty()) {
                int current = queue.front();
                queue.pop();
                for (const auto& i : graph_.at(current)) {
                    if (!visited.contains(i.first)) {
                        queue.push({i.first});
                        visited.insert(i.first);
                    }
                }
            }
        }
    }
    return groups;
}

size_t IlliniBook::CountGroups(const std::string &relationship) const {
    std::set<int> visited;
    size_t groups = 0;
    for (const auto& knode : vertices_) {
        if (!visited.contains(knode)) {
            groups++;
            std::queue<int> queue;
            visited.insert(knode);
            queue.push(knode);
            while (!queue.empty()) {
                int current = queue.front();
                queue.pop();
                for (const auto& i : graph_.at(current)) {
                    if (!visited.contains(i.first) && i.second == relationship) {
                        queue.push({i.first});
                        visited.insert(i.first);
                    }
                }
            }
        }
    }
    return groups;
}
size_t IlliniBook::CountGroups(const std::vector<std::string> &relationships) const {
    std::set<int> visited;
    size_t groups = 0;
    for (const auto& knode : vertices_) {
        if (!visited.contains(knode)) {
            groups++;
            std::queue<int> queue;
            visited.insert(knode);
            queue.push(knode);
            while (!queue.empty()) {
                int current = queue.front();
                queue.pop();
                for (const auto& i : graph_.at(current)) {
                    if (!visited.contains(i.first) && std::find(relationships.cbegin(),relationships.cend(),i.second) != relationships.end()) {
                        queue.push({i.first});
                        visited.insert(i.first);
                    }
                }
            }
        }
    }
    return groups;
}

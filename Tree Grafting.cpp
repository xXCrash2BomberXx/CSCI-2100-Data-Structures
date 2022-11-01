#include <iostream>
#include <string.h>
using std::string;

/*
Return the depth of the subtree rooted at the iterator position in the
input string and advance the iterator so that it ends up at the character
just beyond the ’u’ that ended the subtree traversal
*/
int depth(string::iterator& i) {
  if (*i != NULL) {
    
    int d {0};  // depth to find subtree end
    string str {""};
    do {
      d += (*i=='d'?1:-1);
      str += *i;
      i++;
    } while (*i != NULL && d != 0);  // find subtree end
    
    str = str.substr(1, str.size()-2);  // new string of current subtree
    string::iterator sub {str.begin()};  // new iterator current of subtree
    d = depth(sub)+1;  // depth of current subtree
    
    int d2 {0};
    if (*i != NULL) {
      d2 = depth(i);  // depth of next subtree
    }
    
    return (d>d2?d:d2);
  } else {
    return 0;
  }
}

int main() {
  string str = "dudduduudu";
  string::iterator it;
  it = str.begin();
  std::cout << depth(it) << std::endl;  // 2

  str = "ddddduuuuu";
  it = str.begin();
  std::cout << depth(it) << std::endl;  // 5

  str = "dddduduuuu";
  it = str.begin();
  std::cout << depth(it) << std::endl;  // 4

  str = "dddduuduuu";
  it = str.begin();
  std::cout << depth(it) << std::endl;  // 4
}
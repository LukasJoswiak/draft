#include <ios>
#include <iostream>
#include <fstream>

#include "Draft.hpp"

int main() {
  Draft d;
  d.Serialize(1);

  int n = Draft::Deserialize("binary");
  std::cout << n << std::endl;

  return 0;
}

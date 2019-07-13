#include "Draft.hpp"

#include <iostream>

void Draft::Serialize(int n) {
  std::ofstream ostrm_("binary", std::ios::out | std::ios::binary);
  ostrm_.write(reinterpret_cast<char *>(&n), sizeof(n));
  ostrm_.close();
}

int Draft::Deserialize(const std::string &filename) {
  std::ifstream istrm(filename, std::ios::in | std::ios::binary);
  int n;
  istrm.read(reinterpret_cast<char *>(&n), sizeof(n));
  return n;
}

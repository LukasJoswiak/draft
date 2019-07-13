#include <fstream>

class Draft {
 public:
  void Serialize(int n);

  static int Deserialize(const std::string &filename);
};

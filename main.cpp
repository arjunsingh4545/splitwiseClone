#include "json/json.hpp"
#include <fstream>
#include <iostream>
using json = nlohmann::json;

int main() {
  json j;
  j["username"] = "Alice";
  j["email"] = "alice@example.com";
  j["balance"] = {{"Bob", -50.0}, {"Charlie", 30.0}};

  std::ofstream file("data/user_Alice.json");
  file << j.dump(4); // Pretty print with 4-space indent
  file.close();

  std::cout << "Saved JSON!\n";
}

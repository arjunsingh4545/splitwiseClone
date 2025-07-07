#pragma once
#include "database.h"
#include "expenses.h"
#include "group.h"
#include "json/json.h"
#include <string>
#include <unordered_map>
class User {
public:
  std::string name; // name of the user
  std::unordered_map<std::string, float>
      balances; // list of balances with other users
                // key: user name, value: balance with that user
  User(std::string name) : name(std::move(name)) {}

  void updateBalance(const std::string &userName, float amount) {
    balances[userName] += amount;
  }

  float getTotalOwed() {
    float total = 0.0f;
    for (const auto &pair : balances) {
      if (balance.second < 0) {
        total += pair.second; // Add only negative balances (amount owed)
      }
    }
    return total;
  }

  float getTotalOwing() {
    float total = 0.0f;
    for (const auto &pair : balances) {
      if (pair.second > 0) {
        total +=
            pair.second; // Add only positive balances (amount owed to others)
      }
    }
    return total;
  }
  const std::unordered_map<std::string, float> &getBalances() const {
    return balances;
  }

  const std::string &getName() const { return name; }
};

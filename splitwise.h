#pragma once
#include "database.h"
#include "expenses.h"
#include "group.h"
#include "transaction.h"
#include "users.h"

#include <algorithm>
#include <memory>
#include <string>
#include <vector>
class Splitwise {
public:
  std::vector<User> users;
  std::vector<Group> groups;
  std::vector<Expense> expenses;
  Database db;
  Splitwise() {
    users = db.loadUsers();
    groups = db.loadGroups(users);
    expenses = db.loadExpenses();
  }

  void addUser(const std::string &name) {
    users.emplace_back(name);
    db.saveUsers(users);
  }

  void addGroup(const std::string &groupName,
                const std::vector<std::string> &memberNames) {
    std::vector<User> members;
    for (const auto &name : memberNames) {
      auto it = std::find_if(users.begin(), users.end(),
                             [&](const User &u) { return u.name == name; });
      if (it != users.end()) {
        members.push_back(*it);
      }
    }
    groups.emplace_back(groupName, members);
    db.saveGroups(groups);
  }

  void addExpense(const Expense &expense) {
    expenses.push_back(expense);
    db.saveExpenses(expenses);
    updateBalances(expense.groupName);
  }

private:
  void updateBalances(std::string groupName) {
    auto groupIt =
        std::find_if(groups.begin(), groups.end(),
                     [&](const Group &g) { return g.groupName == groupName; });
    if (groupIt != groups.end()) {
      for (const auto &split : groupIt->members) {
        auto userIt =
            std::find_if(users.begin(), users.end(),
                         [&](const User &u) { return u.name == split.name; });
        if (userIt != users.end()) {
          userIt->updateBalance(groupName, split.amount);
        }
      }
      db.saveUsers(users);
    }
  }

public:
};

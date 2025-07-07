// uses json to store data

#pragma once
#include "expenses.h"
#include "user.h"
#include "json/json.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <group.h>
#include <string>
#include <vector>
using json = nlohmann::json;
class Database {
  const std::string usersPath = "data/users.json";
  const std::string expensesPath = "data/expenses.json";
  const std::string groupsPath = "data/groups.json";

  void ensureDataDir() { std::filesystem::create_directories("data"); }

public:
  Database() { ensureDataDir(); }
  //+++++++++++++++++++USERS++++++++++++++++++++++++
  void saveUsers(const std::vector<User> &users) {
    json jUsers = json::array();
    for (const auto &user : users) {
      json balances = json::object();
      for (const auto &balance : user.balances) {
        balances[balance.first] = balance.second;
      }
      jUsers.push_back({{"name", user.getName()}, {"balances", balances}});
    }
    std::ofstream out(usersPath);
    out << jUsers.dump(4);
  }
  std::vector<User> loadUsers() {
    std::ifstream in(usersPath);
    std::vector<User> users;
    if (!in)
      return users;
    json jUsers;
    in >> jUsers;
    for (const auto &u : jUsers) {
      User user(u["name"]);
      for (auto &[key, val] : u["balances"].items()) {
        user.updateBalance(key, val);
      }
      users.push_back(user);
    }
    return users;
  }

  //+++++++++++++++++++GROUPS++++++++++++++++++++++++
  void saveGroups(const std::vector<Group> &groups) {
    json jGroups = json::array();
    for (const auto &g : groups) {
      json jMembers = json::array();
      for (const auto &m : g.members) {
        jMembers.push_back(m.name);
      }
      jGroups.push_back({{"name", g.groupName}, {"members", jMembers}});
    }
    std::ofstream out(groupsPath);
    out << jGroups.dump(4);
  }

  std::vector<Group> loadGroups(const std::vector<User> &allUsers) {
    std::ifstream in(groupsPath);
    std::vector<Group> groups;
    if (!in)
      return groups;
    json jGroups;
    in >> jGroups;

    for (const auto &g : jGroups) {
      std::vector<User> members;
      for (const auto &uname : g["members"]) {
        auto it = std::find_if(allUsers.begin(), allUsers.end(),
                               [&](const User &u) { return u.name == uname; });
        if (it != allUsers.end())
          members.push_back(*it);
      }
      groups.emplace_back(g["name"], members);
    }
    return groups;
  }

  //+++++++++++++++++++EXPENSES++++++++++++++++++++++++
  void saveExpenses(const std::vector<Expense> &expenses) {
    json jExpenses = json::array();
    for (const auto &e : expenses) {
      json jSplits = json::array();
      for (const auto &s : e.splits) {
        jSplits.push_back({{"user", s.userName}, {"amount", s.amount}});
      }
      jExpenses.push_back({{"description", e.description},
                           {"amount", e.amount},
                           {"payer", e.payer},
                           {"group", e.groupName},
                           {"splitType", static_cast<int>(e.splitType)},
                           {"splits", jSplits}});
    }
    std::ofstream out(expensesPath);
    out << jExpenses.dump(4);
  }

  std::vector<Expense> loadExpenses() {
    std::ifstream in(expensesPath);
    std::vector<Expense> expenses;
    if (!in)
      return expenses;
    json jExpenses;
    in >> jExpenses;

    for (const auto &e : jExpenses) {
      Expense exp(e["description"], e["amount"], e["payer"], e["group"]);
      exp.splitType = static_cast<SplitType>(e["splitType"]);
      for (const auto &s : e["splits"]) {
        exp.splits.push_back(Split(s["user"], s["amount"]));
      }
      expenses.push_back(exp);
    }

    return expenses;
  }
};

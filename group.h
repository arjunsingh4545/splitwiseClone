#pragma once
#include "user.h"
#include <string>
#include <vector>
class Group {
public:
  std::vector<User> members;
  std::string groupName;

  Group(std::string name) : groupName(std::move(name)) {}

  Group(std::string name, std::vector<User> &memberList)
      : groupName(std::move(name)), members(memberList) {}

  void addMember(const User &user) { members.push_back(user); }

  std::vector<User> getMembers() const { return members; }
  std::string getGroupName() const { return groupName; }
};

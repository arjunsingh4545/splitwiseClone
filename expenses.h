#pragma once
#include <string>
#include <vector>

enum class SplitType {
  EQUAL,        // Split the expense equally among all users
  PERCENTAGE,   // Split the expense based on percentage shares
  EXACT_AMOUNT, // Split the expense with exact amounts specified for each user
  UNDEFINED     // Undefined split type
};

class Split {
public:
  std::string userName; // name of the user
  float amount;
  Split(const std::string &name, float amt) : userName(name), amount(amt) {}
};

class Expense {
public:
  std::string description;   // description of the expense
  float amount;              // amount of the expense
  std::string payer;         // name of the user who paid the expense
  std::string groupName;     // name of the group the expense belongs to
  std::vector<Split> splits; // list of users who split the expense
  SplitType splitType;

  Expense(const std::string &desc, float amt, const std::string &payerName,
          const std::string &group)
      : description(desc), amount(amt), payer(payerName), groupName(group),
        splitType(SplitType::UNDEFINED) {}
};

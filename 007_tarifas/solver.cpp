/*
1. Fiz tudo e passou em todos os testes.
2. Fiz sozinho.
3. Entendi melhor quando temos várias classes e uma deve controlar a outra.
4. Demorei umas 3 horas eu acho. (fui fazendo aos poucos então n sei exatamente).
*/

#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <iterator>
#include <list>
#include <fn.hpp>

enum Label {
  deposit = 0,
  fee = 1,
  opening = 2,
  reverse = 3,
  withdraw = 4
};




class Operation {
  Label label;
  int index;
  int value;
  int balance;

public: 

  Operation(int index, Label label, int value, int balance) {
    this->label = label;
    this->index = index;
    this->value = value;
    this->balance = balance;
  }

  int getBalance() {
    return balance;
  }

  int getIndex() {
    return index;
  }

  Label getLabel() {
    return label;
  }

  int getValue() {
    return value;
  }

  std::string str() {
    std::string str_label;

    switch(label) {
      case deposit:
        str_label = "deposit";
        break;
      case fee:
        str_label = "fee";
        break;
      case opening:
        str_label = "opening";
        break;
      case reverse:
        str_label = "reverse";
        break;
      case withdraw:
        str_label = "withdraw";
        break;
      default:
        str_label = "error";
        break;
    }
    
    std::stringstream ss;
    ss << std::setw(2) << index << ": " << std::setw(8) << str_label << ": "; 
    ss << std::setw(4) << value << ": " << std::setw(4) << balance;
    return ss.str();
  }
};

std::ostream &operator<<(std::ostream &os, Operation op) {
  return os << op.str();
}





class BalanceManager {
  int balance {0};
  std::vector<Operation> extract;
  int nextId {0};

public: 

  BalanceManager() {
    addOperation(opening, 0);
  }

  void addOperation(Label label, int value) {
    switch (label) {
      case opening:
        balance = value;
        extract.push_back(Operation(nextId, opening, value, balance));
        nextId++;
        break;
      case deposit:
        balance += value;
        extract.push_back(Operation(nextId, deposit, value, balance));
        nextId++;
        break;
      case withdraw:
        balance -= value;
        extract.push_back(Operation(nextId, withdraw, -value, balance));
        nextId++;
        break;
      case fee:
        balance -= value;
        extract.push_back(Operation(nextId, fee, -value, balance));
        nextId++;
        break;
      case reverse:
        balance -= value;
        extract.push_back(Operation(nextId, reverse, -value, balance));
        nextId++;
        break;
      default:
        break;
    }
  }

  int getBalance() {
    return balance;
  }

  std::vector<Operation> getExtract(int qtdOp) {
    if (qtdOp == 0) {
      return extract;
    }
    else {
      std::vector<Operation> partialExtract;
      for (int i = (extract.size() - qtdOp); i < extract.size(); i++)
          partialExtract.push_back(extract[i]);
      return partialExtract;
    }
  }

  std::string str() {
    return fn::tostr(balance);
  }
};

std::ostream &operator<<(std::ostream &os, BalanceManager bm) {
  return os << bm.str();
}




class Account {
  BalanceManager balanceManager;
  int id;

public: 

  Account(int id=0) {
    this->id = id;
  }

  void accDeposit(int value) {
    if (value > 0)
      balanceManager.addOperation(deposit, value);
    else
      fn::write("fail: invalid value");
  }

  void accFee(int value) {
   balanceManager.addOperation(fee, value); 
  }

  void accReverse(int index) {
    auto operation = balanceManager.getExtract(0)[index];
    if (index < 0 || index >= balanceManager.getExtract(0).size()) {
      fn::write(fn::format("fail: index {} invalid", index));
      return;
    }
    if (operation.getLabel() != 1) {
      fn::write(fn::format("fail: index {} is not a fee", index));
      return;
    }
    balanceManager.addOperation(reverse, operation.getValue());
  }

  void accWithdraw(int value) {
    if (value <= balanceManager.getBalance())
      balanceManager.addOperation(withdraw, value);
    else
      fn::write("fail: insufficient balance");
  }

  BalanceManager getBalanceManager() {
    return balanceManager;
  }


  std::string str() {
    return fn::format("account:{} balance:{}", id, balanceManager);
  }
};

std::ostream &operator<<(std::ostream &os, Account acc) {
  return os << acc.str();
}


int main() {
  Account account;
  while (true) {
    auto line = fn::input();
    auto args = fn::split(line, ' ');
    fn::write("$" + line);
    if (args[0] == "end")
      break;
    else if (args[0] == "show") {
      fn::write(account);
    }
    else if (args[0] == "init") {
      account = Account(+args[1]);
    }
    else if (args[0] == "deposit") {
      account.accDeposit(+args[1]);
    }
    else if (args[0] == "withdraw") {
      account.accWithdraw(+args[1]);
    }
    else if (args[0] == "fee") {
      account.accFee(+args[1]);
    }
    else if (args[0] == "extract") {
      auto extract = account.getBalanceManager().getExtract(+args[1]);
      for (auto operation : extract)
        fn::write(operation);
    }
    else if (args[0] == "reverse") {
      for (int i = 1; i < args.size(); i++)
        account.accReverse(+args[i]);
    }
    else {
      fn::write("fail: comando invalido");
    }
  }
}
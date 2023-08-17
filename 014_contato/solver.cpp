#include <fn.hpp>

class Fone {
  std::string id;
  std::string number;

public:
  Fone(std::string id = "", std::string number = "") {
    this->id = id;
    this->number = number;
  }

  std::string getId() {
    return id;
  }

  std::string getNumber() {
    return number;
  }

  bool isValid() {
    for (auto letter : number) {
      if ((letter < '0' || letter > '9') && (letter != '(' && letter != ')' && letter != '.'))
        return false;
    }
    return true;
  }

  std::string str() {
    return fn::format("{}:{}", id, number);
  }
};

class Contact {
  std::string name;
  bool favorited;
  std::vector<Fone> fones;

public:
  Contact(std::string name = "") {
    this->name = name;
  }

  std::string getName() {
    return name;
  }

  std::vector<Fone> getFones() {
    return fones;
  }

  void addFone(std::string id, std::string number) {
    if (Fone(id, number).isValid()){
      fones.push_back(Fone(id, number));
    }      
    else {
      fn::write("fail: invalid number");
      return;
    }
  }

  void rmFone(int index) {
    fones.erase(fones.begin() + index);
  }

  void toogleFavorited() {
    favorited = !favorited;
  }

  bool isFavorited() {
    return favorited;
  }

  std::string str() {
    return fn::format("{} {} {}", (favorited ? "@" : "-"), name, fones);
  }
};

std::ostream &operator<<(std::ostream &out, Contact contato) {
  return out << contato.str();
}
std::ostream &operator<<(std::ostream &out, Fone fone) {
  return out << fone.str();
}

int main() {
  Contact contato;
  while (true) {
    auto line = fn::input();
    fn::write("$" + line);
    auto args = fn::split(line, ' ');

    if (args[0] == "end") {
      break;
    } 
    else if (args[0] == "init") {
      contato = Contact(args[1]);
    } 
    else if (args[0] == "add") {
      contato.addFone(args[1], args[2]);
    } 
    else if (args[0] == "rm") {
      contato.rmFone(+args[1]);
    } 
    else if (args[0] == "tfav") {
      contato.toogleFavorited();
    } 
    else if (args[0] == "show") {
      fn::write(contato);
    } 
    else {
      fn::write("fail: comando invalido");
    }
  }
}
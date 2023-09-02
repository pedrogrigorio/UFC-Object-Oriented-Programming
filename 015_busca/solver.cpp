 /*
 1. Fiz tudo e passou em todos os testes.
 2. Fiz sozinho.
 3. Aprimorei meu entendimento sobre como uma classe utiliza outra.
 4. Demorei cerca de 40 minutos.
*/

#include <algorithm>
#include <fn.hpp>
#include <sstream>
#include <string>

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
  bool favorited {false};
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




class Agenda {
  std::vector<Contact> contatos;

  int findContact(std::string id) {
    for (int i = 0; i < contatos.size(); i++) {
      if(contatos[i].getName() == id)
        return i;
    }
    return -1;
  }

public:
  // add contato que não existe ou adicionar fones ao contato que existe
  void addContato(std::string name, std::vector<Fone> fones) {
    int index = findContact(name);

    if (index != -1) {
      for (auto fone : fones) {
        contatos[index].addFone(fone.getId(), fone.getNumber());  
      }
    }
    else {
      Contact contact = Contact(name);
      for (auto fone : fones) {
        contact.addFone(fone.getId(), fone.getNumber());  
      }
      
      contatos.push_back(contact);
      
      auto cmp_function = [](auto a, auto b){
        return a.getName() < b.getName();
      };
        
      std::sort(contatos.begin(), contatos.end(), cmp_function);
    }
  }

  void rmContact(std::string name) {
    int index = findContact(name);
    if (index != -1) {
      contatos.erase(contatos.begin() + index);
    }
  }

  Contact *getContact(std::string id) {
    int index = findContact(id);
    if (index != -1) {
      return &contatos[index];
    }
    else {
      return NULL;
    }
  }

  std::vector<Contact> getContatos() {
    return contatos;
  }

  std::vector<Contact> search(std::string pattern) {
    std::vector<Contact> search_result;
    for (auto contato : contatos) {
      std::string contact_str = contato.str();
      size_t found = contact_str.find(pattern);
      if (found != std::string::npos)
        search_result.push_back(contato);
    }
    return search_result;
  }

  std::vector<Contact> getFavorited() {
    std::vector<Contact> favorited_result;
    for (auto contato : contatos) {
      if (contato.isFavorited())
        favorited_result.push_back(contato);
    }
    return favorited_result;
  }

  std::string str() {
    std::stringstream ss;

    for (int i = 0; i < contatos.size(); i++) {
      ss << contatos[i].str() << (i == (contatos.size()-1) ? "" : "\n");
    }
    
    return ss.str();
  }
};

std::ostream &operator<<(std::ostream &out, Fone fone) {
  return out << fone.str();
}
std::ostream &operator<<(std::ostream &out, Contact contato) {
  return out << contato.str();
}
std::ostream &operator<<(std::ostream &out, Agenda agenda) {
  return out << agenda.str();
}

int main() {
  Agenda agenda;
  while (true) {
    auto line = fn::input();
    fn::write("$" + line);
    auto args = fn::split(line, ' ');
    
    if (args[0] == "end") {
      break;
    } 
    else if (args[0] == "add") { // name id:fone id:fone ...
      std::vector<Fone> fones;
      for (int i = 2; i < (int)args.size(); i++) {
        auto parts = fn::split(args[i], ':');
        fones.push_back(Fone(parts[0], parts[1]));
      }
      agenda.addContato(args[1], fones);
    } 
    else if (args[0] == "show") {
      fn::write(agenda);
    } 
    else if (args[0] == "rmFone") { // id index
      Contact *contato = agenda.getContact(args[1]);
      if (contato != nullptr)
        contato->rmFone((int)+args[2]);
    } 
    else if (args[0] == "rm") { // id
      agenda.rmContact(args[1]);
    } 
    else if (args[0] == "tfav") { // id 1 ou 0
      Contact *contato = agenda.getContact(args[1]);
      if (contato != nullptr)
        contato->toogleFavorited();
    } 
    else if (args[0] == "favs") {
      agenda.getFavorited() | fn::JOIN("\n") | fn::WRITE();
    } 
    else if (args[0] == "search") { // pattern
      agenda.search(args[1]) | fn::JOIN("\n") | fn::WRITE();
    } 
    else {
      fn::write("fail: comando invalido");
    }
  }
}

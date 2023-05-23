/*
1. Fiz tudo e passou em todos os testes.
2. Fiz sozinho.
3. Utilização de listas e fixação do contéudo aprendido durante o exercício do
grafite
4. Demorei 20 minutos
*/

#include <fn.hpp>
#include <iostream>
#include <list>
#include <memory>
#include <sstream>
#include <vector>
using namespace fn;



class Kid {
private:
  int age;
  std::string name;

public:
  Kid(std::string name, int age) {
    this->age = age;
    this->name = name;
  }

  int getAge() { 
    return age;
  }

  std::string getName() { 
    return name;
  }

  std::string str() { 
    return name + ":" + std::to_string(age);
  }
};

std::ostream &operator<<(std::ostream &os, Kid kid) { 
  return os << kid.str(); 
}

using PtrKid = std::shared_ptr<Kid>;




class Trampoline {
  std::list<PtrKid> waiting;
  std::list<PtrKid> playing;

  PtrKid removeFromList(std::string name, std::list<PtrKid> &list) {
    for (PtrKid kid : list) {
      if (kid->getName() == name) {
        PtrKid aux = kid;
        list.remove(kid);
        return aux;
      }
    }
    
    return nullptr;
  }

public:
  Trampoline() {}

  void arrive(PtrKid kid) {
    waiting.push_front(kid);
  }

  void enter() {
    if (waiting.empty())
      return;
    playing.push_front(waiting.back());
    waiting.pop_back();
  }

  void leave() {
    if (playing.empty())
      return;
    waiting.push_front(playing.back());
    playing.pop_back();
  }

  PtrKid removeKid(std::string name) {

    PtrKid kid = removeFromList(name, waiting);
    if (kid == nullptr) {
      kid = removeFromList(name, playing);
    }
    
    return kid;
  }

  std::string str() { 
    return fn::tostr(waiting) + " => " + fn::tostr(playing);
  }
};




int main() {
  Trampoline tr;

  while (true) {
    auto line = input();
    write("$" + line);
    auto args = split(line);

    if (args[0] == "end") {
      break;
    } 
    else if (args[0] == "arrive") {
      tr.arrive(std::make_shared<Kid>(args[1], (int)+args[2]));
    } 
    else if (args[0] == "enter") {
      tr.enter();
    } 
    else if (args[0] == "leave") {
      tr.leave();
    } 
    else if (args[0] == "remove") {
      tr.removeKid(args[1]);
    } 
    else if (args[0] == "show") {
      write(tr.str());
    } 
    else {
      write("fail: invalid command");
    }
  }
}
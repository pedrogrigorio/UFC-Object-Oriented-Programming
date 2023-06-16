/*
1. Fiz tudo e passou em todos os testes.
2. Fiz sozinho em sala.
3. Entendimento de acesso quando posições do vetor podem ser nulas.
4. Demorei cerca de 50m.
*/

#include <fn.hpp>

class Cliente {
  std::string id;
  std::string fone;

public: 

  Cliente(std::string id = "", std::string fone = "") {
    this->id = id;
    this->fone = fone;
  }

  std::string getFone() {
    return fone;
  }

  std::string getId() {
    return id;
  }

  void setFone(std::string fone) {
    this->fone = fone;
  }

  void setId(std::string id) {
    this->id = id;
  }

  std::string str() {
    return fn::format("{}:{}", id, fone);
  }
};

std::ostream &operator<<(std::ostream &os, Cliente c) {
  return os << c.str();
}



class Sala {
  std::vector<std::shared_ptr<Cliente>> cadeiras;

  int procurar(std::string nome) {
    for (int i = 0; i < cadeiras.size(); i++) {
      if (cadeiras[i] != nullptr && cadeiras[i]->getId() == nome)
        return i;
    }
    return -1;
  }

public:
  Sala(int qtd = 0) { 
    for (int i = 0; i < qtd; i++)
      cadeiras.push_back(nullptr);
  }

  void reservar(std::string id, std::string fone, int ind) {
    if (ind > cadeiras.size() || ind < 0) {
      fn::write("fail: cadeira nao existe");
      return;
    }
    if (cadeiras[ind] != nullptr) {
      fn::write("fail: cadeira ja esta ocupada");
      return;
    }
    if (procurar(id) != -1) {
      fn::write("fail: cliente ja esta no cinema");
      return;
    }
    cadeiras[ind] = std::make_shared<Cliente>(id, fone);
  }

  void cancelar(std::string id) {
    int index = procurar(id);
    if (index != -1) {
      cadeiras[index] = nullptr;
      return;
    }
    else {
      fn::write("fail: cliente nao esta no cinema");
      return;
    }
  }

  std::string str() {
    std::stringstream ss;
    ss << "[";
    for (int i = 0; i < cadeiras.size(); i++) {
      ss << (cadeiras[i] == nullptr ? "-" : fn::tostr(cadeiras[i]));
      ss << (i == cadeiras.size()-1 ? "" : " ");
    }
    ss << "]";
    return ss.str();
  }
};

std::ostream &operator<<(std::ostream &os, Sala c) {
  return os << c.str();
}

int main() {
  Sala sala;
  while (true) {
    auto line = fn::input();
    auto args = fn::split(line, ' ');
    fn::write("$" + line);

    if (args[0] == "end")
      break;
    else if (args[0] == "show")
      fn::write(sala);
    else if (args[0] == "init")
      sala = Sala(+args[1]);
    else if (args[0] == "reservar")
      sala.reservar(args[1], args[2], (int)+args[3]);
    else if (args[0] == "cancelar")
      sala.cancelar(args[1]);
    else
      fn::write("fail: comando invalido");
  }
}

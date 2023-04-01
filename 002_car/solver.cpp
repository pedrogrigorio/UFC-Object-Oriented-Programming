#include <fn.hpp>

using namespace fn;
using namespace std;

struct Car {
  int pass{0};
  int pass_max{2};
  int gas{0};
  int gas_max{100};
  int km{0};

  void entrar(){
    if (pass == pass_max){
      write("fail: limite de pessoas atingido");
      return;
    }
    pass++;
  }

  void sair(){
    if (pass == 0){
      write("fail: nao ha ninguem no carro");
      return;
    }
    pass--;
  }

  void abastecer(int gas_input){
    if(gas_input > gas_max)
      gas = gas_max;
    else
      gas += gas_input;
    
  }
  void dirigir(int km_input){
    if(pass == 0){
      write("fail: nao ha ninguem no carro");
      return;
    }
    if(gas == 0){
      write("fail: tanque vazio");
      return;
    }
    if(gas < km_input){
      write("fail: tanque vazio apos andar " + tostr(gas) + " km");
      km += gas;
      gas = 0;
      return;
    }
    km += km_input;
    gas -= km_input;
  }
  string str() {
    return "pass: " + tostr(pass) + ", gas: " + tostr(gas) +
           ", km: " + tostr(km);
  }
};

int main() {
  Car car;
  while (true) {
    auto line = input();
    write("$" + line);
    auto args = split(line, ' ');

    if (args[0] == "end")
      break;
    else if (args[0] == "show")
      write(car.str());
    else if (args[0] == "enter")
      car.entrar();
    else if(args[0] == "leave")
      car.sair();
    else if(args[0] == "fuel")
      car.abastecer(stoi(args[1]));
    else if(args[0] == "drive")
      car.dirigir(stoi(args[1]));
  }
}
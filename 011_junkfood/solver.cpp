/*
1. Fiz tudo e passou em todos os testes.
2. Fiz sozinho em sala.
3. Foi o primeiro código construido do zero. Então aprendi melhor a main e os métodos toStr.
4. Demorei 1h 30m.
*/

#include <fn.hpp>
#include <iostream>
#include <iomanip>
#include <list>
#include <memory>
#include <sstream>
#include <vector>
using namespace fn;



class Slot {
    std::string name;
    float price;
    int quantity;

public:
    Slot(std::string name = "empty", int quantity = 0, float price = 0) {
        this->name = name;
        this->price = price; 
        this->quantity = quantity;
    }

    std::string getName() { 
        return name;
    }
  
    float getPrice() {
        return price;
    }
  
    int getQuantity() { 
        return quantity;
    }
  
    void setName(std::string name) { 
        this->name = name;
    }
  
    void setPrice(float price) {
        this->price = price;
    }
  
    void setQuantity(int quantity) { 
        this->quantity = quantity;
    }

    std::string str() { 
        return fn::format("[ {%7s} : {} U : {%.2f} RS]", name, quantity, price);
    }
};

std::ostream &operator<<(std::ostream &os, Slot slot) { 
    return os << slot.str(); 
}





class VendingMachine {
    std::vector<Slot> slots;
    float profit {0};
    float cash {0};
    int capacity {0};

public:
    VendingMachine(int capacity = 0) {
        this->capacity = capacity;
        for (int i = 0; i < capacity; i++) {
            Slot slot;
            slots.push_back(slot);
        }
    }

    std::string getSlot(int index) { 
        return {};
    }
  
    void setSlot(int index, Slot slot) {
        if (index >= slots.size()) {
            fn::write("fail: indice nao existe");
            return;
        }
        slots[index] = slot;
    }
  
    void clearSlot(int index) { 
        if (index >= slots.size()) {
            fn::write("fail: indice nao existe");
            return;
        }
        slots[index] = Slot();
    }
  
    void insertCash(float cash) {
        this->cash += cash;
        return;
    }
    
    float withdrawCash() {
        fn::write(fn::format("voce recebeu {%.2f} RS", cash));
        cash = 0;
        return cash;
    }
    
    float getCash() {
        return cash;
    }

    float getProfit() {
        return profit;
    }
    
    void buyItem(int index) {
        if (index >= slots.size()) {
            fn::write("fail: indice nao existe");
            return;
        }
        if (cash < slots[index].getPrice()) {
            fn::write("fail: saldo insuficiente");
            return;
        }
        if (slots[index].getQuantity() == 0) {
            fn::write("fail: espiral sem produtos");
            return;
        }
        fn::write(fn::format("voce comprou um {}", slots[index].getName()));
        cash -= slots[index].getPrice();
        slots[index].setQuantity(slots[index].getQuantity() - 1);
    }
    
    std::string str() { 
        std::stringstream ss;
        ss << std::fixed << std::setprecision(2) << "saldo: " << cash << "\n";
        for (int i = 0; i < slots.size(); i++) {
            ss << i << " " << slots[i].str() << (i == slots.size()-1 ? "" : "\n");
        }
        
        return ss.str();
    }
};

std::ostream &operator<<(std::ostream &os, VendingMachine machine) { 
    return os << machine.str(); 
}




int main() {
    
    VendingMachine vm;
    while (true) {
        auto line = input();
        write("$" + line);
        auto args = split(line);

        if (args[0] == "end") {
            break;
        } 
        else if (args[0] == "init") {
            vm = VendingMachine(+args[1]);
        } 
        else if (args[0] == "set") {
            vm.setSlot(+args[1], Slot(args[2], +args[3], +args[4]));
        } 
        else if (args[0] == "limpar") {
            vm.clearSlot(+args[1]);
        } 
        else if (args[0] == "dinheiro") {
            vm.insertCash(+args[1]);
        } 
        else if (args[0] == "troco") {
            vm.withdrawCash();
        }
        else if (args[0] == "comprar") {
            vm.buyItem(+args[1]);
        }
        else if (args[0] == "show") {
            write(vm.str());
        }
        else {
            write("fail: invalid command");
        }
    }
}
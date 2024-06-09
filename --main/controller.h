#include "base.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class Controller {
private:
  unsigned int len;
  Order *Orders;

public:
  Controller() {
    len = 0;
    Orders = new Order[len];
  }

  unsigned int getLength() { return len; }

  void getInfo() {
    for (unsigned int i = 0; i < len; i++)
      Orders[i].getInfo();
  }

  void deleteOrder(unsigned int index) {
      Order* newOrders = new Order[len - 1];
      for (unsigned int i = 0, j = 0; i < len; i++, j++) {
          if (i == (index - 1))
              i++;
          if (i < len)
              newOrders[j] = Orders[i];
      }
      len--;
      delete[] Orders;
      Orders = newOrders;
  }

  void newOrder() {
    setlocale(LC_CTYPE, "Russian");
    Order currentOrder;
    string fName;
    string lName;
    string phone;
    cout << "Имя:" << endl;
    cin >> fName;
    cout << "Фамилия" << endl;
    cin >> lName;
    cout << "Телефон:" << endl;
    cin >> phone;
    currentOrder.setClient(Client(fName, lName, phone));
    string cmd = "1";
    cout << "Добавить объект в заказ?\n";
    cout << "[1] Да\n";
    cout << "[2] Нет\n";
    do {
      cin >> cmd;
      if (cmd == "1") {
        string newProductName;
        unsigned int newProductPrice, newProductSize;
        cout << "Название: \n";
        cin >> newProductName;
        cout << "Цена: \n";
        cin >> newProductPrice;
        cout << "Размер: \n";
        cin >> newProductSize;
        currentOrder.addToCart(Product(newProductName, newProductPrice, newProductSize));
        cout << "Добавить еще один объект в заказ?\n";
        cout << "[1] Да\n";
        cout << "[2] Нет\n";
      }
    } while (cmd != "2");
    Order *newOrders = new Order[len + 1];
    for (unsigned int i = 0; i < len; i++)
      newOrders[i] = Orders[i];
    newOrders[len] = currentOrder;
    len++;
    delete[] Orders;
    Orders = newOrders;
  }

  void pushOrder(Order *newOrder) {
    Order *newOrders = new Order[len + 1];
    for (unsigned int i = 0; i < len; i++)
      newOrders[i] = Orders[i];
    newOrders[len] = *newOrder;
    len++;
    delete[] Orders;
    Orders = newOrders;
  }

  void saveFile() {
    ofstream out;
    out.open("data.txt");
    if (out.is_open()) {
      string info;
      for (unsigned int i = 0; i < len; i++) {
        info = Orders[i].getClient().getFirstName() + "|" + Orders[i].getClient().getLastName() + "|" + Orders[i].getClient().getPhone() + "|";
        for (unsigned int j = 0; j < Orders[i].getCartSize(); j++) {
          info += Orders[i].getCart()[j].getName() + "|" + to_string(Orders[i].getCart()[j].getPrice()) + "|" + to_string(Orders[i].getCart()[j].getSize()) + "|";
        }
        out << info << endl;
      }
      out.close();
    }
  }

  void loadFile() {
    ifstream in("data.txt");
    if (in.is_open()) {
      string buffer;
      while (getline(in, buffer)) {
        string firstName = buffer.substr(0, buffer.find("|"));
        buffer = buffer.substr(buffer.find("|") + 1, buffer.length() - buffer.find("|") - 1);

        string lastName = buffer.substr(0, buffer.find("|"));
        buffer = buffer.substr(buffer.find("|") + 1, buffer.length() - buffer.find("|") - 1);

        string phone = buffer.substr(0, buffer.find("|"));
        buffer = buffer.substr(buffer.find("|") + 1, buffer.length() - buffer.find("|") - 1);

        Order newOrder;
        newOrder.setClient(Client(firstName, lastName, phone));

        string temp;
        while (!buffer.empty()) {
          string name = buffer.substr(0, buffer.find("|"));
          buffer = buffer.substr(buffer.find("|") + 1, buffer.length() - buffer.find("|") - 1);
          unsigned int price = (unsigned int)stoi(buffer.substr(0, buffer.find("|")));
          buffer = buffer.substr(buffer.find("|") + 1, buffer.length() - buffer.find("|") - 1);
          unsigned int size = (unsigned int)stoi(buffer.substr(0, buffer.find("|")));
          buffer = buffer.substr(buffer.find("|") + 1, buffer.length() - buffer.find("|") - 1);
          newOrder.addToCart(Product(name, price, size));
        }
        pushOrder(&newOrder);
      }
    }
    in.close();
  }

  void changeOrder(unsigned const int index) {
    setlocale(LC_CTYPE, "Russian");
    Orders[index - 1].getInfo();
    string newClientFirstName, newClientLastName, newClientPhone;
    cout << "Имя: ";
    cin >> newClientFirstName;
    cout << "Фамилия: ";
    cin >> newClientLastName;
    cout << "Телефон: ";
    cin >> newClientPhone;
    Orders[index - 1].setClient(
    Client(newClientFirstName, newClientLastName, newClientPhone));
  }
  
  void removeFromObj(unsigned const int index) {
   setlocale(LC_CTYPE, "Russian");
   Orders[index - 1].getInfo();
   unsigned int itemIndex = 0;
   cout << "Выберите номер объекта";
   cin >> itemIndex;
   Orders[index - 1].removeFromObj(itemIndex - 1);
  }

  void addToOrder(unsigned const int index) {
    setlocale(LC_CTYPE, "Russian");
    Orders[index - 1].getInfo();
    string name;
    unsigned int price, size;
    cout << "Название: ";
    cin >> name;
    cout << "Цена: ";
    cin >> price;
    cout << "Размер: ";
    cin >> size;
    Orders[index - 1].addToCart(Product(name, price, size));
  }
};
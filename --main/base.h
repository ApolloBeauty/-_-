#include <iostream>
#include <string>

using namespace std;

class Product {
private:
  string name;
  unsigned int price;
  unsigned int size;

public:
  Product() : name(""), price(0), size(0) {}

  Product(const Product &other) {
    this->name = other.name;
    this->price = other.price;
    this->size = other.size;
  }

  Product(string name, unsigned int price, unsigned int size) : name(name), price(price), size(size) {}

  ~Product() {}

  string getName() const { 
      return name; 
  }

  unsigned int getPrice() const { 
      return price; 
  }

  unsigned int getSize() const { 
      return size; 
  }

  void setName(string name) { 
      this->name = name; 
  }

  void setPrice(unsigned int price) { 
      this->price = price; 
  }

  void setSize(unsigned int size) { 
      this->size = size; 
  }

  void operator=(const Product &other) {
    this->name = other.name;
    this->price = other.price;
    this->size = other.size;
  }
};

class Client {
private:
  string fName, lName, phone;
public:
  Client() : fName(""), lName(""), phone("") {}

  Client(string fName, string lName, string phone) : fName(fName), lName(lName), phone(phone) {}

  ~Client() {}

  string getFirstName() const { 
      return this->fName; 
  }

  string getLastName() const { 
      return this->lName; 
  }

  string getPhone() const {
      return this->phone; 
  }

  void setFirstName(string fName) { 
      this->fName = fName; 
  }

  void setLastName(string lName) { 
      this->lName = lName; 
  }

  void setPhone(string phone) { 
      this->phone = phone; 
  }
};

class Order {
private:
  Client client;
  Product *cart;
  unsigned int quantity;

public:
  Order() : cart(nullptr), quantity(0) {}

  ~Order() {
    if (this->cart != nullptr)
      delete[] cart;
  }

  void getInfo() {
      setlocale(LC_CTYPE, "Russian");
      cout << "Клиент: " << client.getFirstName() << " " << client.getLastName() << " " << client.getPhone();
      cout << endl;
      cout << "Объекты:\n";
    for (unsigned int i = 0; i < quantity; i++) {
        cout << "[" << i + 1 << "]";
        cout << " Название: " << cart[i].getName();
        cout << " Цена: " << cart[i].getPrice();
        cout << " Размер: " << cart[i].getSize() << endl;
    }
  }

  Client getClient() const { 
      return client; 
  }

  void setClient(const Client &newClient) { 
      client = newClient; 
  }

  Product *getCart() const { 
      return cart; 
  }

  unsigned int getCartSize() const { 
      return quantity; 
  }

  void addToCart(Product product) {
    this->quantity++;

    if (this->quantity == 1) {
      this->cart = new Product[this->quantity];
      this->cart[0] = product;
    }

    if (this->quantity > 1) {
      Product *newCart = new Product[this->quantity];

      for (unsigned int i = 0; i < this->quantity - 1; i++) {
        newCart[i] = this->cart[i];
      }

      newCart[this->quantity - 1] = product;

      this->cart = newCart;
    }
  }

  void removeFromObj(unsigned const int index) {

    delete &cart[index];
    this->quantity--;

    for (unsigned int i = index; i < this->quantity; i++) {
      cart[i] = cart[i + 1];
    }

  }

  Order &operator=(const Order &other) {
    if (this == &other)
      return *this;
    this->client = other.client;

    if (this->cart != nullptr)
      delete[] this->cart;
    this->quantity = other.quantity;

    if (this->quantity > 0) {
      this->cart = new Product[this->quantity];
      for (unsigned int i = 0; i < this->quantity; i++)
        this->cart[i] = other.cart[i];
    } else {
      this->cart = nullptr;
    }

    return *this;
  }
};
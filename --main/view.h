#include "controller.h"
#include <iostream>

using namespace std;

class View {
private:
    Controller base;

public:
    View() { base.loadFile(); }

    ~View() { base.saveFile(); }
    void execute() {
        setlocale(LC_CTYPE, "Russian");
        unsigned int choice = 0, indexForChange = 0, indexForRemoveProduct = 0,
            indexForDel = 0, indexForAdd = 0;
        while (choice != 6) {
            printMenu();
            cin >> choice;
            cin.ignore();
            switch (choice) {
            case 1:
                base.getInfo();
                break;
            case 2:
                base.newOrder();
                break;
            case 3:
                cout << "Выберите номер заказа:\n";
                while (indexForChange < 1 || indexForChange > base.getLength()) {
                    base.getInfo();
                    cin >> indexForChange;
                }
                base.changeOrder(indexForChange);
                break;
            case 4:
                base.getInfo();
                cout << "Выберете номер объекта:\n";
                while (indexForAdd < 1 || indexForAdd > base.getLength()) {
                    cin >> indexForAdd;
                }
                base.addToOrder(indexForAdd);
                break;
            case 5:
                base.getInfo();
                cout << "Выберете номер заказа:\n";
                while (indexForDel < 1 || indexForDel > base.getLength()) {
                    cin >> indexForDel;
                }
                base.deleteOrder(indexForDel);
                break;
            case 6:
                base.getInfo();
                cout << "Выберете номер заказа:\n";
                while (indexForRemoveProduct < 1 ||
                    indexForRemoveProduct > base.getLength()) {
                    cin >> indexForRemoveProduct;
                }
                base.removeFromObj(indexForRemoveProduct);
                break;
            case 0:
                exit(0);
                break;
            default:
                cout << "Попробуйте еще раз\n";
                break;
            }
            cout << endl;
        }
    }

    void printMenu() {
        setlocale(LC_CTYPE, "Russian");
        cout << "[1] Вывести все заказы\n";
        cout << "[2] Добавить заказ\n";
        cout << "[3] Редактировать заказ\n";
        cout << "[4] Добавить объект в заказ\n";
        cout << "[5] Удалить заказ\n";
        cout << "[6] Удалить объект из заказа\n";
        cout << "[0] Выход из программы\n";
        cout << "****************************************************************\n";
        cout << "Введите номер команды: ";
    }
};
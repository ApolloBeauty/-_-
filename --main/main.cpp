#include <iostream>
#include <stdlib.h>
#include "view.h"
#include <Windows.h>
#include <locale>

using namespace std;

int main() {
  setlocale(LC_CTYPE, "Russian");
  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);
  View v;
  v.execute();
}
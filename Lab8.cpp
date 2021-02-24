//
// Created by @mikhirurg on 13.06.2020.
//
#include "Menu.h"
int main(int argc, char** argv) {
  Cubic cubic;
  CubicWorker worker(cubic);
  Menu menu(worker, argc, argv);
  menu.Start();
  return 0;
}

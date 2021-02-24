//
// Created by @mikhirurg on 05.06.2020.
//

#ifndef UNTITLED8__CUBIC_H_
#define UNTITLED8__CUBIC_H_

#include <string>
#include <vector>
#include "Face.h"

/**
 * \brief Cube class
 * \author @mikhirurg
 * \version 0.1
 * \date 05.06.2020
 * \warning It is a study project
 *
 * This class offer do simple moves with the Cube, and get information about it's faces.
 */

class Cubic {
 public:
  Cubic(Cubic& other);
  Cubic();

  Face &operator[](int i);
  void FlipCube();
  Cubic & R();
  Cubic & M();
  Cubic & R(int i);
  Cubic & RS();
  Cubic & RS(int i);
  Cubic & LS();
  Cubic & LS(int g);
  Cubic & L();
  Cubic & L(int i);
  Cubic & U();
  Cubic & US();
  Cubic & DS();
  Cubic & D();
  Cubic & B();
  Cubic & BS();
  Cubic & F(int i);
  Cubic & F();
  Cubic & FS();
  Cubic & FS(int g);
  bool IsComplete();

  void EnableLog();
  void DisableLog();
  void EnablePrintMode();
  void DisablePrintMode();
  bool GetPrintMode();
  void PrintCube();
  std::vector<std::string> log;
 private:
  bool lod_mode = false;
  bool print_mode = false;
  int timeDur = 100;
  std::vector<Face> faces;
};

#endif //UNTITLED8__CUBIC_H_

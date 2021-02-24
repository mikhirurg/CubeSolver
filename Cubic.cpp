//
// Created by @mikhirurg on 05.06.2020.
//

#include <iostream>
#include "Cubic.h"

/**
 * Constructor for Cube.
 * Fills cube faces with basic colors.
 */
Cubic::Cubic()
    : faces() {
  faces.emplace_back('Y');
  faces.emplace_back('B');
  faces.emplace_back('R');
  faces.emplace_back('G');
  faces.emplace_back('O');
  faces.emplace_back('W');
}

Cubic::Cubic(Cubic &other) {
  faces.emplace_back('Y');
  faces.emplace_back('B');
  faces.emplace_back('R');
  faces.emplace_back('G');
  faces.emplace_back('O');
  faces.emplace_back('W');

  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 3; j++) {
      for (int k = 0; k < 3; k++) {
        faces[i][j][k] = other[i][j][k];
      }
    }
  }
}

/**
 * Operator to get cube's face
 * @param i
 * @return Face of the cube
 */
Face &Cubic::operator[](int i) {
  return faces[i];
}

/**
 * This method flips cube clockwise
 */
void Cubic::FlipCube() {
  R().R().M().M().LS().LS();
}

/**
 * This method makes simple move: rotates right face clockwise
 * @return Reference to this cube
 */
Cubic &Cubic::R() {

  char at, bt, ct, dt, ft, gt, ht, it;

  at = faces[2][0][0];
  bt = faces[2][1][0];
  ct = faces[2][2][0];
  dt = faces[2][0][1];
  ft = faces[2][2][1];
  gt = faces[2][0][2];
  ht = faces[2][1][2];
  it = faces[2][2][2];

  faces[2][0][0] = gt;
  faces[2][1][0] = dt;
  faces[2][2][0] = at;
  faces[2][0][1] = ht;
  faces[2][2][1] = bt;
  faces[2][0][2] = it;
  faces[2][1][2] = ft;
  faces[2][2][2] = ct;

  int temp1 = faces[0][2][0];
  faces[0][2][0] = faces[1][2][0];
  int temp2 = faces[3][0][2];
  faces[3][0][2] = temp1;
  temp1 = faces[5][2][0];
  faces[5][2][0] = temp2;
  faces[1][2][0] = temp1;

  temp1 = faces[0][2][1];
  faces[0][2][1] = faces[1][2][1];
  temp2 = faces[3][0][1];
  faces[3][0][1] = temp1;
  temp1 = faces[5][2][1];
  faces[5][2][1] = temp2;
  faces[1][2][1] = temp1;

  temp1 = faces[0][2][2];
  faces[0][2][2] = faces[1][2][2];
  temp2 = faces[3][0][0];
  faces[3][0][0] = temp1;
  temp1 = faces[5][2][2];
  faces[5][2][2] = temp2;
  faces[1][2][2] = temp1;

  if (lod_mode) {
    log.emplace_back("R");
  }

  if (print_mode) {
    PrintCube();
  }

  return *this;
}

/**
 * This method makes simple move: rotates right face counterclock-wise
 * @return Reference to this cube
 */
Cubic &Cubic::RS() {
  this->R().R().R();
  return *this;
}

/**
 * This method makes simple move: rotates left face clockwise
 * @return Reference to this cube
 */
Cubic &Cubic::LS() {
  this->L().L().L();
  return *this;
}

/**
 * This method makes simple move: rotates left face counterclock-wise
 * @return Reference to this cube
 */
Cubic &Cubic::L() {
  char at, bt, ct, dt, ft, gt, ht, it;

  at = faces[4][0][0];
  bt = faces[4][1][0];
  ct = faces[4][2][0];
  dt = faces[4][0][1];
  ft = faces[4][2][1];
  gt = faces[4][0][2];
  ht = faces[4][1][2];
  it = faces[4][2][2];

  faces[4][0][0] = gt;
  faces[4][1][0] = dt;
  faces[4][2][0] = at;
  faces[4][0][1] = ht;
  faces[4][2][1] = bt;
  faces[4][0][2] = it;
  faces[4][1][2] = ft;
  faces[4][2][2] = ct;

  int temp1 = faces[0][0][2];
  faces[0][0][2] = faces[3][2][0];
  int temp2 = faces[1][0][2];
  faces[1][0][2] = temp1;
  temp1 = faces[5][0][2];
  faces[5][0][2] = temp2;
  faces[3][2][0] = temp1;

  temp1 = faces[0][0][1];
  faces[0][0][1] = faces[3][2][1];
  temp2 = faces[1][0][1];
  faces[1][0][1] = temp1;
  temp1 = faces[5][0][1];
  faces[5][0][1] = temp2;
  faces[3][2][1] = temp1;

  temp1 = faces[0][0][0];
  faces[0][0][0] = faces[3][2][2];
  temp2 = faces[1][0][0];
  faces[1][0][0] = temp1;
  temp1 = faces[5][0][0];
  faces[5][0][0] = temp2;
  faces[3][2][2] = temp1;

  if (lod_mode) {
    log.emplace_back("L");
  }

  if (print_mode) {
    PrintCube();
  }

  return *this;
}

/**
 * This method makes simple move: rotates upper face counterclock-wise
 * @return Reference to this cube
 */
Cubic &Cubic::U() {
  char at, bt, ct, dt, ft, gt, ht, it;

  at = faces[0][0][0];
  bt = faces[0][1][0];
  ct = faces[0][2][0];
  dt = faces[0][0][1];
  ft = faces[0][2][1];
  gt = faces[0][0][2];
  ht = faces[0][1][2];
  it = faces[0][2][2];

  faces[0][0][0] = gt;
  faces[0][1][0] = dt;
  faces[0][2][0] = at;
  faces[0][0][1] = ht;
  faces[0][2][1] = bt;
  faces[0][0][2] = it;
  faces[0][1][2] = ft;
  faces[0][2][2] = ct;

  char temp1 = faces[1][0][0];
  faces[1][0][0] = faces[2][0][0];
  char temp2 = faces[4][0][0];
  faces[4][0][0] = temp1;
  temp1 = faces[3][0][0];
  faces[3][0][0] = temp2;
  faces[2][0][0] = temp1;

  temp1 = faces[1][1][0];
  faces[1][1][0] = faces[2][1][0];
  temp2 = faces[4][1][0];
  faces[4][1][0] = temp1;
  temp1 = faces[3][1][0];
  faces[3][1][0] = temp2;
  faces[2][1][0] = temp1;

  temp1 = faces[1][2][0];
  faces[1][2][0] = faces[2][2][0];
  temp2 = faces[4][2][0];
  faces[4][2][0] = temp1;
  temp1 = faces[3][2][0];
  faces[3][2][0] = temp2;
  faces[2][2][0] = temp1;

  if (lod_mode) {
    log.emplace_back("U");
  }

  if (print_mode) {
    PrintCube();
  }
  return *this;
}

/**
 * This method makes simple move: rotates upper face clockwise
 * @return Reference to this cube
 */
Cubic &Cubic::US() {
  this->U().U().U();
  return *this;
}

/**
 * This method makes simple move: rotates down face clockwise
 * @return Reference to this cube
 */
Cubic &Cubic::DS() {
  this->D().D().D();
  return *this;
}

/**
 * This method makes simple move: rotates down face counterclock-wise
 * @return Reference to this cube
 */
Cubic &Cubic::D() {
  int at, bt, ct, dt, ft, gt, ht, it;

  at = faces[5][0][0];
  bt = faces[5][1][0];
  ct = faces[5][2][0];
  dt = faces[5][0][1];
  ft = faces[5][2][1];
  gt = faces[5][0][2];
  ht = faces[5][1][2];
  it = faces[5][2][2];

  faces[5][0][0] = gt;
  faces[5][1][0] = dt;
  faces[5][2][0] = at;
  faces[5][0][1] = ht;
  faces[5][2][1] = bt;
  faces[5][0][2] = it;
  faces[5][1][2] = ft;
  faces[5][2][2] = ct;

  int temp1 = faces[2][0][2];
  faces[2][0][2] = faces[1][0][2];
  int temp2 = faces[3][0][2];
  faces[3][0][2] = temp1;
  temp1 = faces[4][0][2];
  faces[4][0][2] = temp2;
  faces[1][0][2] = temp1;

  temp1 = faces[2][1][2];
  faces[2][1][2] = faces[1][1][2];
  temp2 = faces[3][1][2];
  faces[3][1][2] = temp1;
  temp1 = faces[4][1][2];
  faces[4][1][2] = temp2;
  faces[1][1][2] = temp1;

  temp1 = faces[2][2][2];
  faces[2][2][2] = faces[1][2][2];
  temp2 = faces[3][2][2];
  faces[3][2][2] = temp1;
  temp1 = faces[4][2][2];
  faces[4][2][2] = temp2;
  faces[1][2][2] = temp1;

  if (lod_mode) {
    log.emplace_back("D");
  }

  if (print_mode) {
    PrintCube();
  }
  return *this;
}

/**
 * This method makes simple move: rotates back face counterclock-wise
 * @return Reference to this cube
 */
Cubic &Cubic::B() {

  int at, bt, ct, dt, ft, gt, ht, it;

  at = faces[3][0][0];
  bt = faces[3][1][0];
  ct = faces[3][2][0];
  dt = faces[3][0][1];
  ft = faces[3][2][1];
  gt = faces[3][0][2];
  ht = faces[3][1][2];
  it = faces[3][2][2];

  faces[3][0][0] = gt;
  faces[3][1][0] = dt;
  faces[3][2][0] = at;
  faces[3][0][1] = ht;
  faces[3][2][1] = bt;
  faces[3][0][2] = it;
  faces[3][1][2] = ft;
  faces[3][2][2] = ct;

  int temp1 = faces[4][0][0];
  faces[4][0][0] = faces[0][2][0];
  int temp2 = faces[5][0][2];
  faces[5][0][2] = temp1;
  temp1 = faces[2][2][2];
  faces[2][2][2] = temp2;
  faces[0][2][0] = temp1;

  temp1 = faces[4][0][1];
  faces[4][0][1] = faces[0][1][0];
  temp2 = faces[5][1][2];
  faces[5][1][2] = temp1;
  temp1 = faces[2][2][1];
  faces[2][2][1] = temp2;
  faces[0][1][0] = temp1;

  temp1 = faces[4][0][2];
  faces[4][0][2] = faces[0][0][0];
  temp2 = faces[5][2][2];
  faces[5][2][2] = temp1;
  temp1 = faces[2][2][0];
  faces[2][2][0] = temp2;
  faces[0][0][0] = temp1;

  if (lod_mode) {
    log.emplace_back("B");
  }

  if (print_mode) {
    PrintCube();
  }
  return *this;
}

/**
 * This method makes simple move: rotates back face clockwise
 * @return Reference to this cube
 */
Cubic &Cubic::BS() {
  this->B().B().B();
  return *this;
}

/**
 * This method makes simple move: rotates front face clockwise
 * @return Reference to this cube
 */
Cubic &Cubic::F() {
  int at, bt, ct, dt, ft, gt, ht, it;

  at = faces[1][0][0];
  bt = faces[1][1][0];
  ct = faces[1][2][0];
  dt = faces[1][0][1];
  ft = faces[1][2][1];
  gt = faces[1][0][2];
  ht = faces[1][1][2];
  it = faces[1][2][2];

  faces[1][0][0] = gt;
  faces[1][1][0] = dt;
  faces[1][2][0] = at;
  faces[1][0][1] = ht;
  faces[1][2][1] = bt;
  faces[1][0][2] = it;
  faces[1][1][2] = ft;
  faces[1][2][2] = ct;

  int temp1 = faces[2][0][2];
  faces[2][0][2] = faces[0][2][2];
  int temp2 = faces[5][0][0];
  faces[5][0][0] = temp1;
  temp1 = faces[4][2][0];
  faces[4][2][0] = temp2;
  faces[0][2][2] = temp1;

  temp1 = faces[2][0][1];
  faces[2][0][1] = faces[0][1][2];
  temp2 = faces[5][1][0];
  faces[5][1][0] = temp1;
  temp1 = faces[4][2][1];
  faces[4][2][1] = temp2;
  faces[0][1][2] = temp1;

  temp1 = faces[2][0][0];
  faces[2][0][0] = faces[0][0][2];
  temp2 = faces[5][2][0];
  faces[5][2][0] = temp1;
  temp1 = faces[4][2][2];
  faces[4][2][2] = temp2;
  faces[0][0][2] = temp1;

  if (lod_mode) {
    log.emplace_back("F");
  }

  if (print_mode) {
    PrintCube();
  }
  return *this;
}

/**
 * This method makes simple move: rotates front face counterclock-wise
 * @return Reference to this cube
 */
Cubic &Cubic::FS() {
  this->F().F().F();
  return *this;
}

/**
 * Checks if cube is complete
 * @return true if cube is complete
 */
bool Cubic::IsComplete() {
  for (int i = 0; i < 6; i++) {
    char c = faces[i][0][0];
    for (int j = 0; j < 2; j++) {
      for (int k = 0; k < 2; k++) {
        if (c != faces[i][j][k]) return false;
      }
    }
  }
  return true;
}

/**
 * Stops saving cube moves
 */
void Cubic::DisableLog() {
  lod_mode = false;
}

/**
 * Starts saving cube moves
 */
void Cubic::EnableLog() {
  log.clear();
  lod_mode = true;
}

/**
 * Makes R move relative to face g
 * @param g From what face we are looking to the cube
 * @return Reference to the the cube
 */
Cubic &Cubic::R(int g) {
  switch (g) {
    case 1:R();
      break;
    case 2:B();
      break;
    case 3:L();
      break;
    case 4:F();
      break;
  }
  return *this;
}

/**
 * Makes RS move relative to face g
 * @param g From what face we are looking to the cube
 * @return Reference to the the cube
 */
Cubic &Cubic::RS(int g) {
  R(g).R(g).R(g);
  return *this;
}

/**
 * This method makes simple move: rotates middle face clockwise
 * @return Reference to this cube
 */
Cubic &Cubic::M() {
  int temp1 = faces[0][1][0];
  faces[0][1][0] = faces[1][1][0];
  int temp2 = faces[3][1][2];
  faces[3][1][2] = temp1;
  temp1 = faces[5][1][0];
  faces[5][1][0] = temp2;
  faces[1][1][0] = temp1;

  temp1 = faces[0][1][1];
  faces[0][1][1] = faces[1][1][1];
  temp2 = faces[3][1][1];
  faces[3][1][1] = temp1;
  temp1 = faces[5][1][1];
  faces[5][1][1] = temp2;
  faces[1][1][1] = temp1;

  temp1 = faces[0][1][2];
  faces[0][1][2] = faces[1][1][2];
  temp2 = faces[3][1][0];
  faces[3][1][0] = temp1;
  temp1 = faces[5][1][2];
  faces[5][1][2] = temp2;
  faces[1][1][2] = temp1;

  if (lod_mode) {
    log.emplace_back("M");
  }

  if (print_mode) {
    PrintCube();
  }
  return *this;
}

/**
 * Makes L move relative to face g
 * @param g From what face we are looking to the cube
 * @return Reference to the the cube
 */
Cubic &Cubic::L(int g) {
  switch (g) {
    case 1:L();
      break;
    case 2:F();
      break;
    case 3:R();
      break;
    case 4:B();
      break;
  }
  return *this;
}

/**
 * Makes LS move relative to face g
 * @param g From what face we are looking to the cube
 * @return Reference to the the cube
 */
Cubic &Cubic::LS(int g) {
  return L(g).L(g).L(g);
}

/**
 * Makes F move relative to face g
 * @param g From what face we are looking to the cube
 * @return Reference to the the cube
 */
Cubic &Cubic::F(int g) {
  switch (g) {
    case 1:F();
      break;
    case 2:R();
      break;
    case 3:B();
      break;
    case 4:L();
      break;
  }
  return *this;
}

/**
 * Makes FS move relative to face g
 * @param g From what face we are looking to the cube
 * @return Reference to the the cube
 */
Cubic &Cubic::FS(int g) {
  return F(g).F(g).F(g);
}

/**
 * This method prints cube faces
 */
void Cubic::PrintCube() {
  for (int i = 0; i < 6; i++) {
    std::cout << "Face #" << i << ":" << std::endl;
    for (int j = 0; j < 3; j++) {
      for (int k = 0; k < 3; k++) {
        std::cout << faces[i][j][k] << "\t";
      }
      std::cout << std::endl;
    }
  }
}
/**
 * Enables print mode for cube
 */
void Cubic::EnablePrintMode() {
  print_mode = true;
}

/**
 * Disables print mode for cube
 */
void Cubic::DisablePrintMode() {
  print_mode = false;
}

/**
 * Gets print mode status.
 * @return
 */
bool Cubic::GetPrintMode() {
  return print_mode;
}

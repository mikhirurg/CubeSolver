//
// Created by @mikhirurg on 05.06.2020.
//

#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>
#include <tuple>
#include <set>
#include "CubicWorker.h"

//! Maximum moves for solution
const int MaxMoves = 10000;

CubicWorker::CubicWorker(Cubic &cubic)
    : cubic_(cubic), gen(1) {

}


/**
 * Returns Reference to the cube
 * @return Reference to processed cube
 */
Cubic &CubicWorker::GetCube() {
  return cubic_;
}
std::vector<std::string> CubicWorker::Mix(int t) {
  std::vector<std::string> ans;
  std::uniform_int_distribution<> uid(0, 7);
  for (int i = 0; i < t; i++) {
    int p = uid(gen);
    switch (p) {
      case 0: {
        cubic_.U();
        ans.emplace_back("U");
      }
        break;
      case 1: {
        cubic_.US();
        ans.emplace_back("US");
      }
        break;
      case 2: {
        cubic_.RS();
        ans.emplace_back("RS");
      }
        break;
      case 3: {
        cubic_.R();
        ans.emplace_back("R");
      }
        break;
      case 4: {
        cubic_.L();
        ans.emplace_back("L");
      }
        break;
      case 5: {
        cubic_.LS();
        ans.emplace_back("LS");
      }
        break;
      case 6: {
        cubic_.F();
        ans.emplace_back("F");
      }
        break;
      case 7: {
        cubic_.FS();
        ans.emplace_back("FS");
      }
        break;
      default: {
        // Never happen
      }
    }
  }

  return ans;
}

/**
 * Save cube state to the file
 * @param fname Name of the file to save
 */
void CubicWorker::Save(const std::string &fname) {
  std::ofstream out;
  out.open(fname);
  if (out.is_open()) {
    for (int i = 0; i < 6; i++) {
      for (int j = 0; j < 3; j++) {
        for (int k = 0; k < 3; k++) {
          out << cubic_[i][j][k];
        }
      }
    }
  } else {
    std::cout << "Error while saving cube!" << std::endl;
    out.close();
    return;
  }
  std::cout << "Save completed successfully!" << std::endl;
  out.close();
}

/**
 * Loads cube state from the file and check if cube is valid
 * @param fname Name of the file to load
 */
void CubicWorker::Load(const std::string &fname) {
  std::ifstream in(fname);
  if (in.is_open()) {

    Cubic tmp = cubic_;

    char c;
    for (int i = 0; i < 6; i++) {
      for (int j = 0; j < 3; j++) {
        for (int k = 0; k < 3; k++) {
          in >> c;
          cubic_[i][j][k] = c;
        }
      }
    }

    if (!CheckValid()) {
      std::cout << "Error, invalid cube!" << std::endl;
      cubic_ = tmp;
      return;
    }
    std::cout << "Load completed successfully!" << std::endl;
  } else {
    std::cout << "Error while loading cube!" << std::endl;
  }
  in.close();
}

/**
 * Method which checks if corner contains face
 * @param t Corner of the cube
 * @param e Number of the face
 * @return If corner contains face
 */
bool CubicWorker::HF(std::tuple<int, int, int> &t, int e) {
  return std::get<0>(t) == e || std::get<1>(t) == e || std::get<2>(t) == e;
}

/**
 * Checks if pair of faces contains face with number e
 * @param p Pair of faces of the cube
 * @param e Number of face
 * @return If pair contains the face
 */
bool CubicWorker::HF(std::pair<int, int> &p, int e) {
  return p.first == e || p.second == e;
}

/**
 * Rotates upper face to cube to align face with central segments.
 * @param a Number of segments to align
 * @return
 */
bool CubicWorker::UAlign(int a) {
  int moves = 0;
  int c = 0;
  for (int i = 1; i < 5; i++) {
    if (cubic_[i][1][1] == cubic_[i][1][0]) {
      c++;
    }
  }
  while (c < a && moves < MaxMoves) {
    cubic_.U();
    moves++;
    c = 0;
    for (int i = 1; i < 5; i++) {
      if (cubic_[i][1][1] == cubic_[i][1][0]) {
        c++;
      }
    }
  }

  return c == a;
}

/**
 * This method builds yellow cross on the top of the cube.
 */
void CubicWorker::BuildYellowCross() {
  std::pair<int, int> yb = getYB();
  if (!((yb.first == 1 && yb.second == 0) || (yb.first == 0 && yb.second == 1))) {
    if (yb.first == 0 || yb.second == 0) {
      if (yb.first == 2 || yb.second == 2) {
        cubic_.RS().RS().DS().FS().FS();
      } else if (yb.first == 3 || yb.second == 3) {
        cubic_.B().B().D().D().F().F();
      } else if (yb.first == 4 || yb.second == 4) {
        cubic_.L().L().D().F().F();
      }
    } else if (yb.first == 1 || yb.second == 1) {
      if (yb.first == 4 || yb.second == 4) {
        cubic_.F();
      } else if (yb.first == 5 || yb.second == 5) {
        cubic_.F().F();
      } else if (yb.first == 2 || yb.second == 2) {
        cubic_.FS();
      }
    } else if (yb.first == 2 || yb.second == 2) {
      if (yb.first == 3 || yb.second == 3) {
        cubic_.R().DS().RS().F().F();
      } else if (yb.first == 5 || yb.second == 5) {
        cubic_.DS().F().F();
      }
    } else if (yb.first == 3 || yb.second == 3) {
      if (yb.first == 4 || yb.second == 4) {
        cubic_.LS().D().L().F().F();
      } else if (yb.first == 5 || yb.second == 5) {
        cubic_.D().D().F().F();
      }
    } else if (yb.first == 4 || yb.second == 4) {
      cubic_.D().F().F(); // Only 5
    }
  }

  if (cubic_[0][1][2] == 'B') {
    cubic_.F().US().R().U();
  }

  std::pair<int, int> ry = getCC('R', 'Y');
  if (!((ry.first == 2 && ry.second == 0) || (ry.first == 0 && ry.second == 2))) {
    if (ry.first == 0 || ry.second == 0) {
      if (ry.first == 1 || ry.second == 1) {
        cubic_.F().F().D().R().R();
      } else if (ry.first == 3 || ry.second == 3) {
        cubic_.B().B().DS().R().R();
      } else if (ry.first == 4 || ry.second == 4) {
        cubic_.L().L().D().D().R().R();
      }
    } else if (ry.first == 1 || ry.second == 1) {
      if (ry.first == 2 || ry.second == 2) {
        cubic_.R();
      } else if (ry.first == 5 || ry.second == 5) {
        cubic_.D().R().R();
      } else if (ry.first == 4 || ry.second == 4) {
        cubic_.L().D().D().LS().R().R();
      }
    } else if (ry.first == 2 || ry.second == 2) {
      if (ry.first == 3 || ry.second == 3) {
        cubic_.RS();
      } else if (ry.first == 5 || ry.second == 5) {
        cubic_.R().R();
      }
    } else if (ry.first == 3 || ry.second == 3) {
      if (ry.first == 4 || ry.second == 4) {
        cubic_.LS().DS().DS().L().R().R();
      } else if (ry.first == 5 || ry.second == 5) {
        cubic_.DS().R().R();
      }
    } else if (ry.first == 4 || ry.second == 4) {
      cubic_.D().D().R().R(); // Only 5
    }
  }

  if (cubic_[0][2][1] == 'R') {
    cubic_.R().US().B().U();
  }

  std::pair<int, int> gy = getCC('G', 'Y');

  if (!((gy.first == 3 && gy.second == 0) || (gy.first == 0 && gy.second == 3))) {
    if (gy.first == 0 || gy.second == 0) {
      if (gy.first == 1 || gy.second == 1) {
        cubic_.F().F().D().D().B().B();
      } else if (gy.first == 2 || gy.second == 2) {
        cubic_.R().R().D().B().B();
      } else if (gy.first == 4 || gy.second == 4) {
        cubic_.L().L().DS().B().B();
      }
    } else if (gy.first == 1 || gy.second == 1) {
      if (gy.first == 2 || gy.second == 2) {
        cubic_.RS().D().R().B().B();
      } else if (gy.first == 4 || gy.second == 4) {
        cubic_.FS().D().D().F().B().B();
      } else if (gy.first == 5 || gy.second == 5) {
        cubic_.D().D().B().B();
      }
    } else if (gy.first == 2 || gy.second == 2) {
      if (gy.first == 3 || gy.second == 3) {
        cubic_.B();
      } else if (gy.first == 5 || gy.second == 5) {
        cubic_.D().B().B();
      }
    } else if (gy.first == 3 || gy.second == 3) {
      if (gy.first == 4 || gy.second == 4) {
        cubic_.BS();
      } else if (gy.first == 5 || gy.second == 5) {
        cubic_.B().B();
      }
    } else if (gy.first == 4 || gy.second == 4) {
      cubic_.DS().B().B(); // Only 5
    }
  }

  if (cubic_[0][1][0] == 'G') {
    cubic_.B().US().L().U();
  }

  std::pair<int, int> yo = getCC('Y', 'O');

  if (!((yo.first == 4 && yo.second == 0) || (yo.first == 0 && yo.second == 4))) {
    if (yo.first == 0 || yo.second == 0) {
      if (yo.first == 1 || yo.second == 1) {
        cubic_.F().F().DS().L().L();
      } else if (yo.first == 2 || yo.second == 2) {
        cubic_.RS().RS().DS().DS().L().L();
      } else if (yo.first == 3 || yo.second == 3) {
        cubic_.B().B().D().L().L();
      }
    } else if (yo.first == 1 || yo.second == 1) {
      if (yo.first == 2 || yo.second == 2) {
        cubic_.RS().DS().DS().R().L().L();
      } else if (yo.first == 4 || yo.second == 4) {
        cubic_.LS();
      } else if (yo.first == 5 || yo.second == 5) {
        cubic_.DS().L().L();
      }
    } else if (yo.first == 2 || yo.second == 2) {
      if (yo.first == 3 || yo.second == 3) {
        cubic_.BS().D().B().L().L();
      } else if (yo.first == 5 || yo.second == 5) {
        cubic_.D().D().L().L();
      }
    } else if (yo.first == 3 || yo.second == 3) {
      if (yo.first == 4 || yo.second == 4) {
        cubic_.L();
      } else if (yo.first == 5 || yo.second == 5) {
        cubic_.D().L().L();
      }
    } else if (yo.first == 4 || yo.second == 4) {
      cubic_.L().L(); // Only 5
    }
  }

  if (cubic_[0][0][1] == 'O') {
    cubic_.L().US().F().U();
  }
}

/**
 * Rotates corners on the top face to valid position.
 */
void CubicWorker::BuildYellowCorners() {
  auto cbyr = GetCorner('B', 'Y', 'R');

  if (HF(cbyr, 1) && HF(cbyr, 4) && HF(cbyr, 0)) {
    cubic_.RS(4).DS().R(4).D().D();
  } else if (HF(cbyr, 1) && HF(cbyr, 4) && HF(cbyr, 5)) {
    cubic_.D();
  } else if (HF(cbyr, 4) && HF(cbyr, 0) && HF(cbyr, 3)) {
    cubic_.RS(3).DS().R(3).D().D().D();
  } else if (HF(cbyr, 4) && HF(cbyr, 5) && HF(cbyr, 3)) {
    cubic_.D().D();
  } else if (HF(cbyr, 0) && HF(cbyr, 2) && HF(cbyr, 3)) {
    cubic_.RS(2).DS().R(2).D().DS();
  } else if (HF(cbyr, 5) && HF(cbyr, 2) && HF(cbyr, 3)) {
    cubic_.DS();
  }

  while (!(cubic_[0][2][2] == 'Y' && cubic_[1][2][0] == 'B' && cubic_[2][0][0] == 'R')) {
    cubic_.RS().DS().R().D();
  }

  auto cgyr = GetCorner('G', 'Y', 'R');

  if (HF(cgyr, 0) && HF(cgyr, 1) && HF(cgyr, 2)) {
    cubic_.RS().DS().R().D().D();
  } else if (HF(cgyr, 5) && HF(cgyr, 1) && HF(cgyr, 2)) {
    cubic_.D();
  } else if (HF(cgyr, 0) && HF(cgyr, 1) && HF(cgyr, 4)) {
    cubic_.RS(4).DS().R(4).D().D().D();
  } else if (HF(cgyr, 5) && HF(cgyr, 1) && HF(cgyr, 4)) {
    cubic_.D().D();
  } else if (HF(cgyr, 0) && HF(cgyr, 3) && HF(cgyr, 4)) {
    cubic_.RS(3).DS().R(3).D().DS();
  } else if (HF(cgyr, 5) && HF(cgyr, 3) && HF(cgyr, 4)) {
    cubic_.DS();
  }

  while (!(cubic_[0][2][0] == 'Y' && cubic_[2][2][0] == 'R' && cubic_[3][0][0] == 'G')) {
    cubic_.RS(2).DS().R(2).D();
  }

  auto cgyo = GetCorner('G', 'Y', 'O');

  if (HF(cgyo, 0) && HF(cgyo, 1) && HF(cgyo, 2)) {
    cubic_.RS().DS().R().D().D().D();
  } else if (HF(cgyo, 5) && HF(cgyo, 1) && HF(cgyo, 2)) {
    cubic_.D().D();
  } else if (HF(cgyo, 0) && HF(cgyo, 2) && HF(cgyo, 3)) {
    cubic_.RS(2).DS().R(2).D().D();
  } else if (HF(cgyo, 5) && HF(cgyo, 2) && HF(cgyo, 3)) {
    cubic_.D();
  } else if (HF(cgyo, 1) && HF(cgyo, 0) && HF(cgyo, 4)) {
    cubic_.RS(4).DS().R(4).D().DS();
  } else if (HF(cgyo, 5) && HF(cgyo, 1) && HF(cgyo, 4)) {
    cubic_.DS();
  }

  while (!(cubic_[0][0][0] == 'Y' && cubic_[3][2][0] == 'G' && cubic_[4][0][0] == 'O')) {
    cubic_.RS(3).DS().R(3).D();
  }

  auto cbyo = GetCorner('B', 'Y', 'O');

  if (HF(cbyo, 0) && HF(cbyo, 1) && HF(cbyo, 2)) {
    cubic_.RS().DS().R().D().DS();
  } else if (HF(cbyo, 5) && HF(cbyo, 1) && HF(cbyo, 2)) {
    cubic_.DS();
  } else if (HF(cbyo, 0) && HF(cbyo, 2) && HF(cbyo, 3)) {
    cubic_.RS(2).DS().R(2).D().D().D();
  } else if (HF(cbyo, 5) && HF(cbyo, 2) && HF(cbyo, 3)) {
    cubic_.D().D();
  } else if (HF(cbyo, 0) && HF(cbyo, 3) && HF(cbyo, 4)) {
    cubic_.RS(4).DS().R(4).D().D();
  } else if (HF(cbyo, 4) && HF(cbyo, 5) && HF(cbyo, 3)) {
    cubic_.D();
  }

  while (!(cubic_[0][0][2] == 'Y' && cubic_[1][0][0] == 'B' && cubic_[4][2][0] == 'O')) {
    cubic_.RS(4).DS().R(4).D();
  }
}

/**
 * This method builds middle row of the cube.
 */
void CubicWorker::BuildMiddleRow() {
  cubic_.FlipCube();

  bool p = true;

  while (p) {
    p = false;

    auto cgr = getCC('G', 'R');
    if (HF(cgr, 0)) {
      if (HF(cgr, 3)) {
        cubic_.U();
      } else if (HF(cgr, 4)) {
        cubic_.U().U();
      } else if (HF(cgr, 1)) {
        cubic_.US();
      }
      if (cubic_[0][2][1] == 'G') {
        cubic_.US().LS(2).U().L(2);
        cubic_.U().F(2).US().FS(2);
      } else {
        cubic_.U();
        cubic_.U().R(1).US().RS(1);
        cubic_.US().FS(1).U().F(1);
      }
    } else if (HF(cgr, 4) && HF(cgr, 1)) {
      cubic_.U().R(4).US().RS(4);
      cubic_.US().FS(4).U().F(4);
      p = true;
    } else if (HF(cgr, 4) && HF(cgr, 3)) {
      cubic_.U().R(3).US().RS(3);
      cubic_.US().FS(3).U().F(3);
      p = true;
    } else if (HF(cgr, 2) && HF(cgr, 3)) {
      cubic_.U().R(2).US().RS(2);
      cubic_.US().FS(2).U().F(2);
      p = true;
    } else if (HF(cgr, 1) && HF(cgr, 2) && cubic_[1][2][1] == 'R') {
      cubic_.U().R(1).US().RS(1);
      cubic_.US().FS(1).U().F(1);
      p = true;
    }
  }
  p = true;
  while (p) {
    p = false;
    auto crb = getCC('R', 'B');
    if (HF(crb, 0)) {
      if (HF(crb, 1)) {
        cubic_.U().U();
      } else if (HF(crb, 2)) {
        cubic_.US();
      } else if (HF(crb, 4)) {
        cubic_.U();
      }

      if (cubic_[0][1][0] == 'R') {
        cubic_.US().LS(3).U().L(3);
        cubic_.U().F(3).US().FS(3);
      } else {
        cubic_.U();
        cubic_.U().R(2).US().RS(2);
        cubic_.US().FS(2).U().F(2);
      }
    } else if (HF(crb, 4) && HF(crb, 1)) {
      cubic_.U().R(4).US().RS(4);
      cubic_.US().FS(4).U().F(4);
      p = true;
    } else if (HF(crb, 4) && HF(crb, 3)) {
      cubic_.U().R(3).US().RS(3);
      cubic_.US().FS(3).U().F(3);
      p = true;
    } else if (HF(crb, 2) && HF(crb, 3) && cubic_[2][2][1] == 'B') {
      cubic_.U().R(2).US().RS(2);
      cubic_.US().FS(2).U().F(2);
      p = true;
    } else if (HF(crb, 1) && HF(crb, 2)) {
      cubic_.U().R(1).US().RS(1);
      cubic_.US().FS(1).U().F(1);
      p = true;
    }
  }

  p = true;
  while (p) {
    p = false;
    auto cbo = getCC('B', 'O');
    if (HF(cbo, 0)) {
      if (HF(cbo, 1)) {
        cubic_.U();
      } else if (HF(cbo, 2)) {
        cubic_.U().U();
      } else if (HF(cbo, 3)) {
        cubic_.US();
      }

      if (cubic_[0][0][1] == 'B') {
        cubic_.US().LS(4).U().L(4);
        cubic_.U().F(4).US().FS(4);
      } else {
        cubic_.U();
        cubic_.U().R(3).US().RS(3);
        cubic_.US().FS(3).U().F(3);
      }
    } else if (HF(cbo, 4) && HF(cbo, 1)) {
      cubic_.U().R(4).US().RS(4);
      cubic_.US().FS(4).U().F(4);
      p = true;
    } else if (HF(cbo, 4) && HF(cbo, 3) && cubic_[3][2][1] == 'O') {
      cubic_.U().R(3).US().RS(3);
      cubic_.US().FS(3).U().F(3);
      p = true;
    } else if (HF(cbo, 2) && HF(cbo, 3)) {
      cubic_.U().R(2).US().RS(2);
      cubic_.US().FS(2).U().F(2);
      p = true;
    } else if (HF(cbo, 1) && HF(cbo, 2)) {
      cubic_.U().R(1).US().RS(1);
      cubic_.US().FS(1).U().F(1);
      p = true;
    }
  }

  p = true;
  while (p) {
    p = false;
    auto cgo = getCC('G', 'O');
    if (HF(cgo, 0)) {
      if (HF(cgo, 2)) {
        cubic_.U();
      } else if (HF(cgo, 3)) {
        cubic_.U().U();
      } else if (HF(cgo, 4)) {
        cubic_.US();
      }

      if (cubic_[0][1][2] == 'O') {
        cubic_.US().LS(1).U().L(1);
        cubic_.U().F(1).US().FS(1);
      } else {
        cubic_.U();
        cubic_.U().R(4).US().RS(4);
        cubic_.US().FS(4).U().F(4);
      }
    } else if (HF(cgo, 4) && HF(cgo, 1) && cubic_[4][2][1] == 'G') {
      cubic_.U().R(4).US().RS(4);
      cubic_.US().FS(4).U().F(4);
      p = true;
    } else if (HF(cgo, 4) && HF(cgo, 3)) {
      cubic_.U().R(3).US().RS(3);
      cubic_.US().FS(3).U().F(3);
      p = true;
    } else if (HF(cgo, 2) && HF(cgo, 3)) {
      cubic_.U().R(2).US().RS(2);
      cubic_.US().FS(2).U().F(2);
      p = true;
    } else if (HF(cgo, 1) && HF(cgo, 2)) {
      cubic_.U().R(1).US().RS(1);
      cubic_.US().FS(1).U().F(1);
      p = true;
    }
  }
}

/**
 * Builds wrong white cross on the down face of the cube.
 */
void CubicWorker::BuildWhiteWrongCross() {
  while (!(cubic_[0][1][0] == 'W' &&
      cubic_[0][0][1] == 'W' &&
      cubic_[0][1][2] == 'W' &&
      cubic_[0][2][1] == 'W')) {
    if (cubic_[0][0][1] == 'W' && cubic_[0][2][1] == 'W') {
      cubic_.F().R().U().RS().US().FS();
    } else if (cubic_[0][1][0] == 'W' && cubic_[0][1][2] == 'W') {
      cubic_.U();
      cubic_.F().R().U().RS().US().FS();
    } else if (cubic_[0][0][1] == 'W' && cubic_[0][1][0] == 'W') {
      cubic_.F().R().U().RS().US().FS();
    } else if (cubic_[0][1][0] == 'W' && cubic_[0][2][1] == 'W') {
      cubic_.US();
      cubic_.F().R().U().RS().US().FS();
    } else if (cubic_[0][2][1] == 'W' && cubic_[0][1][2] == 'W') {
      cubic_.U().U();
      cubic_.F().R().U().RS().US().FS();
    } else if (cubic_[0][0][1] == 'W' && cubic_[0][1][2] == 'W') {
      cubic_.U();
      cubic_.F().R().U().RS().US().FS();
    } else {
      cubic_.F().R().U().RS().US().FS();
    }
  }
}

/**
 * This method builds right white cross on the down face of the cube
 */
void CubicWorker::BuildWhiteRightCross() {
  UAlign(2);

  if ((cubic_[1][1][1] == cubic_[1][1][0] && cubic_[3][1][1] == cubic_[3][1][0])) {
    cubic_.R(2).U().RS(2).U().R(2).U().U().RS(2);
  } else if (cubic_[2][1][1] == cubic_[2][1][0] && cubic_[4][1][1] == cubic_[4][1][0]) {
    cubic_.R().U().RS().U().R().U().U().RS();
  }
  UAlign(2);

  if (!(cubic_[1][1][0] == 'G' && cubic_[2][1][0] == 'R' &&
      cubic_[3][1][0] == 'B' && cubic_[4][1][0] == 'O')) {
    if (cubic_[3][1][0] == 'B' && cubic_[2][1][0] == 'R') {
      cubic_.R().U().RS().U().R().U().U().RS().U();
    } else if (cubic_[4][1][0] == 'O' && cubic_[3][1][0] == 'B') {
      cubic_.R(2).U().RS(2).U().R(2).U().U().RS(2).U();
    } else if (cubic_[4][1][0] == 'O' && cubic_[1][1][0] == 'G') {
      cubic_.R(3).U().RS(3).U().R(3).U().U().RS(3).U();
    } else if (cubic_[1][1][0] == 'G' && cubic_[2][1][0] == 'R') {
      cubic_.R(4).U().RS(4).U().R(4).U().U().RS(4).U();
    }
  }
}

/**
 * This method builds white corners on the down face of the cube.
 */
void CubicWorker::BuildWhiteCorners() {
  auto crbw = GetCorner('R', 'B', 'W');
  auto cgrw = GetCorner('G', 'R', 'W');
  auto cbow = GetCorner('B', 'O', 'W');
  auto cgow = GetCorner('G', 'O', 'W');

  if (!((HF(crbw, 2) && HF(crbw, 3)) ||
      (HF(cgrw, 2) && HF(cgrw, 1)) ||
      (HF(cbow, 3) && HF(cbow, 4)) ||
      (HF(cgow, 4) && HF(cgow, 1)))) {
    cubic_.U().R().US().LS().U().RS().US().L();
  }

  if (HF(crbw, 2) && HF(crbw, 3) &&
      HF(cgrw, 4) && HF(cgrw, 3) &&
      HF(cbow, 4) && HF(cbow, 1) &&
      HF(cgow, 1) && HF(cgow, 2)) {
    cubic_.US().LS(3).U().R(3).US().L(3).U().RS(3);
  } else if (HF(crbw, 2) && HF(crbw, 3) &&
      HF(cgrw, 1) && HF(cgrw, 4) &&
      HF(cbow, 1) && HF(cbow, 2) &&
      HF(cgow, 3) && HF(cgow, 4)) {
    cubic_.U().R(2).US().LS(2).U().RS(2).US().L(2);
  } else if (HF(crbw, 1) && HF(crbw, 4) &&
      HF(cgrw, 2) && HF(cgrw, 1) &&
      HF(cbow, 3) && HF(cbow, 2) &&
      HF(cgow, 3) && HF(cgow, 4)) {
    cubic_.U().R(1).US().LS(1).U().RS(1).US().L(1);
  } else if (HF(crbw, 3) && HF(crbw, 4) &&
      HF(cgrw, 2) && HF(cgrw, 1) &&
      HF(cbow, 1) && HF(cbow, 4) &&
      HF(cgow, 2) && HF(cgow, 3)) {
    cubic_.US().LS(2).U().R(2).US().L(2).U().RS(2);
  } else if (HF(crbw, 1) && HF(crbw, 2) &&
      HF(cgrw, 1) && HF(cgrw, 4) &&
      HF(cbow, 3) && HF(cbow, 4) &&
      HF(cgow, 2) && HF(cgow, 3)) {
    cubic_.U().R(3).US().LS(3).U().RS(3).US().L(3);
  } else if (HF(crbw, 1) && HF(crbw, 4) &&
      HF(cgrw, 2) && HF(cgrw, 3) &&
      HF(cbow, 3) && HF(cbow, 4) &&
      HF(cgow, 1) && HF(cgow, 2)) {
    cubic_.US().LS(4).U().R(4).US().L(4).U().RS(4);
  } else if (HF(crbw, 1) && HF(crbw, 2) &&
      HF(cgrw, 3) && HF(cgrw, 4) &&
      HF(cbow, 2) && HF(cbow, 3) &&
      HF(cgow, 4) && HF(cgow, 1)) {
    cubic_.U().R(4).US().LS(4).U().RS(4).US().L(4);
  } else if (HF(crbw, 3) && HF(crbw, 4) &&
      HF(cgrw, 2) && HF(cgrw, 3) &&
      HF(cbow, 1) && HF(cbow, 2) &&
      HF(cgow, 4) && HF(cgow, 1)) {
    cubic_.US().LS(1).U().R(1).US().L(1).U().RS(1);
  }
}

/**
 * This method builds white down face of the cube.
 */
void CubicWorker::BuildWhite() {
  auto crbw = GetCorner('R', 'B', 'W');
  auto cgrw = GetCorner('G', 'R', 'W');
  auto cbow = GetCorner('B', 'O', 'W');
  auto cgow = GetCorner('G', 'O', 'W');
  while (!((HF(crbw, 2) && HF(crbw, 3)) &&
      (HF(cgrw, 2) && HF(cgrw, 1)) &&
      (HF(cbow, 3) && HF(cbow, 4)) &&
      (HF(cgow, 4) && HF(cgow, 1)))) {
    BuildWhiteCorners();
    crbw = GetCorner('R', 'B', 'W');
    cgrw = GetCorner('G', 'R', 'W');
    cbow = GetCorner('B', 'O', 'W');
    cgow = GetCorner('G', 'O', 'W');
  }
}

/**
 * Rotates white corners of the cube.
 */
void CubicWorker::RotateWhiteCorners() {
  while (cubic_[0][2][2] != 'W' || cubic_[1][2][0] != 'G' || cubic_[2][0][0] != 'R') {
    cubic_.RS().DS().R().D();
  }
  cubic_.U();
  while (cubic_[0][2][2] != 'W' || cubic_[1][2][0] != 'R' || cubic_[2][0][0] != 'B') {
    cubic_.RS().DS().R().D();
  }
  cubic_.U();
  while (cubic_[0][2][2] != 'W' || cubic_[1][2][0] != 'B' || cubic_[2][0][0] != 'O') {
    cubic_.RS().DS().R().D();
  }
  cubic_.U();
  while (cubic_[0][2][2] != 'W' || cubic_[1][2][0] != 'O' || cubic_[2][0][0] != 'G') {
    cubic_.RS().DS().R().D();
  }
  cubic_.U();
  cubic_.FlipCube();
}

/**
 * This method tries to solve Rubik's Cube.
 * @return If Rubicks Cube is completed.
 */
bool CubicWorker::CompileCubic() {
  cubic_.EnableLog();

  // Yellow cross
  BuildYellowCross();

  // Yellow corners
  BuildYellowCorners();

  // Middle row
  BuildMiddleRow();

  // White wrong cross
  BuildWhiteWrongCross();

  // Right white cross
  BuildWhiteRightCross();
  //cubic_.FlipCube();

  // Right white corners
  BuildWhite();

  // Rotate white corners
  RotateWhiteCorners();

  cubic_.DisableLog();
  return CheckValid() && IsCompiled();
}

/**
 * Gets pair of faces with yellow and blue colors.
 * @return Pair of faces.
 */
std::pair<int, int> CubicWorker::getYB() {
  if ((cubic_[1][1][0] == 'Y' && cubic_[0][1][2] == 'B') ||
      (cubic_[1][1][0] == 'B' && cubic_[0][1][2] == 'Y')) {
    return {1, 0};
  }
  if ((cubic_[1][2][1] == 'Y' && cubic_[2][0][1] == 'B') ||
      (cubic_[1][2][1] == 'B' && cubic_[2][0][1] == 'Y')) {
    return {1, 2};
  }
  if ((cubic_[1][1][2] == 'Y' && cubic_[5][1][0] == 'B') ||
      (cubic_[1][1][2] == 'B' && cubic_[5][1][0] == 'Y')) {
    return {1, 5};
  }
  if ((cubic_[1][0][1] == 'Y' && cubic_[4][2][1] == 'B') ||
      (cubic_[1][0][1] == 'B' && cubic_[4][2][1] == 'Y')) {
    return {1, 4};
  }

  if ((cubic_[2][1][0] == 'Y' && cubic_[0][2][1] == 'B') ||
      (cubic_[2][1][0] == 'B' && cubic_[0][2][1] == 'Y')) {
    return {2, 0};
  }
  if ((cubic_[2][2][1] == 'Y' && cubic_[3][0][1] == 'B') ||
      (cubic_[2][2][1] == 'B' && cubic_[3][0][1] == 'Y')) {
    return {2, 3};
  }
  if ((cubic_[2][1][2] == 'Y' && cubic_[5][2][1] == 'B') ||
      (cubic_[2][1][2] == 'B' && cubic_[5][2][1] == 'Y')) {
    return {2, 5};
  }

  if ((cubic_[3][1][0] == 'Y' && cubic_[0][1][0] == 'B') ||
      (cubic_[3][1][0] == 'B' && cubic_[0][1][0] == 'Y')) {
    return {3, 0};
  }
  if ((cubic_[3][2][1] == 'Y' && cubic_[4][0][1] == 'B') ||
      (cubic_[3][2][1] == 'B' && cubic_[4][0][1] == 'Y')) {
    return {3, 4};
  }
  if ((cubic_[3][1][2] == 'Y' && cubic_[5][1][2] == 'B') ||
      (cubic_[3][1][2] == 'B' && cubic_[5][1][2] == 'Y')) {
    return {3, 5};
  }

  if ((cubic_[4][1][0] == 'Y' && cubic_[0][0][1] == 'B') ||
      (cubic_[4][1][0] == 'B' && cubic_[0][0][1] == 'Y')) {
    return {4, 0};
  }
  if ((cubic_[4][2][1] == 'Y' && cubic_[4][0][1] == 'B') ||
      (cubic_[4][2][1] == 'B' && cubic_[4][0][1] == 'Y')) {
    return {4, 2};
  }
  if ((cubic_[4][1][2] == 'Y' && cubic_[5][0][1] == 'B') ||
      (cubic_[4][1][2] == 'B' && cubic_[5][0][1] == 'Y')) {
    return {4, 5};
  }
  return {-1, -1};
}

/**
 * Checks if cube has normal number of colors of segments
 * @return If cube has normal number of segments
 */
bool CubicWorker::FaceStat() {
  std::map<char, int> stat;
  stat.insert(std::make_pair('R', 0));
  stat.insert(std::make_pair('G', 0));
  stat.insert(std::make_pair('B', 0));
  stat.insert(std::make_pair('Y', 0));
  stat.insert(std::make_pair('O', 0));
  stat.insert(std::make_pair('W', 0));

  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 3; j++) {
      for (int k = 0; k < 3; k++) {
        int a = stat.find(cubic_[i][j][k])->second;
        stat.find(cubic_[i][j][k])->second = a + 1;
      }
    }
  }

  for (auto c : stat) {
    if (c.second != 9) {
      std::cout << "Wrong state!" << std::endl;
      std::cout << "[";
      for (auto c1 : stat) {
        std::cout << " " << c1.first << " - " << c1.second;
      }
      std::cout << "]" << std::endl;
      return false;
    }
  }

  return true;
}

/**
 * Gets pair of faces with c1 and c2 colors.
 * @return Pair of faces.
 */
std::pair<int, int> CubicWorker::getCC(char c1, char c2) {
  if ((cubic_[1][1][0] == c1 && cubic_[0][1][2] == c2) ||
      (cubic_[1][1][0] == c2 && cubic_[0][1][2] == c1)) {
    return {1, 0};
  }
  if ((cubic_[1][2][1] == c1 && cubic_[2][0][1] == c2) ||
      (cubic_[1][2][1] == c2 && cubic_[2][0][1] == c1)) {
    return {1, 2};
  }
  if ((cubic_[1][1][2] == c1 && cubic_[5][1][0] == c2) ||
      (cubic_[1][1][2] == c2 && cubic_[5][1][0] == c1)) {
    return {1, 5};
  }
  if ((cubic_[1][0][1] == c1 && cubic_[4][2][1] == c2) ||
      (cubic_[1][0][1] == c2 && cubic_[4][2][1] == c1)) {
    return {1, 4};
  }

  if ((cubic_[2][1][0] == c1 && cubic_[0][2][1] == c2) ||
      (cubic_[2][1][0] == c2 && cubic_[0][2][1] == c1)) {
    return {2, 0};
  }
  if ((cubic_[2][2][1] == c1 && cubic_[3][0][1] == c2) ||
      (cubic_[2][2][1] == c2 && cubic_[3][0][1] == c1)) {
    return {2, 3};
  }
  if ((cubic_[2][1][2] == c1 && cubic_[5][2][1] == c2) ||
      (cubic_[2][1][2] == c2 && cubic_[5][2][1] == c1)) {
    return {2, 5};
  }

  if ((cubic_[3][1][0] == c1 && cubic_[0][1][0] == c2) ||
      (cubic_[3][1][0] == c2 && cubic_[0][1][0] == c1)) {
    return {3, 0};
  }
  if ((cubic_[3][2][1] == c1 && cubic_[4][0][1] == c2) ||
      (cubic_[3][2][1] == c2 && cubic_[4][0][1] == c1)) {
    return {3, 4};
  }
  if ((cubic_[3][1][2] == c1 && cubic_[5][1][2] == c2) ||
      (cubic_[3][1][2] == c2 && cubic_[5][1][2] == c1)) {
    return {3, 5};
  }

  if ((cubic_[4][1][0] == c1 && cubic_[0][0][1] == c2) ||
      (cubic_[4][1][0] == c2 && cubic_[0][0][1] == c1)) {
    return {4, 0};
  }
  if ((cubic_[4][2][1] == c1 && cubic_[4][0][1] == c2) ||
      (cubic_[4][2][1] == c2 && cubic_[4][0][1] == c1)) {
    return {4, 2};
  }
  if ((cubic_[4][1][2] == c1 && cubic_[5][0][1] == c2) ||
      (cubic_[4][1][2] == c2 && cubic_[5][0][1] == c1)) {
    return {4, 5};
  }
  return {-1, -1};
}

/**
 * Returns tuple of numbers of faces of corner with c1, c2, c3 params
 * @param c1 Color of face
 * @param c2 Color of face
 * @param c3 Color of face
 * @return Tuple of number of faces of corner with c1, c2, c3 colors. If there no corner with c1, c2, c3 colors returns tuple {-1, -1, -1}.
 */
std::tuple<int, int, int> CubicWorker::GetCorner(char c1, char c2, char c3) {
  if (equals({cubic_[1][2][0], cubic_[0][2][2], cubic_[2][0][0]}, {c1, c2, c3})) {
    return {1, 0, 2};
  }
  if (equals({cubic_[2][2][0], cubic_[0][2][0], cubic_[3][0][0]}, {c1, c2, c3})) {
    return {2, 0, 3};
  }
  if (equals({cubic_[3][2][0], cubic_[0][0][0], cubic_[4][0][0]}, {c1, c2, c3})) {
    return {3, 0, 4};
  }
  if (equals({cubic_[4][2][0], cubic_[0][0][2], cubic_[1][0][0]}, {c1, c2, c3})) {
    return {4, 0, 1};
  }

  if (equals({cubic_[1][2][2], cubic_[5][2][0], cubic_[2][0][2]}, {c1, c2, c3})) {
    return {1, 5, 2};
  }
  if (equals({cubic_[2][2][2], cubic_[5][2][2], cubic_[3][0][2]}, {c1, c2, c3})) {
    return {2, 5, 3};
  }
  if (equals({cubic_[3][2][2], cubic_[5][0][2], cubic_[4][0][2]}, {c1, c2, c3})) {
    return {3, 5, 4};
  }
  if (equals({cubic_[4][2][2], cubic_[5][0][0], cubic_[1][0][2]}, {c1, c2, c3})) {
    return {4, 5, 1};
  }
  return {-1, -1, -1};
}

/**
 * Checks if two vectors c1 and c2 contains equal objects
 * @param c1 Vector of chars
 * @param c2 Vector of chars
 * @return If two vectors contains equal objects.
 */
bool CubicWorker::equals(std::vector<char> c1, std::vector<char> c2) {
  if (c1.size() != c2.size()) {
    return false;
  }
  for (auto it = c1.begin(); it != c1.end(); it++) {
    if (std::find(c2.begin(), c2.end(), *it) == c2.end()) {
      return false;
    }
  }
  return true;
}

/**
 * Checks if cube in valid state
 * @return If cube in valid state.
 */
bool CubicWorker::CheckValid() {
  if (!FaceStat()) {
    return false;
  } else {
    auto bad_corner = std::make_tuple(-1, -1, -1);
    auto bad_pair = std::make_pair(-1, -1);

    // Check corners

    if (GetCorner('Y', 'R', 'G') == bad_corner ||
        GetCorner('Y', 'G', 'O') == bad_corner ||
        GetCorner('Y', 'O', 'B') == bad_corner ||
        GetCorner('B', 'Y', 'R') == bad_corner ||
        GetCorner('W', 'O', 'G') == bad_corner ||
        GetCorner('G', 'W', 'R') == bad_corner ||
        GetCorner('R', 'W', 'B') == bad_corner ||
        GetCorner('B', 'W', 'O') == bad_corner) {
      return false;
    }

    // Check middle segments

    if (getCC('O', 'W') == bad_pair ||
        getCC('O', 'G') == bad_pair ||
        getCC('B', 'O') == bad_pair ||
        getCC('O', 'Y') == bad_pair ||
        getCC('G', 'R') == bad_pair ||
        getCC('R', 'B') == bad_pair ||
        getCC('R', 'W') == bad_pair ||
        getCC('R', 'Y') == bad_pair ||
        getCC('B', 'Y') == bad_pair ||
        getCC('Y', 'G') == bad_pair ||
        getCC('W', 'G') == bad_pair ||
        getCC('W', 'B') == bad_pair) {
      return false;
    }

    // Check central parts

    std::set<char> central_seg;
    for (int i = 0; i < 6; i++) {
      central_seg.emplace(cubic_[i][1][1]);
    }
    if (central_seg.size() != 6) {
      return false;
    }

    std::map<char, char> central_colors = {
        {'W', 'Y'},
        {'R', 'O'},
        {'B', 'G'},
        {'Y', 'W'},
        {'O', 'R'},
        {'G', 'B'}
    };

    if ((central_colors[cubic_[1][1][1]] != cubic_[3][1][1]) ||
        (central_colors[cubic_[2][1][1] != cubic_[4][1][1]]) ||
        (central_colors[cubic_[0][1][1]] != cubic_[5][1][1])) {
      return false;
    }

  }
  return true;
}

/**
 * Check if cube is completed.
 * @return
 */
bool CubicWorker::IsCompiled() {
  for (int i = 0; i < 6; i++) {
    char check_col = cubic_[i][0][0];
    for (int y = 0; y < 3; y++) {
      for (int x = 0; x < 3; x++) {
        if (check_col != cubic_[i][x][y]) {
          return false;
        }
      }
    }
  }

  return true;
}










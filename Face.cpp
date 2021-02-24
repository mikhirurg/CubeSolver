//
// Created by @mikhirurg on 05.06.2020.
//

#include "Face.h"

/**
 * Operator[] which gets row of the face
 * @param i Number of the row
 * @return Row i of this face
 */
std::vector<char> &Face::operator[](int i) {
  return cells[i];
}

/**
 * Constructor of the face
 * @param color Color for filling the face
 */
Face::Face(char color)
    : cells() {
  for (int i = 0; i < 3; i++) {
    std::vector<char> tmp;
    for (int j = 0; j < 3; j++) {
      tmp.push_back(color);
    }
    cells.push_back(tmp);
  }
}

//
// Created by @mikhirurg on 05.06.2020.
//

#ifndef UNTITLED8__FACE_H_
#define UNTITLED8__FACE_H_

#include <vector>

/**
 * \brief Cube Face
 * \author @mikhirurg
 * \version 0.1
 * \date 05.06.2020
 * \warning It is a study project
 *
 * This class contains information about colors of parts of Cube's face.
 * Class constructor helps easily fill face with one color.
 */

class Face {
 public:
  Face(char color);
  std::vector<char> &operator[](int i);

 private:
  std::vector<std::vector<char>> cells;
};

#endif //UNTITLED8__FACE_H_

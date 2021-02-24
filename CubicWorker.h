//
// Created by @mikhirurg on 05.06.2020.
//

#ifndef UNTITLED8__CUBICWORKER_H_
#define UNTITLED8__CUBICWORKER_H_

#include <random>
#include <tuple>
#include "Cubic.h"

/**
 * \brief Cube Worker class
 * \author @mikhirurg
 * \version 0.1
 * \date 05.06.2020
 * \warning It is a study project
 *
 * This class contains functions to implement algorithm for solving Rubik's Cube.
 * Also this class contains methods to check cube state and save or load cube to file.
 */

class CubicWorker {
 public:
  explicit CubicWorker(Cubic &cubic);
  Cubic &GetCube();
  void Save(const std::string &fname);
  void Load(const std::string &fname);
  std::vector<std::string> Mix(int t);
  bool CompileCubic();
  bool IsCompiled();
  bool FaceStat();
  bool CheckValid();
  std::pair<int, int> getYB();
  std::pair<int, int> getCC(char c1, char c2);
  std::tuple<int, int, int> GetCorner(char c1, char c2, char c3);

 private:
  Cubic cubic_;
  std::mt19937 gen;
  bool equals(std::vector<char> c1, std::vector<char> c2);
  bool HF(std::tuple<int, int, int> &t, int e);
  bool HF(std::pair<int, int> &p, int e);
  bool UAlign(int a);
  void BuildYellowCross();
  void BuildYellowCorners();
  void BuildMiddleRow();
  void BuildWhiteWrongCross();
  void BuildWhiteRightCross();
  void BuildWhiteCorners();
  void RotateWhiteCorners();
  void BuildWhite();
};

#endif //UNTITLED8__CUBICWORKER_H_

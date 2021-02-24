//
// Created by @mikhirurg on 05.06.2020.
//

#ifndef UNTITLED8__MENU_H_
#define UNTITLED8__MENU_H_

#include <vector>
#include <string>
#include "CubicWorker.h"

/**
 * \brief Menu class
 * \author @mikhirurg
 * \version 0.1
 * \date 05.06.2020
 * \warning It is a study project
 *
 * This class creates menu, with which you can interact with Rubik's cube.
 */
class Menu {
 public:
  Menu(CubicWorker &worker, int argc, char **argv);
  void Start();

 private:
  int argc_;
  char **argv_;
  int checkCommand(const std::string &command, const std::vector<std::pair<std::string, std::string>> &dict);
  void Greeting();
  void UserAssemblyMessage();
  void PrintHelp(const std::vector<std::pair<std::string, std::string>> &command_list);
  std::vector<std::pair<std::string, std::string>> command_list;
  std::vector<std::pair<std::string, std::string>> command_cube_list;
  std::vector<std::pair<std::string, std::string>> command_gl_list;
  CubicWorker worker_;
};

#endif //UNTITLED8__MENU_H_

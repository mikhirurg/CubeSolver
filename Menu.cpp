//
// Created by @mikhirurg on 05.06.2020.
//

#include <iostream>
#include "Menu.h"
#include "ogl_headers.h"
#include "Application.h"
#include "CubicApp.h"

//! Reference to the application
Application *app;

/**
 * This method creates window for Cubec App
 * @param Title of the window
 */
void createWindow(const char *title) {
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
  //glEnable(GLUT_MULTISAMPLE);
  glutInitWindowSize(800, 600);
  glutInitWindowPosition(0, 0);
  glutCreateWindow(title);
}

/**
 * This method updates the application.
 */
void update() {
  app->update();
}

/**
 * This method displays the application.
 */
void display() {
  app->display();
  glFlush();
  glutSwapBuffers();
}

/**
 * This method handles mouse events
 * @param button
 * @param state
 * @param x
 * @param y
 */
void mouse(int button, int state, int x, int y) {
  app->mouse(button, state, x, y);
}

/**
 * This method reshapes the app window
 * @param width New width of the app
 * @param height New height of the app
 */
void reshape(int width, int height) {
  app->resize(width, height);
}

/**
 * This method handles keyboard events
 * @param key
 * @param x
 * @param y
 */
void keyboard(unsigned char key, int x, int y) {
  app->key(key);
}

/**
 * This method handles mouse motion events
 * @param x
 * @param y
 */
void motion(int x, int y) {
  app->mouseDrag(x, y);
}

/**
 * This is constructor for the Menu.
 * @param worker CubicWorker to solve cube.
 * @param argc
 * @param argv
 */
Menu::Menu(CubicWorker &worker, int argc, char **argv)
    : worker_(worker), argc_(argc), argv_(argv) {
  command_list.emplace_back("print", "Prints cube state.");
  command_list.emplace_back("help", "Help for commands.");
  command_list.emplace_back("mix", "Mix cube in a random order.");
  command_list.emplace_back("user_assembly", "User mode for cube solution.");
  command_list.emplace_back("comp_assembly", "Computer tries to solve cube.");
  command_list.emplace_back("change_print", "Switches print mode");
  command_list.emplace_back("gl_mode", "Starting OpenGL interface.");
  command_list.emplace_back("save", "Save cube state in file.");
  command_list.emplace_back("load", "Load cube state into a file.");
  command_list.emplace_back("exit", "Exit app.");

  command_cube_list.emplace_back("u", "Rotate upper face left on 90 deg.");
  command_cube_list.emplace_back("us", "Rotate upper face right on 90 deg.");
  command_cube_list.emplace_back("r", "Rotate right face up on 90 deg.");
  command_cube_list.emplace_back("rs", "Rotate right face down on 90 deg.");
  command_cube_list.emplace_back("l", "Rotate left face down on 90 deg.");
  command_cube_list.emplace_back("ls", "Rotate left face up on 90 deg.");
  command_cube_list.emplace_back("f", "Rotate front face right on 90 deg.");
  command_cube_list.emplace_back("fs", "Rotate front face left on 90 deg.");
  command_cube_list.emplace_back("print", "Print cube state.");
  command_cube_list.emplace_back("help", "Help for commands.");
  command_cube_list.emplace_back("exit", "Exit user console mode.");

  command_gl_list.emplace_back("u", "Rotate upper face left on 90 deg.");
  command_gl_list.emplace_back("SHIFT + u", "Rotate upper face right on 90 deg.");
  command_gl_list.emplace_back("d", "Rotate down face right on 90 deg.");
  command_gl_list.emplace_back("SHIFT + d", "Rotate down face left on 90 deg.");
  command_gl_list.emplace_back("r", "Rotate right face up on 90 deg.");
  command_gl_list.emplace_back("SHIFT + r", "Rotate right face down on 90 deg.");
  command_gl_list.emplace_back("l", "Rotate left face down on 90 deg.");
  command_gl_list.emplace_back("SHIFT + l", "Rotate left face up on 90 deg.");
  command_gl_list.emplace_back("f", "Rotate front face right on 90 deg.");
  command_gl_list.emplace_back("SHIFT + f", "Rotate front face left on 90 deg.");
  command_gl_list.emplace_back("b", "Rotate back face left on 90 deg.");
  command_gl_list.emplace_back("SHIFT + b", "Rotate back face right on 90 deg.");
  command_gl_list.emplace_back("s", "Solve the cube");
  command_gl_list.emplace_back("z", "Mix the cube");
  command_gl_list.emplace_back("q", "Exit GL Mode");
}

/**
 * This method starts command-line app.
 */
void Menu::Start() {
  std::string in;
  Greeting();
  while (true) {
    std::cin >> in;
    switch (checkCommand(in, command_list)) {
      case 0: {
        worker_.GetCube().PrintCube();
      }
        break;
      case 1: {
        PrintHelp(command_list);
      }
        break;
      case 2: {
        std::vector<std::string> rnd = worker_.Mix(50);
        std::cout << "Cube is mixed!" << std::endl;
        std::cout << "(rotations: ";
        for (const std::string& s : rnd) {
          std::cout << s << " ";
        }
        std::cout << ")" << std::endl;
      }
        break;
      case 3: {
        UserAssemblyMessage();
        bool exit = false;
        while (!exit) {
          std::cin >> in;
          switch (checkCommand(in, command_cube_list)) {
            case 0: {
              worker_.GetCube().U();
            }
              break;
            case 1: {
              worker_.GetCube().US();
            }
              break;
            case 2: {
              worker_.GetCube().R();
            }
              break;
            case 3: {
              worker_.GetCube().RS();
            }
              break;
            case 4: {
              worker_.GetCube().L();
            }
              break;
            case 5: {
              worker_.GetCube().LS();
            }
              break;
            case 6: {
              worker_.GetCube().F();
            }
              break;
            case 7: {
              worker_.GetCube().FS();
            }
              break;
            case 8: {
              worker_.GetCube().PrintCube();
            }
              break;
            case 9: {
              PrintHelp(command_cube_list);
            }
              break;
            case 10: {
              exit = true;
            }
              break;
            default: {
              std::cout << "Unknown command!" << std::endl;
            }
          }
        }

        std::cout << "Welcome back to Main menu!" << std::endl;
      }
        break;
      case 4: {
        std::cout << "Let me try to solve this Rubik's Cube :)" << std::endl;
        if (worker_.CompileCubic()) {
          std::cout << "Hurray! We solve this cube!!!" << std::endl;
          std::cout << "Number of moves: " << worker_.GetCube().log.size() << std::endl;
          std::cout << "Win combination: [";
          for (const auto& c : worker_.GetCube().log) {
            std::cout << " " << c;
          }
          std::cout << "]" << std::endl;
        } else {
          std::cout << "Unfortunately, I can't solve this one. I think, it is invalid!." << std::endl;
        }
      }
        break;
      case 5: {
        if (!worker_.GetCube().GetPrintMode()) {
          std::cout << "Print mode is enabled!" << std::endl;
          worker_.GetCube().EnablePrintMode();
        } else {
          std::cout << "Print mode is disabled!" << std::endl;
          worker_.GetCube().DisablePrintMode();
        }
      }
        break;
      case 6: {
        std::cout << "Welcome to OpenGl interface:" << std::endl;
        std::cout
            << "Unfortunately, OpenGl do not allow users interact with console, so here some possible key commands:"
            << std::endl;
        PrintHelp(command_gl_list);
        std::cout.flush();
        glutInit(&argc_, argv_);
        app = new CubicApp(worker_);
        createWindow(app->getTitle());
        glutReshapeFunc(reshape);
        glutKeyboardFunc(keyboard);
        glutDisplayFunc(display);
        glutIdleFunc(update);
        glutMouseFunc(mouse);
        glutMotionFunc(motion);
        app->initGraphics();

        glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
        glutMainLoop();

        app->deinit();
        delete app;

        std::cout << "Welcome back to console mode!" << std::endl;
        std::cout << "Enter \"help\" for information about commands" << std::endl;
      }
        break;
      case 7: {
        std::cout << "Enter file name: " << std::endl;
        std::string fname;
        std::cin >> fname;
        worker_.Save(fname);
      }
        break;
      case 8: {
        std::cout << "Enter file name: " << std::endl;
        std::string fname;
        std::cin >> fname;
        worker_.Load(fname);
      }
        break;
      case 9: {
        exit(0);
      }
      default: {
        std::cout << "Unknown command!" << std::endl;
      }
    }
  }
}

/**
 * This method checks if command is valid.
 * @param command Command to check.
 * @param dict Dictionary with possible commands.
 * @return If command is valid with dictionary dict
 */

int Menu::checkCommand(const std::string &command, const std::vector<std::pair<std::string, std::string>> &dict) {
  for (int i = 0; i < dict.size(); i++) {
    if (dict[i].first == command) {
      return i;
    }
  }
  return -1;
}

/**
 * Prints Greeting message.
 */
void Menu::Greeting() {
  std::cout << "Welcome to Cubic-Rubik app by Mikhail Ushakov M3102!" << std::endl;
  std::cout << "Enter \"help\" for information about commands" << std::endl;
}

/**
 * Prints help from command list c_list.
 * @param c_list Command list.
 */
void Menu::PrintHelp(const std::vector<std::pair<std::string, std::string>> &c_list) {
  std::cout << "Help: " << std::endl;
  for (int i = 0; i < c_list.size(); i++) {
    std::cout << "\"" << c_list[i].first << "\" : " << c_list[i].second << std::endl;
  }
}

/**
 * Prints message to start User Assembly mode.
 */
void Menu::UserAssemblyMessage() {
  std::cout << "Welcome to user assembly mode!" << std::endl;
  std::cout << "Enter \"help\" for information about commands" << std::endl;
}

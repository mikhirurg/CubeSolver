#include <iostream>
#include "CubicApp.h"
#include "ogl_headers.h"

/**
 * Renders cube using OpenGL
 * @param wired
 */
void CubicApp::renderCubic(bool wired) {
  Application::renderText(10, 10, "Cubic!", GLUT_BITMAP_TIMES_ROMAN_10);
  for (int k = 0; k < 6; k++) {
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        if (wired) {
          glColor3f(0.0, 0.0, 0.0);
          glLineWidth(3.0);
        } else {
          switch (cube[k][i][j]) {
            case 'R' :glColor3f(1.0, 0.0, 0.0);
              break;
            case 'G':glColor3f(0.0, 1.0, 0.0);
              break;
            case 'B':glColor3f(0.0, 0.0, 1.0);
              break;
            case 'Y':glColor3f(1.0, 1.0, 0.0);
              break;
            case 'W':glColor3f(1.0, 1.0, 1.0);
              break;
            case 'O':glColor3f(1.0, 0.65, 0.0);
              break;
          }
        }
        glBegin(GL_QUADS);

        switch (k) {
          case 0:glVertex3f(-30.0 + 20 * i, 30.0, -30.0 + 20 * j);
            glVertex3f(-30.0 + 20 * i, 30.0, -10.0 + 20 * j);
            glVertex3f(-10.0 + 20 * i, 30.0, -10.0 + 20 * j);
            glVertex3f(-10.0 + 20 * i, 30.0, -30.0 + 20 * j);
            break;
          case 1:glVertex3f(-30.0 + 20 * i, -30.0 + 20 * (2 - j), 30.0);
            glVertex3f(-10.0 + 20 * i, -30.0 + 20 * (2 - j), 30.0);
            glVertex3f(-10.0 + 20 * i, -10.0 + 20 * (2 - j), 30.0);
            glVertex3f(-30.0 + 20 * i, -10.0 + 20 * (2 - j), 30.0);
            break;
          case 2:glVertex3f(30.0, -30.0 + 20 * (2 - j), -30.0 + 20 * (2 - i));
            glVertex3f(30.0, -10.0 + 20 * (2 - j), -30.0 + 20 * (2 - i));
            glVertex3f(30.0, -10.0 + 20 * (2 - j), -10.0 + 20 * (2 - i));
            glVertex3f(30.0, -30.0 + 20 * (2 - j), -10.0 + 20 * (2 - i));
            break;
          case 3:glVertex3f(-30.0 + 20 * (2 - i), -30.0 + 20 * (2 - j), -30.0);
            glVertex3f(-30.0 + 20 * (2 - i), -10.0 + 20 * (2 - j), -30.0);
            glVertex3f(-10.0 + 20 * (2 - i), -10.0 + 20 * (2 - j), -30.0);
            glVertex3f(-10.0 + 20 * (2 - i), -30.0 + 20 * (2 - j), -30.0);
            break;
          case 4:glVertex3f(-30.0, -30.0 + 20 * (2 - j), -30.0 + 20 * i);
            glVertex3f(-30.0, -30.0 + 20 * (2 - j), -10.0 + 20 * i);
            glVertex3f(-30.0, -10.0 + 20 * (2 - j), -10.0 + 20 * i);
            glVertex3f(-30.0, -10.0 + 20 * (2 - j), -30.0 + 20 * i);
            break;
          case 5:glVertex3f(-30.0 + 20 * i, -30.0, -30.0 + 20 * (2 - j));
            glVertex3f(-10.0 + 20 * i, -30.0, -30.0 + 20 * (2 - j));
            glVertex3f(-10.0 + 20 * i, -30.0, -10.0 + 20 * (2 - j));
            glVertex3f(-30.0 + 20 * i, -30.0, -10.0 + 20 * (2 - j));
            break;
        }
        glEnd();
      }
    }
  }
}

/**
 * This cube displays cube and scene
 */
void CubicApp::display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glColor3f(0.0, 1.0, 0.0);
  glPolygonMode(GL_FRONT, GL_FILL);
  glPolygonMode(GL_BACK, GL_LINE);
  CubicApp::renderCubic(false);
  glColor3f(0.0, 0.0, 0.0);
  glPolygonMode(GL_FRONT, GL_LINE);
  glPolygonMode(GL_BACK, GL_NONE);
  CubicApp::renderCubic(true);
  Application::update();
}

/**
 * Returns title
 * @return Title of the application
 */
const char *CubicApp::getTitle() {
  return "Cubic App";
}

/**
 * Handles key events
 * @param key
 */
void CubicApp::key(unsigned char key) {
  std::vector<std::string> str;
  switch (key) {
    case 'c':std::cout << "IsComplete()=" << worker.GetCube().IsComplete() << std::endl;
      break;
    case 'u':worker.GetCube().U();
      worker.FaceStat();
      break;
    case 'U':worker.GetCube().US();
      worker.FaceStat();
      break;
    case 'r':worker.GetCube().R();
      worker.FaceStat();
      break;
    case 'R':worker.GetCube().RS();
      worker.FaceStat();
      break;
    case 'l':worker.GetCube().L();
      worker.FaceStat();
      break;
    case 'L':worker.GetCube().LS();
      worker.FaceStat();
      break;
    case 'F':worker.GetCube().FS();
      worker.FaceStat();
      break;
    case 'f':worker.GetCube().F();
      worker.FaceStat();
      break;
    case 'd':worker.GetCube().D();
      worker.FaceStat();
      break;
    case 'D':worker.GetCube().DS();
      worker.FaceStat();
      break;
    case 'b':worker.GetCube().B();
      worker.FaceStat();
      break;
    case 'B':worker.GetCube().BS();
      worker.FaceStat();
      break;
    case 'p':worker.GetCube().FlipCube();
      break;
    case 'z':
      str = worker.Mix(10);
      for (const std::string& s : str) {
        std::cout << s << " ";
      }
      std::cout << std::endl;
      break;
    case 's':
      if (worker.CompileCubic()) {
        std::cout << "Hurray! We solve this cube!!!" << std::endl;
        std::cout << "Number of moves: " << worker.GetCube().log.size() << std::endl;
        std::cout << "Win combination: [";
        for (const auto &c : worker.GetCube().log) {
          std::cout << " " << c;
        }
        std::cout << "]" << std::endl;
      } else {
        std::cout << "Unfortunately, I can't solve this one. I think, it is invalid!." << std::endl;
      }
      break;
    case 'q': {
      std::cout << "Bye!" << std::endl;
      glutLeaveMainLoop();
    }
  }

  Application::key(key);
  CubicApp::display();
}

/**
 * Constructor for cube application
 * @param w CubicWorker
 */
CubicApp::CubicApp(CubicWorker &w) : worker(w), cube(w.GetCube()) {

}

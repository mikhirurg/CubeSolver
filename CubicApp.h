#ifndef CUBIC_CUBICAPP_H
#define CUBIC_CUBICAPP_H

#include "Application.h"
#include "CubicWorker.h"

/**
 * \brief Cube application class
 * \author @mikhirurg
 * \version 0.1
 * \date 05.06.2020
 * \warning It is a study project
 *
 * This class is inheriting base Application class. It is allowing to create OpenGL window with cube.
 */

class CubicApp : public Application {
  virtual void display();
  Cubic &cube;
  CubicWorker &worker;

 public:
  const char *getTitle() override;
  virtual void key(unsigned char key) override;
  CubicApp(CubicWorker &w);
  void renderCubic(bool wired);
};

#endif //CUBIC_CUBICAPP_H

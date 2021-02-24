#include <cstdlib>
#ifndef _APPLICATION_H_
#define _APPLICATION_H_

/**
 * \brief Application class
 * \author @mikhirurg
 * \version 0.1
 * \date 05.06.2020
 * \warning It is a study project
 *
 * This class is a base application class, which cah help to create OpenGL window.
 */

class Application {
 protected:
  int height{};
  int width{};
  float r, th, ph;
  int mx{}, my{};
 public:
  Application();
  virtual const char *getTitle() = 0;
  virtual void initGraphics();
  virtual void setView();
  virtual void deinit();
  virtual void display() = 0;
  virtual void update();
  virtual void key(unsigned char key);
  virtual void resize(int width, int nHeight);
  virtual void mouse(int button, int state, int x, int y);
  virtual void mouseDrag(int x, int y);
  void renderText(float x, float y, const char *text, void *font = nullptr) const;
};
#endif

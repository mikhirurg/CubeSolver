#include <cstring>
#include <cmath>
#include "ogl_headers.h"
#include "Application.h"

/**
 * Inits graphics for OpenGL application.
 */
void Application::initGraphics() {
  glClearColor(0.9f, 0.95f, 1.0f, 1.0f);
  glEnable(GL_DEPTH_TEST);
  glShadeModel(GL_SMOOTH);

  setView();
}

/**
 * Sets view in application.
 */
void Application::setView() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, (double) width / (double) height, 1.0, 500.0);
  float ez = r * std::sin(th) * std::cos(ph);
  float ex = r * std::sin(th) * std::sin(ph);
  float ey = r * std::cos(th);
  gluLookAt(ex, ey, ez, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  glMatrixMode(GL_MODELVIEW);
}

/**
 * Deinits application.
 */
void Application::deinit() {
}

/**
 * Updates OpenGL app.
 */
void Application::update() {
  glutPostRedisplay();
}

void Application::key(unsigned char key) {
}

/**
 * Resize application window
 * @param nWidth New width of the window
 * @param nHeight New height of the window
 */
void Application::resize(int nWidth, int nHeight) {
  if (nHeight <= 0) nHeight = 1;
  Application::width = nWidth;
  Application::height = nHeight;
  glViewport(0, 0, nWidth, nHeight);
  setView();
}

/**
 * Updates position of the mouse
 * @param button Mouse clicked button
 * @param state Mouse state
 * @param x X coord of the mouse
 * @param y Y coord of the mouse
 */
void Application::mouse(int button, int state, int x, int y) {
  mx = x;
  my = y;
}

/**
 * Handles mouse drag event
 * This method uses polar coord system to rotate Cube
 * @param x
 * @param y
 */
void Application::mouseDrag(int x, int y) {
  auto dx = float(x - mx);
  float a = (dx / float(width)) * float(M_PI);
  ph -= a;
  if (ph < -M_PI) {
    ph = -M_PI;
  } else if (ph > M_PI) {
    ph = M_PI;
  }

  auto dy = float(y - my);
  float b = -(dy / float(height)) * float(M_PI);
  th += b;

  if (th < 0.01) {
    th = 0.01;
  } else if (th > M_PI) {
    th = M_PI;
  }

  setView();
  mx = x;
  my = y;
}

/**
 * This method draws text on the window with basic OpenGL fonts
 * @param x X coord of the text label
 * @param y Y coord of the text label
 * @param text Text to display on app window
 * @param font Font for label
 */
void Application::renderText(float x, float y, const char *text, void *font) const {
  glDisable(GL_DEPTH_TEST);

  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  glOrtho(0.0, (double) width, 0.0, (double) height, -1.0, 1.0);

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();

  if (font == nullptr) {
    font = GLUT_BITMAP_HELVETICA_10;
  }

  size_t len = strlen(text);

  glRasterPos2f(x, y);
  for (const char *letter = text; letter < text + len; letter++) {
    if (*letter == '\n') {
      y -= 12.0f;
      glRasterPos2f(x, y);
    }
    glutBitmapCharacter(font, *letter);
  }

  glPopMatrix();
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);

  glEnable(GL_DEPTH_TEST);
}

/**
 * Constructor for the application
 */
Application::Application() {
  r = 122;
  ph = 0;
  th = M_PI / 2.0;
}

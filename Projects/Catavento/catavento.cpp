#include <windows.h>  // For MS Windows
#include <vector>
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <GL/freeglut.h>  // GLUT, includes glu.h and gl.h
#include <cmath>
#include "../../rainbow.h"

using namespace std;

const int width = 720, height = 720;
const float frameTime = 1000.0f / 60.0f, v = 12;

int direction = 1, petalsQnt = 4;
float angle = 0, velocity = 5;

struct triangle {
   float a, b, c, edgeSize, R, G, B;
};

void drawPetals();

vector<triangle> blocks;

void scheduleUpdate(int useless) {
   glutTimerFunc((unsigned int) frameTime, scheduleUpdate, 1);

    angle += velocity * direction;

   glutPostRedisplay();
}

void mouseHandler(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON || button == GLUT_RIGHT_BUTTON) {
        direction = button == GLUT_LEFT_BUTTON ? -1 : 1;
    } else if (button == 3) {
        petalsQnt += 1;
    } else if (button == 4) {
        petalsQnt -= petalsQnt > 4 ? 1 : 0;
    }
}

void keyboardHandler(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_UP:
            velocity += 0.5;
            printf("Speed up!\n");
            break;
        case GLUT_KEY_DOWN:
            velocity -= velocity >= 0.5 ? 0.5 : 0;
            printf("Slow down!\n");
            break;
        default:
            break;
    }
}

void drawCircle(float radius) {
    glBegin(GL_LINES);
    for (int i = 0; i < 360; i++)
    {
        glColor3ub(139, 69, 19);
        double x = radius * cos(i);
        double y = radius * sin(i);
        glVertex3f(0, 0, 0);
        glVertex3f((GLfloat) x, (GLfloat) y, 0);
    }
    glEnd();
}

void drawPetals() {
    double spacing = 360.0 / petalsQnt;
    double petalSize = 800.0 / petalsQnt;

    glPushMatrix();
        glTranslated(width / 2.0, height / 2.0, 0);
        glRotated(angle, 0, 0, 1);

        for (int i = 0; i < petalsQnt; i++) {
            glColor3ub(255, 0, 0);
            glBegin(GL_TRIANGLES);
                glVertex2d(0, 0);
                glVertex2d(-petalSize / 2, -200);
                glVertex2d(petalSize / 2, -200);
            glEnd();
            glRotated(spacing, 0, 0, 1);
        }

        drawCircle(20);
    glPopMatrix();
}

void display() {
   glClearColor(51 / 255.0f, 204 / 255.0f, 1, 1.0); // Set background color to black and opaque
   glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer

    glColor3ub(11, 102, 35);
    glRectd(width / 2 - 5, 0, width / 2 + 5, height / 2.0);
    drawPetals();

   glFlush();  // Render now
}

void init() {
  gluOrtho2D(0, width, 0, height);
}

int main(int argc, char** argv) {
   glutInit(&argc, argv);                 // Initialize GLUT
      glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
      glutInitWindowSize(width, height);   // Set the window's initial width & height
      glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
      glutCreateWindow("OpenGL Project - Wave"); // Create a window with the given title
      init();
   glutDisplayFunc(display); // Register display callback handler for window re-paint
   glutMouseFunc(mouseHandler);
   glutSpecialFunc(keyboardHandler);
   glutTimerFunc((unsigned int) frameTime, scheduleUpdate, 1);
   glutMainLoop();           // Enter the infinitely event-processing loop
   return 0;
}

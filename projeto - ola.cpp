#include <windows.h>  // For MS Windows
#include <vector>
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <GL/freeglut.h>  // GLUT, includes glu.h and gl.h
#include "./rainbow.h"

using namespace std;

const int width = 720, height = 480;
const float frameTime = 1000.0f / 60.0f, v = 4.5f;

struct square {
   float x, y, edgeSize, R, G, B;
   int direction = 1;
};

vector<square> blocks;

void drawSquare(float x, float y, float edgeSize, float R, float G, float B) {
   // Draw a Red 1x1 Square centered at origin
   glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
      glColor3f(R, G, B);
      glVertex2f(x, y + edgeSize);
      glVertex2f(x + edgeSize, y + edgeSize);
      glVertex2f(x + edgeSize,  y);
      glVertex2f(x,  y);
   glEnd();
}

square createSquare() {
   square newBlock = square();
   newBlock.x = 0;
   newBlock.y = 0;
   newBlock.edgeSize = 40;
   double color[3] = {};
   srand(time(NULL));
   int index = ((int) blocks.size() * 200 + rand() * 7) % rainbowSize;
   memcpy(color, rainbowArray[index], sizeof(double) * 3);
   newBlock.R = color[0];
   newBlock.G = color[1];
   newBlock.B = color[2];

   return newBlock;
}

void scheduleUpdate(int useless) {
   glutTimerFunc(frameTime, scheduleUpdate, 1);

   for (int i = 0; i < (int) blocks.size(); i++) {
      cout << "x: " << blocks[i].x << ", y: " << blocks[i].y << endl;
      blocks[i].x += v;
      blocks[i].y += v * 1.7f * blocks[i].direction;

      if (blocks[i].x > width) {
         blocks[i].x = 0;
      }

      if (blocks[i].y >= height - blocks[i].edgeSize) {
         blocks[i].direction = -1;
      } else if (blocks[i].y <= 0) {
         blocks[i].direction = 1;
      }

      cout << "   x: " << blocks[i].x << ", y: " << blocks[i].y << endl;
   }

   if ((int) blocks.size() == 0) {
      blocks.push_back(createSquare());
   } else {
      square lastBlock = blocks[(int) blocks.size() - 1];
      if ((int) blocks.size() < 7 && lastBlock.x > lastBlock.edgeSize + 10) {
         blocks.push_back(createSquare());
      }
   }

   glutPostRedisplay();
}

void display() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
   glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer

   for (int i = 0; i < (int) blocks.size(); i++) {
      drawSquare(blocks[i].x, blocks[i].y, blocks[i].edgeSize, blocks[i].R, blocks[i].G, blocks[i].B);
   }
   
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
   glutTimerFunc(frameTime, scheduleUpdate, 1);
   glutMainLoop();           // Enter the infinitely event-processing loop
   return 0;
}

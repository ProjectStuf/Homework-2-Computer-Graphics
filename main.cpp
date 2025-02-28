/*******************************************************
 * Homework 2: OpenGL                                  *
 *-----------------------------------------------------*
 * First, you should fill in problem1(), problem2(),   *
 * and problem3() as instructed in the written part of *
 * the problem set.  Then, express your creativity     *
 * with problem4()!                                    *
 *                                                     *
 * Note: you will only need to add/modify code where   *
 * it says "TODO".                                     *
 *                                                     *
 * The left mouse button rotates, the right mouse      *
 * button zooms, and the keyboard controls which       *
 * problem to display.                                 *
 *                                                     *
 * For Linux/OS X:                                     *
 * Install Make, GCC, OpenGL and freeglut.                              *
 * To compile your program, run "make" in the          *
 * command line.  Typing "make clean" will remove all  *
 * computer-generated files.  Run by typing "./hw2"    *
 *                                                     *
 * For Visual Studio:                                  *
 * You can create a project with this main.cpp, link   *
 * to your OpenGL libs, build and run the executable   *
 * as you normally would.                              *
 *******************************************************/

 #include <cmath>
 #include <cstdio>
 #include <cstdlib>
 #include <iostream>
 
 #include "GL/freeglut.h"
 
 using namespace std;
 
 bool leftDown = false, rightDown = false;
 int lastPos[2];
 float cameraPos[4] = {0, 1, 4, 1};
 int windowWidth = 640, windowHeight = 480;
 double xRot = 0;
 double yRot = 0;
 int curProblem = 1; // TODO: change this number to try different examples
 
 float specular[] = {1.0, 1.0, 1.0, 1.0};
 float shininess[] = {50.0};
 
 void problem1() {
   glPushMatrix();
 
   // Define each teapot position for a rhombus pattern
   float positions[8][2] = {
     {  0.0f,  0.0f  },  // Bottom Teapot
     {  -0.5f,  -0.7f  }, // Bottom-right Teapot
     {  0.0f,  0.0f  },  // Right Teapot
     { -0.5f,  0.7f  }, // Top-right Teapot
     { 0.0f,  0.0f  },  // Top Teapot
     { 0.5f, 0.7f  }, // Top-left Teapot
     {  0.0f, 0.0f  },  // Left Teapot
     {  0.5f, -0.7f  }  // Bottom-left Teapot
   };
 
   for (int i = 0; i < 8; i++) {
     glPushMatrix();
     glTranslatef(positions[i][0], 0, positions[i][1]); // Place teapots in a rhombus
     glRotatef(i * 45.0f, 0, 1, 0); // places the teapots position from the center
     glRotatef(-100.0f, 1.0f, 0.0f, 0.0f); //rotates the teapots to face each other inward, lids facing the center
     glTranslatef(0, -3.2, -0.5); //moves the teapots closer to the center and how far they are from each other
     glutSolidTeapot(0.3); //how big the teapots are
     glPopMatrix();
   }
 
   glPopMatrix();
 }
 
 
 void problem2() {
     glPushMatrix();
     int levels = 25;  // Number of pyramid levels
 
     for (int i = 0; i < levels; i++) {
         glPushMatrix();
 
         // Move each level upwards, reducing the gap to make it more connected
         glTranslatef(0, i * 0.15, 0);  
 
         // Adjust the width and depth to create a proper pyramid shape
         float scaleFactor = 3 - i * 0.12;
         //+ - upside down or upright, 1st value is width, 2nd value is depth
 
         glScalef(scaleFactor, 0.15, scaleFactor);  // Stretching X and Z while keeping a reasonable height
 
         glutSolidCube(1);  // Draw cube as a stretched rectangle
         glPopMatrix();
     }
     glPopMatrix();
 }
 
 void problem3() {
   int rows = 6; // Number of rows of teapots
   float baseHeight = -1.5; // Adjust this value to move the entire triangle on the y-axis
   for (int i = 0; i < rows; i++) {
     for (int j = 0; j <= i; j++) {
       glPushMatrix();
       float xOffset = (j - i / 2.0f) * 0.6f;
       float yOffset = baseHeight + i * 0.6f; 
       // + makes the triangle upside down, - makes it upright, 3rd value smaller = places the teapots closer to each other
       glTranslatef(xOffset, yOffset, 0);
       glutSolidTeapot(0.3);
       glPopMatrix();
     }
   }
 }
 
 // creating Iron Man's Hand Repulsor Hand Cannon
 void problem4() {
     glPushMatrix();
 
     // Draw the palm
     glPushMatrix();
         glScalef(1.0f, 1.2f, 0.3f);
         glutSolidCube(1.0);
     glPopMatrix();
   
 
     // creates fingers
     for (int i = -1; i <= 2; i++) {  // creates 4 fingers
       glRotatef(-10, 1, 0, 0); // rotates the next finger by -10 on the Z axis
         glPushMatrix();
             glTranslatef(i * 0.3, 0.7, 0);  // Position fingers evenly
             glScalef(0.2f, 0.6f, 0.2f);
             glutSolidCube(1.0);
 
             // Nested transformation: Draw the second segment of the finger (joint)
             glPushMatrix();
                 glTranslatef(0, 0.6, 0);
                 glScalef(1.0, 1.2, 1.0);
                 glutSolidCube(1.0);
             glPopMatrix();
         glPopMatrix();
     }
 
     // Draw a thumb
     glPushMatrix();
         glTranslatef(-0.6, 0.3, -0.3); // creates the thumb in the correct positon
         glRotatef(-40, 0, 0, 1);  // Rotate thumb to natural position
         glScalef(0.2, 0.5, 0.2); // scale of the thumb
         glutSolidCube(1.0);
     glPopMatrix();
 
     // Draw a triangle as the "repulsion hand cannon" for Iron Man's glove
   glPushMatrix();
       glTranslatef(0, 0.2, -0.1);  // Position the triangle
       glScalef(3.0f, 6.0f, 1.0f); // Scale up 3x in X and Y (not in Z)
       glRotatef(70, 1.0f, 0.0f, 0.0f); // Rotate 70 degrees around the X-axis
       glRotatef(0, 0.0f, 1.0f, 0.0f); // Rotate 0 degrees around the Y-axis
       glRotatef(0, 0.0f, 0.0f, 1.0f); // Rotate 0 degrees around the Z-axis
 
       glBegin(GL_TRIANGLES);
           glVertex3f(0.0f, 0.1f, 0.0f);
           glVertex3f(-0.1f, -0.1f, 0.0f);
           glVertex3f(0.1f, -0.1f, 0.0f);
       glEnd();
   glPopMatrix();
 
     glPopMatrix();
 }
 
 
 
 void display() {
   glClearColor(0, 0, 0, 0);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
   glDisable(GL_LIGHTING);
   glEnable(GL_DEPTH_TEST);
   glBegin(GL_LINES);
   glColor3f(1, 0, 0);
   glVertex3f(0, 0, 0);
   glVertex3f(1, 0, 0); // x axis
   glColor3f(0, 1, 0);
   glVertex3f(0, 0, 0);
   glVertex3f(0, 1, 0); // y axis
   glColor3f(0, 0, 1);
   glVertex3f(0, 0, 0);
   glVertex3f(0, 0, 1); // z axis
   glEnd(/*GL_LINES*/);
 
   glEnable(GL_LIGHTING);
   glShadeModel(GL_SMOOTH);
   glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
   glEnable(GL_LIGHT0);
 
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glViewport(0, 0, windowWidth, windowHeight);
 
   float ratio = (float)windowWidth / (float)windowHeight;
   gluPerspective(50, ratio, 1, 1000);
 
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt(cameraPos[0], cameraPos[1], cameraPos[2], 0, 0, 0, 0, 1, 0);
 
   glLightfv(GL_LIGHT0, GL_POSITION, cameraPos);
 
   glRotatef(xRot, 1, 0, 0);
   glRotatef(yRot, 0, 1, 0);
 
   if (curProblem == 1)
     problem1();
   if (curProblem == 2)
     problem2();
   if (curProblem == 3)
     problem3();
   if (curProblem == 4)
     problem4();
 
   glutSwapBuffers();
 }
 
 void mouse(int button, int state, int x, int y) {
   if (button == GLUT_LEFT_BUTTON)
     leftDown = (state == GLUT_DOWN);
   else if (button == GLUT_RIGHT_BUTTON)
     rightDown = (state == GLUT_DOWN);
 
   lastPos[0] = x;
   lastPos[1] = y;
 }
 
 void mouseMoved(int x, int y) {
   if (leftDown) {
     xRot += (y - lastPos[1]) * .1;
     yRot += (x - lastPos[0]) * .1;
   }
   if (rightDown) {
     for (int i = 0; i < 3; i++)
       cameraPos[i] *= pow(1.1, (y - lastPos[1]) * .1);
   }
 
   lastPos[0] = x;
   lastPos[1] = y;
   glutPostRedisplay();
 }
 
 void keyboard(unsigned char key, int x, int y) {
   curProblem = key - '0';
   if (key == 'q' || key == 'Q' || key == 27) {
     exit(0);
   }
   glutPostRedisplay();
 }
 
 void reshape(int width, int height) {
   windowWidth = width;
   windowHeight = height;
   glutPostRedisplay();
 }
 
 int main(int argc, char **argv) {
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize(windowWidth, windowHeight);
   glutCreateWindow("HW2");
 
   glutDisplayFunc(display);
   glutMotionFunc(mouseMoved);
   glutMouseFunc(mouse);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
 
   glutMainLoop();
 
   return 0;
 }

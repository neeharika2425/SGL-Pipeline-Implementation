#include <iostream>
#include "sgl.h"
#include<fstream>
#include <cmath>
#include <GL/glut.h>
using namespace std;
int flagl=0;
int flagt=0;
int flagr=0;

#define PI 3.141592653589
#define DEG2RAD(deg) (deg * PI / 180)
// Function Declarations
void drawScene();
void update(int value);
void drawBox(float len);
void drawBall(float rad);
void drawTriangle();
void initRendering();
void handleResize(int w, int h);
void handleKeypress1(unsigned char key, int x, int y);
void handleKeypress2(int key, int x, int y);
void handleMouseclick(int button, int state, int x, int y);

// Global Variables
float ball_x = 1.0f;
float ball_y = 0.0f;
float ball_velx = 0.01f;
float ball_vely = 0.02f;
float ball_rad = 0.2f;
float box_len = 4.0f;
float tri_x = 0.0f;
float tri_y = 0.0f;
float theta = 0.0f; 


int main(int argc, char **argv) {

    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    int w = glutGet(GLUT_SCREEN_WIDTH);
    int h = glutGet(GLUT_SCREEN_HEIGHT);
    int windowWidth = w * 2 / 3;
    int windowHeight = h * 2 / 3;

    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition((w - windowWidth) / 2, (h - windowHeight) / 2);

    glutCreateWindow("CSE251_sampleCode");  // Setup the window
    initRendering();

    // Register callbacks
    glutDisplayFunc(drawScene);
   glutIdleFunc(drawScene);
    glutKeyboardFunc(handleKeypress1);
    glutSpecialFunc(handleKeypress2);
    glutMouseFunc(handleMouseclick);
    glutReshapeFunc(handleResize);
    glutTimerFunc(10, update, 0);
    glutMainLoop();
    return 0;
}
void handleResize(int w, int h)
{
	float m[16];
	glMatrixMode(GL_PROJECTION);
	//glFrustum(0,150,-100,300,-200,300);
//	glGetFloatv(GL_PROJECTION_MATRIX, projectionMatrix);
//	for(int h=0;h<16;h++)
//		printf("o%fo ",projectionMatrix[h]);
//	printf("\n\n");
   sglViewPort(0,0,w,h);
   glLoadIdentity();
   sglModLoadIdentity();
	sglProjOrtho(-15,15,-15,15,-15,15);
   //    sglLookAt(0,0,-100,0,0,-100,0,1,0);
	for(int y=0;y<16;y++)
	{
		m[y]=proj_m[y];			
		printf("p%fp ",mod_view[y]);
		
	}
	glLoadMatrixf(m);
	sglProjFrustum(10,-10,10,-10,10,-10);
	for(int y=0;y<16;y++)
	{
		m[y]=proj_m[y];			
		printf("p%fp ",proj_m[y]);
		
	}
//	glLoadMatrixf(m);
//	glGetFloatv(GL_PROJECTION_MATRIX, projectionMatrix);
//	for(int h=0;h<16;h++)
//		printf("g%fg ",projectionMatrix[h]);
//	printf("\n\n");

// Function to draw objects on the screen
}
void drawScene() {

int y;
GLfloat m[16];
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
  //  glLoadIdentity();
    sglClear(0,0,0);
    drawBox(box_len);
    init();
    sglModLoadIdentity();
    sglViewLoadIdentity();
    sglModPushMatrix();
 if (flagl==1)
sglLookAt(0,1,-10,0,0,0,0,1,0);
 if (flagr==1)
{
    sglViewRotate(30, 0.0f, 0.0f, 1.0f);
}
 if (flagt==1)
{
    sglViewTranslate(3.0f, 0.0f, -5.0f);
}

    // Draw Box
   sglModScale(1.5, 1.5, 1.5);
    sglModTranslate(0.0f, 0.0f, -5.0f);
//glLoadMatrixf(m);
    sglColour3f(1.0f, 0.0f, 0.0f);
    drawTriangle();
   // drawBox(box_len);
    
    // Draw Ball
    sglModPushMatrix();
    sglModTranslate(ball_x, ball_y, 0.0f);
//glLoadMatrixf(m);
    sglColour3f(0.0f, 1.0f, 0.0f);
    //drawBall(ball_rad);
    sglModPopMatrix();
//glLoadMatrixf(m);

    // Draw Triangle
    sglModPushMatrix();
    sglModTranslate(tri_x, tri_y, 0.0f);
//glLoadMatrixf(m);
    sglModRotate(theta, 0.0f, 0.0f, 1.0f);
/*	for(y=0;y<16;y++)
	{
		m[y]=mvmat[y];
	}
glLoadMatrixf(m);*/
//    drawTriangle();
  //  sglModTranslate(tri_x+0.3, tri_y+0.3, 0.0f);
//glLoadMatrixf(m);
//   sglModScale(5, 5, 5);
    drawTriangle();
    sglModPopMatrix();
//glLoadMatrixf(m);

    sglModPopMatrix();
//glLoadMatrixf(m);
      sglShow();
    glutSwapBuffers();
}

// Function to handle all calculations in the scene
// updated evry 10 milliseconds
void update(int value) {
    
    // Handle ball collisions with box
    if(ball_x + ball_rad > box_len/2 || ball_x - ball_rad < -box_len/2)
        ball_velx *= -1;
    if(ball_y + ball_rad > box_len/2 || ball_y - ball_rad < -box_len/2)
        ball_vely *= -1;
    
    // Update position of ball
    ball_x += ball_velx;
    ball_y += ball_vely;

    glutTimerFunc(10, update, 0);
}

void drawBox(float len) {
   
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_QUADS);
    glVertex2f(-len / 2, -len / 2);
    glVertex2f(len / 2, -len / 2);
    glVertex2f(len / 2, len / 2);
    glVertex2f(-len / 2, len / 2);
    glEnd();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void drawBall(float rad) {
    
   glBegin(GL_TRIANGLE_FAN);
   for(int i=0 ; i<360 ; i++) {
       glVertex2f(rad * cos(DEG2RAD(i)), rad * sin(DEG2RAD(i)));
   }
   glEnd();
}

void drawTriangle() {

/*    glBegin(GL_TRIANGLES);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 0.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 0.0f);
    glEnd();*/
sglBegin();


    sglVertex3f(0.0f, 1.0f, 0.0f);
    sglVertex3f(-1.0f, -1.0f, 0.0f);
    sglVertex3f(1.0f, -1.0f, 0.0f);
    sglVertex3f(1.0f, 1.0f, 0.0f);
    sglVertex3f(-1.0f, -1.0f, 0.7f);
    sglVertex3f(1.0f, -1.0f, 0.6f);



sglEnd();
}

// Initializing some openGL 3D rendering options
void initRendering() {

    glEnable(GL_DEPTH_TEST);        // Enable objects to be drawn ahead/behind one another
    glEnable(GL_COLOR_MATERIAL);    // Enable coloring
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);   // Setting a background color
}

// Function called when the window is resized
/*void handleResize(int w, int h) {

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
    gluPerspective(45.0f, (float)w / (float)h, 0.1f, 200.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}*/

void handleKeypress1(unsigned char key, int x, int y) {

    if (key == 27) {
        exit(0);     // escape key is pressed
    }
else if (key == 'l' && flagl==0)
  flagl=1;
 else if (key == 'l' && flagl==1)
  flagl=0;
else if (key == 't' && flagt==0)
  flagt=1;
 else if (key == 't' && flagt==1)
  flagt=0;
else if (key == 'r' && flagr==0)
  flagr=1;
else if (key == 'r' && flagr==1)
  flagr=0;

}

void handleKeypress2(int key, int x, int y) {

    if (key == GLUT_KEY_LEFT)
        tri_x -= 0.1;
    if (key == GLUT_KEY_RIGHT)
        tri_x += 0.1;
    if (key == GLUT_KEY_UP)
        tri_y += 0.1;
    if (key == GLUT_KEY_DOWN)
        tri_y -= 0.1;
}

void handleMouseclick(int button, int state, int x, int y) {

    if (state == GLUT_DOWN)
    {
        if (button == GLUT_LEFT_BUTTON)
            theta += 15;
        else if (button == GLUT_RIGHT_BUTTON)
            theta -= 15;
    }
}

#ifdef WIN32
#include <windows.h>
#endif

#if defined (__APPLE__) || defined(MACOSX)
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
//#include <OpenGL/glu.h>
#include <GLUT/glut.h>

#include "Scene.h"
#include "PixelBuffer.h"

#else //linux
#include <GL/gl.h>
#include <GL/glut.h>
#endif

std::unique_ptr<Scene> scenePtr;

void init();
void display();
void key(unsigned char ch, int x, int y);
void mouse(int button, int state, int x, int y);
void check();
void reshape(size_t width, size_t height);
void idle();
void draw_pix(float x, float y, float r, float g, float b);
void pix_to_norm(float* x, float* y);

size_t screen_width = 200;
size_t screen_height = 200;

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(screen_width, screen_height);
  glutCreateWindow("Project 2");

  /*defined glut callback functions*/
  glutDisplayFunc(display); //rendering calls here
  glutMouseFunc(mouse);     //mouse button events
  glutKeyboardFunc(key);    //Keyboard events
  //glutIdleFunc(idle);       //Function called while program is sitting "idle"

  //initialize opengl variables
  init();

  scenePtr = std::make_unique<Scene>();
  //scenePtr->addSphere(0, 0, 0, 10);
  scenePtr->addSphere(2, 2, 0.5, 0);

  //start glut event loop
  glutMainLoop();

  return 0;
}

/*initialize gl stufff*/
void init()
{
  //set clear color (Default background to white)
  glClearColor(1.0,1.0,1.0,1.0);
  //checks for OpenGL errors
  check();
}

/*Gets called when display size changes, including initial craetion of the display*/
void reshape(size_t width, size_t height) {
  /*set up projection matrix to define the view port*/
  //update the ne window width and height
  screen_width = width;
  screen_height = height;

  //creates a rendering area across the window
  glViewport(0,0,width,height);
  // up an orthogonal projection matrix so that
  // the pixel space is mapped to the grid space
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0,screen_width,0,screen_height,-10,10);

  //clear the modelview matrix
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  //set pixel size relative to the grid cell size
  glPointSize(1);
  //check for opengl errors
  check();
}

//called repeatedly when glut isn't doing anything else
void idle() {
  //redraw the scene over and over again
  glutPostRedisplay();
}

//this is where we writeToBuffer the screen
void display() {
  //clears the screen
  glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
  //clears the opengl Modelview transformation matrix
  glLoadIdentity();

  PixelBuffer pb(screen_width, screen_height);
  pb.fill(1, 1, 1);

  scenePtr->writeToBuffer(pb);
  pb.display();

  //blits the current opengl framebuffer on the screen
  glutSwapBuffers();
  //checks for opengl errors
  check();
}

//gets called when a key is pressed on the keyboard
void key(unsigned char ch, int x, int y)
{
  //redraw the scene after keyboard input
  glutPostRedisplay();
}

//gets called when a mouse button is pressed
void mouse(int button, int state, int x, int y)
{
  if(state !=GLUT_DOWN) {  //button released
  }

  glutPostRedisplay();
}

//checks for any opengl errors in the previous calls and
//outputs if they are present
void check()
{
  GLenum err = glGetError();
  if(err != GL_NO_ERROR)
  {
    printf("GLERROR: There was an error %s\n",gluErrorString(err) );
    exit(1);
  }
}

void pix_to_norm(float* x, float* y) {
  *x = (*x / screen_width - 0.5f) * 2.0f;
  *y = -(*y / screen_width - 0.5f) * 2.0f;
}

/*void draw_pix(float x, float y, float r, float g, float b){
  glBegin(GL_POINTS);
    glColor3f(r, g, b);
    glVertex3f(pix_to_norm(x), pix_to_norm(y), 0);
  glEnd();
}*/
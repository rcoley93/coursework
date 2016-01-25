//Ryan Coley
//rjcoley@ucsc.edu
//asg4
// $Id: graphics.cpp,v 1.11 2014-05-15 16:42:55-07 - - $

#include <iostream>
using namespace std;

#include <GL/freeglut.h>

#include "graphics.h"
#include "util.h"
#include "shape.h"

int window::width = 640; // in pixels
int window::height = 480; // in pixels
GLfloat window::moveChange = 4.0;
int window::borderWidth = 4;
size_t window::selected_obj = 0;
vector<object> window::objects;
mouse window::mus;


//move the selected object
void move_selected_object(int x, int y){
   if(window::objects.size() == 0) return;
   object curr = window::objects.at(window::selected_obj);
   curr.move(x*window::moveChange,y*window::moveChange);
   if(curr.center.xpos > window::width) curr.center.xpos = 0;
   else if(curr.center.xpos < 0) curr.center.xpos = window::width;
   if(curr.center.ypos > window::height) curr.center.ypos = 0;
   else if(curr.center.ypos < 0) curr.center.ypos = window::height;
   
   window::objects.at(window::selected_obj) = curr;
   
   DEBUGF('o',"Current object being moved: " << window::selected_obj);
   DEBUGF('o',"new (x,y): ("<<curr.center.xpos<<","<<curr.center.ypos<<
   ")");
}

//switch to a specific object
void change_object(unsigned int i){
   DEBUGF('o',"Number of obj: " << window::objects.size());
   DEBUGF('o',"Current object: " << window::selected_obj);
   object prev = window::objects.at(window::selected_obj);
   shared_ptr<shape> p_shape = prev.pshape;
   DEBUGF('o',"Old Border Visability Before change: "<<p_shape->border);
   prev.pshape->disableBorder();
   
   DEBUGF('o',"i: " << i);
   
   if(i < window::objects.size()) window::selected_obj = i;
   DEBUGF('o',"Old Border Visability After change: "<<p_shape->border);
   object curr = window::objects.at(window::selected_obj);
   curr.pshape->enableBorder();
   shared_ptr<shape> c_shape = curr.pshape;
   DEBUGF('o',"New Border Visability: "<<c_shape->border);
   
   DEBUGF('o',"Selected object: " << window::selected_obj);
   
}

//switch to the next or prev object
void nextObject(){
   DEBUGF('o',"Number of obj: " << window::objects.size());
   DEBUGF('o',"Current object: " << window::selected_obj);
   
   object curr = window::objects.at(window::selected_obj);
   curr.pshape->disableBorder();
   
   if(window::selected_obj < window::objects.size()-1)
      ++window::selected_obj;
   else window::selected_obj = 0;
   
   curr = window::objects.at(window::selected_obj);
   curr.pshape->enableBorder();
}

//go to the prev selected object
void prevObject(){
   DEBUGF('o',"Number of obj: " << window::objects.size());
   DEBUGF('o',"Current object: " << window::selected_obj);
   
   object curr = window::objects.at(window::selected_obj);
   curr.pshape->disableBorder();
   
   if(window::selected_obj != 0) --window::selected_obj;
   else window::selected_obj = window::objects.size()-1;
   
   curr = window::objects.at(window::selected_obj);
   curr.pshape->enableBorder();
}


// Executed when window system signals to shut down.
void window::close() {
   DEBUGF ('g', sys_info::execname() << ": exit ("
           << sys_info::exit_status() << ")");
   exit (sys_info::exit_status());
}

// Executed when mouse enters or leaves window.
void window::entry (int mouse_entered) {
   DEBUGF ('g', "mouse_entered=" << mouse_entered);
   window::mus.entered = mouse_entered;
   if (window::mus.entered == GLUT_ENTERED) {
      DEBUGF ('g', sys_info::execname() << ": width=" << window::width
           << ", height=" << window::height);
   }
   glutPostRedisplay();
}

// Called to display the objects in the window.
void window::display() {
   glClear (GL_COLOR_BUFFER_BIT);
   for (unsigned int i = 0; i < window::objects.size(); ++i) 
      window::objects.at(i).draw(i);
   mus.draw();
   glutSwapBuffers();
}

// Called when window is opened and when resized.
void window::reshape (int width, int height) {
   DEBUGF ('g', "width=" << width << ", height=" << height);
   window::width = width;
   window::height = height;
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D (0, window::width, 0, window::height);
   glMatrixMode (GL_MODELVIEW);
   glViewport (0, 0, window::width, window::height);
   glClearColor (0.25, 0.25, 0.25, 1.0);
   glutPostRedisplay();
}

// Executed when a regular keyboard key is pressed.
enum {BS=8, TAB=9, ESC=27, SPACE=32, DEL=127};
void window::keyboard (GLubyte key, int x, int y) {
   DEBUGF ('g', "key=" << (unsigned)key << ", x=" << x << ", y=" << y);
   window::mus.set (x, y);
   switch (key) {
      case 'Q': case 'q': case ESC:
         window::close();
         break;
      case 'H': case 'h':
         move_selected_object (-1,0);
         break;
      case 'J': case 'j':
         move_selected_object (0,-1);
         break;
      case 'K': case 'k':
         move_selected_object (0,1);
         break;
      case 'L': case 'l':
         move_selected_object (1,0);
         break;
      case 'N': case 'n': case SPACE: case TAB:
         nextObject();
         break;
      case 'P': case 'p': case BS:
         prevObject();
         break;
      case '0'...'9':
         change_object (key - '0');
         break;
      default:
         cerr << (unsigned)key << ": invalid keystroke" << endl;
         break;
   }
   glutPostRedisplay();
}

// Executed when a special function key is pressed.
void window::special (int key, int x, int y) {
   DEBUGF ('g', "key=" << key << ", x=" << x << ", y=" << y);
   window::mus.set (x, y);
   switch (key) {
      case GLUT_KEY_LEFT:  move_selected_object(-1,0); break;
      case GLUT_KEY_DOWN:  move_selected_object(0,-1); break;
      case GLUT_KEY_UP:    move_selected_object(0,1);  break;
      case GLUT_KEY_RIGHT: move_selected_object(1,0);  break;
      case GLUT_KEY_F1:  change_object (1);  break;
      case GLUT_KEY_F2:  change_object (2);  break;
      case GLUT_KEY_F3:  change_object (3);  break;
      case GLUT_KEY_F4:  change_object (4);  break;
      case GLUT_KEY_F5:  change_object (5);  break;
      case GLUT_KEY_F6:  change_object (6);  break;
      case GLUT_KEY_F7:  change_object (7);  break;
      case GLUT_KEY_F8:  change_object (8);  break;
      case GLUT_KEY_F9:  change_object (9);  break;
      case GLUT_KEY_F10: change_object (10); break;
      case GLUT_KEY_F11: change_object (11); break;
      case GLUT_KEY_F12: change_object (12); break;
      default:
         cerr << (unsigned)key << ": invalid function key" << endl;
         break;
   }
   glutPostRedisplay();
}

void window::motion (int x, int y) {
   DEBUGF ('g', "x=" << x << ", y=" << y);
   window::mus.set (x, y);
   glutPostRedisplay();
}

void window::passivemotion (int x, int y) {
   DEBUGF ('g', "x=" << x << ", y=" << y);
   window::mus.set (x, y);
   glutPostRedisplay();
}

void window::mousefn (int button, int state, int x, int y) {
   DEBUGF ('g', "button=" << button << ", state=" << state
           << ", x=" << x << ", y=" << y);
   window::mus.state (button, state);
   window::mus.set (x, y);
   glutPostRedisplay();
}

void window::main () {
   static int argc = 0;
   object first;
   if(objects.size() > 0) first = objects.at(0);
   first.pshape->enableBorder();
   glutInit (&argc, nullptr);
   glutInitDisplayMode (GLUT_RGBA | GLUT_DOUBLE);
   glutInitWindowSize (window::width, window::height);
   glutInitWindowPosition (128, 128);
   glutCreateWindow (sys_info::execname().c_str());
   glutCloseFunc (window::close);
   glutEntryFunc (window::entry);
   glutDisplayFunc (window::display);
   glutReshapeFunc (window::reshape);
   glutKeyboardFunc (window::keyboard);
   glutSpecialFunc (window::special);
   glutMotionFunc (window::motion);
   glutPassiveMotionFunc (window::passivemotion);
   glutMouseFunc (window::mousefn);
   DEBUGF ('g', "Calling glutMainLoop()");
   glutMainLoop();
}

void mouse::state (int button, int state) {
   switch (button) {
      case GLUT_LEFT_BUTTON: left_state = state; break;
      case GLUT_MIDDLE_BUTTON: middle_state = state; break;
      case GLUT_RIGHT_BUTTON: right_state = state; break;
   }
}

void mouse::draw() {
   static rgbcolor color ("green");
   ostringstream text;
   text << "(" << xpos << "," << window::height - ypos << ")";
   if (left_state == GLUT_DOWN) text << "L"; 
   if (middle_state == GLUT_DOWN) text << "M"; 
   if (right_state == GLUT_DOWN) text << "R"; 
   if (entered == GLUT_ENTERED) {
      void* font = GLUT_BITMAP_HELVETICA_18;
      glColor3ubv (color.ubvec);
      glRasterPos2i (10, 10);
      glutBitmapString (font, (GLubyte*) text.str().c_str());
   }
}


//Ryan Coley
//rjcoley@ucsc.edu
//asg4
// $Id: graphics.h,v 1.9 2014-05-15 16:42:55-07 - - $

#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#include <memory>
#include <vector>
using namespace std;

#include <GL/freeglut.h>

#include "rgbcolor.h"
#include "shape.h"
#include "util.h"

class object {
   public:
      shared_ptr<shape> pshape;
      vertex center;
      rgbcolor color;
   
      // Default copiers, movers, dtor all OK.
      void draw(int i) { pshape->draw (center, color, i); }
      void move (float delta_x, float delta_y) {
         vertex newCenter;
         newCenter.xpos = center.xpos+delta_x;
         newCenter.ypos = center.ypos+delta_y;
         center = newCenter;
      }
};

class mouse {
      friend class window;
   private:
      int xpos {0};
      int ypos {0};
      int entered {GLUT_LEFT};
      int left_state {GLUT_UP};
      int middle_state {GLUT_UP};
      int right_state {GLUT_UP};
   private:
      void set (int x, int y) { xpos = x; ypos = y; }
      void state (int button, int state);
      void draw();
};

class window {
      friend class mouse;
      friend void nextObject();
      friend void prevObject();
      friend void change_object(unsigned int i);
      friend void move_selected_object(int x, int y);
   private:
      static int width;         // in pixels
      static int height;        // in pixels
      static vector<object> objects;
      static size_t selected_obj;
      static GLfloat moveChange;
      static int borderWidth;
      static mouse mus;
   private:
      static void close();
      static void entry (int mouse_entered);
      static void display();
      static void reshape (int width, int height);
      static void keyboard (GLubyte key, int, int);
      static void special (int key, int, int);
      static void motion (int x, int y);
      static void passivemotion (int x, int y);
      static void mousefn (int button, int state, int x, int y);
   public:
      static void setBorder(int border, rgbcolor color){
         borderWidth = border;
         borderLineColor = color;
      }
      static int getBorderWidth () {return borderWidth;}
      static rgbcolor getBorderColor() {return borderLineColor;}
      static void setMoveby(GLfloat change) { moveChange = change;}
      static void push_back (const object& obj) {
                  objects.push_back (obj); }
      static void setwidth (int width_) { width = width_; }
      static void setheight (int height_) { height = height_; }
      static void main();
};

#endif


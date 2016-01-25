//Ryan Coley
//rjcoley@ucsc.edu
//asg4
// $Id: shape.cpp,v 1.7 2014-05-08 18:32:56-07 - - $

#include <typeinfo>
#include <unordered_map>
#include <cmath>
using namespace std;

#include "shape.h"
#include "util.h"
#include "graphics.h"
rgbcolor color("red");
rgbcolor borderLineColor = color;

static unordered_map<void*,string> fontname {
   {GLUT_BITMAP_8_BY_13       , "Fixed-8x13"    },
   {GLUT_BITMAP_9_BY_15       , "Fixed-9x15"    },
   {GLUT_BITMAP_HELVETICA_10  , "Helvetica-10"  },
   {GLUT_BITMAP_HELVETICA_12  , "Helvetica-12"  },
   {GLUT_BITMAP_HELVETICA_18  , "Helvetica-18"  },
   {GLUT_BITMAP_TIMES_ROMAN_10, "Times-Roman-10"},
   {GLUT_BITMAP_TIMES_ROMAN_24, "Times-Roman-24"},
};

static unordered_map<string,void*> fontcode {
   {"Fixed-8x13"    , GLUT_BITMAP_8_BY_13       },
   {"Fixed-9x15"    , GLUT_BITMAP_9_BY_15       },
   {"Helvetica-10"  , GLUT_BITMAP_HELVETICA_10  },
   {"Helvetica-12"  , GLUT_BITMAP_HELVETICA_12  },
   {"Helvetica-18"  , GLUT_BITMAP_HELVETICA_18  },
   {"Times-Roman-10", GLUT_BITMAP_TIMES_ROMAN_10},
   {"Times-Roman-24", GLUT_BITMAP_TIMES_ROMAN_24},
};

ostream& operator<< (ostream& out, const vertex& where) {
   out << "(" << where.xpos << "," << where.ypos << ")";
   return out;
}

shape::shape() {
   DEBUGF ('c', this);
}

void* getFont(string str){
   auto font = fontcode.find(str);
   if(font == fontcode.end()) throw runtime_error("syntax error");
   return font->second;
}

text::text (string glut_bitmap_font, const string& textdata):
      glut_bitmap_font(getFont(glut_bitmap_font)), textdata(textdata) {
   DEBUGF ('c', this);
}

ellipse::ellipse (GLfloat width, GLfloat height):
dimension ({width, height}) {
   DEBUGF ('c', this);
}

circle::circle (GLfloat diameter): ellipse (diameter, diameter) {
   DEBUGF ('c', this);
}

vertex_list avgPolygon(vertex_list vl){
   //get the average
   GLfloat xAvg = 0, yAvg = 0;
   vertex_list v;
   
   for(auto i : vl){
      DEBUGF('o',"cur pos: "<<i.xpos<<" "<<i.ypos);
      xAvg += i.xpos;
      yAvg += i.ypos;
      DEBUGF('o',"Curr AVG: "<<xAvg<<" "<<yAvg);
   }
   xAvg /= vl.size();
   yAvg /= vl.size();
   
   DEBUGF('o',"AVG: "<<xAvg<<" "<<yAvg);
   
   for(auto i: vl){
      vertex vx;
      vx.xpos = i.xpos - xAvg;
      vx.ypos = i.ypos - yAvg;
      v.push_back(vx);
   }
   
   for(auto i:v){
      DEBUGF('o',"new pos: "<<i.xpos<<" "<<i.ypos);
   }
   
   return v;
}

polygon::polygon (const vertex_list& vertices) : vertices(
                                                avgPolygon(vertices)) {
   DEBUGF ('c', this);
}

vertex_list makeRect(GLfloat w, GLfloat h){
   //define variables
   vertex a,b,c,d;
   vertex_list v;
   
   //lower left corner
   a.xpos = 0;
   a.ypos = 0;
   v.push_back(a);
   
   //lower right corner
   b.xpos = w;
   b.ypos = 0;
   v.push_back(b);
   
   //upper left corner
   c.xpos = w;
   c.ypos = h;
   v.push_back(c);
   
   //upper right corner
   d.xpos = 0;
   d.ypos = h;
   v.push_back(d);

   return v;
}

rectangle::rectangle (GLfloat width, GLfloat height):
            polygon(makeRect(width,height)) {
   DEBUGF ('c', this << "(" << width << "," << height << ")");
}

square::square (GLfloat width): rectangle (width, width) {
   DEBUGF ('c', this);
}

vertex_list makeTriangle (GLfloat x0, GLfloat y0, GLfloat x1,
                          GLfloat y1, GLfloat x2, GLfloat y2){
   //define the vertex lists
   vertex_list v;
   vertex a,b,c;
   
   //define the new vertices
   a.xpos = x0;
   a.ypos = y0;
   b.xpos = x1;
   b.ypos = y1;
   c.xpos = x2;
   c.ypos = y2;
   
   //add them
   v.push_back(a);
   v.push_back(b);
   v.push_back(c);
     
   return v;
}

triangle::triangle (GLfloat x0, GLfloat y0, GLfloat x1, GLfloat y1, 
                    GLfloat x2, GLfloat y2) : 
                    polygon(makeTriangle(x0,y0,x1,y1,x2,y2)){
   DEBUGF ('c', this);
}

right_triangle::right_triangle(GLfloat width,GLfloat height) :
                               triangle(0,0,width,0,0,height) {
   DEBUGF ('c', this);
}

isosceles::isosceles (GLfloat width, GLfloat height) :
                      triangle(0,0,width,0,width/2,height) {
   DEBUGF ('c', this);
}

equilateral::equilateral (GLfloat width) : 
                          triangle(0,0,width,0,width/2,width) {
   DEBUGF ('c', this);
}

vertex_list makeDiamond(GLfloat w, GLfloat h){
   //define variables
   vertex a,b,c,d;
   vertex_list v;
   
   //left corner
   a.xpos = 0;
   a.ypos = 0;
   v.push_back(a);
   
   //top corner
   b.xpos = w/2;
   b.ypos = h/2;
   v.push_back(b);
   
   //right corner
   c.xpos = w;
   c.ypos = 0;
   v.push_back(c);
   
   //bottom corner
   d.xpos = w/2;
   d.ypos = -h/2;
   v.push_back(d);
   
   //get the average
   GLfloat xAvg = 0, yAvg = 0;
   
   for(auto i : v){
      xAvg += i.xpos;
      yAvg += i.ypos;
   }
   xAvg /= v.size();
   yAvg /= v.size();
   
   for(auto i : v){
      i.xpos -= xAvg;
      i.ypos -= yAvg;
   }
   
   return v;
}

diamond::diamond (GLfloat width, GLfloat height):
                 polygon(makeDiamond(width,height)) {
   DEBUGF ('c', this << "(" << width << "," << height << ")");
}  

void text::draw (const vertex& center, const rgbcolor& color, int i) 
const {
   (void) i;
   DEBUGF ('d', this << "(" << center << "," << color << ")");
   auto text = reinterpret_cast<const GLubyte*> (textdata.c_str());
   size_t width = glutBitmapLength (glut_bitmap_font, text);
   size_t height = glutBitmapHeight (glut_bitmap_font);
   glColor3ub (color.red,color.green,color.blue);
   glRasterPos2f (center.xpos+(width/2),center.ypos+(height/2));
   glutBitmapString (glut_bitmap_font, text);
   
   if(border){
      //set the type of shape
      glLineWidth(window::getBorderWidth());
      glBegin(GL_LINES);
      glEnable(GL_LINE_SMOOTH);
      
      //set the parameters for the border
      DEBUGF('o',"Line width: "<<window::getBorderWidth());
      rgbcolor b_color = borderLineColor;
      glColor3ub(b_color.red,b_color.green,b_color.blue);
      glutSwapBuffers();
      
      //make the outline
      
      //left line
      glVertex2f(center.xpos+(width/2),center.ypos+(height/2)-1);
      glVertex2f(center.xpos+(width/2),center.ypos+height+(height/2));
      
      //top line
      glVertex2f(center.xpos+(width/2),center.ypos+height+(height/2));
      glVertex2f(center.xpos+width+(width/2)
                ,center.ypos+height+(height/2));
      
      //right line
      glVertex2f(center.xpos+width+(width/2)
                ,center.ypos+height+(height/2));
      glVertex2f(center.xpos+width+(width/2),center.ypos+(height/2)-1);
      
      //bottom line
      glVertex2f(center.xpos+width+(width/2),center.ypos+(height/2)-1);
      glVertex2f(center.xpos+(width/2),center.ypos+(height/2)-1);
      
      //done with the shape
      glEnd();
   }
   glFlush();
}

void ellipse::draw (const vertex& center, const rgbcolor& color, int i) 
const {
   DEBUGF ('d', this << "(" << center << "," << color << ")");
   glBegin (GL_POLYGON);
   glEnable (GL_LINE_SMOOTH);
   glColor3ub (color.red,color.green,color.blue);
   const float delta = 2 * M_PI / 128;
   float width = dimension.xpos;
   float height = dimension.ypos;
   for (float theta = 0; theta < 2 * M_PI; theta += delta) {
      float xpos = width * cos (theta) + center.xpos;
      float ypos = height * sin (theta) + center.ypos;
      glVertex2f (xpos, ypos);
   }
   glEnd();
   
   if(border){
      //set the type of shape
      glLineWidth(window::getBorderWidth());
      glBegin(GL_LINES);
      glEnable(GL_LINE_SMOOTH);
      
      //set the parameters for the border
      DEBUGF('o',"Line width: "<<window::getBorderWidth());
      rgbcolor b_color = borderLineColor;
      glColor3ub(b_color.red,b_color.green,b_color.blue);
      
      //make the outline
      const float delta = 2 * M_PI / 128;
      float width = dimension.xpos;
      float height = dimension.ypos;
      for (float theta = 0; theta < 2 * M_PI; theta += delta) {
         float xpos = width * cos (theta) + center.xpos;
         float ypos = height * sin (theta) + center.ypos;
         float xpos2 = width * cos (theta+delta) + center.xpos;
         float ypos2 = height * sin (theta+delta) + center.ypos;
         glVertex2f (xpos, ypos);
         glVertex2f (xpos2, ypos2);
      }
      
      //done with the shape
      glEnd();
   }
   
   //set object label
   if(i<=9){
      //convert the number
      string strNumber = to_string(i);
      auto text = reinterpret_cast<const GLubyte*> (strNumber.c_str());
      
      //center the text
      size_t width = glutBitmapLength (GLUT_BITMAP_HELVETICA_12, text);
      size_t height = glutBitmapHeight (GLUT_BITMAP_HELVETICA_12);
      glColor3ub (0xff,0xff,0xff);
      glRasterPos2f (center.xpos-(width/2), center.ypos-(height/2));
      
      //display text
      glutBitmapString (GLUT_BITMAP_HELVETICA_12, text);
   }
   glFlush();
}

void polygon::draw (const vertex& center, const rgbcolor& color, int i) 
const {
   DEBUGF ('d', this << "(" << center << "," << color << ")");
   
   //start the polygon
   glBegin (GL_POLYGON);
   glColor3ub (color.red, color.green, color.blue);
   
   //make all the lines
   for(auto i : vertices){
      glVertex2f(i.xpos+center.xpos, i.ypos+center.ypos);
   }
   
   glEnd();
   
   if(border){
      //set the type of shape
      glLineWidth(window::getBorderWidth());
      glBegin(GL_LINES);
      
      //set the parameters for the border
      DEBUGF('o',"Line width: "<<window::getBorderWidth());
      rgbcolor b_color = borderLineColor;
      glColor3ub(b_color.red,b_color.green,b_color.blue);
      
      //make the outline
      for(unsigned int i = 0; i<vertices.size(); ++i){
         float x_begin = vertices.at(i).xpos+center.xpos;
         float y_begin = vertices.at(i).ypos+center.ypos;
         float x_end,y_end;
         if(i != vertices.size()-1) {
            x_end = vertices.at(i+1).xpos+center.xpos;
            y_end = vertices.at(i+1).ypos+center.ypos;
         }else{
            x_end = vertices.at(0).xpos+center.xpos;
            y_end = vertices.at(0).ypos+center.ypos;
         }
         glVertex2f(x_begin, y_begin);
         glVertex2f(x_end, y_end);
      }
      
      //done with the shape
      glEnd();
   }
   
   
   
   //set object label
   if(i<=9){
      //convert the number
      string strNumber = to_string(i);
      auto text = reinterpret_cast<const GLubyte*> (strNumber.c_str());
      
      //center the text
      size_t width = glutBitmapLength (GLUT_BITMAP_HELVETICA_12, text);
      size_t height = glutBitmapHeight (GLUT_BITMAP_HELVETICA_12);
      glColor3ub (0xff,0xff,0xff);
      glRasterPos2f (center.xpos-(width/2), center.ypos-(height/2));
      
      //display text
      glutBitmapString (GLUT_BITMAP_HELVETICA_12, text);
   }
   
   glFlush();
}

void shape::show (ostream& out) const {
   out << this << "->" << demangle (*this) << ": ";
}

void text::show (ostream& out) const {
   shape::show (out);
   out << glut_bitmap_font << "(" << fontname[glut_bitmap_font]
       << ") \"" << textdata << "\"";
}

void ellipse::show (ostream& out) const {
   shape::show (out);
   out << "{" << dimension << "}";
}

void polygon::show (ostream& out) const {
   shape::show (out);
   out << "{" << vertices << "}";
}

void shape::enableBorder(){ border = true; }
void shape::disableBorder(){ border = false; }

void polygon::enableBorder(){ border = true; }
void polygon::disableBorder(){ border = false; }

void text::enableBorder(){ border = true; }
void text::disableBorder(){ border = false; }

void ellipse::enableBorder(){ border = true; }
void ellipse::disableBorder(){ border = false; }

ostream& operator<< (ostream& out, const shape& obj) {
   obj.show (out);
   return out;
}


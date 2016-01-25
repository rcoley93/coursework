//Ryan Coley
//rjcoley@ucsc.edu
//asg4
// $Id: interp.cpp,v 1.18 2015-02-19 16:50:37-08 - - $

#include <memory>
#include <string>
#include <vector>
using namespace std;
using parameters = vector<string>;
using param = parameters::const_iterator;

#include <GL/freeglut.h>

#include "debug.h"
#include "interp.h"
#include "shape.h"
#include "util.h"

unordered_map<string,interpreter::interpreterfn>
interpreter::interp_map {
   {"define" , &interpreter::do_define },
   {"draw"   , &interpreter::do_draw   },
   {"moveby" , &interpreter::do_move   },
   {"border" , &interpreter::do_border },
};

unordered_map<string,interpreter::factoryfn>
interpreter::factory_map {
   {"text"           , &interpreter::make_text           },
   {"ellipse"        , &interpreter::make_ellipse        },
   {"circle"         , &interpreter::make_circle         },
   {"polygon"        , &interpreter::make_polygon        },
   {"rectangle"      , &interpreter::make_rectangle      },
   {"square"         , &interpreter::make_square         },
   {"triangle"       , &interpreter::make_triangle       },
   {"right_triangle" , &interpreter::make_right_triangle },
   {"isosceles"      , &interpreter::make_isosceles      },
   {"equilateral"    , &interpreter::make_equilateral    },
   {"diamond"        , &interpreter::make_diamond        },
};

interpreter::shape_map interpreter::objmap;

interpreter::~interpreter() {
   for (const auto& itor: objmap) {
      cout << "objmap[" << itor.first << "] = "
           << *itor.second << endl;
   }
}

void interpreter::interpret (const parameters& params) {
   DEBUGF ('i', params);
   param begin = params.cbegin();
   string command = *begin;
   auto itor = interp_map.find (command);
   if (itor == interp_map.end()) 
         throw runtime_error ("Command not found!");
   interpreterfn func = itor->second;
   func (++begin, params.cend());
}

void interpreter::do_define (param begin, param end) {
   DEBUGF ('f', range (begin, end));
   string name = *begin;
   objmap.emplace (name, make_shape (++begin, end));
}

void interpreter::do_draw (param begin, param end) {
   DEBUGF('f',"entering do_draw");
   DEBUGF ('f', range (begin, end));
   
   //syntax error
   if (end - begin != 4) throw runtime_error ("Not Correct Arguments");
   DEBUGF('f',"no syntax errors");
   
   //name of the shape
   string name = begin[1];
   DEBUGF('f',"name: "<<name);
   
   //finding the object that the name refers to
   DEBUGF('f',"finding: "<<name);
   shape_map::const_iterator itor = objmap.find (name);
   if (itor == objmap.end()) {
      DEBUGF('f',"couldn't find: "<<name);
      throw runtime_error (name + ": no such shape");
   }
   DEBUGF('f',"found: "<<name);
   
   //placing coordinates
   DEBUGF('f',"creating vertex");
   vertex where {from_string<GLfloat> (begin[2]),
                 from_string<GLfloat> (begin[3])};
   DEBUGF('f',"where = ("<<where.xpos<<","<<where.ypos<<")");
   
   //getting color
   rgbcolor color {begin[0]};
   DEBUGF('f',"color: "<<color);
   
   //creating new object
   object newShape;
   newShape.pshape = itor->second;
   newShape.color = color;
   newShape.center = where;
   
   //drawing shape
   DEBUGF('f',"drawing");
   window::push_back(newShape);
   //itor->second->draw (where, color);
}


void interpreter::do_move (param begin, param end) {
   DEBUGF ('f', range (begin, end));
   window::setMoveby(stoi(*begin));
}

void interpreter::do_border (param begin, param end) {
   DEBUGF ('f', range (begin, end));
   if(begin == end || begin+1 == end) {
      throw runtime_error(
         "Error: Border color and width are incorrectly defined!"
      );
   }
   rgbcolor color (begin[0]);
   window::setBorder(stoi(begin[1]),color);
}

shape_ptr interpreter::make_shape (param begin, param end) {
   DEBUGF ('f', range (begin, end));
   string type = *begin++;
   auto itor = factory_map.find(type);
   if (itor == factory_map.end()) {
      throw runtime_error (type + ": no such shape");
   }
   factoryfn func = itor->second;
   return func (begin, end);
}

shape_ptr interpreter::make_text (param begin, param end) {
   DEBUGF ('f', range (begin, end));
   string strData = "";
   for(auto itor = begin+1;itor!=end;++itor){
      strData+=*itor+" ";
   }
   strData += "\b";
   return make_shared<text> (*begin, strData);
}

vector<GLfloat> getParam(param begin, param end){
   vector<GLfloat> params;
   for(auto itor = begin;itor != end;++itor){
      params.push_back(stof(*itor));
   }
   return params;
}

shape_ptr interpreter::make_ellipse (param begin, param end) {
   DEBUGF ('f', range (begin, end));
   vector<GLfloat> points = getParam(begin,end);
   if(points.size() != 2) {
      throw runtime_error(
         "Error: Ellipse height and width are incorrectly defined!"
      );
   }
   return make_shared<ellipse> (points.at(0), points.at(1));
}

shape_ptr interpreter::make_circle (param begin, param end) {
   DEBUGF ('f', range (begin, end));
   vector<GLfloat> points = getParam(begin,end);
   if(points.size() != 1) {
      throw runtime_error(
         "Error: Circle radius is incorrectly defined!"
      );
   }
   return make_shared<circle> (points.at(0));
}

shape_ptr interpreter::make_polygon (param begin, param end) {
   DEBUGF ('f', range (begin, end));
   vector<GLfloat> points = getParam(begin,end);
   vertex_list v;
   if(points.size() % 2 != 0 && points.size() < 6) {
      throw runtime_error(
         "Error: Polygon vertices are incorrectly defined!"
      );
   }
   for(unsigned int i = 0;i<points.size();i+=2){
      vertex a;
      a.xpos = points.at(i);
      a.ypos = points.at(i+1);
      v.push_back(a);
   }
   return make_shared<polygon> (v);
}

shape_ptr interpreter::make_rectangle (param begin, param end) {
   DEBUGF ('f', range (begin, end));
   vector<GLfloat> points = getParam(begin,end);
   if(points.size() != 2) {
      throw runtime_error(
         "Error: Rectangle height and width are incorrectly defined!"
      );
   }
   return make_shared<rectangle> (points.at(0), points.at(1));
}

shape_ptr interpreter::make_square (param begin, param end) {
   DEBUGF ('f', range (begin, end));
   vector<GLfloat> points = getParam(begin,end);
   if(points.size() != 1) {
      throw runtime_error(
         "Error: Square width is incorrectly defined!"
      );
   }
   return make_shared<square> (points.at(0));
}

shape_ptr interpreter::make_triangle (param begin, param end) {
   DEBUGF ('f', range (begin, end));
   vector<GLfloat> points = getParam(begin,end);
   if(points.size() != 6) {
      throw runtime_error(
         "Error: Triangle vertices are incorrectly defined!"
      );
   }
   return make_shared<triangle> (points.at(0),points.at(1),
                                 points.at(2),points.at(3),
                                 points.at(4),points.at(5));
}

shape_ptr interpreter::make_right_triangle (param begin, param end) {
   DEBUGF ('f', range (begin, end));
   vector<GLfloat> points = getParam(begin,end);
   if(points.size() != 2) {
      throw runtime_error(
      "Error: Right triangle height and width are incorrectly defined!"
      );
   }
   return make_shared<right_triangle> (points.at(0),points.at(1));
}

shape_ptr interpreter::make_isosceles (param begin, param end) {
   DEBUGF ('f', range (begin, end));
   vector<GLfloat> points = getParam(begin,end);
   if(points.size() != 2) {
      throw runtime_error(
         "Error: Isosceles height and width are incorrectly defined!"
      );
   }
   return make_shared<isosceles> (points.at(0),points.at(1));
}

shape_ptr interpreter::make_equilateral (param begin, param end) {
   DEBUGF ('f', range (begin, end));
   vector<GLfloat> points = getParam(begin,end);
   if(points.size() != 1) {
      throw runtime_error(
         "Error: Equilateral width is incorrectly defined!"
      );
   }
   return make_shared<equilateral> (points.at(0));
}

shape_ptr interpreter::make_diamond (param begin, param end) {
   DEBUGF ('f', range (begin, end));
   vector<GLfloat> points = getParam(begin,end);
   if(points.size() != 2) {
      throw runtime_error(
         "Error: Diamond height and width are incorrectly defined!"
      );
   }
   return make_shared<diamond> (points.at(0),points.at(1));
}

//Ryan Coley
//rjcoley@ucsc.edu
//asg3
// $Id: listmap.tcc,v 1.7 2015-04-28 19:22:02-07 - - $

#include "listmap.h"
#include "trace.h"

//
/////////////////////////////////////////////////////////////////
// Operations on listmap::node.
/////////////////////////////////////////////////////////////////
//

//
// listmap::node::node (link*, link*, const value_type&)
//
template <typename Key, typename Value, class Less>
listmap<Key,Value,Less>::node::node (node* next, node* prev,
                                     const value_type& value):
            link (next, prev), value (value) {
}

//
/////////////////////////////////////////////////////////////////
// Operations on listmap.
/////////////////////////////////////////////////////////////////
//

//
// listmap::~listmap()
//
template <typename Key, typename Value, class Less>
listmap<Key,Value,Less>::~listmap() {
   TRACE ('l', (void*) this);
   while(!(this->empty())){
      this->erase(this->begin());
   }
}

//
// iterator listmap::insert (const value_type&)
//
template <typename Key, typename Value, class Less>
typename listmap<Key,Value,Less>::iterator
listmap<Key,Value,Less>::insert (const value_type& pair) {
   TRACE ('l', &pair << "->" << pair);
   //the list is empty
   if(this->empty()){
      node* nodeNew = new node(anchor(),anchor(),pair);
      anchor()->next = nodeNew;
      anchor()->prev = nodeNew;
      return iterator(nodeNew);
   }else{
      node* nodeCurrent = anchor()->next;
      while(nodeCurrent != NULL){
         //if it comes before the first node
         if(less(pair.first,nodeCurrent->value.first)
                                    && nodeCurrent->prev == anchor()){
            node* nodeNew = new node(nodeCurrent,anchor(),pair);
            anchor()->next = nodeNew;
            nodeCurrent->prev = nodeNew;
            return iterator(nodeNew);
         //if it comes after the last node
         }else if(less(nodeCurrent->value.first,pair.first) 
                                    && nodeCurrent->next == anchor()){
            node* nodeNew = new node(anchor(),nodeCurrent,pair);
            nodeCurrent->next = nodeNew;
            anchor()->prev = nodeNew;
            return iterator(nodeNew);
         //if it comes between two node
         }else{
            node* nodeAfter = nodeCurrent->next;
            
            value_type nodeCurrentValue = nodeCurrent->value;
            value_type nodeAfterValue = nodeAfter->value;
            
            if(less(nodeCurrentValue.first,pair.first) 
                           && less(pair.first,nodeAfterValue.first)){
               node* nodeNew = new node(nodeAfter,nodeCurrent,pair);
               nodeAfter->prev = nodeNew;
               nodeCurrent->next = nodeNew;
               
               return iterator(nodeNew);
            }
         }
         nodeCurrent = nodeCurrent->next;
      }
   }
   
   //if error return the end
   return iterator(anchor());
}

//
// listmap::find(const key_type&)
//
template <typename Key, typename Value, class Less>
typename listmap<Key,Value,Less>::iterator
listmap<Key,Value,Less>::find (const key_type& that) {
   if (this->empty()) return iterator(anchor());
   node* nodeCurrent = anchor()->next;
   while(nodeCurrent->next != NULL){
      if(nodeCurrent->value.first == that){
         return iterator(nodeCurrent);
      }
      else{
         if(nodeCurrent->next != anchor()) 
            nodeCurrent = nodeCurrent->next;
         else break;
      }
   }
   return iterator(anchor());
}

//
// iterator listmap::erase (iterator position)
//
template <typename Key, typename Value, class Less>
typename listmap<Key,Value,Less>::iterator
listmap<Key,Value,Less>::erase (iterator position) {
   TRACE ('l', &*position);
   if(this->empty()) return iterator(anchor());
   node* nodeDelete = position.where;
   node* nodeBefore = nodeDelete->prev;
   node* nodeAfter = nodeDelete->next;
   
   nodeAfter->prev = nodeBefore;
   nodeBefore->next =nodeAfter;
   
   delete nodeDelete;
   
   return iterator(nodeAfter);
}

//
/////////////////////////////////////////////////////////////////
// Operations on listmap::iterator.
/////////////////////////////////////////////////////////////////
//

//
// listmap::value_type& listmap::iterator::operator*()
//
template <typename Key, typename Value, class Less>
typename listmap<Key,Value,Less>::value_type&
listmap<Key,Value,Less>::iterator::operator*() {
   TRACE ('l', where);
   return where->value;
}

//
// listmap::value_type* listmap::iterator::operator->()
//
template <typename Key, typename Value, class Less>
typename listmap<Key,Value,Less>::value_type*
listmap<Key,Value,Less>::iterator::operator->() {
   TRACE ('l', where);
   return &(where->value);
}

//
// listmap::iterator& listmap::iterator::operator++()
//
template <typename Key, typename Value, class Less>
typename listmap<Key,Value,Less>::iterator&
listmap<Key,Value,Less>::iterator::operator++() {
   TRACE ('l', where);
   where = where->next;
   return *this;
}

//
// listmap::iterator& listmap::iterator::operator--()
//
template <typename Key, typename Value, class Less>
typename listmap<Key,Value,Less>::iterator&
listmap<Key,Value,Less>::iterator::operator--() {
   TRACE ('l', where);
   where = where->prev;
   return *this;
}

//
// bool listmap::iterator::operator== (const iterator&)
//
template <typename Key, typename Value, class Less>
inline bool listmap<Key,Value,Less>::iterator::operator==
            (const iterator& that) const {
   return this->where == that.where;
}

//
// bool listmap::iterator::operator!= (const iterator&)
//
template <typename Key, typename Value, class Less>
inline bool listmap<Key,Value,Less>::iterator::operator!=
            (const iterator& that) const {
   return this->where != that.where;
}


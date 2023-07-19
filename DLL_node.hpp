// FILE: DLL_node.hpp
// Header file for Circular Doubly-linked List
// Barb Wahl and Theresa Wilson
// Last Revised: 3-15-23

 /*--------------------- DO NOT CHANGE THIS FILE ---------------------
 * 
 * PROVIDES: A class for a node in a circular doubly-linked list, 
 * all within the namespace cs223_dll
 *
 * DLL_NODE CLASS DATA:
 *   - The type of data stored in the node is determined by a typedef 
 *     statement at the top of the class. The typedef statement defines 
 *     a data type called `value_type`, which can then be used in place 
 *     of the actual data type (i.e., as an alias) stored in the node.
 *     
 *     For example,
 *
 *          typedef double value_type;  
 *
 *     defines `value_type` to be an alias for a double. 
 *
 *   - The data type of `value_type` may be any built-in C++ types (int, 
 *     char, ...) or any class with a copy constructor, an assignment 
 *     operator (=), and a test for equality (==).
 *
 *   - To change the type of data stored in the node, just update 
 *     the typedef statement.
 *
 *   - Within the class definition, use `value_type` as the data type for 
 *     any value stored in the node.
 *
 *   - Outside of the DLL_node class, use `DLL_node::value_type` as 
 *     the data type for any value stored in a DLL_node.
 *
 *
 * CONST POINTER RETURN TYPES:
 *   Some member functions have a return value that is a pointer to 
 *   to a DLL_node object (DLL_node*).  Each of these functions comes 
 *   in two versions: const and non-const.
 *
 *   - const version, where the return type is `const DLL_node*`
 *
 *     Example:
 *       const DLL_node* c;
 *       c -> next() // activates the const version of next() on 
 *                      the const DLL_node referenced by c
 *
 *   - non-const version, where the return type is `DLL_node*`
 *
 *     Example:
 *       DLL_node* p;
 *       p -> next() // activates the non-const version of next() 
 *                      on the DLL_node referenced by p
 *
 * ---------------------------------------------------------------------- /*

/* ----------------------------------------------------------------------
 * MEMBER FUNCTIONS for the DLL_node class:
 *   
 * CONSTRUCTORS
 *   DLL_node()
 *      Postconditions: 
 *         The node now contains the default value for `value_type`.
 *         The node's previous and next pointers are set to `nullptr`.
 *       
 *   DLL_node(const value_type& init_data)
 *      Postconditions: 
 *         The node now contains `init_data`.
 *         The node's previous and next pointers are set to `nullptr`.
 *
 *   DLL_node(const value_type& init_data, DLL_node* init_prev, DLL_node* init_next)
 *      Postcondition: 
 *         The node now contains `init_data`.
 *         The node's previous pointer is set to `init_prev`.
 *         The node's next pointer is set to `init_next`.
 *
 *   void set_data(const value_type& new_data)
 *      Postcondition: The node now contains the specified new data.
 *
 *   void set_prev(DLL_node* new_link)
 *      Postcondition: The node's previous pointer is reset to equal new_link.
 *
 *   void set_link(DLL_node* new_link)
 *      Postcondition: The node's next pointer is reset to equal new_link.
 *
 *   value_type data() const
 *      Postcondition: The return value is the data from this node.
 *
 *   const DLL_node* prev() const <----- const version
 *     Postcondition: The return value is the previous pointer from this node.
 *
 *   DLL_node* prev() <----------------- non-const version
 *     Postcondition: The return value is the previous pointer from this node.
 *
 *   const DLL_node* next() const <----- const version
 *     Postcondition: The return value is the next pointer from this node.
 *
 *   DLL_node* next() <----------------- non-const version
 *     Postcondition: The return value is the next pointer from this node.
 * ------------------------------------------------------------------------ */

#ifndef DLL_node_H
#define DLL_node_H

#include "Person.hpp"   // so we can store Person data

namespace cs223_dll {

class DLL_node {
  public:
    // TYPEDEF
    typedef Person value_type;

    // CONSTRUCTORS
    // Default Constructor, delegates to 3-arg constructor
    DLL_node() : DLL_node(value_type(), nullptr, nullptr) {
    }

    // 1-argument Constructor, delegates to 3-arg constructor
    DLL_node(const value_type& init_data) : DLL_node(init_data, nullptr, nullptr) {
    }
        
    // 3-argument Constructor
    DLL_node(const value_type& init_data, DLL_node* init_prev, DLL_node* init_next) {
        data_field = init_data; 
        prev_field = init_prev; 
        next_field = init_next;
    }

    // Setters
    void set_data(const value_type& new_data) { 
        data_field = new_data; 
    }

    void set_prev(DLL_node* new_link) { 
        prev_field = new_link; 
    }

    void set_next(DLL_node* new_link) { 
        next_field = new_link; 
    }

    // Getters
    value_type data() const { 
        return data_field; 
    }

    // const and non-const prev()
    const DLL_node* prev() const { 
        return prev_field; 
    }

    DLL_node* prev() { 
        return prev_field; 
    }

    // const and non-const next()
    const DLL_node* next() const { 
        return next_field; 
    }

    DLL_node* next() { 
        return next_field; 
    }

 private:
    value_type data_field;
    DLL_node* prev_field;
    DLL_node* next_field;

};  // end DLL_node class

}  // end namespace cs223_dll

#endif

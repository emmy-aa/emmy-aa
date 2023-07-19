// FILE: List.hpp
// Header file for Circular Doubly-linked List (CDLL)
// Barb Wahl and Theresa Wilson
// Last Revised: 2-18-18
//
// PROVIDES: A class for a circular, doubly-linked list with sentinel node.

#ifndef List_H_DLL
#define List_H_DLL

#include "DLL_node.hpp"  // which already includes Person.hpp

namespace cs223_dll {

class List {
 public:
    typedef DLL_node::value_type value_type;

    /* ------------------ Constructors and Destructor ------------------ */

    // Default Constructor
    //   Postcondition: The new list is empty with just a sentinel node,
    //      with the sentinel's previous and next pointers pointing back
    //      to itself.
    List();

    // Copy Constructor: new_list(other_list)
    //   Postcondition: The new list is an independent copy of `other_list`.
    //      Changing the new list will not change `other_list`, and changing
    //      `other_list` will not change the new list.
    List(const List &other_list);

    // Constructor taking an initialization list
    //   Postcondition: The new list contains the values provided by an
    //      initialization list in the same order that they were provided.
    //   EXAMPLE: `List L1({ A, B, C })` creates a list with A at the
    //      front, followed by B, with C at the end.
    List(std::initializer_list<value_type> init_list);

    // Assignment Operator: list = other_list
    //   Postcondition: This list becomes an identical -- but indepedent --
    //      copy of `other_list` list.
    //   NOTE: Returns the updated list to enable chaining of assignment.
    List& operator=(const List &other_list);

    // Destructor
    //   Postcondition: All memory in the heap that was used by this
    //      list has been freed.
    //   NOTE: Test indirectly by checking for memory leaks with Valgrind.
    ~List();

    /* ------------------ Accessor Member Functions ------------------ */

    // is_empty() - checks if the list is empty
    //   Postcondition: Returns `true` if there are no items in this list;
    //      otherwise, returns `false`.
    bool is_empty() const;

    // front() - get the value at the front of the list
    //   Precondition: This list is not empty.
    //   Postcondition: Return value is a copy of the value stored at
    //      the front of this list.
    value_type front() const;

    // back() - get the value at the end of the list
    //   Precondition: This list is not empty.
    //   Postcondition: Return value is a copy of the value stored at
    //      the end of this list.
    value_type back() const;

    // length() - get the length of the list
    //   Postcondition: Returns the number of items in this list.
    int length() const;

    // contains(item) - checks for an item in the list
    //   Postcondition: Returns `true` if there is an item equivalent to
    //      `val` in this list; otherwise, returns `false`.
    bool contains(value_type val) const;

    // bracket-indexing operator: list[index]
    //   Precondition: index >= 0
    //   Precondition: This list has at least index+1 items.
    //   Postcondition: Returns the ith item in this list, indexing from 0
    //   EXAMPLE: If myList is <D, O, G>, then myList[0] returns 'D',
    //      myList[1] returns 'O', and myList[2] returns 'G'.
    value_type operator[](unsigned int index) const;

    // public helper function to assist with testing
    const DLL_node* get_head_ptr() const { return head_ptr; }

    /* ------------------ Modification Member Functions ------------------ */

    // append(item) - add an item to the end of the list
    //   Postcondition: The list has one more node than before, and the
    //      value `val` is stored at the end of the list.
    //   EXAMPLE: If this list has items <p, i, g>, and then the call 
    //      was to append('g'), this list now has items: <p, i, g, g>
    void append(value_type val);

    // insert(item) - add an item to the list at the given index
    //   Precondition: 0 <= index <= length of this list.
    //   Postcondition: The list has one more node than before, the value `val`
    //      is stored in the list such that `list[index]` return the item.
    //   Postcondition: Items previously stored in the list from `index` to
    //      end of the list are now stored in the list starting at `index+1`.
    //   EXAMPLE: If this list had items <n, i, x>, and then the call was
    //      to insert(1, 'f'), this list now has items: <n, f, i, x>
    void insert(unsigned int index, value_type val);

    // remove(item) - tries to remove the first instance of an item from the list
    //   Postcondition: Removes the front-most item in this list that is
    //      equivalent (==) to the given value `val`.  
    //   Postcondition: Returns `true` if `val` is successfully removed
    //      from this list; otherwise, returns `false`.
    //   EXAMPLE: This list has items <j, z, g, z>.  A call to remove('z') 
    //      will return `true`, and the list items are now <j, g, z>.
    //   EXAMPLE: This list has items <j, z, g, z>.  A call to remove('n') 
    //      will return `false`, and the list items are still <j, g, z, z>.
    bool remove(value_type val);

    // remove(index) - removes the item stored in the list at the given index
    //   Precondition: 0 <= index < length of this list.
    //   Postcondition: The item previously stored in the list at `index`
    //      is not longer in the list.
    //   Postcondition: Items previously stored in the list from `index+1` to
    //      end of the list are now stored in the list starting at `index`.
    //   EXAMPLE: The list has items <j, z, g, z>.  A call to remove(2) 
    //      will return true, and the list items are now <j, z, z>.
    void remove(unsigned int index);

    // clear - removes all items from the list
    //   Postcondition: List is empty.
    void clear();

    /* ------------------ Friend NON-MEMBER Functions ------------------ */

    // list equivalence operator - IMPLEMENTATION PROVIDED
    //   Postcondition: Returns `true` when list1 and list2 have the same 
    //     length and store equivalent elements in the same order: for every 
    //     position i in the range [0, length of list1), the ith element of 
    //     list1 is equivalent to the ith element of list2
    friend bool operator==(const List& list1, const List& list2);

    // stream output operator - IMPLEMENTATION PROVIDED
    //   Postcondition: For lists with length > 0, contents of the list are 
    //      placed into the given output stream using the following format:
    //           "List:\nfirst_item\n...\nlast_item\n"
    //      For lists of length = 0, the following will be placed into the
    //      given output stream:
    //           "Empty List\n"
    //    EXAMPLE: If myList is <rain, grass, flowers>, then cout << myList will
    //       produce the following in standard out:
    //         List:
    //          rain
    //          grass
    //          flowers
    friend std::ostream& operator<<(std::ostream& out, const List& list);

 private:
    DLL_node* head_ptr;  // pointer to sentinel node

    /* ------------------ Private Helper Functions ------------------ */

    // setup_sentinel() 
    //   Description: Used by constructors to initialize the list.
    //   Postcondition: `head_ptr` points to the sentinel node for an empty list
    void setup_sentinel();

    // insert_after_node(node_ptr, item) 
    //   Description: Used by functions that add values to the list.
    //   Postcondition: A new node containing `item` has been added to
    //      this list after the node pointed to by `node_ptr`.
    void insert_after_node(DLL_node* node_ptr, value_type item);

    // remove_node(node_ptr) 
    //   Description: Used by functions that remove items from the list.
    //   Postcondition: A the node pointed to by `node_ptr` has been
    //      removed from this list.
    void remove_node(DLL_node* node_ptr);
    

};  // end List class
}  // end namespace cs223_dll

#endif

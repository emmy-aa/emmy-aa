// FILE: List.cpp
// CS 223 Winter 2023, Lab 2
//
// Student Name: Emmy Apaloo
// Date: 03-20-2023
//
// List class implementation for a circular doubly-linked list with sentinel
// node.
//
// Instance data:
//    Every List has a pointer (called "head_ptr") to its sentinel node.
//
// Class invariants:
//    1. All the list nodes, including the sentinel node, are stored in
//       dynamic memory.
//    2. The head pointer for the list ALWAYS points to the sentinel node.
//    3. The sentinel node's data is always the default value for
//       DLL_node::value_type.
//    4. For an EMPTY list, the sentinel node's links (prev, next) refer to
//       the sentinel node itself.
//
// NOTE: The DLL_node class is already completely implemented in DLL_node.hpp.
//

#include <iostream>
#include <string>
#include "List.hpp"

using namespace std;

namespace cs223_dll {

// Private helper method. Use for diagnostics, to print out node info.
//   Example use:
//   cout << *head_ptr     -- Prints info on sentinel node
ostream& operator<<(ostream& out, const DLL_node& n) {
    out << "Node at: " << &n << "\n"
        << "\tdata: " << n.data() << "\n"
        << "\tprev: " << n.prev() << "\n"
        << "\tnext: " << n.next() << endl;
    return out;
}

// setup_sentinel() - Private Helper Function
//   Description: Used by constructors to initialize the list.
//   Postcondition: `head_ptr` points to the sentinel node for an empty list
void List::setup_sentinel() {
    //Create a DLL_node in the heap
    head_ptr = new DLL_node;
    // Set prev_field to point back to the sentinel
    head_ptr -> set_prev(head_ptr);
    // Set the next_field to point back to the sentinel
    head_ptr -> set_next(head_ptr);

    
}

// Default Constructor
//   Postcondition: The new list is empty with just a sentinel node,
//      with the sentinel's previous and next pointers pointing back
//      to itself.
List::List() {
    setup_sentinel();
}


// Copy Constructor: new_list(other_list)
//   Postcondition: The new list is an independent copy of `other_list`.
//      Changing the new list will not change `other_list`, and changing
//      `other_list` will not change the new list.
List::List(const List &other_list) {
    cout << "copy constructor: NOT YET IMPLEMENTED" << endl;
}

// Constructor taking an initialization list -- PROVIDED
//   Postcondition: The new list contains the values provided by an
//      initialization list in the same order that they were provided.
//   EXAMPLE: `List L1({ A, B, C })` creates a list with A at the
//      front, followed by B, with C at the end.
List::List(std::initializer_list<DLL_node::value_type> l)
{
    setup_sentinel();
    for (auto it = l.begin(); it != l.end(); ++it)
    {
        append(*it);
    }
}

// Assignment Operator: list = other_list
//   Postcondition: This list becomes an identical -- but indepedent --
//      copy of `other_list` list.
//   NOTE: Returns the updated list to enable chaining of assignment.
List& List::operator=(const List &other_list) {
    cout << "assignment operator: NOT YET IMPLEMENTED" << endl;
    return *this;
}

// Destructor
//   Postcondition: All memory in the heap that was used by this
//      list has been freed.
//   NOTE: Test indirectly by checking for memory leaks with Valgrind.
List::~List() {
    cout << "destructor: NOT YET IMPLEMENTED" << endl;
}

// is_empty() - checks if the list is empty
//   Postcondition: Returns `true` if there are no items in this list;
//      otherwise, returns `false`.
bool List::is_empty() const {
    return head_ptr ->next() == head_ptr;
}

// front() - get the value at the front of the list
//   Precondition: This list is not empty.
//   Postcondition: Return value is a copy of the value stored at
//      the front of this list.
DLL_node::value_type List::front() const {
    return head_ptr ->next()->data();
}

// back() - get the value at the end of the list
//   Precondition: This list is not empty.
//   Postcondition: Return value is a copy of the value stored at
//      the end of this list.
DLL_node::value_type List::back() const {
    return head_ptr -> prev()->data();
}

// length() - get the length of the list
//   Postcondition: Returns the number of items in this list.
int List::length() const {
    DLL_node* curr_node = head_ptr ->next();
    int acc = 0;
    while(curr_node != head_ptr){
        acc = acc + 1;
        curr_node = curr_node -> next();
    }
    
    return acc;
}

// contains(item) - checks for an item in the list
//   Postcondition: Returns `true` if there is an item equivalent to
//      `val` in this list; otherwise, returns `false`.
bool List::contains(value_type val) const {
    DLL_node* curr_node = head_ptr ->next();
    while(curr_node != head_ptr){
        if (curr_node ->data() == val) {
            return true;

        }
        else{
            curr_node = curr_node ->next();
        }

    }
    return false;
}

// bracket-indexing operator: list[index]
//   Precondition: index >= 0 
//   Precondition: This list has at least index+1 items.
//   Postcondition: Returns the ith item in this list, indexing from 0
//   EXAMPLE: If myList is <D, O, G>, then myList[0] returns 'D',
//      myList[1] returns 'O', and myList[2] returns 'G'.
DLL_node::value_type List::operator[](unsigned int index) const {
    DLL_node* curr_node = head_ptr ->next();
    if(index == 0){
        return curr_node ->data();
    }

    for(int i = 0; i < index; i++ ){
        curr_node = curr_node -> next();
    }
    return curr_node ->data();
}

// insert_after_node(node_ptr, item) - Private Helper Function
//   Description: Used by functions that add values to the list.
//   Postcondition: A new node containing `item` has been added to
//      this list after the node pointed to by `node_ptr`.
void List::insert_after_node(DLL_node* node_ptr, value_type item) {
    DLL_node*  prev_ptr = node_ptr ->prev();
    DLL_node*  next_ptr = node_ptr ->next();
    DLL_node*  new_node = new DLL_node;
    new_node -> set_data(item);

    //Resetting pointers for new/next ptr
    new_node -> set_prev(node_ptr);
    new_node -> set_next(next_ptr);
    next_ptr -> set_prev(new_node);
    node_ptr -> set_next(new_node);
}

// append(item) - add an item to the end of the list
//   Postcondition: The list has one more node than before, and the
//      value `val` is stored at the end of the list.
//   EXAMPLE: If this list has items <p, i, g>, and then the call
//      was to append('g'), this list now has items: <p, i, g, g>
void List::append(value_type val) {
    insert_after_node(head_ptr ->prev(), val);
}

// insert(item) - add an item to the list at the given index
//   Precondition: 0 <= index <= length of this list.
//   Postcondition: The list has one more node than before, the value `val`
//      is stored in the list such that `list[index]` return the item.
//   Postcondition: Items previously stored in the list from `index` to
//      end of the list are now stored in the list starting at `index+1`.
//   EXAMPLE: If this list had items <n, i, x>, and then the call was
//      to insert(1, 'f'), this list now has items: <n, f, i, x>
void List::insert(unsigned int index, value_type val) {
     DLL_node* curr_ptr = head_ptr;
    for (int i = 0; i<index; i++){
        curr_ptr = curr_ptr -> next();
    }
    insert_after_node(curr_ptr, val);
}

// remove_node(node_ptr) - Private Helper Function
//   Description: Used by functions that remove items from the list.
//   Postcondition: A the node pointed to by `node_ptr` has been
//      removed from this list.
void List::remove_node(DLL_node* node_ptr) {
    DLL_node* remove_ptr = node_ptr;
    node_ptr = remove_ptr -> prev();
    node_ptr -> set_next(remove_ptr -> next());
    node_ptr = remove_ptr -> next();
    node_ptr -> set_prev(remove_ptr -> prev());
    delete remove_ptr;
    
}

// remove(item) - tries to remove the first instance of an item from the list
//   Postcondition: Removes the front-most item in this list that is
//      equivalent (==) to the given value `val`.
//   Postcondition: Returns `true` if `val` is successfully removed
//      from this list; otherwise, returns `false`.
//   EXAMPLE: This list has items <j, z, g, z>.  A call to remove('z')
//      will return `true`, and the list items are now <j, g, z>.
//   EXAMPLE: This list has items <j, z, g, z>.  A call to remove('n')
//      will return `false`, and the list items are still <j, g, z, z>.
bool List::remove(value_type val) {
    DLL_node* curr_ptr = head_ptr -> next();
    while (curr_ptr != head_ptr) {
        if (curr_ptr -> data() == val) {
            remove_node(curr_ptr);
            return true;
        }
        curr_ptr = curr_ptr -> next();
    }
    return false;
}

// remove(index) - removes the item stored in the list at the given index
//   Precondition: 0 <= index < length of this list.
//   Postcondition: The item previously stored in the list at `index`
//      is not longer in the list.
//   Postcondition: Items previously stored in the list from `index+1` to
//      end of the list are now stored in the list starting at `index`.
//   EXAMPLE: The list has items <j, z, g, z>.  A call to remove(2)
//      will return true, and the list items are now <j, z, z>.
void List::remove(unsigned int index) {
    DLL_node* curr_ptr = head_ptr -> next();
    int acc = 0;
    while(curr_ptr!=head_ptr){
        if(acc == index){
            remove_node(curr_ptr);
            return;
            
        }
        curr_ptr = curr_ptr->next();
        acc++;
    }
   
}

// clear - removes all items from the list
//   Postcondition: List is empty.
void List::clear() {
    while (!is_empty()) {
        remove_node(head_ptr -> next());
    }
    
}

// list equivalence operator - IMPLEMENTATION PROVIDED
//   Postcondition: Returns `true` when list1 and list2 have the same
//     length and store equivalent elements in the same order: for every
//     position i in the range [0, length of list1), the ith element of
//     list1 is equivalent to the ith element of list2
bool operator==(const List& list1, const List& list2) {
    const DLL_node* head1 = list1.head_ptr;
    const DLL_node* head2 = list2.head_ptr;
    const DLL_node* curr1 = head1;
    const DLL_node* curr2 = head2;

    while (curr1->next() != head1 && curr2->next() != head2) {
        curr1 = curr1->next();
        curr2 = curr2->next();
        if (curr1->data() != curr2->data()) {
            return false;
        }
    }

    return (curr1->next() == head1 && curr2->next() == head2);
}

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
std::ostream& operator<<(std::ostream& out, const List& list) {
    if (list.is_empty()) {
        out << "Empty List" << endl;
    }
    else {
        out << "List:\n";
        const DLL_node* curr = list.head_ptr->next();
        while (curr != list.head_ptr) {
            out << curr->data() << endl;
            curr = curr->next();
        }
    }
    return out;
}

}  // namespace cs223_dll

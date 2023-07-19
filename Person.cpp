//  Person.cpp
//
//  Function implementations for Person class, CS 223, Lab 1
//
//  Student: 
//  Date:
//
//    Person Class Instance Variables
//    string first;      // the person's first name
//    string last;       // the person's last name
//    int age;           // the person's age

#include <iostream>
#include <string>
#include "Person.hpp"

using namespace std;

// CONSTRUCTORS
Person::Person(string fname, string lname, int A) {
    first = fname;
    last = lname; 
    age = A;
}

// ACCESSOR MEMBER FUNCTIONS

string Person::getFirstName() const {
    return first;   
}

string Person::getLastName() const {
    return last;
}

int Person::getAge() const {
    return age;
}

string Person::getFullName() const {
    return first + " " + last;
}

// MODIFICATION MEMBER FUNCTIONS
void Person::setFirstName(string newName) {
    first = newName;
}

void Person::setLastName(string newName) {
    last = newName;
}

void Person::setAge(int newAge) {
    age = newAge;
}

void Person::agePerson() {
    age++;
}

// NON-MEMBER FUNCTIONS

bool operator==(const Person& personA, const Person& personB) {
    return personA.getLastName() == personB.getLastName() &&
           personA.getFirstName() == personB.getFirstName() &&
           personA.getAge() == personB.getAge();
}

bool operator!=(const Person& personA, const Person& personB) {
    return !(personA == personB);
}

bool operator<(const Person& personA, const Person& personB) {
    if (personA.getLastName() < personB.getLastName()) {
        return true;
    }
    else if (personA.getLastName() == personB.getLastName() &&
             personA.getFirstName() < personB.getFirstName()) {
        return true;
    }
    else if (personA.getLastName() == personB.getLastName() &&
             personA.getFirstName() == personB.getFirstName() &&
             personA.getAge() < personB.getAge()) {
        return true;
    }
    else {
        return false;
    }
}

bool operator<=(const Person& personA, const Person& personB) {
    return !(personA > personB);
}

bool operator>(const Person& personA, const Person& personB) {
    if (personA.getLastName() > personB.getLastName()) {
        return true;
    }
    else if (personA.getLastName() == personB.getLastName() &&
             personA.getFirstName() > personB.getFirstName()) {
        return true;
    }
    else if (personA.getLastName() == personB.getLastName() &&
             personA.getFirstName() == personB.getFirstName() &&
             personA.getAge() > personB.getAge()) {
        return true;
    }
    else {
        return false;
    }
}

bool operator>=(const Person& personA, const Person& personB) {
    return !(personA < personB);
}

Person operator+(const Person& personA, const Person& personB) {
    string newlast = personA.getLastName() + "-" + personB.getLastName();
    return Person("Baby", newlast);
}

ostream& operator<<(ostream& out, const Person& person) {
    out << "Person: " << person.getFullName() << ", ";
    out << "age " << person.getAge();
    return out;
}

istream& operator>>(istream& in, Person& person) {
    string ignore;
    string fname, lname;
    int A;

    in >> ignore;
    in >> fname;
    in >> lname;
    lname = lname.substr(0, lname.length()-1);
    in >> ignore;
    in >> A;
    
    person.setFirstName(fname);
    person.setLastName(lname);
    person.setAge(A);

    return in;
}

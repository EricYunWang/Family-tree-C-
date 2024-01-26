/*
* Eric (Yun) Wang
* Oct 14 2023
* SFU 301291511
* 778-223-3039
* eric_wang_13@sfu.ca
* 
* Code test to CD PROJEKT RED Vancouver - Junior Programmer
*/

/*
* README
* I included an Main.cpp file containing my informal test functions.
* I understand this test is a C++ with lots of relationship pointings going on, runtime error/seg fault happens quite a bit during writing the code.
* I did this project on my own, so I acknowledge that it is impossible for me to cover all test cases.
* If my code does not run with your test cases, please check my Main.cpp as it might show you what I missed.
* 
* I chose to leave some cout statements inside the functions.
* The purpose was to see which function statements got excuted successfully.
* Simply comment them out if they should not be there please.
* 
* The h file is completely unmodified as I believe there is enought information to make it work.
* 
* Lastly, feel free to email me about any confusions in the code.
* And I appreciate any feedback to my code. 
*/

#include <iostream>
#include "Person.h"

// @return the aurthor's name, my name.
const char* Person::getAuthor()
{
    return "Eric (Yun) Wang";
}

// Constructor for Person class.
// @param the gender of the person, and the name of the person.
// @return the person class object with given inputs.
Person::Person(Sex inputSex, const std::string& inputName):
    sex(inputSex), name(inputName)
{
}

// Destructor for Person class.
Person::~Person()
{
}

// Function to set father of this person.
// @param the father to be set.
// @return a boolean according to the outcome of the execution.
// returns true if new father is set or unset father.
// returns false otherwise.
bool Person::setFather(Person* inputFather)
{
    // Condition if input is nullptr
    if (inputFather == nullptr) {
        if (father != nullptr) {
            father->removeChild(this);
            // Warning: reusing removeChild here maybe cause more function call than needed because
            // removeChild also calls setFather/setMother functions, when input nullptr for example.
            // The other option would be copying erase vector from removeChild here.
            // This is more readable, but other option might be more efficient.
        }
        father = nullptr;
        std::cout << "Father name unset" << std::endl;
        return true;
    }
    // Same input as existing father, exit.
    if (inputFather == father) {
        std::cout << "Identical father's name" << std::endl;
        return false;
    }
    // New father input.
    else {
        if (father != nullptr) {
            father->removeChild(this); // children vector handling.
        }
        father = inputFather;
        if (father != nullptr) {
            father->children.push_back(this);
            std::cout << "New father name set" << std::endl;
            return true;
        }
    }
    return false;
}

// Function to set mother of this person.
// @param the mother to be set.
// @return a boolean according to the outcome of the execution.
// returns true if new mother is set or unset mother.
// returns false otherwise.
bool Person::setMother(Person* inputMother)
{
    if (inputMother == nullptr) {
        if (mother != nullptr) {
            mother->removeChild(this);
        }
        mother = nullptr;
        std::cout << "Mother name unset" << std::endl;
        return true;
    }
    if (inputMother == mother) {
        std::cout << "Identical mother's name" << std::endl;
        return false;
    }
    else {
        if (mother != nullptr) {
            mother->removeChild(this);
        }
        mother = inputMother;
        if (mother != nullptr) {
            mother->children.push_back(this);
            std::cout << "New mother name set" << std::endl;
            return true;
        }
    }
    return false;
}

// Function to check if person has the input person as child.
// @param the child's name to check
// @return a boolean according to the outcome. True if is a child, false if not.
bool Person::hasChild(const Person* child) const
{
    for (int i = 0; i < getNumChildren(); i++) {
        if (getChild(i) == child) {
            return true;
        }
    }
    return false;
}

// Function to add input child to person.
// @param the child to be added.
// @return a boolean according to the outcome of the execution.
// True if child added successfully. False if not.
bool Person::addChild(Person* child)
{
    // Return false if duplicate child found or invalid child.
    if (hasChild(child) == true || child == nullptr) {
        std::cout << "Please enter a valid child" << std::endl;
        return false;
    }

    // Use set functions from above.
    // Set functions will handle push children.
    else {
        if (this->sex == MALE) {
            child->setFather(this);
            return true;
        }
        if (this->sex == FEMALE) {
            child->setMother(this);
            return true;
        }
    }
    return false;
}

// Function to remove input child from person
// @param the child to be removed.
// @return a boolean according to the outcome. True if successfully remove, false if not.
bool Person::removeChild(Person* child)
{
    // Returns false if no such child exist or invalid input.
    // Warning: this if statement might get called more times than necessary, from setFather setMother.
    if (hasChild(child) == false || child == nullptr) {
        std::cout << "Please enter a valid child" << std::endl;
        return false;
    }

    People::iterator childIterator = findChild(child);
    if (childIterator != children.end()) {
        children.erase(childIterator); // Erase the child from the vector
        if (this->sex == MALE) {
            child->setFather(nullptr); // set parent to nullptr.
        }
        if (this->sex == FEMALE) {
            child->setMother(nullptr);
        }
        std::cout << "Remove successful" << std::endl;
        return true;
    }
    return false;
}

// Function to remove all children of person
void Person::removeAllChildren()
{
    // Traverse vector and remove.
    for (Person* list : children) {
        removeChild(list);
    }
}

// Function to find all ancestors of person.
// @param the result to be stored to.
void Person::getAncestors(People& results) const
{
    // Recursion
    // If person has parent, store parent and recursively call function on parents.
    if (this->father != nullptr) {
        results.push_back(this->father);
        this->father->getAncestors(results);
    }
    if (this->mother != nullptr) {
        results.push_back(this->mother);
        this->mother->getAncestors(results);
    }
}

// Function to find all descendants of person.
// @param the result to be stored to.
void Person::getDescendants(People& results) const
{
    // Recursion as well
    for (Person* list : children) {
        results.push_back(list);
        list->getDescendants(results);
    }
}

// Function to find all siblings of person.
// @param the result to be stored to.
void Person::getSiblings(People& results) const
{
    // Store same father's children except for self
    if (this->father != nullptr) {
        for (Person* list : this->father->children) {
            if (list != this) {
                results.push_back(list);
            }
        }
    }
    // Store same mother's children except for self
    if (this->mother != nullptr) {
        for (Person* list : this->mother->children) {
            if (list != this) {
                results.push_back(list);
            }
        }
    }

}

// Function to find all cousins of person.
// @param the result to be stored to.
void Person::getCousins(People& results) const
{
    // Uses getSiblings as helper function.
    // The siblings of parents are uncles/aunts.
    // Their children are cousins.
    if (this->father != nullptr) {
        People uncle;
        this->father->getSiblings(uncle);
        for (const Person* uncle : uncle) {
            for (Person* list : uncle->children) {
                results.push_back(list);
            }
        }
    }

    if (this->mother != nullptr) {
        People aunt;
        this->mother->getSiblings(aunt);
        for (const Person* uncle : aunt) {
            for (Person* list : uncle->children) {
                results.push_back(list);
            }
        }
    }
}

People::iterator Person::findChild(const Person* child)
{
    return std::find(children.begin(), children.end(), child);
}

People::const_iterator Person::findChild(const Person* child) const
{
    return std::find(children.begin(), children.end(), child);
}

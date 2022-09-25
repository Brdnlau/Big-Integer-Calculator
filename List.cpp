/********************************************************************************* 
* Brandon Lau, blau7
* 2022 Spring CSE101 PA6
* List.cpp 
* Implementation File for List ADT 
*********************************************************************************/
#include <iostream>
#include <string>
#include <stdexcept>

#include "List.h"

// Private Constructor --------------------------------------------------------
List::Node::Node(ListElement x){
   data = x;
   prev = nullptr;
   next = nullptr;
}


// Class Constructors & Destructors -------------------------------------------
// Constructor
List::List(){
    frontDummy = new Node(-1);
    backDummy = new Node(-1);
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;
}

// Copy Constructor
List::List(const List& L){
    frontDummy = new Node(-1);
    backDummy = new Node(-1);
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    num_elements = 0;

    for (Node* N = L.frontDummy->next; N != L.backDummy; N = N->next){
        insertBefore(N->data);
    }
    pos_cursor = 0;
}

// Destructor
List::~List(){
    // clear all nodes and then clear sentinel nodes
    clear();
    delete frontDummy;
    delete backDummy;
}


// Access functions --------------------------------------------------------
int List::length() const{
    return num_elements;
}

ListElement List::front() const{
    if (num_elements <= 0){
        throw std::length_error("List: front(): empty List");
    }
    return frontDummy->next->data;
}

ListElement List::back() const{
    if (num_elements <= 0){
        throw std::length_error("List: back(): empty List");
    }
    return backDummy->prev->data;
}

int List::position() const{
    if (pos_cursor > num_elements || pos_cursor < 0){
        throw std::range_error("List: position(): cursor out of bounds");
    }
    return pos_cursor;
}

ListElement List::peekNext() const{
    if (position() >= num_elements){
        throw std::range_error("List: peekNext(): cursor at back");
    }
    return afterCursor->data;
}

ListElement List::peekPrev() const{
    if (position() <= 0){
        throw std::range_error("List: peekPrev(): cursor at front");
    }
    return beforeCursor->data;
}


// Manipulation procedures -------------------------------------------------
void List::clear(){
    // move to front and erase every node until empty
    moveFront();
    while (num_elements != 0){
        eraseAfter();
    }
}

void List::moveFront(){
    // set cursor to 0 and before cursor to the front dummy, and then check if list is empty or not to see where aftercursor should point
    pos_cursor = 0;
    beforeCursor = frontDummy;
    if (num_elements == 0){
        afterCursor = backDummy;
    }
    else{
        afterCursor = frontDummy->next;
    }
}

void List::moveBack(){
    // set cursor to the length and after cursor to the back dummy, and then check if list is empty or not to see where beforecursor should point
    pos_cursor = num_elements;
    afterCursor = backDummy;
    if (num_elements == 0){
        beforeCursor = frontDummy;
    }
    else{
        beforeCursor = backDummy->prev;
    }
}

// pre: position()<length() 
ListElement List::moveNext(){
    if (position() >= length()){
        throw std::range_error("List: moveNext(): cursor at back");
    }
    // move nodes right one and increment cursor
    beforeCursor = beforeCursor->next;
    afterCursor = afterCursor->next;
    pos_cursor ++;
    return peekPrev();   
}

ListElement List::movePrev(){
    if (position() <= 0){
        throw std::range_error("List: movePrev(): cursor at front");
    }
    // move nodes left one and decrement cursor
    beforeCursor = beforeCursor->prev;
    afterCursor = afterCursor->prev;
    pos_cursor --;
    return peekNext();   
}

void List::insertAfter(ListElement x){
    // create a new node and change cursor pointers, then increment number of elements
    Node* newNode = new Node(x);
    beforeCursor->next = newNode;
    afterCursor->prev = newNode;
    newNode->prev = beforeCursor;
    newNode->next = afterCursor;
    afterCursor = newNode;
    num_elements ++;
}

void List::insertBefore(ListElement x){
    // create a new node and change cursor pointers, then increment number of elements and cursor position
    Node* newNode = new Node(x);
    beforeCursor->next = newNode;
    afterCursor->prev = newNode;
    newNode->prev = beforeCursor;
    newNode->next = afterCursor;
    beforeCursor = newNode;
    pos_cursor ++;
    num_elements ++;
}

void List::setAfter(ListElement x){
    if (position() >= length()){
        throw std::range_error("List: setAfter(): cursor at back");
    }
    afterCursor->data = x;
}

void List::setBefore(ListElement x){
    if (position() <= 0){
        throw std::range_error("List: setBefore(): cursor at front");
    }
    beforeCursor->data = x;
}

void List::eraseAfter(){
    if (position() >= length()){
        throw std::range_error("List: eraseAfter(): cursor at back");
    }
    // bridge gap between nodes and delete the aftercursor, and set it to the one after, then decrement num elements
    beforeCursor->next = afterCursor->next;
    afterCursor->next->prev = beforeCursor;
    delete afterCursor;
    afterCursor = beforeCursor->next;
    afterCursor->prev = beforeCursor;
    num_elements --;
}

void List::eraseBefore(){
    if (position() <= 0){
        throw std::range_error("List: eraseBefore(): cursor at front");
    }
    // bridge gap between nodes and delete the beforecursor, and set it to the one before, then decrement num elements and cursor position
    afterCursor->prev = beforeCursor->prev;
    beforeCursor->prev->next = afterCursor;
    delete beforeCursor;
    beforeCursor = afterCursor->prev;
    beforeCursor->next = afterCursor;
    num_elements --;
    pos_cursor --;
}


// Other Functions ---------------------------------------------------------
int List::findNext(ListElement x){
    // loop through list starting at the cursor, if found return position after where it is found, if not, return -1
    while (pos_cursor != length()){
        if (moveNext() == x){
            return position();
        }
    }
    return -1;
}
 
int List::findPrev(ListElement x){
    // loop through list starting at the cursor, but backwards, if found return position in front of where it is found, if not, return -1
    while (pos_cursor > 0){
        if (movePrev() == x){
            return position();
        }
    }
    return -1;
}

void List::cleanup(){
    // first for loop keeps track of the unique element, second for loop searching list after it for repeats and deletes them
    int iPos = -1;
    for (Node* i = frontDummy->next; i != backDummy; i = i->next){
        iPos ++;
        Node* j = i->next;
        int jPos = iPos;
        while (j != backDummy){
            jPos ++;
            if (i->data == j->data){
                if (j == beforeCursor){
                    beforeCursor = beforeCursor->prev;
                }
                else if (j == afterCursor){
                    afterCursor = afterCursor->next;
                }
                j->prev->next = j->next;
                j->next->prev = j->prev;
                Node* del = j;
                j = j->next;
                delete del;
                num_elements --;
                if (jPos < pos_cursor){
                    pos_cursor --;
                    jPos --;
                }
            }
            else{
                j = j->next;
            }
        }
    }
} 

List List::concat(const List& L) const{
    // loops through both this list and the reference List and appends them to the new list and returns it
    List concat;
    for (Node* A = this->frontDummy->next; A != this->backDummy; A = A->next){
        concat.insertBefore(A->data);
    }
    for (Node* B = L.frontDummy->next; B != L.backDummy; B = B->next){
        concat.insertBefore(B->data);
    }
    concat.moveFront();
    return concat;
}

std::string List::to_string() const{
    // loops through each node and concatinates it to string s, then returns s
    std::string s = "(";
    for (Node* N = frontDummy->next; N != backDummy; N = N->next){
        if (N->next != backDummy){
            s += std::to_string(N->data) + ", ";
        }
        else{
            s += std::to_string(N->data) + ")";
        }
    }
    if (s.compare("(") == 0){
        return "";
    }
    else{
        return s;
    }
}

bool List::equals(const List& R) const{
    bool eq = false;
    Node* N = nullptr;
    Node* M = nullptr;

    // check if lengths are even equal
    eq = (this->num_elements == R.num_elements );
    N = this->frontDummy->next;
    M = R.frontDummy->next;
    // loops through both lists until false element found
    while( eq && N!=backDummy){
        eq = (N->data==M->data);
        N = N->next;
        M = M->next;
    }
    return eq;
}


// Overriden Operators -----------------------------------------------------
std::ostream& operator<<( std::ostream& stream, const List& L ){
    return stream << L.List::to_string();
}

bool operator==( const List& A, const List& B ){
    return A.List::equals(B);
}

List& List::operator=( const List& L ){
    if( this != &L ){
        List temp = L;
        std::swap(frontDummy, temp.frontDummy);
        std::swap(backDummy, temp.backDummy);
        std::swap(num_elements, temp.num_elements);
    }
    return *this;
} 
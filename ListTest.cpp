/********************************************************************************* 
* Brandon Lau, blau7
* 2022 Spring CSE101 PA6
* ListTest.cpp
* Test File for List ADT 
*********************************************************************************/
#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"

using namespace std;

int main(){
    List A;

    cout << "A Length: " << A.length() << endl;
    cout << "A Position: " << A.position() << endl;
    cout << "A: " << A << endl << endl;

    for(int i=1; i<=5; i++){
        A.insertBefore(i);
    }

    cout << "A Length: " << A.length() << endl;
    cout << "A Position: " << A.position() << endl;
    cout << "A: " << A << endl << endl;

    List B = A;
    cout << "B Length: " << B.length() << endl;
    cout << "B Position: " << B.position() << endl;
    cout << "B: " << B << endl << endl;

    List C = A.concat(B);
    cout << "C Length: " << C.length() << endl;
    cout << "C Position: " << C.position() << endl;
    cout << "C: " << C << endl << endl;

    C.moveFront();
    C.insertBefore(420);
    C.moveBack();
    C.insertAfter(6);
    cout << "C Length: " << C.length() << endl;
    cout << "C Position: " << C.position() << endl;
    cout << "C Front: " << C.front() << endl;
    cout << "C Back: " << C.back() << endl;
    cout << "C PeekPrev: " << C.peekPrev() << endl;
    cout << "C PeekNext: " << C.peekNext() << endl;
    cout << "C: " << C << endl << endl;

    C.cleanup();
    cout << "C Length: " << C.length() << endl;
    cout << "C Position: " << C.position() << endl;
    cout << "C Front: " << C.front() << endl;
    cout << "C Back: " << C.back() << endl;
    cout << "C PeekPrev: " << C.peekPrev() << endl;
    cout << "C PeekNext: " << C.peekNext() << endl;
    cout << "C: " << C << endl << endl;

    C.movePrev();
    cout << "C Position: " << C.position() << endl;
    C.moveNext();
    cout << "C Position: " << C.position() << endl << endl;

    C.eraseAfter();
    C.eraseBefore();
    cout << "C Length: " << C.length() << endl;
    cout << "C Position: " << C.position() << endl;
    cout << "C Front: " << C.front() << endl;
    cout << "C Back: " << C.back() << endl;
    cout << "C: " << C << endl << endl;

    int val = C.movePrev();
    cout << val << endl;
    C.setBefore(8);
    C.setAfter(9);
    cout << "C Length: " << C.length() << endl;
    cout << "C Position: " << C.position() << endl;
    cout << "C Front: " << C.front() << endl;
    cout << "C Back: " << C.back() << endl;
    cout << "C: " << C << endl << endl;
    
    C.findNext(5);
    cout << "C Position: " << C.position() << endl;
    C.findPrev(1);
    cout << "C Position: " << C.position() << endl << endl;

    C.clear();
    cout << "C Length: " << C.length() << endl;
    cout << "C Position: " << C.position() << endl;
    cout << "C: " << C << endl << endl;

    List D;
    cout << (C == D) << endl;
    cout << (C == A) << endl;

    C = A;
    cout << (C == A) << endl;
    cout << "A Length: " << A.length() << endl;
    cout << "A Position: " << A.position() << endl;
    cout << "A: " << A << endl << endl;
    cout << "C Length: " << C.length() << endl;
    cout << "C Position: " << C.position() << endl;
    cout << "C: " << C << endl << endl;

    return(EXIT_SUCCESS);
}

/*
Output of this program:
A Length: 0
A Position: 0
A: 

A Length: 5
A Position: 5
A: (1 2 3 4 5)

B Length: 5
B Position: 0
B: (1 2 3 4 5)

C Length: 10
C Position: 0
C: (1 2 3 4 5 1 2 3 4 5)

C Length: 12
C Position: 11
C Front: 420
C Back: 6
C PeekPrev: 5
C PeekNext: 6
C: (420 1 2 3 4 5 1 2 3 4 5 6)

C Length: 7
C Position: 6
C Front: 420
C Back: 6
C PeekPrev: 5
C PeekNext: 6
C: (420 1 2 3 4 5 6)

C Position: 5
C Position: 6

C Length: 5
C Position: 5
C Front: 420
C Back: 4
C: (420 1 2 3 4)

4
C Length: 5
C Position: 4
C Front: 420
C Back: 9
C: (420 1 2 8 9)

C Position: 5
C Position: 1

C Length: 0
C Position: 0
C: 

1
0
1
A Length: 5
A Position: 5
A: (1 2 3 4 5)

C Length: 5
C Position: 0
C: (1 2 3 4 5)
*/
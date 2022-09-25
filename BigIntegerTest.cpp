/********************************************************************************* 
* Brandon Lau, blau7
* 2022 Spring CSE101 PA6
* BigIntegerTest.cpp
* Test File for BigInteger ADT 
*********************************************************************************/
#include<iostream>
#include<string>
#include<stdexcept>
#include"BigInteger.h"

using namespace std;

int main(){

   string s1 = "123456789";
   string s2 = "9876543210";

   BigInteger A = BigInteger(s1);
   BigInteger B = BigInteger(s2);
   BigInteger C = A;
   cout << endl;

   cout << "A = " << A << endl;
   cout << "B = " << B << endl;
   cout << "C = " << B << endl;
   cout << "A's sign is " << A.sign() << endl;
   cout << "B's sign is " << B.sign() << endl;
   cout << "C's sign is " << C.sign() << endl;
   cout << "(C==A) = " << ((C==A)?"True":"False") << endl;
   cout << endl;

   cout << "(A==B) = " << ((A==B)?"True":"False") << endl;
   cout << "(A<B)  = " << ((A<B)? "True":"False") << endl;
   cout << "(A<=B) = " << ((A<=B)?"True":"False") << endl;
   cout << "(A>B)  = " << ((A>B)? "True":"False") << endl;
   cout << "(A>=B) = " << ((A>=B)?"True":"False") << endl << endl;

   C.negate();
   cout << "C's sign is " << C.sign() << endl;
   cout << "C = " << C << endl;
   cout << endl;

   BigInteger D = A+B;
   BigInteger E = B+A;
   cout << "D = " << D << endl;
   cout << "E = " << E << endl;
   cout << "(D==E) = " << ((D==E)?"True":"False") << endl;
   BigInteger F = C + A;
   cout << "F = " << F << endl;
   cout << endl;

   BigInteger uno = BigInteger("+1");
   D += uno;
   cout << "D = " << D << endl;
   cout << endl;

   BigInteger G = A - B;
   BigInteger H = B - A;
   cout << "G = " << G << endl;
   cout << "H = " << H << endl;
   F = C - A;
   cout << "F = " << F << endl;
   cout << endl;

   H -= uno;
   cout << "H = " << H << endl;
   cout << endl;

   BigInteger I = A * B;
   BigInteger J = B * A;
   cout << "I = " << I << endl;
   cout << "J = " << J << endl;
   F = C * A;
   cout << "F = " << F << endl;
   cout << endl;

   BigInteger nada;
   H *= nada;
   cout << "H = " << H << endl;
   cout << endl;

   cout << A*B*C*D*F*G*H << endl << endl;

   cout << "A = " << A << endl;
   A.makeZero();
   cout << "A = " << A << endl;
   nada.makeZero();
   cout << "nada = " << nada << endl << endl;


   // test exceptions
   try{
      BigInteger J = BigInteger("");
   }catch( std::invalid_argument& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      BigInteger J = BigInteger("+");
   }catch( std::invalid_argument& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      BigInteger J = BigInteger("12329837492387492837492$4982379487293847");
   }catch( std::invalid_argument& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      BigInteger J = BigInteger("5298374902837409+82734098729287349827398");
   }catch( std::invalid_argument& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }

   cout << endl;

   return EXIT_SUCCESS;
}

/* Expected Output:
A = 123456789
B = 9876543210
C = 9876543210
A's sign is 1
B's sign is 1
C's sign is 1
(C==A) = True

(A==B) = False
(A<B)  = True
(A<=B) = True
(A>B)  = False
(A>=B) = False

C's sign is -1
C = -123456789

D = 9999999999
E = 9999999999
(D==E) = True
F = 0

D = 10000000000

G = -9753086421
H = 9753086421
F = -246913578

H = 9753086420

I = 1219326311126352690
J = 1219326311126352690
F = -15241578750190521

H = 0

0

A = 123456789
A = 0
nada = 0

BigInteger: Constructor: empty string
   continuing without interruption
BigInteger: Constructor: non-numeric string
   continuing without interruption
BigInteger: Constructor: non-numeric string
   continuing without interruption
BigInteger: Constructor: non-numeric string
   continuing without interruption
   */
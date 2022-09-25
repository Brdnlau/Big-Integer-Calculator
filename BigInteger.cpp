/********************************************************************************* 
* Brandon Lau, blau7
* 2022 Spring CSE101 PA6
* BigInteger.cpp 
* Implementation File for BigInteger ADT 
*********************************************************************************/
#include <iostream>
#include <string>
#include <stdexcept>
#include <math.h>

#include "List.h"
#include "BigInteger.h"

const int power = 9;
const ListElement base = pow(10, power);

// Class Constructors & Destructors ----------------------------------------
// BigInteger()
// Constructor that creates a new BigInteger in the zero state: 
// signum=0, digits=().
BigInteger::BigInteger(){
    signum = 0;
}

bool isnumber(const std::string& str){
    return str.find_first_not_of("0123456789") == std::string::npos;
}

// BigInteger()
// Constructor that creates a new BigInteger from the string s.
// Pre: s is a non-empty string consisting of (at least one) base 10 digit
// {0,1,2,3,4,5,6,7,8,9}, and an optional sign {+,-} prefix.
BigInteger::BigInteger(std::string s){
    if (s.length() <= 0){
        throw std::invalid_argument("BigInteger: Constructor: empty string");
    }
    if (!((((s[0] == '+' || s[0] == '-') && s.length() > 1)|| isdigit(s[0])) && isnumber(s.substr(1)))){
        throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
    }
    signum = 1;

    if (s[0] == '-'){
        signum = -1;
        s = s.substr(1);
    }
    else if(s[0] == '+'){
        s = s.substr(1);
    }

    while (s.length() % power != 0){
        s.insert(0, "0");
    }
    for (size_t i = s.length(); i >= power; i = i - power){
        digits.insertAfter(stol(s.substr(i - power, power)));
    }
}

// BigInteger()
// Constructor that creates a copy of N.
BigInteger::BigInteger(const BigInteger& N){
    digits = N.digits;
    signum = N.signum;
} 

// Access functions --------------------------------------------------------

// sign()
// Returns -1, 1 or 0 according to whether this BigInteger is positive, 
// negative or 0, respectively.
int BigInteger::sign() const{
    return signum;
}

// compare()
// Returns -1, 1 or 0 according to whether this BigInteger is less than N,
// greater than N or equal to N, respectively.
int BigInteger::compare(const BigInteger& N) const{
    List current = digits;
    List other = N.digits;

    if (signum == N.signum){
        if (signum == 0){
            return 0;
        }
        else if (digits.length() > N.digits.length()){
            if (signum == 1){
                return 1;
            }
            else{
                return -1;
            }
        }
        else if (digits.length() < N.digits.length()){
            if (signum == 1){
                return -1;
            }
            else{
                return 1;
            }
        }
        else{
            current.moveFront();
            other.moveFront();
            for (int i = 0; i < digits.length(); i++){
                ListElement val1 = current.moveNext();
                ListElement val2 = other.moveNext();
                if (val1 > val2){
                    if (signum == 1){
                        return 1;
                    }
                    else{
                        return -1;
                    }
                }
                else if (val1 < val2){
                    if (signum == 1){
                        return -1;
                    }
                    else{
                        return 1;
                    }
                }
            }
            return 0;
        }
    }
    else{
        if (signum == 1){
            return 1;
        }
        else if (signum == 0 && N.signum == -1){
            return 1;
        }
        else if (signum == 0 && N.signum == 1){
            return -1;
        }
        else{
            return -1;
        }
    }
}

// Manipulation procedures -------------------------------------------------
// makeZero()
// Re-sets this BigInteger to the zero state.
void BigInteger::makeZero(){
    signum = 0;
    digits.clear();
}

void negateList(List& L){
    List result;
    L.moveFront();
    for (int i = 0; i < L.length(); i++){
        ListElement val = L.moveNext();
        result.insertBefore(val * -1);
    }
    L = result;
}

// negate()
// If this BigInteger is zero, does nothing, otherwise reverses the sign of 
// this BigInteger positive <--> negative. 
void BigInteger::negate(){
    if (signum != 0){
        signum *= -1;
    }
}

// BigInteger Arithmetic operations ----------------------------------------
void sumList(List& S, List A, List B, int sgn){
    List result;
    A.moveBack();
    B.moveBack();

    while (A.position() != 0 || B.position() != 0){
        ListElement val1 = 0, val2 = 0;
        if (A.position() != 0){
            val1 = A.movePrev();
        }
        if (B.position() != 0){
            val2 = B.movePrev();
        }
        result.insertAfter(val1 + sgn * val2);
    }
    S = result;
}

int normalizeList(List& L){
    List result;
    int signum = 1;
    L.moveBack();
    ListElement carry = 0;
    while (L.position() != 0){
        ListElement val = L.movePrev();
        if (val + carry >= base && L.position() != 0){
            result.insertAfter((val + carry) % base);
            carry = (val + carry) / base;
        }
        else if (val + carry < 0 && L.position() != 0){
            result.insertAfter(((val + carry) % base + base) % base);
            carry = ((val + carry) - (((val + carry) % base + base) % base)) / base;
        }
        else{
            result.insertAfter(val + carry);
            carry = 0;
        }
    }
    
    if (result.front() < 0){
        signum = -1;
        negateList(result); 
        normalizeList(result);
    }
    else if (result.front() >= base){
        while (result.front() >= base){
            ListElement val = result.peekNext();
            result.setAfter(val % base);
            result.insertAfter(val / base);
        }
    }
    else if (result.front() == 0){
        while (result.front() == 0){
            result.eraseAfter();
            if (result.length() == 0){
                signum = 0;
                break;
            }
        }
    }
    L = result;
    return signum;
}

// add()
// Returns a BigInteger representing the sum of this and N.
BigInteger BigInteger::add(const BigInteger& N) const{
    BigInteger sum;
    if (signum == -1 || N.signum == -1){
        List current = digits;
        List other = N.digits;
        if (signum == -1){
            negateList(current);
        }
        if (N.signum == -1){
            negateList(other);
        }
        sumList(sum.digits, current, other, 1);
    }
    else{
        sumList(sum.digits, digits, N.digits, 1);
    }
    sum.signum = normalizeList(sum.digits);
    return sum;
}

// sub()
// Returns a BigInteger representing the difference of this and N.
BigInteger BigInteger::sub(const BigInteger& N) const{
    BigInteger diff;
    if (digits == N.digits && signum == N.signum){
        return diff;
    }
    if (signum == -1 || N.signum == -1){
        List current = digits;
        List other = N.digits;
        if (signum == -1){
            negateList(current);
        }
        if (N.signum == -1){
            negateList(other);
        }
        sumList(diff.digits, current, other, -1);
    }
    else{
        sumList(diff.digits, digits, N.digits, -1);
    }
    diff.signum = normalizeList(diff.digits);
    return diff;
}

// shiftList()
// Prepends p zero digits to L, multiplying L by base^p. Used by mult().
void shiftList(List& L, int p){
    List result;
    for (int i = 0; i < p; i++){
        result.insertAfter(0);
    }
    L = L.concat(result);
}

// scalarMultList()
// Multiplies L (considered as a vector) by m. Used by mult().
void scalarMultList(List& L, ListElement m){
    if (m == 1){
        return;
    }
    List result;
    L.moveFront();
    for (int i = 0; i < L.length(); i++){
        ListElement val = L.moveNext();
        result.insertBefore(val * m);
    }
    L = result;
}

// mult()
// Returns a BigInteger representing the product of this and N. 
BigInteger BigInteger::mult(const BigInteger& N) const{
    BigInteger result;
    List other = N.digits;
    other.moveBack();
    if (signum == 0 || N.signum == 0){
        return result;
    }
    for (int i = 0; i < other.length(); i++){
        ListElement val = other.movePrev();
        List current = digits;
        scalarMultList(current, val);
        shiftList(current, i);
        sumList(result.digits, result.digits, current, 1);
        normalizeList(result.digits);
    }
    if ((signum == -1 && N.signum != -1) || (N.signum == -1 && signum != -1)){
        result.signum = -1;
    }
    else{
        result.signum = 1;
    }
    return result;
}

// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this BigInteger consisting of its
// base 10 digits. If this BigInteger is negative, the returned string 
// will begin with a negative sign '-'. If this BigInteger is zero, the
// returned string will consist of the character '0' only.
std::string BigInteger::to_string(){
    std::string s = "";
    if (signum == -1){
        s.insert(0, "-");
    }
    else if (digits.length() == 0){
        s = "0";
        return s;
    }
    digits.moveFront();
    for (int i = 0; i < digits.length(); i++){
        std::string val = std::to_string(digits.moveNext());
        while (val.length() < power && digits.position() != 1){
            val.insert(0, "0");
        }
        s += val;
    }
    if (s[0] == '+' || s[0] == '-'){
        while (s[1] == '0'){
            s.erase(1, 1);
        }
    }
    return s;
}


// Overriden Operators -----------------------------------------------------
// operator<<()
// Inserts string representation of N into stream.
std::ostream& operator<<( std::ostream& stream, BigInteger N ){
    return stream << N.BigInteger::to_string();
}

// operator==()
// Returns true if and only if A equals B. 
bool operator==( const BigInteger& A, const BigInteger& B ){
    if (A.compare(B) == 0){
        return true;
    }
    return false;
}

// operator<()
// Returns true if and only if A is less than B. 
bool operator<( const BigInteger& A, const BigInteger& B ){
    if (A.compare(B) == -1){
        return true;
    }
    return false;
}

// operator<=()
// Returns true if and only if A is less than or equal to B. 
bool operator<=( const BigInteger& A, const BigInteger& B ){
    if (A.compare(B) == -1 || A.compare(B) == 0){
        return true;
    }
    return false;
}

// operator>()
// Returns true if and only if A is greater than B. 
bool operator>( const BigInteger& A, const BigInteger& B ){
    if (A.compare(B) == 1){
        return true;
    }
    return false;
}

// operator>=()
// Returns true if and only if A is greater than or equal to B. 
bool operator>=( const BigInteger& A, const BigInteger& B ){
    if (A.compare(B) == 1 || A.compare(B) == 0){
        return true;
    }
    return false;
}

// operator+()
// Returns the sum A+B. 
BigInteger operator+( const BigInteger& A, const BigInteger& B ){
    return A.add(B);
}


// operator+=()
// Overwrites A with the sum A+B. 
BigInteger operator+=( BigInteger& A, const BigInteger& B ){
    A = A.add(B);
    return A;
}

// operator-()
// Returns the difference A-B. 
BigInteger operator-( const BigInteger& A, const BigInteger& B ){
    return A.sub(B);
}

// operator-=()
// Overwrites A with the difference A-B. 
BigInteger operator-=( BigInteger& A, const BigInteger& B ){
    A = A.sub(B);
    return A;
}

// operator*()
// Returns the product A*B. 
BigInteger operator*( const BigInteger& A, const BigInteger& B ){
    return A.mult(B);
}

// operator*=()
// Overwrites A with the product A*B. 
BigInteger operator*=( BigInteger& A, const BigInteger& B ){
    A = A.mult(B);
    return A;
}
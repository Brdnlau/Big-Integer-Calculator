/********************************************************************************* 
* Brandon Lau, blau7
* 2022 Spring CSE101 PA6
* Arithmetic.cpp 
* Client Module for BigInteger ADT 
*********************************************************************************/
#include <iostream>
#include "BigInteger.h"
#include <fstream>

int main(int argc, char* argv[]){
        if(argc < 2){
                std::cerr << "Usage: ./Arithmetic <inputfile> <outputfile>" << std::endl;
                return(EXIT_FAILURE);
        }

        BigInteger A,B,C,D,E,F;

        std::ifstream infile;
        infile.open(argv[1]);
        std::string s;
        getline(infile, s);
        A = BigInteger(s);
        getline(infile, s);
        getline(infile, s);
        B = BigInteger(s);
        infile.close();

        std::ofstream outfile;
        outfile.open(argv[2]);
        outfile << A << "\n" << std::endl;
        outfile << B << "\n" << std::endl;
        outfile << A+B << "\n" << std::endl;
        outfile << A-B << "\n" << std::endl;
        outfile << A-A << "\n" << std::endl;
        std::string a = "3";
        std::string b = "2";
        C = BigInteger(a);
        D = BigInteger(b);
        outfile << (C*A) - (D*B) << "\n" << std::endl;
        outfile << A*B << "\n" << std::endl;
        outfile << A*A << "\n" << std::endl;
        outfile << B*B << "\n" << std::endl;
        a = "9";
        b = "16";
        E = BigInteger(a);
        F = BigInteger(b);
        A = A*A*A*A;
        B = B*B*B*B*B;
        outfile << (E*A)+(B*F) << std::endl;
        outfile.close();
}
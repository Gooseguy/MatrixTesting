//
//  main.cpp
//  MatrixTesting
//
//  Created by Christian Cosgrove on 9/15/14.
//  Copyright (c) 2014 Test. All rights reserved.
//


#include "Matrix.h"
#include <iostream>

int main(int argc, const char * argv[])
{
    
    Matrix matrix1(std::vector<double>{0,1,2,3000,4,5},0);
    Matrix matrix2(6);
    for (int i = 0; i<matrix1.elements.size();++i)
    {
        matrix1.elements[i]=i;
        matrix2.elements[i] = 6*6-i;
    }
    matrix1.Print(); std::cout << "\n\n";
//    matrix2.Print(); std::cout << "\n\n";
    Matrix q(6),r(6);
    matrix1.QRHouseholder(q,r);
    q.Print();
//    matrix1.Print(); std::cout << std::endl;
////    matrix1.QREig(100);
////    matrix1.Print();
//    matrix1.QRHouseholder(q,r);
//    q.Print();
//    std::cout << std::endl;
//    r.Print();
//
    //matrix1.Print(); std::cout << std::endl; matrix2.Print();std::cout << std::endl;
    //(matrix1 * matrix2).Print();
    
    return 0;
}


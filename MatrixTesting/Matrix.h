#pragma once
//
//  Matrix.h
//  MatrixTesting
//
//  Created by Christian Cosgrove on 9/15/14.
//  Copyright (c) 2014 Test. All rights reserved.
//
#include <vector>


//class for a square matrix

class Matrix
{
public:
    const unsigned int WIDTH;
    Matrix (unsigned int width);
    Matrix(const Matrix& matrix);
    Matrix(const std::vector<double>& diag, int diagPos);
    std::vector<double> elements;
    void Print();
    inline double GetElement(unsigned int row, unsigned int column);
    inline unsigned int GetIndex(unsigned int row, unsigned int column);
    Matrix operator+(const Matrix& b);
    Matrix operator-(const Matrix& b);
    Matrix operator*(const double& a);
    Matrix operator/(const double& k);
    Matrix& operator=(const Matrix& m);
    Matrix operator*(Matrix& b);
    void QR(Matrix& q, Matrix& r); // Modified Gram-Schmit orthogonalization
    void QRHouseholder(Matrix& q, Matrix& r); // Householder rotation QR decomposition
    void QREig(unsigned int iterations);
};

double Matrix::GetElement(unsigned int row, unsigned int column)
{
    return elements[column + WIDTH*row];
}
unsigned int Matrix::GetIndex(unsigned int row, unsigned int column)
{
    return column + WIDTH * row;
}


//
//  Matrix.cpp
//  MatrixTesting
//
//  Created by Christian Cosgrove on 9/15/14.
//  Copyright (c) 2014 Test. All rights reserved.
//

#include "Matrix.h"
#include <iostream>
#include <string>
#include<iomanip>
#include <limits>
#include <cmath>


Matrix::Matrix(unsigned int width) : WIDTH(width), elements(WIDTH*WIDTH)
{
    for (int i = 0; i<width;++i) elements[GetIndex(i, i)]=1;
}

Matrix::Matrix(const Matrix& matrix) : WIDTH(matrix.WIDTH), elements(matrix.elements)
{
    
}
//initialize with a diagonal
Matrix::Matrix(const std::vector<double>& diag, int diagPos) : WIDTH(diag.size() + abs(diagPos)),elements(WIDTH*WIDTH)
{
    for (int i = 0; i<WIDTH - abs(diagPos);++i)
    {
        if (diagPos > 0)
            elements[GetIndex(i, i+diagPos)]=diag[i];
        else
            elements[GetIndex(i-diagPos, i)]=diag[i];
    }
}

void Matrix::Print()
{
    std::string output;
    for (int i = 0; i<WIDTH;++i)
    {
        for (int j = 0; j<WIDTH;++j)
        {
            std::cout << std::setprecision(3) << GetElement(i,j) << " ";
        }
        std::cout<<std::endl;
    }
    }

Matrix Matrix::operator+(const Matrix& b)
{
    if (WIDTH!=b.WIDTH) throw std::logic_error("Matrix sizes incompatible!");
    Matrix ret(*this);
    for (int i = 0; i<WIDTH*WIDTH;++i) ret.elements[i]+=b.elements[i];
    return ret;
}
Matrix Matrix::operator-(const Matrix& b)
{
    if (WIDTH!=b.WIDTH) throw std::logic_error("Matrix sizes incompatible!");
    Matrix ret(*this);
    for (int i = 0; i<WIDTH*WIDTH;++i) ret.elements[i]-=b.elements[i];
    return ret;
}
Matrix Matrix::operator*(const double& k)
{
    Matrix ret(*this);
    for (int i = 0; i<WIDTH*WIDTH; ++i) ret.elements[i]*=k;
    return ret;
}
Matrix Matrix::operator/(const double& k)
{
    Matrix ret(*this);
    for (int i = 0; i<WIDTH*WIDTH; ++i) ret.elements[i]/=k;
    return ret;
}

Matrix& Matrix::operator=(const Matrix& matrix)
{
    if (WIDTH!=matrix.WIDTH) throw std::logic_error("Matrix sizes incompatible!");
    for (int i = 0; i<elements.size();++i) elements[i] = matrix.elements[i];
    return *this;
}

Matrix Matrix::operator*(Matrix& b)
{
    if (WIDTH!=b.WIDTH) throw std::logic_error("Matrix sizes incompatible!");
    Matrix c(WIDTH);
    for (int i = 0; i<WIDTH;++i)
    {
        for (int j = 0; j<WIDTH;++j){
            double s=0;
            for (int k = 0; k<WIDTH;++k)
            {
                s+=GetElement(i,k)*b.GetElement(k,j);
            }
            c.elements[GetIndex(i,j)]=s;
        }
    }
    return c;
}

//http://www.inf.ethz.ch/personal/gander/papers/qrneu.pdf
//Modified Gram-Schmit algorithm
void Matrix::QR(Matrix &q, Matrix &r)
{
    for (int k = 0; k<WIDTH;++k)
    {
        double s=0;
        for (int j=0;j<WIDTH;++j)
            s+=GetElement(j, k)*GetElement(j, k);
        r.elements[r.GetIndex(k,k)]=sqrt(s);
        for (int j=0;j<WIDTH;++j) q.elements[q.GetIndex(j, k)]=GetElement(j,k)/r.GetElement(k, k);
        for (int i = k+1;i<WIDTH;++i)
        {
            s=0;
            for (int j=0;j<WIDTH;++j)s+=GetElement(j,k)*q.GetElement(j,k);
            r.elements[r.GetIndex(k,i)]=s;
            for (int j = 0; j<WIDTH;++j) elements[GetIndex(j,i)]-=r.elements[GetIndex(k,i)]*q.GetElement(j,k);
        }
    }
}

void Matrix::QREig(unsigned int iterations)
{
    Matrix a(WIDTH);
    Matrix q(WIDTH), r(WIDTH);
    for (unsigned int i = 0; i<iterations;++i)
    {
        a.QRHouseholder(q,r);
        //a = r * q;
    }
}


void Matrix::QRHouseholder(Matrix& q, Matrix& r)
{
    std::vector<double> d(WIDTH);
    for (int j = 0; j<WIDTH;++j)
    {
        double s = 0;
        for (int i = j; i<WIDTH;++i) s+=GetElement(i,j)*GetElement(i,j);
        s=sqrt(s);
        d[j] = (GetElement(j,j) > 0) ? -s : s;
        double fak = sqrt(s * (s + std::abs(GetElement(j,j))));
        elements[GetIndex(j,j)]-=d[j];
        for (int k = j;k<WIDTH;++k)elements[GetIndex(k,j)]/=fak;
        for (int i = j+1; i<WIDTH;++i)
        {
            s=0;
            for (int k = j; k<WIDTH;++k) s+=GetElement(k,j)*GetElement(k,i);
            for (int k = j; k<WIDTH;++k) elements[GetIndex(k,i)]-=GetElement(k,j)*s;
            
        }
        d[j] = std::abs(d[j]); // ensure positive-definiteness
    }
    for (double k : d) std::cout << k << std::endl;
    r=Matrix(d,0);
    for (int j = 0; j<WIDTH;++j) for (int i = j+1;i<WIDTH;++i) r.elements[GetIndex(j,i)] =std::abs(GetElement(j,i));
    r.Print();
    for (int i = 0; i<WIDTH;++i)
    {
        std::vector<double> y(WIDTH);
        y[i]=1.0;
        for (int j = WIDTH-1; j>=0;--j)
        {
            double s=0;
            for (int k = j;k<WIDTH;++k) { s+=GetElement(j,k)*y[k]; std::cout << GetElement(k, j) << " "; } for (int k = 0; k<j;++k) std::cout << " ";
            for (int k = j;k<WIDTH;++k) y[k]+=GetElement(j,k)*s;
            std::cout << std::endl;
        }
        for (int j = 0; j<WIDTH;++j) q.elements[GetIndex(i,j)]=y[j];
    }
    //(r * q).Print();
    //q.Print();
    std::cout << "\n\n";
    //Print();
    //elements=(q * r).elements;
    //(q * r).Print();
}

//void Matrix::QR(Matrix &q, Matrix &r)
//{
//    for (int k = 0; k<WIDTH;++k)
//    {
//        double s=0;
//        for (int j=0;j<WIDTH;++j)
//            s+=GetElement(j, k)*GetElement(j, k);
//        r.elements[r.GetIndex(k,k)]=sqrt(s);
//        for (int j=0;j<WIDTH;++j) q.elements[q.GetIndex(j, k)]=GetElement(j,k)/r.GetElement(k, k);
//        for (int i = k+1;i<WIDTH;++i)
//        {
//            s=0;
//            for (int j=0;j<WIDTH;++j)s+=GetElement(j,k)*q.GetElement(j,k);
//            r.elements[r.GetIndex(k,i)]=s;
//            for (int j = 0; j<WIDTH;++j) elements[GetIndex(j,i)]-=r.elements[GetIndex(k,i)]*q.GetElement(j,k);
//        }
//    }
//}
#ifndef MATRICA_H
#define MATRICA_H

#include "lista.h" //uključuje algorithm i using namespace std, i to preko "lista.cpp"
#include <iostream>
#include <vector>

class Matrica{
    Lista<pair<int, Lista<pair<int, double>>>> M;
    int broj_redova, broj_kolona;

    void init(const int &broj_redova, const int &broj_kolona);
public:
    Matrica(const Matrica &kopija);
    Matrica& operator=(const Matrica &rhs);
    ~Matrica();
    Matrica(Matrica &&kopija);
    Matrica& operator=(Matrica &&rhs);
    Matrica(const int &broj_redova, const int &broj_kolona);
    Matrica(const int &broj_redova, const int &broj_kolona, vector<pair<pair<int, int>, double>> elementi);

    double getElement(const int &i, const int &j) const;

    Matrica friend operator+(const Matrica &A, const Matrica &B);
    Matrica friend operator*(const double &broj, const Matrica &A);
    Matrica friend operator*(const Matrica &A, const double &broj);
    Matrica friend operator-(const Matrica &A, const Matrica &B);
    Matrica friend operator*(const Matrica &A, const Matrica &B);
    Matrica friend operator^(const Matrica &A, const int &stepen);
    Matrica friend operator-(const Matrica &A); //tj.: -A
    Matrica friend operator*(const Matrica &A); //operator transponovanja

    Matrica& operator+=(const Matrica &A);
    Matrica& operator*=(const double &broj);
    Matrica& operator-=(const Matrica &A);
    Matrica& operator*=(const Matrica &A);
    Matrica& operator^=(const int &stepen);

    friend ostream& operator<<(ostream &cout, const Matrica &A);
};

#endif // MATRICA_H

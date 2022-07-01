#ifndef LISTA_CPP
#define LISTA_CPP

#include "lista.h"
#include <algorithm>

using namespace std;

template<typename T>
void Lista<T>::init(){
    glava=new Cvor(T());
    rep=new Cvor(T(), glava);
    glava->sljedeci=rep;
    broj_elemenata=0;
}

template<typename T>
Lista<T>::Lista(){
    init();
}

template<typename T>
Lista<T>::Lista(const int &n, const T &element){
    init();
    for(int i=0; i<n; i++) Push_Front(element);
}

template<typename T>
Lista<T>::Lista(const Lista<T> &kopija){
    init();
    for(auto it=kopija.Begin(); it!=kopija.End(); it++) Push_Back(*it);
}

template<typename T>
Lista<T>& Lista<T>::operator=(const Lista<T> &rhs){
    if(this==&rhs) return *this;
    Clear();
    for(auto it=rhs.Begin(); it!=rhs.End(); it++) Push_Back(*it);
    return *this;
}

template<typename T>
Lista<T>::~Lista(){
    while(Size()>0) Pop_Back();
    delete glava;
    delete rep;
}

template<typename T>
Lista<T>::Lista(Lista<T> &&kopija) : broj_elemenata(kopija.broj_elemenata), glava(kopija.glava), rep(kopija.rep) {
    kopija.broj_elemenata=0;
    kopija.glava=nullptr;
    kopija.rep=nullptr;
}

template<typename T>
Lista<T>& Lista<T>::operator=(Lista<T> &&rhs){
    swap(glava, rhs.glava);
    swap(rep, rhs.rep);
    swap(broj_elemenata, rhs.broj_elemenata);
    return *this;
}

template<typename T>
int Lista<T>::Size() const {
    return broj_elemenata;
}

template<typename T>
bool Lista<T>::Empty() const {
    return Size()==0;
}

template<typename T>
typename Lista<T>::Iterator Lista<T>::Insert(Iterator pozicija, const T &element){
    pozicija.pok->prethodni->sljedeci=new Cvor(element, pozicija.pok->prethodni, pozicija.pok);
    pozicija.pok->prethodni=pozicija.pok->prethodni->sljedeci;
    broj_elemenata++;
    return Iterator(pozicija.pok->prethodni);
}

template<typename T>
void Lista<T>::Push_Front(const T &element){
    Insert(Begin(), element);
}

template<typename T>
void Lista<T>::Push_Back(const T &element){
    Insert(End(), element);
}

template<typename T>
typename Lista<T>::Iterator Lista<T>::Erase(Iterator pozicija){
    Iterator za_vracanje(pozicija.pok->sljedeci);
    pozicija.pok->prethodni->sljedeci=pozicija.pok->sljedeci;
    pozicija.pok->sljedeci->prethodni=pozicija.pok->prethodni;
    delete pozicija.pok;
    broj_elemenata--;
    return za_vracanje;
}

template<typename T>
void Lista<T>::Pop_Front(){
    Erase(Begin());
}

template<typename T>
void Lista<T>::Pop_Back(){
    Erase(--End());
}

template<typename T>
void Lista<T>::Clear(){
    while(Size()>0) Pop_Back();
}

#endif // LISTA_CPP

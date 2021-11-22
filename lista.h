#ifndef LISTA_H
#define LISTA_H

template<typename T>
class Lista{
    struct Cvor{
        T element;
        Cvor *prethodni;
        Cvor *sljedeci;
        Cvor(const T &element, Cvor *prethodni=nullptr, Cvor *sljedeci=nullptr) : element(element), prethodni(prethodni),
                                                                                  sljedeci(sljedeci) {}
    };
    int broj_elemenata;
    Cvor *glava;
    Cvor *rep;

    void init();
public:
    class Const_Iterator{
    protected:
        Cvor *pok;
    public:
        Const_Iterator(Cvor *pok=nullptr) : pok(pok) {}
        T& operator*() const { return pok->element; }//bez & ne rade fje i operatori koji kao parametar imaju: const Matrica &
        Const_Iterator operator++(int){
            Const_Iterator za_vracanje(*this);
            pok=pok->sljedeci;
            return za_vracanje;
        }
        Const_Iterator operator++(){
            pok=pok->sljedeci;
            return *this;
        }
        Const_Iterator operator--(int){
            Const_Iterator za_vracanje(*this);
            pok=pok->prethodni;
            return za_vracanje;
        }
        Const_Iterator operator--(){
            pok=pok->prethodni;
            return *this;
        }
        bool friend operator==(Const_Iterator it1, Const_Iterator it2){
            return it1.pok==it2.pok;
        }
        bool friend operator!=(Const_Iterator it1, Const_Iterator it2){
            return !(it1==it2);
        }
        friend class Lista<T>;
    };
    class Iterator : public Const_Iterator{
    public:
        Iterator(Cvor *pok=nullptr){ this->pok=pok; }
        T& operator*(){ return this->pok->element; }
        Iterator operator++(int){
            Iterator za_vracanje(*this);
            this->pok=this->pok->sljedeci;
            return za_vracanje;
        }
        Iterator operator++(){
            this->pok=this->pok->sljedeci;
            return *this;
        }
        Iterator operator--(int){
            Iterator za_vracanje(*this);
            this->pok=this->pok->prethodni;
            return za_vracanje;
        }
        Iterator operator--(){
            this->pok=this->pok->prethodni;
            return *this;
        }
    };

    Const_Iterator Begin() const { return glava->sljedeci; }
    Const_Iterator End() const { return rep; }
    Iterator Begin(){ return glava->sljedeci; }
    Iterator End(){ return rep; }

    Lista();
    Lista(const int &n, const T &element);
    Lista(const Lista<T> &kopija);
    Lista<T>& operator=(const Lista<T> &rhs);
    ~Lista();
    Lista(Lista<T> &&kopija);
    Lista<T>& operator=(Lista<T> &&rhs);

    int Size() const;
    bool Empty() const;
    Iterator Insert(Iterator pozicija, const T &element);
    void Push_Front(const T &element);
    void Push_Back(const T &element);
    Iterator Erase(Iterator pozicija);
    void Pop_Front();
    void Pop_Back();
    void Clear();
};

#include "lista.cpp"

#endif // LISTA_H

#include "matrica.h"

void Matrica::init(const int &broj_redova, const int &broj_kolona){
    this->broj_redova=broj_redova;
    this->broj_kolona=broj_kolona;
}

Matrica::Matrica(const Matrica &kopija) : M(kopija.M),//poziva se konstruktor kopije za listu
                                        broj_redova(kopija.broj_redova), broj_kolona(kopija.broj_kolona) {}

Matrica& Matrica::operator=(const Matrica &rhs){
    if(this==&rhs) return *this;
    init(rhs.broj_redova, rhs.broj_kolona);
    M=rhs.M;//poziva se operator= za listu
    return *this;
}

Matrica::~Matrica(){
    M.Clear();
    this->broj_redova=0;
    this->broj_kolona=0;
}

Matrica::Matrica(Matrica &&kopija) : M(kopija.M),//poziva se pomjerajuci konstruktor kopije za listu
                                   broj_redova(kopija.broj_redova), broj_kolona(kopija.broj_kolona) {}

Matrica& Matrica::operator=(Matrica &&rhs){
    init(rhs.broj_redova, rhs.broj_kolona);
    M=rhs.M;//poziva se pomjerajuci operator= za listu
    return *this;
}

Matrica::Matrica(const int &broj_redova, const int &broj_kolona){
    init(broj_redova, broj_kolona);
}

bool kriterij(const pair<pair<int,int>,double> &a, const pair<pair<int,int>,double> &b){
    if(a.first.first>b.first.first) return false;
    if(a.first.first==b.first.first and a.first.second>b.first.second) return false;
    return true;
}

Matrica::Matrica(const int &broj_redova, const int &broj_kolona, vector<pair<pair<int, int>, double>> elementi){
    init(broj_redova, broj_kolona);
    if(elementi.size()==0) return;
    sort(elementi.begin(), elementi.end(), kriterij);
    Lista<pair<int,double>> red;
    red.Push_Back(make_pair(elementi[0].first.second, elementi[0].second));
    for(unsigned i=1; i<elementi.size(); i++){
        if(elementi[i].first.first!=elementi[i-1].first.first){
            M.Push_Back(make_pair(elementi[i-1].first.first, red));
            red.Clear();
            red.Push_Back(make_pair(elementi[i].first.second, elementi[i].second));
        }
        else red.Push_Back(make_pair(elementi[i].first.second, elementi[i].second));
    }
    M.Push_Back(make_pair(elementi[elementi.size()-1].first.first,red));
}

double Matrica::getElement(const int &i, const int &j) const {
    auto it1(M.Begin());
    bool nasao_red(false);
    for(auto it=M.Begin(); it!=M.End(); it++){
        if(i==(*it).first){
            it1=it;
            nasao_red=true;
            break;
        }
        else if(i<(*it).first) return 0.0;
    }
    if(nasao_red){
        for(auto it2=(*it1).second.Begin(); it2!=(*it1).second.End(); it2++){
            if(j==(*it2).first) return (*it2).second;
            else if(j<(*it2).first) return 0.0;
        }
    }
    return 0.0;
}

Matrica operator+(const Matrica &A, const Matrica &B){
    if(A.broj_redova!=B.broj_redova or A.broj_kolona!=B.broj_kolona) throw "Nemoguce sabiranje matrica razlicitih dimenzija";
    Matrica za_vracanje(A);
    for(auto IT2=B.M.Begin(); IT2!=B.M.End(); IT2++){
        bool sabiranje_reda(false);
        auto IT1(za_vracanje.M.End());
        for(auto it=za_vracanje.M.Begin(); it!=za_vracanje.M.End(); it++){
            if((*IT2).first==(*it).first){
                sabiranje_reda=true;
                IT1=it;
                break;
            }
            else if((*IT2).first<(*it).first){
                IT1=it;
                break;
            }
        }
        if(sabiranje_reda){
            auto IT((*IT1).second.Begin());
            for(auto it2=(*IT2).second.Begin(); it2!=(*IT2).second.End(); it2++){
                bool dodat(false);
                for(auto it1=IT; it1!=(*IT1).second.End(); it1++){
                    if((*it2).first==(*it1).first){
                        IT=it1;
                        if((*it1).second+(*it2).second==0) (*IT1).second.Erase(it1);
                        else (*it1).second+=(*it2).second;
                        dodat=true;
                        break;
                    }
                    else if((*it2).first<(*it1).first){
                        (*IT1).second.Insert(it1, *it2);
                        dodat=true;
                        break;
                    }
                }
                if(!dodat) (*IT1).second.Push_Back(*it2);
            }
            if((*IT1).second.Size()==0) za_vracanje.M.Erase(IT1);
        }
        else za_vracanje.M.Insert(IT1,*IT2);
    }
    return za_vracanje;
}

Matrica operator*(const double &broj, const Matrica &A){
    if(!broj) return Matrica(A.broj_redova, A.broj_kolona);//množenje nulom
    Matrica za_vracanje(A);
    for(auto it1=za_vracanje.M.Begin(); it1!=za_vracanje.M.End(); it1++){
        for(auto it2=(*it1).second.Begin(); it2!=(*it1).second.End(); it2++){
            (*it2).second*=broj;
        }
    }
    return za_vracanje;
}

Matrica operator*(const Matrica &A, const double &broj){
    return broj*A;
}

Matrica operator-(const Matrica &A, const Matrica &B){
    if(A.broj_redova!=B.broj_redova or A.broj_kolona!=B.broj_kolona) throw "Nemoguce oduzimanje matrica razlicitih dimenzija";
    return Matrica(A+(-1*B));
}

Matrica operator*(const Matrica &A, const Matrica &B){
    if(A.broj_kolona!=B.broj_redova) throw "Nemoguce pomnoziti matrice datih dimenzija";
    Matrica za_vracanje(A.broj_redova, B.broj_kolona);
    for(auto it1=A.M.Begin(); it1!=A.M.End(); it1++){
        bool dodajRed(false);
        pair<int, Lista<pair<int, double>>> red;
        red.first=(*it1).first;
        for(int j=0; j<B.broj_kolona; j++){//jer ne znamo koje kolone imamo u (*it1).first-om redu u Matrici B
            double vrijednost(0);
            for(auto it2=(*it1).second.Begin(); it2!=(*it1).second.End(); it2++){
                vrijednost+=(*it2).second*B.getElement((*it2).first, j);
            }
            if(vrijednost){//ako vrijednost nije nula
                dodajRed=true;
                red.second.Push_Back(make_pair(j, vrijednost));
            }
        }
        if(dodajRed) za_vracanje.M.Push_Back(red);
    }
    return za_vracanje;
}

Matrica operator^(const Matrica &A, const int &stepen){
    if(A.broj_redova!=A.broj_kolona) throw "Moguce je stepenovati samo kvadratne matrice";
    if(stepen<0) throw "Matrica se može stepenovati samo nenegativnim brojem";
    Matrica za_vracanje(A.broj_redova, A.broj_kolona);
    if(stepen==0){//pravimo jediničnu matrica
        for(int i=0; i<za_vracanje.broj_redova; i++){
            Lista<pair<int,double>> red;
            red.Push_Back(make_pair(i, 1));
            za_vracanje.M.Push_Back(make_pair(i,red));
        }
        return za_vracanje;
    }
    else if(stepen==1) return A;
    else if(stepen%2==0) return (A*A)^(stepen/2);
    return ((A*A)^((stepen-1)/2))*A;//ako je neparan stepen
}

Matrica operator-(const Matrica &A){
    return (-1)*A;
}

Matrica operator*(const Matrica &A){
    vector<pair<pair<int, int>, double>> elementi;
    for(auto it1=A.M.Begin(); it1!=A.M.End(); it1++){
        for(auto it2=(*it1).second.Begin(); it2!=(*it1).second.End(); it2++){
            elementi.push_back(make_pair(make_pair((*it2).first,(*it1).first),(*it2).second));
        }
    }
    return Matrica(A.broj_kolona, A.broj_redova, elementi);
}

Matrica& Matrica::operator+=(const Matrica &A){
    *this=*this+A;
    return *this;
}

Matrica& Matrica::operator*=(const double &broj){
    *this=*this*broj;
    return *this;
}

Matrica& Matrica::operator-=(const Matrica &A){
    *this=*this-A;
    return *this;
}

Matrica& Matrica::operator*=(const Matrica &A){
    *this=*this*A;
    return *this;
}

Matrica& Matrica::operator^=(const int &stepen){
    *this=*this^stepen;
    return *this;
}

ostream& operator<<(ostream &cout, const Matrica &A){
    cout << A.broj_redova << " " << A.broj_kolona << endl;
    for(auto it1=A.M.Begin(); it1!=A.M.End(); it1++){
        for(auto it2=(*it1).second.Begin(); it2!=(*it1).second.End(); it2++){
            cout << "(" << (*it1).first << "," << (*it2).first << "):" << (*it2).second << " ";
        }
        cout << endl;
    }
    return cout;
}

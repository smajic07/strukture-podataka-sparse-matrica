#include "matrica.h"

int main(){
    try{ /// gdje god sam stavio komentar napisao sam šta se redom poziva, s tim da to nisam pisao za operator<<
        Matrica M(10000,10000); //konstruktor sa dva parametra pravi nula matricu
        cout << M << endl;
        Matrica M1(1000, 1000, {{{2,10},5},{{100,50},25},{{2,400},15},{{700,800},35}}); //konstruktor sa tri parametra
        cout << M1 << endl;
        Matrica M2(1000, 1000, {{{1,1},1},{{1,2},2},{{1,3},3},{{2,11},11}}); //konstruktor sa tri parametra
        cout << M2 << endl;
        cout << M1+M2 << endl; //operator+ sa dva parametra (oba instance klase Matrica)
        cout << M1-M2 << endl; //operator- sa dva parametra (oba instance klase Matrica)
        cout << (M1+=M2) << endl; //operator+= sa jednim parametrom (instanca klase Matrica)
        cout << (M1-=M2) << endl; //operator-= sa jednim parametrom (instanca klase Matrica)
        cout << M2-M2 << endl; //operator- sa dva parametra (oba instance klase Matrica)
        cout << -M2 << endl; //operator- sa jednim parametrom (instanca klase Matrica)
        cout << -M2+M2 << endl; //operator- sa jednim paramterom i operator+ sa dva parametra
        cout << M2+(-M2) << endl; //operator - sa jednim parametrom i operator+ sa dva parametra

        Matrica M3(2000, 2000, {{{0,0},1},{{0,1},2},{{1,0},3},{{1,1},4}}); //konstruktor sa tri parametra
        cout << M3 << endl;
        Matrica M4(2000, 4000, {{{0,0},5},{{0,1},6},{{1,0},7},{{1,1},8}}); //konstruktor sa tri parametra
        cout << M4 << endl;
        cout << M3*4 << endl; //operator* sa dva parametra (prvi je instanca klase Matrica, drugi je double)
        cout << 4*M3 << endl; //operator* sa dva parametra (prvi je double, drugi je instanca klase Matrica)
        cout << (M3*=4) << endl; //operator*= sa jednim parametrom (double)
        cout << M3*M4 << endl; //operator* sa dva parametra (oba instance klase Matrica)
        Matrica M5(4000, 2000, {{{0,0},1},{{1,1},5}}); //poziva se konstruktor sa 3 parametra
        cout << M5 << endl;
        cout << M5*(M3*M4) << endl; //operator* sa dva parametra i operator* sa dva parametra
        cout << (M5*=M3*M4) << endl; //operator* sa dva parametra i operator*= sa jednim parametrom (instanca klase Matrica)
        M=M3*M4; //operator* sa dva parametra i pomjerajuci operator dodjele
        cout << M << endl;

        Matrica M6(10000,10000, {{{1,100},1},{{2,10},7},{{100,50},9},{{2,400},8},{{700,800},10},{{1,2},5},
                                {{1,3},6},{{2,11},7},{{0,0},1},{{0,1},2},{{1,0},3},{{1,1},4}}); //konstruktor sa tri parametra
        cout << M6 << endl;
        cout << (M6^7) << endl; //operator^ sa dva parametra (prvi je instanca klase Matrica, drugi je int)
        cout << (M6^=7) << endl; //operator^= sa jednim parametrom (int)
        cout << *M6 << endl; //operator* sa jednim paramterom (instanca klase Matrica)
        Matrica M7(10, 10); //konstruktor sa 2 parametra pravi nula matricu
        cout << M7 << endl;
        cout << (M7^0) << endl; //operator^ sa dva parametra pravi jediničnu matricu
        cout << (M7^=0) << endl; //operator^= sa jednim parametrom pravi jediničnu matricu
        cout << *M7 << endl; //operator* sa jednim parametrom

        Matrica M8(M7*(*M7)); //operator* sa jednim parametrom i operator* sa dva parametra i pomjerajuci konstruktor kopije
        cout << M8 << endl;
        cout << M8*0 << endl; //operator* sa dva parametra
        cout << 0*M8 << endl; //operator* sa dva parametra
        cout << (M8*=0) << endl; //operator*= sa jednim parametrom

        Matrica M9(Matrica(10000,10000, {{{1,100},1},{{2,10},7},{{100,50},9},{{2,400},8},{{700,800},10},{{1,2},5}, //konstruktor sa tri parametra i
                                        {{1,3},6},{{2,11},7},{{0,0},1},{{0,1},2},{{1,0},3},{{1,1},4}})); //i pomjerajuci konstruktor kopije
        cout << M9 << endl;
        cout << (M9+=M9) << endl; //operator+= sa jednim parametrom
        cout << (M9*=M9) << endl; //operator*= sa jednim parametrom
        cout << (M9-=M9) << endl; //operator-= sa jednim parametrom
        M9=M4; //operator dodjele
        cout << M9 << endl;
        M9=Matrica(10000,10000, {{{1,100},1},{{2,10},7},{{100,50},9},{{2,400},8},{{700,800},10},{{1,2},5}, //konstruktor sa tri parametra i
                                   {{1,3},6},{{2,11},7},{{0,0},1},{{0,1},2},{{1,0},3},{{1,1},4}}); //i pomjerajuci operator dodjele
        cout << M9 << endl;
        M9=M9; //operator dodjele
        cout << M9 << endl;
        Matrica M10(M9); //konstruktor kopije
        cout << M10 << endl;

        cout << ((M10^2)^5) << endl; //operator^ sa dva parametra i operator^ sa dva parametra
        cout << Matrica(2000, 2000, {{{0,0},1},{{0,1},2},{{1,0},3},{{1,1},4}}) // konstruktor sa tri parametra i konstruktor sa tri parametra
                *Matrica(2000, 4000, {{{0,0},5},{{0,1},6},{{1,0},7},{{1,1},8}}) << endl; //i operator* sa dva parametra
        cout << Matrica(100,100, {{{1,99},1},{{2,10},7},{{99,99},9},{{2,40},8},{{70,80},10},{{1,2},5},
                                                {{1,3},6},{{2,11},7},{{0,0},1},{{0,1},2},{{1,0},3},{{1,1},4}})-(Matrica(100,100)^0) << endl;
                //konstruktor sa tri parametra i konstruktor sa tri paramtera i operator^ sa dva parametra i operator- sa dva  parametra

    }
    catch(const char *poruka){
        cout << poruka << endl;
    }

return 0;
}

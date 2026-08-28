// Tests nuestros para la función cambiarBanderita.
// Ver el archovo README.md para ayuda


#include "../ejercicios.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;

TEST(cambiarBanderitaTEST , hayBanderita){
    vector<vector<bool>> m ={
            {cMINA,cVACIA,cVACIA},
            {cVACIA,cVACIA,cVACIA},
            {cMINA,cVACIA,cMINA}
    };
    jugadas j = {};
    pos p;
    pos b1;
    pos b2;
    p = make_pair(1,1);
    b1 = make_pair(1,2);
    b2 = make_pair(1,1);
    banderitas b = {b1,b2};
    banderitas expect = {b1};
    cambiarBanderita(m,j,p,b);
    ASSERT_EQ(b,expect);
}

TEST(cambiarBanderitaTEST , noHayBanderita){
    vector<vector<bool>> m ={
            {cMINA,cVACIA,cVACIA},
            {cVACIA,cVACIA,cVACIA},
            {cMINA,cVACIA,cMINA}
    };
    jugadas j = {};
    pos p;
    pos b1;
    pos b2;
    p = make_pair(1,1);
    b1 = make_pair(1,2);
    b2 = make_pair(1,3);
    banderitas b = {b1,b2};
    banderitas expect = {b1,b2,p};
    cambiarBanderita(m,j,p,b);
    ASSERT_EQ(b,expect);
}
TEST(cambiarBanderitaTEST , noEstaEnPos){
    vector<vector<bool>> m ={
            {cMINA,cVACIA,cVACIA},
            {cVACIA,cVACIA,cVACIA},
            {cMINA,cVACIA,cMINA}
    };
    jugadas j = {};
    pos p;
    pos b1;
    pos b2;
    p = make_pair(1,1);
    b1 = make_pair(1,2);
    b2 = make_pair(1,3);
    banderitas b = {b1,b2};
    banderitas expect = {b1,b2,p};
    cambiarBanderita(m,j,p,b);
    ASSERT_EQ(b,expect);
}

TEST(cambiarBanderitaTEST , sinBanderitas){
    vector<vector<bool>> m ={
            {cMINA,cVACIA,cVACIA},
            {cVACIA,cVACIA,cVACIA},
            {cMINA,cVACIA,cMINA}
    };
    jugadas j = {};
    pos p;
    p = make_pair(1,1);
    banderitas b = {};
    banderitas expect = {p};
    cambiarBanderita(m,j,p,b);
    ASSERT_EQ(b,expect);
}

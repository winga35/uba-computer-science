// Tests nuestros para la función perdio.
// Ver el archovo README.md para ayuda

#include "../ejercicios.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;

TEST(perdioTEST , perdio){
    vector<vector<bool>> m ={
            {cMINA,cVACIA,cVACIA},
            {cVACIA,cVACIA,cVACIA},
            {cMINA,cVACIA,cMINA}
    };
    pos p1;
    pos p2;
    jugada j1;
    jugada j2;
    p1 = make_pair(1,1);
    p2 = make_pair(2,2);
    j1 = make_pair(p1, minasAdyacentes(m,p1));
    j2 = make_pair(p2, minasAdyacentes(m,p2));
    jugadas j = {j1,j2};
    bool res = perdio(m,j);
    ASSERT_TRUE(res);
}

TEST(perdioTEST , perdio2veces){
    vector<vector<bool>> m ={
            {cMINA,cVACIA,cVACIA},
            {cVACIA,cVACIA,cVACIA},
            {cMINA,cVACIA,cMINA}
    };
    pos p1;
    pos p2;
    jugada j1;
    jugada j2;
    p1 = make_pair(0,0);
    p2 = make_pair(2,2);
    j1 = make_pair(p1, minasAdyacentes(m,p1));
    j2 = make_pair(p2, minasAdyacentes(m,p2));
    jugadas j = {j1,j2};
    bool res = perdio(m,j);
    ASSERT_TRUE(res);
}

TEST(perdioTEST , noPerdio){
    vector<vector<bool>> m ={
            {cMINA,cVACIA,cVACIA},
            {cVACIA,cVACIA,cVACIA},
            {cMINA,cVACIA,cMINA}
    };
    pos p1;
    pos p2;
    jugada j1;
    jugada j2;
    p1 = make_pair(1,1);
    p2 = make_pair(2,1);
    j1 = make_pair(p1, minasAdyacentes(m,p1));
    j2 = make_pair(p2, minasAdyacentes(m,p2));
    jugadas j = {j1,j2};
    bool res = perdio(m,j);
    ASSERT_FALSE(res);
}

TEST(perdioTEST , noPerdioLargo1){
    vector<vector<bool>> m ={
            {cVACIA}
    };
    pos p1;
    jugada j1;
    p1 = make_pair(0,0);
    j1 = make_pair(p1, minasAdyacentes(m,p1));
    jugadas j = {j1};
    bool res = perdio(m,j);
    ASSERT_FALSE(res);
}

TEST(perdioTEST , sinJugadas){
    vector<vector<bool>> m ={
            {cMINA,cVACIA,cVACIA},
            {cVACIA,cVACIA,cVACIA},
            {cMINA,cVACIA,cMINA}
    };
    jugadas j = {};
    bool res = perdio(m,j);
    ASSERT_FALSE(res);
}


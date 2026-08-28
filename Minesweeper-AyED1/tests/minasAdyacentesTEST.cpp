// Tests nuestros para la función minasAdyacentes.
// Ver el archivo README.md para ayuda

#include "../ejercicios.h"
#include "../auxiliares.h"
#include "../definiciones.h"
#include "gtest/gtest.h"

using namespace std;

TEST(minasAdyacentesTest , TableroLargoUno) {
    vector<vector<bool>> m = {
            {cMINA}

    };
    pos p;
    p.first = 0;
    p.second = 0;
    int result = minasAdyacentes(m, p);
    ASSERT_EQ(result, 0);
}



TEST(minasAdyacentesTest , casoIdeal3x3){
    vector<vector<bool>> m ={
            {cMINA,cVACIA,cVACIA},
            {cVACIA,cVACIA,cVACIA},
            {cMINA,cVACIA,cMINA}
    };
    pos p;
    p.first = 1;
    p.second = 1;
    int result = minasAdyacentes(m , p );
    ASSERT_EQ(result,3);
}

TEST(minasAdyacentesTest , casoBorde) {
    vector<vector<bool>> m = {
            {cMINA,cVACIA,cVACIA},
            {cVACIA,cVACIA,cMINA},
            {cMINA,cVACIA,cMINA}
    };
    pos p;
    p.first = 0;
    p.second = 1;
    int result = minasAdyacentes(m, p);
    ASSERT_EQ(result, 2);
}

TEST(minasAdyacentesTest , casoBorde2) {
    vector<vector<bool>> m = {
            {cMINA,  cVACIA, cVACIA},
            {cVACIA, cVACIA, cMINA},
            {cMINA,  cVACIA, cMINA}
    };
    pos p;
    p.first = 0;
    p.second = 0;
    int result = minasAdyacentes(m, p);
    ASSERT_EQ(result, 0);
}

TEST(minasAdyacentesTest , casoBorde3) {
    vector<vector<bool>> m = {
            {cMINA,  cVACIA, cVACIA},
            {cVACIA, cVACIA, cMINA},
            {cMINA,  cVACIA, cMINA}
    };
    pos p;
    p.first = 0;
    p.second = 2;
    int result = minasAdyacentes(m, p);
    ASSERT_EQ(result, 1);
}

TEST(minasAdyacentesTest , casoBorde4) {
    vector<vector<bool>> m = {
            {cMINA,  cVACIA, cVACIA},
            {cVACIA, cVACIA, cMINA},
            {cMINA,  cVACIA, cMINA}
    };
    pos p;
    p.first = 2;
    p.second = 0;
    int result = minasAdyacentes(m, p);
    ASSERT_EQ(result, 0);
}

TEST(minasAdyacentesTest , casoBorde5) {
    vector<vector<bool>> m = {
            {cMINA,  cVACIA, cVACIA},
            {cVACIA, cVACIA, cMINA},
            {cMINA,  cVACIA, cMINA}
    };
    pos p;
    p.first = 2;
    p.second = 2;
    int result = minasAdyacentes(m, p);
    ASSERT_EQ(result, 1);
}

TEST(minasAdyacentesTest , TableroMasChico) {
    vector<vector<bool>> m = {
            {cMINA,  cVACIA},
            {cVACIA, cVACIA},

    };
    pos p;
    p.first = 0;
    p.second = 0;
    int result = minasAdyacentes(m, p);
    ASSERT_EQ(result, 0);
}
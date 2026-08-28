// Tests nuestros para la función jugarPlus.
// Ver el archovo README.md para ayuda

#include "../ejercicios.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;
// ┌───┬───┬───┬───┬───┐
// │ * │ * │ 2 │ 1 │ 1 │
// ├───┼───┼───┼───┼───┤
// │ 3 │ 3 │ 3 │ * │ * │
// ├───┼───┼───┼───┼───┤
// │ * │ * │ * │ * │ 1 │
// ├───┼───┼───┼───┼───┤
// │ 2 │ 3 │ 2 │ 1 │ 0 │
// ├───┼───┼───┼───┼───┤
// │ * │ 2 │ * │ 1 │ 0 │
// └───┴───┴───┴───┴───┘

tablero t1 = {
        { cMINA,  cMINA,  cVACIA, cVACIA, cVACIA },
        { cVACIA, cVACIA, cVACIA, cMINA,  cMINA },
        { cMINA, cMINA,  cMINA, cMINA, cVACIA },
        { cVACIA, cVACIA, cVACIA, cVACIA, cVACIA },
        { cMINA,  cVACIA, cMINA,  cVACIA, cVACIA },
};

tablero t1x1 = {
        {cVACIA}
};

tablero t3 = {
        { cVACIA,  cVACIA,  cVACIA, cVACIA, cMINA, cVACIA, cMINA, cVACIA, cVACIA, cMINA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cMINA, cVACIA, cVACIA, cVACIA },
        { cVACIA,  cVACIA,  cVACIA, cMINA, cVACIA, cMINA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cMINA, cVACIA, cMINA, cMINA},
        { cVACIA,  cVACIA,  cVACIA, cVACIA, cVACIA, cMINA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA },
        { cVACIA,  cMINA,  cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA },
        { cVACIA,  cVACIA,  cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cMINA, cVACIA },
        { cVACIA,  cVACIA,  cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cMINA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA },
        { cVACIA,  cVACIA,  cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cMINA, cVACIA, cVACIA, cVACIA, cVACIA, cMINA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA },
        { cVACIA,  cVACIA,  cVACIA, cMINA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA },
        { cVACIA,  cVACIA,  cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cMINA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cMINA, cVACIA },
        { cVACIA,  cVACIA,  cVACIA, cMINA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cMINA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA },
        { cVACIA,  cVACIA,  cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA },
        { cMINA,  cVACIA,  cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cMINA, cVACIA, cVACIA, cVACIA, cMINA, cMINA },
        { cVACIA,  cVACIA,  cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cMINA, cVACIA, cVACIA, cMINA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cMINA },
        { cVACIA,  cVACIA,  cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cMINA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA },
        { cMINA,  cMINA,  cVACIA, cVACIA, cVACIA, cMINA, cVACIA, cVACIA, cMINA, cVACIA, cVACIA, cMINA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA },
        { cVACIA,  cVACIA,  cMINA, cVACIA, cVACIA, cVACIA, cMINA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cMINA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA },
        { cVACIA,  cMINA,  cVACIA, cVACIA, cVACIA, cVACIA, cMINA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cMINA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA },
        { cVACIA,  cVACIA,  cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cMINA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA },
        { cVACIA,  cVACIA,  cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA, cVACIA },
        { cMINA,  cMINA,  cMINA, cMINA, cVACIA, cVACIA, cVACIA, cVACIA, cMINA, cVACIA, cVACIA, cVACIA, cVACIA, cMINA, cVACIA, cMINA, cVACIA, cMINA, cMINA, cVACIA },

};

jugadas jugadasValidas1 = {
        jugada(pos(0, 2), 2),jugada(pos(0, 3), 2)};

TEST(jugarPlusTest, testBorde) {
    jugadas j = jugadasValidas1;
    banderitas b = {};
    pos p = {4, 4};
    jugarPlus(t1, b, p, j);
    jugadas jugadasesperadas = {
            jugada(pos(0, 2), 2), jugada(pos(0, 3), 2), jugada(p, 0),
            jugada(pos(3, 3), 3), jugada(pos(3, 4), 1),jugada(pos(4, 3), 1)};

    ASSERT_EQ(j,jugadasesperadas);
}

TEST(jugarPlusTest, test2banderitas) {
    jugadas j = jugadasValidas1;
    banderitas b = {{3,3},{3,4},{1,2}};
    pos p = {4, 4};
    jugarPlus(t1, b, p, j);
    jugadas jugadasesperadas = {
            jugada(pos(0, 2), 2), jugada(pos(0, 3), 2), jugada(p, 0),
            jugada(pos(4, 3), 1),};
    // banderitas bEesperada = {{1,2}};
    ASSERT_EQ(j,jugadasesperadas);
    //ASSERT_EQ(b,bEesperada);
}


TEST(jugarPlusTest, test1){
    jugadas j = jugadasValidas1;
    banderitas b={};
    pos p={1,1};
    jugarPlus(t1,b,p,j);
    jugadas jugadasesperadas ={
            jugada(pos(0, 2), 2),jugada(pos(0, 3), 2),jugada(p,5)};
    ASSERT_EQ(j,jugadasesperadas);
}




TEST(jugarPlusTest, test3){
    jugadas j = {};
    banderitas b={};
    pos p={17,11};
    jugarPlus(t3,b,p,j);
    jugadas jugadasesperadas = {
            jugada(pos(15, 9), 1), jugada(pos(15, 10), 1), jugada(pos(15, 11), 1), jugada(pos(15, 12), 2),
            jugada(pos(16, 9), 1), jugada(pos(16, 10), 0), jugada(pos(16, 11), 0), jugada(pos(16, 12), 1), jugada(pos(16, 13), 2),
            jugada(pos(17, 9), 1), jugada(pos(17, 10), 0), jugada(pos(p), 0), jugada(pos(17, 12), 0), jugada(pos(17, 13), 1),
            jugada(pos(18, 9), 2), jugada(pos(18, 10), 0), jugada(pos(18, 11), 0), jugada(pos(18, 12), 1), jugada(pos(18, 13), 1),
            jugada(pos(19, 9), 1), jugada(pos(19, 10), 0), jugada(pos(19, 11), 0), jugada(pos(19, 12), 1)};


    ASSERT_EQ(j.size(),jugadasesperadas.size());
}

TEST(jugarPlusTest, test1x1) {
    jugadas j = {};
    banderitas b = {};
    pos p = {0, 0};
    jugarPlus(t1x1, b, p, j);
    jugadas jugadasesperadas = {
            jugada(pos(0, 0), 0)};
    ASSERT_EQ(j,jugadasesperadas);
}



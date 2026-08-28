// Tests nuestros para la función sugerir121.
// Ver el archovo README.md para ayuda

#include "../ejercicios.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;

tablero t5x5 = {
        { cMINA,  cMINA,  cVACIA, cVACIA, cVACIA },
        { cVACIA, cVACIA, cVACIA, cMINA,  cVACIA },
        { cVACIA, cVACIA, cVACIA, cVACIA, cVACIA },
        { cVACIA, cVACIA, cVACIA, cMINA, cVACIA },
        { cMINA,  cVACIA, cVACIA,  cVACIA, cVACIA },
};

tablero t121Borde = {
        { cVACIA,  cVACIA,  cVACIA, cVACIA, cVACIA },
        { cVACIA, cMINA, cVACIA, cMINA,  cVACIA },
        { cVACIA, cVACIA, cVACIA, cVACIA, cVACIA },
        { cVACIA, cVACIA, cVACIA, cMINA, cVACIA },
        { cMINA,  cVACIA, cVACIA,  cVACIA, cVACIA },
};

tablero t4 = {
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

TEST(sugerirAutomatico121, testHorizontalArribaBorde) {
    jugadas j = {jugada(pos(0, 1), 1), jugada(pos(0, 2), 2), jugada(pos(0, 3), 1)};
    tablero t = t121Borde;
    banderitas b = {{2,1},{2,3}};
    pos p = {};
    pos expected = {1,2};
    bool result = sugerirAutomatico121 (t,b,j,p);
    ASSERT_EQ(result, true);
    ASSERT_EQ(p,expected);
}

TEST(sugerirAutomatico121, testNormal) {
    jugadas j = {jugada(pos(15, 9), 1), jugada(pos(15, 10), 1), jugada(pos(15, 11), 1), jugada(pos(15, 12), 2),
                 jugada(pos(16, 9), 1), jugada(pos(16, 10), 0), jugada(pos(16, 11), 0), jugada(pos(16, 12), 1), jugada(pos(16, 13), 2),
                 jugada(pos(17, 9), 1), jugada(pos(17, 10), 0), jugada(pos(17, 11), 0), jugada(pos(17, 12), 0), jugada(pos(17, 13), 1),
                 jugada(pos(18, 9), 2), jugada(pos(18, 10), 0), jugada(pos(18, 11), 0), jugada(pos(18, 12), 1), jugada(pos(18, 13), 1),
                 jugada(pos(19, 9), 1), jugada(pos(19, 10), 0), jugada(pos(19, 11), 0), jugada(pos(19, 12), 1)};;
    tablero t = t4;
    banderitas b = {};
    pos p = {};
    pos expected = {18,8};
    bool result = sugerirAutomatico121 (t,b,j,p);
    ASSERT_EQ(result, true);
    ASSERT_EQ(p,expected);
}

//mismo test que arriba solo que modifique la posicion donde habia 121 para que no tenga.
TEST(sugerirAutomatico121, testBanderitasEnLosCandidatosAJugar) {
    jugadas j = {jugada(pos(1, 2), 1), jugada(pos(2, 2), 2), jugada(pos(3, 2), 1)};
    tablero t = t5x5;
    banderitas b = {{2,1},{2,3}};
    pos p = {};
    pos expected = {};
    bool result = sugerirAutomatico121 (t,b,j,p);
    ASSERT_EQ(result, false);
    ASSERT_EQ(p,expected);
}


//igual al test1 pero donde tendria que estar la sugerencia hay una banderita.
TEST(sugerirAutomatico121, testNormalPeroConBanderita) {
    jugadas j = {jugada(pos(15, 9), 1), jugada(pos(15, 10), 1), jugada(pos(15, 11), 1), jugada(pos(15, 12), 2),
                 jugada(pos(16, 9), 1), jugada(pos(16, 10), 0), jugada(pos(16, 11), 0), jugada(pos(16, 12), 1), jugada(pos(16, 13), 2),
                 jugada(pos(17, 9), 1), jugada(pos(17, 10), 0), jugada(pos(17, 11), 0), jugada(pos(17, 12), 0), jugada(pos(17, 13), 1),
                 jugada(pos(18, 9), 2), jugada(pos(18, 10), 0), jugada(pos(18, 11), 0), jugada(pos(18, 12), 1), jugada(pos(18, 13), 1),
                 jugada(pos(19, 9), 1), jugada(pos(19, 10), 0), jugada(pos(19, 11), 0), jugada(pos(19, 12), 1)};;
    tablero t = t4;
    banderitas b = {{18, 8}};
    pos p = {};
    pos expected = {};
    bool result = sugerirAutomatico121 (t,b,j,p);
    ASSERT_EQ(result, false);
    ASSERT_EQ(p,expected);
}

TEST(sugerirAutomatico121, testJugadasALosCostados) {
    jugadas j = {jugada(pos(15, 9), 1), jugada(pos(15, 10), 1), jugada(pos(15, 11), 1), jugada(pos(15, 12), 2),
                 jugada(pos(16, 9), 1), jugada(pos(16, 10), 0), jugada(pos(16, 11), 0), jugada(pos(16, 12), 1), jugada(pos(16, 13), 2),
                 jugada(pos(17, 9), 1), jugada(pos(17, 10), 0), jugada(pos(17, 11), 0), jugada(pos(17, 12), 0), jugada(pos(17, 13), 1),
                 jugada(pos(18, 9), 2), jugada(pos(18, 10), 0), jugada(pos(18, 11), 0), jugada(pos(18, 12), 1), jugada(pos(18, 13), 1),
                 jugada(pos(19, 9), 1), jugada(pos(19, 10), 0), jugada(pos(19, 11), 0), jugada(pos(19, 12), 1), jugada(pos(18, 8), 2) };;
    tablero t = t4;
    banderitas b = {};
    pos p = {};
    pos expected = {};
    bool result = sugerirAutomatico121 (t,b,j,p);
    ASSERT_EQ(result, false);
    ASSERT_EQ(p,expected);
}

#pragma once

#include <iostream>
#include <random>
#include <vector>
#include <string>
#include <set>
#include "Cube.h"

class RubiksCube {
public:

    RubiksCube();

    void generation();

    void R();

    void R2();

    void R_();

    void U();

    void U2();

    void U_();

    void L_();

    void L2();

    void L();

    void M_();

    void M();

    void M2();

    void Lw_();

    void Lw();

    void F_();

    void F();

    void F2();

    void S_();

    void S();

    void S2();

    void B();

    void B_();

    void B2();

    void D_();

    void D2();

    void D();

    void E_();

    void E2();

    void E();

    void Dw_();

    void Dw();

    void Dw2();

    void print();

    void read(std::istream &in);

    bool validation();

    void T();

    void lambda();

    void reverseLambda();

    void reverseLambdaLeft();

    void spear();

    void circumcisedSpear();

    void seven();

    void assembling();

    void assemblingCorners();

    void assemblingEdges();

    int cycle(int startX, int startY, int startZ, bool visit[][3][3]);

    bool edgeParity();

    bool permutationParity();

    bool differentCubes();

    bool correctCorners();


private:
    Cube cubes[3][3][3];
    char up, down, front, back, left, right;
    std::string answer = {};
    bool assemble = false;

    void upRotation(int x);

    void leftRotation(int y);

    void anticlockwiseRotation(int z);

    void moveEdges(char position);

    void moveCorners(char position);

    bool moveWrongEdge();

    bool moveWrongCorners();

    void assemblingEdge();

    void assemblingCorner();

    int colorToInt(char color) const;
};
#include "RubikCube.h"

void RubiksCube::T() {
    R();
    U();
    R_();
    U_();
    R_();
    F();
    R2();
    U_();
    R_();
    U_();
    R();
    U();
    R_();
    F_();
}

void RubiksCube::lambda() {
    R();
    U();
    R_();
    F_();
    R();
    U();
    R_();
    U_();
    R_();
    F();
    R2();
    U_();
    R_();
    U_();
}

void RubiksCube::reverseLambda() {
    R_();
    U2();
    R();
    U();
    R_();
    U2();
    L();
    U_();
    R();
    U();
    L_();
}

void RubiksCube::reverseLambdaLeft() {
    L();
    U2();
    L_();
    U_();
    L();
    U2();
    R_();
    U();
    L_();
    U_();
    R();
}

void RubiksCube::spear() {
    F();
    R();
    U_();
    R_();
    U_();
    R();
    U();
    R_();
    F_();
    R();
    U();
    R_();
    U_();
    R_();
    F();
    R();
    F_();
}

void RubiksCube::circumcisedSpear() {
    R();
    U_();
    R_();
    U_();
    R();
    U();
    R_();
    F_();
    R();
    U();
    R_();
    U_();
    R_();
    F();
    R();
}

void RubiksCube::seven() {
    R();
    U_();
    R_();
    U_();
    R();
    U();
    R();
    D();
    R_();
    U_();
    R();
    D_();
    R_();
    U2();
    R_();
    U_();
}
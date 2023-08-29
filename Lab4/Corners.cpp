#include "RubikCube.h"

void RubiksCube::assemblingCorners() {
    int count = 0;
    while ((cubes[0][0][2].getUpColor() != cubes[1][0][1].getUpColor() ||
            cubes[0][0][2].getLeftColor() != cubes[0][1][1].getLeftColor()) || moveWrongCorners()) {
        if (count >= 20)
            throw std::exception();
        assemblingCorner();
        ++count;
    }
}

void RubiksCube::assemblingCorner() {
    Cube buf = cubes[0][0][2];
    if (buf.getUpColor() == up) {
        if (buf.getLeftColor() == back)
            moveCorners('A');
        else if (buf.getLeftColor() == right)
            moveCorners('D');
        else if (buf.getLeftColor() == front)
            moveCorners('G');
    } else if (buf.getUpColor() == back) {
        if (buf.getLeftColor() == right)
            moveCorners('B');
        else if (buf.getLeftColor() == down)
            moveCorners('L');
        else if (buf.getLeftColor() == left)
            moveCorners('T');
        else if (buf.getLeftColor() == up) {
            if (!moveWrongCorners())
                throw std::exception();
        }
    } else if (buf.getUpColor() == left) {
        if (buf.getLeftColor() == up)
            moveCorners('I');
        else if (buf.getLeftColor() == front)
            moveCorners('Q');
        else if (buf.getLeftColor() == back) {
            if (!moveWrongCorners())
                throw std::exception();
        } else if (buf.getLeftColor() == down)
            moveCorners('U');
    } else if (buf.getUpColor() == right) {
        if (buf.getLeftColor() == up)
            moveCorners('C');
        else if (buf.getLeftColor() == front)
            moveCorners('E');
        else if (buf.getLeftColor() == back)
            moveCorners('K');
        else if (buf.getLeftColor() == down)
            moveCorners('O');
    } else if (buf.getUpColor() == front) {
        if (buf.getLeftColor() == up)
            moveCorners('F');
        else if (buf.getLeftColor() == left)
            moveCorners('H');
        else if (buf.getLeftColor() == right)
            moveCorners('N');
        else if (buf.getLeftColor() == down)
            moveCorners('R');
    } else if (buf.getUpColor() == down) {
        if (buf.getLeftColor() == right)
            moveCorners('J');
        else if (buf.getLeftColor() == front)
            moveCorners('M');
        else if (buf.getLeftColor() == left)
            moveCorners('P');
        else if (buf.getLeftColor() == back)
            moveCorners('S');
    } else throw std::exception();
}

void RubiksCube::moveCorners(char position) {
    switch (position) {
        case 'A':
            R();
            D_();
            circumcisedSpear();
            D();
            R_();
            break;
        case 'B':
            R_();
            spear();
            R();
            break;
        case 'C':
            R_();
            F_();
            reverseLambdaLeft();
            F();
            R();
            break;
        case 'D':
            spear();
            break;
        case 'E':
            F_();
            reverseLambdaLeft();
            F();
            break;
        case 'F':
            F();
            R();
            spear();
            R_();
            F_();
            break;
        case 'G':
            reverseLambdaLeft();
            break;
        case 'H':
            F2();
            R();
            spear();
            R_();
            F2();
            break;
        case 'I':
            F();
            spear();
            F_();
            break;
        case 'J':
            R2();
            spear();
            R2();
            break;
        case 'K':
            D_();
            R();
            spear();
            R_();
            D();
            break;
        case 'L':
            D_();
            circumcisedSpear();
            D();
            break;
        case 'M':
            D();
            R2();
            spear();
            R2();
            D_();
            break;
        case 'N':
            R();
            spear();
            R_();
            break;
        case 'O':
            circumcisedSpear();
            break;
        case 'P':
            F_();
            circumcisedSpear();
            F();
            break;
        case 'Q':
            D();
            R();
            spear();
            R_();
            D_();
            break;
        case 'R':
            D();
            circumcisedSpear();
            D_();
            break;
        case 'S':
            D_();
            R2();
            spear();
            R2();
            D();
            break;
        case 'T':
            D2();
            R();
            spear();
            R_();
            D2();
            break;
        case 'U':
            D2();
            circumcisedSpear();
            D2();
            break;
        default:
            throw std::exception();
    }
}

bool RubiksCube::moveWrongCorners() {
    up = cubes[1][0][1].getUpColor();
    front = cubes[1][1][0].getFrontColor();
    back = cubes[1][1][2].getBackColor();
    down = cubes[1][2][1].getDownColor();
    left = cubes[0][1][1].getLeftColor();
    right = cubes[2][1][1].getRightColor();
    if (cubes[0][0][0].getUpColor() != up || cubes[0][0][0].getLeftColor() != left)
        reverseLambdaLeft();
    else if (cubes[2][0][0].getUpColor() != up || cubes[2][0][0].getRightColor() != right)
        spear();
    else if (cubes[2][2][0].getDownColor() != down || cubes[2][2][0].getRightColor() != right)
        circumcisedSpear();
    else if (cubes[2][0][2].getUpColor() != up || cubes[2][0][2].getRightColor() != right)
        moveCorners('B');
    else if (cubes[0][2][0].getDownColor() != down || cubes[0][2][0].getLeftColor() != left)
        moveCorners('R');
    else if (cubes[0][2][2].getDownColor() != down || cubes[0][2][2].getLeftColor() != left)
        moveCorners('U');
    else if (cubes[2][2][2].getDownColor() != down || cubes[2][2][2].getRightColor() != right)
        moveCorners('J');
    else
        return false;
    return true;
}
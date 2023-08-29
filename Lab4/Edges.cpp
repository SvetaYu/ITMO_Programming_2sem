#include "RubikCube.h"

void RubiksCube::assemblingEdges() {
    int count = 0;
    while ((cubes[2][0][1].getUpColor() != cubes[1][0][1].getUpColor() ||
            cubes[2][0][1].getRightColor() != cubes[2][1][1].getRightColor()) || moveWrongEdge()) {
        if (count >= 20)
            throw std::exception();
        else {
            assemblingEdge();
            ++count;
        }
    }
    if (count % 2 != 0)
        seven();

}

void RubiksCube::assemblingEdge() {
    up = cubes[1][0][1].getUpColor();
    front = cubes[1][1][0].getFrontColor();
    back = cubes[1][1][2].getBackColor();
    down = cubes[1][2][1].getDownColor();
    left = cubes[0][1][1].getLeftColor();
    right = cubes[2][1][1].getRightColor();
    Cube buf = cubes[2][0][1];
    if (buf.getUpColor() == up) {
        if (buf.getRightColor() == front)
            moveEdges('B');
        else if (buf.getRightColor() == left)
            moveEdges('C');
        else if (buf.getRightColor() == back)
            moveEdges('D');
    } else if (buf.getUpColor() == back) {
        if (buf.getRightColor() == up)
            moveEdges('H');
        else if (buf.getRightColor() == right)
            moveEdges('I');
        else if (buf.getRightColor() == left)
            moveEdges('P');
        else if (buf.getRightColor() == down)
            moveEdges('T');
    } else if (buf.getUpColor() == left) {
        if (buf.getRightColor() == up)
            moveEdges('G');
        else if (buf.getRightColor() == front)
            moveEdges('N');
        else if (buf.getRightColor() == back)
            moveEdges('O');
        else if (buf.getRightColor() == down)
            moveEdges('S');
    } else if (buf.getUpColor() == right) {
        if (buf.getRightColor() == front)
            moveEdges('K');
        else if (buf.getRightColor() == back)
            moveEdges('J');
        else if (buf.getRightColor() == down)
            moveEdges('Q');
        else if (buf.getRightColor() == up) {
            if (!moveWrongEdge())
                throw std::exception();
        }
    } else if (buf.getUpColor() == front) {
        if (buf.getRightColor() == up)
            moveEdges('F');
        else if (buf.getRightColor() == left)
            moveEdges('M');
        else if (buf.getRightColor() == right)
            moveEdges('L');
        else if (buf.getRightColor() == down)
            moveEdges('R');
    } else if (buf.getUpColor() == down) {
        if (buf.getRightColor() == left)
            moveEdges('W');
        else if (buf.getRightColor() == front)
            moveEdges('V');
        else if (buf.getRightColor() == back)
            moveEdges('X');
        else if (buf.getRightColor() == right)
            moveEdges('U');
    } else throw std::exception();
}

void RubiksCube::moveEdges(char position) {
    switch (position) {
        case 'B':
            lambda();
            break;
        case 'C':
            T();
            break;
        case 'D':
            reverseLambda();
            break;
        case 'F':
            Lw_();
            reverseLambda();
            Lw();
            break;
        case 'G':
            L2();
            D();
            Lw_();
            lambda();
            Lw();
            D_();
            L2();
            break;
        case 'H':
            Lw();
            lambda();
            Lw_();
            break;
        case 'I':
            Dw2();
            L_();
            T();
            L();
            Dw2();
            break;
        case 'J':
            Dw();
            L();
            T();
            L_();
            Dw2();
            break;
        case 'K':
            Dw_();
            L_();
            T();
            L();
            Dw();
            break;
        case 'L':
            Dw2();
            L();
            T();
            L_();
            Dw2();
            break;
        case 'M':
            L_();
            T();
            L();
            break;
        case 'N':
            Dw_();
            L();
            T();
            L_();
            Dw();
            break;
        case 'O':
            Dw();
            L_();
            T();
            L();
            Dw_();
            break;
        case 'P':
            L();
            T();
            L_();
            break;
        case 'Q':
            D_();
            Lw_();
            lambda();
            Lw();
            D();
            break;
        case 'R':
            Lw_();
            lambda();
            Lw();
            break;
        case 'S':
            D();
            Lw_();
            lambda();
            Lw();
            D_();
            break;
        case 'T':
            Lw();
            reverseLambda();
            Lw_();
            break;
        case 'U':
            D2();
            L2();
            T();
            L2();
            D2();
            break;
        case 'V':
            D_();
            L2();
            T();
            L2();
            D();
            break;
        case 'W':
            L2();
            T();
            L2();
            break;
        case 'X':
            D();
            L2();
            T();
            L2();
            D_();
            break;
        default:
            throw std::exception();
    }
}

bool RubiksCube::moveWrongEdge() {
    up = cubes[1][0][1].getUpColor();
    front = cubes[1][1][0].getFrontColor();
    back = cubes[1][1][2].getBackColor();
    down = cubes[1][2][1].getDownColor();
    left = cubes[0][1][1].getLeftColor();
    right = cubes[2][1][1].getRightColor();
    if (cubes[0][0][1].getUpColor() != up || cubes[0][0][1].getLeftColor() != left)
        T();
    else if (cubes[1][0][0].getUpColor() != up || cubes[1][0][0].getFrontColor() != front)
        lambda();
    else if (cubes[1][0][2].getUpColor() != up || cubes[1][0][2].getBackColor() != back)
        reverseLambda();
    else if (cubes[0][1][0].getLeftColor() != left || cubes[0][1][0].getFrontColor() != front)
        moveEdges('M');
    else if (cubes[2][1][0].getFrontColor() != front || cubes[2][1][0].getRightColor() != right)
        moveEdges('L');
    else if (cubes[0][1][2].getBackColor() != back || cubes[0][1][2].getLeftColor() != left)
        moveEdges('P');
    else if (cubes[2][1][2].getBackColor() != back || cubes[2][1][2].getRightColor() != right)
        moveEdges('J');
    else if (cubes[1][2][0].getFrontColor() != front || cubes[1][2][0].getDownColor() != down)
        moveEdges('R');
    else if (cubes[2][2][1].getDownColor() != down || cubes[2][2][1].getRightColor() != right)
        moveEdges('Q');
    else if (cubes[1][2][2].getBackColor() != back || cubes[1][2][2].getDownColor() != down)
        moveEdges('T');
    else if (cubes[0][2][1].getDownColor() != down || cubes[0][2][1].getLeftColor() != left)
        moveEdges('S');
    else
        return false;
    return true;
}
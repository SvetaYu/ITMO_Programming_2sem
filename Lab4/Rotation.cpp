#include "RubikCube.h"

void RubiksCube::R() {
    upRotation(2);
    answer += "R ";
}

void RubiksCube::R2() {
    for (int i = 0; i < 2; ++i) {
        upRotation(2);
    }
    answer += "R2 ";
}

void RubiksCube::R_() {
    for (int i = 0; i < 3; ++i) {
        upRotation(2);
    }
    answer += "R' ";
}

void RubiksCube::U() {
    leftRotation(0);
    answer += "U ";
}

void RubiksCube::U2() {
    for (int i = 0; i < 2; ++i) {
        leftRotation(0);
    }
    answer += "U2 ";
}

void RubiksCube::U_() {
    for (int i = 0; i < 3; ++i) {
        leftRotation(0);
    }
    answer += "U' ";
}

void RubiksCube::L_() {
    upRotation(0);
    answer += "L' ";
}

void RubiksCube::L2() {
    for (int i = 0; i < 2; ++i) {
        upRotation(0);
    }
    answer += "L2 ";
}

void RubiksCube::L() {
    for (int i = 0; i < 3; ++i) {
        upRotation(0);
    }
    answer += "L ";
}

void RubiksCube::M_() {
    upRotation(1);
    char temp = up;
    up = front;
    front = down;
    down = back;
    back = temp;
    answer += "M' ";
}

void RubiksCube::M() {
    for (int i = 0; i < 3; ++i) {
        upRotation(1);
    }
    char temp = up;
    up = back;
    back = down;
    down = front;
    front = temp;
    answer += "M ";
}

void RubiksCube::M2() {
    for (int i = 0; i < 2; ++i) {
        upRotation(1);
    }
    std::swap(up, down);
    std::swap(back, front);
    answer += "M2 ";
}


void RubiksCube::Lw_() {
    upRotation(0);
    upRotation(1);
    answer += "Lw' ";
}

void RubiksCube::Lw() {
    for (int i = 0; i < 3; ++i) {
        upRotation(0);
        upRotation(1);
    }
    answer += "Lw ";
}

void RubiksCube::F_() {
    anticlockwiseRotation(0);
    answer += "F' ";
}

void RubiksCube::F() {
    for (int i = 0; i < 3; ++i) {
        anticlockwiseRotation(0);
    }
    answer += "F ";
}

void RubiksCube::F2() {
    for (int i = 0; i < 2; ++i) {
        anticlockwiseRotation(0);
    }
    answer += "F2 ";
}

void RubiksCube::S_() {
    anticlockwiseRotation(1);
    char temp = up;
    up = right;
    right = down;
    down = left;
    left = temp;
    answer += "S' ";
}

void RubiksCube::S() {
    for (int i = 0; i < 3; ++i) {
        anticlockwiseRotation(1);
    }
    char temp = up;
    up = left;
    left = down;
    down = right;
    right = temp;
    answer += "S ";
}

void RubiksCube::S2() {
    for (int i = 0; i < 2; ++i) {
        anticlockwiseRotation(1);
    }
    std::swap(up, down);
    std::swap(left, right);
    answer += "S2 ";
}

void RubiksCube::B() {
    anticlockwiseRotation(2);
    answer += "B ";
}

void RubiksCube::B_() {
    for (int i = 0; i < 3; ++i) {
        anticlockwiseRotation(2);
    }
    answer += "B' ";

}

void RubiksCube::B2() {
    for (int i = 0; i < 2; ++i) {
        anticlockwiseRotation(2);
    }
    answer += "B2 ";
}

void RubiksCube::D_() {
    leftRotation(2);
    answer += "D' ";
}

void RubiksCube::D2() {
    for (int i = 0; i < 2; ++i) {
        leftRotation(2);
    }
    answer += "D2 ";
}

void RubiksCube::D() {
    for (int i = 0; i < 3; ++i) {
        leftRotation(2);
    }
    answer += "D ";
}

void RubiksCube::E_() {
    leftRotation(1);
    char temp = front;
    front = right;
    right = back;
    back = left;
    left = temp;
    answer += "E' ";
}

void RubiksCube::E2() {
    for (int i = 0; i < 2; ++i) {
        leftRotation(1);
    }
    std::swap(left, right);
    std::swap(front, back);
    answer += "E2 ";
}

void RubiksCube::E() {
    for (int i = 0; i < 3; ++i) {
        leftRotation(1);
    }
    char temp = front;
    front = left;
    left = back;
    back = right;
    right = temp;
    answer += "E ";
}


void RubiksCube::Dw_() {
    leftRotation(1);
    leftRotation(2);
    answer += "Dw' ";
}

void RubiksCube::Dw() {
    for (int i = 0; i < 3; ++i) {
        leftRotation(1);
        leftRotation(2);
    }
    answer += "Dw ";
}

void RubiksCube::Dw2() {
    for (int i = 0; i < 2; ++i) {
        leftRotation(1);
        leftRotation(2);
    }
    answer += "Dw2 ";
}

void RubiksCube::upRotation(int x) {
    int count = 0;
    int a = -1, b = 3;
    Cube temp3 = cubes[x][0][2], temp6 = cubes[x][1][2], temp8 = cubes[x][2][1], temp9 = cubes[x][2][2];
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            ++count;
            a = (a + 1) % 3;
            if (count % 3 == 1) {
                --b;
            }
            switch (count) {
                case 3:
                    cubes[x][a][b] = temp3;
                    break;
                case 6:
                    cubes[x][a][b] = temp6;
                    break;
                case 8:
                    cubes[x][a][b] = temp8;
                    break;
                case 9:
                    cubes[x][a][b] = temp9;
                    break;
                default:
                    cubes[x][a][b] = cubes[x][i][j];
            }
            cubes[x][a][b].upRotation();
        }
    }
}

void RubiksCube::leftRotation(int y) {
    int count = 0;
    int a = -1, b = 3;
    Cube temp3 = cubes[0][y][2], temp6 = cubes[1][y][2], temp8 = cubes[2][y][1], temp9 = cubes[2][y][2];
    for (auto &cube: cubes) {
        for (int j = 0; j < 3; ++j) {
            ++count;
            a = (a + 1) % 3;
            if (count % 3 == 1) {
                --b;
            }
            switch (count) {
                case 3:
                    cubes[a][y][b] = temp3;
                    break;
                case 6:
                    cubes[a][y][b] = temp6;
                    break;
                case 8:
                    cubes[a][y][b] = temp8;
                    break;
                case 9:
                    cubes[a][y][b] = temp9;
                    break;
                default:
                    cubes[a][y][b] = cube[y][j];
            }
            cubes[a][y][b].leftRotation();
        }
    }
}

void RubiksCube::anticlockwiseRotation(int z) {
    int count = 0;
    int a = -1, b = 3;
    Cube temp3 = cubes[0][2][z], temp6 = cubes[1][2][z], temp8 = cubes[2][1][z], temp9 = cubes[2][2][z];
    for (auto &cube: cubes) {
        for (auto &j: cube) {
            ++count;
            a = (a + 1) % 3;
            if (count % 3 == 1) {
                --b;
            }
            switch (count) {
                case 3:
                    cubes[a][b][z] = temp3;
                    break;
                case 6:
                    cubes[a][b][z] = temp6;
                    break;
                case 8:
                    cubes[a][b][z] = temp8;
                    break;
                case 9:
                    cubes[a][b][z] = temp9;
                    break;
                default:
                    cubes[a][b][z] = j[z];
            }
            cubes[a][b][z].anticlockwiseRotation();
        }
    }
}

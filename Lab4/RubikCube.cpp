#include "RubikCube.h"

RubiksCube::RubiksCube() {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            cubes[0][i][j].setLeftColor('o');
            cubes[i][0][j].setUpColor('y');
            cubes[i][j][0].setFrontColor('b');
            cubes[2][i][j].setRightColor('r');
            cubes[i][2][j].setDownColor('w');
            cubes[i][j][2].setBackColor('g');
        }
    }
    up = 'y';
    front = 'b';
    back = 'g';
    down = 'w';
    left = 'o';
    right = 'r';
}

void RubiksCube::print() {
    std::cout << std::endl;
    int y = 0;
    for (int z = 2; z >= 0; --z) {
        std::cout << '\t';
        for (int x = 0; x <= 2; ++x) {
            std::cout << cubes[x][y][z].getUpColor() << ' ';
        }
        std::cout << std::endl;
    }
    for (int i = 0; i < 3; ++i) {
        std::cout << "  ";
        for (int j = 0; j < 12; ++j) {
            if (j < 3) {
                std::cout << cubes[0][i][2 - (j % 3)].getLeftColor() << ' ';
            } else if (j < 6) {
                std::cout << cubes[j % 3][i][0].getFrontColor() << ' ';
            } else if (j < 9) {
                std::cout << cubes[2][i][j % 3].getRightColor() << ' ';
            } else if (j < 12) {
                std::cout << cubes[2 - (j % 3)][i][2].getBackColor() << ' ';
            }
        }
        std::cout << std::endl;
    }
    y = 2;
    for (int z = 0; z <= 2; ++z) {
        std::cout << '\t';
        for (int x = 0; x <= 2; ++x) {
            std::cout << cubes[x][y][z].getDownColor() << ' ';
        }
        std::cout << std::endl;
    }
}

void RubiksCube::read(std::istream &in) {
    char temp;
    int y = 0;
    for (int z = 2; z >= 0; --z) {
        for (int x = 0; x <= 2; ++x) {
            in >> temp;
            cubes[x][y][z].setUpColor(temp);
        }
    }
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 12; ++j) {
            in >> temp;
            if (j < 3) {
                cubes[0][i][2 - (j % 3)].setLeftColor(temp);
            } else if (j < 6) {
                cubes[j % 3][i][0].setFrontColor(temp);
            } else if (j < 9) {
                cubes[2][i][j % 3].setRightColor(temp);
            } else if (j < 12) {
                cubes[2 - (j % 3)][i][2].setBackColor(temp);
            }
        }
    }
    y = 2;
    for (int z = 0; z <= 2; ++z) {
        for (int x = 0; x <= 2; ++x) {
            in >> temp;
            cubes[x][y][z].setDownColor(temp);
        }
    }
    up = cubes[1][0][1].getUpColor();
    front = cubes[1][1][0].getFrontColor();
    back = cubes[1][1][2].getBackColor();
    down = cubes[1][2][1].getDownColor();
    left = cubes[0][1][1].getLeftColor();
    right = cubes[2][1][1].getRightColor();
}

void RubiksCube::assembling() {
    answer.clear();
    if (!validation()) {
        std::cout << "Cube is not correct" << std::endl;
    } else {
        assemblingEdges();
        assemblingCorners();
        std::cout << answer << std::endl;
    }
    answer.clear();
}



void RubiksCube::generation() {
    answer.clear();
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, 27);
    for (int i = 0; i < 50; ++i) {
        int algorithm = distrib(gen);
        switch (algorithm) {
            case 1:
                U();
                break;
            case 2:
                U_();
                break;
            case 3:
                U2();
                break;
            case 4:
                R();
                break;
            case 5:
                R_();
                break;
            case 6:
                R2();
                break;
            case 7:
                L();
                break;
            case 8:
                L_();
                break;
            case 9:
                L2();
                break;
            case 10:
                M();
                break;
            case 11:
                M_();
                break;
            case 12:
                M2();
                break;
            case 13:
                F();
                break;
            case 14:
                F_();
                break;
            case 15:
                F2();
                break;
            case 16:
                D();
                break;
            case 17:
                D_();
                break;
            case 18:
                D2();
                break;
            case 19:
                B();
                break;
            case 20:
                B_();
                break;
            case 21:
                B2();
                break;
            case 22:
                E();
                break;
            case 23:
                E_();
                break;
            case 24:
                E2();
                break;
            case 25:
                S();
                break;
            case 26:
                S_();
                break;
            case 27:
                S2();
                break;
            default: {
            }
        }
    }

    up = cubes[1][0][1].getUpColor();
    front = cubes[1][1][0].getFrontColor();
    back = cubes[1][1][2].getBackColor();
    down = cubes[1][2][1].getDownColor();
    left = cubes[0][1][1].getLeftColor();
    right = cubes[2][1][1].getRightColor();
    std::cout << answer << std::endl;
    answer.clear();
}

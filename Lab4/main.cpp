#include <fstream>
#include <cstring>
#include "RubikCube.h"

void scramble(RubiksCube &cube, int size, const char *str) {
    int i = 0;
    while (i < size) {
        switch (str[i]) {
            case 'R':
                ++i;
                switch (str[i]) {
                    case '\'':
                        cube.R_();
                        i += 2;
                        break;
                    case ' ':
                        cube.R();
                        ++i;
                        break;
                    case '2':
                        cube.R2();
                        i += 2;
                        break;
                }
                break;
            case 'L':
                ++i;
                switch (str[i]) {
                    case '\'':
                        cube.L_();
                        i += 2;
                        break;
                    case ' ':
                        cube.L();
                        ++i;
                        break;
                    case '2':
                        cube.L2();
                        i += 2;
                        break;
                }
                break;
            case 'U':
                ++i;
                switch (str[i]) {
                    case '\'':
                        cube.U_();
                        i += 2;
                        break;
                    case ' ':
                        cube.U();
                        ++i;
                        break;
                    case '2':
                        cube.U2();
                        i += 2;
                        break;
                }
                break;
            case 'D':
                ++i;
                switch (str[i]) {
                    case '\'':
                        cube.D_();
                        i += 2;
                        break;
                    case ' ':
                        cube.D();
                        ++i;
                        break;
                    case '2':
                        cube.D2();
                        i += 2;
                        break;
                }
                break;
            case 'F':
                ++i;
                switch (str[i]) {
                    case '\'':
                        cube.F_();
                        i += 2;
                        break;
                    case ' ':
                        cube.F();
                        ++i;
                        break;
                    case '2':
                        cube.F2();
                        i += 2;
                        break;
                }
                break;
            case 'B':
                ++i;
                switch (str[i]) {
                    case '\'':
                        cube.B_();
                        i += 2;
                        break;
                    case ' ':
                        cube.B();
                        ++i;
                        break;
                    case '2':
                        cube.B2();
                        i += 2;
                        break;
                }
                break;
            case 'E':
                ++i;
                switch (str[i]) {
                    case '\'':
                        cube.E_();
                        i += 2;
                        break;
                    case ' ':
                        cube.E();
                        ++i;
                        break;
                    case '2':
                        cube.E2();
                        i += 2;
                        break;
                }
            case 'S':
                ++i;
                switch (str[i]) {
                    case '\'':
                        cube.S_();
                        i += 2;
                        break;
                    case ' ':
                        cube.S();
                        ++i;
                        break;
                    case '2':
                        cube.S2();
                        i += 2;
                        break;
                }
                break;
            case 'M':
                ++i;
                switch (str[i]) {
                    case '\'':
                        cube.M_();
                        i += 2;
                        break;
                    case ' ':
                        cube.M();
                        ++i;
                        break;
                    case '2':
                        cube.M2();
                        i += 2;
                        break;
                }
        }
    }
}


int main(int argc, char **argv) {
    std::cout << "Hello, World!" << std::endl;
    RubiksCube R;
    int i = 1;
    while (i < argc) {
        if (std::strcmp(argv[i], "--file") == 0) {
            std::ifstream fin(argv[i + 1]);
            R.read(fin);
            i += 2;
        } else if (std::strcmp(argv[i], "--random") == 0) {
            R.generation();
            ++i;
        } else if (std::strcmp(argv[i], "--scramble") == 0) {
            scramble(R, atoi(argv[i + 1]), argv[i + 2]);
            i += 3;
        }
        if (std::strcmp(argv[i], "--validation") == 0) {
            if (R.validation())
                std::cout << "The cube is correct" << std::endl;
            else
                std::cout << "The cube is not correct" << std::endl;
            ++i;
        }
        if (std::strcmp(argv[i], "--assembling") == 0) {
            R.assembling();
            ++i;
        }
        if (std::strcmp(argv[i], "--print") == 0) {
            R.print();
    return 0;
}

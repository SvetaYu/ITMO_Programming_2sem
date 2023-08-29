#pragma once

#include "RubikCube.h"


bool RubiksCube::validation() {
    std::cout << answer << std::endl;
    answer.clear();

    if (!differentCubes())
        return false;

    if (!correctCorners())
        return false;

    if (!edgeParity())
        return false;

    if (!permutationParity())
        return false;

    return true;
}

bool RubiksCube::differentCubes() {
    std::set<std::set<int>> differentCubes;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < 3; ++k) {
                char *colors = cubes[i][j][k].getColors();
                std::set<int> cubesColors;
                for (int c = 1; c < 7; ++c) {
                    cubesColors.insert(colors[c]);
                }
                if (i == 1 && j == 1 && k == 1) {}
                else if ((i == 1 && j == 1) || (i == 1 && k == 1) || (j == 1 && k == 1)) {
                    if (cubesColors.size() != 2)
                        return false;
                } else if (i == 1 || j == 1 || k == 1) {
                    if (cubesColors.size() != 3)
                        return false;
                } else if (cubesColors.size() != 4)
                    return false;
                differentCubes.insert(cubesColors);
            }
        }
    }
    if (differentCubes.size() != 27)
        return false;
    return true;

}

bool RubiksCube::permutationParity() {
    int countCorners = 0, countEdges = 0, count;
    bool visit[3][3][3];
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < 3; ++k) {
                visit[i][j][k] = false;
            }
        }
    }
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < 3; ++k) {
                if ((i == 1 && j == 1) || (i == 1 && k == 1) || (j == 1 && k == 1)) {}
                else if (!visit[i][j][k]) {
                    visit[i][j][k] = true;
                    count = cycle(i, j, k, visit);
                    if (i == 1 || j == 1 || k == 1) {
                        if (count != 0)
                            countEdges += (count + 1) % 2;
                    } else if (count != 0)
                        countCorners += (count + 1) % 2;
                }
            }
        }
    }
    if (countCorners % 2 != countEdges % 2)
        return false;
    else
        return true;
}

int RubiksCube::cycle(int startX, int startY, int startZ, bool visit[][3][3]) {
    int x = -1, y = -1, z = -1;
    int count = 0;
    std::set<int> setCubes[3][3][3];

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            setCubes[0][i][j].insert(left);
            setCubes[i][0][j].insert(up);
            setCubes[i][j][0].insert(front);
            setCubes[2][i][j].insert(right);
            setCubes[i][2][j].insert(down);
            setCubes[i][j][2].insert(back);
        }
    }

    Cube buf = cubes[startX][startY][startZ];
    while (x != startX || y != startY || z != startZ) {
        std::set<int> set;
        for (int c = 1; c < 7; ++c) {
            if (buf.getColors()[c] != 0)
                set.insert(buf.getColors()[c]);
        }
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                for (int k = 0; k < 3; ++k) {
                    if (setCubes[i][j][k] == set) {
                        visit[i][j][k] = true;
                        x = i;
                        y = j;
                        z = k;
                        buf = cubes[x][y][z];
                        ++count;
                        break;
                    }
                }
            }
        }
        if (x == -1)
            break;
    }
    return count;
}

bool RubiksCube::edgeParity() {
    int count = 0;
    for (int i = 0; i < 3; i += 2) {
        if (cubes[0][i][1].getUpColor() == up || cubes[0][i][1].getUpColor() == down ||
            cubes[0][i][1].getDownColor() == up || cubes[0][i][1].getDownColor() == down)
            ++count;
        else if ((cubes[0][i][1].getUpColor() == front || cubes[0][i][1].getUpColor() == back ||
                  cubes[0][i][1].getDownColor() == front || cubes[0][i][1].getDownColor() == back) &&
                 (cubes[0][i][1].getLeftColor() != up) && (cubes[0][i][1].getLeftColor() != down))
            ++count;

        if (cubes[2][i][1].getDownColor() == up || cubes[2][i][1].getDownColor() == down ||
            cubes[2][i][1].getUpColor() == up || cubes[2][i][1].getUpColor() == down)
            ++count;
        else if ((cubes[2][i][1].getUpColor() == front || cubes[2][i][1].getUpColor() == back ||
                  cubes[2][i][1].getDownColor() == front || cubes[2][i][1].getDownColor() == back) &&
                 (cubes[2][i][1].getRightColor() != up) && (cubes[2][i][1].getRightColor() != down))
            ++count;

        if (cubes[1][i][0].getDownColor() == up || cubes[1][i][0].getDownColor() == down ||
            cubes[1][i][0].getUpColor() == up || cubes[1][i][0].getUpColor() == down)
            ++count;
        else if ((cubes[1][i][0].getUpColor() == front || cubes[1][i][0].getUpColor() == back ||
                  cubes[1][i][0].getDownColor() == front || cubes[1][i][0].getDownColor() == back) &&
                 (cubes[1][i][0].getFrontColor() != up) && (cubes[1][i][0].getFrontColor() != down))
            ++count;

        if (cubes[1][i][2].getDownColor() == up || cubes[1][i][2].getDownColor() == down ||
            cubes[1][i][2].getUpColor() == up || cubes[1][i][2].getUpColor() == down)
            ++count;
        else if ((cubes[1][i][2].getUpColor() == front || cubes[1][i][2].getUpColor() == back ||
                  cubes[1][i][2].getDownColor() == front || cubes[1][i][2].getDownColor() == back) &&
                 (cubes[1][i][2].getBackColor() != up) && (cubes[1][i][2].getBackColor() != down))
            ++count;

        if (cubes[i][1][2].getBackColor() == up || cubes[i][1][2].getBackColor() == down ||
            ((cubes[i][1][2].getBackColor() == back || cubes[i][1][2].getBackColor() == front) &&
             (cubes[i][1][2].getLeftColor() == left || cubes[i][1][2].getRightColor() == left ||
              cubes[i][1][2].getLeftColor() == right || cubes[i][1][2].getRightColor() == right)))
            ++count;

        if (cubes[i][1][0].getFrontColor() == up || cubes[i][1][0].getFrontColor() == down ||
            ((cubes[i][1][0].getFrontColor() == front || cubes[i][1][0].getFrontColor() == back) &&
             (cubes[i][1][0].getLeftColor() == left || cubes[i][1][0].getRightColor() == left ||
              cubes[i][1][0].getLeftColor() == right || cubes[i][1][0].getRightColor() == right)))
            ++count;
    }
    if (count % 2 != 0)
        return false;
    return true;
}


bool RubiksCube::correctCorners() {
    int count = 0;
    {
        short traversal[3] = {u, f, l};
        if (!cubes[0][0][0].correctness(traversal, up, down, left, right, front, back, count))
            return false;
    }

    {
        short traversal[3] = {u, r, f};
        if (!cubes[2][0][0].correctness(traversal, up, down, left, right, front, back, count))
            return false;
    }

    {
        short traversal[3] = {u, b, r};
        if (!cubes[2][0][2].correctness(traversal, up, down, left, right, front, back, count))
            return false;
    }

    {
        short traversal[3] = {u, l, b};
        if (!cubes[0][0][2].correctness(traversal, up, down, left, right, front, back, count))
            return false;
    }

    {
        short traversal[3] = {d, f, r};
        if (!cubes[2][2][0].correctness(traversal, up, down, left, right, front, back, count))
            return false;
    }

    {
        short traversal[3] = {d, r, b};
        if (!cubes[2][2][2].correctness(traversal, up, down, left, right, front, back, count))
            return false;
    }

    {
        short traversal[3] = {d, b, l};
        if (!cubes[0][2][2].correctness(traversal, up, down, left, right, front, back, count))
            return false;
    }

    {
        short traversal[3] = {d, l, f};
        if (!cubes[0][2][0].correctness(traversal, up, down, left, right, front, back, count))
            return false;
    }

    if (count % 3 != 0)
        return false;
    return true;

}

bool Cube::
correctness(const short Traversal[], char up, char down, char left, char right,
            char front, char back, int &count) {
    int i = 0;
    if (colors[Traversal[1]] == up || colors[Traversal[1]] == down)     // parity corners
        count -= 1;
    else if (colors[Traversal[2]] == up || colors[Traversal[2]] == down)
        count += 1;

    if (colors[Traversal[i]] == front) {
        if (colors[Traversal[i + 1]] == up) {
            if (colors[Traversal[i + 2]] != right)
                return false;
        } else if (colors[Traversal[i + 1]] == down) {
            if (colors[Traversal[i + 2]] != left)
                return false;
        } else if (colors[Traversal[i + 1]] == right) {
            if (colors[Traversal[i + 2]] != down)
                return false;
        } else if (colors[Traversal[i + 1]] == left) {
            if (colors[Traversal[i + 2]] != up)
                return false;
        } else return false;
    } else if (colors[Traversal[i]] == up) {
        if (colors[Traversal[i + 1]] == right) {
            if (colors[Traversal[i + 2]] != front)
                return false;
        } else if (colors[Traversal[i + 1]] == front) {
            if (colors[Traversal[i + 2]] != left)
                return false;
        } else if (colors[Traversal[i + 1]] == left) {
            if (colors[Traversal[i + 2]] != back)
                return false;
        } else if (colors[Traversal[i + 1]] == back) {
            if (colors[Traversal[i + 2]] != right)
                return false;
        } else return false;
    } else if (colors[Traversal[i]] == right) {
        if (colors[Traversal[i + 1]] == front) {
            if (colors[Traversal[i + 2]] != up)
                return false;
        } else if (colors[Traversal[i + 1]] == down) {
            if (colors[Traversal[i + 2]] != front)
                return false;
        } else if (colors[Traversal[i + 1]] == up) {
            if (colors[Traversal[i + 2]] != back)
                return false;
        } else if (colors[Traversal[i + 1]] == back) {
            if (colors[Traversal[i + 2]] != down)
                return false;
        } else return false;
    } else if (colors[Traversal[i]] == down) {
        if (colors[Traversal[i + 1]] == left) {
            if (colors[Traversal[i + 2]] != front)
                return false;
        } else if (colors[Traversal[i + 1]] == right) {
            if (colors[Traversal[i + 2]] != back)
                return false;
        } else if (colors[Traversal[i + 1]] == back) {
            if (colors[Traversal[i + 2]] != left)
                return false;
        } else if (colors[Traversal[i + 1]] == front) {
            if (colors[Traversal[i + 2]] != right)
                return false;
        } else return false;
    } else if (colors[Traversal[i]] == left) {
        if (colors[Traversal[i + 1]] == front) {
            if (colors[Traversal[i + 2]] != down)
                return false;
        } else if (colors[Traversal[i + 1]] == up) {
            if (colors[Traversal[i + 2]] != front)
                return false;
        } else if (colors[Traversal[i + 1]] == back) {
            if (colors[Traversal[i + 2]] != up)
                return false;
        } else if (colors[Traversal[i + 1]] == down) {
            if (colors[Traversal[i + 2]] != back)
                return false;
        } else return false;
    } else if (colors[Traversal[i]] == back) {
        if (colors[Traversal[i + 1]] == up) {
            if (colors[Traversal[i + 2]] != left)
                return false;
        } else if (colors[Traversal[i + 1]] == right) {
            if (colors[Traversal[i + 2]] != up)
                return false;
        } else if (colors[Traversal[i + 1]] == down) {
            if (colors[Traversal[i + 2]] != right)
                return false;
        } else if (colors[Traversal[i + 1]] == left) {
            if (colors[Traversal[i + 2]] != down)
                return false;
        } else return false;
    }
    return true;
}
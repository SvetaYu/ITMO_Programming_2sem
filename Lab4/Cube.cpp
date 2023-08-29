#include "Cube.h"
#include <iostream>

Cube::Cube() {
    for (int i = 1; i < 7; ++i) {
        colors[i] = 0;
    }
}

void Cube::setLeftColor(char newColor) {
    colors[l] = newColor;
}

void Cube::setRightColor(char newColor) {
    colors[r] = newColor;
}

void Cube::setUpColor(char newColor) {
    colors[u] = newColor;
}

void Cube::setDownColor(char newColor) {
    colors[d] = newColor;
}

void Cube::setFrontColor(char newColor) {
    colors[f] = newColor;
}

void Cube::setBackColor(char newColor) {
    colors[b] = newColor;
}

char Cube::getLeftColor() {
    return colors[l];
}

char Cube::getRightColor() {
    return colors[r];
}

char Cube::getUpColor() {
    return colors[u];
}

char Cube::getDownColor() {
    return colors[d];
}

char Cube::getFrontColor() {
    return colors[f];
}

char Cube::getBackColor() {
    return colors[b];
}

char *Cube::getColors() {
    return colors;
}

void Cube::upRotation() {
    short upTraversal[b] = {d, f, u, b};
    rotation(upTraversal);
}

void Cube::leftRotation() {
    short lefTraversal[b] = {f, l, b, r};
    rotation(lefTraversal);
}

void Cube::anticlockwiseRotation() {
    short anticlockwiseTraversal[b] = {d, r, u, l};
    rotation(anticlockwiseTraversal);
}

void Cube::rotation(const short Traversal[4]) {
    char temp = colors[Traversal[3]];
    for (int i = 3; i > 0; --i) {
        colors[Traversal[i]] = colors[Traversal[i - 1]];
    }
    colors[Traversal[0]] = temp;
}
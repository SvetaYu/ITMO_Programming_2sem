#pragma once
enum sides{d=1,f,r,b,l,u};

class Cube {
public:
    Cube() ;

    void setLeftColor(char newColor) ;

    void setRightColor(char newColor) ;

    void setUpColor(char newColor) ;

    void setDownColor(char newColor) ;

    void setFrontColor(char newColor) ;

    void setBackColor(char newColor);

    char getLeftColor() ;

    char getRightColor() ;

    char getUpColor() ;

    char getDownColor() ;

    char getFrontColor() ;

    char getBackColor() ;

    char *getColors() ;

    void upRotation() ;

    void leftRotation() ;

    void anticlockwiseRotation() ;

    bool
    correctness(const short Traversal[], char up, char down, char left, char right,
                char front, char back, int & count);

private:
    char colors[7]{};

    void rotation(const short Traversal[4]);
};
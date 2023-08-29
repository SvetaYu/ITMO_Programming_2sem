#pragma once

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

class Point {
public:
    Point(char name, double x, double y);

    Point();

    Point(const Point &other);

    Point &operator=(const Point &other);

    void print() const;

    char getName() const;

    double getX() const;

    double getY() const;

protected:
    char name;
    double x;
    double y;
};

class Polyline {
public:
    Polyline(int size, Point points[]);

    ~Polyline();

    Polyline(const Polyline &other);

    Polyline &operator=(const Polyline &other);

    virtual void findingTheLength();

    virtual void print();

    void printPoints();

    virtual void printLength();

    double getLength() const;

protected:
    Point *points;
    string name;
    double length = 0;
    int size = 0;
};

class ClosedPolyline : public Polyline {
public:
    ClosedPolyline(int size, Point points[]);

    ClosedPolyline(const ClosedPolyline &other);

    ClosedPolyline &operator=(const ClosedPolyline &other);

    void findingTheLength();
};

class Polygon : public ClosedPolyline {
public:
    Polygon(int size, Point points[]);

    Polygon(const Polygon &other);

    Polygon &operator=(const Polygon &other);

    void printLength();

    void findingTheArea();

    void printArea() const;

    void print();

    double getArea() const;

protected:
    double area;
};

class Triangle : public Polygon {
public:
    Triangle(int size, Point points[3]);

    Triangle(const Triangle &other);

    Triangle &operator=(const Triangle &other);
};

class Trapezoid : public Polygon {
public:
    Trapezoid(int size, Point points[4]);

    Trapezoid(const Trapezoid &other);

    Trapezoid &operator=(const Trapezoid &other);
};

class RegularPolygon : public Polygon {
public:
    RegularPolygon(int size, Point points[]);

    RegularPolygon(const RegularPolygon &other);

    RegularPolygon &operator=(const RegularPolygon &other);
};

bool parallelism(const Point &point0, const Point &point1, const Point &point2, const Point &point3);

double angle(const Point &point0, const Point &point1, const Point &point2);
#include <iostream>
#include <string>
#include <cmath>
using namespace std;
class Point //точка
{
public:
    Point(char name, double x, double y)
    {
        this->name = name;
        this->x = x;
        this->y = y;
    }
    Point()
    {
        this->name = 'A';
        this->x = 0;
        this->y = 0;
    }
    Point(const Point &other)
    {
        this->x = other.x;
        this->y = other.y;
        this->name = other.name;
    }
    void operator=(const Point &other)
    {
        this->x = other.x;
        this->y = other.y;
        this->name = other.name;
    }
    void print()
    {
        cout << name << '(' << x << ',' << y << ')' << endl;
    }
    char getName()
    {
        return name;
    }
    double getX()
    {
        return x;
    }
    double getY()
    {
        return y;
    }

protected:
    char name;
    double x;
    double y;
};
class Polyline //ломаная
{
    friend Point;

public:
    Polyline(int size, Point points[])
    {
        this->points = new Point[size];
        for (int i = 0; i < size; i++)
        {
            this->points[i] = points[i];
        }
        this->size = size;
        for (int i = 0; i < size; i++)
        {
            this->name = this->name + this->points[i].getName();
        }
        findingTheLength();
    }
    ~Polyline()
    {
        delete[] points;
    }
    Polyline(const Polyline &other)
    {
        this->length = other.length;
        this->name = other.name;
        this->size = other.size;
        this->points = new Point[this->size];
        for (int i = 0; i < this->size; i++)
        {
            this->points[i] = other.points[i];
        }
    }
    Polyline operator=(const Polyline &other)
    {
        delete[] points;
        this->length = other.length;
        this->name = other.name;
        this->size = other.size;
        this->points = new Point[this->size];
        for (int i = 0; i < this->size; i++)
        {
            this->points[i] = other.points[i];
        }
        return *this;
    }
    virtual void findingTheLength()
    {
        length = 0;
        Point temp = points[0];
        for (int i = 1; i < size; i++)
        {
            length += hypot(points[i].getX() - temp.getX(), points[i].getY() - temp.getY());
            temp = points[i];
        }
    }
    virtual void print()
    {
        printPoints();
        printlength();
    }
    void printPoints()
    {
        cout << name << ':' << endl;
        for (int i = 0; i < size; i++)
        {
            points[i].print();
        }
    }
    virtual void printlength()
    {
        cout << "length = " << length << endl;
    }

protected:
    Point *points;
    string name = "";
    double length = 0;
    int size = 0;
};
class ClosedPolyline : public Polyline //замкнутая ломаная
{
public:
    ClosedPolyline(int size, Point points[]) : Polyline(size, points)
    {
        findingTheLength();
    }
    ClosedPolyline(const ClosedPolyline &other) : Polyline(other)
    {
    }
    ClosedPolyline operator=(const ClosedPolyline &other)
    {
        this->length = other.length;
        this->name = other.name;
        this->size = other.size;
        this->points = new Point[this->size];
        for (int i = 0; i < this->size; i++)
        {
            this->points[i] = other.points[i];
        }
        return *this;
    }
    void findingTheLength()
    {
        Polyline::findingTheLength();
        length += hypot(points[size - 1].getX() - points[0].getX(), points[size - 1].getY() - points[0].getY());
    }
};
class Polygon : public ClosedPolyline //многоугольник
{
public:
    Polygon(int size, Point points[]) : ClosedPolyline(size, points)
    {
        findingTheArea();
    }
    Polygon(const Polygon &other) : ClosedPolyline(other)
    {
        this->area = other.area;
    }
    Polygon operator=(const Polygon &other)
    {
        delete[] points;
        this->length = other.length;
        this->name = other.name;
        this->size = other.size;
        this->points = new Point[this->size];
        for (int i = 0; i < this->size; i++)
        {
            this->points[i] = other.points[i];
        }
        this->area = other.area;
        return *this;
    }
    void printlength()
    {
        cout << "perimeter = " << length << endl;
    }
    void findingTheArea()
    {
        area = 0;
        for (int i = 0; i < size - 1; i++)
        {
            area += points[i + 1].getX() * points[i].getY();
        }
        area *= -1;
        for (int i = 0; i < size - 1; i++)
        {
            area += points[i].getX() * points[i + 1].getY();
        }
        area += points[size - 1].getX() * points[0].getY() - points[0].getX() * points[size - 1].getY();
        area = abs(area) / 2;
    }
    void printArea()
    {
        cout << "Area = " << area << endl;
    }
    void print()
    {
        printPoints();
        printlength();
        printArea();
    }

protected:
    double area;
};
class Triangle : public Polygon //треугольник
{
public:
    Triangle(int size, Point points[3]) : Polygon(size, points)
    {
    }
    Triangle(const Triangle &other) : Polygon(other)
    {
    }
    Triangle operator=(const Triangle &other)
    {
        delete[] points;
        this->length = other.length;
        this->name = other.name;
        this->size = other.size;
        this->points = new Point[this->size];
        for (int i = 0; i < this->size; i++)
        {
            this->points[i] = other.points[i];
        }
        this->area = other.area;
        return *this;
    }
};
class Trapezoid : public Polygon //трапеция
{
public:
    Trapezoid(int size, Point points[4]) : Polygon(size, points)
    {
    }
    Trapezoid(const Trapezoid &other) : Polygon(other)
    {
    }
    Trapezoid operator=(const Trapezoid &other)
    {
        delete[] points;
        this->length = other.length;
        this->name = other.name;
        this->size = other.size;
        this->points = new Point[this->size];
        for (int i = 0; i < this->size; i++)
        {
            this->points[i] = other.points[i];
        }
        this->area = other.area;
        return *this;
    }
};
class RegularPolygon : public Polygon //правильный многоугольник
{
public:
    RegularPolygon(int size, Point points[]) : Polygon(size, points)
    {
    }
    RegularPolygon(const RegularPolygon &other) : Polygon(other)
    {
    }
    RegularPolygon operator=(const RegularPolygon &other)
    {
        delete[] points;
        this->length = other.length;
        this->name = other.name;
        this->size = other.size;
        this->points = new Point[this->size];
        for (int i = 0; i < this->size; i++)
        {
            this->points[i] = other.points[i];
        }
        this->area = other.area;
        return *this;
    }
};
int main()
{
    Point A('A', 0, 0);
    Point B('B', 0, 3);
    Point C('C', 4, 3);
    Point D('D', 8, 0);
    Point E('E', 3, 3);
    Point F('F', 3, 0);
    Point arr[3] = {A, B, C};
    Point arr2[4] = {A, B, C, D};
    Point arr3[4] = {A, B, E, F};
    int size = sizeof(arr) / sizeof(arr[0]);
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    Polyline polyline(size, arr);
    ClosedPolyline polyline2(size, arr);
    Polygon polygon(size, arr);
    Triangle triangle(size, arr);
    Trapezoid trapezoid(size2, arr2);
    RegularPolygon regularPolygon(size2, arr3);
    Polyline *array[6] = {&polyline, &polyline2, &polygon, &triangle, &trapezoid, &regularPolygon};
    Polyline array2[6] = {polyline, polyline2, polygon, triangle, trapezoid, regularPolygon};
    for (int i = 0; i < 6; i++)
    {
        array[i]->print();
        cout << endl;
        array2[i].print();
        cout << endl;
    }
    return 0;
}
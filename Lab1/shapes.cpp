#include "shapes.h"

Point::Point(char name, double x, double y) {
    this->name = name;
    this->x = x;
    this->y = y;
}

Point::Point() {
    this->name = 'A';
    this->x = 0;
    this->y = 0;
}

Point::Point(const Point &other) {
    this->x = other.x;
    this->y = other.y;
    this->name = other.name;
}

Point &Point::operator=(const Point &other) {
    this->x = other.x;
    this->y = other.y;
    this->name = other.name;
    return *this;
}

void Point::print() const {
    cout << name << '(' << x << ',' << y << ')' << endl;
}

char Point::getName() const {
    return name;
}

double Point::getX() const {
    return x;
}

double Point::getY() const {
    return y;
}

Polyline::Polyline(int size, Point points[]) {
    this->points = new Point[size];
    for (int i = 0; i < size; i++) {
        this->points[i] = points[i];
    }
    this->size = size;
    for (int i = 0; i < size; i++) {
        this->name = this->name + this->points[i].getName();
    }
    findingTheLength();
}

Polyline::~Polyline() {
    delete[] points;
}

Polyline::Polyline(const Polyline &other) {
    this->length = other.length;
    this->name = other.name;
    this->size = other.size;
    this->points = new Point[this->size];
    for (int i = 0; i < this->size; i++) {
        this->points[i] = other.points[i];
    }
}

Polyline &Polyline::operator=(const Polyline &other) {
    delete[] points;
    this->length = other.length;
    this->name = other.name;
    this->size = other.size;
    this->points = new Point[this->size];
    for (int i = 0; i < this->size; i++) {
        this->points[i] = other.points[i];
    }
    return *this;
}

void Polyline::findingTheLength() {
    length = 0;
    Point temp = points[0];
    for (int i = 1; i < size; i++) {
        length += hypot(points[i].getX() - temp.getX(), points[i].getY() - temp.getY());
        temp = points[i];
    }
}

void Polyline::print() {
    printPoints();
    printLength();
}

void Polyline::printPoints() {
    cout << name << ':' << endl;
    for (int i = 0; i < size; i++) {
        points[i].print();
    }
}

void Polyline::printLength() {
    cout << "length = " << length << endl;
}

double Polyline::getLength() const {
    return length;
}

ClosedPolyline::ClosedPolyline(int size, Point points[]) : Polyline(size, points) {
    findingTheLength();
}

ClosedPolyline::ClosedPolyline(const ClosedPolyline &other) : Polyline(other) {
}

ClosedPolyline &ClosedPolyline::operator=(const ClosedPolyline &other) {
    this->length = other.length;
    this->name = other.name;
    this->size = other.size;
    this->points = new Point[this->size];
    for (int i = 0; i < this->size; i++) {
        this->points[i] = other.points[i];
    }
    return *this;
}

void ClosedPolyline::findingTheLength() {
    Polyline::findingTheLength();
    length += hypot(points[size - 1].getX() - points[0].getX(), points[size - 1].getY() - points[0].getY());
}

Polygon::Polygon(int size, Point points[]) : ClosedPolyline(size, points) {
    findingTheArea();
}

Polygon::Polygon(const Polygon &other) : ClosedPolyline(other) {
    this->area = other.area;
}

Polygon &Polygon::operator=(const Polygon &other) {
    delete[] points;
    this->length = other.length;
    this->name = other.name;
    this->size = other.size;
    this->points = new Point[this->size];
    for (int i = 0; i < this->size; i++) {
        this->points[i] = other.points[i];
    }
    this->area = other.area;
    return *this;
}

void Polygon::printLength() {
    cout << "perimeter = " << length << endl;
}

void Polygon::findingTheArea() {
    area = 0;
    for (int i = 0; i < size - 1; i++) {
        area += points[i + 1].getX() * points[i].getY();
    }
    area *= -1;
    for (int i = 0; i < size - 1; i++) {
        area += points[i].getX() * points[i + 1].getY();
    }
    area += points[size - 1].getX() * points[0].getY() - points[0].getX() * points[size - 1].getY();
    area = abs(area) / 2;
}

void Polygon::printArea() const {
    cout << "Area = " << area << endl;
}

void Polygon::print() {
    printPoints();
    printLength();
    printArea();
}

double Polygon::getArea() const {
    return area;
}

Triangle::Triangle(int size, Point points[3]) : Polygon(size, points) {
    if (size != 3) {
        throw exception();
    }
}

Triangle::Triangle(const Triangle &other) : Polygon(other) {
}

Triangle &Triangle::operator=(const Triangle &other) {
    delete[] points;
    this->length = other.length;
    this->name = other.name;
    this->size = other.size;
    this->points = new Point[this->size];
    for (int i = 0; i < this->size; i++) {
        this->points[i] = other.points[i];
    }
    this->area = other.area;
    return *this;
}

Trapezoid::Trapezoid(int size, Point points[4]) : Polygon(size, points) {
    if (size != 4) {
        throw exception();
    }
    bool parallelism1 = parallelism(points[0], points[1], points[2], points[3]);
    bool parallelism2 = parallelism(points[1], points[2], points[3], points[0]);
    if ((parallelism1 && parallelism2) || (!parallelism2 && !parallelism1)) {
        throw exception();
    }
}

Trapezoid::Trapezoid(const Trapezoid &other) : Polygon(other) {
}

Trapezoid &Trapezoid::operator=(const Trapezoid &other) {
    delete[] points;
    this->length = other.length;
    this->name = other.name;
    this->size = other.size;
    this->points = new Point[this->size];
    for (int i = 0; i < this->size; i++) {
        this->points[i] = other.points[i];
    }
    this->area = other.area;
    return *this;
}

RegularPolygon::RegularPolygon(int size, Point points[]) : Polygon(size, points) {
    if (size < 3) {
        throw exception();
    }
    double length1 = hypot(points[size - 1].getX() - points[0].getX(), points[size - 1].getY() - points[0].getY());
    double angle1 = angle(points[size - 2], points[size - 1], points[0]);
    Point temp = points[0];
    for (int i = 1; i < size; i++) {
        if (hypot(points[i].getX() - temp.getX(), points[i].getY() - temp.getY()) != length1) {
            throw exception();
        }
        if (angle(points[i - 1], points[i], points[i + 1]) != angle1) {
            throw exception();
        }
        temp = points[i];
    }
}

RegularPolygon::RegularPolygon(const RegularPolygon &other) : Polygon(other) {
}

RegularPolygon &RegularPolygon::operator=(const RegularPolygon &other) {
    delete[] points;
    this->length = other.length;
    this->name = other.name;
    this->size = other.size;
    this->points = new Point[this->size];
    for (int i = 0; i < this->size; i++) {
        this->points[i] = other.points[i];
    }
    this->area = other.area;
    return *this;
}

bool parallelism(const Point &point0, const Point &point1, const Point &point2, const Point &point3) {
    if (point0.getX() == point1.getX() && point2.getX() == point3.getX()) {
        return true;
    } else if (point0.getX() == point1.getX() || point2.getX() == point3.getX()) {
        return false;
    }
    return (point0.getY() - point1.getY()) / (point0.getX() - point1.getX()) ==
           (point2.getY() - point3.getY()) / (point2.getX() - point3.getX());
}

double angle(const Point &point0, const Point &point1, const Point &point2) {
    double x1 = point1.getX() - point0.getX();
    double x2 = point1.getX() - point2.getX();
    double y1 = point1.getY() - point0.getY();
    double y2 = point1.getY() - point2.getY();
    return (x1 * x2 + y1 * y2) / (sqrt(x1 * x1 + y1 * y1) * sqrt(x2 * x2 + y2 * y2));
}
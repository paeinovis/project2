#ifndef LAB6_SHAPES_H
#define LAB6_SHAPES_H
#include <vector>
#include "string"
#include <iomanip>
#include <math.h>
using namespace std;

const float PI = 3.14159f;

class Shape {

protected:
    float height = 0;   // Y dimension
    float width = 0;    // X dimension (AKA base or radius)
    float length = 0;   // Z dimension
    float area = 0.0;
    float volume = 0.0;
    string name2D;
    string name3D;
public:
    Shape();
    virtual void Scale(float scaleFactor) = 0;
    virtual void Display() const = 0;
    virtual ~Shape();
};

class Shape2D : virtual public Shape {
public:
    Shape2D();
    virtual float Area() const = 0;
    void ShowArea() const;
    virtual string GetName2D() const = 0;
    bool operator>(const Shape2D &rhs) const;
    bool operator<(const Shape2D &rhs) const;
    bool operator==(const Shape2D &rhs) const;
};


class Square : virtual public Shape2D{
public:
    Square();
    Square(float r);
    void Scale(float scaleFactor);
    void Display() const;
    float Area() const;
    string GetName2D() const;
};

class Triangle : virtual public Shape2D{
public:
    Triangle();
    Triangle(float b, float h);
    void Scale(float scaleFactor);
    void Display() const;
    float Area() const;
    string GetName2D() const;
};

class Circle : virtual public Shape2D{
public:
    Circle();
    Circle(float r);
    void Scale(float scaleFactor);
    void Display() const;
    float Area() const;
    string GetName2D() const;
};


class Shape3D : virtual public Shape {
public:
    Shape3D();
    virtual float Volume() const = 0;
    void ShowVolume() const;
    virtual string GetName3D() const = 0;
    bool operator>(const Shape3D &rhs) const;
    bool operator<(const Shape3D &rhs) const;
    bool operator==(const Shape3D &rhs) const;
};

class Sphere : virtual public Shape3D, public Shape2D{
public:
    Sphere();
    Sphere(float r);
    void Scale(float scaleFactor);
    void Display() const;
    float Area() const;
    string GetName2D() const;
    float Volume() const;
    string GetName3D() const;
};

class TriangularPyramid : virtual public Shape3D, public Shape2D{
public:
    TriangularPyramid();
    TriangularPyramid(float h, float l, float b);
    void Scale(float scaleFactor);
    void Display() const;
    float Area() const;
    string GetName2D() const;
    float Volume() const;
    string GetName3D() const;
};

class Cylinder : virtual public Shape3D, public Shape2D{
public:
    Cylinder();
    Cylinder(float h, float r);
    void Scale(float scaleFactor);
    void Display() const;
    float Area() const;
    string GetName2D() const;
    float Volume() const;
    string GetName3D() const;
};


#endif //LAB6_SHAPES_H

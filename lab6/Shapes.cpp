#include "Shapes.h"
#include <vector>
#include "string"
#include <iomanip>
#include <iostream>
#include <math.h>
using namespace std;

// Shape

Shape::Shape(){
    height = 0;
    width = 0;
    length = 0;
    name2D = "";
    name3D = "";
}

void Shape::Scale(float scaleFactor) {
    height *= scaleFactor;
    width *= scaleFactor;
    length *= scaleFactor;
}

Shape::~Shape() {
}

// 2D

Shape2D::Shape2D() {
    height = 0;
    width = 0;
    length = 0;
}

float Shape2D::Area() const{
    return area;
}

void Shape2D::ShowArea() const{
    cout << "The area of the " << GetName2D() << "is : " << endl;
    cout << Area() << endl;
}

string Shape2D::GetName2D() const {
    return name2D;
}

bool Shape2D::operator>(const Shape2D &rhs) const{
    return (this->Area() > rhs.Area());
}
bool Shape2D::operator<(const Shape2D &rhs) const{
    return (this->Area() < rhs.Area());
}
bool Shape2D::operator==(const Shape2D &rhs) const{
    return (this->Area() == rhs.Area());
}

// 2D Shapes

Square::Square(){
    name2D = "Square";
}
Square::Square(float r){
    name2D = "Square";
    height = width = r;
    area = pow(r, 2);
}

void Square::Scale(float scaleFactor) {
    Shape::Scale(scaleFactor);
    area = pow(width, 2);
}
void Square::Display() const {
    cout << "The area of the Square is : " << Area() << endl;
    cout << "Length of a side: " << this->width << endl;
}
float Square::Area() const {
    return Shape2D::Area();
}
string Square::GetName2D() const {
    return name2D;
}

Triangle::Triangle(){
    name2D = "Triangle";
}
Triangle::Triangle(float b, float h){
    name2D = "Triangle";
    height = h;
    width = b;
    area = (1.0 / 2.0) * b * h;
}

void Triangle::Scale(float scaleFactor) {
    Shape::Scale(scaleFactor);
    area = (1.0 / 2.0) * width * height;
}
void Triangle::Display() const {
    cout << "The area of the Triangle is : " << Area() << endl;
    cout << "Base: " << this->width << endl;
    cout << "Height: " << this->height << endl;
}
float Triangle::Area() const {
    return Shape2D::Area();
}
string Triangle::GetName2D() const {
    return name2D;
}

Circle::Circle(){
    name2D = "Circle";
}
Circle::Circle(float r){
    name2D = "Circle";
    width = r;
    height = 2 * r; // Height is diameter
    area = PI * pow(r, 2);
}

void Circle::Scale(float scaleFactor) {
    Shape::Scale(scaleFactor);
    area = PI * pow(width, 2);
}
void Circle::Display() const {
    cout << "The area of the Circle is : " << Area() << endl;
    cout << "Radius: " << this->width << endl;
}
float Circle::Area() const {
    return Shape2D::Area();
}
string Circle::GetName2D() const {
    return name2D;
}

// 3D

Shape3D::Shape3D(){
    height = 0;
    width = 0;
    length = 0;
}

float Shape3D::Volume() const {
    return volume;
}
void Shape3D::ShowVolume() const{
    cout << "The volume of the " << GetName3D() << "is : " << endl;
    cout << Volume() << endl;
}

string Shape3D::GetName3D() const {
    return name3D;
}

bool Shape3D::operator>(const Shape3D &rhs) const{
    return (this->Volume() > rhs.Volume());
}
bool Shape3D::operator<(const Shape3D &rhs) const{
    return (this->Volume() < rhs.Volume());
}
bool Shape3D::operator==(const Shape3D &rhs) const{
    return (this->Volume() == rhs.Volume());
}

// 3D Shapes

TriangularPyramid::TriangularPyramid(){
    name2D = "Triangle";
    name3D = "Triangular Pyramid";
}
TriangularPyramid::TriangularPyramid(float l, float b, float h){
    name2D = "Triangle";
    name3D = "Triangular Pyramid";
    area = (1.0 / 2.0) * b * h;
    volume = (1.0 / 3.0) * area * l;
    height = h;
    width = b;
    length = l;
}

void TriangularPyramid::Scale(float scaleFactor) {
    Shape::Scale(scaleFactor);
    area = (1.0 / 2.0) * width * height;
    volume = (1.0 / 3.0) * area * length;
}
void TriangularPyramid::Display() const {
    cout << "The volume of the TriangularPyramid is : " << Volume() << endl;
    cout << "The height is: " << this->length << endl;
    cout << "The area of the Triangle is : " << Area() << endl;
    cout << "Base: " << this->width << endl;
    cout << "Height: " << this->height << endl;
}
float TriangularPyramid::Area() const {
    return Shape2D::Area();
}
string TriangularPyramid::GetName2D() const {
    return name2D;
}
float TriangularPyramid::Volume() const {
    return Shape3D::Volume();
}
string TriangularPyramid::GetName3D() const {
    return name3D;
}

Cylinder::Cylinder(){
    name2D = "Circle";
    name3D = "Cylinder";
}
Cylinder::Cylinder(float h, float r){
    name2D = "Circle";
    name3D = "Cylinder";
    width = r;
    height = h;
    length = 2 * r;
    area = PI * pow(r, 2);
    volume = area * h;
}

void Cylinder::Scale(float scaleFactor) {
    Shape::Scale(scaleFactor);
    area = PI * pow(width, 2);
    volume = area * height;
}
void Cylinder::Display() const {
    cout << "The volume of the Cylinder is : " << Volume() << endl;
    cout << "The height is: " << this->height << endl;
    cout << "The area of the Circle is : " << Area() << endl;
    cout << "Radius: " << this->width << endl;
}
float Cylinder::Area() const {
    return Shape2D::Area();
}
string Cylinder::GetName2D() const {
    return name2D;
}
float Cylinder::Volume() const {
    return Shape3D::Volume();
}
string Cylinder::GetName3D() const {
    return name3D;
}

Sphere::Sphere(){
    name2D = "Circle";
    name3D = "Sphere";
}
Sphere::Sphere(float r){
    name2D = "Circle";
    name3D = "Sphere";
    width = r;
    height = length = 2 * r;
    area = PI * pow(r, 2);
    volume = (4.0 / 3.0) * area * r;
}

void Sphere::Scale(float scaleFactor) {
    Shape::Scale(scaleFactor);
    area = PI * pow(width, 2);
    volume = (4.0 / 3.0) * area * width;
}
void Sphere::Display() const {
    cout << "The volume of the Sphere is : " << Volume() << endl;
    cout << "The area of the Circle is : " << Area() << endl;
    cout << "Radius: " << this->width << endl;
}
float Sphere::Area() const {
    return Shape2D::Area();
}
string Sphere::GetName2D() const {
    return name2D;
}
float Sphere::Volume() const {
    return Shape3D::Volume();
}
string Sphere::GetName3D() const {
    return name3D;
}
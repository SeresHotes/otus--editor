#pragma once

#include <string>
#include <vector>

struct Point {
    int x;
    int y;
};

struct Line {
    Point a;
    Point b;
};

struct Circle {
    Point center;
    double radius;
};

struct Text {
    std::string text;
};

struct Polygon {
    std::vector<Point> points;
};

#include <variant>

using Primitive = std::variant<Line, Circle, Text, Polygon>;
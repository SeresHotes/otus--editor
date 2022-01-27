#pragma once

#include <string>
#include <vector>
#include <variant>


namespace editor {
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


    using Primitive = std::variant<Line, Circle, Text, Polygon>;
}
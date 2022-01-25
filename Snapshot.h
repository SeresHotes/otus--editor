#pragma once

#include <list>
#include "Primitives.h"

struct Snapshot {
    std::list<Line> lines;
    std::list<Circle> circles;
    std::list<Text> texts;
    std::list<Polygon> polygons;
};
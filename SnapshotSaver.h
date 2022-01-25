#pragma once

#include "Snapshot.h"



std::ostream& operator<<(std::ostream& out, const Point& p) {
    out << p.x << " " << p.y;
    return out;
}
std::ostream& operator<<(std::ostream& out, const Line& line) {
    out << line.a << " " << line.b;
    return out;
}
std::ostream& operator<<(std::ostream& out, const Circle& c) {
    out << c.center << " " << c.radius;
    return out;
}
std::ostream& operator<<(std::ostream& out, const Text& t) {
    out << t.text;
    return out;
}
std::ostream& operator<<(std::ostream& out, const Polygon& pol) {
    out << pol.points.size();
    for (const auto& p : pol.points) {
        out << " " << p;
    }
    return out;
}

std::istream& operator>>(std::istream& in, Point& p) {
    in >> p.x >> p.y;
    return in;
}
std::istream& operator>>(std::istream& in, Line& line) {
    in >> line.a >> line.b;
    return in;
}
std::istream& operator>>(std::istream& in, Circle& c) {
    in >> c.center >> c.radius;
    return in;
}
std::istream& operator>>(std::istream& in, Text& t) {
    in >> t.text;
    return in;
}
std::istream& operator>>(std::istream& in, Polygon& pol) {
    pol.points.clear();
    size_t size;
    in >> size;
    for (size_t i = 0; i < size; i++) {
        Point p;
        in >> p;
        pol.points.push_back(p);
    }
    return in;
}
class SnapshotSaver {
private:
    template<class T>
    static void save_container(std::ostream& out, const T& c) {
        out << c.size() << "\n";
        for (const auto& el : c) {
            out << el << "\n";
        }
    }
    template<class T>
    static std::list<T> load_container(std::istream& in) {
        std::list<T> cont;
        size_t size;
        in >> size;

        for (size_t i = 0; i < size; i++) {
            T c;
            in >> c;
            cont.push_back(c);
        }
        return cont;
    }

public:

    static void save(std::ostream& out, Snapshot s) {
        save_container(out, s.lines);
        save_container(out, s.circles);
        save_container(out, s.texts);
        save_container(out, s.polygons);
    }
    static Snapshot load(std::istream& in) {
        Snapshot s;
        s.lines = load_container<Line>(in);
        s.circles = load_container<Circle>(in);
        s.texts = load_container<Text>(in);
        s.polygons = load_container<Polygon>(in);
        return s;
    }
};
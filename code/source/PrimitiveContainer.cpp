#include "PrimitiveContainer.h"


namespace editor {

    std::list<Primitive>::iterator PrimitiveContainer::add(const Primitive& primitive) {
        primList.push_back(primitive);
        auto it = primList.end();
        it--;

        primMap[&*it] = it;
        return it;
    }

    void PrimitiveContainer::remove(const Primitive& primitive) {
        primList.erase(primMap.at(&primitive));
        primMap.erase(&primitive);
    }

    Snapshot PrimitiveContainer::makeSnapshot() {
        Snapshot s = {};
        for (const auto& x : primList) {
            if (const Line* line = std::get_if<Line>(&x)) {
                s.lines.push_back(*line);
            } else if (const Circle* circle = std::get_if<Circle>(&x)) {
                s.circles.push_back(*circle);
            } else if (const Text* text = std::get_if<Text>(&x)) {
                s.texts.push_back(*text);
            } else if (const Polygon* polygon = std::get_if<Polygon>(&x)) {
                s.polygons.push_back(*polygon);
            }
        }

        return s;
    }
    void PrimitiveContainer::restore(const Snapshot& s) {
        primList.clear();
        primMap.clear();
        primList.insert(primList.end(), s.lines.begin(), s.lines.end());
        primList.insert(primList.end(), s.circles.begin(), s.circles.end());
        primList.insert(primList.end(), s.texts.begin(), s.texts.end());
        primList.insert(primList.end(), s.polygons.begin(), s.polygons.end());

        for (auto it = primList.begin(); it != primList.end(); it++) {
            primMap.emplace(&*it, it);
        }
    }

}
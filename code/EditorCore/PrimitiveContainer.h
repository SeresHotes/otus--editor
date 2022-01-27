#pragma once

#include <list>
#include <unordered_map>

#include "Primitives.h"
#include "Snapshot.h"


namespace editor {

    class PrimitiveContainer {
    private:
        std::list<Primitive> primList;
        std::unordered_map<const Primitive*, typename std::list<Primitive>::iterator> primMap;
    public:
        std::list<Primitive>::iterator add(const Primitive& primitive);

        void remove(const Primitive& primitive);

        Snapshot makeSnapshot();

        void restore(const Snapshot& s);

    };

}
#pragma once

#include "Snapshot.h"
#include <iostream>

namespace editor {

    namespace SnapshotSaver {

        void save(std::ostream& out, Snapshot s);
        Snapshot load(std::istream& in);
    };

}
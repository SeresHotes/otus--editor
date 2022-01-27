#pragma once

#include <unordered_map>
#include <fstream>

#include "IModel.h"
#include "IView.h"
#include "PrimitiveContainer.h"
#include "SnapshotSaver.h"


namespace editor {
    class Model : public IModel {
        PrimitiveContainer& container;
        IViewModel& view;
    public:
        Model(PrimitiveContainer& container, IViewModel& view) : container(container), view(view) {

        }
        void addPrimitive(Primitive primitive) override {
            auto it = container.add(primitive);
            view.messageAddPrimitive(*it);
        }
        void removePrimitive(const Primitive& primitive) override {
            view.messageRemovePrimitive(primitive);
            container.remove(primitive);
        }
        void saveTo(std::string filename) override {
            std::ofstream fout(filename);
            SnapshotSaver::save(fout, container.makeSnapshot());
        }
        void loadFrom(std::string filename) override {
            std::ifstream fin(filename);
            container.restore(SnapshotSaver::load(fin));
        }
    };
}
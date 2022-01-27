#pragma once
#include "ConsoleView.h"
#include "Model.h"
#include "SnapshotSaver.h"
#include "PrimitiveContainer.h"

namespace editor {
    class Application {
        PrimitiveContainer container;
        Model model;
        ConsoleView view;
        ConsoleViewModel viewModel;
        ConsoleController controller;

    public:
        Application() :
            model(container, viewModel),
            view(),
            viewModel(model, view),
            controller(viewModel) {

        }
        void start() {
            while (controller.handleInput()) {

            }
        }
    };
}
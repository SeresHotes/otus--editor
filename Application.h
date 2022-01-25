#pragma once
#include "ConsoleView.h"
#include "Model.h"
#include "SnapshotSaver.h"
#include "PrimitiveContainer.h"

class Application {
    PrimitiveContainer container;
    UseCase useCase;
    ConsoleView view;
    ConsoleViewModel viewModel;
    ConsoleController controller;

public:
    Application() : 
        useCase(container, viewModel), 
        view(),
        viewModel(useCase, view), 
        controller(viewModel) 
    {

    }
    void start() {
        while (controller.handleInput()) {

        }
    }
};
#pragma once

#include <sstream>
#include <unordered_set>
#include <iostream>

#include "IView.h"
#include "IModel.h"

enum class MenuState {
    global,
    print,
    add,
    remove
};

class IConsoleView {
public:
    virtual void messageAddPrimitive(const Primitive& primitive) = 0;
    virtual void messageRemovePrimitive() = 0;
    virtual void printPrimitive(const Primitive& primitive) = 0;
    virtual void updateMenu(MenuState state) = 0;
};

class IConsoleViewModel {
public:
    virtual ~IConsoleViewModel() = default;
    virtual bool handleInput(std::string str) = 0;
};

class ConsoleViewModel : public IViewModel, public IConsoleViewModel {
    std::unordered_set<const Primitive*> primitives;
    IUseCase& useCase;
    IConsoleView& view;


    MenuState state = MenuState::global;

public:
    ConsoleViewModel(IUseCase& useCase, IConsoleView& view) : useCase(useCase), view(view) {
        view.updateMenu(MenuState::global);
    }
    void messageAddPrimitive(const Primitive& primitive) override {
        primitives.emplace(&primitive);
        view.messageAddPrimitive(primitive);
    }
    void messageRemovePrimitive(const Primitive& primitive) override {
        primitives.erase(&primitive);
        view.messageRemovePrimitive();
    }
    void printAllPrimitives() {
        for (const auto& x : primitives) {
            view.printPrimitive(*x);
        }
    }

    bool handleInput(std::string str) {
        std::stringstream sstream(str);
        std::string word;
        sstream >> word;
        if (state == MenuState::global) {
            if (word == "add") {
                state = MenuState::add;
            } else if (word == "remove") {
                state = MenuState::remove;
            } else if (word == "print") {
                state = MenuState::print;
            } else if (word == "exit") {
                return false;
            }
        } else if (state == MenuState::add) {
            if (word == "back") {
                state = MenuState::global;
            } else if (word == "line") {
                Line line;
                sstream >> line.a.x >> line.a.y >> line.b.x >> line.b.y;
                useCase.addPrimitive(line);
            }
        } else if (state == MenuState::print) {
            if (word == "back") {
                state = MenuState::global;
            } else if (word == "all") {
                printAllPrimitives();
            }
        }
        view.updateMenu(state);

        return true;
    }
};

class ConsoleController {
    IConsoleViewModel& vm;
public:
    ConsoleController(IConsoleViewModel& vm) : vm(vm) {
        
    }

    bool handleInput() {
        std::string str;
        std::getline(std::cin, str);
        return vm.handleInput(str);
    }
};

class ConsoleView : public IConsoleView {
public:
    ConsoleView() {
    }
    void messageAddPrimitive(const Primitive& primitive) override {
        std::cout << "Added" << std::endl;
    }
    void messageRemovePrimitive() override {
        std::cout << "Removed" << std::endl;
    }

    void printPrimitive(const Primitive& primitive) override {
        if (const Line* line = std::get_if<Line>(&primitive)) {
            std::cout << "line: (" << line->a.x << ", " << line->a.y << ") - ("
                                   << line->b.x << ", " << line->b.y << ")" << std::endl;
        
        } else if (const Circle* circle = std::get_if<Circle>(&primitive)) {
            std::cout << "circle: center = (" << circle->center.x << ", " << circle->center.y;
            std::cout << "), radius = " << circle->radius << std::endl;
        
        } else if (const Text* text = std::get_if<Text>(&primitive)) {
            std::cout << "text: \"" << text << "\"" << std::endl;
        
        } else if (const Polygon* polygon = std::get_if<Polygon>(&primitive)) {
            std::cout << "polygon: points:" << std::endl;
            for (const auto& point : polygon->points) {
                std::cout << point.x << ", " << point.y << std::endl;
            }
        }
    }

    void updateMenu(MenuState state) override {
        if (state == MenuState::global) {
            std::cout << "Choose option: exit, add, remove, print" << std::endl;
        } else if (state == MenuState::add) {
            std::cout << "Choose add option: back, line" << std::endl;
        } else if (state == MenuState::print) {
            std::cout << "Choose add option: back, all" << std::endl;
        }
    }
};
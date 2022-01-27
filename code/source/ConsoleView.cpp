
#include "ConsoleView.h"

#include <sstream>
#include <unordered_set>
#include <iostream>

#include "IView.h"
#include "IModel.h"

namespace editor {

    ConsoleViewModel::ConsoleViewModel(IModel& model, IConsoleView& view) : model(model), view(view) {
        state = MenuState::global;
        view.updateMenu(state);
    }
    void ConsoleViewModel::messageAddPrimitive(const Primitive& primitive) {
        size_t size = primitives_to_index.size();
        primitives_to_index.emplace(&primitive, size);
        index_to_primitives.emplace_back(&primitive);

        view.messageAddPrimitive(primitive);
    }
    void ConsoleViewModel::messageRemovePrimitive(const Primitive& primitive) {
        size_t index = primitives_to_index.at(&primitive);
        size_t last = primitives_to_index.size() - 1;

        std::swap(index_to_primitives[index], index_to_primitives[last]);
        std::swap(primitives_to_index[index_to_primitives[index]],
                  primitives_to_index[index_to_primitives[last]]);

        primitives_to_index.erase(&primitive);
        index_to_primitives.pop_back();

        view.messageRemovePrimitive();
    }
    void ConsoleViewModel::printAllPrimitives() {
        int index = 0;
        for (const auto& x : index_to_primitives) {
            
            view.printPrimitiveWithIndex(++index, *x);
        }
    }

    bool ConsoleViewModel::handleInput(std::string str) {
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
                model.addPrimitive(line);
            }
        } else if (state == MenuState::print) {
            if (word == "back") {
                state = MenuState::global;
            } else if (word == "all") {
                printAllPrimitives();
            }
        } else if (state == MenuState::remove) {
            if (word == "back") {
                state = MenuState::global;
            } else {
                int number = 0;
                bool is_number_ok = false;
                size_t size = index_to_primitives.size();
                try {
                    number = std::stoi(word);
                    is_number_ok = true;
                } catch ([[maybe_unused]] const std::invalid_argument& e) {
                } catch ([[maybe_unused]] const std::out_of_range& e) {
                }
                if (is_number_ok && (number < 1 || (size_t)number > size)) {
                    is_number_ok = false;
                }

                if (!is_number_ok) {
                    view.errorMessage(std::string("you should write number between 1 and ") + std::to_string(size));
                } else {
                    model.removePrimitive(*index_to_primitives[(size_t)number - 1]);
                }

                
            }
        }
        view.updateMenu(state);

        if (state == MenuState::remove) {
            printAllPrimitives();
        }

        return true;
    }


    void ConsoleView::messageAddPrimitive([[maybe_unused]] const Primitive& primitive) {
        std::cout << "Added" << std::endl;
    }
    void ConsoleView::messageRemovePrimitive() {
        std::cout << "Removed" << std::endl;
    }

    void ConsoleView::printPrimitiveWithIndex(int index, const Primitive& primitive) {
        std::cout << index << ": \t";
        printPrimitive(primitive);
    }

    void ConsoleView::printPrimitive(const Primitive& primitive) {
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

    void ConsoleView::updateMenu(MenuState state) {
        if (state == MenuState::global) {
            std::cout << "Choose option: exit, add, remove, print" << std::endl;
        } else if (state == MenuState::add) {
            std::cout << "Choose add option: back, line" << std::endl;
        } else if (state == MenuState::print) {
            std::cout << "Choose add option: back, all" << std::endl;
        } else if (state == MenuState::remove) {
            std::cout << "Choose back or a number" << std::endl;
        }
    }

    void ConsoleView::errorMessage(std::string str) {
        std::cout << "Error: " << str << std::endl;
    }

}
#pragma once

#include <sstream>
#include <unordered_set>
#include <unordered_map>
#include <iostream>

#include "IView.h"
#include "IModel.h"

namespace editor {
    enum class MenuState {
        global,
        print,
        add,
        remove
    };

    class IConsoleView {
    public:
        virtual ~IConsoleView() = default;
        virtual void messageAddPrimitive(const Primitive& primitive) = 0;
        virtual void messageRemovePrimitive() = 0;
        virtual void printPrimitiveWithIndex(int index, const Primitive& primitive) = 0;
        virtual void printPrimitive(const Primitive& primitive) = 0;
        virtual void updateMenu(MenuState state) = 0;
        virtual void errorMessage(std::string str) = 0;
    };

    class IConsoleViewModel {
    public:
        virtual ~IConsoleViewModel() = default;
        virtual bool handleInput(std::string str) = 0;
    };

    class ConsoleViewModel : public IViewModel, public IConsoleViewModel {
        std::unordered_map<const Primitive*, size_t> primitives_to_index;
        std::vector<const Primitive*> index_to_primitives;
        IModel& model;
        IConsoleView& view;


        MenuState state;

        void printAllPrimitives();

    public:
        ConsoleViewModel(IModel& model, IConsoleView& view);

        void messageAddPrimitive(const Primitive& primitive) override;

        void messageRemovePrimitive(const Primitive& primitive) override;

        bool handleInput(std::string str);
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
        void messageAddPrimitive(const Primitive& primitive) override;

        void messageRemovePrimitive() override;

        void printPrimitiveWithIndex(int index, const Primitive& primitive) override;

        void printPrimitive(const Primitive& primitive) override;

        void updateMenu(MenuState state) override;

        void errorMessage(std::string str) override;
    };

}
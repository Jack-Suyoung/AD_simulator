#ifndef VISUALIZER_HPP
#define VISUALIZER_HPP

#include "../00_SimulatorManager/SimulatorManager.hpp"
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

class Visualizer {
public:
    Visualizer();
    ~Visualizer();
    void Run(SimulatorManager& simulator);

private:
    GLFWwindow* window_;
    void Render(SimulatorManager& simulator);
};

#endif // VISUALIZER_HPP

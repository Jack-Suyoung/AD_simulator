#ifndef VISUALIZER_HPP
#define VISUALIZER_HPP

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

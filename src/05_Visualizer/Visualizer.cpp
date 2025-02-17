#include "Visualizer.hpp"

Visualizer::Visualizer() {
    // GLFW 초기화
    if (!glfwInit()) return;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window_ = glfwCreateWindow(1280, 720, "Autonomous Driving Visualizer", nullptr, nullptr);
    if (!window_) {
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window_);

    // ImGui 초기화
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window_, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

Visualizer::~Visualizer() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window_);
    glfwTerminate();
}

void Visualizer::Run(SimulatorManager& simulator) {
    while (!glfwWindowShouldClose(window_)) {
        glfwPollEvents();

        // 시뮬레이션 업데이트
        simulator.Update();

        // ImGui 새 프레임
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // UI 요소
        Render(simulator);

        // 렌더링
        ImGui::Render();
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window_);
    }
}

void Visualizer::Render(SimulatorManager& simulator) {
    const VehicleState_t& state = simulator.GetVehicleState();

    ImGui::Begin("Simulation State");
    ImGui::Text("Frame Count: %d", simulator.GetCurrentFrame());
    ImGui::Text("Position X: %.2f", state.Global_X_m);
    ImGui::Text("Position Y: %.2f", state.Global_Y_m);
    ImGui::Text("Heading: %.2f rad", state.Global_Heading_rad);
    ImGui::Text("Speed: %.2f m/s", state.speed_mps);
    ImGui::Text("Steering: %.2f rad", state.FrontWhlAng_rad);
    ImGui::End();
}

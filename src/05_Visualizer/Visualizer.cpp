#include <iostream>
#include <vector>
#include <cmath>
#include <thread>

#include "../00_SimulatorManager/SimulatorManager.hpp"
#include "../imgui/imgui.h"
#include "external/implot/implot.h"
#include "external/implot/implot_internal.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

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
    ImPlot::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window_, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

Visualizer::~Visualizer() {
    ImPlot::DestroyContext();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window_);
    glfwTerminate();
}

void Visualizer::Run(SimulatorManager& simulator) {
    while (!glfwWindowShouldClose(window_)) {
        auto start_time = std::chrono::high_resolution_clock::now();  // 🔹 시작 시간 기록

        glfwPollEvents();

        // 시뮬레이션 업데이트
        simulator.Update();
        simulator.PrintFrame();

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

        // 🔹 0.3초(300ms) 대기
        std::this_thread::sleep_for(std::chrono::milliseconds(150));

        auto end_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed_time = end_time - start_time;
        std::cout << "Frame Time: " << elapsed_time.count() << "s" << std::endl;
    }
}

    // Global 좌표계 기반 Plot
void Visualizer::Render(SimulatorManager& simulator) {
    const VehicleState_t& ego_state = simulator.GetVehicleState();
    const VizDebug_t& viz_debug = simulator.GetVizDebug();
    const MapInfo& map_info = simulator.GetMapInfo();

    // ImGui::Begin("Simulation State");
    // ImGui::Text("Frame Count: %d", simulator.GetCurrentFrame());
    // ImGui::Text("Position X: %.2f", ego_state.Global_X_m);
    // ImGui::Text("Position Y: %.2f", ego_state.Global_Y_m);
    // ImGui::Text("Heading: %.2f rad", ego_state.Global_Heading_rad);
    // ImGui::Text("Speed: %.2f m/s", ego_state.speed_mps);
    // ImGui::Text("Steering: %.2f rad", ego_state.FrontWhlAng_rad);
    // ImGui::End();

    ImGui::Begin("Global Path Visualization");

        // X, Y 범위 설정을 위해 최소/최대 값 계산
        float x_min = std::numeric_limits<float>::max();
        float x_max = std::numeric_limits<float>::lowest();
        float y_min = std::numeric_limits<float>::max();
        float y_max = std::numeric_limits<float>::lowest();
    
        auto update_bounds = [&](const std::vector<Point>& points) {
            for (const auto& pt : points) {
                if (pt.x < x_min) x_min = pt.x;
                if (pt.x > x_max) x_max = pt.x;
                if (pt.y < y_min) y_min = pt.y;
                if (pt.y > y_max) y_max = pt.y;
            }
        };
    
        // 모든 데이터에서 X, Y 범위 업데이트
        update_bounds(map_info.center_line);
        update_bounds(viz_debug.stPathPlanningGlobal);
    
        // Ego Vehicle 포함
        x_min = std::min(x_min, static_cast<float>(ego_state.Global_X_m));
        x_max = std::max(x_max, static_cast<float>(ego_state.Global_X_m));
        y_min = std::min(y_min, static_cast<float>(ego_state.Global_Y_m));
        y_max = std::max(y_max, static_cast<float>(ego_state.Global_Y_m));
    
        // XY 축을 동일 비율로 유지하도록 설정
        float x_range = x_max - x_min;
        float y_range = y_max - y_min;
        float max_range = std::max(x_range, y_range);
        float x_center = (x_max + x_min) / 2.0f;
        float y_center = (y_max + y_min) / 2.0f;

    // Figure 설정
    ImVec2 plot_size = ImVec2(600, 600);
    if (ImPlot::BeginPlot("Global Path", plot_size)) {
        ImPlot::SetupAxes("X", "Y");
        ImPlot::SetupAxesLimits(
            ego_state.Global_X_m - 15.0, ego_state.Global_X_m + 15.0,
            ego_state.Global_Y_m - 15.0, ego_state.Global_Y_m + 15.0,
            ImGuiCond_Always
        );
        
        // Reference Path (Center Line) 플롯
        // 🔹 Reference Path (Dashed Line) 플롯
        std::vector<float> ref_x, ref_y;
        float dash_length = 5.0;  // 선의 길이
        float gap_length = 2.0;   // 비어있는 공간 길이
        bool draw_line = true;    // 선을 그릴지 여부

        for (size_t i = 0; i < map_info.center_line.size() - 1; ++i) {
            double dx = map_info.center_line[i + 1].x - map_info.center_line[i].x;
            double dy = map_info.center_line[i + 1].y - map_info.center_line[i].y;
            double segment_length = sqrt(dx * dx + dy * dy);
            double unit_x = dx / segment_length;
            double unit_y = dy / segment_length;
            double remaining_length = segment_length;

            double current_x = map_info.center_line[i].x;
            double current_y = map_info.center_line[i].y;

            while (remaining_length > 0) {
                double draw_segment_length = draw_line ? dash_length : gap_length;
                draw_segment_length = std::min(draw_segment_length, remaining_length);

                double next_x = current_x + unit_x * draw_segment_length;
                double next_y = current_y + unit_y * draw_segment_length;

                if (draw_line) {
                    std::vector<float> segment_x = {static_cast<float>(current_x), static_cast<float>(next_x)};
                    std::vector<float> segment_y = {static_cast<float>(current_y), static_cast<float>(next_y)};

                    ImPlot::PushStyleColor(ImPlotCol_Line, ImVec4(0.7f, 0.7f, 0.7f, 1.0f)); // 회색
                    ImPlot::PushStyleVar(ImPlotStyleVar_LineWeight, 1.5f); // 두꺼운 선
                    ImPlot::PlotLine("Reference Path", segment_x.data(), segment_y.data(), segment_x.size());
                    ImPlot::PopStyleVar();
                    ImPlot::PopStyleColor();
                }

                current_x = next_x;
                current_y = next_y;
                remaining_length -= draw_segment_length;
                draw_line = !draw_line; // 다음 구간을 반대로 설정
            }
        }

        std::vector<float> lft_lane_x, lft_lane_y;
        for (const auto& pt : map_info.left_lane) {
            lft_lane_x.push_back(pt.x);
            lft_lane_y.push_back(pt.y);
        }


        std::vector<float> right_lane_x, right_lane_y;
        for (const auto& pt : map_info.right_lane) {
            right_lane_x.push_back(pt.x);
            right_lane_y.push_back(pt.y);
        }

        ImPlot::PushStyleColor(ImPlotCol_Line, ImVec4(0.5f, 0.5f, 0.5f, 1.0f)); // 회색
        ImPlot::PushStyleVar(ImPlotStyleVar_LineWeight, 3.0f); // 두꺼운 선

        ImPlot::PlotLine("Left Lane", lft_lane_x.data(), lft_lane_y.data(), lft_lane_x.size());
        ImPlot::PlotLine("Right Lane", right_lane_x.data(), right_lane_y.data(), right_lane_x.size());

        ImPlot::PopStyleVar();   // 선 두께 설정 해제
        ImPlot::PopStyleColor(); // 색상 설정 해제




         // 차량을 사각형으로 표현
         const double car_width = 2.0;
         const double car_length = 5.0;
         double theta = ego_state.Global_Heading_rad;
 
         // 차량의 꼭짓점 계산
         std::vector<Point> car_corners = {
             { -car_length / 2, -car_width / 2 }, // Rear Left
             {  car_length / 2, -car_width / 2 }, // Front Left
             {  car_length / 2,  car_width / 2 }, // Front Right
             { -car_length / 2,  car_width / 2 }, // Rear Right
             { -car_length / 2, -car_width / 2 }  // 다시 Rear Left로 연결 (완전한 사각형)
         };
 
         std::vector<float> car_x, car_y;
         for (const auto& corner : car_corners) {
             double global_x = ego_state.Global_X_m + cos(theta) * corner.x - sin(theta) * corner.y;
             double global_y = ego_state.Global_Y_m + sin(theta) * corner.x + cos(theta) * corner.y;
             car_x.push_back(global_x);
             car_y.push_back(global_y);
         }
 
         ImPlot::PlotLine("Ego Vehicle", car_x.data(), car_y.data(), car_x.size());
 
         // 🔹 앞바퀴 타원 추가 (휠 조향각 반영)
         double wheel_radius_x = 0.8;  // 타원의 가로 반경
         double wheel_radius_y = 0.3;  // 타원의 세로 반경
         double front_wheel_angle = ego_state.FrontWhlAng_rad; // Front Wheel Angle
 
         // 앞바퀴 중심 위치 계산
         double front_wheel_x = ego_state.Global_X_m + cos(theta) * (car_length / 2);
         double front_wheel_y = ego_state.Global_Y_m + sin(theta) * (car_length / 2);
 
         // 타원형 휠을 구성하는 점 계산
         std::vector<float> wheel_x, wheel_y;
         for (double angle = 0; angle <= 2 * M_PI; angle += 0.2) {
             double local_x = wheel_radius_x * cos(angle);
             double local_y = wheel_radius_y * sin(angle);
             double rotated_x = front_wheel_x + cos(front_wheel_angle) * local_x - sin(front_wheel_angle) * local_y;
             double rotated_y = front_wheel_y + sin(front_wheel_angle) * local_x + cos(front_wheel_angle) * local_y;
             wheel_x.push_back(rotated_x);
             wheel_y.push_back(rotated_y);
         }
 
         ImPlot::PlotLine("Front Wheel", wheel_x.data(), wheel_y.data(), wheel_x.size());
 




        // Path Planning 결과 플롯
        std::vector<float> global_x, global_y;
        for (const auto& pt : viz_debug.stPathPlanningGlobal) {
            global_x.push_back(pt.x);
            global_y.push_back(pt.y);
        }
        ImPlot::PlotLine("Planned Path (Global)", global_x.data(), global_y.data(), global_x.size());

        ImPlot::EndPlot();
    }

    ImGui::End();
}


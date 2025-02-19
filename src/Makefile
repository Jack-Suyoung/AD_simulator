CC = g++
CFLAGS = -I. -Iexternal/implot -Iimgui -Iexternal/eigen \
         -I00_SimulatorManager -I01_LocalMapGenerator -I02_BehaviorPlanning \
         -I03_PlanningAndControl -I04_VehicleStateUpdate -I05_Visualizer \
         -Wall -Wextra -std=c++17 -g

LDFLAGS = -lglfw -lGLEW -lGL -lm

SRC = main.cpp \
      00_Common/CommonFunc.cpp \
      00_SimulatorManager/SimulatorManager.cpp \
      01_LocalMapGenerator/MapGenerator.cpp \
      01_LocalMapGenerator/LoadMapData.cpp \
      02_BehaviorPlanning/BehaviorPlanning.cpp \
      03_PlanningAndControl/PlanningAndControl.cpp \
      03_PlanningAndControl/LateralControl.cpp \
      04_VehicleStateUpdate/VehicleStateUpdate.cpp \
      04_VehicleStateUpdate/KinematicBicycleModel.cpp \
      05_Visualizer/Visualizer.cpp \
      imgui/imgui.cpp \
      imgui/imgui_draw.cpp \
      imgui/imgui_widgets.cpp \
      imgui/imgui_tables.cpp \
      imgui/imgui_impl_glfw.cpp \
      imgui/imgui_impl_opengl3.cpp \
      external/implot/implot.cpp \
      external/implot/implot_items.cpp  # 🔹 ImPlot 추가

OBJ = $(SRC:.cpp=.o)

TARGET = ad_simulator

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $(TARGET) $(OBJ) $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

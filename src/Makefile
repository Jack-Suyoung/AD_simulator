# 컴파일러 및 옵션 설정
CC = g++
CFLAGS = -I . -I 02_BehaviorPlanning -I 01_LocalMapGenerator -Wall -Wextra -std=c++17

# 소스 및 객체 파일 경로 설정
SRC = main.cpp \
	01_LocalMapGenerator/LoadMapData.cpp \
	01_LocalMapGenerator/LocalMapGenerator.cpp \
	02_BehaviorPlanning/BehaviorPlanning.cpp

OBJ = $(SRC:.cpp=.o)

# 실행 파일 이름
TARGET = ad_simulator

# 기본 빌드 규칙
all: $(TARGET)

# 실행 파일 생성 규칙
$(TARGET): $(OBJ)
	$(CC) -o $(TARGET) $(OBJ)

# .cpp -> .o 변환 규칙 (경로 인식 문제 해결)
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# 정리 규칙
clean:
	rm -f $(OBJ) $(TARGET)

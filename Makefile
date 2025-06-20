BUILD     := build
OBJ_DIR   := $(BUILD)/objects
APP_DIR   := $(BUILD)
TARGET    := app
INCLUDE   := -Iinclude/
SRC       := $(wildcard src/*.cpp)
OBJECTS   := $(patsubst src/%.cpp,$(OBJ_DIR)/%.o,$(SRC))

CXX       := g++
CXXFLAGS  := -Wall -Wextra -Werror
LDFLAGS   := -lm

all: $(APP_DIR)/$(TARGET)
	clear
	echo "Executando $(APP_DIR)/$(TARGET)..."
	/usr/bin/time -v ./$(APP_DIR)/$(TARGET)

run: $(APP_DIR)/$(TARGET)
	clear
	/usr/bin/time -v ./$(APP_DIR)/$(TARGET)

.PHONY: all clean run
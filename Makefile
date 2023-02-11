SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin
SDL_DIR := /opt/homebrew/Cellar

EXE := $(BIN_DIR)/main
SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

CXX       := g++
TARGET    := -target arm64-apple-macos11
FRAMEWORK := -framework ApplicationServices
CPPFLAGS  := -I $(SDL_DIR)/curl/7.85.0/include/curl -I $(SDL_DIR)/sdl2/2.24.1/include/SDL2 -I $(SDL_DIR)/sdl2_ttf/2.20.1/include/SDL2 -I $(SDL_DIR)/sdl2_image/2.6.2/include/SDL2 -I $(SDL_DIR)/sdl2_mixer/2.6.2/include/SDL2 -Iinc -MMD -MP
CXXFLAGS  := -Wall -Wextra -std=c++17 -ggdb $(TARGET)
LDFLAGS   := -Llib -L $(SDL_DIR)/curl/7.85.0/lib -L $(SDL_DIR)/sdl2/2.24.1/lib -L $(SDL_DIR)/sdl2_ttf/2.20.1/lib -L $(SDL_DIR)/sdl2_image/2.6.2/lib -L $(SDL_DIR)/sdl2_mixer/2.6.2/lib
LDLIBS    := -l curl -l SDL2-2.0.0 -l SDL2_ttf -l SDL2_image-2.0.0 -l SDL2_mixer-2.0.0

.PHONY: all clean run

all: $(EXE)

$(EXE): $(OBJ) | $(BIN_DIR)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) $(TARGET) $(FRAMEWORK) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

clean:
	@$(RM) -rv $(BIN_DIR) $(OBJ_DIR)

run:
	$(EXE)

-include $(OBJ:.o=.d)





# BIN = bin
# CXX = g++
# EXE = main
# SDL = /opt/homebrew/Cellar
# INC = -I $(SDL)/sdl2/2.0.14_1/include/SDL2 -I $(SDL)/sdl2_image/2.0.5/include/SDL2 -I $(SDL)/sdl2_mixer/2.0.4/include/SDL2 -Iinc 
# LIB = -L $(SDL)/sdl2/2.0.14_1/lib -L $(SDL)/sdl2_image/2.0.5/lib -L $(SDL)/sdl2_mixer/2.0.4/lib
# LIBS = -l SDL2-2.0.0 -l SDL2_image-2.0.0 -l SDL2_mixer-2.0.0
# SET = -std=c++17 -Wall -Wextra -target arm64-apple-macos11
# SRC = src/*.cpp

# all: $(BIN)/$(EXE)

# $(BIN)/$(EXE): $(SRC)
# 	$(CXX) $(SET) $(INC) $(LIB) $^ -o $@ $(LIBS)

# run: clean all
# 	clear
# 	./$(BIN)/$(EXE)

# .PHONY: clean
# clean:
# 	rm $(BIN)/*

# g++ -std=c++17 src/Main.cpp -o main -I include -I include/SDL2 -L lib -l SDL2-2.0.0
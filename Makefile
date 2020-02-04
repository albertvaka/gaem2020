
EXEC	= bin/gaem2020

SRC	= $(wildcard src/*.cpp)
OBJ	= $(patsubst src/%, obj/%.o, $(SRC))

IMGUI_SRC = $(wildcard imgui*/*.cpp)
IMGUI_OBJ = $(patsubst imgui/%, obj/imgui/%.o, $(patsubst imgui_sfml/%, obj/imgui_sfml/%.o, $(IMGUI_SRC)))

OPTIM	= 0
DEBUG	= 1
PROFILE	= 0

# Bash so we can use curly braces expansion
SHELL = bash
CXX	= g++

CFLAGS	= -pipe -I imgui -I imgui_sfml -std=c++17 -Wall -Wno-unused-parameter $(PROFILEFLAGS) $(DEBUGFLAGS) -O$(strip $(OPTIM))
LDFLAGS	= -pipe -std=c++17 -lsfml-graphics -lsfml-system -lsfml-audio -lsfml-window  -framework OpenGL $(PROFILEFLAGS) $(DEBUGFLAGS) -O$(strip $(OPTIM))

ifeq ($(strip $(PROFILE)),1)
	PROFILEFLAGS=-pg
endif
ifeq ($(strip $(DEBUG)),1)
	#DEBUGFLAGS=-DDEBUG -ggdb3
	DEBUGFLAGS=-D_DEBUG -g
endif

$(EXEC): $(OBJ) $(IMGUI_OBJ)
	$(CXX) $(LDFLAGS) $(OBJ) $(IMGUI_OBJ) -o $(EXEC)

obj/main.cpp.o: src/main.cpp
	$(CXX) $(CFLAGS) -c $< -o $@

obj/imgui_sfml/%.cpp.o: imgui_sfml/%.cpp src/*.h
	$(CXX) $(CFLAGS) -c $< -o $@

obj/imgui/%.cpp.o: imgui/%.cpp imgui/*.h
	$(CXX) $(CFLAGS) -c $< -o $@

obj/%.cpp.o: src/%.cpp imgui/*.h
	$(CXX) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ) $(IMGUI_OBJ) $(EXEC)

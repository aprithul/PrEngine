INC_DIR := ./Sources
SRC_DIR := ./Sources
OBJ_DIR := ./Build

CC       := g++
CPPFLAGS := -I$(INC_DIR) -MMD -MP -std=c++11 -g
CXXFLAGS := -Wall
LDLIBS   := -lSDL2 -lSDL2_image -lSDL2_ttf

SOURCES := $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS := $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
DEPS    := $(wildcard $(OBJ_DIR)/*.d)

.PHONY: clean

Pringine: $(OBJECTS)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJECTS): $(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $(OUTPUT_OPTION) $<

clean: ; $(RM) $(DEPS) $(OBJECTS)

run: Pringine
	./Pringine

include $(DEPS)

$(MAKEFILE_LIST): ;
%:: %,v
%:: RCS/%,v
%:: RCS/%
%:: s.%
%:: SCCS/s.%
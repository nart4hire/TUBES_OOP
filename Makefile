EXECUTABLE_FILENAME = main
LIB_SRCS := $(wildcard lib/*.cpp)
ALL_SRCS := $(wildcard *.cpp) $(LIB_SRCS)
SRCS     := $(filter-out check.cpp testinv.cpp, $(ALL_SRCS))
TEST_DIR := test

all: compile

# Compile all cpp files except check.cpp
compile:
	g++ -std=c++17 -o $(EXECUTABLE_FILENAME) $(SRCS)

# Test
testinv:
	g++ -o testinv testinv.cpp $(filter-out main.cpp lib/Crafting.cpp, $(SRCS))

unit-test:
ifneq ($(MODULE), )
	g++ -std=c++17 -o $(TEST_DIR)/bin/$(MODULE) $(TEST_DIR)/$(MODULE).cpp $(LIB_SRCS)
	./$(TEST_DIR)/bin/$(MODULE)
endif

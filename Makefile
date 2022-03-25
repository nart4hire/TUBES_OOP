TC_FOLDER = tests
EXT_IN = in
EXT_OUT = out
EXT_ANS = ans
EXECUTABLE_FILENAME = main
LIB_SRCS := $(wildcard lib/*.cpp)
ALL_SRCS := $(wildcard *.cpp) $(LIB_SRCS)
SRCS     := $(filter-out check.cpp, $(ALL_SRCS))

all: compile test check

# Compile all cpp files except check.cpp
compile:
	g++ -std=c++17 -o $(EXECUTABLE_FILENAME) $(SRCS)

# Test
testinv:
	g++ -o testinv testinv.cpp $(filter-out main.cpp lib/Crafting.cpp, $(SRCS))

unit-test:
ifneq ($(MODULE), )
	g++ -std=c++17 -o $(TC_FOLDER)/bin/$(MODULE) $(TC_FOLDER)/$(MODULE).cpp $(LIB_SRCS)
	./$(TC_FOLDER)/bin/$(MODULE)
endif

test: $(TC_FOLDER)/*.$(EXT_IN)
	for inputfile in $(TC_FOLDER)/*.$(EXT_IN); do \
		./$(EXECUTABLE_FILENAME) < $$inputfile; \
	done;

check: FORCE check.cpp
	g++ -std=c++17 -o check check.cpp
	./check

FORCE: ;
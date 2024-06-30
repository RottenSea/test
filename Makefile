# compiler
CXX = g++

# compiler flags
CXXFLAGS = -c -Iutility

# directories
INJECTORDIR = injector
UTILITYDIR = utility

# source files
SRC := $(wildcard *.cpp) $(wildcard $(INJECTORDIR)/*.cpp) $(wildcard $(UTILITYDIR)/*.cpp)
OBJ = $(patsubst %.cpp, %.o,$(SRC))

# target directory
BINDIR = Build

# target
TARGET = $(BINDIR)/main

# rules
all: $(TARGET)

# link the object files to create the executable
$(TARGET): $(OBJ)
	$(CXX) -o $@ $^
 
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

# clean up
clean:
	rm -f $(TARGET) $(OBJ)

clean-all:
	rm -rf $(BINDIR)/logs







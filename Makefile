# compiler
CXX = g++

# compiler flags
CXXFLAGS =

# directories
INJECTORDIR = injector
UTILITYDIR = utility

# source files
SRCS := $(wildcard *.cpp) $(wildcard $(INJECTORDIR)/*.cpp) $(wildcard $(UTILITYDIR)/*.cpp)

# target directory
BINDIR = Build

# target
TARGET = $(BINDIR)/main

# rules
all: $(TARGET)

# link the object files to create the executable
$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# clean up
clean:
	rm -f $(TARGET)Makefile
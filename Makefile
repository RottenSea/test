# compiler
CXX = g++

# compiler flags
CXXFLAGS = -c -Iutility -Iinjector -ffunction-sections -fdata-sections -static-libgcc -static-libstdc++

# linker flags
LDFLAGS = -Wl --gc-sections

# directories
UTILITYDIR = utility

# source files
SRC := $(wildcard *.cpp) $(wildcard $(UTILITYDIR)/*.cpp)
OBJ = $(patsubst %.cpp, %.o, $(SRC))

# target directory
BINDIR = build

# target
TARGET = *.exe $(BINDIR)/*.exe

# rules
all: release
cs1: CStudent.o
	$(CXX) $(LDFLAGS) -o $(BINDIR)/$@ $^

# release build
release: CXXFLAGS += -O2
release: $(TARGET)

# debug build
debug: CXXFLAGS += -DDEBUG
debug: $(TARGET)

# link the object files to create the executable
$(TARGET): $(OBJ)
	$(CXX) $(LDFLAGS) -o $@ $^
 
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

# clean up
clean:
	rm -f $(OBJ) $(TARGET)

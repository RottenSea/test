# compiler
CXX = g++

# compiler flags
CXXFLAGS = -Iutility -ffunction-sections -fdata-sections -static-libgcc -static-libstdc++

# linker flags
LDFLAGS = -Wl,--gc-sections

# compile mode
MODE ?= release
ifeq ($(MODE),release)
    CXXFLAGS += -O2
else ifeq ($(MODE),debug)
    CXXFLAGS += -DDEBUG -g
else
    $(error Unknown MODE '$(MODE)'. Use 'release' or 'debug')
endif

# target directory
BINDIR = build

# source files
SRC := $(wildcard *.cpp)
OBJ := $(SRC:.cpp=.o)

# target
EXE := $(patsubst %.cpp, $(BINDIR)/%.exe, $(SRC))

# rules
all: $(EXE)

# compile rules
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# link rules
$(BINDIR)/%.exe: %.o
	@mkdir -p $(BINDIR)
	$(CXX) $(LDFLAGS) -o $@ $<

# clean up
clean:
	rm -f *.o
	rm -rf $(BINDIR)

# PHONY
.PHONY: all clean

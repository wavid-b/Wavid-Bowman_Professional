# Compiler to use
CXX = g++

# Compiler flags
CXXFLAGS = -D_FILE_OFFSET_BITS=64 -DFUSE_USE_VERSION=26

# Libraries to link against
LIBS = -L../libWad -lWad -lfuse

# Source files
SRCS = wadDaemon.cpp

# Output executable
OUT = wadfs

# Default rule
all: $(OUT)

$(OUT): $(SRCS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LIBS)

# Clean rule
.PHONY: clean
clean:
	rm -f $(OUT)
# The name of the library
LIBRARY = libWad.a

# The object files that the library is made from
OBJECTS = Wad.o

# The header files
HEADERS = Wad.h

# The compiler to use
CXX = g++

# The flags to pass to the compiler
CXXFLAGS = -Wall -Wextra -pedantic -std=c++11

# The rule to build the library
$(LIBRARY): $(OBJECTS)
	ar rcs $@ $^

# The rule to build the object files
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# The rule to clean the build
.PHONY: clean
clean:
	rm -f $(OBJECTS) $(LIBRARY)

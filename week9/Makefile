CXX ?= g++
CPPFLAGS += -Iinclude
CXXFLAGS ?= -std=c++17 -O0 -Wall -Wextra -Wpedantic -Werror

APP := build/seating
HEADERS := $(wildcard include/*.hpp)

.PHONY: all run test clean

all: $(APP)

$(APP): src/main.cpp $(HEADERS) Makefile
	@mkdir -p build
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) src/main.cpp -o $@

run: $(APP)
	./$(APP)

clean:
	rm -rf build

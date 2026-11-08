CXX ?= g++
CPPFLAGS += -Iinclude
CXXFLAGS ?= -std=c++17 -O0 -Wall -Wextra -Wpedantic -Werror
EXPERIMENT_FLAGS := -std=c++17 -O0 -fno-inline -g0 -Wall -Wextra -Wpedantic -Werror

APP := build/seating
HEADERS := $(wildcard include/*.hpp)

.PHONY: all run test sizes clean

all: $(APP)

$(APP): src/main.cpp $(HEADERS) Makefile
	@mkdir -p build
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) src/main.cpp -o $@

run: $(APP)
	./$(APP)

build/one.o: experiments/one.cpp $(HEADERS) Makefile
	@mkdir -p build
	$(CXX) $(CPPFLAGS) $(EXPERIMENT_FLAGS) -c $< -o $@

build/many.o: experiments/many.cpp $(HEADERS) Makefile
	@mkdir -p build
	$(CXX) $(CPPFLAGS) $(EXPERIMENT_FLAGS) -c $< -o $@

build/one: build/one.o
	$(CXX) $< -o $@

build/many: build/many.o
	$(CXX) $< -o $@

sizes: build/one.o build/many.o build/one build/many
	@echo "File sizes in bytes (one specialization vs five):"
	@wc -c build/one.o build/many.o build/one build/many
	@echo "Possible template-generated symbols (depends on compiler):"
	@nm -C build/many.o | grep 'Index<' | head -n 12 || true

clean:
	rm -rf build

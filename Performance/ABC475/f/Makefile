TARGET := main.cpp
OUTPUT := a.out

LIBPATH := $(HOME)/src/github.com/hidehic0/library_cpp
ALL.H := $(LIBPATH)/all.h
ALL.H.GCH := $(LIBPATH)/all.h.gch
PROJECTPATH := $(HOME)/src/github.com/hidehic0/atcoder

CXX := g++
CXXFLAGS := -std=gnu++23 -Wall
INCLUDES := -I$(LIBPATH) -I/usr/include

cpp-build: $(OUTPUT)

$(ALL.H.GCH): $(ALL.H)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c cxx-header $<
$(OUTPUT): $(TARGET) $(ALL.H.GCH)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $< -o $@


cpp-debug: CXXFLAGS += -g
cpp-debug: clean $(OUTPUT)

cpp-run: $(OUTPUT)
	@./$(OUTPUT)

clean:
	rm -f $(OUTPUT)

cpp-bundle: $(TARGET)
	@oj-bundle $(TARGET) $(INCLUDES) | wl-copy

.PHONY: cpp-build

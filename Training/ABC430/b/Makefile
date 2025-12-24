TARGET=main.cpp
OUTPUT=a.out
LIBPATH=$(HOME)/src/github.com/hidehic0/library_cpp
PROJECTPATH=$(HOME)/src/github.com/hidehic0/atcoder

cpp-build: $(TARGET)
	@$(PROJECTPATH)/.bin/date_check_build.sh "g++ -I$(LIBPATH) -std=gnu++23 -Wall $(TARGET)" $(TARGET) $(OUTPUT)

cpp-debug: $(TARGET)
	@rm -f a.out
	@$(PROJECTPATH)/.bin/date_check_build.sh "g++ -I$(LIBPATH) -std=gnu++23 -g -Wall $(TARGET)" $(TARGET) $(OUTPUT)

cpp-run: cpp-build
	@./$(OUTPUT)

cpp-bundle: $(TARGET)
	@oj-bundle $(TARGET) -I$(LIBPATH) | wl-copy

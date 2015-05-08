OBJECTS = bin/splitter.o
CPPFLAGS = $(shell pkg-config --cflags opencv)
LDLIBS = $(shell pkg-config --libs opencv)
.DEFAULT_GOAL = main


bin/%.o: src/%.cpp includes/%.h
	g++ -c $< -o $@ $(CPPFLAGS) $(LDLIBS)

main: $(OBJECTS)
	g++ src/$@.cpp $^ $(CPPFLAGS) $(LDLIBS) -o $@

clean:
	rm -rf bin/*
	rm -rf main

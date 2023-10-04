CPPFLAGS=-Wall -Werror -std=c++17 -pedantic -ggdb3
SRCS=$(wildcard *.cpp)
OBJS=$(patsubst %.cpp, %.o, $(SRCS))
PROGRAM=points

$(PROGRAM): $(OBJS)
	g++ $(CPPFLAGS) -o $@ $(OBJS)

%.o: %.cpp point.hpp
	g++ -c $(CPPFLAGS) $<

.PHONY: clean
clean:
	rm -f $(OBJS) $(PROGRAM) *~

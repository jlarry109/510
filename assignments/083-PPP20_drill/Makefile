CPPFLAGS=-Wall -Wextra -Wpedantic -Werror -std=c++17 -pedantic -ggdb3 -O2 -g -fno-omit-frame-pointer -fstack-protector-all -Wformat -Wformat-security 
SRCS=$(wildcard *.cpp)
OBJS=$(patsubst %.cpp, %.o, $(SRCS))
PROGRAM=drill20

$(PROGRAM): $(OBJS)
	g++ $(CPPFLAGS) -o $@ $(OBJS)

%.o: %.cpp %.hpp
	g++ -c $(CPPFLAGS) $<

.PHONY: clean
clean:
	rm -f $(OBJS) $(PROGRAM) *~
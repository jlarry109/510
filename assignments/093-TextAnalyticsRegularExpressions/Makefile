executables: wordfreq wordfreq_stop

wordfreq: wordfreq.cpp
	g++ -o wordfreq -pedantic -std=c++17 -Wall -Wextra -Werror -ggdb3 wordfreq.cpp

wordfreq_stop: wordfreq_stop.cpp
	g++ -o wordfreq_stop -pedantic -std=c++17 -Wall -Wextra -Werror -ggdb3 wordfreq_stop.cpp

clean:
	rm -rf *.dSYM *.o wordfreq wordfreq_stop

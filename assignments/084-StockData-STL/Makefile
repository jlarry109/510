stock: stock.cpp StockData.o stringutility.o
	g++ -o stock -pedantic -std=c++17 -Wall -Wextra -Werror -ggdb3 stock.cpp StockData.o stringutility.o

stringutility.o: stringutility.hpp stringutility.cpp
	g++ -c -o stringutility.o -pedantic -std=c++17 -Wall -Wextra -Werror -ggdb3 stringutility.cpp

StockData.o: StockData.hpp StockData.cpp
	g++ -c -o StockData.o -pedantic -std=c++17 -Wall -Wextra -Werror -ggdb3 StockData.cpp

clean:
	rm -rf *.dSYM *.o stock

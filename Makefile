SDSL_FLAGS = -lsdsl -ldivsufsort -ldivsufsort64

all: ej_1 ej_2 ej_6

ej_1: entropy_c.o entropia.o
	g++ -o ej_1 entropy_c.o entropia.o
	rm *.o

entropy_c.o: entropia.h
	g++ -c entropy_c.cpp

entropia.o: entropia.h
	g++ -c entropia.cpp -lm

ej_2: bit_test.o data_utils.o
	g++ bit_test.o data_utils.o -o ej_2 $(SDSL_FLAGS)

bit_test.o: bit_test.cpp
	g++ -c bit_test.cpp $(SDSL_FLAGS)

data_utils.o: data_utils.cpp data_utils.h
	g++ -c data_utils.cpp $(SDSL_FLAGS)

ej_6: difference.o data_utils.o
	g++ difference.o data_utils.o -o ej_6 $(SDSL_FLAGS)
	rm *.o


difference.o: difference.cpp
	g++ -c difference.cpp $(SDSL_FLAGS)


clean:
	rm -f ej_1 ej_2 ej_6 *.o

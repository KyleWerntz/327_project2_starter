
myexe: Project2.o utilities.o array_functions.o
	g++ $(CFLAGS) -o myexe Project2.o utilities.o array_functions.o constants.h utilities.h array_functions.h


Project2.o: Project2.cpp
	g++ $(CFLAGS) -c Project2.cpp

utilities.o: utilities.cpp
	g++ $(CFLAGS) -c utilities.cpp

array_functions.o: array_functions.cpp
	g++ $(CFLAGS) -c array_functions.cpp

clean:
	rm -f *.o myexe.exe
	rm myexe
		
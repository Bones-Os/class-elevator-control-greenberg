CXX = g++
CXXFLAGS = -Wall

proj1: centcom.o driver.o
	$(CXX) $(CXXFLAGS) centcom.o driver.o -o proj1

centcom.o: centcom.cpp centcom.h
	$(CXX) $(CXXFLAGS) -c centcom.cpp

driver.o: driver.cpp
	$(CXX) $(CXXFLAGS) -c driver.cpp

mytest.o: mytest.cpp centcom.o
	$(CXX) $(CXXFLAGS) -c mytest.cpp

clean:
	rm *.o*
	rm *~

run: ./proj1

test1: mytest.o
	$(CXX) $(CXXFLAGS) centcom.cpp mytest.o -o mytest
	./mytest

test2: mytest.o
	$(CXX) $(CXXFLAGS) centcom.cpp mytest.o -o mytest
	valgrind ./mytest
	#for more details, can run: valgrind --track-origins=yes ./mytest

debug: mytest.o
	$(CXX) $(CXXFLAGS) centcom.cpp mytest.o -o mytest
	gdb centcom.h centcom.cpp mytest.cpp --args mytest

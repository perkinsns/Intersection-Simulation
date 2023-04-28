project5.exe: project5.o CarClass.o constants.h EventClass.o IntersectionSimulationClass.o random.o LinkedNodeClass.inl LinkedNodeClass.h SortedListClass.h SortedListClass.inl SortedListClass.h FIFOQueueClass.inl FIFOQueueClass.h
	g++ -Wall -std=c++98 project5.o CarClass.o EventClass.o IntersectionSimulationClass.o random.o -o project5.exe

project5.o: project5.cpp
	g++ -c project5.cpp -o project5.o

CarClass.o: CarClass.h CarClass.cpp
	g++ -c CarClass.cpp -o CarClass.o

IntersectionSimulationClass.o: IntersectionSimulationClass.h IntersectionSimulationClass.cpp
	g++ -c IntersectionSimulationClass.cpp -o IntersectionSimulationClass.o

random.o: random.h random.cpp
	g++ -c random.cpp -o random.o

EventClass.o: EventClass.h EventClass.cpp
	g++ -c EventClass.cpp -o EventClass.o

clean:
	rm -rf project5.o CarClass.o EventClass.o IntersectionSimulationClass.o random.o project5.exe


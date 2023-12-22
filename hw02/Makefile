CXX=clang++
CXXFLAGS=-g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS=-g3

timer: timer_main.o CharLinkedList.o
	${CXX} ${LDFLAGS} -o timer timer_main.o CharLinkedList.o

unit_test: unit_test_driver.o CharLinkedList.o
	$(CXX) unit_test_driver.o CharLinkedList.o

CharLinkedList.o: CharLinkedList.cpp CharLinkedList.h
	$(CXX) -c CharLinkedList.cpp

timer_main.o: timer_main.cpp CharLinkedList.h
	${CXX} ${CXXFLAGS} -c timer_main.cpp

clean:
	@rm -r *~ *# *.o a.out core* vgcore*

CXX = g++
CXXFLAGS = -g -std=c++14 -Wall -MMD -Werror=vla -lX11
EXEC = a4q5
OBJECTS = main.o cell.o textdisplay.o grid.o graphicsdisplay.o window.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC} ${CXXFLAGS}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}

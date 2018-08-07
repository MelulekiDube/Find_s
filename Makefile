#Make file for project_maker
#Created on: Thu Feb 19 00:18:08 1970

#Meluleki Dube
CPP =g++
CPPFLAGS =-std=c++11
TARGET=find_s
SRC=main.cpp
OBJECTS=main.o 


$(TARGET): $(OBJECTS)
	$(CPP) $(OBJECTS)-o $@ $(CPPFLAGS)

$(OBJECTS): $(SRC)
	$(CPP) $< -c $(SRC) $(CPPFLAGS)

run:
	./$(TARGET)

clean:
	rm -f -r *.o bin/*.o *.exe

# end of Makefile
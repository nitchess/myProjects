#Project Files
TARGET=test

SRCS=$(wildcard ./*.cpp ../../agent/FireController.cpp ../../location/location.cpp ../../agent/FireEvent.cpp) 

OBJS=$(SRCS:.cpp=.o)

INC_PATH=-I../../include -I../publisher -I../distributer -I./ -I../../../lib/waitableQueue -I../../agent -I../../location

#Compilation Flags
CC=g++

CXXFLAGS=-g -Wall -Wconversion -pedantic -ansi -std=c++11 $(INC_PATH)

LDFLAGS=-lpthread

.PHONY: clean run gdb

$(TARGET): depends $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) 

clean:
	rm -v $(OBJS) $(TARGET) 
	
run: $(TARGET)
	@clear
	./$(TARGET)
	
gdb: $(TARGET)
	gdb ./$(TARGET) -q

depends:
	$(CC) -MM $(SRCS) > depends

include depends   


#Project Files
TARGET=test

SRCS=$(wildcard ./*.cpp) 

OBJS=$(SRCS:.cpp=.o)

INC_PATH=-I../../include -I./ -I../../../lib/waitableQueue

#Compilation Flags
CC=g++

CXXFLAGS=-g -Wall -Wconversion -pedantic -ansi $(INC_PATH)

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


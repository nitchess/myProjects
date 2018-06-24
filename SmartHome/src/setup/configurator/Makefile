#Project Files
TARGET=test

SRCS=$(wildcard ./reader/*.cpp ./parser/*.cpp ./*.cpp) 

OBJS=$(SRCS:.cpp=.o)

INC_PATH=$(addprefix -I, ./include ../../include)

#Compilation Flags
CC=g++

CXXFLAGS=-g -Wall -Wconversion -pedantic -ansi -std=c++11 $(INC_PATH)

LDFLAGS=-lpthread

.PHONY: clean run gdb

$(TARGET): depends $(OBJS)
	$(CC) $(OBJS) -pthread -o $(TARGET) 

clean:
	rm -v $(OBJS) $(TARGET) depends 
	
run: $(TARGET)
	@clear
	./$(TARGET)
	
gdb: $(TARGET)
	gdb ./$(TARGET) -q

depends:
	$(CC) -MM $(SRCS) $(INC_PATH) > depends

include depends   


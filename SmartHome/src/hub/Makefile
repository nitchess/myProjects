#Project Files
TARGET=test

SRCS=$(wildcard ./publisher/publisher.cpp ./registrar/registrar.cpp \
 ./distributer/distributer.cpp ./*.cpp ../agent/*.cpp ) 

#../location/*.cpp  ../location

OBJS=$(SRCS:.cpp=.o)

INC_PATH=$(addprefix -I, ./publisher ../agent ../include ../../lib/waitableQueue ./registrar ./distributer ../../location)

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


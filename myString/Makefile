#Project Files
TARGET=test

SRCS=$(wildcard ./test.cpp) 

#../location/*.cpp  ../location

OBJS=$(SRCS:.cpp=.o)

INC_PATH=$(addprefix -I, ./ ../../include)

#Compilation Flags
CC=g++

CXXFLAGS=-g -Wall -Wconversion -Werror -pedantic -ansi -std=c++0x $(INC_PATH)

LDFLAGS=

.PHONY: clean run gdb

$(TARGET): depends $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) 

clean:
	rm -v $(OBJS) $(TARGET) depends 
	
#run: $(TARGET)
#	@clear
#	./$(TARGET)
	
#gdb: $(TARGET)
#	gdb ./$(TARGET) -q

depends:
	$(CC) -MM $(SRCS) $(INC_PATH) > depends

include depends   


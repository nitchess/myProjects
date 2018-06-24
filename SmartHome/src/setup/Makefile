#Project Files
TARGET=test

SRCS=$(wildcard ./configurator/reader/*.cpp ./configurator/parser/*.cpp ./configurator/configurator.cpp ./*.cpp \
	./agentFactory/agentFactory.cpp ../hub/hub.cpp ../hub/distributer/*.cpp ../hub/registrar/registrar.cpp \
	../hub/publisher/publisher.cpp) 

OBJS=$(SRCS:.cpp=.o)

INC_PATH=$(addprefix -I, ./configurator/include ../include ./agentFactory ../hub ../hub/registrar ../hub/publisher \
	../../lib/waitableQueue ../hub/distributer)

#Compilation Flags
CC=g++

CXXFLAGS=-g -Wall -Wconversion -pedantic -ansi -std=c++11 $(INC_PATH)

LDFLAGS=-lpthread

.PHONY: clean run gdb

$(TARGET): depends $(OBJS)
	$(CC) $(OBJS) -pthread -ldl -static-libstdc++ -o $(TARGET) 

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

# search for .so file here
#  export LD_LIBRARY_PATH=./

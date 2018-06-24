#Project Files
TARGET=smartHome

SRCS=$(wildcard  ./*.cpp ../src/setup/configurator/reader/*.cpp ../src/setup/configurator/parser/*.cpp \
	../src/setup/configurator/configurator.cpp ../src/setup/agentFactory/agentFactory.cpp \
	../src/hub/hub.cpp ../src/hub/distributer/*.cpp ../src/hub/registrar/registrar.cpp\
	../src/hub/publisher/publisher.cpp ../src/setup/setup.cpp) 

OBJS=$(SRCS:.cpp=.o)

INC_PATH=$(addprefix -I, ../src/setup/configurator/include ../src/include ../src/setup/agentFactory \
	../src/hub ../src/hub/registrar ../src/hub/publisher ../lib/waitableQueue ../src/hub/distributer ../src/setup/)

#Compilation Flags
CC=g++

CXXFLAGS=-g -Wall -Wconversion -pedantic -ansi -std=c++11 $(INC_PATH)

LDFLAGS=-lpthread

.PHONY: clean run gdb

$(TARGET): depends $(OBJS)
	$(CC) $(OBJS) -pthread -ldl  -o $(TARGET) 

# -static-libstdc++
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

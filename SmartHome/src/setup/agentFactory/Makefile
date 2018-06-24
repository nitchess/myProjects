#Project Files
TARGET=test

SRCS=$(wildcard ../../hub/publisher/publisher.cpp ../../hub/registrar/registrar.cpp \
 ../../hub/distributer/distributer.cpp ./*.cpp ../../agent/HVACSensor.cpp ../../agent/HVACEvent.cpp \
  ../../agent/HVACController.cpp ../../hub/hub.cpp) 

OBJS=$(SRCS:.cpp=.o)

INC_PATH=$(addprefix -I, ../../hub/publisher ../../agent ../../include \
 ../../../lib/waitableQueue ../../hub/registrar ../../hub/distributer ../../hub ./)

#Compilation Flags
CC=g++

CXXFLAGS=-g -Wall -Wconversion -pedantic -ansi -std=c++11 $(INC_PATH)

LDFLAGS=-lpthread

.PHONY: clean run gdb

$(TARGET): depends $(OBJS)
	$(CC) $(OBJS) -pthread -ldl -o $(TARGET) 

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


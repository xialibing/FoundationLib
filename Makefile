CC = gcc
C++ = g++
LINK = g++

C++FLAGS = $(COMPILER_FLAGS) -c -g -fPIC

TARGET=libFoundation.so

INCLUDES = -I.

C++FILES = CMutex.cpp \
CLinuxMutex.cpp \
CPipe.cpp \
CLinuxPipe.cpp \
CPosixSem.cpp \
CLinuxPosixSem.cpp \
CSem.cpp \
CLinuxSem.cpp \
CShareMem.cpp \
CLinuxShareMem.cpp \
CThread.cpp \
CLinuxThread.cpp \
CTimer.cpp \
CLinuxTimer.cpp \
COSObjectFactory.cpp \
CSleepSem.cpp

OBJFILE = $(C++FILES:.cpp=.o)

all:$(TARGET)

$(TARGET): $(OBJFILE)
	$(LINK) $^ -Wall -fPIC -shared -o $@
%.o:%.cpp
	$(C++) -o $@  $(C++FLAGS) $< $(INCLUDES)
clean:
	rm -rf $(TARGET)
	rm -rf $(OBJFILE)

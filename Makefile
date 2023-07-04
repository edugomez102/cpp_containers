###############################################################################
# Variable macros
###############################################################################

TEST_APP := main

CCFLAGS := -std=c++20 
CFLAGS  := $(CCFLAGS)
CC      := g++
C       := gcc
MKDIR   := mkdir -p
SRC     := src
OBJ     := obj
LIBS    := 
INCLUDE  := -Isrc -Isrc/lib

TEST_SRC    := test
TEST_OBJ    := $(OBJ)/test

ALLCPPS      := $(shell find $(SRC)/ -type f -iname "*.cpp" -not -path "$(TEST_DIR)/*")
ALLCPPSOBJS  := $(patsubst $(SRC)/%.cpp,$(OBJ)/%.o,$(ALLCPPS))

TEST_ALLCPPS  := $(shell find $(TEST_SRC)/ -type f -iname "*.cpp")
TEST_OBJS     := $(patsubst $(TEST_SRC)/%.cpp,$(TEST_OBJ)/%.o,$(TEST_ALLCPPS))

TEST_SRC_CPPOBJS   := $(filter-out $(OBJ)/main.o,$(ALLCPPSOBJS))

SUBDIRS      := $(shell find $(SRC)/ -type d)
OBJSUBDIRS   := $(patsubst $(SRC)%,$(OBJ)%,$(SUBDIRS))

###############################################################################
# Config
###############################################################################

ifeq ($(RELEASE),1)
    CCFLAGS += -O2
else
		CCFLAGS += -g -Wall -Wextra -Wpedantic -Wconversion
endif
CFLAGS  := $(CCFLAGS)


###############################################################################

.PHONY: dir

test: $(TEST_APP)

$(OBJ)/%.o : $(SRC)/%.cpp
	$(CC) -o $@ -c $^ $(CCFLAGS) $(INCLUDE)

$(TEST_OBJ)/%.o: $(TEST_SRC)/%.cpp
	$(CC) -o $@ -c $^ $(CCFLAGS) -Isrc -Isrc/lib

$(TEST_APP) : $(OBJSUBDIRS) $(TEST_OBJS)
	$(CC) -o $(TEST_APP) $(TEST_OBJS) $(TEST_SRC_CPPOBJS) $(ALLCSOBJS) $(LIBS)
	./$(TEST_APP)

draft: draft.cpp
	$(CC) draft.cpp -o draft $(CCFLAGS) $(INCLUDE) -g

$(OBJSUBDIRS): 
	@$(MKDIR) $@
	@$(MKDIR) obj/test

clean:
	rm -rf obj
	rm -f $(TEST_APP)

recode: clean $(TEST_APP)

##make file to run motorMath tests
##Set this to @ to keep the makefile quiet
SILENCE = @

#---- Outputs ----#
COMPONENT_NAME = PidControl
TARGET_LIB = \
	lib/lib$(COMPONENT_NAME).a
	
TEST_TARGET = \
	$(COMPONENT_NAME)_tests

#--- Inputs ----#
PROJECT_HOME_DIR = .

CPP_PLATFORM = Gcc

CPPUTEST_WARNINGFLAGS += -Wall 
CPPUTEST_WARNINGFLAGS += -Werror 
CPPUTEST_WARNINGFLAGS += -Wswitch-default 
CPPUTEST_WARNINGFLAGS += -Wswitch-enum  
CPPUTEST_CFLAGS += -std=c89
CPPUTEST_CFLAGS += -Wextra 
CPPUTEST_CFLAGS += -pedantic 
CPPUTEST_CFLAGS += -Wstrict-prototypes

CPPUTEST_EXE_FLAGS += -c

# SRC_DIRS = \
 	./src\

SRC_FILES = ./src/PidControl.cpp

TEST_SRC_DIRS = \
	./tests/PidControl\
	./tests\
	
INCLUDE_DIRS =\
  $(CPPUTEST_HOME)/include/\
  ./src\
  
  
ifeq ($(CPPUTEST_HOME),)
$(info CPPUTEST_HOME not set! See README.txt)
else  
include $(CPPUTEST_HOME)/build/MakefileWorker.mk 
endif
# $Id $

# Copyright (c) 2007-2015, Trustees of The Leland Stanford Junior University
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# Redistributions of source code must retain the above copyright notice, this
# list of conditions and the following disclaimer.
# Redistributions in binary form must reproduce the above copyright notice,
# this list of conditions and the following disclaimer in the documentation
# and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
# LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.

LEX = flex
YACC   = bison -y
# DEBUG Flags: DEBUG_POWERGATE DEBUG_ROUTE DEBUG_POWERGATE_CONFIG
DEFINE = -DDEBUG_POWERGATE_CONFIG #-DDEBUG_FLOWS
INCPATH = -I. -Iarbiters -Iallocators -Irouters -Inetworks -Ipower
CPPFLAGS += -Wall $(INCPATH) $(DEFINE)
CPPFLAGS += -g
LFLAGS +=

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
  CPPFLAGS +=
else
  CPPFLAGS += -std=c++11
endif

OBJDIR := obj
PROG := booksim

# simulator source files
CPP_SRCS = $(wildcard *.cpp) $(wildcard */*.cpp)
CPP_HDRS = $(wildcard *.hpp) $(wildcard */*.hpp)
CPP_DEPS = $(addprefix ${OBJDIR}/,$(notdir $(CPP_SRCS:.cpp=.d)))
CPP_OBJS = $(addprefix ${OBJDIR}/,$(notdir $(CPP_SRCS:.cpp=.o)))

LEX_SRCS = lex.yy.c
LEX_OBJS = ${OBJDIR}/lex.yy.o

YACC_SRCS = y.tab.c
YACC_HDRS = y.tab.h
YACC_OBJS = ${OBJDIR}/y.tab.o

OBJS :=  $(CPP_OBJS) $(LEX_OBJS) $(YACC_OBJS)

.PHONY: clean

all: CPPFLAGS += -O3
all: CCFLAGS += -Wall -O3 -g $(INCPATH) $(DEFINE)
all: $(OBJDIR) $(PROG)

dbg: CPPFLAGS += -O0
dbg: CCFLAGS += -Wall -O0 -g $(INCPATH) $(DEFINE)
dbg: $(OBJDIR) $(PROG)

$(OBJDIR):
	 mkdir -p $(OBJDIR)

$(PROG): $(OBJS)
	 $(CXX) $(LFLAGS) $^ -o $@

$(LEX_SRCS): config.l
	$(LEX) $<

$(YACC_SRCS) $(YACC_HDRS): config.y
	$(YACC) -d $<

$(LEX_OBJS): $(LEX_SRCS) $(YACC_HDRS)
	$(CC) $(CCFLAGS) -c $< -o $@

$(YACC_OBJS): $(YACC_SRCS)
	$(CC) $(CCFLAGS) -c $< -o $@

${OBJDIR}/%.o: %.cpp
	$(CXX) $(CPPFLAGS) -MMD -c $< -o $@

# rules to compile networks
${OBJDIR}/%.o: networks/%.cpp
	$(CXX) $(CPPFLAGS) -c $< -o $@

# rules to compile arbiters
${OBJDIR}/%.o: arbiters/%.cpp
	$(CXX) $(CPPFLAGS) -c $< -o $@

# rules to compile allocators
${OBJDIR}/%.o: allocators/%.cpp
	$(CXX) $(CPPFLAGS) -c $< -o $@

# rules to compile routers
${OBJDIR}/%.o: routers/%.cpp
	$(CXX) $(CPPFLAGS) -c $< -o $@

# rules to compile power classes
${OBJDIR}/%.o: power/%.cpp
	$(CXX) $(CPPFLAGS) -c $< -o $@

clean:
	rm -f $(YACC_SRCS) $(YACC_HDRS)
	rm -f $(LEX_SRCS)
	rm -f $(CPP_DEPS)
	rm -f $(OBJS)
	rm -rf $(OBJDIR)
	rm -f $(PROG)

distclean: clean
	rm -f *~ */*~
	rm -f *.o */*.o
	rm -f *.d */*.d
	rm -rf $(OBJDIR)

-include $(CPP_DEPS)

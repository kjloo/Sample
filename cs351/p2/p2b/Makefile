# Copyright (C) 2013  Eric Larson and Rochelle Palting
# elarson@seattleu.edu
#
# This file is part of the MDAT infrastructure.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

all: mdatA mdatB

OBJS = main.o
INSTR_OBJS = sectionsA.o sectionsB.o
MDAT_OBJS = $(INSTR_OBJS:.o=.mdat.o)
MDAT_SRC = $(INSTR_OBJS:.o=.mdat.c)
MDAT_PP = $(INSTR_OBJS:.o=.i)

LIBS = -L. -lmdat -lpthread
INCLUDE = -I.

CPP = gcc -E
CPPFLAGS =
CC = gcc
CFLAGS = -O0 -Wall -Wno-implicit -g
CXX = g++
CXXFLAGS = -O0 -Wall -Wno-implicit -g
LD = g++
LDFLAGS =

mdatA: $(OBJS) sectionsA.mdat.o checkerA.o
	$(LD) $(LDFLAGS) -o $@ $(OBJS) sectionsA.mdat.o checkerA.o $(LIBS)

mdatB: $(OBJS) sectionsB.mdat.o checkerB.o
	$(LD) $(LDFLAGS) -o $@ $(OBJS) sectionsB.mdat.o checkerB.o $(LIBS)

$(OBJS): %.o : %.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(INCLUDE)

$(MDAT_OBJS): %.o : %.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)

$(MDAT_SRC): %.mdat.c : %.i
	./suds -suffix mdat $<

$(MDAT_PP): %.i : %.c $(HDRS)
	$(CPP) $(CPPFLAGS) $< > $@ $(INCLUDE)

checkerA.o: checker.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(INCLUDE)

checkerB.o: checker.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) -DCHECK_LIMIT -c $< -o $@ $(INCLUDE)

.DELETE_ON_ERROR: $(MDAT_SRC)

clean: 
	rm -f mdatA mdatB
	rm -f $(OBJS) $(MDAT_OBJS) checkerA.o checkerB.o
	rm -f $(MDAT_SRC) $(MDAT_PP)

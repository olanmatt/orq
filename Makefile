# The MIT License (MIT)
#
# Copyright (c) 2014 Matt Olan
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.


SRCDIR := src
TESTDIR := test
INCDIR := include
BUILDDIR := build
LIBDIR := lib

CC ?= gcc
CXX ?= g++
CFLAGS := -g -Wall -pedantic -std=c1x -I$(INCDIR)
CXXFLAGS := -g -Wall -pedantic -std=c++0x -I$(INCDIR)
LDFLAGS :=

PROG := orq
VERSION := 1
LIBNAME := lib$(PROG).so

SRCEXT := cpp

TARGET := $(LIBNAME).$(VERSION)
SOURCES := $(shell find $(SRCDIR) -type f -name "*.$(SRCEXT)")
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
HEADERS := $(shell find $(INCDIR) -type f -name "*.h" -a -not -name "catch.h")

TESTTARGET := bin/test
TESTSOURCES := $(shell find $(TESTDIR) -type f -name "*.$(SRCEXT)")
TESTOBJECTS := $(patsubst $(TESTDIR)/%,$(BUILDDIR)/$(TESTDIR)/%,$(TESTSOURCES:.$(SRCEXT)=.o))

all: $(TARGET)

default: $(TARGET)

clang: CXX=clang++
clang: all

$(TARGET): $(OBJECTS)
	@echo ""; echo "Linking..."
	$(CXX) -shared -Wl,-soname,$(TARGET) -o $(LIBDIR)/$(TARGET) $(LDFLAGS) $(OBJECTS)
	@[ -e $(LIBDIR)/$(LIBNAME) ] || ln -s $(TARGET) $(LIBDIR)/$(LIBNAME)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -fPIC -c -o $@ $<

# make test
test: $(TARGET) $(TESTTARGET)
	LD_LIBRARY_PATH=$(LIBDIR) $(TESTTARGET)

$(TESTTARGET): $(TESTOBJECTS)
	@echo ""; echo "Linking..."
	$(CXX) $^ -o $(TESTTARGET) $(LDFLAGS) -L$(LIBDIR) -l$(PROG)

$(BUILDDIR)/$(TESTDIR)/%.o: $(TESTDIR)/%.$(SRCEXT)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

gcov:
ifeq ($(CXX),g++)
# gcov: CXXFLAGS += -g -O0 --coverage
# gcov: LDFLAGS += -lgcov
gcov: clean test
else ifeq ($(CC),gcc)
# gcov: CFLAGS += -g -O0 --coverage
# gcov: LDFLAGS += -lgcov
gcov: clean test
endif

.PHONY: clean style astyle cpplint

style: astyle cpplint

astyle:
	@astyle --options=.astylerc $(ASTYLE_FLAGS) $(SOURCES) $(HEADERS) $(TESTSOURCES)

cpplint:
	@cpplint  $(CPPLINT_EXTRA) \
		--filter=-whitespace/indent,-whitespace/line_length,-whitespace/braces,-runtime/int,-whitespace/labels\
		$(SOURCES) $(HEADERS) $(TESTSOURCES) 2>&1 | \
		awk '!/^Done processing .*(cpp|h)/ { print $$0 }; \
			/Total errors / { gsub ("^[[:alpha:] ]+: ", ""); err=$$0} \
			END { exit err; }'

clean:
	@echo " Cleaning...";
	$(RM) -r $(BUILDDIR) $(TARGET) $(LIBDIR)/$(LIBNAME) $(TESTTARGET)


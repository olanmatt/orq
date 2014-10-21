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

CC ?= gcc
GXX ?= g++
SRCDIR := src
TESTDIR := test
INCDIR := include
BUILDDIR := build
TARGET := bin/orq
TESTTARGET := bin/test

SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name "*.$(SRCEXT)")
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
TESTSOURCES := $(shell find $(TESTDIR) -type f -name "*.$(SRCEXT)")
TESTOBJECTS := $(patsubst $(TESTDIR)/%,$(BUILDDIR)/$(TESTDIR)/%,$(TESTSOURCES:.$(SRCEXT)=.o))
CFLAGS := -g -Wall -pedantic -std=c++0x
LIB :=
INC := -I $(INCDIR)

# make
$(TARGET): $(OBJECTS)
	@echo ""; echo "Linking..."
	$(GXX) $^ -o $(TARGET) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(dir $@)
	$(GXX) $(CFLAGS) $(INC) -c -o $@ $<

# make test
test: $(TARGET) $(TESTTARGET)
	$(TESTTARGET)

$(TESTTARGET): $(TESTOBJECTS)
	@echo ""; echo "Linking..."
	$(GXX) $^ $(filter-out $(BUILDDIR)/orq.o,$(OBJECTS)) -o $(TESTTARGET) $(LIB)

$(BUILDDIR)/$(TESTDIR)/%.o: $(TESTDIR)/%.$(SRCEXT)
	@mkdir -p $(dir $@)
	$(GXX) $(CFLAGS) $(INC) -c -o $@ $<

astyle:
	astyle --options=.astylerc "$(SRCDIR)/*.cpp" "$(INCDIR)/*.h" "$(TESTDIR)/*.cpp"

# make clean
.PHONY: clean
clean:
	@echo " Cleaning...";
	$(RM) -r $(BUILDDIR) $(TARGET) $(TESTTARGET)


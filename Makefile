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
CXX ?= g++
SRCDIR := src
TESTDIR := test
INCDIR := include
BUILDDIR := build
TARGET := bin/orq
TESTTARGET := bin/test

SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name "*.$(SRCEXT)")
HEADERS := $(shell find $(SRCDIR) -type f -name "*.h")
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
TESTSOURCES := $(shell find $(TESTDIR) -type f -name "*.$(SRCEXT)")
TESTOBJECTS := $(patsubst $(TESTDIR)/%,$(BUILDDIR)/$(TESTDIR)/%,$(TESTSOURCES:.$(SRCEXT)=.o))
HEADERS := $(shell find $(INCDIR) -type f -name "*.h" -a -not -name "catch.h")
CFLAGS := -g -Wall -pedantic -std=c1x
CXXFLAGS := -g -Wall -pedantic -std=c++0x
LDFLAGS :=
INC := -I $(INCDIR)

# make
$(TARGET): $(OBJECTS)
	@echo ""; echo "Linking..."
	$(CXX) $^ -o $(TARGET) $(LDFLAGS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INC) -c -o $@ $<

# make test
test: $(TARGET) $(TESTTARGET)
	$(TESTTARGET)

$(TESTTARGET): $(TESTOBJECTS)
	@echo ""; echo "Linking..."
	$(CXX) $^ $(filter-out $(BUILDDIR)/orq.o,$(OBJECTS)) -o $(TESTTARGET) $(LDFLAGS)

$(BUILDDIR)/$(TESTDIR)/%.o: $(TESTDIR)/%.$(SRCEXT)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INC) -c -o $@ $<

gcov:
ifeq ($(CXX),g++)
gcov: CXXFLAGS += -g -O0 --coverage
gcov: LDFLAGS += -lgcov
gcov: clean test
else ifeq ($(CC),gcc)
gcov: CFLAGS += -g -O0 --coverage
gcov: LDFLAGS += -lgcov
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
	$(RM) -r $(BUILDDIR) $(TARGET) $(TESTTARGET)


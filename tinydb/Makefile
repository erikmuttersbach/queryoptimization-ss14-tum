CXXFLAGS:=-g -std=c++0x -Wall -Wextra -Isrc

DEPTRACKING=-MD -MF $(@:.o=.d)
BUILDEXE=g++ -o$@ $(CXXFLAGS) $(LDFLAGS) $^

ifeq ($(OS),Windows_NT)
nativefile=$(subst /,\\,$(1))
CHECKDIR=@if not exist $(call nativefile,$(dir $@)) mkdir $(call nativefile,$(dir $@))
LDFLAGS:= -Wl,--enable-auto-import
EXEEXT:=.exe
else
CHECKDIR=@mkdir -p $(dir $@)
EXEEXT:=
endif

all: bin/admin$(EXEEXT) examples_bin exercises_bin

include src/LocalMakefile
include examples/LocalMakefile
include exercises/LocalMakefile

-include bin/*.d bin/*/*.d

bin/%.o: src/%.cpp
	$(CHECKDIR)
	g++ -o$@ -c $(CXXFLAGS) $(DEPTRACKING) $<

bin/examples/%.o: examples/%.cpp
	$(CHECKDIR)
	g++ -o$@ -c $(CXXFLAGS) $(DEPTRACKING) $<
	
bin/exercises/%.o: exercises/%.cpp
	$(CHECKDIR)
	g++ -o$@ -c $(CXXFLAGS) $(DEPTRACKING) $<

clean:
	find bin -name '*.d' -delete -o -name '*.o' -delete -o '(' -perm -u=x '!' -type d ')' -delete

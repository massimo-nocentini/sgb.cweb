#
#   Makefile for the Stanford GraphBase
#

#   Be sure that CWEB version 3.0 or greater is installed before proceeding!

#   Skip down to "SHORTCUT" if you're going to work only from the
#   current directory. (Not recommended for serious users.)

CC = clang

#   Change SGBDIR to the directory where all GraphBase files will go:
SGBDIR = /usr/local/sgb

#   Change DATADIR to the directory where GraphBase data files will go:
DATADIR = $(SGBDIR)/data

#   Change INCLUDEDIR to the directory where GraphBase header files will go:
INCLUDEDIR = $(SGBDIR)/include

#   Change LIBDIR to the directory where GraphBase library routines will go:
LIBDIR = /usr/local/lib

#   Change BINDIR to the directory where installdemos will put demo programs:
BINDIR = /usr/local/bin

#   Change CWEBINPUTS to the directory where CWEB include files will go:
CWEBINPUTS = /usr/local/lib/cweb

#   SHORTCUT: Uncomment these lines, for single-directory installation:
#DATADIR = .
#INCLUDEDIR = .
#LIBDIR = .
#BINDIR = .
#CWEBINPUTS = .

#   Uncomment the next line if your C uses <string.h> but not <strings.h>:
SYS = -DSYSV

#   If you prefer optimization to debugging, change -g to something like -O:
CFLAGS = -O3 -I$(INCLUDEDIR) $(SYS) -fPIC -Wno-deprecated-non-prototype -Wno-implicit-int

install_graph_helpers:
	ctangle makegraph.w makegraph.c
	ctangle makedigraph.w makedigraph.c
	$(CC) $(CFLAGS) makegraph.c -o makegraph $(LDFLAGS) $(LDLIBS)
	$(CC) $(CFLAGS) makedigraph.c -o makedigraph $(LDFLAGS) $(LDLIBS) 
	cp makegraph makedigraph $(BINDIR)/

#   This is our own addition to compile everything, doc included for kernel files:
complete:
	make clean
	make tests
	make install
	make installdemos
	make install_graph_helpers
	make doc

########## You shouldn't have to change anything after this point ##########

LDFLAGS = -L. -L$(LIBDIR)
LDLIBS = -lgb
LOADLIBES = $(LDLIBS)

.SUFFIXES: .dvi .tex .w

.tex.dvi:
	tex $*.tex
	dvipdf $*.dvi

.w.c:
	if test -r $*.ch; then ctangle $*.w $*.ch; else ctangle $*.w; fi

.w.tex:
	if test -r $*.ch; then cweave $*.w $*.ch; else cweave $*.w; fi

.w.o:
	make $*.c
	make $*.o

.w:
	make $*.c
	make $*.dvi
	make $*

.w.dvi:
	make $*.tex
	make $*.dvi

DATAFILES = anna.dat david.dat econ.dat games.dat homer.dat huck.dat \
        jean.dat lisa.dat miles.dat roget.dat words.dat
KERNELFILES = gb_flip.w gb_graph.w gb_io.w gb_sort.w
GENERATORFILES = gb_basic.w gb_books.w gb_econ.w gb_games.w gb_gates.w \
        gb_lisa.w gb_miles.w gb_plane.w gb_raman.w gb_rand.w gb_roget.w \
        gb_words.w
DEMOFILES = assign_lisa.w book_components.w econ_order.w football.w \
        girth.w ladders.w miles_span.w multiply.w queen.w roget_components.w \
        take_risc.w word_components.w
MISCWEBS = boilerplate.w gb_dijk.w gb_save.w gb_types.w test_sample.w
CHANGEFILES = queen_wrap.ch word_giant.ch gb_graph-bigalloc.ch
MISCFILES = Makefile README abstract.plaintex cities.texmap blank.w \
        sample.correct test.correct test.dat +The+Stanford+GraphBase+
ALL = $(DATAFILES) $(KERNELFILES) $(GENERATORFILES) $(DEMOFILES) \
        $(MISCWEBS) $(CHANGEFILES) $(MISCFILES)

OBJS = $(KERNELFILES:.w=.o) $(GENERATORFILES:.w=.o) gb_dijk.o gb_save.o
HEADERS = $(OBJS:.o=.h)
DEMOS = $(DEMOFILES:.w=)

help:
	@ echo "First 'make tests';"
	@ echo "then (optionally) become superuser;"
	@ echo "then 'make install';"
	@ echo "then (optionally) 'make installdemos';"
	@ echo "then (optionally) 'make clean'."

lib: libgb.a

libgb.a: $(OBJS)
	rm -f certified
	ar rcv libgb.a $(OBJS)
	- ranlib libgb.a

gb_io.o: gb_io.c
	$(CC) $(CFLAGS) -DDATA_DIRECTORY=\"$(DATADIR)/\" -c gb_io.c

test_io: gb_io.o
	$(CC) $(CFLAGS) test_io.c gb_io.o -o test_io

test_graph: gb_graph.o
	$(CC) $(CFLAGS) test_graph.c gb_graph.o -o test_graph

test_flip: gb_flip.o
	$(CC) $(CFLAGS) test_flip.c gb_flip.o -o test_flip

tests: test_io test_graph test_flip
	./test_io
	./test_graph
	./test_flip
	make gb_sort.o
	make lib
	make test_sample
	- ./test_sample > sample.out
	diff test.gb test.correct
	diff sample.out sample.correct
	rm test.gb sample.out test_io test_graph test_flip test_sample
	echo "Congratulations --- the tests have all been passed."
	touch certified

install: lib
	if test ! -r certified; then echo "Please run 'make tests' first!"; fi
	test -r certified
	make installdata
	- mkdir $(LIBDIR)
	- cp libgb.a $(LIBDIR)
	- mkdir $(CWEBINPUTS)
	- cp -p boilerplate.w gb_types.w $(CWEBINPUTS)
	- mkdir $(INCLUDEDIR)
	- cp -p $(HEADERS) Makefile $(INCLUDEDIR)

installdata: $(DATAFILES)
	- mkdir $(SGBDIR)
	- mkdir $(DATADIR)
	- cp -p $(DATAFILES) $(DATADIR)

installdemos: lib $(DEMOS)
	- mkdir $(BINDIR)
	- mv $(DEMOS) $(BINDIR)

uninstalldemos:
	- cd $(BINDIR); rm -f $(DEMOS)

doc:
	tex abstract.plaintex
	cweave boilerplate.w && tex boilerplate.tex && dvipdf boilerplate.dvi
	cweave gb_basic.w && tex gb_basic.tex && dvipdf gb_basic.dvi
	cweave gb_graph.w && tex gb_graph.tex && dvipdf gb_graph.dvi
	cweave gb_flip.w && tex gb_flip.tex && dvipdf gb_flip.dvi
	cweave gb_io.w && tex gb_io.tex && dvipdf gb_io.dvi
	cweave gb_sort.w && tex gb_sort.tex && dvipdf gb_sort.dvi
	cweave gb_dijk.w && tex gb_dijk.tex && dvipdf gb_dijk.dvi
	cweave gb_save.w && tex gb_save.tex && dvipdf gb_save.dvi
	cweave gb_types.w && tex gb_types.tex && dvipdf gb_types.dvi
	cweave gb_books.w && tex gb_books.tex && dvipdf gb_books.dvi
	cweave gb_econ.w && tex gb_econ.tex && dvipdf gb_econ.dvi
	cweave gb_games.w && tex gb_games.tex && dvipdf gb_games.dvi
	cweave gb_gates.w && tex gb_gates.tex && dvipdf gb_gates.dvi
	cweave gb_lisa.w && tex gb_lisa.tex && dvipdf gb_lisa.dvi
	cweave gb_miles.w && tex gb_miles.tex && dvipdf gb_miles.dvi
	cweave gb_plane.w && tex gb_plane.tex && dvipdf gb_plane.dvi
	cweave gb_raman.w && tex gb_raman.tex && dvipdf gb_raman.dvi
	cweave gb_rand.w && tex gb_rand.tex && dvipdf gb_rand.dvi
	cweave gb_roget.w && tex gb_roget.tex && dvipdf gb_roget.dvi
	cweave gb_words.w && tex gb_words.tex && dvipdf gb_words.dvi
	cweave makegraph.w && tex makegraph.tex && dvipdf makegraph.dvi
	cweave makedigraph.w && tex makedigraph.tex && dvipdf makedigraph.dvi
	

clean:
	rm -f *~ *.o *.c *.h libgb.a certified \
	         *.tex *.log *.dvi *.toc *.idx *.scn core

veryclean: clean
	rm -f $(DEMOS)

sgb.tar: $(ALL)
	tar cvf sgb.tar $(ALL)

floppy: $(ALL)
	bar cvf /dev/rfd0 $(ALL)
	bar tvf /dev/rfd0
	eject

fullfloppy: $(ALL) ERRATA ANSI AMIGA PROTOTYPES MSVC
	bar cvf /dev/rfd0 $(ALL) ERRATA ANSI AMIGA PROTOTYPES MSVC
	bar tvf /dev/rfd0
	eject

fulltar: $(ALL) ERRATA ANSI AMIGA PROTOTYPES MSVC
	tar cvf sgb.tar $(ALL) ERRATA ANSI AMIGA PROTOTYPES MSVC

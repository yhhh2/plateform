PUBINCL = -I/project/public

PUBCPP = /project/public/_public.cpp

CFLAGS = -g

all: checkproc procctl gzipfiles deletefiles tcpputfiles filesserver

procctl:procctl.cc
	g++ -o procctl procctl.cc
	cp procctl ../bin/.
test:test.cc
	g++ $(CFLAGS) -o test test.cc $(PUBINCL) $(PUBCPP) -lm -lc


checkproc:checkproc.cc
	g++ $(CFLAGS) -o checkproc checkproc.cc $(PUBINCL) $(PUBCPP) -lm -lc
	cp checkproc ../bin/.

gzipfiles:gzipfiles.cc
	g++ $(CFLAGS) -o gzipfiles gzipfiles.cc $(PUBINCL) $(PUBCPP) -lm -lc
	cp gzipfiles ../bin/.
deletefiles:deletefiles.cc
	g++ $(CFLAGS) -o deletefiles deletefiles.cc $(PUBINCL) $(PUBCPP) -lm -lc
	cp deletefiles ../bin/.

tcpputfiles:tcpputfiles.cc
	g++ $(CFLAGS) -o  tcpputfiles tcpputfiles.cc $(PUBINCL) $(PUBCPP) -lm -lc
	cp tcpputfiles ../bin/.
filesserver:filesserver.cc
	g++ $(CFLAGS) -o filesserver filesserver.cc $(PUBINCL) $(PUBCPP) -lm -lc
	cp filesserver ../bin/.

clean:
	rm -rf procctl checkproc gzipfiles deletefiles tcpputfiles filesserver


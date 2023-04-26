CPP = g++
CPPFLAGS = -O2 -g -Iinclude

all : lib test

objs = integration_Naive.o integration_MeanVariance.o pdfs.o
objs := $(addprefix obj/, $(objs)) 

lib : $(objs)
	ar -r lib/libintegration.a $^ 

bin/test_% : test/test_%.cc lib
	$(CPP) $(CPPFLAGS) $(filter %.o %.cc, $^) -Llib -lintegration -o $@

bin/% : src/%.cc lib
	$(CPP) $(CPPFLAGS) $(filter %.o %.cc, $^) -Llib -lintegration -o $@

obj/%.o : src/%.cc 
	$(CPP) $(CPPFLAGS) -c $^ -o $@


test : bin/test_pi_1D_Naive bin/test_pi_1D_MeanVariance bin/test_mb_1D_Naive


clean : 
	rm -f bin/*
	find  obj -name '*.o' -exec rm {} \;
	rm -f lib/*.a
	find ./ -name '*~' -exec rm {} \;
	find ./ -name '#*' -exec rm {} \;

realclean : clean
	rm -f bin/*.dat


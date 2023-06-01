
# set to vegas_kh to use mine///
WHICH_VEGAS_LIB = vegas_kh # vegas

CPP = g++
CPPFLAGS = -O2 -g -std=c++0x -DFIXED_ITERATIONS  -I../probability/include -Iinclude
LDFLAGS = -L./lib -l$(WHICH_VEGAS_LIB) -L../probability/lib -lprobability 

#GSL_CPPFLAGS = -I../basic_integration/include
#GSL_LDFLAGS = -L../basic_integration/lib -lbasic_integration -L ../khgsl/lib -lgsl -lgslcblas
#CPPFLAGS_C = -O2 -g -pg -I../../c/pdf/include -I../../c/vegas/include
#LDFLAGS_C = -L../../c/pdf/lib -lpdf -L../../c/vegas/lib -lvegas

all : lib bin

obj = vegas_importance.o vegas_dump.o vegas_integrals.o #vegas_stratify.o 
obj := $(addprefix obj/, $(obj)) 

vegas_test = vegas_integrate_1d2gaus #vegas_integrate_2d2gaus vegas2_integrate_2d2gaus
test :=  $(addprefix bin/, $(vegas_test)) 

#gsl_test = gsl_integrate_1d2gaus gsl_integrate_2d2gaus
#gsl :=  $(addprefix bin/, $(gsl_test)) 
#vegas_ctest = vegas_integrate_1d2gaus_clinkage
#ctest :=  $(addprefix bin/, $(vegas_ctest)) 



obj/%.o : src/%.cc 
	$(CPP) $(CPPFLAGS) -c $^ -o $@
lib : $(obj)
	ar -r lib/libvegas.a $^ 

libKH : lib
	cp lib/libvegas.a lib/libvegas_kh.a
	rm ./obj/*.o

deplib : 
	$(MAKE) -C ../probability lib


#bin/%_clinkage : tests/%_clinkage.cc lib
#	$(CPP) $(CPPFLAGS_C) $(filter %.o %.cc, $^) $(LDFLAGS_C) -o $@
#bin/gsl% : tests/gsl%.cc lib
#	$(CPP) $(CPPFLAGS) $(GSL_CPPFLAGS) $(filter %.o %.cc, $^) $(GSL_LDFLAGS) $(LDFLAGS) -o $@

bin/% : tests/%.cc lib deplib
	$(CPP) $(CPPFLAGS) $(filter %.o %.cc, $^) $(LDFLAGS) -o $@

bin : $(test) #$(gsl) $(ctest)

clean : 
	rm -f bin/*
	find  obj -name '*.o' -exec rm {} \;
	rm -f lib/libvegas.a
	find ./ -name '*~' -exec rm {} \;
	find ./ -name '#*' -exec rm {} \;
	touch bin/.keepme
	touch obj/.keepme
	touch lib/.keepme
	$(MAKE)  -C ../probability clean

realclean : clean
	rm -rf data/vegas*
	rm -rf png/vegas*	
	rm ./lib/*.a

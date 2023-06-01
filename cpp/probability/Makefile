CPP = g++
CPPFLAGS = -O2 -g -Iinclude

all : lib test

objs = pdfs.o cdfs.o pdfs2D.o sampling.o
objs := $(addprefix obj/, $(objs)) 

lib : $(objs)
	ar -r lib/libprobability.a $^ 

bin/test_% : test/test_%.cc lib
	$(CPP) $(CPPFLAGS) $(filter %.o %.cc, $^) -Llib -lprobability -o $@

bin/% : src/%.cc lib
	$(CPP) $(CPPFLAGS) $(filter %.o %.cc, $^) -Llib -lprobability -o $@

obj/%.o : src/%.cc 
	$(CPP) $(CPPFLAGS) -c $^ -o $@


test : bin/test_uniform_rejection bin/test_gaussian_rejection bin/test_exp_inversion bin/test_gaussian_inversion bin/test_compare_sampling bin/test_exp_rejection_with_cdf bin/test_double_gaussian_sampling bin/test_maxwell_boltzmann_rejection bin/test_maxwell_boltzmann_metropolis

clean : 
	rm -f bin/*
	find  obj -name '*.o' -exec rm {} \;
	rm -f lib/*.a
	find ./ -name '*~' -exec rm {} \;
	find ./ -name '#*' -exec rm {} \;




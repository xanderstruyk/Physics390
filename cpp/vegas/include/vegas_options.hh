#ifndef VEGAS_OPTIONS
#define VEGAS_OPTIONS

#include <stdio.h>

class VegasOptions 
{ 
public:
  bool importance,stratify, adaptive, debug;
  unsigned bins, evts, iter, trial;
  unsigned seed, Nstrat;
  double beta;
  char * path;

  VegasOptions() : importance(false),stratify(false),adaptive(false),debug(false) {;}

};


void
help() 
{
  printf("\n");
  printf("vegas options :\n");
  printf("\n");
  printf( " -h, --help\n");
  printf( " -d, --debug\n");
  printf( " -m, --importance : [ Ng]\n");
  printf( " -s, --stratify   : [ Nstrat ]\n");
  printf( " -a, --adaptive   : [ beta value ]\n");
  printf( " -e, --events     : [ Nevts ]\n");
  printf( " -i, --iterations : [ Niter ]\n");
  printf( " -t, --trials     : [ Ntrials ]\n");
  printf( " -s, --seed       : [ rseed ]\n");
  printf( " -p, --path       : [ path ]\n");
  printf("\n");
  exit(0);
}

int 
parse_args( int argc, char ** argv, VegasOptions & sopt ) 
{

  if( argc < 2 ) 	help();
  
  int opt;
  int option_index = 0;
  
  static struct option long_options[] =
    {
      {"debug",               no_argument, NULL, 'd'},
      {"importance",          required_argument, NULL, 'm'},
      {"stratify",            required_argument, NULL, 's'},
      {"adaptive",            required_argument, NULL, 'a'},
      {"events",              required_argument, NULL, 'e'},
      {"iterations",          required_argument, NULL, 'i'},
      {"trials",              required_argument, NULL, 't'},
      {"seed",                required_argument, NULL, 'r'},
      {"path",                required_argument, NULL, 'p'},
      {"help",                no_argument, NULL, 'h'},
      {NULL, 0, NULL, 0}
    };


  fprintf(stderr,"-----------------------------------\n");
  while(1)
    {  
      opt = getopt_long(argc, argv, "::r::e::i::t::s::a::m::p::d0::",long_options, &option_index);

      if (opt == -1) {
	break; 
      }

      switch(opt)  
	{  
	case 0: 
	  printf("option -->%s\n", long_options[option_index].name); 
	  break;
	case 'm':  
	  if(optarg==NULL) {
	    fprintf(stderr,"Error: importance sampling must be specified with -m<bins> or --importance=<bins>\n");
	    return -1;
	  }
	  fprintf(stderr,"option: importance sampling, Ng = %d\n", strtoul(optarg, NULL, 10));  
	  sopt.importance = true;
	  sopt.bins = strtoul(optarg, NULL, 10);
	  break;  
	case 's':  
	  if(optarg==NULL) {
	    fprintf(stderr,"Error: stratification must be specified with -s<Nstrat> or --stratify=<Nstrat>\n");
	    return -1;
	  }
	  fprintf(stderr,"option: stratification, Nstrat = %d\n",strtoul(optarg, NULL, 10));  
	  sopt.stratify = true;
	  sopt.Nstrat = strtoul(optarg, NULL, 10);
	  break;  
	case 'a':  
	  if(optarg==NULL) {
	    fprintf(stderr,"Error: adaptive stratification must be specified with -a<beta> or --adpative=<beta>\n");
	    return -1;
	  }
	  fprintf(stderr,"option: adaptive stratification, beta = %f\n", strtof(optarg, NULL));  
	  sopt.adaptive = true;
	  sopt.beta = strtof(optarg, NULL);
	  break;  
	case 'e':  
	  if(optarg==NULL) {
	    fprintf(stderr,"Error: Nevts must be specified with -e<evts> or --events=<evts>\n");
	    return -1;
	  }
	  fprintf(stderr,"option: Nevts = %d\n", strtoul(optarg, NULL, 10));  
	  sopt.evts = strtoul(optarg, NULL, 10);
	  break;  
	case 'i':  
	  if(optarg==NULL) {
	    fprintf(stderr,"Error: Niter must be specified with -i<iter> or --iterations=<iter>\n");
	    return -1;
	  }
	  fprintf(stderr,"option: Niter = %d\n", strtoul(optarg, NULL, 10));  
	  sopt.iter = strtoul(optarg, NULL, 10);
	  break;  
	case 't':  
	  if(optarg==NULL) {
	    fprintf(stderr,"Error: Ntrial must be specified with -t<trial> or --trials=<trial>\n");
	    return -1;
	  }
	  fprintf(stderr,"option: Ntrial = %d\n", strtoul(optarg, NULL, 10));  
	  sopt.trial = strtoul(optarg, NULL, 10);
	  break;  
	case 'r':  
	  if(optarg==NULL) {
	    fprintf(stderr,"Error: random seed must be specified with -r<seed> or --seed=<seed>\n");
	    return -1;
	  }
	  fprintf(stderr,"option: random seed = %d\n", strtoul(optarg, NULL, 10));  
	  sopt.seed = strtoul(optarg, NULL, 10);
	  break;  
	case 'p':  
	  if(optarg==NULL) {
	    fprintf(stderr,"Error: output path must be specified with -p<path> or --path=<path>\n");
	    return -1;
	  }
	  fprintf(stderr,"option: path = %s\n", optarg);
	  sopt.path = optarg;
	  break;  
	case 'd':  
	  fprintf(stderr,"option: debug\n");  
	  sopt.debug = true;
	  break;  
	case 'h':  
	  fprintf(stderr,"option: help\n");  
	  help();
	  return 0;
	  break;  
	}  
    }     

  fprintf(stderr,"-----------------------------------\n");  
  return 0;
};

#endif

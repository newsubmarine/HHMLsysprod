//Steering macro

//C++
#include <iostream>
#include <sstream>
#include <memory>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <sys/time.h>

//Root
#include <TFile.h>
#include <TString.h>
#include <TSystem.h>

//Local include
#include "HHMLSys/HHMLSys_EventSaver.h"

static void usage(const std::string  &name) {

  std::cerr << "Usage: " << name << " <option(s)>\n"
	    << "Options:\n"
	    << "\t--h  or --help   : help\n"
	    << "\t--sp             : path of the input root file \n"
	    << "\t--me             : maximum number of events to be process\n"
	    << "\t--conf           : path of configuration file\n"
	    << "\t--out            : Output dir path\n"
            << "\t--outName        : Output root file name\n"
	    << "\t--mcRun          : mc campaign e.g. mc16a etc\n"
	    << std::endl;
}

int main(int argc, char* argv[]) {

  if(argc < 2) {
    std::cerr << "At least 1 option needed. Type --h for help. Exiting!!" << std::endl;
    return EXIT_FAILURE;
  }

  struct timeval startTime, endTime;
  gettimeofday(&startTime, NULL);

  std::string input;
  std::string samplePath = "";
  std::string max_evnt    = "-1";
  int out_arg = 0;
  TString configFile, outDir, mcRun;
  TString sampleName = "";

  for(int i = 0; i < argc; ++i) {
    
    std::string arg = argv[i];
    
    if(arg == "--h" or arg == "--help") {
      usage( argv[0] );
      return EXIT_SUCCESS;
    }
    else if(arg == "--sp") {
      if(argc < 3) {
	std::cerr << "--sp requires one argument. Exiting!!" << std::endl;
        return EXIT_FAILURE;
      }
      input = argv[++i];
      if((input != "--h" or input != "--help") && input != "--conf" && input != "--me" && input != "--out") samplePath = input;
    }
    else if(arg == "--conf") {
      if(argc < 5) {
	std::cerr << "--conf requires one argument. Exiting!!" << std::endl;
        return EXIT_FAILURE;
      }
      input = argv[++i];
      if((input != "--h" or input != "--help") && input != "--sp" && input != "--me" && input != "--out") configFile = input;
    }
    else if(arg == "--out") {
      if(argc < 7) {
	std::cerr << "--out requires one argument. Exiting!!" << std::endl;
        return EXIT_FAILURE;
      }
      input = argv[++i];
      if((input != "--h" or input != "--help") && input != "--sp" && input != "--me" && input != "--conf") outDir = input;
      out_arg = 1;
    }
    else if(arg == "--mcRun" && out_arg == 0 ) {
      if(argc < 7) {
	std::cerr << "--mcRun requires one argument. Exiting!!" << std::endl;
        return EXIT_FAILURE;
      }
      input = argv[++i];
      if((input != "--h" && input != "--help") && input != "--sp" && input != "--me" && input != "--conf" && input != "--out") mcRun = input;
      out_arg = 2;
    }
    else if(arg == "--mcRun" && out_arg == 1 ) {
      if(argc < 9) {
	std::cerr << "--mcRun requires one argument. Exiting!!" << std::endl;
        return EXIT_FAILURE;
      }
      input = argv[++i];
      if((input != "--h" or input != "--help") && input != "--sp" && input != "--me" && input != "--conf" && input != "--out") mcRun = input;
      out_arg = 3;
    }
    else if(arg == "--me" && out_arg == 0) {
      if(argc < 7) {
	std::cerr << "--me requires one argument. Exiting!!" << std::endl;
        return EXIT_FAILURE;
      }
      input = argv[++i];
      if((input != "--h" or input != "--help") && input != "--sp" && input != "--conf" && input != "--out" && input != "--mcRun") max_evnt = input;
    }
    else if(arg == "--me" && out_arg == 1) {
      if(argc < 9) {
	std::cerr << "--me requires one argument. Exiting!!" << std::endl;
        return EXIT_FAILURE;
      }
      input = argv[++i];
      if((input != "--h" or input != "--help") && input != "--sp" && input != "--conf" && input != "--out" && input != "--mcRun") max_evnt = input;
    }
    else if(arg == "--me" && out_arg == 2) {
      if(argc < 9) {
	std::cerr << "--me requires one argument. Exiting!!" << std::endl;
        return EXIT_FAILURE;
      }
      input = argv[++i];
      if((input != "--h" or input != "--help") && input != "--sp" && input != "--conf" && input != "--out" && input != "--mcRun") max_evnt = input;
    }
    else if(arg == "--me" && out_arg == 3) {
      if(argc < 11) {
	std::cerr << "--me requires one argument. Exiting!!" << std::endl;
        return EXIT_FAILURE;
      }
      input = argv[++i];
      if((input != "--h" or input != "--help") && input != "--sp" && input != "--conf" && input != "--out" && input != "--mcRun") max_evnt = input;
    }
    else if(arg == "--outName") {
      input = argv[++i];
      sampleName = input;
    }
  }

  if(samplePath == "") {
    std::cerr << "No Input file found. Exiting!!" << std::endl;
    return EXIT_FAILURE;
  }
  if(configFile == "") {
    std::cerr << "No configuration file found. Exiting!!" << std::endl;
    return EXIT_FAILURE;
  }
  if(outDir == "") std::cerr << "Warning!! output path is not given. Output file will be written in current dir!" << std::endl;
  
  gSystem->ExpandPathName(configFile);

  HHMLSys_EventSaver hhmlSys;

  hhmlSys.msg().setLevel(MSG::INFO);
  
  if(!hhmlSys.initialize(configFile, samplePath, outDir, sampleName, mcRun).isSuccess()) return EXIT_FAILURE;
  
  if(!hhmlSys.executeEventLoop(atoi(max_evnt.c_str())).isSuccess()) return EXIT_FAILURE;
  
  if(!hhmlSys.finalize().isSuccess()) return EXIT_FAILURE;

  gettimeofday(&endTime, NULL);

  time_t diffsec = difftime(endTime.tv_sec, startTime.tv_sec);
  suseconds_t diffsub = endTime.tv_usec - startTime.tv_usec;
  double realsec = diffsec+diffsub*1e-6;
  printf("real time: %0.3f sec \n", realsec);

  std::cout << "\033[1mAlright - done!!!\033[0m" << std::endl;

  return EXIT_SUCCESS;
}

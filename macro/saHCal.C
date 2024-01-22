#include "saHCal.h"
R__LOAD_LIBRARY(libsaHCal.so)

void saHCal(const char * filename) {
  if ( filename != NULL) pfileopen(filename);
  get_runtype(filename);
  pinit();
  prun(1000); //frequncey
  find_hot_tower();
  prun(500);
  output_hot_tower();
  std::cout << "File done." << std::endl;
}

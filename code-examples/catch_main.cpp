/*
 * catch_main.cpp
 *
 *  Created on: Sep 15, 2020
 *      Author: KZ
 */
#ifdef CATCH_ENABLED
#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

namespace unit_catch {

int main( int argc, char** argv ) {
  // global setup...

  int result = Catch::Session().run( argc, argv );

  // global clean-up...

  return result;
}
}
#endif


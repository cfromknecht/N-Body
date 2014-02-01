#include <nbody/CelestialSystem.h>
#include <nbody/Integrator.h>
#include <gtest/gtest.h>

#include <iostream>
#include <fstream>
#include <iosfwd>


TEST( integratorTest, forwardEuler )
{
  std::fstream sysFile{ "resources/nbody/binary-system-simple.txt" };
  auto es = ForwardEuler< CelestialSystem >( sysFile );
  for ( size_t i = 0; i < 1000; i++ ) {
    es.step( 0.01f );
  }
  CelestialSystem *system = es.getSystem();
  std::cout << "pos0: " << system->getPosition( 0 ) << " vel0: " << system->getVelocity( 0 ) << std::endl;
  std::cout << "pos1: " << system->getPosition( 1 ) << " vel1: " << system->getVelocity( 1 ) << std::endl;

  // Check masses
  ASSERT_FLOAT_EQ( system->getMass( 0 ), 10 );
  ASSERT_FLOAT_EQ( system->getMass( 1 ), 10 );
  
  // Check position
  ASSERT_FLOAT_EQ( system->getPosition( 0 ).x(), -0.49399781 );
  ASSERT_FLOAT_EQ( system->getPosition( 0 ).y(), 0.028223313 );
  ASSERT_FLOAT_EQ( system->getPosition( 0 ).z(), 0.0 );
  ASSERT_FLOAT_EQ( system->getPosition( 1 ).x(), 0.49399781 );
  ASSERT_FLOAT_EQ( system->getPosition( 1 ).y(), -0.028223313 );
  ASSERT_FLOAT_EQ( system->getPosition( 1 ).z(), 0.0 );

  // Check velocity
  ASSERT_FLOAT_EQ( system->getVelocity( 0 ).x(), 0.40118569 );
  ASSERT_FLOAT_EQ( system->getVelocity( 0 ).y(), 0.69844019 );
  ASSERT_FLOAT_EQ( system->getVelocity( 0 ).z(), 0.0 );
  ASSERT_FLOAT_EQ( system->getVelocity( 1 ).x(), -0.40118569 );
  ASSERT_FLOAT_EQ( system->getVelocity( 1 ).y(), -0.69844019 );
  ASSERT_FLOAT_EQ( system->getVelocity( 1 ).z(), 0.0 );
}

TEST( integratorTest, trapezoidal )
{
  std::fstream sysFile{ "resources/nbody/binary-system-simple.txt" };
  auto ts = Trapezoidal< CelestialSystem >( sysFile );
  for ( size_t i = 0; i < 1000; i++ ) {
    ts.step( 0.01f );
  }
  CelestialSystem *system = ts.getSystem();
  std::cout << "pos0: " << system->getPosition( 0 ) << " vel0: " << system->getVelocity( 0 ) << std::endl;
  std::cout << "pos1: " << system->getPosition( 1 ) << " vel1: " << system->getVelocity( 1 ) << std::endl;

  // Check masses
  ASSERT_FLOAT_EQ( system->getMass( 0 ), 10 );
  ASSERT_FLOAT_EQ( system->getMass( 1 ), 10 );
  
  // Check position
  ASSERT_FLOAT_EQ( system->getPosition( 0 ).x(), -19.53125 );
  ASSERT_FLOAT_EQ( system->getPosition( 0 ).y(), 0.0 );
  ASSERT_FLOAT_EQ( system->getPosition( 0 ).z(), 0.0 );
  ASSERT_FLOAT_EQ( system->getPosition( 1 ).x(), 19.53125 );
  ASSERT_FLOAT_EQ( system->getPosition( 1 ).y(), 0.0 );
  ASSERT_FLOAT_EQ( system->getPosition( 1 ).z(), 0.0 );

  // Check velocity
  ASSERT_FLOAT_EQ( system->getVelocity( 0 ).x(), 0.0 );
  ASSERT_FLOAT_EQ( system->getVelocity( 0 ).y(), 27.617188 );
  ASSERT_FLOAT_EQ( system->getVelocity( 0 ).z(), 0.0 );
  ASSERT_FLOAT_EQ( system->getVelocity( 1 ).x(), 0.0 );
  ASSERT_FLOAT_EQ( system->getVelocity( 1 ).y(), -27.617188 );
  ASSERT_FLOAT_EQ( system->getVelocity( 1 ).z(), 0.0 );
}

TEST( integratorTest, rk4 )
{
  std::fstream sysFile{ "resources/nbody/binary-system-simple.txt" };
  auto cs = RK4< CelestialSystem >( sysFile );

  for ( size_t i = 0; i < 1000; i++ ) {
    cs.step( 0.01f );
  }
  CelestialSystem *system = cs.getSystem();
  std::cout << "pos0: " << system->getPosition( 0 ) << " vel0: " << system->getVelocity( 0 ) << std::endl;
  std::cout << "pos1: " << system->getPosition( 1 ) << " vel1: " << system->getVelocity( 1 ) << std::endl;
}



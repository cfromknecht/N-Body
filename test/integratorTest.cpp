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
  for ( size_t i = 0; i < 1000; i++ )
    es.step( 0.01f );
  std::cout << "pos0: " << es.getSystem()->getPosition( 0 ); 
  std::cout << " vel0: " << es.getSystem()->getVelocity( 0 ) << std::endl;
  std::cout << "pos1: " << es.getSystem()->getPosition( 1 ); 
  std::cout << " vel1: " <<  es.getSystem()->getVelocity( 1 ) << std::endl;

  // Check masses
  ASSERT_FLOAT_EQ( es.getSystem()->getMass( 0 ), 10 );
  ASSERT_FLOAT_EQ( es.getSystem()->getMass( 1 ), 10 );
  
  // Check position
  ASSERT_FLOAT_EQ( es.getSystem()->getPosition( 0 ).x(), -0.49399781 );
  ASSERT_FLOAT_EQ( es.getSystem()->getPosition( 0 ).y(), 0.028223313 );
  ASSERT_FLOAT_EQ( es.getSystem()->getPosition( 0 ).z(), 0.0 );
  ASSERT_FLOAT_EQ( es.getSystem()->getPosition( 1 ).x(), 0.49399781 );
  ASSERT_FLOAT_EQ( es.getSystem()->getPosition( 1 ).y(), -0.028223313 );
  ASSERT_FLOAT_EQ( es.getSystem()->getPosition( 1 ).z(), 0.0 );

  // Check velocity
  ASSERT_FLOAT_EQ( es.getSystem()->getVelocity( 0 ).x(), 0.40118569 );
  ASSERT_FLOAT_EQ( es.getSystem()->getVelocity( 0 ).y(), 0.69844019 );
  ASSERT_FLOAT_EQ( es.getSystem()->getVelocity( 0 ).z(), 0.0 );
  ASSERT_FLOAT_EQ( es.getSystem()->getVelocity( 1 ).x(), -0.40118569 );
  ASSERT_FLOAT_EQ( es.getSystem()->getVelocity( 1 ).y(), -0.69844019 );
  ASSERT_FLOAT_EQ( es.getSystem()->getVelocity( 1 ).z(), 0.0 );
}

TEST( integratorTest, trapezoidal )
{
  std::fstream sysFile{ "resources/nbody/binary-system-simple.txt" };
  auto ts = Trapezoidal< CelestialSystem >( sysFile );
  for ( size_t i = 0; i < 1000; i++ )
    ts.step( 0.01f );
  std::cout << "pos0: " << ts.getSystem()->getPosition( 0 ) << " vel0: " << ts.getSystem()->getVelocity( 0 ) << std::endl;
  std::cout << "pos1: " << ts.getSystem()->getPosition( 1 ) << " vel1: " << ts.getSystem()->getVelocity( 1 ) << std::endl;

  // Check masses
  ASSERT_FLOAT_EQ( ts.getSystem()->getMass( 0 ), 10 );
  ASSERT_FLOAT_EQ( ts.getSystem()->getMass( 1 ), 10 );
  
  // Check position
  ASSERT_FLOAT_EQ( ts.getSystem()->getPosition( 0 ).x(), -19.53125 );
  ASSERT_FLOAT_EQ( ts.getSystem()->getPosition( 0 ).y(), 0.0 );
  ASSERT_FLOAT_EQ( ts.getSystem()->getPosition( 0 ).z(), 0.0 );
  ASSERT_FLOAT_EQ( ts.getSystem()->getPosition( 1 ).x(), 19.53125 );
  ASSERT_FLOAT_EQ( ts.getSystem()->getPosition( 1 ).y(), 0.0 );
  ASSERT_FLOAT_EQ( ts.getSystem()->getPosition( 1 ).z(), 0.0 );

  // Check velocity
  ASSERT_FLOAT_EQ( ts.getSystem()->getVelocity( 0 ).x(), 0.0 );
  ASSERT_FLOAT_EQ( ts.getSystem()->getVelocity( 0 ).y(), 27.617188 );
  ASSERT_FLOAT_EQ( ts.getSystem()->getVelocity( 0 ).z(), 0.0 );
  ASSERT_FLOAT_EQ( ts.getSystem()->getVelocity( 1 ).x(), 0.0 );
  ASSERT_FLOAT_EQ( ts.getSystem()->getVelocity( 1 ).y(), -27.617188 );
  ASSERT_FLOAT_EQ( ts.getSystem()->getVelocity( 1 ).z(), 0.0 );
}

TEST( integratorTest, rk4 )
{
  std::fstream sysFile{ "resources/nbody/binary-system-simple.txt" };
  auto cs = RK4< CelestialSystem >();

  for ( size_t i = 0; i < 1000; i++ )
    cs.step( 0.01f );
  std::cout << "pos0: " << cs.getSystem()->getPosition( 0 ) << " vel0: " << cs.getSystem()->getVelocity( 0 ) << std::endl;
  std::cout << "pos1: " << cs.getSystem()->getPosition( 1 ) << " vel1: " << cs.getSystem()->getVelocity( 1 ) << std::endl;
}



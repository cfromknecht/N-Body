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
  for ( size_t i = 0; i < 40; i++ )
    es.step( 0.01f );
  ParticleSystem *system = es.getSystem();

  // Check masses
  ASSERT_FLOAT_EQ( system->getMass( 0 ), 10 );
  ASSERT_FLOAT_EQ( system->getMass( 1 ), 10 );
  
  // Check position
  ASSERT_FLOAT_EQ( es.getSystem()->getPosition( 0 ).x(), 0.23644742 );
  ASSERT_FLOAT_EQ( es.getSystem()->getPosition( 0 ).y(), -0.90136856 );
  ASSERT_FLOAT_EQ( es.getSystem()->getPosition( 0 ).z(), 0.0 );
  ASSERT_FLOAT_EQ( es.getSystem()->getPosition( 1 ).x(), -0.23644742 );
  ASSERT_FLOAT_EQ( es.getSystem()->getPosition( 1 ).y(), 0.90136856 );
  ASSERT_FLOAT_EQ( es.getSystem()->getPosition( 1 ).z(), 0.0 );

  // Check velocity
  ASSERT_FLOAT_EQ( es.getSystem()->getVelocity( 0 ).x(), 0.63465178 );
  ASSERT_FLOAT_EQ( es.getSystem()->getVelocity( 0 ).y(), -8.0781898 );
  ASSERT_FLOAT_EQ( es.getSystem()->getVelocity( 0 ).z(), 0.0 );
  ASSERT_FLOAT_EQ( es.getSystem()->getVelocity( 1 ).x(), -0.63465178 );
  ASSERT_FLOAT_EQ( es.getSystem()->getVelocity( 1 ).y(), 8.0781898 );
  ASSERT_FLOAT_EQ( es.getSystem()->getVelocity( 1 ).z(), 0.0 );
}

TEST( integratorTest, trapezoidal )
{
  std::fstream sysFile{ "resources/nbody/binary-system-simple.txt" };
  auto ts = Trapezoidal< CelestialSystem >( sysFile );
  for ( size_t i = 0; i < 40; i++ )
    ts.step( 0.01f );
  ParticleSystem *system = ts.getSystem();

  // Check masses
  ASSERT_FLOAT_EQ( system->getMass( 0 ), 10 );
  ASSERT_FLOAT_EQ( system->getMass( 1 ), 10 );
  
  // Check position
  ASSERT_FLOAT_EQ( ts.getSystem()->getPosition( 0 ).x(), -0.32648417 );
  ASSERT_FLOAT_EQ( ts.getSystem()->getPosition( 0 ).y(), -0.98219901 );
  ASSERT_FLOAT_EQ( ts.getSystem()->getPosition( 0 ).z(), 0.0 );
  ASSERT_FLOAT_EQ( ts.getSystem()->getPosition( 1 ).x(), 0.32648417 );
  ASSERT_FLOAT_EQ( ts.getSystem()->getPosition( 1 ).y(), 0.98219901 );
  ASSERT_FLOAT_EQ( ts.getSystem()->getPosition( 1 ).z(), 0.0 );

  // Check velocity
  ASSERT_FLOAT_EQ( ts.getSystem()->getVelocity( 0 ).x(), -2.831713 );
  ASSERT_FLOAT_EQ( ts.getSystem()->getVelocity( 0 ).y(), -6.9607625 );
  ASSERT_FLOAT_EQ( ts.getSystem()->getVelocity( 0 ).z(), 0.0 );
  ASSERT_FLOAT_EQ( ts.getSystem()->getVelocity( 1 ).x(), 2.831713 );
  ASSERT_FLOAT_EQ( ts.getSystem()->getVelocity( 1 ).y(), 6.9607625 );
  ASSERT_FLOAT_EQ( ts.getSystem()->getVelocity( 1 ).z(), 0.0 );
}

TEST( integratorTest, rk4 )
{
  std::fstream sysFile{ "resources/nbody/binary-system-simple.txt" };
  auto ts = RK4< CelestialSystem >( sysFile );

  for ( size_t i = 0; i < 40; i++ )
    ts.step( 0.01f );
  ParticleSystem *system = ts.getSystem();

  // Check masses
  ASSERT_FLOAT_EQ( system->getMass( 0 ), 10 );
  ASSERT_FLOAT_EQ( system->getMass( 1 ), 10 );
  
  // Check position
  ASSERT_FLOAT_EQ( ts.getSystem()->getPosition( 0 ).x(), -0.057943415 );
  ASSERT_FLOAT_EQ( ts.getSystem()->getPosition( 0 ).y(), -0.90091085 );
  ASSERT_FLOAT_EQ( ts.getSystem()->getPosition( 0 ).z(), 0.0 );
  ASSERT_FLOAT_EQ( ts.getSystem()->getPosition( 1 ).x(), 0.057943415 );
  ASSERT_FLOAT_EQ( ts.getSystem()->getPosition( 1 ).y(), 0.90091085 );
  ASSERT_FLOAT_EQ( ts.getSystem()->getPosition( 1 ).z(), 0.0 );

  // Check velocity
  ASSERT_FLOAT_EQ( ts.getSystem()->getVelocity( 0 ).x(), -0.72619396 );
  ASSERT_FLOAT_EQ( ts.getSystem()->getVelocity( 0 ).y(), -5.9548426 );
  ASSERT_FLOAT_EQ( ts.getSystem()->getVelocity( 0 ).z(), 0.0 );
  ASSERT_FLOAT_EQ( ts.getSystem()->getVelocity( 1 ).x(), 0.72619396 );
  ASSERT_FLOAT_EQ( ts.getSystem()->getVelocity( 1 ).y(), 5.9548426 );
  ASSERT_FLOAT_EQ( ts.getSystem()->getVelocity( 1 ).z(), 0.0 );
}



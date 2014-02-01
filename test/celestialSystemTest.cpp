#include <fstream>
#include <iosfwd>

#include <nbody/CelestialSystem.h>
#include <nbody/Integrator.h>
#include <gtest/gtest.h>

TEST( celestialSystemTest, init )
{
  auto ps = CelestialSystem( 20 );
  ASSERT_EQ( ps.getN(), (size_t) 20 );
}

TEST( celestialSystemTest, readFile )
{
  std::ifstream sysFile{ "resources/nbody/binary-system-simple.txt" };
  auto ps = CelestialSystem( sysFile );
  ASSERT_EQ( ps.getN(), (size_t) 2 );

  // Check mass
  ASSERT_FLOAT_EQ( ps.getMass( 0 ), 10.0 );
  ASSERT_FLOAT_EQ( ps.getMass( 1 ), 10.0 );

  // Check position
  ASSERT_FLOAT_EQ( ps.getPosition( 0 ).x(), -0.5 );
  ASSERT_FLOAT_EQ( ps.getPosition( 0 ).y(), 0.0 );
  ASSERT_FLOAT_EQ( ps.getPosition( 0 ).z(), 0.0 );
  ASSERT_FLOAT_EQ( ps.getPosition( 1 ).x(), 0.5 );
  ASSERT_FLOAT_EQ( ps.getPosition( 1 ).y(), 0.0 );
  ASSERT_FLOAT_EQ( ps.getPosition( 1 ).z(), 0.0 );

  // Check velocity
  ASSERT_FLOAT_EQ( ps.getVelocity( 0 ).x(), 0.0 );
  ASSERT_FLOAT_EQ( ps.getVelocity( 0 ).y(), 7.07e-1 );
  ASSERT_FLOAT_EQ( ps.getVelocity( 0 ).z(), 0.0 );
  ASSERT_FLOAT_EQ( ps.getVelocity( 1 ).x(), 0.0 );
  ASSERT_FLOAT_EQ( ps.getVelocity( 1 ).y(), -7.07e-1 );
  ASSERT_FLOAT_EQ( ps.getVelocity( 1 ).z(), 0.0 );
}

TEST( celestialSystemTest, evalTest )
{
  std::ifstream sysFile{ "resources/nbody/binary-system-simple.txt" };
  auto ps = ForwardEuler< CelestialSystem >( sysFile );

  for ( size_t i = 0; i < 40; i++ )
    ps.step( 0.01f );
  std::cout << "eval pos0: " << ps.getSystem()->getPosition( 0 ) << " vel0: " << ps.getSystem()->getVelocity( 0 ) << std::endl;
  std::cout << "eval pos1: " << ps.getSystem()->getPosition( 1 ) << " vel1: " << ps.getSystem()->getVelocity( 1 ) << std::endl;

  // Check mass
  ASSERT_EQ( ps.getSystem()->getMass( 0 ), 10.0f );
  ASSERT_EQ( ps.getSystem()->getMass( 1 ), 10.0f );

  // Check position
  ASSERT_FLOAT_EQ( ps.getSystem()->getPosition( 0 ).x(), 0.23644742 );
  ASSERT_FLOAT_EQ( ps.getSystem()->getPosition( 0 ).y(), -0.90136856 );
  ASSERT_FLOAT_EQ( ps.getSystem()->getPosition( 0 ).z(), 0.0 );
  ASSERT_FLOAT_EQ( ps.getSystem()->getPosition( 1 ).x(), -0.23644742 );
  ASSERT_FLOAT_EQ( ps.getSystem()->getPosition( 1 ).y(), 0.90136856 );
  ASSERT_FLOAT_EQ( ps.getSystem()->getPosition( 1 ).z(), 0.0 );

  // Check velocity
  ASSERT_FLOAT_EQ( ps.getSystem()->getVelocity( 0 ).x(), 0.63465178 );
  ASSERT_FLOAT_EQ( ps.getSystem()->getVelocity( 0 ).y(), -8.07819 );
  ASSERT_FLOAT_EQ( ps.getSystem()->getVelocity( 0 ).z(), 0.0 );
  ASSERT_FLOAT_EQ( ps.getSystem()->getVelocity( 1 ).x(), -0.63465178 );
  ASSERT_FLOAT_EQ( ps.getSystem()->getVelocity( 1 ).y(), 8.07819 );
  ASSERT_FLOAT_EQ( ps.getSystem()->getVelocity( 1 ).z(), 0.0 );

}


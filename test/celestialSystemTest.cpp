#include <fstream>
#include <iosfwd>

#include <nbody/CelestialSystem.h>
#include <nbody/Integrator.h>
#include <gtest/gtest.h>

TEST( celestialSystemTest, init )
{
  float maxAxis = 10.0f,
        maxSpeed = 1.0f,
        maxMass = 10.0f;
  auto ps = CelestialSystem( 20, maxAxis, maxSpeed, maxMass );
  ASSERT_EQ( ps.getN(), (size_t) 20 );
  for ( size_t i = 0; i < ps.getN(); i++ ) {
    ASSERT_LE( ps.getMass( i ), maxMass );
    ASSERT_GE( ps.getMass( i ), 0.0f );

    ASSERT_LE( ps.getPosition( i ).x(), maxAxis );
    ASSERT_GE( ps.getPosition( i ).x(), -maxAxis );
    ASSERT_LE( ps.getPosition( i ).y(), maxAxis );
    ASSERT_GE( ps.getPosition( i ).y(), -maxAxis );
    ASSERT_LE( ps.getPosition( i ).z(), maxAxis );
    ASSERT_GE( ps.getPosition( i ).z(), -maxAxis );

    ASSERT_LE( ps.getVelocity( i ).x(), maxSpeed );
    ASSERT_GE( ps.getVelocity( i ).x(), -maxSpeed );
    ASSERT_LE( ps.getVelocity( i ).y(), maxSpeed );
    ASSERT_GE( ps.getVelocity( i ).y(), -maxSpeed );
    ASSERT_LE( ps.getVelocity( i ).z(), maxSpeed );
    ASSERT_GE( ps.getVelocity( i ).z(), -maxSpeed );
  }
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


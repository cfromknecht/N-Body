#include <nbody/CelestialSystem.h>
#include <nbody/Integrator.h>
#include <gtest/gtest.h>

#include <iostream>
#include <fstream>
#include <iosfwd>

class EasySystem : public ParticleSystem
{
public:
  EasySystem( std::istream &is ) : ParticleSystem( is ) {}
  std::vector< Vector3f > evalF( std::vector< Vector3f > state ) { return state; }
  void draw() {}
};

TEST( integratorTest, forwardEuler )
{
  std::fstream sysFile{ "resources/nbody/binary-system-simple.txt" };
  auto es = EasySystem( sysFile );
  auto fe = ForwardEuler();
  for ( size_t i = 0; i < 4; i++ )
    fe.step( &es, 1.0 );

  // Check masses
  ASSERT_FLOAT_EQ( es.getMass( 0 ), 10 );
  ASSERT_FLOAT_EQ( es.getMass( 1 ), 10 );
  
  // Check position
  ASSERT_FLOAT_EQ( es.getPosition( 0 ).x(), -8.0 );
  ASSERT_FLOAT_EQ( es.getPosition( 0 ).y(), 0.0 );
  ASSERT_FLOAT_EQ( es.getPosition( 0 ).z(), 0.0 );
  ASSERT_FLOAT_EQ( es.getPosition( 1 ).x(), 8.0 );
  ASSERT_FLOAT_EQ( es.getPosition( 1 ).y(), 0.0 );
  ASSERT_FLOAT_EQ( es.getPosition( 1 ).z(), 0.0 );

  // Check velocity
  ASSERT_FLOAT_EQ( es.getVelocity( 0 ).x(), 0.0 );
  ASSERT_FLOAT_EQ( es.getVelocity( 0 ).y(), 11.312 );
  ASSERT_FLOAT_EQ( es.getVelocity( 0 ).z(), 0.0 );
  ASSERT_FLOAT_EQ( es.getVelocity( 1 ).x(), 0.0 );
  ASSERT_FLOAT_EQ( es.getVelocity( 1 ).y(), -11.312 );
  ASSERT_FLOAT_EQ( es.getVelocity( 1 ).z(), 0.0 );
}

TEST( integratorTest, trapezoidal )
{
  std::fstream sysFile{ "resources/nbody/binary-system-simple.txt" };
  auto es = EasySystem( sysFile );
  auto tr = Trapezoidal();
  for ( size_t i = 0; i < 4; i++ )
    tr.step( &es, 1.0 );

  // Check masses
  ASSERT_FLOAT_EQ( es.getMass( 0 ), 10 );
  ASSERT_FLOAT_EQ( es.getMass( 1 ), 10 );
  
  // Check position
  ASSERT_FLOAT_EQ( es.getPosition( 0 ).x(), -19.53125 );
  ASSERT_FLOAT_EQ( es.getPosition( 0 ).y(), 0.0 );
  ASSERT_FLOAT_EQ( es.getPosition( 0 ).z(), 0.0 );
  ASSERT_FLOAT_EQ( es.getPosition( 1 ).x(), 19.53125 );
  ASSERT_FLOAT_EQ( es.getPosition( 1 ).y(), 0.0 );
  ASSERT_FLOAT_EQ( es.getPosition( 1 ).z(), 0.0 );

  // Check velocity
  ASSERT_FLOAT_EQ( es.getVelocity( 0 ).x(), 0.0 );
  ASSERT_FLOAT_EQ( es.getVelocity( 0 ).y(), 27.617188 );
  ASSERT_FLOAT_EQ( es.getVelocity( 0 ).z(), 0.0 );
  ASSERT_FLOAT_EQ( es.getVelocity( 1 ).x(), 0.0 );
  ASSERT_FLOAT_EQ( es.getVelocity( 1 ).y(), -27.617188 );
  ASSERT_FLOAT_EQ( es.getVelocity( 1 ).z(), 0.0 );
}

TEST( integratorTest, rk4 )
{
  std::fstream sysFile{ "resources/nbody/binary-system-simple.txt" };
  auto cs = CelestialSystem( sysFile );
  auto rk = RK4();

  for ( size_t i = 0; i < 1000; i++ )
    rk.step( &cs, 0.01f );
  std::cout << "pos0: " << cs.getPosition( 0 ) << " vel0: " << cs.getVelocity( 0 ) << std::endl;
  std::cout << "pos1: " << cs.getPosition( 1 ) << " vel1: " << cs.getVelocity( 1 ) << std::endl;

}

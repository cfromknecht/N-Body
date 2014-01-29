#include <iostream>

#include <nbody/CelestialSystem.h>
#include <nbody/constants.h>

CelestialSystem::CelestialSystem( const size_t nBodies ) : ParticleSystem( nBodies ) {}

Vector3f
CelestialSystem::computeGravitationTwixt( const size_t i, 
                                          const size_t j )
{
  Vector3f radius = getPosition( j ) - getPosition( i );
  float dist = radius.norm();
  float invDistCubed = cube( 1.0f / dist );
  return nbody::NEWTON_G * getMass( j ) * invDistCubed * radius;
}

std::vector< Vector3f >
CelestialSystem::evalF( const std::vector< Vector3f > state )
{
  std::vector< Vector3f > newState;
  newState.reserve( state.size() );
  
  for ( size_t i = 0; i < getN(); i++ ) {
    newState.push_back( getVelocity( i ) );

    Vector3f acc{ 0.0f, 0.0f, 0.0f };
    for ( size_t j = 0; j < getN(); j++ ) 
      if ( i != j )
        acc += computeGravitationTwixt( i, j );
    newState.push_back( acc );
  }
  return newState;
}

void
CelestialSystem::draw() {}

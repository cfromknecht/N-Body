#include <iostream>

#include <nbody/CelestialSystem.h>
#include <nbody/constants.h>

CelestialSystem::CelestialSystem( const size_t nBodies ) : 
  ParticleSystem( nBodies ) {}

Vector3f
CelestialSystem::computeGravitationTwixt( const size_t                  i, 
                                          const size_t                  j,
                                          const std::vector< Vector3f > state ) {
  Vector3f radius = state[2 * j] - state[2 * i];
  float dist = radius.norm();
  float invDistCubed = cube( 1.0f / dist );
  return nbody::NEWTON_G * getMass( j ) * invDistCubed * radius;
}

std::vector< Vector3f >
CelestialSystem::evalF( const std::vector< Vector3f > state ) {
  std::vector< Vector3f > newState;
  newState.reserve( state.size() );
  for ( size_t i = 0; i < state.size() / 2; i++ ) {
    newState.push_back( state[2 * i + 1] );
    Vector3f acc{ 0.0f, 0.0f, 0.0f };
    for ( size_t j = 0; j < state.size() / 2; j++ ) {
      if ( i != j ) {
        acc += computeGravitationTwixt( i, j, state );
      }
    newState.push_back( acc );
    }
  }
  return newState;
}

void
CelestialSystem::draw() {}

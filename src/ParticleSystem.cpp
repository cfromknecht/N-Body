#include <nbody/ParticleSystem.h>

#include <iostream>


ParticleSystem::ParticleSystem( const size_t nBodies, const float maxAxis, 
    const float maxSpeed, const float maxMass ) : _nBodies{ nBodies } {
  _state.reserve( 2 * _nBodies );  
  _masses.reserve( _nBodies );
  for ( size_t i = 0; i < _nBodies; i++ ) {
    Vector3f pos{ rand() / static_cast<float>( RAND_MAX / maxAxis ), 
                  rand() / static_cast<float>( RAND_MAX / maxAxis ),
                  rand() / static_cast<float>( RAND_MAX / maxAxis ) };
    Vector3f vel{ rand() / static_cast<float>( RAND_MAX / maxSpeed ),
                  rand() / static_cast<float>( RAND_MAX / maxSpeed ),
                  rand() / static_cast<float>( RAND_MAX / maxSpeed ) };
    float mass = rand() / static_cast<float>( RAND_MAX / maxMass );
    _state.push_back( pos );
    _state.push_back( vel );
    _masses.push_back( mass );
  }
}

ParticleSystem::ParticleSystem( std::istream &is ) {
  is >> _nBodies;
  _state.reserve( 2 * _nBodies );
  _masses.reserve( _nBodies );
  Vector3f blank;
  for ( size_t i = 0; i < _nBodies; i++ ) {
    Vector3f pos, vel;
    float mass;
    is >> pos >> vel >> blank >> mass;
    _state.push_back( pos );
    _state.push_back( vel );
    _masses.push_back( mass );
  }
}



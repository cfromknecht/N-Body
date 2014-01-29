#include "nbody/ParticleSystem.h"

#include <iostream>

ParticleSystem::ParticleSystem( size_t nBodies ) : _nBodies( nBodies ) 
{
  _state.reserve( 2 * _nBodies );  
  _masses.reserve( _nBodies );
}

ParticleSystem::ParticleSystem( std::istream &is )
{
  is >> _nBodies;
  _state.reserve( 2 * _nBodies );
  _masses.reserve( _nBodies );
  Vector3f blank;
  for ( size_t i = 0; i < _nBodies; i++ )
  {
    Vector3f pos, vel;
    float mass;
    is >> pos >> vel >> blank >> mass;
    _state.push_back( pos );
    _state.push_back( vel );
    _masses.push_back( mass );
  }
}


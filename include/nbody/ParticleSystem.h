#ifndef PARTICLE_SYSTEM_H_
#define PARTICLE_SYSTEM_H_

#include <vector>

#include <nbody/Vector3.h>

class ParticleSystem
{
  size_t _nBodies;
  std::vector< Vector3f > _state;
  std::vector< float >    _masses;
public:
  ParticleSystem( const size_t nBodies, const float maxAxis, 
      const float maxSpeed, const float maxMass );
  ParticleSystem( std::istream &is );
  virtual ~ParticleSystem() {}
  
  inline size_t getN() const { return _nBodies; }
  inline float getMass( const size_t i ) const { return _masses[i]; }
  inline std::vector< Vector3f > getState() const { return _state; };
  inline void setState( const std::vector< Vector3f > &newState ) { 
    _state = newState; 
  }
  inline Vector3f getPosition( const size_t i ) const { return _state[2 * i]; }
  inline Vector3f getVelocity( const size_t i ) const { 
    return _state[2 * i + 1]; 
  }

  virtual std::vector< Vector3f > evalF( const std::vector< Vector3f > state)=0;
};

#endif


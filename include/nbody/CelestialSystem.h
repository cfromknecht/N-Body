#ifndef CELESTIAL_SYSTEM_H_
#define CELESTIAL_SYSTEM_H_

#include "nbody/ParticleSystem.h"

class CelestialSystem : public ParticleSystem
{
  CelestialSystem() = delete;
  Vector3f computeGravitationTwixt( const size_t i, const size_t j );
public:
  CelestialSystem( const size_t nBodies );
  CelestialSystem( std::istream &is ) : ParticleSystem( is ) {}
  std::vector< Vector3f > evalF( const std::vector< Vector3f > state );
  void draw();
};

#endif


#ifndef PARTICLE_SYSTEM_H_
#define PARTICLE_SYSTEM_H_

#include <vector>

#include <nbody/Vector3.h>
#include <nbody/Integrator.h>

class Integrator;

template <typename Integrator_T>
class ParticleSystem
{
  size_t _nBodies;
  std::vector< Vector3f > _state;
  std::vector< float >    _masses;
  Integrator *_integrator;
public:
  ParticleSystem( size_t nBodies ) : 
    _nBodies( nBodies ),
    _integrator( new Integrator_T{} ) {
        _state.reserve( 2 * _nBodies );
        _masses.reserve( _nBodies );
    }
  ParticleSystem( std::istream &is ) :
    _integrator( new Integrator_T{} ) {
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
  virtual std::vector< Vector3f > evalF( const std::vector< Vector3f > state) = 0;
  virtual void draw() = 0;
  inline size_t getN() const { return _nBodies; }
  inline float getMass( const size_t i ) const { return _masses[i]; }
  inline std::vector< Vector3f > getState() const { return _state; };
  inline void setState( const std::vector< Vector3f > &newState ) { _state = newState; }
  inline Vector3f getPosition( const size_t i ) const { return _state[2 * i]; }
  inline Vector3f getVelocity( const size_t i ) const { return _state[2 * i + 1]; }
  void integrateSystem( float dt ) { _integrator->step(this, dt); } 
};

#endif


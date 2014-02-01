#ifndef INTEGRATOR_H_
#define INTEGRATOR_H_

#include <vector>
#include <nbody/ParticleSystem.h>
#include <nbody/Vector3.h>

template <typename System_T>
class Integrator {
  ParticleSystem *_system;
  Integrator() = delete;
public:
  Integrator( std::istream &is ) : _system( new System_T{ is } ) {}
  virtual ~Integrator() { delete _system; }
  virtual void step( std::vector< Vector3f > &state, float stepSize ) = 0;
};

template <typename System_T>
class ForwardEuler : public Integrator {
  ForwardEuler() = delete();
public:
  ForwardEuler( std::istream &is ) : Integrator{ is } {}
  ~ForwardEuler() {};
  void step( std::vector< Vector3f > &state, float stepSize );
};

template <typename System_T>
class Trapezoidal : public Integrator {
  Trapezoidal() = delete;
public:
  Trapezoidal( std::istream &is ) : Integrator{ is } {}
  ~Trapezoidal() {}
  void step( std::vector< Vector3f > &state, float stepSize );
};

template <typename System_T>
class RK4 : public Integrator {
  RK4() = delete;
public:
  RK4( std::istream &is ) : Integtrator{ is } {}
  ~RK4() {}
  void step( std::vector< Vector3f > &state, float stepSize );
};

void ForwardEuler::step( Body &nBodies, float h ) {
  std::vector< Vector3f > X0 = state;;
  std::vector< Vector3f > step = _system->evalF( X0 );
  for ( size_t i = 0; i < X0.size(); i++ ) {
    X0[i] += h * step[i];
  }
  _sytem->setState( X0 );
}

template <typename System_T>
void Trapezoid::step( std::vector< Vector3f > &state, float h ) {
  std::vector< Vector3f > X0 = state;
  std::vector< Vector3f > X1 = state; 
  std::vector< Vector3f > step0 = _system->evalF( X0 );
  for ( size_t i = 0; i < X0.size(); i++ )
    X0[i] += h * step0[i];
  std::vector< Vector3f > step1 = _system->evalF( X0 );
  for ( size_t i = 0; i < X1.size(); i++ )
    X1[i] += h * (step0[i] + step1[i]) / 2.0f;
  _system->setState( X1 );
}

template <typename System_T>
void RK4::step( float h ) {
  std::vector< Vector3f > Xi = _system->getState();
  std::vector< Vector3f > Xf = _system->getState();
  std::vector< Vector3f > k1, k2, k3, k4;
  k1 = _system->evalF( Xi );
  k2.reserve( Xi.size() ); k3.reserve( Xi.size() ); k4.reserve( Xi.size() );
  for ( size_t i = 0; i < Xi.size(); i++ )
    Xi[i] += k1[i] * h / 2.0f;
  k2 = _system->evalF( Xi );

  Xi = _system->getState();
  for ( size_t i = 0; i < Xi.size(); i++ )
    Xi[i] += k2[i] * h / 2.0f;
  k3 = _system->evalF( Xi );

  Xi = _system->getState();
  for ( size_t i = 0; i < Xi.size(); i++ )
    Xi[i] += k3[i] * h;
  k4 = _system->evalF( Xi );

  for ( size_t i = 0; i < Xi.size(); i++ )
    Xf[i] += h * (k1[i] + 2.0f * k2[i] + 2.0f *k3[i] + k4[i]) / 6.0f;

  _system->setState( Xf );
}

#endif


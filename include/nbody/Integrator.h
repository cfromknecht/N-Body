#ifndef INTEGRATOR_H_
#define INTEGRATOR_H_

#include <vector>
#include <nbody/ParticleSystem.h>
#include <nbody/Vector3.h>

template <typename System_T>
class Integrator {
  Integrator() = delete;
protected:
  ParticleSystem *_system;
public:
  Integrator( std::istream &is ) : _system( new System_T{ is } ) {}
  virtual ~Integrator() { delete _system; }
  virtual void step( float stepSize ) = 0;
  inline ParticleSystem* getSystem() { return _system; }
};

template <typename System_T>
class ForwardEuler : public Integrator<System_T> {
  ForwardEuler() = delete;
public:
  ForwardEuler( std::istream &is ) : Integrator<System_T>{ is } {}
  ~ForwardEuler() {};
  void step( float stepSize );
};

template <typename System_T>
class Trapezoidal : public Integrator<System_T> {
  Trapezoidal() = delete;
public:
  Trapezoidal( std::istream &is ) : Integrator<System_T>{ is } {}
  ~Trapezoidal() {}
  void step( float stepSize );
};

template <typename System_T>
class RK4 : public Integrator<System_T> {
  RK4() = delete;
public:
  RK4( std::istream &is ) : Integrator<System_T>{ is } {}
  ~RK4() {}
  void step( float stepSize );
};

template <typename System_T>
void ForwardEuler<System_T>::step( float h ) {
  std::vector< Vector3f > X0 = this->_system->getState();
  std::vector< Vector3f > step = this->_system->evalF( X0 );
  for ( size_t i = 0; i < X0.size(); i++ ) {
    X0[i] += h * step[i];
  }
  this->_system->setState( X0 );
}

template <typename System_T>
void Trapezoidal<System_T>::step( float h ) {
  std::vector< Vector3f > X0 = this->_system->getState();
  std::vector< Vector3f > X1 = this->_system->getState(); 
  std::vector< Vector3f > step0 = this->_system->evalF( X0 );
  for ( size_t i = 0; i < X0.size(); i++ )
    X0[i] += h * step0[i];
  std::vector< Vector3f > step1 = this->_system->evalF( X0 );
  for ( size_t i = 0; i < X1.size(); i++ )
    X1[i] += h * (step0[i] + step1[i]) / 2.0f;
  this->_system->setState( X1 );
}

template <typename System_T>
void RK4<System_T>::step( float h ) {
  std::vector< Vector3f > Xi = this->_system->getState();
  std::vector< Vector3f > Xf = this->_system->getState();
  std::vector< Vector3f > k1, k2, k3, k4;
  k1 = this->_system->evalF( Xi );
  k2.reserve( Xi.size() ); k3.reserve( Xi.size() ); k4.reserve( Xi.size() );
  for ( size_t i = 0; i < Xi.size(); i++ )
    Xi[i] += k1[i] * h / 2.0f;
  k2 = this->_system->evalF( Xi );

  Xi = this->_system->getState();
  for ( size_t i = 0; i < Xi.size(); i++ )
    Xi[i] += k2[i] * h / 2.0f;
  k3 = this->_system->evalF( Xi );

  Xi = this->_system->getState();
  for ( size_t i = 0; i < Xi.size(); i++ )
    Xi[i] += k3[i] * h;
  k4 = this->_system->evalF( Xi );

  for ( size_t i = 0; i < Xi.size(); i++ )
    Xf[i] += h * (k1[i] + 2.0f * k2[i] + 2.0f *k3[i] + k4[i]) / 6.0f;

  this->_system->setState( Xf );
}

#endif


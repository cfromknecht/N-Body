#include <iostream>

#include "nbody/Integrator.h"

void
ForwardEuler::step( ParticleSystem *sys,
                    float          h )
{
  std::vector< Vector3f > X0 = sys->getState();
  std::vector< Vector3f > step = sys->evalF( X0 );
  for ( size_t i = 0; i < X0.size(); i++ )
    X0[i] += h * step[i];
  sys->setState( X0 );
}

void
Trapezoidal::step( ParticleSystem *sys,
                   float          h )
{
  std::vector< Vector3f > X0 = sys->getState();
  std::vector< Vector3f > X1 = sys->getState();
  std::vector< Vector3f > step0 = sys->evalF( X0 );
  for ( size_t i = 0; i < X0.size(); i++ )
    X0[i] += h * step0[i];
  std::vector< Vector3f > step1 = sys->evalF( X0 );
  for ( size_t i = 0; i < X1.size(); i++ )
    X1[i] += h * (step0[i] + step1[i]) / (float) 2.0;
  sys->setState( X1 );
}

void
RK4::step( ParticleSystem *sys,
           float          h )
{
  std::vector< Vector3f > X0 = sys->getState();
  std::vector< Vector3f > k1 = sys->getState();
  std::vector< Vector3f > k2, k3, k4;
  k2.reserve( X0.size() ); k3.reserve( X0.size() ); k4.reserve( X0.size() );
  for ( size_t i = 0; i < X0.size(); i++ )
    k2.push_back( X0[i] + k1[i] * h / 2.0f );
}

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
    X1[i] += h * (step0[i] + step1[i]) / 2.0f;
  sys->setState( X1 );
}

void
RK4::step( ParticleSystem *sys,
           float          h )
{
  std::vector< Vector3f > Xi = sys->getState();
  std::vector< Vector3f > Xf = sys->getState();
  std::vector< Vector3f > k1, k2, k3, k4;
  k1 = sys->evalF( Xi );
  k2.reserve( Xi.size() ); k3.reserve( Xi.size() ); k4.reserve( Xi.size() );
  for ( size_t i = 0; i < Xi.size(); i++ )
    Xi[i] += k1[i] * h / 2.0f;
  k2 = sys->evalF( Xi );

  Xi = sys->getState();
  for ( size_t i = 0; i < Xi.size(); i++ )
    Xi[i] += k2[i] * h / 2.0f;
  k3 = sys->evalF( Xi );

  Xi = sys->getState();
  for ( size_t i = 0; i < Xi.size(); i++ )
    Xi[i] += k3[i] * h;
  k4 = sys->evalF( Xi );

  for ( size_t i = 0; i < Xi.size(); i++ )
    Xf[i] += h * (k1[i] + 2.0f * k2[i] + 2.0f *k3[i] + k4[i]) / 6.0f;

  sys->setState( Xf );
}

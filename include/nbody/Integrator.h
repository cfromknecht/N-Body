#ifndef INTEGRATOR_H_
#define INTEGRATOR_H_

#include "nbody/ParticleSystem.h"

class Integrator
{
public:
  virtual void step( ParticleSystem *sys, float stepSize ) = 0;
};

class ForwardEuler : public Integrator
{
public:
  void step( ParticleSystem *sys, float stepSize );
};

class Trapezoidal : public Integrator
{
public:
  void step( ParticleSystem *sys, float stepSize );
};

class RK4 : public Integrator
{
public:
  void step( ParticleSystem *sys, float stepSiez );
};

#endif


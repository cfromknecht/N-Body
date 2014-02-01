#ifndef INTEGRATOR_H_
#define INTEGRATOR_H_

#include <vector>
#include <nbody/Vector3.h>

class Integrator {
public:
  virtual void step( std::vector< Vector3f > &state, float stepSize ) = 0;
};

class ForwardEuler : public Integrator {
public:
  virtual void step( std::vector< Vector3f > &state, float stepSize ) = 0;
};

class Trapezoidal : public Integrator {
public:
  virtual void step( std::vector< Vector3f > &state, float stepSize ) = 0;
};

class RK4 : public Integrator {
public:
  virtual void step( std::vector< Vector3f > &state, float stepSize ) = 0;
};

#endif


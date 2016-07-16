#include "environment.h"

#include "body.h"

#include <cmath>

unsigned int Body::ms_nextUniqueId = 1;

Body::Body(Environment* environment)
: m_id(ms_nextUniqueId++),
  m_x(),
  m_para(),
  m_environment(environment)
{
  m_x[0] = 200.0;
  m_x[1] = 200.0;
  m_x[2] = 0;
  m_x[3] = 0;

  m_para[0] = 1.0; // mass [kg]
  m_para[1] = 15.0; // radius [m]
}


Body::~Body()
{
}


void
Body::setPosition(double xin, double yin)
{
  m_x[0] = xin;
  m_x[1] = yin;
}


void
Body::setVelocity(double vxin, double vyin)
{
  m_x[2] = vxin;
  m_x[3] = vyin;
}


void
Body::setMass(double mass)
{
  m_para[0] = mass;
}


double
Body::getMass() const
{
  return m_para[0];
}


const std::array<double, 4>&
Body::getState() const
{
  return m_x;
}


const std::array<double, 2>&
Body::getParameters() const
{
  return m_para;
}


void
Body::integrate(double stepsize)
{
  std::array<double, 4> x0k1;
  std::array<double, 4> x0k2;
  std::array<double, 4> x0k3;

  std::array<double, 4> k1;
  std::array<double, 4> k2;
  std::array<double, 4> k3;
  std::array<double, 4> k4;

  std::array<double, 4> force = m_environment->getStateDerivative(m_x, this);
  for (std::size_t j = 0; j < 4; j++)
  {
    k1[j] = stepsize * force[j];
    x0k1[j] = m_x[j] + 1./2.* k1[j]; // used in next step
  }

  force = m_environment->getStateDerivative(x0k1, this);
  for (std::size_t j = 0; j < 4; j++)
  {
    k2[j] = stepsize * force[j];
    x0k2[j] = m_x[j] + 1./2.* k2[j]; // used in next step
  }

  force = m_environment->getStateDerivative(x0k2, this);
  for (std::size_t j = 0; j < 4; j++)
  {
    k3[j] = stepsize * force[j];
    x0k3[j] = m_x[j] + k3[j]; // used in next step
  }

  force = m_environment->getStateDerivative(x0k3, this);

  for (std::size_t j = 0; j < 4; j++)
  {
    k4[j] = stepsize * force[j];
  }

  for (std::size_t i = 0; i < 4; i++)
  {
    m_x[i] = m_x[i] + 1.0/6.0 * (k1[i]+2*k2[i]+2*k3[i]+k4[i]);
  }
}


void
Body::printPosition() const
{
  double distance = std::sqrt(m_x[0]*m_x[0]+m_x[1]*m_x[1]);
  std::cout << "pos: " << m_x[0] << ", " << m_x[1] << ", distance: " << distance << std::endl;
}

void
Body::printVelocity() const
{
  double speed = std::sqrt(m_x[2]*m_x[2]+m_x[3]*m_x[3]);
  std::cout << "vel: " << m_x[2] << ", " << m_x[3] << ", speed: " << speed << std::endl;
}

unsigned int
Body::getId() const
{
  return m_id;
}


double
Body::random(double start, double end)
{
  double randomDouble = start+(end-start)*rand()/(RAND_MAX + 1.0);
  return randomDouble;
}


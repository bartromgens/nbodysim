#include "environment.h"

#include "body.h"

#include <cmath>

unsigned int Body::ms_nextUniqueId = 1;

Body::Body(Environment* environment, double x, double y, double vx, double vy, double mass, double radius)
: m_id(ms_nextUniqueId++),
  m_x(),
  m_mass(mass),
  m_radius(radius),
  m_environment(environment)
{
  m_x[0] = x;
  m_x[1] = y;
  m_x[2] = vx;
  m_x[3] = vy;
}


Body::~Body()
{
}


void
Body::setPosition(double x, double y)
{
  m_x[0] = x;
  m_x[1] = y;
}


void
Body::setVelocity(double vx, double vy)
{
  m_x[2] = vx;
  m_x[3] = vy;
}


void
Body::setMass(double mass)
{
  m_mass = mass;
}


double
Body::getMass() const
{
  return m_mass;
}


const std::array<double, 4>&
Body::getState() const
{
  return m_x;
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


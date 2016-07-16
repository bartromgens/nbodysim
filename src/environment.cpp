#include "environment.h"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <functional>
#include <thread>


Environment::Environment(double gravitationalConstant)
  : m_gravitationalConstant(gravitationalConstant)
{
}


Environment::~Environment() {
}


void
Environment::addBody(Body* body)
{
//  std::lock_guard<std::mutex> lock(m_mutex);
  m_bodies.push_back(body);
}


void
Environment::removeBody(Body* body)
{
  m_bodies.erase( std::remove(m_bodies.begin(), m_bodies.end(), body), m_bodies.end() );
}


void
Environment::addMasslessBody(Body* body)
{
//  std::lock_guard<std::mutex> lock(m_mutex);
  m_masslessBodies.push_back(body);
}


void
Environment::clearAllBodies()
{
//  std::lock_guard<std::mutex> lock(m_mutex);
  m_bodies.clear();
  m_masslessBodies.clear();
}


void
Environment::oneStep(double tEnd, double stepsize)
{
  oneStepImpl(tEnd, stepsize);
}


//void
//Environment::oneStepThread(double tEnd, double stepsize)
//{
//  std::thread t(&Environment::oneStepImpl, this, tEnd, stepsize);
//  t.detach();
//}


void
Environment::oneStepImpl(double tEnd, double stepsize)
{
//  std::lock_guard<std::mutex> lock(m_mutex);

  double stepsizeAbsolute = std::fabs(stepsize);
  if (stepsizeAbsolute < 1.0e-6)
  {
    std::cerr << "Environment::oneStepImpl() - ERROR: stepsize too small: " << stepsize << std::endl;
    return;
  }

  int steps = tEnd/stepsizeAbsolute;
  assert(steps >= 0);

  for (int i = 0; i < steps; ++i)
  {
    for (std::size_t i = 0; i < m_bodies.size(); i++)
    {
      m_bodies[i]->integrate(stepsize);
    }
    for (std::size_t i = 0; i < m_masslessBodies.size(); i++)
    {
      m_masslessBodies[i]->integrate(stepsize);
    }
  }
}


std::array<double, 4>
Environment::getStateDerivative(const std::array<double, 4>& x, const Body* ignoreBody) const
{
  std::array<double, 4> stateDerivative;
  stateDerivative.fill(0.0);

  for (auto iter = m_bodies.begin(); iter != m_bodies.end(); iter++)
  {
    if (ignoreBody == *iter)
    {
      continue;
    }

    std::array<double, 4> x2 = (*iter)->getState();
    double x12 = x[0]-x2[0];
    double y12 = x[1]-x2[1];
    double r = sqrt(x12*x12+y12*y12);
    if (r > 0.1/std::sqrt(m_gravitationalConstant))
    {
      double mu = (*iter)->getMass() * m_gravitationalConstant;
      double r3 = r*r*r;
      stateDerivative[2] -= mu / r3 * x12;
      stateDerivative[3] -= mu / r3 * y12;
    }
    else
    {
      // TODO: make a better rule
      std::cout << "limit: " << 1.0/std::sqrt(m_gravitationalConstant) << std::endl;
      std::cout << "r: " << r << std::endl;
      assert(false);
    }
  }

  stateDerivative[0] = x[2];
  stateDerivative[1] = x[3];
  return stateDerivative;
}


double
Environment::getFieldStrength(double x, double y)
{
  std::array<double, 4> x2;
  double x12[2];
  double gravityAcc = 0.0;
  double gravityAccX = 0.0;
  double gravityAccY = 0.0;

  for (auto iter = m_bodies.begin(); iter != m_bodies.end(); iter++)
  {
    x2 = (*iter)->getState();
    if (x2[0] != x && x2[1] != y)
    {
      double mass = (*iter)->getMass();
      x12[0] = x-x2[0];
      x12[1] = y-x2[1];
      double r = sqrt(x12[0]*x12[0]+x12[1]*x12[1]);
      if (r > 1)
      {
        gravityAccX += mass/(r*r*r)*x12[0];
        gravityAccY += mass/(r*r*r)*x12[1];
      }
    }
  }

  gravityAcc = sqrt( pow(gravityAccX, 2) + pow(gravityAccY, 2) );
  return gravityAcc;
}


double
Environment::getEnergy()
{
  double energy;
  double kineticEnergy = 0.0;
  double potentialEnergy = 0.0;

  double x12, y12, r12;

  for (auto iter = m_bodies.begin(); iter != m_bodies.end(); iter++)
  {
    std::array<double, 4> x1 = (*iter)->getState();
    double mass_1 = (*iter)->getMass();

    for (auto iter2 = m_bodies.begin(); iter2 != m_bodies.end(); iter2++)
    {
      if (iter2 != iter)
      {
        std::array<double, 4> x2 = (*iter2)->getState();
        x12 = x2[0]-x1[0];
        y12 = x2[1]-x1[1];
        r12 = sqrt(x12*x12+y12*y12);

        double mass_2 = (*iter2)->getMass();
        potentialEnergy -= mass_1*mass_2/r12;
      }
    }
    kineticEnergy += 0.5*mass_1*(x1[2]*x1[2]+x1[3]*x1[3]);
  }

  energy = 2*kineticEnergy + potentialEnergy;
  return energy;
}


double
Environment::getLinearMomentum()
{
  double linearMomentum = 0;

  for (auto iter = m_bodies.begin(); iter != m_bodies.end(); iter++)
  {
    std::array<double, 4> x = (*iter)->getState();
    linearMomentum += (*iter)->getMass() * std::sqrt(x[1]*x[1]+x[2]*x[2]);
  }

  return linearMomentum;
}


double
Environment::getGravitationalConstant() const
{
  return m_gravitationalConstant;
}


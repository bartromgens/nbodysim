#include "environment.h"

#include <cassert>
#include <cmath>
#include <iostream>


int testSolarSystem();
int testBasic();


int main(int /*argc*/, char* /*argv*/[])
{
  std::cout << "main() - START!" << std::endl;
  testBasic();
  testSolarSystem();
  std::cout << "main() - END!" << std::endl;
  return 0;
}


int testBasic()
{
  const double G = 2.0;
  std::unique_ptr<Environment> environment = std::unique_ptr<Environment>(new Environment(G));
  double mass = 100.0;
  Body* bodyA = new Body(environment.get(), 0.0, 0.0, 0.0, 0.0, mass);
  environment->addBody(bodyA);

  double radius = 2.0;
  Body* bodyB = new Body(environment.get(), radius, 0.0, 0.0, std::sqrt(mass*G/radius), 0.0);
  environment->addBody(bodyB);

  double duration = 60.0;
  double stepsize = 0.001;
  environment->oneStep(duration, stepsize);

  bodyA->printPosition();
  bodyB->printPosition();

  const std::array<double, 4>& x = bodyB->getState();
  assert( std::fabs( std::sqrt(x[0]*x[0]+x[1]*x[1]) - radius) < 1.0e-9 );

  delete bodyA;
  delete bodyB;
  return 0;
}

int testSolarSystem()
{
  const double gravitationalConstant = 6.67408e-11;
  std::unique_ptr<Environment> solarSystem = std::unique_ptr<Environment>(new Environment(gravitationalConstant));
  const double sunMass = 1.989e30;
  Body* sun = new Body(solarSystem.get(), 0.0, 0.0, 0.0, 0.0, sunMass);
  solarSystem->addBody(sun);

  const double earthMass = 5.972e24;
  const double muSun = sunMass*gravitationalConstant;
  const double earthEccentricity = 0.0167086;
  double earthApogeeX = 152.10e9;
  double earthApogeeVy = std::sqrt(muSun/earthApogeeX*(1.0-earthEccentricity));
  Body* earth = new Body(solarSystem.get(), earthApogeeX, 0.0, 0.0, earthApogeeVy, earthMass);
  solarSystem->addBody(earth);

  sun->printPosition();
  sun->printVelocity();
  earth->printPosition();
  earth->printVelocity();

  double a = earthApogeeX/(1+earthEccentricity);
  double orbitalPeriod = 2*M_PI*std::sqrt(a*a*a/muSun);
  std::cout << "orbital period: " << orbitalPeriod/60.0/60.0/24.0/365.0 << std::endl;
//  double year_in_seconds = 60*60*24*365;
  double stepsize = 10.0;
  solarSystem->oneStep(orbitalPeriod, stepsize);

  assert( std::fabs(earth->getState()[0] - earthApogeeX) < 10e6);
  assert( std::fabs(earth->getState()[1] - 0.0) < 10e6);

  std::cout << "Earth:" << std::endl;
  earth->printPosition();
  earth->printVelocity();
  std::cout << "Sun:" << std::endl;
  sun->printPosition();
  sun->printVelocity();

  delete earth;
  delete sun;
  return 0;
}

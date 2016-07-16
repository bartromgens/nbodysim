#ifndef BODY_H_
#define BODY_H_

#include <array>
#include <memory>
#include <iostream>
#include <vector>

class Drawable;
class Environment;

class Body
{
public:
  explicit Body(Environment* environment, double x, double y, double vx, double vy, double mass, double radius=1.0);
  ~Body();

  void integrate(double stepsize);

  void setPosition(double x, double y);
  void setVelocity(double vx, double vy);

  const std::array<double, 4>& getState() const;

  void setMass(double mass);
  double getMass() const;



  void printPosition() const;
  void printVelocity() const;

  unsigned int getId() const;

private:
  double random(double start, double end);

private:
  static unsigned int ms_nextUniqueId;
  unsigned int m_id;
  std::array<double, 4> m_x;
  double m_mass;
  double m_radius;

  Environment* m_environment;
};

#endif /* BODY_H_ */

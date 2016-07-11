#include "solarsystemscene.h"

#include "bodyitem.h"

#include "environment.h"

#include <QDebug>
#include <QGraphicsEllipseItem>
#include <QGraphicsSceneMouseEvent>

const double AU = 149.6e9;

namespace
{
  double calcOrbitalVelocity(double apogeeX, double eccentricity, double muCentralBody)
  {
    double apogeeVy = std::sqrt(muCentralBody/apogeeX*(1.0-eccentricity));
    return apogeeVy;
  }
}


SolarSystemScene::SolarSystemScene()
: m_environment(new Environment())
{
  const double sunMass = 1.989e30;
  const double muSun = sunMass*m_environment->getGravitationalConstant();
  Body* sun = new Body(m_environment.get());
  sun->setMass(sunMass);
  sun->setVelocity(0.0, 0.0);
  sun->setPosition(0.0, 0.0);
  addBody(sun);

  Body* earth = new Body(m_environment.get());
  double earthEccentricity = 0.0167086;
  const double earthMass = 5.972e24;
  earth->setMass(earthMass);
  double earthX = 152.10e9;
  double earthVy = calcOrbitalVelocity(earthX, earthEccentricity, muSun);
  earth->setPosition(earthX, 0.0);
  earth->setVelocity(0.0, -earthVy);
  addBody(earth);

  Body* venus = new Body(m_environment.get());
  double venusEccentricity = 0.006772;
  const double venusMass = 4.8675e24;
  venus->setMass(venusMass);
  double venusX = 108.939e9;
  double venusVy = calcOrbitalVelocity(venusX, venusEccentricity, muSun);
  venus->setPosition(venusX, 0.0);
  venus->setVelocity(0.0, -venusVy);
  addBody(venus);

  Body* mercury = new Body(m_environment.get());
  double mercuryEccentricity = 0.205630;
  const double mercuryMass = 3.3011e23;
  mercury->setMass(mercuryMass);
  double mercuryX = 69.81690e9;
  double mercuryVy = calcOrbitalVelocity(mercuryX, mercuryEccentricity, muSun);
  mercury->setPosition(mercuryX, 0.0);
  mercury->setVelocity(0.0, -mercuryVy);
  addBody(mercury);

//  Body* moon = new Body(m_environment.get());
//  moon->setMass(7.34767e22);
//  double moonX = 405.400e6 * 1.0;
//  double moonVy = calcOrbitalVelocity(moonX, eccentricity, muEarth);
//  moon->setPosition(earthX + moonX, 0.0);
//  moon->setVelocity(0.0, earthVy - moonVy);
//  addBody(moon);
}


SolarSystemScene::~SolarSystemScene()
{
  for (auto body : m_bodies)
  {
    delete body;
  }
  m_bodies.clear();
}


void
SolarSystemScene::addBody(Body* body)
{
  m_environment->addBody(body);
  m_bodyItems.push_back(BodyItem(body));
  m_bodies.push_back(body);
}


void
SolarSystemScene::init()
{
  QBrush brush(Qt::black);
  setBackgroundBrush(brush);
  for (const BodyItem& planet : m_bodyItems)
  {
    addItem(planet.getItem());
  }
}


void
SolarSystemScene::step()
{
  double tEnd = 60*60*6.0;
  double stepsize = 60.0;
  m_environment->oneStep(tEnd, stepsize);

  for (BodyItem& planet : m_bodyItems)
  {
    planet.update();
  }
}


void
SolarSystemScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
  qDebug() << event->scenePos();
  QGraphicsScene::mousePressEvent(event);
}


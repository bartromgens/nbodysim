#include "solarsystemscene.h"

#include "bodyitem.h"

#include "environment.h"

#include <QDebug>
#include <QGraphicsEllipseItem>
#include <QGraphicsSceneMouseEvent>


const double AU = 149.6e9;
const double muSun = 1.32712440018e20;

namespace
{
  double calcOrbitalVelocity(double apogeeX, double eccentricity, double muCentralBody)
  {
    double apogeeVy = std::sqrt(muCentralBody/apogeeX*(1.0-eccentricity));
    return apogeeVy;
  }
}


SolarSystemScene::SolarSystemScene()
: m_environment(new Environment()),
  m_newBody(),
  m_tempBodyItem(0),
  m_sunItem(0)
{
  const double sunMass = 1.989e30;
  Body* sun = new Body(m_environment.get());
  sun->setMass(sunMass);
  sun->setVelocity(0.0, 0.0);
  sun->setPosition(0.0, 0.0);
  m_sunItem = addBody(sun, Qt::yellow);

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


BodyItem*
SolarSystemScene::addBody(Body* body, const QColor& color)
{
  m_environment->addBody(body);
  BodyItem* bodyItem = new BodyItem(body, color);
  m_bodyItems.push_back(bodyItem);
  m_bodies.push_back(body);
  addItem(bodyItem->getItem());
  return bodyItem;
}


void
SolarSystemScene::init()
{
  setBackgroundBrush(QBrush(Qt::black));
}


void
SolarSystemScene::step()
{
  double tEnd = 60*60*6.0;
  double stepsize = 30.0;
  m_environment->oneStep(tEnd, stepsize);

  for (BodyItem* planet : m_bodyItems)
  {
    planet->update();
  }

  detectCollision();
}


void
SolarSystemScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
  qDebug() << event->scenePos();

  if (m_newBody)
  {
    Body* body = new Body(m_environment.get());
    body->setMass(m_newBody->m_mass);
    QPointF envPos = BodyItem::sceneToEnv(m_newBody->scenePos);
    QPointF velVect = event->scenePos() - m_newBody->scenePos;
    velVect = velVect * 2.0e2;
    body->setPosition(envPos.x(), envPos.y());
    body->setVelocity(velVect.x(), velVect.y());
    addBody(body, Qt::green);
    removeItem(m_tempBodyItem);
    delete m_tempBodyItem;
    m_tempBodyItem = 0;
    m_newBody.release();
  }
  else
  {
    double mass = 5.0e28;
    double radius = BodyItem::calcRadius(mass);
    m_tempBodyItem = addEllipse(event->scenePos().x()-radius, event->scenePos().y()-radius, 2*radius, 2*radius, QPen(Qt::darkGreen), QBrush(Qt::darkGreen));
    m_newBody.reset(new NewBodyData(mass, event->scenePos()));
  }

  QGraphicsScene::mousePressEvent(event);
}


void
SolarSystemScene::detectCollision()
{
  for (const auto& bodyItem : m_bodyItems)
  {
    if (bodyItem != m_sunItem && bodyItem->getItem()->collidesWithItem(m_sunItem->getItem()))
    {
      std::cout << "COLLISION" << std::endl;
      removeBodyItem(bodyItem);
    }
  }
}


void
SolarSystemScene::removeBodyItem(BodyItem* bodyItem)
{
  m_bodyItems.erase( std::remove(m_bodyItems.begin(), m_bodyItems.end(), bodyItem), m_bodyItems.end() );
  removeItem(bodyItem->getItem());
  for (const auto& body : m_bodies)
  {
    if (body == bodyItem->getBody())
    {
      m_environment->removeBody(body);
      break;
    }
  }
}

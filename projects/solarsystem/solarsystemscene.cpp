#include "solarsystemscene.h"

#include "bodyitem.h"

#include "environment.h"

#include <QDebug>
#include <QGraphicsEllipseItem>
#include <QGraphicsSceneMouseEvent>

const double AU = 149.6e9;


SolarSystemScene::SolarSystemScene()
: m_environment(new Environment())
{
  Body* earth = new Body(m_environment.get());
  earth->setMass(5.972e24);
  earth->setVelocity(0.0, -29294.7);
  earth->setPosition(152.10e9, 0.0);
  addBody(earth);

  Body* sun = new Body(m_environment.get());
  sun->setMass(1.989e30);
  sun->setVelocity(0, 0);
  sun->setPosition(0, 0);
  addBody(sun);
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
  for (const BodyItem& planet : m_bodyItems)
  {
    addItem(planet.getItem());
  }
}


void
SolarSystemScene::step()
{
  double tEnd = 60*60*24;
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


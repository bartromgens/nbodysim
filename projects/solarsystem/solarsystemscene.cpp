#include "solarsystemscene.h"

#include "bodyitem.h"

#include "environment.h"

#include <QDebug>
#include <QGraphicsEllipseItem>
#include <QGraphicsSceneMouseEvent>

const double AU = 149.6e9;


SolarSystemScene::SolarSystemScene()
: m_environment(new Environment()),
  m_sun(new Body(m_environment.get())),
  m_sunItem(0)
{
  Body* earthBody = new Body(m_environment.get());  // TODO: delete
  earthBody->setMass(5.972e24);
  earthBody->setVelocity(0.0, -29294.7);
  earthBody->setPosition(152.10e9, 0.0);
  m_environment->addBody(earthBody);
  m_planets.push_back(BodyItem(earthBody));

  m_sun->setMass(1.989e30);
  m_sun->setPosition(0, 0);
  m_sun->setVelocity(0, 0);
}


SolarSystemScene::~SolarSystemScene()
{
}


void
SolarSystemScene::init()
{
  m_environment->addBody(m_sun.get());
  m_sunItem = addEllipse(500, 500, 20, 20);

  for (const BodyItem& planet : m_planets)
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

  for (BodyItem& planet : m_planets)
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


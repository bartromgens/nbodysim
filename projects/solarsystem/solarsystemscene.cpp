#include "solarsystemscene.h"

#include "environment.h"

#include <QDebug>
#include <QGraphicsEllipseItem>
#include <QGraphicsSceneMouseEvent>

const double AU = 149.6e9;


SolarSystemScene::SolarSystemScene()
: m_environment(new Environment()),
  m_sun(new Body(m_environment.get())),
  m_earth(new Body(m_environment.get())),
  m_sunItem(0),
  m_earthItem(0)
{
  m_sun->setMass(1.989e30);
  m_sun->setPosition(0, 0);
  m_sun->setVelocity(0, 0);
  m_earth->setMass(5.972e24);
  m_earth->setPosition(152.10e9, 0.0);
  m_earth->setVelocity(0.0, -29294.7);
}


SolarSystemScene::~SolarSystemScene()
{
}


void
SolarSystemScene::init()
{
  m_environment->addBody(m_sun.get());
  m_environment->addBody(m_earth.get());
  m_sunItem = addEllipse(500, 500, 20, 20);
  m_earthItem = addEllipse(20, 10, 10, 10);
}


void
SolarSystemScene::step()
{
  double tEnd = 60*60*24;
  double stepsize = 60.0;
  m_environment->oneStep(tEnd, stepsize);
  double xEarth = m_earth->getState()[0]/AU * 500 + 500;
  double yEarth = m_earth->getState()[1]/AU * 500 + 500;
//  std::cout << xEarth << ", " << yEarth << std::endl;
  m_earthItem->setPos(xEarth, yEarth);
}


void
SolarSystemScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
  qDebug() << event->scenePos();
  QGraphicsScene::mousePressEvent(event);
}


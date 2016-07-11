#include "bodyitem.h"

#include "body.h"

#include <QGraphicsEllipseItem>
#include <QPen>


const double AU = 149.6e9;
const double earthMass = 5.972e24;

BodyItem::BodyItem(Body* body)
: m_body(body),
  m_item(0),
  m_radius(1.0)
{
  m_radius = std::pow(body->getMass(), 1/6.0) / std::pow(earthMass, 1/6.0) * 3.0;
  std::cout << "radius: " << m_radius << std::endl;
  m_item = new QGraphicsEllipseItem(20, 10, 2*m_radius, 2*m_radius);
  m_item->setPen(QPen(Qt::white));
  m_item->setBrush(QBrush(Qt::white));
}


QGraphicsEllipseItem*
BodyItem::getItem() const
{
  return m_item;
}


unsigned int
BodyItem::getRadius() const
{
  return m_body->getMass();
}


void
BodyItem::update()
{
  const std::array<double, 4> state = m_body->getState();
  double x = state[0]/AU * 400 + 400 - m_radius;
  double y = state[1]/AU * 400 + 400 - m_radius;
  m_item->setPos(x, y);  // -y due to Qt coordinate system
}


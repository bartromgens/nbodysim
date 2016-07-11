#include "bodyitem.h"

#include "body.h"

#include <QGraphicsEllipseItem>


const double AU = 149.6e9;

BodyItem::BodyItem(Body* body)
: m_body(body)
{
  m_item = new QGraphicsEllipseItem(20, 10, 10, 10);
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
  double x = state[0]/AU * 500 + 500;
  double y = state[1]/AU * 500 + 500;;
  m_item->setPos(x, y);
}


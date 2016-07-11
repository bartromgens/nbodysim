#ifndef BODYITEM_H
#define BODYITEM_H

#include <memory>

class Body;
class QGraphicsEllipseItem;


class BodyItem
{
public:
  BodyItem(Body* body);

  void update();
  QGraphicsEllipseItem* getItem() const;
  unsigned int getRadius() const;

private:

private:
  std::unique_ptr<Body> m_body;
  QGraphicsEllipseItem* m_item;
  double m_radius;
};

#endif // BODYITEM_H

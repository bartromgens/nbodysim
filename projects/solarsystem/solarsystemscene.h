#ifndef SOLARSYSTEMSCENE_H
#define SOLARSYSTEMSCENE_H

#include <QGraphicsScene>

#include <memory>

class Environment;
class Body;
class BodyItem;

class SolarSystemScene : public QGraphicsScene
{
public:
  struct NewBodyData
  {
  public:
    NewBodyData(double mass, const QPointF& scenePos)
      : m_mass(mass), scenePos(scenePos) {}
    double m_mass;
    QPointF scenePos;
  };

public:
  explicit SolarSystemScene();
  virtual ~SolarSystemScene();

  void init();
  void step();

protected:
  void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

private:
  void addBody(Body* body, const QColor& color=Qt::white);

private:
  std::unique_ptr<Environment> m_environment;
  std::vector<BodyItem*> m_bodyItems;
  std::vector<Body*> m_bodies;
  std::unique_ptr<NewBodyData> m_newBody;
  QGraphicsEllipseItem* m_tempBodyItem;
};

#endif // SOLARSYSTEMSCENE_H

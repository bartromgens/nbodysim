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
  explicit SolarSystemScene();
  virtual ~SolarSystemScene();

  void init();
  void step();

protected:
  void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

private:
  void addBody(Body* body);

private:
  std::unique_ptr<Environment> m_environment;
  std::vector<BodyItem> m_bodyItems;
  std::vector<Body*> m_bodies;
};

#endif // SOLARSYSTEMSCENE_H

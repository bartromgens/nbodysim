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
  std::unique_ptr<Environment> m_environment;
  std::unique_ptr<Body> m_sun;
  QGraphicsEllipseItem* m_sunItem;
  std::vector<BodyItem> m_planets;
};

#endif // SOLARSYSTEMSCENE_H

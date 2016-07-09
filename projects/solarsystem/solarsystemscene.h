#ifndef SOLARSYSTEMSCENE_H
#define SOLARSYSTEMSCENE_H

#include <QGraphicsScene>

#include <memory>

class Environment;
class Body;


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
  std::unique_ptr<Body> m_earth;
  QGraphicsEllipseItem* m_sunItem;
  QGraphicsEllipseItem* m_earthItem;
};

#endif // SOLARSYSTEMSCENE_H

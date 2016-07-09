#include "mainwindow.h"
#include "solarsystemscene.h"

#include <QGraphicsView>


MainWindow::MainWindow(QWidget *parent)
: QMainWindow(parent),
  m_view(new QGraphicsView()),
  m_scene(new SolarSystemScene())
{
  m_view->setScene(m_scene);
  setCentralWidget(m_view);

  m_scene->init();

  m_view->setSceneRect(QRectF(0,0,1000,800));

  m_scene->step();
}

MainWindow::~MainWindow()
{

}

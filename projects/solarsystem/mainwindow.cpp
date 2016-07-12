#include "mainwindow.h"
#include "solarsystemscene.h"

#include <QGraphicsView>
#include <QTimer>
#include <QTime>

#include <iostream>


MainWindow::MainWindow(QWidget *parent)
: QMainWindow(parent),
  m_timer(new QTimer(this)),
  m_view(new QGraphicsView()),
  m_scene(new SolarSystemScene())
{
  m_view->setScene(m_scene);
  m_view->setSceneRect(QRectF(0, 0, 1000, 800));
  m_view->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

  m_scene->init();

  setCentralWidget(m_view);

  connect(m_timer, SIGNAL(timeout()), this, SLOT(step()));
  m_timer->start(1000/80);
}


MainWindow::~MainWindow()
{
}


void
MainWindow::step()
{
//  QTime timer;
//  timer.start();
  m_scene->step();
//  std::cout << "step time: " << timer.elapsed() << std::endl;
}

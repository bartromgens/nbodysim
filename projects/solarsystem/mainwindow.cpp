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
  setCentralWidget(m_view);

  m_scene->init();

  m_view->setSceneRect(QRectF(0,0,1000,1000));

  connect(m_timer, SIGNAL(timeout()), this, SLOT(step()));
  m_timer->start(1000/60);
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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QGraphicsView;
class QTimer;

class SolarSystemScene;


class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = 0);
  ~MainWindow();

private slots:
  void step();

private:
  QTimer* m_timer;
  QGraphicsView* m_view;
  SolarSystemScene* m_scene;
};

#endif // MAINWINDOW_H

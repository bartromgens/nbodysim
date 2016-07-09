#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class SolarSystemScene;
class QGraphicsView;


class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = 0);
  ~MainWindow();

private:
  QGraphicsView* m_view;
  SolarSystemScene* m_scene;
};

#endif // MAINWINDOW_H

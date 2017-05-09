#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gamefield.h"
#include <thread>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_generateButton_clicked();
    void on_visualizeButton_clicked();
    void timerGenerateField();
    void timerMoveAnt();

private:
    Ui::MainWindow *ui;
    GameField* gameField;
    int visualizedSteps;
    int sliderValue;
    QImage image;
    bool stopVis;

    void drawPoint(QPainter& p, int fieldX, int fieldY, QBrush color);
    void drawField(QPixmap& image, Cell** cells, Direction antDirection);
    void testGen();
};

#endif // MAINWINDOW_H

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "gamefield.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QImage image(":/img/res/grid.jpg");
    QPixmap pm = QPixmap::fromImage(image);
    QGraphicsScene* scene = new QGraphicsScene(this);


    QPainter p(&pm);
    p.setRenderHint(QPainter::Antialiasing, true);

    GameField gameField(0, 0);


    for (int i = 0; i < 200; i++) gameField.updateField();


    Cell** cells = gameField.getCells();

    for (int i = 0; i < FIELD_SIZE; i++){
        for (int j = 0; j < FIELD_SIZE; j++){
            QBrush color;
            if (cells[i][j] == APPLE) color = Qt::black;
            else if (cells[i][j] == APPLEWAY) color = Qt::gray;
            else continue;
            drawPoint(p, j, i, color);
        }
    }


    scene->addPixmap(pm);
    scene->setSceneRect(pm.rect());
    ui->graphicsView->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::drawPoint(QPainter& p, int fieldX, int fieldY, QBrush color)
{
    QPen pen(color, 1);
    p.setPen(pen);
    QBrush brush(color);
    p.setBrush(brush);

    int x = 20 * fieldX + 6;
    int y = 20 * fieldY + 6;
    p.drawRect(x, y, 10, 10);
}

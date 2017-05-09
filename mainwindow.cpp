#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->visualizeButton->setEnabled(false);
    image = QImage(":/img/res/grid.jpg");
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

void MainWindow::drawField(QPixmap& image, Cell** cells, Direction antDirection)
{
    QGraphicsScene* scene = new QGraphicsScene(this);
    QPainter p(&image);
    p.setRenderHint(QPainter::Antialiasing, true);

    for (int i = 0; i < FIELD_SIZE; i++){
        for (int j = 0; j < FIELD_SIZE; j++){
            if (cells[i][j] == APPLE) {
                drawPoint(p, j, i, Qt::black);
            }
            else if (cells[i][j] == APPLEWAY) {
                drawPoint(p, j, i, Qt::gray);
            }
            else if (cells[i][j] == PASSED){
                QImage antImg;
                switch (antDirection){
                    case WEST: antImg = QImage(":/img/res/ant_east.png"); break;
                    case EAST: antImg = QImage(":/img/res/ant_west.png"); break;
                    case SOUTH: antImg = QImage(":/img/res/ant_south.png"); break;
                    default: antImg = QImage(":/img/res/ant_north.png"); break;
                }
                QPixmap antPm = QPixmap::fromImage(antImg);
                int x = 20 * j + 2;
                int y = 20 * i + 2;
                p.drawPixmap(x, y, 20, 20, antPm);
            }
        }
    }

    scene->addPixmap(image);
    scene->setSceneRect(image.rect());
    ui->graphicsView->setScene(scene);
}

void MainWindow::on_generateButton_clicked()
{
    ui->generateButton->setText("Generating...");
    ui->generateButton->setEnabled(false);
    ui->visualizeButton->setEnabled(false);
    QTimer::singleShot(100, this, SLOT(timerGenerateField()));
}

void MainWindow::on_visualizeButton_clicked()
{
    qDebug() << visualizedSteps;

    if (stopVis){
        ui->generateButton->setEnabled(false);
        ui->visualizeButton->setText("Stop");
        QTimer::singleShot(500, this, SLOT(timerMoveAnt()));
        stopVis = false;
    }
    else {
        ui->generateButton->setEnabled(true);
        ui->visualizeButton->setText("Resume");
        stopVis = true;
    }
}

void MainWindow::timerGenerateField()
{
    visualizedSteps = 0;
    stopVis = true;
    gameField = new GameField(0, 0);
    ui->generateButton->setText("Regenerate");
    ui->visualizeButton->setText("Visualize");
    ui->generateButton->setEnabled(true);
    ui->visualizeButton->setEnabled(true);
    ui->scoreLabel->setText(QString("Steps: 0\n\nApples: 0"));
}

void MainWindow::timerMoveAnt()
{
    // Stop pressed
    if (stopVis) return;

    QPixmap pm = QPixmap::fromImage(image);
    gameField->updateField();
    Cell** cells = gameField->getCells();
    drawField(pm, cells, gameField->getAntDirection());

    visualizedSteps++;

    int eatenApples = APPLES_COUNT - gameField->applesCount();
    QString str;
    str.sprintf("Steps: %d\n\nApples: %d", visualizedSteps, eatenApples);
    ui->scoreLabel->setText(str);

    if (visualizedSteps >= 200){
        ui->visualizeButton->setText("End reached");
        ui->visualizeButton->setEnabled(false);
        ui->generateButton->setEnabled(true);
        return;
    }
    else if (ui->horizontalSlider->value() != sliderValue){
        sliderValue = ui->horizontalSlider->value();
    }
    int interval = 200 + (100 - sliderValue) * 10;

    QTimer::singleShot(interval, this, SLOT(timerMoveAnt()));
}




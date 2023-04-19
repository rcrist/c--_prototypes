#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    // Set default outline pen color and width
    outlinePen.setColor(Qt::red);       // Set border color
    outlinePen.setWidth(2);             // Set border width

//    // Add test shapes
//    blueBrush = *new QBrush(Qt::blue);  // Set fill color
//    rectangle = scene->addRect(80, 30, 80, 150, outlinePen, blueBrush);
//    rectangle->setFlag(QGraphicsItem::ItemIsMovable);
//    rectangle->setFlag(QGraphicsItem::ItemIsSelectable);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_rectButton_clicked()
{
    // Add rectangle
    rectangle = scene->addRect(80, 30, 80, 150, outlinePen, QBrush(Qt::blue));
    rectangle->setFlag(QGraphicsItem::ItemIsMovable);
    rectangle->setFlag(QGraphicsItem::ItemIsSelectable);
}

void MainWindow::on_ovalButton_clicked()
{
    // Add ellipse (oval)
    ellipse = scene->addEllipse(280, 30, 80, 150, outlinePen, QBrush(Qt::yellow));
    ellipse->setFlag(QGraphicsItem::ItemIsMovable);
    ellipse->setFlag(QGraphicsItem::ItemIsSelectable);
}


void MainWindow::on_triangleButton_clicked()
{
    // Add triangle
    points << QPointF(50,100) << QPointF(100,25) << QPointF(150,100); //[50,100,100,25,150,100];
    triangle = scene->addPolygon(points, outlinePen, QBrush(Qt::green));
    triangle->setFlag(QGraphicsItem::ItemIsMovable);
    triangle->setFlag(QGraphicsItem::ItemIsSelectable);
}


void MainWindow::on_lineButton_clicked()
{
    // Add line
    line = scene->addLine(80, 30, 140, 150, outlinePen);
    line->setFlag(QGraphicsItem::ItemIsMovable);
    line->setFlag(QGraphicsItem::ItemIsSelectable);
}


void MainWindow::on_fillColorButton_clicked()
{
    QColor color = QColorDialog::getColor(QColor(Qt::white));
    QVariant variant = color;
    QString colcode = variant.toString();
    ui->fillColorLabel->setStyleSheet("QLabel { background-color :"+colcode+" }");

    foreach (QGraphicsItem *item, scene->selectedItems()) {
        QGraphicsRectItem *rect = qgraphicsitem_cast<QGraphicsRectItem *>(item);
        if (rect)
        {
            rect->setBrush(color);
            rect->update();
        }

        QGraphicsEllipseItem *oval = qgraphicsitem_cast<QGraphicsEllipseItem *>(item);
        if (oval)
        {
            oval->setBrush(color);
            oval->update();
        }

        QGraphicsPolygonItem *tri = qgraphicsitem_cast<QGraphicsPolygonItem *>(item);
        if (tri)
        {
            tri->setBrush(color);
            tri->update();
        }
    }
}

void MainWindow::on_borderColorButton_clicked()
{
    QColor color = QColorDialog::getColor(QColor(Qt::white));
    QVariant variant = color;
    QString colcode = variant.toString();
    ui->borderColorLabel->setStyleSheet("QLabel { background-color :"+colcode+" }");

    outlinePen.setColor(color);

    foreach (QGraphicsItem *item, scene->selectedItems()) {
        QGraphicsRectItem *rect = qgraphicsitem_cast<QGraphicsRectItem *>(item);
        if (rect)
        {
            rect->setPen(outlinePen);
            rect->update();
        }

        QGraphicsEllipseItem *oval = qgraphicsitem_cast<QGraphicsEllipseItem *>(item);
        if (oval)
        {
            oval->setPen(outlinePen);
            oval->update();
        }

        QGraphicsPolygonItem *tri = qgraphicsitem_cast<QGraphicsPolygonItem *>(item);
        if (tri)
        {
            tri->setPen(outlinePen);
            tri->update();
        }

        QGraphicsLineItem *line = qgraphicsitem_cast<QGraphicsLineItem *>(item);
        if (line)
        {
            line->setPen(outlinePen);
            line->update();
        }
    }
}


void MainWindow::on_borderWidthButton_clicked()
{
    int width = ui->spinBox->value();
//    qDebug() << "Spinbox value: " << width << "\n";
    outlinePen.setWidth(width);

    foreach (QGraphicsItem *item, scene->selectedItems()) {
        QGraphicsRectItem *rect = qgraphicsitem_cast<QGraphicsRectItem *>(item);
        if (rect)
        {
            rect->setPen(outlinePen);
            rect->update();
        }

        QGraphicsEllipseItem *oval = qgraphicsitem_cast<QGraphicsEllipseItem *>(item);
        if (oval)
        {
            oval->setPen(outlinePen);
            oval->update();
        }

        QGraphicsPolygonItem *tri = qgraphicsitem_cast<QGraphicsPolygonItem *>(item);
        if (tri)
        {
            tri->setPen(outlinePen);
            tri->update();
        }

        QGraphicsLineItem *line = qgraphicsitem_cast<QGraphicsLineItem *>(item);
        if (line)
        {
            line->setPen(outlinePen);
            line->update();
        }
    }
}


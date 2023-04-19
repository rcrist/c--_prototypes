#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QColorDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_rectButton_clicked();
    void on_ovalButton_clicked();
    void on_triangleButton_clicked();
    void on_lineButton_clicked();

    void on_fillColorButton_clicked();

    void on_borderColorButton_clicked();

    void on_borderWidthButton_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsEllipseItem *ellipse;
    QGraphicsRectItem *rectangle;
    QGraphicsTextItem *text;
    QGraphicsPolygonItem *triangle;
    QGraphicsLineItem *line;
    QPolygonF points;

    QBrush greenBrush;
    QBrush blueBrush;
    QBrush yellowBrush;
    QPen outlinePen;
};
#endif // MAINWINDOW_H

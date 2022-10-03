#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QHash>
#include <functional>
#include <QGraphicsItem>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class ItemEventFilter : public QGraphicsItem
{
public:
    QRectF boundingRect() const override;
    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget* = 0) override;
protected:
    bool sceneEventFilter(QGraphicsItem* object, QEvent* event) override;
private:
    bool move(QGraphicsItem* object, QEvent* event);
    bool rotate(QGraphicsItem *watched, QEvent *event);
private:
    bool canMove = false;
    bool canRotate = false;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    enum Figure { RECTANGLE, ELLIPS,STAR };
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool eventFilter(QObject* object, QEvent* event) override;
private:
    QRectF Get_Rect(qint32 x, qint32 y) const;
    QRectF Get_Ellipse(qint32 x, qint32 y) const;
    QPolygonF Get_Star(qint32 x, qint32 y) const;
    Figure Get_Figure_Type() const;
    QPen Get_Pen() const;
    QBrush Get_Brash() const;
    void Create_Figure(int x, int y);

private:
    Ui::MainWindow *ui;
    QGraphicsScene* scene;
    QGraphicsView view;
    qint8 FigureIndex;
    QHash <qint32, std::function<void(int,int)>> Figures_makers;
};
#endif // MAINWINDOW_H

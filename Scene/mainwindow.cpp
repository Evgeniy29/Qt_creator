#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>
#include <QRandomGenerator>
#include <QGraphicsSceneMouseEvent>
#include <QtMath>

namespace
{
    constexpr qreal ellipse_d1 = 100.;
    constexpr qreal ellipse_d2 = 50.;
    constexpr qreal rect_width = 100.;
    constexpr qreal rect_heigh = 50.;
    constexpr qreal star_size = 80.;
    constexpr qint32 max_color_value = std::numeric_limits<uint8_t>::max();
    constexpr qint32 count = 3;
    constexpr qreal scale_step = 0.1;
}

QRectF ItemEventFilter::boundingRect() const
{
    return {};
}

void ItemEventFilter::paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*)
{

}

bool ItemEventFilter::sceneEventFilter(QGraphicsItem* object, QEvent* event)
{
    if (move(object, event))
    {
        return true;
    }
    return rotate(object, event);
}

bool ItemEventFilter::move(QGraphicsItem* object, QEvent *event)
{
    if (event->type() == QEvent::GraphicsSceneMouseMove)
    {
        auto moveEvent = static_cast<QGraphicsSceneMouseEvent*>(event);
        if (canMove)
        {
            auto delta = moveEvent->scenePos() - moveEvent->lastScenePos();
            object->moveBy(delta.x(), delta.y());
            return true;
        }
    }
    if (event->type() == QEvent::GraphicsSceneMousePress)
    {
        auto pressEvent = static_cast<QGraphicsSceneMouseEvent*>(event);
        if (pressEvent->button() == Qt::LeftButton)
        {
            canMove = true;
            return true;
        }
    }
    if (event->type() == QEvent::GraphicsSceneMouseRelease)
    {
        auto pressEvent = static_cast<QGraphicsSceneMouseEvent*>(event);
        if (pressEvent->button() == Qt::LeftButton)
        {
            canMove = false;
            return true;
        }
    }
    return false;
}

bool ItemEventFilter::rotate(QGraphicsItem* object, QEvent* event)
{
    if (event->type() == QEvent::GraphicsSceneMouseMove)
    {
        auto moveEvent = static_cast<QGraphicsSceneMouseEvent*>(event);
        if (canRotate)
        {
            QTransform transform;
            auto mousePos = moveEvent->pos().toPoint();
            auto center = object->boundingRect().center();
            double angle = mousePos.x() - center.x();
            transform.translate(center.x(), center.y()).rotate(angle).translate(-center.x(), -center.y());
            object->setTransform(transform);
            return true;
        }
    }
    if (event->type() == QEvent::GraphicsSceneMousePress)
    {
        auto pressEvent = static_cast<QGraphicsSceneMouseEvent*>(event);
        if (pressEvent->button() == Qt::LeftButton)
        {
            canRotate = true;
            return true;
        }
    }
    if (event->type() == QEvent::GraphicsSceneMouseRelease)
    {
        auto pressEvent = static_cast<QGraphicsSceneMouseEvent*>(event);
        if (pressEvent->button() == Qt::LeftButton)
        {
            canRotate = false;
            return true;
        }
    }
    return false;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}
    , ui{new Ui::MainWindow}
    , FigureIndex{0}
{
    ui->setupUi(this);

    scene = new QGraphicsScene(0, 0, rect().width(), rect().height());

    view.setScene(scene);
    auto filter = new ItemEventFilter{};
    scene->addItem(filter);

    view.setAlignment(Qt::AlignTop | Qt::AlignLeft);
    view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setRenderHint(QPainter::Antialiasing);
    view.installEventFilter(this);
    view.setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    ui->graphicsLayout->addWidget(&view);


    Figures_makers.insert(Figure::RECTANGLE, [this, filter](int x, int y)
    {
        auto item = scene->addRect(Get_Rect(x, y), Get_Pen(), Get_Brash());
        item->installSceneEventFilter(filter);
    });

    Figures_makers.insert(Figure::ELLIPS, [this, filter](int x, int y)
    {
        auto item = scene->addEllipse(Get_Ellipse(x, y), Get_Pen(), Get_Brash());
        item->installSceneEventFilter(filter);
    });

    Figures_makers.insert(Figure::STAR, [this, filter](int x, int y)
    {
        auto item = scene->addPolygon(Get_Star(x, y), Get_Pen(), Get_Brash());
        item->installSceneEventFilter(filter);
    });

}

MainWindow::~MainWindow()
{
    delete ui;
}


bool MainWindow::eventFilter(QObject* object, QEvent* event)
{
    if (object != &view)
    {
        return false;
    }

    if (event->type() == QEvent::MouseButtonPress)
    {
        auto mouseEvent = static_cast<QMouseEvent*>(event);
        if (mouseEvent->button() == Qt::LeftButton)
        {
            Create_Figure(mouseEvent->x(), mouseEvent->y());
            return true;
        }
        else if (mouseEvent->button() == Qt::RightButton)
        {
            auto figure = scene->itemAt(view.mapToScene(mouseEvent->x(), mouseEvent->y()), QTransform{});
            if (figure)
            {
                scene->removeItem(figure);
                return true;
            }
        }
    }
    else if (event->type() == QEvent::Wheel)
    {
        auto weelEvent = static_cast<QWheelEvent*>(event);
        qreal scale = 1.0 + (weelEvent->angleDelta().y() > 0 ? scale_step : -scale_step);
        view.scale(scale, scale);
        return true;
    }
    else if (event->type() == QEvent::KeyPress)
    {
        auto key = static_cast<QKeyEvent*>(event)->key();
        if (key == Qt::Key_Plus || key == Qt::Key_Minus)
        {
            double scale = 1.0 + (key == Qt::Key_Plus ? scale_step : -scale_step);
            view.scale(scale, scale);
            return true;
        }
    }
    return false;
}

QRectF MainWindow::Get_Rect(qint32 x, qint32 y) const
{
    QPointF point = view.mapToScene(x, y);
    QPointF left_top{ point.x() - rect_width / 2, point.y() - rect_heigh / 2 };
    return QRectF{ left_top, QPointF{ left_top.x() + rect_width, left_top.y() + rect_heigh} };
}

QRectF MainWindow::Get_Ellipse(qint32 x, qint32 y) const
{
    QPointF point = view.mapToScene(x, y);
    QPointF left_top{ point.x() - ellipse_d1 / 2, point.y() - ellipse_d2 / 2 };
    return QRectF{ left_top, QPointF{ left_top.x() + ellipse_d1, left_top.y() + ellipse_d2 } };
}

QPolygonF MainWindow::Get_Star(qint32 x, qint32 y) const
{
    QPolygonF polygon{};
    QPointF point = view.mapToScene(x, y);
    polygon << QPointF{ point.x(), point.y() - star_size / 2 }
            << QPointF{ point.x() - star_size / 9, point.y() - star_size / 9 }
            << QPointF{ point.x() - star_size / 2, point.y() - star_size / 9 }
            << QPointF{ point.x() - star_size / 5, point.y() + star_size / 9 }
            << QPointF{ point.x() - star_size / 3, point.y() + star_size / 2 }
            << QPointF{ point.x(), point.y() + star_size / 6 }
            << QPointF{ point.x() + star_size / 3, point.y() + star_size / 2 }
            << QPointF{ point.x() + star_size / 5, point.y() + star_size / 8 }
            << QPointF{ point.x() + star_size / 2, point.y() - star_size / 9 }
            << QPointF{ point.x() + star_size / 9, point.y() - star_size / 9 };
    return polygon;
}

MainWindow::Figure MainWindow::Get_Figure_Type() const
{
    return static_cast<Figure>(FigureIndex);
}

QPen MainWindow::Get_Pen() const
{
    return QPen{Qt::NoPen};
}

QBrush MainWindow::Get_Brash() const
{
    return QBrush{QColor{QRandomGenerator::global()->bounded(max_color_value),
        QRandomGenerator::global()->bounded(max_color_value),
        QRandomGenerator::global()->bounded(max_color_value)}};
}

void MainWindow::Create_Figure(int x, int y)
{
    Figure type = Get_Figure_Type();
    FigureIndex++;
    if(FigureIndex == count)
    {
        FigureIndex = 0;
    }

    if (auto it = Figures_makers.find(type); it != Figures_makers.end())
    {
        it.value()(x, y);
    }
}

#ifndef GRAPHVIEW_H
#define GRAPHVIEW_H

#define point_R     10
#define edge_width  3
#define Line_cnt    20

#include <QMainWindow>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QWidget>
#include <QPainter>
#include <map>

#include "amtr_line_1.h"

using namespace std;

namespace Ui
{
class GraphView;
}

class GraphView : public QWidget
{
    Q_OBJECT

public:
    explicit GraphView(QWidget *parent = 0);
    ~GraphView();

    QList<QPoint> Station_Pos;
    QList<QString> Station_name;

    QList<int> Line;
    QList<int> Path_id;

    multimap<int, pair<int, int> > Edge;
protected:
    void paintEvent(QPaintEvent* event);

    // remake mouse_event
    int m_currentID;
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    const QColor LineColor[Line_cnt + 1] = {QColor(0, 0, 0, 0),
                                            QColor(155, 155, 0, 200), QColor(155, 0, 155, 200), QColor(0, 155, 155, 200), QColor(155, 155, 155, 200),
                                            QColor(255, 0, 0, 200), QColor(0, 255, 0, 200), QColor(0, 0, 255, 200), QColor(200, 100, 0, 200),
                                            QColor(200, 0, 100, 200), QColor(0, 200, 100, 200), QColor(100, 200, 0, 200), QColor(100, 0, 200, 200),
                                            QColor(0, 100, 200, 200), QColor(100, 100, 200, 200), QColor(100, 200, 100, 200), QColor(200, 100, 100 ,200),
                                            QColor(50, 100, 150, 200), QColor(150, 50, 100, 200), QColor(50, 150, 100, 200), QColor(100, 150, 50, 200)};
};

#endif // GRAPHVIEW_H

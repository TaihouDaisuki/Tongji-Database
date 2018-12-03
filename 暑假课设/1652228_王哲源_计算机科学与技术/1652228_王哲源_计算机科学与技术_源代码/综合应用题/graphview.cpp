#include "graphview.h"

#include <string>

using namespace std;

GraphView::GraphView(QWidget *parent) :
    QWidget(parent)
{
    Station_name.clear();
    Station_Pos.clear();

    Path_id.clear();
    Line.clear();

    Edge.clear();
    setAttribute(Qt::WA_DeleteOnClose);  //关闭时自动释放内存
}
GraphView::~GraphView()
{

}

void GraphView::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    if(Station_name.size() == 0)
        return;

    //----------draw node----------
    for(int i = 0; i < Station_name.size(); ++i)
    {
        QPoint p(Station_Pos[i]);
        painter.setBrush(QBrush(QColor(30, 100, 130, 160)));
        painter.setPen(QPen(QColor(255, 255, 255, 0)));
        painter.drawEllipse(p, point_R, point_R);

        QPen pen(QColor(54, 52, 51));
        pen.setWidth(4);
        painter.setPen(pen);
        painter.setFont(QFont("Consolas", 9));
        QPoint n(p.x() - 10, p.y());
        painter.drawText(n, Station_name[i]);
    }

    //----------draw edge----------
    int preu = -1, prev = -1;
    int delta = -2;
    for(multimap<int, pair<int, int> >::const_iterator i = Edge.begin(); i != Edge.end(); ++i)
    {
        int u = i->first, v = i->second.first;
        if(u == preu && v == prev)
            delta += edge_width + 1;
        else
            delta = -2;
        preu = u; prev = v;

        QPoint uP(Station_Pos[u - 1]);
        QPoint vP(Station_Pos[v - 1]);
        uP.setY(uP.y() + delta);
        vP.setY(vP.y() + delta);

        QPen pen(LineColor[i->second.second]);
        pen.setWidth(edge_width);
        painter.setPen(pen);
        painter.drawLine(uP, vP);
    }

    //----------draw path----------
    if(!Path_id.size())
        return;
    QPoint p(Station_Pos[Path_id[0] - 1]);
    painter.setBrush(QBrush(QColor(30, 200, 50, 160)));
    painter.setPen(QPen(QColor(255, 255, 255, 0)));
    painter.drawEllipse(p, point_R + 3, point_R + 3);
    for(int i = 1; i < Path_id.size(); ++i)
    {
        p = QPoint(Station_Pos[Path_id[i] - 1]);
        painter.setBrush(QBrush(QColor(1, 187, 1, 160)));
        painter.setPen(QPen(QColor(255, 255, 255, 0)));
        painter.drawEllipse(p, point_R + 3, point_R + 3);

        QPoint S(Station_Pos[Path_id[i - 1] - 1]), T(Station_Pos[Path_id[i] - 1]);
        QPen pen(QColor(255, 120, 100, 255));
        pen.setWidth(5);
        painter.setPen(pen);
        painter.drawLine(S, T);
    }
}

void GraphView::mousePressEvent(QMouseEvent *event)
{
    QPoint pos = event->pos();
    m_currentID = -1;

    for(int i = 0; i < Station_Pos.size(); ++i)
    {
        int dx = pos.x() - Station_Pos[i].x();
        int dy = pos.y() - Station_Pos[i].y();

        int dist = dx * dx + dy * dy;
        if(dist < point_R * point_R)
        {
            m_currentID = i;
        }
    }
}

void GraphView::mouseMoveEvent(QMouseEvent *event)
{

    if(m_currentID == -1)
        return;

    Station_Pos[m_currentID] = event->pos();

    update();
}

void GraphView::mouseReleaseEvent(QMouseEvent *event)
{
    m_currentID = -1;
}

#include "mapwindow.h"
#include "ui_mapwindow.h"

#include <new>
#include <QTime>

using namespace std;

MapWindow::MapWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MapWindow)
{
    ui->setupUi(this);

    ui->start_point->addItem(QString(""));
    ui->end_point->addItem(QString(""));
    ui->from_station->addItem(QString(""));
    ui->to_station->addItem(QString(""));

    setWindowTitle("AMTR - Xiamen Metro");

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    Map_Reset();
}
MapWindow::~MapWindow()
{
    delete ui;
}

void MapWindow::Map_Reset()
{
    for(int i = 0; i < AMTR_Line_1_cnt; ++i)
        preAddStation(QString::fromLocal8Bit(AMTR_Line_1[i].c_str()), AMTR_Line_1_pos[i]);
    for(int i = 1; i < AMTR_Line_1_cnt; ++i)
        preAddEdge(i, i + 1, 1);
    ui->MapWidget->update();
}
void MapWindow::preAddStation(const QString station, const QPoint pos)
{
    AMTR.add_point(station);

    ui->start_point->addItem(station);
    ui->end_point->addItem(station);
    ui->from_station->addItem(station);
    ui->to_station->addItem(station);

    ui->MapWidget->Station_name.append(station);
    ui->MapWidget->Station_Pos.append(pos);
}
void MapWindow::preAddEdge(const int u, const int v, const int tLine)
{
    AMTR.add_path(u, v);
    AMTR.add_path(v, u);

    ui->MapWidget->Edge.insert(make_pair(u, make_pair(v, tLine)));
}

void MapWindow::on_add_station_button_clicked()
{
    int empty = ui->station_input->text().isEmpty();
    if(empty == 1)
        return;

    QString station  = ui->station_input->text();
    int exist = AMTR.exist(station);
    if(exist == 1)
        return;

    AMTR.add_point(station);

    ui->start_point->addItem(station);
    ui->end_point->addItem(station);
    ui->from_station->addItem(station);
    ui->to_station->addItem(station);
    ui->station_input->setText("");

    ui->MapWidget->Station_name.append(station);
    ui->MapWidget->Station_Pos.append(QPoint(qrand() % 70 + 30, qrand() % 70 + 30));
    ui->MapWidget->update();
}

void MapWindow::on_add_path_button_clicked()
{
    int u_empty = ui->from_station->currentText().isEmpty();
    int v_empty = ui->to_station->currentText().isEmpty();

    if(u_empty || v_empty || ui->from_station->currentText() == ui->to_station->currentText())
    {
        ui->from_station->setCurrentIndex(0);
        ui->to_station->setCurrentIndex(0);
        return;
    }
    int u = AMTR.get_id(ui->from_station->currentText());
    int v = AMTR.get_id(ui->to_station->currentText());
    if(u > v)
        swap(u, v);
    int tLine = ui->Line_input->value();

    pair<multimap<int, pair<int, int> >::const_iterator, multimap<int, pair<int, int> >::const_iterator> Range = ui->MapWidget->Edge.equal_range(u);
    for(multimap<int, pair<int, int> >::const_iterator it = Range.first; it != ui->MapWidget->Edge.end() && it != Range.second; ++it)
        if(it->second.first == v && it->second.second == tLine)
        {
            ui->from_station->setCurrentIndex(0);
            ui->to_station->setCurrentIndex(0);
            return;
        }

    AMTR.add_path(u, v); AMTR.add_path(v, u);

    ui->MapWidget->Edge.insert(make_pair(u, make_pair(v, tLine)));
    ui->MapWidget->update();

    ui->from_station->setCurrentIndex(0);
    ui->to_station->setCurrentIndex(0);
}

void MapWindow::on_calc_button_clicked()
{
    int u_empty = ui->start_point->currentText().isEmpty();
    int v_empty = ui->end_point->currentText().isEmpty();
    if(u_empty || v_empty ||  ui->start_point->currentText() ==  ui->end_point->currentText())
        return;

    QString u = ui->start_point->currentText();
    QString v = ui->end_point->currentText();

    int *path = AMTR.get_shortest_path(u, v);
    if(path == NULL)
        return;

    ui->MapWidget->Path_id.clear();
    int i;
    for(i = 1; path[i] != -1; ++i)
        ui->MapWidget->Path_id.append(path[i]);
    ui->MapWidget->update();

    //----------route_info----------
    ui->route_info->clear(); preL.clear();
    for(int j = 1; j <= Line_cnt; ++j)
        preL.append(j);

    QString info = QString::fromLocal8Bit((const char*)("在"));
    info = info + ui->MapWidget->Station_name[path[i - 1] - 1];
    info = info + QString::fromLocal8Bit((const char*)("站上车"));
    ui->route_info->append(info);
    for(i = i - 1; i > 1; --i)
    {
        curL.clear(); tmpL.clear();
        int u = path[i], v=path[i - 1];
        if(u > v)
            swap(u, v);
        pair<multimap<int, pair<int, int> >::const_iterator, multimap<int, pair<int, int> >::const_iterator> Range = ui->MapWidget->Edge.equal_range(u);
        for(multimap<int, pair<int, int> >::const_iterator it = Range.first; it != ui->MapWidget->Edge.end() && it != Range.second; ++it)
            if(it->second.first == v)
            {
                curL.append(it->second.second);
            }

        for(int j = 0; j < curL.size(); ++j)
        {
            int pos = preL.indexOf(curL[j]);
            if(pos == -1)
                continue;
            tmpL.append(curL[j]);
        }
        if(!tmpL.size())
        {
            info = QString::fromLocal8Bit((const char*)("乘坐"));
            info = info + QString::number(preL[0]);
            for(int j = 1; j < curL.size(); ++j)
            {
                info = info + QString::fromLocal8Bit((const char*)("号线或"));
                info = info + QString::number(preL[j]);
            }
            info = info + QString::fromLocal8Bit((const char*)("号线至"));
            info = info + ui->MapWidget->Station_name[path[i] - 1];
            info = info + QString::fromLocal8Bit((const char*)("站换乘"));
            ui->route_info->append(info);
            preL = curL;
        }
        else
            preL = tmpL;
    }
    info = QString::fromLocal8Bit((const char*)("乘坐"));
    info = info + QString::number(preL[0]);
    for(int j = 1; j < preL.size(); ++j)
    {
        info = info + QString::fromLocal8Bit((const char*)("号线或"));
        info = info + QString::number(preL[j]);
    }
    info = info + QString::fromLocal8Bit((const char*)("号线"));
    info = info + QString::fromLocal8Bit((const char*)("至"));
    info = info + ui->MapWidget->Station_name[path[i] - 1];
    info = info + QString::fromLocal8Bit((const char*)("站下车"));
    ui->route_info->append(info);

    delete[]path;
}

void MapWindow::on_reset_button_clicked()
{
    ui->start_point->setCurrentIndex(0);
    ui->end_point->setCurrentIndex(0);

    ui->MapWidget->Path_id.clear();
    ui->MapWidget->update();

    ui->route_info->clear();
}

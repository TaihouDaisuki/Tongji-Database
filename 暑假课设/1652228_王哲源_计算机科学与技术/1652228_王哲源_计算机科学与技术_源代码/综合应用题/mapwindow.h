#ifndef MAPWINDOW_H
#define MAPWINDOW_H

#include <QMainWindow>

#include "map.h"
#include "graphview.h"
#include "amtr_line_1.h"

namespace Ui {
class MapWindow;
}

class MapWindow : public QMainWindow
{
    Q_OBJECT

public:
    Map AMTR;

    explicit MapWindow(QWidget *parent = 0);
    ~MapWindow();

private slots:
    void on_add_station_button_clicked();

    void on_add_path_button_clicked();

    void on_calc_button_clicked();

    void on_reset_button_clicked();

private:
    Ui::MapWindow *ui;
    QList<int> preL, curL, tmpL;

    void Map_Reset();
    void preAddStation(const QString, const QPoint);
    void preAddEdge(const int, const int, const int);
};

#endif // MAPWINDOW_H

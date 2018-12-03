#ifndef SORTWINDOW_H
#define SORTWINDOW_H

#include <QDialog>
#include "heap.h"

namespace Ui {
class SortWindow;
}

class SortWindow : public QDialog
{
    Q_OBJECT

public:
    Heap_For_Sort heap;

    explicit SortWindow(QWidget *parent = 0);
    ~SortWindow();

private slots:
    void on_next_button_clicked();

    void on_array_cur_linkActivated(const QString &link);

    void on_heap_cur_linkActivated(const QString &link);

private:
    Ui::SortWindow *ui;
};

#endif // SORTWINDOW_H

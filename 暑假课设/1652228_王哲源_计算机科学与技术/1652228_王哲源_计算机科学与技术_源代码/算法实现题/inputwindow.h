#ifndef INPUTWINDOW_H
#define INPUTWINDOW_H

#include <QDialog>

#include "array_input.h"

namespace Ui {
class InputWindow;
}

class InputWindow : public QDialog
{
    Q_OBJECT

public:
    array_input arr;

    explicit InputWindow(QWidget *parent = 0);
    ~InputWindow();

private slots:
    void on_number_OK_clicked();

    void on_array_output_linkActivated(const QString &link);

private:
    Ui::InputWindow *ui;
};

#endif // INPUTWINDOW_H

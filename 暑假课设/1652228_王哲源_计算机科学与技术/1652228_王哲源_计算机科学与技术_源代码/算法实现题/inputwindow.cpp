#include "inputwindow.h"
#include "ui_inputwindow.h"

InputWindow::InputWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InputWindow)
{
    ui->setupUi(this);
    this->resize(QSize(800, 600));
    this->setWindowTitle("Array Input");

    ui->array_output->setAlignment(Qt::AlignLeft | Qt::AlignTop);       //设置位置，左上角对齐
    ui->array_output->adjustSize();                                     //Qlabel自适应窗口大小
    ui->array_output->setGeometry(QRect(100, 170, 580, 290));           //设置左上角坐标、宽度及高度
    ui->array_output->setWordWrap(true);                                //自动换行
}

InputWindow::~InputWindow()
{
    delete ui;
}

void InputWindow::on_number_OK_clicked()
{
    static QString numString = "";

    int num = int(ui -> number_input -> value());
    arr.add(num);

    QString tmp;
    tmp.sprintf("%d",num);
    numString.append(tmp + "  ");
    this -> on_array_output_linkActivated(numString);
}

void InputWindow::on_array_output_linkActivated(const QString &link)
{
    ui->array_output->setText(link);
}

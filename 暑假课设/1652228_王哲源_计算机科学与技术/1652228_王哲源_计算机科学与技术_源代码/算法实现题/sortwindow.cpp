#include "sortwindow.h"
#include "ui_sortwindow.h"

SortWindow::SortWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SortWindow)
{
    ui->setupUi(this);
    this->resize(QSize(800, 600));
    this->setWindowTitle("Heap Sort");

    QFont output_font("A-OTF Shin Maru Go Pro DB", 12, 50);

    ui->heap_cur->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    ui->heap_cur->adjustSize();
    ui->heap_cur->setGeometry(QRect(140, 178, 501, 141));
    ui->heap_cur->setWordWrap(true);
    ui->heap_cur->setStyleSheet("color:red");
    ui->heap_cur->setFont(output_font);

    ui->array_cur->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    ui->array_cur->adjustSize();
    ui->array_cur->setGeometry(QRect(140, 380, 501, 141));
    ui->array_cur->setWordWrap(true);
    ui->array_cur->setStyleSheet("color:green");
    ui->array_cur->setFont(output_font);

    ui->next_button->setText("start");
    ui->top_number->display("");
}

SortWindow::~SortWindow()
{
    delete ui;
}

void SortWindow::on_next_button_clicked()
{
    if(this->heap.tail == 0)
    {
        ui->next_button->setText("finish");
        this->close();
        return;
    }
    if(this->heap.tail == 1)
        ui->next_button->setText("finish");
    else
        ui->next_button->setText("next");
    ui->top_number->display(this->heap.top());

    int tmp = this->heap.heap[1];
    this->heap.heap[1] = this->heap.heap[this->heap.tail];
    this->heap.heap[this->heap.tail] = tmp;
    --this->heap.tail;
    this->heap.push_down();

    QString sorted = "", unsorted = "", tmpQS;
    qDebug("%d %d\n",heap.n, heap.tail);

    for(int i = 1; i <= this->heap.tail; ++i)
        tmpQS.sprintf("%d",this->heap.heap[i]), unsorted.append(tmpQS + "  ");
    for(int i = this->heap.tail + 1; i <= this->heap.n; ++i)
        tmpQS.sprintf("%d",this->heap.heap[i]), sorted.append(tmpQS + "  ");


    this->on_heap_cur_linkActivated(unsorted);
    this->on_array_cur_linkActivated(sorted);
}

void SortWindow::on_heap_cur_linkActivated(const QString &link)
{
    ui->heap_cur->setText(link);
}

void SortWindow::on_array_cur_linkActivated(const QString &link)
{
    ui->array_cur->setText(link);
}

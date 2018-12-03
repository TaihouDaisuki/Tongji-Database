#include <QApplication>

#include "inputwindow.h"
#include "sortwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    InputWindow inputW;

    SortWindow sortW;

    if(inputW.exec() == QDialog::Accepted)  //接收到accept指令
    {
        //heap reset
        sortW.heap.build(inputW.arr.A, inputW.arr.n);
        for(int i = 1; i <= sortW.heap.n; ++i)
            sortW.heap.push_up(i);

        sortW.show();       //转到排序界面
        return a.exec();    //继续执行
    }
    else
        return 0;
}

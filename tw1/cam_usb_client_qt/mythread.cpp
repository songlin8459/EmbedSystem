#include "mythread.h"
#include "mainwindow.h"

#include <QMutex>
//全局变量

extern QMutex mutex;
extern int isOC;
extern QString oc_result;
MyThread::MyThread(QObject *parent) : QThread(parent)
{

}


void MyThread::run()
{
//    while(1)
//    {
//        mutex.lock();
//        if(img_show_and_oc.size > 0 && isOC == 1)
//        {
//            argument = "E:/tech/hqyj_project_client/img/oc_img.jpg";
//            cv::imwrite(argument.toStdString(), img_show_and_oc);
//            qDebug() << "imwrite img_show_and_oc success!";

//            //1.创建进程用于调用python
//            py_process = new QProcess(this);
//            py_process->setProgram("C:/ProgramData/anaconda3/envs/tf/python.exe");
//            py_process->setArguments({"E:/hqyj_project/trash_classification_tf2.3_master_complete/code/test_without_pyqt.py", argument});

//            //2.连接信号与槽，捕获python打印的数据
//            QString output;
//            connect(py_process, &QProcess::readyReadStandardOutput, [&]() {
//                QString outputs = py_process->readAllStandardOutput().data();

//                if(outputs.contains("blue"))
//                {
//                    output = "可回收垃圾";
//                }
//                if(outputs.contains("green"))
//                {
//                    output = "厨余垃圾";
//                }
//                if(outputs.contains("red"))
//                {
//                    output = "有害垃圾";
//                }
//                if(outputs.contains("gray"))
//                {
//                    output = "其他垃圾";
//                }
//                //显示分类结果
//                qDebug() << "output:" << output;
//            });
//            //进程启动
//            py_process->close();
//            py_process->start();

//            //识别结束，返回结果，isOC=0
//            oc_result = output;
//            py_process->close();
//            isOC = 0;
//        }
//        mutex.unlock();
//    }

}



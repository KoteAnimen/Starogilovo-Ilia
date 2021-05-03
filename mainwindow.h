#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "cameraconnect.h"

#include <QMainWindow>
#include <QFile>
#include <QScrollBar>
#include <QThread>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void FrameFromFirstCamera(cv::Mat);
    void FrameFromSecondCamera(cv::Mat);

signals:
    void getFrameFirst();
    void getFrameSecond();


private slots:
    void on_btn_Close_clicked();

    void on_btn_Start_clicked();

    void on_btn_Stop_clicked();

private:
    Ui::MainWindow *ui;

    CameraConnect* cam_First;
    CameraConnect* cam_Second;

    QThread* thread_cam_first;
    QThread* thread_cam_second;

    QImage* cam_Frame_First;
    QImage* cam_Frame_Second;




};
#endif // MAINWINDOW_H

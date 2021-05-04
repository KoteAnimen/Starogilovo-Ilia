#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    cam_First = new CameraConnect();
    cam_Second = new CameraConnect();

    thread_cam_first = new QThread();
    thread_cam_second = new QThread();

    cam_First->moveToThread(thread_cam_first);
    cam_Second->moveToThread(thread_cam_second);



    connect(cam_First, &CameraConnect::FrameReady, this, &MainWindow::FrameFromFirstCamera);
    connect(this, &MainWindow::getFrameFirst, cam_First, &CameraConnect::GrabImage);
    connect(thread_cam_first, &QThread::started, cam_First, &CameraConnect::GrabImage);

    connect(cam_Second, &CameraConnect::FrameReady, this, &MainWindow::FrameFromSecondCamera);
    connect(this, &MainWindow::getFrameSecond, cam_Second, &CameraConnect::GrabImage);
    connect(thread_cam_second, &QThread::started, cam_Second, &CameraConnect::GrabImage);




    ui->btn_Report->setFlat(true);
    ui->btn_Settings->setFlat(true);
    ui->btn_Close->setFlat(true);
    ui->btn_Stop->setFlat(true);
    ui->btn_Start->setFlat(true);
    ui->btn_DeleteCode->setFlat(true);

//    ui->scrollArea->setWidgetResizable(true);

    ui->btn_Stop->setVisible(false);
    ui->btn_DeleteCode->setVisible(false);

    QScrollBar* vScrollBar = new QScrollBar;
//    vScrollBar->setValue(1000);

    ui->scrollArea->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);

    cam_First->initSome();
    cam_First->setSerial("22310683");
    cam_First->OpenCamera();

    cam_Second->initSome();
    cam_Second->setSerial("40043746");
    cam_Second->OpenCamera();

    thread_cam_first->start();
    thread_cam_second->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_Close_clicked()
{
    exit(0);
}

void MainWindow::FrameFromFirstCamera(cv::Mat src)
{
    cam_Frame_First = new QImage(src.data, src.cols, src.rows, src.step,QImage::Format_Grayscale8);
    ui->lbl_LeftFrame->setPixmap(QPixmap::fromImage(*cam_Frame_First).scaled(ui->lbl_LeftFrame->size()));
    ui->lbl_LeftFrame->update();
    emit getFrameFirst();
    delete cam_Frame_First;
}

void MainWindow::FrameFromSecondCamera(cv::Mat src)
{
    cam_Frame_Second = new QImage(src.data, src.cols, src.rows, src.step,QImage::Format_Grayscale8);
    ui->lbl_RigthFrame->setPixmap(QPixmap::fromImage(*cam_Frame_Second).scaled(ui->lbl_RigthFrame->size()));
    ui->lbl_RigthFrame->update();
    emit getFrameSecond();
    delete cam_Frame_Second;
}

void MainWindow::on_btn_Start_clicked()
{
    ui->btn_Start->setVisible(false);
    ui->btn_Stop->setVisible(true);
    ui->btn_DeleteCode->setVisible(true);

    ui->swg_MainForm->setCurrentIndex(1);
}

void MainWindow::on_btn_Stop_clicked()
{
    ui->btn_Start->setVisible(true);
    ui->btn_Stop->setVisible(false);
    ui->btn_DeleteCode->setVisible(false);

    ui->swg_MainForm->setCurrentIndex(0);
}




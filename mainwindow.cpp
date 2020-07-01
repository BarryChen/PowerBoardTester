#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include "adbpath.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("电源板测试工具");

    this->mAdbWatch = new AdbWatch;
    connect(this->mAdbWatch, SIGNAL(onUsbConnect()), this, SLOT(MainUsbConnected()));
    connect(this->mAdbWatch, SIGNAL(onUsbDisconnect()), this, SLOT(MainUsbDisconnected()));
    connect(this->mAdbWatch, SIGNAL(onExeCmdError()), this, SLOT(ExeCmdError()));


    this->mGpsInfo = new GpsInfo;
    connect(this->mGpsInfo, SIGNAL(onHaveGpsInfo(GpsData *, QString)), this, SLOT(HaveGpsInfo(GpsData *, QString)));

    this->mKeyInfo = new KeyInfo;
    connect(this->mKeyInfo, SIGNAL(onKeyPress(KEYPRESS)), this, SLOT(MainKeyPress(KEYPRESS)));

    label_palette.setColor(QPalette::Background, QColor(0xcc,0xff,0xcc));

}

MainWindow::~MainWindow()
{
    if(this->mAdbWatch != nullptr)
    {
        qDebug() << "mainwindow: delete adbwatch";
        delete this->mAdbWatch;

    }
    this->mAdbPath = nullptr;

    if(this->mGpsInfo != nullptr)
    {
        qDebug() << "mainwindow: delete gpsinfo";
        delete this->mGpsInfo;
    }
    this->mGpsInfo = nullptr;

    delete ui;
}


void MainWindow::ClearBackground()
{
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(0, 0, 0, 0));
    ui->label_power->setAutoFillBackground(true); //这句很关键，否则背景色被默认windows替代
    ui->label_power->setPalette(palette);

    ui->label_volup->setAutoFillBackground(true); //这句很关键，否则背景色被默认windows替代
    ui->label_volup->setPalette(palette);

    ui->label_voldown->setAutoFillBackground(true); //这句很关键，否则背景色被默认windows替代
    ui->label_voldown->setPalette(palette);

}

void MainWindow::MainUsbConnected()
{
    this->ui->label_usb->setText("已经连接成功");
    this->mGpsInfo->StartCmd();
    this->mKeyInfo->StartCmd();

}

void MainWindow::MainUsbDisconnected()
{
    this->mGpsInfo->StopCmd();
    this->mKeyInfo->StopCmd();
    ClearBackground();
    this->ui->label_usb->setText("未连接");
    this->ui->label_gps->setText("未定位");
    this->ui->label_gpsinfo->setText("");
}

void MainWindow::setLableBackcolor(QLabel *lable)
{
    lable->setAutoFillBackground(true); //这句很关键，否则背景色被默认windows替代
    lable->setPalette(label_palette);
}
void MainWindow::MainKeyPress(KEYPRESS key)
{
    if(key == KEYPRESS_PWR)
    {
        ui->label_power->setAutoFillBackground(true);
        ui->label_power->setPalette(label_palette);
    }
    else if(key == KEYPRESS_VUP)
    {
        ui->label_volup->setAutoFillBackground(true);
        ui->label_volup->setPalette(label_palette);
    }
    else if(key == KEYPRESS_VDOWN)
    {
        ui->label_voldown->setAutoFillBackground(true);
        ui->label_voldown->setPalette(label_palette);
    }


}
void MainWindow::ExeCmdError()
{
    QStringList title;
    title << "电源板测试工具";
    title << " - ";
    title << "请设置adb.exe文件~~";
    this->setWindowTitle(title.join(" "));
}

void MainWindow::HaveGpsInfo(GpsData * data, QString str)
{
    QStringList gpsinfo;
    QString tmp;

    if(data == nullptr)
        return;

    if(data->status == "V") {
        ui->label_gps->setText("未定位");
    } else if(data->status == "A"){
        gpsinfo << data->lat;
        gpsinfo << data->ew;
        gpsinfo << data->lng;
        gpsinfo << data->ns;
        tmp = gpsinfo.join(",");
        ui->label_gps->setText("已定位: "+tmp);
    }
    ui->label_gpsinfo->setText(str);
}

void MainWindow::SelectFile()
{
    QStringList title;
    title << "电源板测试工具";
    title << " - ";

    QString fileName = QFileDialog::getOpenFileName(this,tr("文件对话框！"), ".", tr("exe(*.exe);"));
    qDebug()<<"filename : "<<fileName;

    title << fileName;

    this->setWindowTitle(title.join(" "));
    this->mAdbPath = fileName;


}

void MainWindow::on_action_adb_triggered()
{
    SelectFile();
    if(!this->mAdbPath.isEmpty() && this->mAdbPath.right(7) == "adb.exe")
    {
        qDebug() << "adb path" << this->mAdbPath;
        SetAdbPath(this->mAdbPath);
    }
}

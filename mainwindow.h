#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include "adbwatch.h"
#include "gpsinfo.h"
#include "keyinfo.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void SelectFile();
    void setLableBackcolor(QLabel *lable);
    void ClearBackground();

    AdbWatch    *mAdbWatch;
    GpsInfo     *mGpsInfo;
    KeyInfo     *mKeyInfo;

    QString     mAdbPath;
    QPalette    label_palette;

private slots:
    void MainUsbConnected();
    void MainUsbDisconnected();
    void ExeCmdError();

    void HaveGpsInfo(GpsData *data, QString str);
    void MainKeyPress(KEYPRESS key);

    void on_action_adb_triggered();

signals:
    void onAdbPathChanged(QString path);
};
#endif // MAINWINDOW_H

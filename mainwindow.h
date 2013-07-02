#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QSettings>
#include <QByteArray>
#include <QMessageBox>
#include <QNetworkReply>
#include <QNetworkAccessManager>

#include <qjson/parser.h>

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void writeSettings();
    void readSettings(bool window = false);

private slots:
    void finished(QNetworkReply *reply);
    void doHttpRequest(QUrl url, bool post = false, QString postData = "");
    
    void on_button_update_clicked();
    void on_action_Settings_triggered();
    void on_action_AboutQt_triggered();
    void on_action_About_triggered();

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *nam;
    QJson::Parser parser;
    QStringList knownActions;
};

#endif // MAINWINDOW_H
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 

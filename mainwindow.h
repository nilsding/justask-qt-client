/*  This file is part of justask-qt-client, a Qt4 client for justask installations.
 *  Copyright (C) 2013 nilsding
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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
    void deleteQuestion(int question_id);
    void answerQuestion(int question_id, QString answer, Qt::CheckState postToTwitter);
    
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

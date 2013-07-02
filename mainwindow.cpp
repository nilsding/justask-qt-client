#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settingsdialog.h"

QSettings s("nilsding", "justask-qt");

QString user_name = "";
QString api_key = "";
QString api_endpoint = "";

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    nam = new QNetworkAccessManager();
    s.beginGroup("general");
    user_name = s.value("user_name", "").toString();
    api_key = s.value("api_key", "").toString();
    api_endpoint = s.value("installation_url", "http://").toString().append("/api.php?user_name=").append(user_name).append("&api_key=").append(api_key);
    s.endGroup();
    if (!(QString("").compare(user_name)) || !(QString("").compare(api_key))) {
        SettingsDialog sd;
        sd.exec();
    }

    // all available actions
    knownActions << "info" << "get_inbox" << "get_answers";

    connect(nam, SIGNAL(finished(QNetworkReply *)), this, SLOT(finished(QNetworkReply *)));

    readSettings(true);
}

void MainWindow::writeSettings()
{
    qDebug() << "[i] saving settings";
    s.beginGroup("MainWindow");
    s.setValue("size", size());
    s.setValue("pos", pos());
    s.endGroup();
}

void MainWindow::readSettings(bool window)
{
    qDebug() << "[i] loading settings";

    if (window) {
        s.beginGroup("MainWindow");
        this->resize(s.value("size", QSize(410, 211)).toSize());
        this->move(s.value("pos", QPoint(200, 200)).toPoint());
        this->repaint();
        s.endGroup();
    }

    s.beginGroup("general");
    user_name = s.value("user_name", "").toString();
    api_key = s.value("api_key", "").toString();
    api_endpoint = s.value("installation_url", "http://").toString().append("/api.php?user_name=").append(user_name).append("&api_key=").append(api_key);
    s.endGroup();

    doHttpRequest(QUrl(api_endpoint.append("&action=info")));
}

MainWindow::~MainWindow()
{
    writeSettings();
    delete nam;
    delete ui;
}

void MainWindow::finished(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray ba = reply->readAll();
        qDebug() << "[i] request successful!";
        qDebug() << "[i] ==> data:" << ba;
        QVariantMap res = parser.parse(ba).toMap();
        switch (res["code"].toInt()) {
            case 200: {        // success
                switch (knownActions.indexOf(res["action"].toString())) {
                    case 0: {       // info
//                         QMessageBox mb;
//                         mb.setWindowTitle(tr("Success"));
//                         mb.setIcon(QMessageBox::Information);
//                         mb.setText(tr("Hi, %1! You have already answered %2 questions.<br />"
//                                       "There are %3 questions in your inbox waiting to be answered.<br /><br />Sending tweets is <strong>%4</strong> by default.")
//                                   .arg(res["data"].toMap()["user_name"].toString()).arg(res["data"].toMap()["answer_count"].toInt()).arg(res["data"].toMap()["question_count"].toInt()).arg((res["data"].toMap()["twitter_check"].toBool()) ? tr("enabled") : tr("disabled")));
//                         mb.setParent(this);
//                         mb.exec();
                        ui->label_info_site_name->setText(res["data"].toMap()["site_name"].toString());
                        ui->label_user_name->setText(res["data"].toMap()["user_name"].toString());
                        ui->label_question_count->setText(res["data"].toMap()["question_count"].toString());
                        ui->label_answer_count->setText(res["data"].toMap()["answer_count"].toString());
                        ui->label_gravatar->setText(res["data"].toMap()["gravatar"].toBool() ? tr("Yes") : tr("No"));
                        ui->label_twitter_on->setText(res["data"].toMap()["twitter_on"].toBool() ? tr("Yes") : tr("No"));
                        ui->label_anon_questions->setText(res["data"].toMap()["anon_questions"].toBool() ? tr("Yes") : tr("No"));
                        break;
                    }
                    case 1: {       // get_inbox
                        break;
                    }
                    case 2: {       // get_answers
                        break;
                    }
                    default: {      // ???

                    }
                }
                break;
            }
            case 405: {
                QMessageBox mb;
                mb.setWindowTitle("Error");
                //ugh
                break;
            }
        }
        if (res["success"].toBool() == true && res["code"].toInt() == 200) {
            QString s = QString("(").append(res["data"].toMap()["question_count"].toString()).append(") justask-qt-client");//.append(res["data"].toMap()["site_name"].toString());
            this->setWindowTitle(s);
        }
    } else {
        qDebug() << "[e] got an error while doing the network request:" << reply->errorString();
        
        QMessageBox mb;
        mb.setWindowTitle(tr("Error"));
        mb.setIcon(QMessageBox::Critical);
        switch (reply->error()) {
            case QNetworkReply::NoError: {
                mb.setText(tr("No error occurred.<br />Congratulations, you found aBug&trade;"));
                break;
            }
            case QNetworkReply::ConnectionRefusedError: {
                mb.setText(tr("Connection refused"));
                break;
            }
            case QNetworkReply::RemoteHostClosedError: {
                mb.setText(tr("The remote host closed the connection."));
                break;
            }
            case QNetworkReply::HostNotFoundError: {
                mb.setText(tr("Host not found."));
                break;
            }
            case QNetworkReply::TimeoutError: {
                mb.setText(tr("The connection timed out."));
                break;
            }
            case QNetworkReply::SslHandshakeFailedError: {
                mb.setText(tr("The SSL/TLS handshake failed."));
                break;
            }
            case QNetworkReply::TemporaryNetworkFailureError: {
                mb.setText(tr("The connection was broken due to disconnection from the network, however the system has initiated roaming to another access point."));
                break;
            }
            case QNetworkReply::ContentAccessDenied: {
                mb.setText(tr("HTTP 401: Access denied."));
                break;
            }
            case QNetworkReply::ContentNotFoundError: {
                mb.setText(tr("HTTP 404: File not found."));
                break;
            }
            case QNetworkReply::UnknownNetworkError: {
                mb.setText(tr("Network error."));
                break;
            }
            default: {
                mb.setText(tr("Unknown error."));
            }
        }
        mb.setParent(this);
        mb.exec();
    }
}

/**
 * Do a HTTP GET or POST request
 * @param url The URL
 * @param post If set to true, the HTTP request will be a POST request.
 * @param postData The data to send with the POST request.
 * @return The response
 */
void MainWindow::doHttpRequest(QUrl url, bool post, QString postData)
{
    QByteArray ba;
    ba.append(postData.toAscii());

    qDebug() << "[i] initiating HTTP" << (post ? "POST" : "GET") << "request";
    qDebug() << "[i] ==> URL:" << url;
    if (post) {
        qDebug() << "[i] ==> POST data:" << postData;
        nam->post(QNetworkRequest(url), ba);
    } else {
        nam->get(QNetworkRequest(url));
    }
}

void MainWindow::on_button_update_clicked()
{
    doHttpRequest(QUrl(api_endpoint.append("&action=info")));
}

void MainWindow::on_action_Settings_triggered()
{
    SettingsDialog sd(this);
    sd.exec();
}

void MainWindow::on_action_AboutQt_triggered()
{
    QMessageBox::aboutQt(this, tr("About %1").arg("Qt"));
}

void MainWindow::on_action_About_triggered()
{
    QMessageBox::about(this, tr("About %1").arg("justask-qt-client"), "<strong>justask-qt-client</strong> - a Qt client for justask installations<br />"
                       "&copy; 2013 nilsding<br /><br />"
                       "justask-qt-client is free software: you can redistribute it and/or modify<br />"
                       "it under the terms of the GNU General Public License as published by<br />"
                       "the Free Software Foundation, either version 3 of the License, or<br />"
                       "(at your option) any later version.<br />"
                       "<a href=\"https://www.gnu.org/licenses/gpl-3.0.html\">Read the full license text here</a><br /><br />"
                       "<a href=\"https://github.com/nilsding/justask-qt-client\">Get the source code at GitHub</a>");
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 

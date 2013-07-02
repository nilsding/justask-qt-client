#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include "mainwindow.h"

#include <QUrl>

extern QSettings s;

SettingsDialog::SettingsDialog(QWidget *parent) : QDialog(parent), ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    s.beginGroup("general");
    ui->line_user_name->setText(s.value("user_name", "").toString());
    ui->line_apikey->setText(s.value("api_key", "").toString());
    ui->installation_url->setText(s.value("installation_url", "http://").toString());
    s.endGroup();
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::on_installation_url_textChanged(QString s)
{
    if (s.toLower().startsWith("https://")) {
        ui->http_s->setCurrentIndex(1);
        ui->installation_url->setText(s.replace("https://", "", Qt::CaseInsensitive));
    } else if (s.toLower().startsWith("http://")) {
        ui->http_s->setCurrentIndex(0);
        ui->installation_url->setText(s.replace("http://", "", Qt::CaseInsensitive));
    }
}

void SettingsDialog::accept()
{
    qDebug("[i] saving settings");
    s.beginGroup("general");
    s.setValue("user_name", ui->line_user_name->text());
    s.setValue("api_key", ui->line_apikey->text());
    s.setValue("installation_url", ui->http_s->currentText().append(ui->installation_url->text()));
    s.endGroup();
    QDialog::accept();
}

void SettingsDialog::reject()
{
    qDebug("[i] settings not saved");
    QDialog::reject();
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 

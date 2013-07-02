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

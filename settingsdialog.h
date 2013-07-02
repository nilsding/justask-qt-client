#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QSettings>

namespace Ui
{
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = 0);
    ~SettingsDialog();

private slots:
    void on_installation_url_textChanged(QString s);
    void accept();
    void reject();
    
private:
    Ui::SettingsDialog *ui;
};

#endif // SETTINGS_H
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 

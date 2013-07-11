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

#ifndef QUESTIONWIDGET_H
#define QUESTIONWIDGET_H

#include <QtGui/QWidget>
#include <QVariantMap>

namespace Ui
{
class QuestionWidget;
}

class QuestionWidget : public QWidget
{
    Q_OBJECT
public:
    QuestionWidget(QVariantMap question, bool twitter);
    ~QuestionWidget();
    int getQuestionId();
    
private:
    Ui::QuestionWidget *ui;
    
    QVariantMap question;
    int question_id;

private slots:
    void on_button_delete_clicked();
    
};

#endif // QUESTIONWIDGET_H

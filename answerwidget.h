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

#ifndef ANSWERWIDGET_H
#define ANSWERWIDGET_H

#include <QtGui/QWidget>
#include <QVariantMap>

namespace Ui
{
class AnswerWidget;
}

class AnswerWidget : public QWidget
{
    Q_OBJECT
public:
    AnswerWidget(QVariantMap answer, QString answered_by);
    ~AnswerWidget();
    
private:
    Ui::AnswerWidget *ui;
    
    QString answered_by;
    QVariantMap answer;
    int answer_id;

};

#endif // ANSWERWIDGET_H

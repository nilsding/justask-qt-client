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

#include "questionwidget.h"
#include "ui_questionwidget.h"
#include <QDebug>

QuestionWidget::QuestionWidget(QVariantMap question, bool twitter) : ui(new Ui::QuestionWidget), question(question)
{
    QString question_asked_by = "";
    
    question_id = question["question_id"].toInt();
    
    if (question["asker_private"].toBool()) {
        question_asked_by = tr("Anonymous");
    } else {
        question_asked_by = question["question_asked_by"].toString();
    }
    
    ui->setupUi(this);
    
    ui->label_user_asked->setText(tr("<strong>%1</strong> asked:").arg(question_asked_by));
    ui->label_question->setText(question["question_content"].toString());
    ui->chk_post_to_twitter->setCheckState(twitter ? Qt::Checked : Qt::Unchecked);
}

int QuestionWidget::getQuestionId()
{
    return question_id;
}

QuestionWidget::~QuestionWidget()
{
    delete ui;
}
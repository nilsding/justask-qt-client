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

#include "answerwidget.h"
#include "ui_answerwidget.h"

AnswerWidget::AnswerWidget(QVariantMap answer, QString answered_by) : ui(new Ui::AnswerWidget), answer(answer), answered_by(answered_by)
{
    QString question_asked_by = "";
    
    answer_id = answer["answer_id"].toInt();
    
    if (answer["asker_private"].toBool()) {
        question_asked_by = tr("Anonymous");
    } else {
        question_asked_by = answer["question_asked_by"].toString();
    }
    
    ui->setupUi(this);
    
    ui->label_user_asked->setText(tr("<strong>%1</strong> asked:").arg(question_asked_by));
    ui->label_question->setText(answer["question_content"].toString());
    
    ui->label_user_answered->setText(tr("<strong>%1</strong> answered:").arg(answered_by));
    ui->label_answer->setText(answer["answer_text"].toString());
}

AnswerWidget::~AnswerWidget()
{
    delete ui;
}

/*
 * TEMPO - Topographic Eeg Mapping PrOgram.
 * 
 * Copyright (C) 1995, 1996, 2003, 2004, 2005, 2007 Aleksandar
 * Samardzic
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301
 * USA
 */

//!\file info_widget.cpp
//!Definition of InfoWidget class.

#include "info_widget.h"

InfoWidget::InfoWidget(QWidget *parent)
        : QGroupBox(tr("Info"), parent)
{
        /* Create patient informations widgets. */
        QLabel *patientLabel = new QLabel(tr("Patient"), this);
        patientLineEdit = new QLineEdit(this);
        patientLineEdit->setFocusPolicy(Qt::NoFocus);
        patientLineEdit->setReadOnly(true);
        patientLineEdit->setToolTip(tr("Patient identification"));

        /* Create recording informations widgets. */
        QLabel *recordingLabel = new QLabel(tr("Recording"), this);
        recordingLineEdit = new QLineEdit(this);
        recordingLineEdit->setFocusPolicy(Qt::NoFocus);
        recordingLineEdit->setReadOnly(true);
        recordingLineEdit->setToolTip(tr("Recording identification"));

        /* Create starting date and time informations widgets. */
        QLabel *startingLabel = new QLabel(tr("Starting"), this);
        startingLineEdit = new QLineEdit(this);
        startingLineEdit->setFocusPolicy(Qt::NoFocus);
        startingLineEdit->setReadOnly(true);
        startingLineEdit->setToolTip(tr("Starting date and time of recording"));

        /* Create widget layout. */
        QGridLayout *layout = new QGridLayout(this);
        layout->setMargin(5);
        layout->setSpacing(3);
        layout->addWidget(patientLabel, 0, 0);
        layout->addWidget(patientLineEdit, 0, 1);
        layout->addWidget(recordingLabel, 1, 0);
        layout->addWidget(recordingLineEdit, 1, 1);
        layout->addWidget(startingLabel, 2, 0);
        layout->addWidget(startingLineEdit, 2, 1);

        /* Disable widget initially. */
        setEnabled(false);
}

void
InfoWidget::reinitialize(const Input *input)
{
        /* Reinitialize patient informations. */
        patientLineEdit->setText(input->getPatient().c_str());
        patientLineEdit->setCursorPosition(0);
        
        /* Reinitialize recording informations. */
        recordingLineEdit->setText(input->getRecording().c_str());
        recordingLineEdit->setCursorPosition(0);

        /* Reinitialize starting date and time informations. */
        startingLineEdit->setText(QDateTime(QDate(input->getYear(), input->getMonth(), input->getDay()), QTime(input->getHour(), input->getMinute(), input->getSecond())).toString());
        startingLineEdit->setCursorPosition(0);

        /* Enable widget. */
        setEnabled(true);
}

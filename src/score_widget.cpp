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

//!\file score_widget.cpp
//!Definition of ScoreWidget class.

#include "score_widget.h"

ScoreWidget::ScoreWidget(QWidget *parent)
        : QGroupBox(tr("Score"), parent)
{
        /* Initialize input signal sampling frequency. */
        frequency = 0;

        /* Create score related widgets. */
        QLabel *scoreLabel = new QLabel(tr("Score"), this);
        scoreComboBox = new QComboBox(this);
        scoreComboBox->setEditable(false);
        scoreComboBox->setToolTip(tr("Score mapped"));
        connect(scoreComboBox, SIGNAL(activated(int)), SLOT(slotScoreActivated(int)));

        /* Create window related widgets. */
        windowLabel = new QLabel(tr("Window"), this);
        windowComboBox = new QComboBox(this);
        windowComboBox->setEditable(false);
        windowComboBox->setToolTip(tr("Number of samples for Fourier transform"));
        connect(windowComboBox, SIGNAL(activated(int)), SLOT(slotWindowActivated(int)));

        /* Create frequency related widgets. */
        frequencyLabel = new QLabel(tr("Frequency"), this);
        frequencySpinBox = new QSpinBox(this);
        frequencySpinBox->setToolTip(tr("Frequency mapped for DFT scores"));
        connect(frequencySpinBox, SIGNAL(valueChanged(int)), SLOT(slotFrequencyChanged(int)));

        /* Create widget layout. */
        QGridLayout *layout = new QGridLayout(this);
        layout->setMargin(5);
        layout->setSpacing(3);
        layout->addWidget(scoreLabel, 0, 0);
        layout->addWidget(scoreComboBox, 0, 1);
        layout->addWidget(windowLabel, 1, 0);
        layout->addWidget(windowComboBox, 1, 1);
        layout->addWidget(frequencyLabel, 2, 0);
        layout->addWidget(frequencySpinBox, 2, 1);

        /* Disable widget initially. */
        setEnabled(false);
}

void
ScoreWidget::reinitialize(const Input *input)
{
        int last = input->getLast();

        /* Reinitialize score related widgets. */
        scoreComboBox->clear();
        scoreComboBox->addItem(tr("Raw potential (uV)"));
        if (last >= 127) {
                scoreComboBox->addItem(tr("DFT amplitude (uV)"));
                scoreComboBox->addItem(tr("DFT phase (radians)"));
        }

        /* Reinitialize window related widgets. */
        windowLabel->setEnabled(false);
        windowComboBox->clear();
        if (last >= 127)
                windowComboBox->addItem(tr("128 samples"));
        if (last >= 255)
                windowComboBox->addItem(tr("256 samples"));
        if (last >= 511)
                windowComboBox->addItem(tr("512 samples"));
        windowComboBox->setEnabled(false);

        /* Reinitialize frequency related widgets. */
        frequency = input->getFrequency();
        frequencyLabel->setEnabled(false);
        frequencySpinBox->setEnabled(false);
        frequencySpinBox->setRange(0, (int) ((frequency / 2 - 1 <= 127) ? frequency / 2 - 1 : 127));
        frequencySpinBox->setValue(10);

        /* Enable widget. */
        setEnabled(true);
}

Input::Score
ScoreWidget::getScore() const
{
        /* Return current score from score selection widget. */
        switch (scoreComboBox->currentIndex()) {
        case 0:
                return Input::RAW_POTENTIAL;

        case 1:
                return Input::DFT_AMPLITUDE;

        case 2:
                return Input::DFT_PHASE;
        }

        return Input::RAW_POTENTIAL;
}

int
ScoreWidget::getWindow() const
{
        /* Return current window from window selection widget. */
        switch (windowComboBox->currentIndex()) {
        case 0:
                return 128;

        case 1:
                return 256;

        case 2:
                return 512;
        }

        return 128;
}

int
ScoreWidget::getFrequency() const
{
        /* Return current frequency from frequency selection widget. */
        return frequencySpinBox->value();
}

void
ScoreWidget::slotScoreActivated(int)
{
        Input::Score score = getScore();

        /* Enable or disable window and frequency related widgets
           according to current score. */
        switch (score) {
        case Input::RAW_POTENTIAL:
                windowLabel->setEnabled(false);
                windowComboBox->setEnabled(false);
                frequencyLabel->setEnabled(false);
                frequencySpinBox->setEnabled(false);
                break;

        case Input::DFT_AMPLITUDE:
        case Input::DFT_PHASE:
                windowLabel->setEnabled(true);
                windowComboBox->setEnabled(true);
                frequencyLabel->setEnabled(true);
                frequencySpinBox->setEnabled(true);
                break;
        }

        /* Notify observers on change. */
        emit changed();
}

void
ScoreWidget::slotWindowActivated(int)
{
        /* Adjust frequency selection widget range. */
        int window = getWindow();
        frequencySpinBox->setRange(0, (int) ((frequency / 2 - 1 <= window - 1) ? frequency / 2 - 1 : window - 1));

        /* Notify observers on change. */
        emit changed();
}

void
ScoreWidget::slotFrequencyChanged(int)
{
        /* Notify observers on change. */
        emit changed();
}

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

//!\file time_widget.cpp
//!Definition of TimeWidget class.

#include "time_widget.h"

TimeWidget::TimeWidget(QWidget *parent)
        : QGroupBox(tr("Time"), parent)
{
        /* Initialize indices of first, last and current set of samples
           and sampling frequency of input signal. */
        first = last = current = 0;
        frequency = 0;

        /* Create sampling frequency widgets. */
        QLabel *samplingFrequencyLabel = new QLabel(tr("Sampling frequency"), this);
        samplingFrequencyLineEdit = new QLineEdit(this);
        samplingFrequencyLineEdit->setFocusPolicy(Qt::NoFocus);
        samplingFrequencyLineEdit->setReadOnly(true);
        samplingFrequencyLineEdit->setToolTip(tr("Input signal sampling rate"));
        QLabel *hzLabel = new QLabel(tr("Hz"));

        /* Create current time widgets. */
        QLabel *currentTimeLabel = new QLabel(tr("Current time"), this);
        currentTimeSpinBox = new QDoubleSpinBox(this);
        currentTimeSpinBox->setDecimals(3);
        currentTimeSpinBox->setToolTip(tr("Current animation time"));
        connect(currentTimeSpinBox, SIGNAL(valueChanged(double)), SLOT(slotCurrentTimeChanged(double)));
        QLabel *secLabel = new QLabel(tr("sec"));

        /* Create animation step widgets. */
        QLabel *stepLabel = new QLabel(tr("Step"), this);
        stepSpinBox = new QSpinBox(this);
        stepSpinBox->setToolTip(tr("Number of samples to advance during each animation step"));
        QLabel *samplesLabel = new QLabel(tr("samples"));

        /* Create animation buttons. */
        QButtonGroup *buttonGroup = new QButtonGroup(this);
        buttonGroup->setExclusive(true);
        QPushButton *playButton = new QPushButton(QIcon(":/images/play.png"), tr("Play"), this);
        playButton->setCheckable(true);
        playButton->setToolTip(tr("Play animation"));
        connect(playButton, SIGNAL(toggled(bool)), SLOT(slotPlayButtonToggled(bool)));
        buttonGroup->addButton(playButton);
        pauseButton = new QPushButton(QIcon(":/images/pause.png"), tr("Pause"), this);
        pauseButton->setCheckable(true);
        pauseButton->setToolTip(tr("Pause animation"));
        connect(pauseButton, SIGNAL(toggled(bool)), SLOT(slotPauseButtonToggled(bool)));
        buttonGroup->addButton(pauseButton);
        stopButton = new QPushButton(QIcon(":/images/stop.png"), tr("Stop"), this);
        stopButton->setCheckable(true);
        stopButton->setToolTip(tr("Stop animation"));
        connect(stopButton, SIGNAL(toggled(bool)), SLOT(slotStopButtonToggled(bool)));
        buttonGroup->addButton(stopButton);

        /* Create animation speed widgets. */
        QLabel *slowerLabel = new QLabel(tr("Slower"), this);
        speedSlider = new QSlider(Qt::Horizontal, this);
        speedSlider->setRange(10, 1000);
        speedSlider->setToolTip(tr("Animation speed"));
        speedSlider->setValue(510);
        connect(speedSlider, SIGNAL(valueChanged(int)), SLOT(slotSpeedChanged(int)));
        QLabel *fasterLabel = new QLabel(tr("Faster"), this);

        /* Create layout for animation buttons. */
        QHBoxLayout *midLayout = new QHBoxLayout;
        midLayout->setSpacing(3);
        midLayout->addStretch(1);
        midLayout->addWidget(playButton);
        midLayout->addWidget(pauseButton);
        midLayout->addWidget(stopButton);
        midLayout->addStretch(1);

        /* Create layout for animation speed widgets. */
        QHBoxLayout *bottomLayout = new QHBoxLayout;
        bottomLayout->setSpacing(3);
        bottomLayout->addStretch(1);
        bottomLayout->addWidget(slowerLabel);
        bottomLayout->addWidget(speedSlider);
        bottomLayout->addWidget(fasterLabel);
        bottomLayout->addStretch(1);

        /* Create widget layout. */
        QGridLayout *layout = new QGridLayout(this);
        layout->setMargin(5);
        layout->setSpacing(3);
        layout->addWidget(samplingFrequencyLabel, 0, 0);
        layout->addWidget(samplingFrequencyLineEdit, 0, 1);
        layout->addWidget(hzLabel, 0, 2);
        layout->addWidget(currentTimeLabel, 1, 0);
        layout->addWidget(currentTimeSpinBox, 1, 1);
        layout->addWidget(secLabel, 1, 2);
        layout->addWidget(stepLabel, 2, 0);
        layout->addWidget(stepSpinBox, 2, 1);
        layout->addWidget(samplesLabel, 2, 2);
        layout->addLayout(midLayout, 3, 0, 1, 3);
        layout->addLayout(bottomLayout, 4, 0, 1, 3);

        /* Create timer. */
        timer = new QTimer(this);
        timer->setInterval(500);
        connect(timer, SIGNAL(timeout()), SLOT(slotTimeout()));

        /* Disable widget initially. */
        setEnabled(false);
}

void
TimeWidget::reinitialize(const Input *input)
{
        /* Reinitialize indices of first, last and current set of
           samples and sampling frequency of input signal. */
        first = 0;
        last = input->getLast();
        current = 0;
        frequency = input->getFrequency();

        /* Reinitialize sampling frequency, current time and animation
           step related widgets. */
        samplingFrequencyLineEdit->setText(QString::number(frequency));
        samplingFrequencyLineEdit->setCursorPosition(0);
        if (frequency != 0)
                currentTimeSpinBox->setRange(first / frequency, last / frequency);
        else
                currentTimeSpinBox->setRange(0, 0);
        stepSpinBox->setRange(1, last - first);

        /* Enable widget. */
        setEnabled(true);

        /* Toggle stop button. */
        stopButton->toggle();
}

void
TimeWidget::setFirst(const int first)
{
        /* Remember index of first set of samples. */
        this->first = first;

        /* Adjust current time and animation step ranges. */
        if (frequency != 0)
                currentTimeSpinBox->setRange(first / frequency, last / frequency);
        else
                currentTimeSpinBox->setRange(0, 0);
        stepSpinBox->setRange(1, last - first);
}

int
TimeWidget::getCurrent() const
{
        /* Return index of current set of samples. */
        return current;
}

void
TimeWidget::slotCurrentTimeChanged(double value)
{
        /* Calculate new index of current set of samples. */
        current = (int) (value * frequency + 0.5);
        if (current < first)
                current = first;
        else if (current > last)
                current = last;

        /* Notify observers on change. */
        emit changed();
}

void
TimeWidget::slotPlayButtonToggled(bool checked)
{
        /* Handle pressing button down only. */
        if (!checked)
                return;

        /* Disable current time and animation step selection widget and
           start timer. */
        currentTimeSpinBox->setReadOnly(true);
        stepSpinBox->setReadOnly(true);
        timer->start();
}
 
void
TimeWidget::slotPauseButtonToggled(bool checked)
{
        /* Handle pressing button down only. */
        if (!checked)
                return;

        /* Enable current time and animation step selection widget and
           stop timer. */
        currentTimeSpinBox->setReadOnly(false);
        stepSpinBox->setReadOnly(false);
        timer->stop();
}

void
TimeWidget::slotStopButtonToggled(bool checked)
{
        /* Handle pressing button down only. */
        if (!checked)
                return;

        /* Enable current time and animation step selection widget and
           stop timer. */
        currentTimeSpinBox->setReadOnly(true);
        stepSpinBox->setReadOnly(true);
        timer->stop();

        /* Return to first set of samples. */
        current = first;
        currentTimeSpinBox->setValue((frequency != 0) ? current / frequency : 0);
}

void
TimeWidget::slotSpeedChanged(int value)
{
        /* Adjust timer interval. */
        timer->setInterval(1010 - value);
}

void
TimeWidget::slotTimeout()
{
        /* Adjust index of current set of samples. */
        current += stepSpinBox->value();
        if (current < first)
                current = first;
        else if (current > last)
                current = last;
        currentTimeSpinBox->setValue((frequency != 0) ? current / frequency : 0);

        /* Pause animation if elapsed. */
        if (current == last)
                pauseButton->toggle();
}

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

//!\file time_widget.h
//!Declaration of TimeWidget class.

#ifndef TIME_WIDGET_H
#define TIME_WIDGET_H 1

#include "input.h"
#include <QtCore>
#include <QtGui>

//! Time parameters widget.
/*!
 * This class represents widget displaying and controlling animation
 * time-related parameters.
 */
class TimeWidget : public QGroupBox
{
        Q_OBJECT

 public:
        /*!
         * Construct an object of TimeWidget class given parent widget.
         */
        TimeWidget(QWidget * = 0);

        /*!
         * Reinitialize widget contents when new input supplied.
         */
        void reinitialize(const Input *);

        /*!
         * Set index of first set of samples for animation.
         */
        void setFirst(const int);

        /*!
         * Return index of current set of samples.
         */
        int getCurrent() const;

 signals:
        /*!
         * Signal emitted when some of time parameters changed.
         */
        void changed();

 private:
        /*!
         * Indices of first, last and current set of samples.
         */
        int first, last, current;

        /*!
         * Sampling frequency of input signal.
         */
        float frequency;

        /*!
         * Sampling frequency information widget.
         */
        QLineEdit *samplingFrequencyLineEdit;

        /*!
         * Current time selection widget.
         */
        QDoubleSpinBox *currentTimeSpinBox;

        /*!
         * Animation step selection widget.
         */
        QSpinBox *stepSpinBox;

        /*!
         * Animation controlling buttons.
         */
        QPushButton *pauseButton, *stopButton;

        /*!
         * Animation speed selection widget.
         */
        QSlider *speedSlider;

        /*!
         * Timer controlling animation.
         */
        QTimer *timer;

 private slots:
        /*!
         * Handle current time selection widget change.
         */
        void slotCurrentTimeChanged(double);

        /*!
         * Handle play button pressing.
         */
        void slotPlayButtonToggled(bool);

        /*!
         * Handle pause button pressing.
         */
        void slotPauseButtonToggled(bool);

        /*!
         * Handle stop button pressing.
         */
        void slotStopButtonToggled(bool);

        /*!
         * Handle animation speed selection widget change.
         */
        void slotSpeedChanged(int);

        /*!
         * Handle timeout event.
         */
        void slotTimeout();
};

#endif

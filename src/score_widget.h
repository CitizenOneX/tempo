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

//!\file score_widget.h
//!Declaration of ScoreWidget class.

#ifndef SCORE_WIDGET_H
#define SCORE_WIDGET_H 1

#include "input.h"
#include <QtCore>
#include <QtGui>
#include <QComboBox>
#include <QLabel>
#include <QSpinBox>
#include <QGroupBox>
#include <QGridLayout>

//! Score parameters widget.
/*!
 * This class represents widget controlling score related parameters of
 * mapping.
 */
class ScoreWidget : public QGroupBox
{
        Q_OBJECT

 public:
        /*!
         * Construct an object of ScoreWidget class given parent widget.
         */
        ScoreWidget(QWidget * = 0);

        /*!
         * Reinitialize widget contents when new input supplied.
         */
        void reinitialize(const Input *);

        /*!
         * Return current score.
         */
        Input::Score getScore() const;

        /*!
         * Return current DFT window length.
         */
        int getWindow() const;

        /*!
         * Return current frequency for DFT scores.
         */
        int getFrequency() const;

 signals:
        /*!
         * Signal emitted when some of score parameters changed.
         */
        void changed();

 private:
        /*!
         * Sampling frequency of input signal.
         */
        float frequency;

        /*!
         * Current score selection widget.
         */
        QComboBox *scoreComboBox;

        /*!
         * Current DFT window label.
         */
        QLabel *windowLabel;

        /*!
         * Current DFT window selection widget.
         */
        QComboBox *windowComboBox;

        /*!
         * Current frequency label.
         */
        QLabel *frequencyLabel;

        /*!
         * Current frequency selection widget.
         */
        QSpinBox *frequencySpinBox;

 private slots:
        /*!
         * Handle current score selection widget change.
         */
        void slotScoreActivated(int);

        /*!
         * Handle current window selection widget change.
         */
        void slotWindowActivated(int);

        /*!
         * Handle current frequency selection widget change.
         */
        void slotFrequencyChanged(int);
};

#endif

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

//!\file main_widget.h
//!Declaration of MainWidget class.

#ifndef MAIN_WIDGET_H
#define MAIN_WIDGET_H 1

#include <vector>
#include "info_widget.h"
#include "input.h"
#include "interpolation.h"
#include "legend_widget.h"
#include "manual_widget.h"
#include "scene.h"
#include "score_widget.h"
#include "sensors.h"
#include "time_widget.h"
#include "visualization_widget.h"
#include <QtCore>
#include <QtGui>

//! Application main widget.
/*!
 * This class represents main widget of TEMPO application.
 */
class MainWidget : public QWidget
{
        Q_OBJECT

 public:
        /*!
         * Construct an object of InfoWidget class given parent widget.
         */
        MainWidget(QWidget * = 0);

        /*!
         * Class destructor.
         */
        ~MainWidget();

 private:
        /*!
         * Count of random data points used to estimate score minimal
         * and maximal value.
         */
        static const int COUNT;

        /*!
         * Scale used to multiply estimated score minimal and maximal
         * value to calculate allowed range for adjusting score minimal
         * and maximal value.
         */
        static const int SCALE;

        /*!
         * Scene description object.
         */
        Scene *scene;

        /*!
         * Sensors set object.
         */
        Sensors *sensors;

        /*!
         * Input dataset object.
         */
        Input *input;

        /*!
         * Interpolation of sampled values object.
         */
        Interpolation *interpolation;

        /*!
         * Estimated total range of score values and range of these
         * values represented by color spectrum.
         */
        std::vector<float> lowest, low, high, highest;

        /*!
         * Index of current score into arrays of ranges of score values.
         */
        int index;

        /*!
         * Score visualization widget.
         */
        VisualizationWidget *visualizationWidget;

        /*!
         * Recording information widget.
         */
        InfoWidget *infoWidget;

        /*!
         * Score parameters widget.
         */
        ScoreWidget *scoreWidget;

        /*!
         * Mapping legend widget.
         */
        LegendWidget *legendWidget;

        /*!
         * Time parameters widget.
         */
        TimeWidget *timeWidget;

        /*!
         * On-line manual widget.
         */
        ManualWidget manualWidget;

        /*!
         * Calculating total range of score values and range of these
         * values represented by color spectrum for current score, if
         * these not calculated already.
         */
        void updateLegendRanges();

 private slots:
        /*!
         * Handle open command.
         */
        void slotOpen();

        /*!
         * Handle save command.
         */
        void slotSave();

        /*!
         * Handle manual command.
         */
        void slotManual();

        /*!
         * Handle score parameters change.
         */
        void slotScoreChanged();

        /*!
         * Handle legend parameters change.
         */
        void slotLegendChanged();

        /*!
         * Handle time parameters change.
         */
        void slotTimeChanged();

        /*!
         * Update widget contents.
         */
        void slotUpdate();
};

#endif

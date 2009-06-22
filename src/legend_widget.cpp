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

//!\file legend_widget.cpp
//!Definition of LegendWidget class.

#include "legend_widget.h"

LegendWidget::LegendWidget(QWidget *parent)
        : QGroupBox(tr("Legend"), parent)
{
        /* Create lowest mapped score value related widgets. */
        QLabel *lowLabel = new QLabel(tr("Low"), this);
        lowSpinBox = new QDoubleSpinBox(this);
        lowSpinBox->setDecimals(2);
        lowSpinBox->setToolTip(tr("Score value mapped to legend lefmost color"));
        lowSpinBox->setValue(lowSpinBox->minimum());
        connect(lowSpinBox, SIGNAL(valueChanged(double)), SLOT(slotLowValueChanged(double)));

        /* Create gradient widget. */
        gradientWidget = new GradientWidget(this);
        gradientWidget->setToolTip(tr("Color map"));

        /* Create highest mapped score value related widgets. */
        highSpinBox = new QDoubleSpinBox(this);
        highSpinBox->setDecimals(2);
        highSpinBox->setToolTip(tr("Score value mapped to legend rightmost color"));
        highSpinBox->setValue(highSpinBox->maximum());
        connect(highSpinBox, SIGNAL(valueChanged(double)), SLOT(slotHighValueChanged(double)));
        QLabel *highLabel = new QLabel(tr("High"), this);

        /* Create widget layout. */
        QHBoxLayout *layout = new QHBoxLayout(this);
        layout->setMargin(5);
        layout->setSpacing(3);
        layout->addStretch(1);
        layout->addWidget(lowLabel);
        layout->addWidget(lowSpinBox);
        layout->addWidget(gradientWidget);
        layout->addWidget(highSpinBox);
        layout->addWidget(highLabel);
        layout->addStretch(1);

        /* Disable widget initially. */
        setEnabled(false);
}

void
LegendWidget::reinitialize(const Interpolation *interpolation)
{
        /* Pass interpolation object to gradient widget. */
        gradientWidget->setInterpolation(interpolation);
        
        /* Enable widget. */
        setEnabled(true);
}

void
LegendWidget::getRange(float *low, float *high) const
{
        /* Return lowest and highest mapped score values. */
        *low = lowSpinBox->value();
        *high = highSpinBox->value();
}

void
LegendWidget::setRange(const float lowest, const float low, const float high, const float highest)
{
        /* Set ranges and values of lowest and higest mapped score
           values selection widgets according to given score values
           range and score mapped values range. */
        lowSpinBox->setRange(lowest, high);
        lowSpinBox->setValue(low);
        highSpinBox->setRange(low, highest);
        highSpinBox->setValue(high);
}

void
LegendWidget::slotLowValueChanged(double value)
{
        /* Set current lowest mapped score value to highest mapped score
           value selection widget minimum. */
        highSpinBox->setMinimum(value);

        /* Notify observers on change. */
        emit changed();
}

void
LegendWidget::slotHighValueChanged(double value)
{
        /* Set current highest mapped score value to lowest mapped score
           value selection widget maximum. */
        lowSpinBox->setMaximum(value);

        /* Notify observers on change. */
        emit changed();
}

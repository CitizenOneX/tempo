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

//!\file main_widget.cpp
//!Definion of MainWidget class.

#include <cstdlib>
#include <cmath>
#include <limits>
#include "main_widget.h"

#define DATA_DIRECTORY "data"
#define FACE_FILENAME "face.mo"
#define SCALP_FILENAME "scalp.mo"
#define SENSORS_FILENAME "10_10.ms"

const int MainWidget::COUNT = 64;
const int MainWidget::SCALE = 2;

MainWidget::MainWidget(QWidget *parent)
        : QWidget(parent)
{
        /* Initialize random number generator. */
        srand(0);

        /* Set widget caption. */
        setWindowTitle(tr("TEMPO"));

        /* Create scene and sensors objects, initialize input and
           interpolation objects. */
        scene = new Scene(QString(qApp->applicationDirPath() + "/" DATA_DIRECTORY "/" SCALP_FILENAME).toStdString(), QString(qApp->applicationDirPath() + "/" DATA_DIRECTORY "/" FACE_FILENAME).toStdString());
        sensors = new Sensors(QString(qApp->applicationDirPath() + "/" DATA_DIRECTORY "/" SENSORS_FILENAME).toStdString());
        input = 0;
        interpolation = 0;

        /* Initalize index of current score into arrays of ranges of
           score values. */
        index = -1;

        /* Create visualization widget. */
        visualizationWidget = new VisualizationWidget(scene, this);

        /* Create info widget. */
        infoWidget = new InfoWidget(this);

        /* Create score widget. */
        scoreWidget = new ScoreWidget(this);
        connect(scoreWidget, SIGNAL(changed()), SLOT(slotScoreChanged()));

        /* Create legend widget. */
        legendWidget = new LegendWidget(this);
        connect(legendWidget, SIGNAL(changed()), SLOT(slotLegendChanged()));

        /* Create time widget. */
        timeWidget = new TimeWidget(this);
        connect(timeWidget, SIGNAL(changed()), SLOT(slotTimeChanged()));

        /* Create command buttons. */
        QPushButton *openButton = new QPushButton(QIcon(":/images/open.png"), tr("&Open"), this);
        openButton->setToolTip(tr("Open EDF file"));
        connect(openButton, SIGNAL(clicked()), SLOT(slotOpen()));
        QPushButton *saveButton = new QPushButton(QIcon(":/images/save.png"), tr("&Save"), this);
        saveButton->setToolTip(tr("Save current map in PNG format"));
        connect(saveButton, SIGNAL(clicked()), SLOT(slotSave()));
        QPushButton *manualButton = new QPushButton(QIcon(":/images/manual.png"), tr("&Manual"), this);
        manualButton->setToolTip(tr("Show on-line manual"));
        connect(manualButton, SIGNAL(clicked()), SLOT(slotManual()));
        QPushButton *quitButton = new QPushButton(QIcon(":/images/quit.png"), tr("&Quit"), this);
        quitButton->setDefault(true);
        quitButton->setToolTip(tr("Quit application"));
        connect(quitButton, SIGNAL(clicked()), qApp, SLOT(quit()));

        /* Create layout for command buttons. */
        QHBoxLayout *bottomRightLayout = new QHBoxLayout;
        bottomRightLayout->setSpacing(3);
        bottomRightLayout->addWidget(openButton);
        bottomRightLayout->addWidget(saveButton);
        bottomRightLayout->addWidget(manualButton);
        bottomRightLayout->addStretch(1);
        bottomRightLayout->addWidget(quitButton);

        /* Create layout for parameters displaying and selection
           widgets. */
        QVBoxLayout *rightLayout = new QVBoxLayout;
        rightLayout->setSpacing(3);
        rightLayout->addWidget(infoWidget);
        rightLayout->addWidget(scoreWidget);
        rightLayout->addWidget(legendWidget);
        rightLayout->addWidget(timeWidget);
        rightLayout->addStretch(1);
        rightLayout->addLayout(bottomRightLayout);

        /* Create widget layout. */
        QHBoxLayout *layout = new QHBoxLayout(this);
        layout->setMargin(5);
        layout->setSpacing(3);
        layout->addWidget(visualizationWidget);
        layout->addLayout(rightLayout);
}

MainWidget::~MainWidget()
{
        /* Destroy scene, sensors, input and interpolation objects. */
        delete scene;
        delete sensors;
        delete input;
        delete interpolation;
}

void
MainWidget::updateLegendRanges()
{
        /* Check if input object available. */
        if (!input)
                return;

        /* Remember current score lowest and highest mapped value. */
        if (index != -1)
                legendWidget->getRange(&low[index], &high[index]);

        /* Get current score and frequency. */
        Input::Score score = scoreWidget->getScore();
        int frequency = scoreWidget->getFrequency();

        /* Calculate index into arrays of ranges of score values for
           current score. */
        switch (score) {
        case Input::RAW_POTENTIAL:
                index = 0;
                break;

        case Input::DFT_AMPLITUDE:
                index = 1 + frequency;
                break;

        case Input::DFT_PHASE:
                index = 1 + ((int) (input->getFrequency() / 2)) + frequency;
                break;
        }

        /* If not already, estimate ranges of values for current
           score. */
        if (lowest[index] == std::numeric_limits<float>::max()) {
                int count = input->getCount();
                int last = input->getLast();
                int window = 128;
                std::vector<float> values;
                int i, j;

                /* Estimate ranges according to score. */
                switch(score) {
                case Input::RAW_POTENTIAL:
                        /* Calculate number of data values for given
                           score and use minimal and maximal values
                           among these as basis for estimation. */
                        for (i = 0; i < COUNT; i++) {
                                values = input->getValues(score, (int) (std::rand() / (RAND_MAX + 1.0) * last));
                                for (j = 0; j < count; j++) {
                                        if (low[index] > values[j])
                                                low[index] = values[j];
                                        else if (high[index] < values[j])
                                                high[index] = values[j];
                                }
                        }
                        if (std::fabs(low[index]) < std::fabs(high[index]))
                                low[index] = -high[index];
                        else
                                high[index] = -low[index];
                        lowest[index] = SCALE * low[index];
                        highest[index] = SCALE * high[index];
                        break;
                                
                case Input::DFT_AMPLITUDE:
                        /* Calculate number of data values for given
                           score and use maximal value among these as
                           basis for estimation (minimal value for this
                           score is always 0). */
                        lowest[index] = low[index] = 0;
                        for (i = 0; i < COUNT; i++) {
                                values = input->getValues(score, 127 + (int) (std::rand() / (RAND_MAX + 1.0) * (last - 128)), window, frequency);
                                for (j = 0; j < count; j++)
                                        if (high[index] < values[j])
                                                high[index] = values[j];
                        }
                        highest[index] = SCALE * high[index];
                        break;

                case Input::DFT_PHASE:
                        /* This score values are always in [-pi,pi]
                           range. */
                        lowest[index] = low[index] = -M_PI;
                        high[index] = highest[index] = M_PI;
                        break;
                }
        }

        /* Set range of legend widget according to calculated/remembered
           range for current score. */
        legendWidget->setRange(lowest[index], low[index], high[index], highest[index]);
}

void
MainWidget::slotOpen()
{
        /* Get name of file to open. */
        QString filename = QFileDialog::getOpenFileName(this, tr("Open file"), QDir::currentPath(), tr("EDF files (*.edf)"));
        if (filename.isNull())
                return;

        /* Delete current input and interpolation objects. */
        delete input;
        delete interpolation;

        /* Create new input and interpolation objects. */
        input = new Input(filename.toStdString(), *sensors);
        interpolation = new Interpolation(scene->getMapped().getVertices(), *input);

        /* Reinitialize variables related to minimal and maximal score
           values. */
        int count = (int) (1 + input->getFrequency());
        lowest.resize(count);
        low.resize(count);
        high.resize(count);
        highest.resize(count);
        for (int i = 0; i < count; i++) {
                lowest[i] = low[i] = std::numeric_limits<float>::max();
                high[i] = highest[i] = -std::numeric_limits<float>::max();
        }
        index = -1;

        /* Reinitialize widgets. */
        infoWidget->reinitialize(input);
        scoreWidget->reinitialize(input);
        legendWidget->reinitialize(interpolation);
        timeWidget->reinitialize(input);

        /* Update ranges for color legend. */
        updateLegendRanges();

        /* Change widget caption. */
        setWindowTitle(tr("TEMPO - ") + filename);

        /* Schedule widget update. */
        QTimer::singleShot(0, this, SLOT(slotUpdate()));
}

void
MainWidget::slotSave()
{
        /* Get name of file to save. */
        QString filename = QFileDialog::getSaveFileName(this, tr("Save map"), QDir::currentPath(), tr("PNG files (*.png)"));
        if (filename.isNull())
                return;
        
        /* Save current map into given file */
        visualizationWidget->grabFrameBuffer().save(filename, "png");
}

void
MainWidget::slotManual()
{
        /* Show manual widget. */
        manualWidget.show();
}

void
MainWidget::slotScoreChanged()
{
        /* Update ranges for color legend. */
        updateLegendRanges();

        /* Update index of first set of samples. */
        switch (scoreWidget->getScore()) {
        case Input::RAW_POTENTIAL:
                timeWidget->setFirst(0);
                break;

        case Input::DFT_AMPLITUDE:
        case Input::DFT_PHASE:
                timeWidget->setFirst(scoreWidget->getWindow() - 1);
                break;
        }

        /* Schedule widget update. */
        QTimer::singleShot(0, this, SLOT(slotUpdate()));
}

void
MainWidget::slotLegendChanged()
{
        /* Schedule widget update. */
        QTimer::singleShot(0, this, SLOT(slotUpdate()));
}

void
MainWidget::slotTimeChanged()
{
        /* Schedule widget update. */
        QTimer::singleShot(0, this, SLOT(slotUpdate()));
}

void
MainWidget::slotUpdate()
{
        /* Check if input object available. */
        if (!input)
                return;

        /* Get set of current score values. */
        std::vector<float> values;
        Input::Score score = scoreWidget->getScore();
        int current = timeWidget->getCurrent();
        int window, frequency;
        switch(score) {
        case Input::RAW_POTENTIAL:
                values = input->getValues(score, current);
                break;

        case Input::DFT_AMPLITUDE:
        case Input::DFT_PHASE:
                window = scoreWidget->getWindow();
                frequency = scoreWidget->getFrequency();
                values = input->getValues(score, current, window, frequency);
                break;
        }

        /* Interpolate values across all mapped vertices. */
        float low, high;
        legendWidget->getRange(&low, &high);
        interpolation->process(values, low, high);

        /* Schedule visualization widget repaint. */
        QTimer::singleShot(0, visualizationWidget, SLOT(updateGL()));
}

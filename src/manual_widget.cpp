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

//!\file manual_widget.cpp
//!Definion of ManualWidget class.

#include "manual_widget.h"

#define MANUAL_DIRECTORY "manual"
#define MANUAL_HOME_PAGE "index.html"

ManualWidget::ManualWidget(QWidget *parent)
        : QWidget(parent)
{
        /* Adjust widget attributes. */
        setAttribute(Qt::WA_GroupLeader);

        /* Create help browser widget. */
        textBrowser = new QTextBrowser(this);
        connect(textBrowser, SIGNAL(sourceChanged(const QUrl &)), SLOT(slotUpdateCaption()));

        /* Create command buttons. */
        QPushButton *backwardButton = new QPushButton(QIcon(":/images/backward.png"), tr("&Backward"), this);
        connect(textBrowser, SIGNAL(backwardAvailable(bool)), backwardButton, SLOT(setEnabled(bool)));
        connect(backwardButton, SIGNAL(clicked()), textBrowser, SLOT(backward()));
        QPushButton *forwardButton = new QPushButton(QIcon(":/images/forward.png"), tr("&Forward"), this);
        connect(textBrowser, SIGNAL(forwardAvailable(bool)), forwardButton, SLOT(setEnabled(bool)));
        connect(forwardButton, SIGNAL(clicked()), textBrowser, SLOT(forward()));
        QPushButton *homeButton = new QPushButton(QIcon(":/images/home.png"), tr("&Home"), this);
        connect(homeButton, SIGNAL(clicked()), textBrowser, SLOT(home()));
        QPushButton *closeButton = new QPushButton(QIcon(":/images/close.png"), tr("&Close"), this);
        closeButton->setDefault(true);
        connect(closeButton, SIGNAL(clicked()), SLOT(hide()));

        /* Create layout for command buttons. */
        QHBoxLayout *topLayout = new QHBoxLayout;
        topLayout->setSpacing(3);
        topLayout->addWidget(backwardButton);
        topLayout->addWidget(forwardButton);
        topLayout->addWidget(homeButton);
        topLayout->addStretch(1);
        topLayout->addWidget(closeButton);

        /* Create widget layout. */
        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->setMargin(5);
        layout->setSpacing(3);
        layout->addWidget(textBrowser);
        layout->addLayout(topLayout);
        
        /* Set manual home page. */
        textBrowser->setSource(QUrl::fromLocalFile(qApp->applicationDirPath() + "/" MANUAL_DIRECTORY "/" MANUAL_HOME_PAGE));
}

QSize
ManualWidget::minimumSizeHint() const
{
        /* Return mimimum size. */
        return QSize(320, 240);
}

QSize
ManualWidget::sizeHint() const
{
        /* Return preferred size. */
        return QSize(480, 320);
}

void
ManualWidget::slotUpdateCaption()
{
        /* Set manual widget caption according to current manual page
           title. */
        setWindowTitle(tr("TEMPO Manual - ") + textBrowser->documentTitle());
}

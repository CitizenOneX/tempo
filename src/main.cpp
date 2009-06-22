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

/*!
 * \mainpage TEMPO
 *
 * TEMPO (Topographic Eeg Mapping Program) is software for 3D
 * visualization of brain electrical activity.
 */

//!\file main.cpp
//!Definition of main() function.

#include <iostream>
#include "exception.h"
#include "main_widget.h"
#include <QtGui>

int
main(int argc, char **argv)
{
        int value;

        try {
                /* Create application object. */
                QApplication application(argc, argv);

                /* Create and show application main widget. */
                MainWidget mainWidget;
                mainWidget.show();

                /* Enter application main loop. */
                value = application.exec();
        }
        catch (Exception exception) {
                /* Report exception caught. */
                std::cerr << "Error type #" << (int) exception.getType() << std::endl;
        }

        return value;
}

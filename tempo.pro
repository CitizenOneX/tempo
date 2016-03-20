CONFIG      += debug qt stl warn_on
MOC_DIR      = tmp
OBJECTS_DIR  = tmp
QT          += widgets opengl
LIBS        += -lopengl32 -lGLU32
RCC_DIR      = tmp
TARGET       = tempo
TEMPLATE     = app

HEADERS      = src/bounding_box.h \
               src/color.h \
               src/exception.h \
               src/fft.h \
               src/gradient_widget.h \
               src/info_widget.h \
               src/input.h \
               src/interpolation.h \
               src/legend_widget.h \
               src/main_widget.h \
               src/manual_widget.h \
               src/material.h \
               src/object.h \
               src/quaternion.h \
               src/rotation.h \
               src/scene.h \
               src/score_widget.h \
               src/sensors.h \
               src/signal.h \
               src/time_widget.h \
               src/triangle.h \
               src/vector.h \
               src/vertex.h \
               src/visualization_widget.h

RESOURCES    = resources/tempo.qrc

SOURCES      = src/bounding_box.cpp \
               src/color.cpp \
               src/exception.cpp \
               src/fft.cpp \
               src/gradient_widget.cpp \
               src/info_widget.cpp \
               src/input.cpp \
               src/interpolation.cpp \
               src/legend_widget.cpp \
               src/main.cpp \
               src/main_widget.cpp \
               src/manual_widget.cpp \
               src/material.cpp \
               src/object.cpp \
               src/quaternion.cpp \
               src/rotation.cpp \
               src/scene.cpp \
               src/score_widget.cpp \
               src/sensors.cpp \
               src/signal.cpp \
               src/time_widget.cpp \
               src/triangle.cpp \
               src/vector.cpp \
               src/vertex.cpp \
               src/visualization_widget.cpp

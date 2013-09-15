
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

HEADERS += \
    flyer.h \
    playerPlane.h \
    global.h \
    flightvehicle.h \
    bloodsupply.h \
    randomizer.h \
    bullet.h \
    flypath.h \
    space.h \
    bulletfactory.h \
    frame.h \
    scoringdevice.h \
    menuitem.h \
    customitem.h \
    menuwidget.h \
    textitem.h \
    bulletsupply.h \
    enemyplane.h \
    bomb.h

SOURCES += \
    playerPlane.cpp \
    bloodsupply.cpp \
    randomizer.cpp \
    bullet.cpp \
    main.cpp \
    space.cpp \
    bulletfactory.cpp \
    scoringdevice.cpp \
    menuitem.cpp \
    customitem.cpp \
    menuwidget.cpp \
    textitem.cpp \
    bulletsupply.cpp \
    enemyplane.cpp \
    bomb.cpp

OTHER_FILES += \
    备注 \
    README \

RESOURCES += \
    image.qrc

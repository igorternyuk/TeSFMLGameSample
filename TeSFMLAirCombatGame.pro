TEMPLATE = app
CONFIG += c++1z
CONFIG -= app_bundle
CONFIG -= qt
LIBS += `pkg-config --libs sfml-all`
SOURCES += main.cpp \
    game.cpp \
    entity.cpp \
    aircraft.cpp \
    scenenode.cpp \
    world.cpp \
    spritenode.cpp \
    command.cpp \
    commandqueue.cpp \
    player.cpp \
    category.cpp

HEADERS += \
    game.hpp \
    resourcemanager.hpp \
    entity.hpp \
    aircraft.hpp \
    scenenode.hpp \
    world.hpp \
    spritenode.hpp \
    resourceindentifiers.hpp \
    category.hpp \
    command.hpp \
    commandqueue.hpp \
    player.hpp

DISTFILES += \
    resourcemanager.impl

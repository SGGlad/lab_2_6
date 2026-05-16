TEMPLATE = app
CONFIG += console c++20
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        item.cpp \

HEADERS += \
    ../nlohman/json.hpp \
    item.hpp

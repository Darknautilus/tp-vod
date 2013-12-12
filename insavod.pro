QT += network
QMAKE_CXXFLAGS += -std=c++0x
CONFIG += qt
TARGET = bin/insavod
HEADERS += Server.h \
					fenetreServ.h
SOURCES += insavod.cpp \
					Server.cpp \
					fenetreServ.cpp

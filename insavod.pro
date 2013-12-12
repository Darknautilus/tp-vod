QT += network
QMAKE_CXXFLAGS += -std=c++0x
CONFIG += qt
TARGET = bin/insavod
HEADERS += httpServer.h \
					fenetreServ.h \
					insavodServer.h
SOURCES += insavod.cpp \
					httpServer.cpp \
					fenetreServ.cpp \
					insavodServer.cpp

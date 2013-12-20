QT += network
QMAKE_CXXFLAGS += -std=c++0x
CONFIG += qt
TARGET = bin/insavod
HEADERS += httpServer.h \
					fenetreServ.h \
					insavodServer.h \
					insavodTcpServer.h \
				 	insavodUdpServer.h	
SOURCES += insavod.cpp \
					httpServer.cpp \
					fenetreServ.cpp \
					insavodServer.cpp \
					insavodTcpServer.cpp \
				 	insavodUdpServer.cpp

######################################################################
# Automatically generated by qmake (3.0) ?? ???. 14 15:58:18 2015
######################################################################

TEMPLATE = app
TARGET = tower_of_hanoi
INCLUDEPATH += .

CONFIG += debug gui

# Input
HEADERS += visualizer.h console_visualizer.h rods.h hanoi_puzzle_algorithm.h tower_of_hanoi_console.h hanoi_thread.h
SOURCES += main.cpp visualizer.cpp console_visualizer.cpp rods.cpp hanoi_puzzle_algorithm.cpp tower_of_hanoi_console.cpp hanoi_thread.cpp

CONFIG (gui) {
	HEADERS += main_window.h rod_widget.h
	SOURCES += main_window.cpp rod_widget.cpp
	QMAKE_CXXFLAGS += -DGUI_HANOI
}

QT += widgets core
QMAKE_CXXFLAGS += -std=c++11
RESOURCES += 

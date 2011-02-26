SOURCES += sources/main.cpp \
    sources/Core/FunctionManager.cpp \
    sources/Core/FunctionsView.cpp \
    sources/Data/ItemData.cpp \
    sources/Data/MathTools.cpp \
    sources/Rendering/FunctionGraphics.cpp \
    sources/Rendering/FunctionItem.cpp \
    sources/Rendering/FunctionRender.cpp \
    sources/Rendering/Grid.cpp \
    sources/Rendering/PointRender.cpp \
    sources/Rendering/SurfaceRender.cpp \
    sources/Rendering/TangentRender.cpp \
    sources/UserControls/CalcButton.cpp \
    sources/UserControls/XPositionBar.cpp \
    sources/Windows/AboutBox.cpp \
    sources/Windows/MainWindow.cpp
HEADERS += sources/Core/FunctionManager.h \
    sources/Core/FunctionsView.h \
    sources/Data/ItemData.h \
    sources/Data/MathTools.h \
    sources/Rendering/FunctionGraphics.h \
    sources/Rendering/FunctionItem.h \
    sources/Rendering/FunctionRender.h \
    sources/Rendering/Grid.h \
    sources/Rendering/PointRender.h \
    sources/Rendering/SurfaceRender.h \
    sources/Rendering/TangentRender.h \
    sources/UserControls/CalcButton.h \
    sources/UserControls/XPositionBar.h \
    sources/Windows/AboutBox.h \
    sources/Windows/MainWindow.h
INCLUDEPATH += sources \
    lib \
    lib/Parser \
    lib/Expression
RESOURCES += resources.qrc
LIBS += Parser.dll \
    Expression.dll
RC_FILE += Effex.rc

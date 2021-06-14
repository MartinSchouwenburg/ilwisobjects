#-------------------------------------------------
#
# Project created by QtCreator 2021-03-23T10:50:24
#
#-------------------------------------------------

TARGET = ilwisscript
TEMPLATE = lib

DEFINES += ILWISSCRIPT_LIBRARY

include(../global.pri)
INCLUDEPATH += ./include \
               ./include/ast \
               ./include/parserlexer

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES +=  \
    source/ast/addnode.cpp \
    source/ast/assignmentnode.cpp \
    source/ast/astnode.cpp \
    source/ast/breaknode.cpp \
    source/ast/commandnode.cpp \
    source/ast/domainformatter.cpp \
    source/ast/expressionnode.cpp \
    source/ast/formatter.cpp \
    source/ast/functionnode.cpp \
    source/ast/functionstatementnode.cpp \
    source/ast/idnode.cpp \
    source/ast/ifnode.cpp \
    source/ast/multiplicationnode.cpp \
    source/ast/operationnodescript.cpp \
    source/ast/outparametersnode.cpp \
    source/ast/parametersnode.cpp \
    source/ast/relationnode.cpp \
    source/ast/returnnode.cpp \
    source/ast/scriptlinenode.cpp \
    source/ast/scriptnode.cpp \
    source/ast/selectnode.cpp \
    source/ast/selectornode.cpp \
    source/ast/termnode.cpp \
    source/ast/valuerangenode.cpp \
    source/ast/variablenode.cpp \
    source/ast/whilenode.cpp \
    source/ilwisscript.cpp \
    source/parserlexer/bridge.cpp \
    source/parserlexer/ilwisscriptLexer.cpp \
    source/parserlexer/ilwisscriptParser.cpp \
    source/parserlexer/runtimechecks.cpp \
    source/ilwisscriptmodule.cpp

win32 {
SOURCES += \
    source/parserlexer/antlr3baserecognizer.c \
    source/parserlexer/antlr3basetree.c \
    source/parserlexer/antlr3basetreeadaptor.c \
    source/parserlexer/antlr3bitset.c \
    source/parserlexer/antlr3collections.c \
    source/parserlexer/antlr3commontoken.c \
    source/parserlexer/antlr3commontree.c \
    source/parserlexer/antlr3commontreeadaptor.c \
    source/parserlexer/antlr3commontreenodestream.c \
    source/parserlexer/antlr3convertutf.c \
    source/parserlexer/antlr3cyclicdfa.c \
    source/parserlexer/antlr3debughandlers.c \
    source/parserlexer/antlr3encodings.c \
    source/parserlexer/antlr3exception.c \
    source/parserlexer/antlr3filestream.c \
    source/parserlexer/antlr3inputstream.c \
    source/parserlexer/antlr3intstream.c \
    source/parserlexer/antlr3lexer.c \
    source/parserlexer/antlr3parser.c \
    source/parserlexer/antlr3rewritestreams.c \
    source/parserlexer/antlr3string.c \
    source/parserlexer/antlr3tokenstream.c \
    source/parserlexer/antlr3treeparser.c \
}

HEADERS +=  \
    include/IlwisScriptLexer.h \
    include/parserlexer/bridge.h \
    include/parserlexer/ilwisscriptLexer.h \
    include/parserlexer/ilwisscriptParser.h \
    source/ilwisscript.g\
    include/ast/addnode.h \
    include/ast/assignmentnode.h \
    include/ast/astnode.h \
    include/ast/breaknode.h \
    include/ast/commandnode.h \
    include/ast/domainformatter.h \
    include/ast/expressionnode.h \
    include/ast/formatter.h \
    include/ast/formatters.h \
    include/ast/functionnode.h \
    include/ast/functionstatementnode.h \
    include/ast/idnode.h \
    include/ast/ifnode.h \
    include/ast/multiplicationnode.h \
    include/ast/operationnodescript.h \
    include/ast/outparametersnode.h \
    include/ast/parametersnode.h \
    include/ast/relationnode.h \
    include/ast/returnnode.h \
    include/ast/scriptlinenode.h \
    include/ast/scriptnode.h \
    include/ast/selectnode.h \
    include/ast/selectornode.h \
    include/ast/termnode.h \
    include/ast/valuerangenode.h \
    include/ast/variablenode.h \
    include/ast/whilenode.h \
    include/ilwisscript.h \
    include/ilwisscriptParser.h \
    include/ilwisscriptmodule.h

win32 {
SOURCES += \
    include/parserlexer/antlr3.h \
    include/parserlexer/antlr3baserecognizer.h \
    include/parserlexer/antlr3basetree.h \
    include/parserlexer/antlr3basetreeadaptor.h \
    include/parserlexer/antlr3bitset.h \
    include/parserlexer/antlr3collections.h \
    include/parserlexer/antlr3commontoken.h \
    include/parserlexer/antlr3commontree.h \
    include/parserlexer/antlr3commontreeadaptor.h \
    include/parserlexer/antlr3commontreenodestream.h \
    include/parserlexer/antlr3config.h \
    include/parserlexer/antlr3convertutf.h \
    include/parserlexer/antlr3cyclicdfa.h \
    include/parserlexer/antlr3debugeventlistener.h \
    include/parserlexer/antlr3defs.h \
    include/parserlexer/antlr3encodings.h \
    include/parserlexer/antlr3errors.h \
    include/parserlexer/antlr3exception.h \
    include/parserlexer/antlr3filestream.h \
    include/parserlexer/antlr3input.h \
    include/parserlexer/antlr3interfaces.h \
    include/parserlexer/antlr3intstream.h \
    include/parserlexer/antlr3lexer.h \
    include/parserlexer/antlr3memory.h \
    include/parserlexer/antlr3parser.h \
    include/parserlexer/antlr3parsetree.h \
    include/parserlexer/antlr3recognizersharedstate.h \
    include/parserlexer/antlr3rewritestreams.h \
    include/parserlexer/antlr3string.h \
    include/parserlexer/antlr3tokenstream.h \
    include/parserlexer/antlr3treeparser.h \
}

DISTFILES += \
    ilwisscript.json \
    include/IlwisScript.tokens \
    include/parserlexer/ilwisscript.tokens
linux {
LIBS += -L$$OUTPUTPATH/ -lantlr3c
}

LIBS += -L$$OUTPUTPATH/ -lilwiscore

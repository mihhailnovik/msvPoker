######################################################################
# Automatically generated by qmake (2.01a) Fri Nov 6 12:33:33 2009
######################################################################

TEMPLATE = app
TARGET = client
DEPENDPATH += . src/gui
INCLUDEPATH += .

# Gui
HEADERS += src/gui/TableRowWidget.h src/gui/LoginWidget.h src/gui/TableChoseWidget.h src/gui/TableListWidget.h src/gui/elements/MsvQPushButton.h src/gui/GameMainWidget.h src/gui/PlayerInfoWidget.h src/gui/elements/LCDRange.h
SOURCES += src/Main.cpp src/gui/TableRowWidget.cpp src/gui/LoginWidget.cpp src/gui/TableChoseWidget.cpp src/gui/TableListWidget.cpp src/gui/elements/MsvQPushButton.cpp src/gui/GameMainWidget.cpp src/gui/PlayerInfoWidget.cpp src/gui/elements/LCDRange.cpp

# Model
HEADERS += src/model/PokerPlayerModel.h src/model/MsvServerMessage.h src/model/AuthInfoModel.h src/model/MsvEnvironment.h src/model/game_engine/PokerRoomModel.h src/model/JoinTableInfoModel.h src/model/PlayerJoinChairModel.h src/model/game_engine/CardModel.h
SOURCES += src/model/PokerPlayerModel.cpp src/model/MsvServerMessage.cpp src/model/AuthInfoModel.cpp src/model/MsvEnvironment.cpp src/model/game_engine/PokerRoomModel.cpp src/model/JoinTableInfoModel.cpp src/model/PlayerJoinChairModel.cpp src/model/game_engine/CardModel.cpp

#Service
HEADERS += src/service/LoginService.h src/service/ServerInfoService.h src/model/ServerInfoModel.h src/service/GameService.h
SOURCES += src/service/LoginService.cpp src/service/ServerInfoService.cpp src/model/ServerInfoModel.cpp src/service/GameService.cpp

#utils
HEADERS += src/utils/SocketHolder.h src/utils/ServiceHolder.h src/utils/MessageBuilder.h src/utils/MessageTransformer.h src/utils/XmlParserHelper.h src/gui/WidgetHelper.h src/utils/StringUtil.h src/utils/CardSuiteUtil.h
SOURCES += src/utils/SocketHolder.cpp src/utils/ServiceHolder.cpp src/utils/MessageBuilder.cpp src/utils/MessageTransformer.cpp src/utils/XmlParserHelper.cpp src/gui/WidgetHelper.cpp src/utils/StringUtil.cpp src/utils/CardSuiteUtil.cpp

CONFIG += console
QT += network
QT += xml
RESOURCES += application.qrc

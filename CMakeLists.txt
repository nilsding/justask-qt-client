project(justask-qt-client)
cmake_minimum_required(VERSION 2.6)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

find_package(Qt4 REQUIRED)
find_package(QJSON REQUIRED)

set(lang translations/de.ts)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR} ${QJSON_INCLUDE_DIR})

set(sources mainwindow.cpp settingsdialog.cpp main.cpp)
set(headers mainwindow.h settingsdialog.h)
set(forms mainwindow.ui settingsdialog.ui)

qt4_wrap_cpp(headers_moc ${headers})
qt4_wrap_ui(forms_headers ${forms})
qt4_add_translation(translations ${lang})

add_executable(justask-qt-client ${sources} ${headers_moc} ${forms_headers} ${translations})
target_link_libraries(justask-qt-client ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${QT_QTNETWORK_LIBRARIES} ${QJSON_LIBRARIES})
install(TARGETS justask-qt-client RUNTIME DESTINATION bin)

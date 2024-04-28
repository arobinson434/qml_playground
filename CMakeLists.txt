cmake_minimum_required(VERSION 3.16)

project(ModelTest VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick Gui)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable( ModelTest
    src/main.cpp
    src/controller/TestModel.h
)

qt_add_qml_module( ModelTest
    RESOURCE_PREFIX /
    URI gui
    QML_FILES
        qml/main.qml
)

#target_compile_definitions(ModelTest PUBLIC QT_QML_DEBUG QT_DECLARATIVE_DEBUG)
target_link_libraries(ModelTest PRIVATE Qt6::Gui Qt6::Quick)


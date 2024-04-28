import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Window {
    width: 200
    height: 400
    visible: true

    required property var testCtlr

    ColumnLayout {
        anchors.fill: parent

        ListView {
            Layout.fillWidth: true
            Layout.fillHeight: true

            model: testCtlr.model
            delegate: Text {
                text: "Name: "+name+"; Value: "+value

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        value++
                    }
                }
            }
        }

        Button {
            text: "Add"
            palette.buttonText: "black"
            Layout.fillWidth: true

            onClicked: {
                testCtlr.model.addData("Tim", 21);
            }
        }
    }
}

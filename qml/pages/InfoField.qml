
import QtQuick 2.0
import Sailfish.Silica 1.0

Item {
    id: item
    property alias label: label.text
    property alias value: value.text
    property real fontpixelSize: Theme.fontSizeLarge
    property color textColour: Theme.highlightColor
    anchors.left: parent.left
    anchors.leftMargin: Theme.paddingMedium
    anchors.right: parent.right
    anchors.rightMargin: Theme.paddingMedium
    height:80
    Label {
        id: label
        color: parent.textColour
        font.pixelSize: fontpixelSize
        text: "Label"
    }
    Label {
        id: value
        font.pixelSize: fontpixelSize
        color: parent.textColour
        text: "Value"
        anchors.right: parent.right
    }
}


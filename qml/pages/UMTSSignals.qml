import QtQuick 2.0
import Sailfish.Silica 1.0

Page {

    // The effective value will be restricted by ApplicationWindow.allowedOrientations
    allowedOrientations: Orientation.All

    // To enable PullDownMenu, place our content in a SilicaFlickable
    SilicaFlickable {
        anchors.fill: parent

        // Tell SilicaFlickable the height of its content.
        contentHeight: column.height

        Column {
               id:column
               anchors.fill: parent
               PageHeader {
                title: "UMTS Signals"
               }

               // Table Header
               Row {
                   width: parent.width
                   spacing: 10
                   height: 80

                   Rectangle {
                       width: parent.width / 3
                       height: 80
                       color: Theme.backgroundGlowColor
                       Label {
                           anchors.centerIn: parent
                           text: "PSC"
                           font.bold: true
                           color: Theme.primaryColor
                       }
                   }

                   Rectangle {
                       width: parent.width / 3
                       height: 80
                       color: Theme.backgroundGlowColor
                       Label {
                           anchors.centerIn: parent
                           text: "UARFCN"
                           font.bold: true
                           color: Theme.primaryColor
                       }
                   }

                   Rectangle {
                       width: parent.width / 3
                       height: 80
                       color: Theme.backgroundGlowColor
                       Label {
                           anchors.centerIn: parent
                           text: "Signal Strength"
                           font.bold: true
                           color: Theme.primaryColor
                       }
                   }
               }

               SilicaListView {
                    width: parent.width; height: 1600
                    model: umtsSignals
                    delegate: ListItem {
                        width: parent.width
                        height: Theme.itemSizeSmall
                       Row {
                           width: parent.width
                           spacing: 10
                           height: 80
                       Rectangle {
                           width: parent.width / 3
                           height: 80
                           color: Theme.backgroundGlowColor
                           Label {
                           anchors.centerIn: parent
                           text: PSC
                           color: Serving ? Theme.highlightColor : Theme.secondaryColor
                           }
                       }
                       Rectangle {
                           width: parent.width / 3
                           height: 80
                           color: Theme.backgroundGlowColor
                           Label {
                           anchors.centerIn: parent
                           text: UARFCN
                           color: Serving ? Theme.highlightColor : Theme.secondaryColor
                           }
                       }
                       Rectangle {
                           width: parent.width / 3
                           height: 80
                           color: Theme.backgroundGlowColor
                           Label {
                           anchors.centerIn: parent
                           text: SignalStrength
                           color: Serving ? Theme.highlightColor : Theme.secondaryColor
                           }
                       }
                       }
                    }
                }

           }
    }
}

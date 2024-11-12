import QtQuick 2.0
import Sailfish.Silica 1.0
import co.uk.solotel 1.0


Page {
    id: page
    property CellWatcher watcher

    // The effective value will be restricted by ApplicationWindow.allowedOrientations
    allowedOrientations: Orientation.All

    PageHeader {
        id: pageHeader
        title: "Network Monitor"
    }

    Button {
                text: "LTE Neighbours"
                anchors.horizontalCenter: parent.horizontalCenter
                onClicked: pageStack.push(Qt.resolvedUrl("LTESignals.qml"))
            }

    Component {
           id: sectionHeading
           Rectangle {
               width: ListView.view.width
               height: childrenRect.height
               color: Theme.highlightBackgroundColor
               Column {
                   Text {
                   text: section
                   font.bold: true
                   font.pixelSize: Theme.fontSizeMedium
                   }
                   Row {
                       Loader {
                           source: "ColumnHeadings" + section + ".qml"
                       }
                   }
               }
           }
       }

    TechSelector {
        id: lteModel
        model: dmodel
        filterGroup: "lte"
        delegate:
            InfoField {
                 label: model.name
                 value: model.signal
                 textColour: model.active ? Theme.highlightColor : Theme.secondaryColor
                 ListView.onAdd: AddAnimation {
                     target: lteMeasuresList
                 }
                 ListView.onRemove: RemoveAnimation {
                     target: lteMeasuresList
                 }
             }
    }

    TechSelector {
        id: gsmModel
        model: dmodel
        filterGroup: "gsm"
        delegate:
            InfoField {
                 label: model.name
                 value: model.signal
                 textColour: model.active ? Theme.highlightColor : Theme.secondaryColor
                 ListView.onAdd: AddAnimation {
                     target: gsmMeasuresList
                 }
                 ListView.onRemove: RemoveAnimation {
                     target: gsmMeasuresList
                 }
             }
    }

    TechSelector {
        id: wcdmaModel
        model: dmodel
        filterGroup: "wcdma"
        delegate:
            InfoField {
                 label: model.name
                 value: model.signal
                 textColour: model.active ? Theme.highlightColor : Theme.secondaryColor
                 ListView.onAdd: AddAnimation {
                     target: wcdmaMeasuresList
                 }
                 ListView.onRemove: RemoveAnimation {
                     target: wcdmaMeasuresList
                 }
             }
    }

    SilicaFlickable {
             anchors.fill: parent

             Label {
                id: serveLabel
                font.pixelSize: Theme.fontSizeExtraLarge
                font.family: Theme.fontFamilyHeading
                padding: Theme.paddingMedium
                color: Theme.secondaryColor
                text: dmodel.tech
                anchors.left: parent.left
                onTextChanged: {
                    console.log("Serving Cell Changed")
                    console.log(dmodel.tech);
                    if (dmodel.tech=="LTE"){
                        serveLoader.source="./LTEServingCell.qml"
                    }
                    if (dmodel.tech=="WCDMA"){
                        serveLoader.source="./UMTSServingCell.qml"
                    }
                    if (dmodel.tech=="GSM"){
                        serveLoader.source="./GSMServingCell.qml"
                    }
                }
             }

             Loader {
                 anchors.top: serveLabel.bottom
                 id: serveLoader
                 width: parent.width
                 height: 300
                 source : "LTEServingCell.qml"}

             Label {
                id: lteMeasLabel
                anchors.top:serveLoader.bottom
                font.pixelSize: Theme.fontSizeLarge
                font.family: Theme.fontFamilyHeading
                padding: Theme.paddingMedium
                color: Theme.secondaryColor
                text: "LTE"
             }

            Column{
            anchors.top:lteMeasLabel.bottom
            anchors.right:parent.right
            anchors.left:parent.left

            Repeater {
            id: lteMeasuresList
            model: lteModel.filteredModel
            anchors.top:lteMeasLabel.bottom
            anchors.right:parent.right
            anchors.left:parent.left
        }

            Label {
            id: wcdmaMeasLabel
            font.pixelSize: Theme.fontSizeLarge
            font.family: Theme.fontFamilyHeading
            padding: Theme.paddingMedium
            color: Theme.secondaryColor
            text: "WCDMA"
            }

        Repeater {
        id: wcdmaMeasuresList
        model: wcdmaModel.filteredModel
        anchors.right:parent.right
        anchors.left:parent.left
        height: 400
        clip: true
    }
            Label {
            font.pixelSize: Theme.fontSizeLarge
            font.family: Theme.fontFamilyHeading
            padding: Theme.paddingMedium
            color: Theme.secondaryColor
            text: "GSM"
            }

        Repeater {
        id: gsmMeasuresList
        model: gsmModel.filteredModel
        anchors.right:parent.right
        anchors.left:parent.left
        height: 400
        clip: true

    }


}
}
}


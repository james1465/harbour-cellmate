import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: page

    // The effective value will be restricted by ApplicationWindow.allowedOrientations
    allowedOrientations: Orientation.All

    // To enable PullDownMenu, place our content in a SilicaFlickable
    SilicaFlickable {
        anchors.fill: parent

        // PullDownMenu and PushUpMenu must be declared in SilicaFlickable, SilicaListView or SilicaGridView
        PullDownMenu {
            MenuItem {
                text: qsTr("Start Recording")
                visible: logger.isRecording == false
                onClicked: pageStack.push(Qt.resolvedUrl("StartRecording.qml"),
                                          {"name": "Start Recording"})
            }
            MenuItem {
                text: qsTr("Finish Recording")
                visible: logger.isRecording
                onClicked: pageStack.push(Qt.resolvedUrl("FinishRecording.qml"))
            }
            MenuItem {
                text: qsTr("LTE Measurements")
                onClicked: pageStack.push(Qt.resolvedUrl("LTESignals.qml"))
            }
            MenuItem {
                text: qsTr("UMTS Measurements")
                onClicked: pageStack.push(Qt.resolvedUrl("UMTSSignals.qml"))
            }
            MenuItem {
                text: qsTr("GSM Measurements")
                onClicked: pageStack.push(Qt.resolvedUrl("GSMSignals.qml"))
        }
        }

        // Tell SilicaFlickable the height of its content.
        contentHeight: column.height

        Column {
            id: column

            width: page.width
            spacing: Theme.paddingLarge
            PageHeader {
                title: qsTr("Serving Cell")
            }

            InfoField {
                label: qsTr('Radio Tech')
                visible: true
                value: serving.rat
            }

            InfoField {
                label: qsTr('MCC')
                visible: true
                value: serving.mcc
            }
            InfoField {
                label: qsTr('MNC')
                visible: true
                value: serving.mnc
            }
            InfoField {
                label: qsTr('Signal Level (Dbm)')
                visible: true
                value: serving.signalLevelDbm
            }
            InfoField {
                label: qsTr('ARFCN')
                visible: serving.rat == "GSM"
                value: serving.arfcn
            }
            InfoField {
                label: qsTr('BSIC')
                visible: serving.rat == "GSM"
                value: serving.bsic
            }
            InfoField {
                label: qsTr('Cell ID')
                visible: serving.rat == "GSM" || serving.rat =="UMTS"
                value: serving.cid
            }
            InfoField {
                label: qsTr('LAC')
                visible: serving.rat == "GSM" || serving.rat =="UMTS"
                value: serving.lac
            }
            InfoField {
                label: qsTr('Bit Error Rate')
                visible: serving.rat == "GSM" || serving.rat =="UMTS"
                value: serving.bitErrorRate
            }
            InfoField {
                label: 'PSC'
                visible: serving.rat == "UMTS"
                value: serving.psc
            }
            InfoField {
                label: 'UARFCN'
                visible: serving.rat == "UMTS"
                value: serving.uarfcn
            }
            InfoField {
                label: qsTr('PCI')
                visible: serving.rat == "LTE" || serving.rat == "NR"
                value: serving.pci
            }
            InfoField {
                label: qsTr('TAC')
                visible: serving.rat == "LTE" || serving.rat == "NR"
                value: serving.tac
            }
            InfoField {
                label: qsTr('Cell ID')
                visible: serving.rat == "LTE"
                value: serving.ci
            }
            InfoField {
                label: qsTr('EARFCN')
                visible: serving.rat == "LTE"
                value: serving.earfcn
            }
            InfoField {
                label: qsTr('RSRP')
                visible: serving.rat == "LTE"
                value: serving.rsrp
            }
            InfoField {
                label: qsTr('RSRQ')
                visible: serving.rat == "LTE"
                value: serving.rsrq
            }
            InfoField {
                label: qsTr('RSSNR')
                visible: serving.rat == "LTE"
                value: serving.rssnr
            }
            InfoField {
                label: qsTr('CQI')
                visible: serving.rat == "LTE"
                value: serving.cqi
            }
            InfoField {
                label: qsTr('Timing Advance')
                visible: serving.rat == "LTE"
                value: serving.timingAdvance
            }
            InfoField {
                label: qsTr('nciString')
                visible: serving.rat == "NR"
                value: serving.nciString
            }
            InfoField {
                label: qsTr('nrarfcn')
                visible: serving.rat == "NR"
                value: serving.nrarfcn
            }
            InfoField {
                label: 'ssRsrp'
                visible: serving.rat == "NR"
                value: serving.ssRsrp
            }
            InfoField {
                label: 'ssRsrq'
                visible: serving.rat == "NR"
                value: serving.ssRsrq
            }
            InfoField {
                label: qsTr('ssSinr')
                visible: serving.rat == "NR"
                value: serving.ssSinr
            }
            InfoField {
                label: qsTr('csiRsrp')
                visible: serving.rat == "NR"
                value: serving.csiRsrp
            }
            InfoField {
                label: qsTr('csiRsrq')
                visible: serving.rat == "NR"
                value: serving.csiRsrq
            }
            InfoField {
                label: qsTr('csiSinr')
                visible: serving.rat == "NR"
                value: serving.csiSinr
            }
            InfoField {
                label: qsTr('Longitude')
                value: location.longitude
            }
            InfoField {
                label: qsTr('Latitude')
                value: location.latitude
            }
            Label {
                horizontalAlignment: Text.AlignHCenter
                x: Theme.horizontalPageMargin
                text: qsTr("Pull Down For More")
                color: Theme.secondaryHighlightColor
                font.pixelSize: Theme.fontSizeExtraLarge
            }
        }
    }
}

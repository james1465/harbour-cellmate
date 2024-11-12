import QtQuick 2.0
import QtQuick 2.2
import Sailfish.Silica 1.0
import Sailfish.Pickers 1.0

Dialog {
    property string name
    property string targetPath

    Column {
        width: parent.width

        DialogHeader {
            title : "Finish Recording"
        }
        TextField {
            id: nameField
            width: parent.width
            label: "Name"
            text: logger.filename
            readOnly: True
        }
    }


    onDone: {
        if (result == DialogResult.Accepted) {
            logger.stopRecording();
        }
    }

    }

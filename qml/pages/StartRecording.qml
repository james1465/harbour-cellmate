import QtQuick 2.2
import Sailfish.Silica 1.0
import Sailfish.Pickers 1.0

Dialog {
    id: startRecording
    property string name
    property string directoryPath : StandardPaths.documents

    Column {
        width: parent.width

        // Four Cannot read property (of ...IndicatorDown) get generated here
        // it seems to be an internal silica problem
        DialogHeader {
          id: startRecordingDialog
          title: "Start Recording"
        }
    }

    onDone: {
        if (result == DialogResult.Accepted) {
            logger.startRecording();
        }
    }

}

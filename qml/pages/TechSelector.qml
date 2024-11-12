import QtQuick 2.0

Item {
    property alias model: techDelegateModel.model
    property alias filterGroup: techDelegateModel.filterOnGroup
    property alias filteredModel: techDelegateModel
    property alias delegate: techDelegateModel.delegate
    VisualDataModel {
        id: techDelegateModel


    model: dmodel

        groups: [
            VisualDataGroup {
                id: newCells
                includeByDefault: true
                name: "new"
                onChanged: {
                    console.log("GroupChanged");
                    console.log(newCells.count);
                    var i = newCells.count
                    while (i--) {
                        var newCell = newCells.get(i);
                        console.log(newCell.model.tech);
                        newCells.setGroups(i, 1, newCell.model.tech.toLowerCase());
                    }
                }
            },
            VisualDataGroup {
                id: gsmCells
                includeByDefault: false
                name: "gsm"
            },
            VisualDataGroup {
                id: wcdmaCells
                includeByDefault: false
                name: "wcdma"
            },
            VisualDataGroup {
                id: lteCells
                includeByDefault: false
                name: "lte"
            }
        ]
        filterOnGroup: "wcdma"

    }

}

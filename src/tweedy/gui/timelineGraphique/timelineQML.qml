
import QtQuick 1.0
import "fonction.js" as MyScript

Rectangle {
    id: timeline
    width: 800
    height: 100

    color: "#414042"

    //Component.onCompleted: MyScript.createSpriteObjects(3);

    ListView {
        width:  parent.width
        height:  parent.height
        anchors.fill: parent

        model : timelineData.clips
        delegate : Rectangle {

            width: 25
            height: 100
            radius: model.modelData.radius
        }
    }
}

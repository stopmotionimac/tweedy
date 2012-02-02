
import QtQuick 1.0
import "fonction.js" as MyScript

Rectangle {
    id: timeline
    width: 800
    height: 100

    color: "#414042"

    ListView {
        id:listClips
        width:  parent.width
        height:  parent.height
        anchors.fill: parent
        orientation: "Horizontal"

        model : timelineData.clips

        delegate : Rectangle {
            id:clip
            x: model.modelData.timeIn * 60
            width: (model.modelData.timeOut - model.modelData.timeIn) * 60
            height: 60
            radius: 5
            Image{
                  width:55
                  height:55
                  fillMode: Image.PreserveAspectFit
                  smooth: true
                  source: "../../../../"+model.modelData.imgPath
            }
            MouseArea {
                  anchors.fill: parent
                  drag.target: clip
                  drag.axis: Drag.XAxis
                  onEntered: {
                       var timeInDepart = parent.x / 60
                       timelineData.setTimeInDepart(timeInDepart)
                  }
                  onReleased: {
                       var timeInArrive = parent.x / 60
                       timelineData.dragNdrop(timeInArrive)
                  }
           }//end mousearea
        }//end delegate
    }//end listview
}//end rectangle

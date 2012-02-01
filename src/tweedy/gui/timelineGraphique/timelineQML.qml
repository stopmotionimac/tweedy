
import QtQuick 1.0
import "fonction.js" as MyScript

Rectangle {
    id: timeline
    width: 800
    height: 100

    color: "#414042"

    //Component.onCompleted: MyScript.createSpriteObjects(3);

    Component {
        id: componentDelegate


        Column {
            spacing: 10
            y:10

            Text {
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                width: 100
                height: 10
                color: "#ffffff"
                font.bold: true
                text: index


            }

            Rectangle {

                id: clip
                width: 100
                height: 40
                radius: model.modelData.radius

                gradient: Gradient {
                    GradientStop {
                        position: 0.00;
                        color: "#ffffff";
                    }
                    GradientStop {
                        position: 1.00;
                        color: "#e28a26";
                    }
                }


                MouseArea {
                    anchors.fill: parent
                    drag.target: clip
                    drag.axis: Drag.XAxis
                }
            }


        }
    }

    ListView {
        id: listClips
        width:  parent.width
        height:  parent.height
        anchors.fill: parent
        orientation: "Horizontal"

        model : timelineData.clips
        delegate : componentDelegate

    }
}

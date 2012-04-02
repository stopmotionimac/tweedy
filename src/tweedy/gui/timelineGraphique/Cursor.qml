import QtQuick 1.0

Item {
    id: cursor
    focus: true

    Rectangle {
        id: zoneCursor
        width: 9


        /*Image {
            id: triangle
            source: "img/triangle.qml"
            fillMode: Image.PreserveAspectFit
            smooth: true
            x:0
            y:0
            width: 6
        }*/

        Rectangle {
            id: lineCursor
            x: zoneCursor.x+3
            width: 3
            height: timeline.height

        }

        MouseArea {
            anchors.fill: parent
            drag.target: parent
            drag.axis: Drag.XAxis
            onReleased: {
                lineCursor.color= 'white';
                console.log("onReleased");
                onXChanged: {
                        var xCursor = zoneCursor.x /100;
                        console.log("x curseur : ", xCursor);
                        timelineData.play(xCursor);
                }
            }

            onEntered: {
                lineCursor.color= 'red';
                console.log("toucheeeee");
            }


        }

    }



}

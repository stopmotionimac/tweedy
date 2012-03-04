import QtQuick 1.0

Item {
    id: cursor

    /*Image {
        id: triangle
        source: "img/triangle.qml"
        fillMode: Image.PreserveAspectFit
        smooth: true

    }*/

    Rectangle {
        id: lineCursor
        width: 5
        //x: triangle.width /2 -1
        height: tw_timeline.height
    }

    MouseArea {
        anchors.fill: lineCursor
        drag.target: cursor
        drag.axis: Drag.XAxis
        onReleased: {
            lineCursor.color= 'white';
            console.log("onReleased");
            onXChanged: {
                    var xCursor = cursor.x /100;
                    console.log("x curseur : ", xCursor);
                    tweedyTimelineData.play(xCursor);
            }
        }

        onEntered: {
            lineCursor.color= 'red';
            console.log("toucheeeee");
        }


    }

}

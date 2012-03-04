import QtQuick 1.0

Item {
    id: tw_cursor

    /*Image {
        id: triangle
        source: "img/triangle.qml"
        fillMode: Image.PreserveAspectFit
        smooth: true

    }*/

    Rectangle {
        id: tw_cursorLine
        width: 2
        x: _tw_timelineData.timeIn * tw_timelineScale  //tw_cursorTop.width/2 - width/2
        height: tw_timeline.height
		color: 'white'
    }
    Rectangle {
        id: tw_cursorTop
        width: 10
        height: 20
		color: 'white'
    }
    MouseArea {
        id: tw_cursorHandle
        anchors.fill: tw_cursorTop
        drag.target: tw_cursor
        drag.axis: Drag.XAxis
		
        onReleased: {
            tw_cursorLine.color= 'white';
            tw_cursorTop.color= 'white';
            console.log("onReleased");
        }
        onPositionChanged: {
            var xCursor = tw_cursor.x / tw_timelineScale;
            console.log("onPositionChanged x curseur : ", xCursor);
            _tw_timelineData.play(xCursor);
        }

        onXChanged: {
				var xCursor = tw_cursor.x / tw_timelineScale;
                console.log("onXChanged x curseur : ", xCursor);
				_tw_timelineData.play(xCursor);
		}
        onEntered: {
            tw_cursorLine.color= 'red';
            tw_cursorTop.color= 'red';
            console.log("toucheeeee");
        }


    }

}

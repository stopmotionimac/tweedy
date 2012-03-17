import QtQuick 1.1

Item {
    id: tw_cursor

    /*Image {
        id: triangle
        source: "img/triangle.qml"
        fillMode: Image.PreserveAspectFit
        smooth: true

    }*/
    //x = -tw_cursorTop.width/2

	/*
    Rectangle {
        id: tw_cursorLine
        width: 2
        x: _tw_timelineData.timeIn * _tw_timelineData.timelineScale  //tw_cursorTop.width/2 - width/2
        height: tw_timeline.height
		color: 'white'
    }
	*/
    Rectangle {
        id: tw_cursorTop
        width: 10
        height: 20
        x: _tw_timelineData.timeIn * _tw_timelineData.timelineScale - 5
        color: 'white'
    }
    Rectangle {
        id: tw_cursorLine
        width: 2
        height: tw_timeline.height
        x: _tw_timelineData.timeIn * _tw_timelineData.timelineScale//tw_cursorTop.width/2 - width/2
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
        }
        onPositionChanged: {
            var xCursor = tw_cursor.x / _tw_timelineData.timelineScale;
            //console.log("onPositionChanged x curseur : ", xCursor);
            _tw_timelineData.play(xCursor);
        }
        onEntered: {
            tw_cursorLine.color= 'red';
            tw_cursorTop.color= 'red';
        }


    }

}

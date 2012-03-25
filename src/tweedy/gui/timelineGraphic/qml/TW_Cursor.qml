import QtQuick 1.1

Item {
    id: tw_cursor

    scale: tw_cursorHandle.pressed ? 1.2 : 1.0

    Rectangle {
        id: tw_cursorTop
        width: 10
        height: tw_allTracks.height - tw_track.height - 25
        x: _tw_timelineData.timeIn * _tw_timelineData.timelineScale - 5
        color: 'red'
    }
    Rectangle {
        id: tw_cursorLine
        width: 2
        height: tw_timeline.height
        x: _tw_timelineData.timeIn * _tw_timelineData.timelineScale//tw_cursorTop.width/2 - width/2
        color: 'red'
    }
    MouseArea {
        id: tw_cursorHandle
        anchors.fill: tw_cursorTop
        drag.target: tw_cursor
        drag.axis: Drag.XAxis
		
        onReleased: {
            tw_cursorLine.color= 'red';
            tw_cursorTop.color= 'red';
        }
        onPositionChanged: {
            var xCursor = tw_cursor.x / _tw_timelineData.timelineScale;
            _tw_timelineData.play(xCursor);
        }

        onEntered: {
            tw_cursorLine.color= '#C40101';
            tw_cursorTop.color= '#C40101';
        }


    }

}

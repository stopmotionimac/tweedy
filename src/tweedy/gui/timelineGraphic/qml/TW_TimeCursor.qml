import QtQuick 1.1

Item {
    id: tw_cursor

    scale: tw_cursorHandle.pressed ? 1.2 : 1.0

    Rectangle {
        id: tw_cursorTop
        width: 10
        height: tw_graduation.height
        x: - tw_cursorTop.width/2
        color: 'red'
    }
    Rectangle {
        id: tw_cursorLine
        width: 2
        height: tw_timelineWindow.height - 25
        x: _tw_timelineData.timeIn * _tw_timelineData.timelineScale
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
            _tw_timelineData.displayCurrentClip(xCursor - tw_track.x/ _tw_timelineData.timelineScale);
        }

        onEntered: {
            tw_cursorLine.color= '#C40101';
            tw_cursorTop.color= '#C40101';
        }


    }


}

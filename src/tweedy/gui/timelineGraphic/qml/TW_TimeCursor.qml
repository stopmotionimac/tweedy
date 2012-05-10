import QtQuick 1.1

Item {
    id: tw_cursor

    property int gradHeight

    Rectangle {
        id: tw_cursorTop
        width: 11
        height: tw_graduation.height
        x: - width/2
        color: 'red'
    }
    Rectangle {
        id: tw_cursorLine
        width: 2
        //x: - width/2
        height: tw_graduation.height + tw_track.height
        color: 'red'
    }
}

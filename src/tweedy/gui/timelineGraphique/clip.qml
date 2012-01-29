import QtQuick 1.0

Rectangle {
    id: clip
    width: 100
    height: 62
    gradient: Gradient {
        GradientStop {
            position: 0
            color: "#ffffff"
        }

        GradientStop {
            position: 1
            color: "#ff8800"
        }
    }

    MouseArea {
        anchors.fill: parent
        drag.target: clip
        drag.axis: Drag.XAxis

        MouseArea {
            id: zoneAgrandissementClip
            width: 10
            height: clip.height
            x: clip.x
            y: clip.y

            onEntered: { color: 'red' }
        }
    }

}

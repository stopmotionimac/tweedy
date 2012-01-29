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
    }

    MouseArea {
        id: areaScaleLeft
        width: 10
        height: clip.height
        hoverEnabled: true

        onEntered: {
            aaa.AfficheCurseur("scale");
        }
        onExited: {
            aaa.AfficheCurseur("none")
          }
    }

    MouseArea {
        id: areaScaleRight
        width: 10
        height: clip.height
        x:clip.width - areaScaleLeft.width
        hoverEnabled: true

        onEntered: {
            aaa.AfficheCurseur("scale");
        }
        onExited: {
            aaa.AfficheCurseur("none")
          }
    }

}

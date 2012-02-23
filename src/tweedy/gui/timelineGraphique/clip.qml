import QtQuick 1.0
//import MyClipData 1.0


Rectangle {
    id: clip
    width: 100
    height: 60
    border.color: "black"
    radius: 10

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

    /* drag and drop horizontal */
    MouseArea {
        anchors.fill: parent
        drag.target: clip
        drag.axis: Drag.XAxis

        acceptedButtons: Qt.LeftButton | Qt.RightButton
        onPressed: {
            if (mouse.button == Qt.RightButton)
                console.log("Bouton de souris cliqué")
        }
    }

    //si x change on affiche dans la console
    onXChanged: {
        Prop.afficheXClip(5.0)
        console.log("La position horizontal est maintenant :", x)
    }


    MouseArea {
        id: areaScaleLeft
        width: 10
        height: clip.height
        hoverEnabled: true

        onEntered: {
            Prop.afficheCurseur("scale");
        }
        onExited: {
            Prop.afficheCurseur("none")
          }
    }

    MouseArea {
        id: areaScaleRight
        width: 10
        height: clip.height
        x:clip.width - areaScaleLeft.width
        hoverEnabled: true

        onEntered: {
            Prop.afficheCurseur("scale");
        }
        onExited: {
            Prop.afficheCurseur("none")
        }
    }

}

import QtQuick 1.0

Rectangle {
    id: myTimeline
    width: 1000
    height: 500
    color: "#414042"

	
	Component {
		id: clipDelegate

		Rectangle {
			id: myClip
            width: parent.parent.width
			height: model.realSize * 10
			border.color: "black"
			border.width: 2
			radius: 10
            color:"red"

            Text {
				id: myClipText
				text: "Animal: " + model.type + ", " + model.size + "."
			}

			MouseArea {
				id:dragNdrop
                anchors.fill: parent
				acceptedButtons: Qt.LeftButton | Qt.RightButton

                onReleased: {
					console.log("qml myClip onReleased.")
					var posInBox = myClip.mapToItem(myTimeline, mouse.x, mouse.y)
					myClipText.text =
						'Pressed'
						+ '\n'
						+ 'button= ' + mouse.button + " " + (mouse.button == Qt.RightButton ? 'right' : 'left')
						+ '\n'
						+ 'shift=' + (mouse.modifiers & Qt.ShiftModifier ? 'true' : 'false')
						+ '\n'
						+ 'mouse x: ' + mouse.x + ", " + mouse.y
						+ '\n'
						+ 'mouse int timeline x: ' + posInBox.x + ", " + posInBox.y
                    if( mouse.button == Qt.LeftButton )
                    {
                        console.log("qml asks to add a data.")
						myQmlWrapper.add()
                    }
                    else
                    {
                        console.log("qml asks to remove a data.")
						myQmlWrapper.remove();
                    }
				}
			}
            
            Component.onCompleted: {
                console.log("qml myClip completed !")
            }

		}//end Rectangle
	}//end Component

	ListView {
        //width: 200; height: 250
        anchors.fill: parent

		Connections {
			target: myQmlWrapper
			onDataChanged: {
				console.log("qml - item onDataChanged "  + model.type + ", " + model.size)
			}
		}

		model: myQmlWrapper.animalModel
		delegate: clipDelegate
	}

}

import QtQuick 1.0

Rectangle {
	id: myContainer
	width: 1000
	height: 500
	color: "#414042"


	Component {
		id: myItemDelegate
		
		Rectangle {
			id: myClip
			width: parent.parent.width
			height: object.bSize * 10
			border.color: "black"
			border.width: 2
			radius: 10
			color:"red"

			Text {
				id: myClipText
				text: "a: " + object.a + ", b: " + object.b + "."
			}

			MouseArea {
				id:dragNdrop
				anchors.fill: parent
				acceptedButtons: Qt.LeftButton | Qt.RightButton

				onReleased: {
					console.log("qml myClip onReleased.")
					var posInContainer = myClip.mapToItem(myContainer, mouse.x, mouse.y)
					myClipText.text =
						'Pressed'
						+ '\n'
						+ 'button= ' + mouse.button + " " + (mouse.button == Qt.RightButton ? 'right' : 'left')
						+ '\n'
						+ 'shift=' + (mouse.modifiers & Qt.ShiftModifier ? 'true' : 'false')
						+ '\n'
						+ 'mouse x: ' + mouse.x + ", " + mouse.y
						+ '\n'
						+ 'mouse in myContainer x: ' + posInContainer.x + ", " + posInContainer.y
					if( mouse.button == Qt.LeftButton )
					{
						console.log("qml asks to add a data.")
						myQmlWrapper.add()
					}
					else
					{
						console.log("qml asks to remove a data.")
						myQmlWrapper.remove( index );
					}
				}
			}


			Component.onCompleted: {
				console.log("qml myClip completed !")
			}
			Component.onDestruction: {
				console.log("qml myClip destruction !")
			}
			
			ListView.onRemove: SequentialAnimation {
				PropertyAction { target: myClip; property: "ListView.delayRemove"; value: true }
				NumberAnimation { target: myClip; property: "height"; to: myClip.height; duration: 1; easing.type: Easing.InOutQuad }

				// Make sure delayRemove is set back to false so that the item can be destroyed
				PropertyAction { target: myClip; property: "ListView.delayRemove"; value: false }
            }
			
			/*
			ListView.delayRemove: true
			ListView.onRemove: SequentialAnimation {
				PropertyAction { target: myClip; property: "ListView.delayRemove"; value: false }
			}
			*/
		}
		

	}//end Component

	ListView {
		//width: 200; height: 250
		anchors.fill: parent

/*
		Connections {
			target: myQmlWrapper
			onDataChanged: {
				console.log("qml - item onDataChanged "  + object.type + ", " + object.size)
			}
		}
*/
		

		model: myQmlWrapper.myModel
		delegate: myItemDelegate
	}

}

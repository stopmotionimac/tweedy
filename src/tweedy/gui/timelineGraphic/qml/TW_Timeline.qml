
import QtQuick 1.0

Rectangle {
    id: tw_timeline
    width: 1000
    height: 200
    color: "#414042"

	property int tw_timelineScale: 50
	property int tw_handleWidth: 10

	/*
	onVisibleChanged: {
		console.log("qml tw_timeline onVisibleChanged.")
		console.log("object.timeIn: " + object.timeIn)
		console.log("object.timeOut: " + object.timeOut)
	}
	*/

   Component {
        id: tw_clipDelegate

		// Clip represente
		Rectangle {

			id: tw_clip
			x: object.timeIn * tw_timelineScale
			y: parent.y
			width: (object.timeOut - object.timeIn) * tw_timelineScale
			height: 100
			border.color: "black"
			border.width: 2
			radius: 10
			color:"#e28a26"

			Text {
				text: object.timeIn
			}
			/*
            onVisibleChanged: {
                console.log("qml tweedyClipDelegate onVisibleChanged.")
                console.log("object.timeIn: " + object.timeIn)
                console.log("object.timeOut: " + object.timeOut)
            }
			*/

			// image du Clip
			Image {
				id:image
				anchors.top: parent.top
                anchors.margins: 2
				width: parent.width
				height: parent.height
				fillMode: Image.PreserveAspectFit
				smooth: true
				source:object.imgPath
				asynchronous: true
				//source: "../../../../" + object.imgPath
				}

			// zone de deplacement
			MouseArea {
				id: tw_clipHandle
				
				anchors.fill: parent
				hoverEnabled: true
				drag.axis: "XAxis"
				drag.minimumX: 0
				drag.maximumX: tw_timelineData.maxtime * tw_timelineScale - tw_timelineScale
				drag.target: parent

				onEntered: {
					console.log("qml tw_clipHandle onEntered.")
					tw_timelineData.setTimeInDrag(parent.x / tw_timelineScale)
				}

				onReleased: {
					console.log("qml tw_clipHandle onReleased.")
					tw_timelineData.translate(parent.x / tw_timelineScale)
				}
			}

			// zone gauche pour l'agrandissement du clip
			MouseArea {
				id: tw_clipLeftHandle
				
				width: tw_handleWidth
				height: tw_clip.height
				hoverEnabled: true

				onEntered: {
					tw_timelineData.displayCursor("scale");
					console.log("qml tw_clipLeftHandle onEntered.")
				}
				onExited: {
					tw_timelineData.displayCursor("none")
					console.log("qml tw_clipLeftHandle onExited.")
				}
			}

			// zone droite pour l'agrandissement du clip
			MouseArea {
				id: tw_clipRightHandle
				
				width: tw_handleWidth
				height: tw_clip.height
                anchors.right: parent.right
                //x: tw_clip.width - width
				hoverEnabled: true

				onEntered: {
					tw_timelineData.displayCursor("scale");
					console.log("qml tw_clipRightHandle onEntered.")
				}
				onExited: {
					tw_timelineData.displayCursor("none")
					console.log("qml tw_clipRightHandle onExited.")
				}
			}
		
			ListView.onRemove: SequentialAnimation {
				PropertyAction { target: tw_clip; property: "ListView.delayRemove"; value: true }
				// fake animation to delay the tw_clip destruction
				NumberAnimation { target: tw_clip; property: "height"; to: tw_clip.height; duration: 1; easing.type: Easing.InOutQuad }
				// Make sure delayRemove is set back to false so that the item can be destroyed
				PropertyAction { target: tw_clip; property: "ListView.delayRemove"; value: false }
            }
		}
    }

    ListView {
        id: tw_clipsList
        width:  parent.width
        height:  parent.height
        anchors.fill: parent

        model : tw_timelineData.tw_clips
        delegate : tw_clipDelegate
    }

    TW_Cursor {
        id: tw_cursorTimeline
    }

}



import QtQuick 1.0

Rectangle {
    id: tweedyTimeline
    width: 1000
    height: 200
    color: "#414042"

	property int tweedyTimelineScale: 50

	/*
	onVisibleChanged: {
		console.log("qml tweedyTimeline onVisibleChanged.")
		console.log("object.timeIn: " + object.timeIn)
		console.log("object.timeOut: " + object.timeOut)
	}
	*/

   Component {
        id: tweedyClipDelegate

		// Clip represente
		Rectangle {

			id: tweedyClip
			x: object.timeIn * tweedyTimelineScale
			//y: parent.y
			width: (object.timeOut - object.timeIn) * tweedyTimelineScale
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

/*
			// image du Clip
			Image {
				id:image
				y: tweedyClip.y
				width: 90
				height: 70
				fillMode: Image.PreserveAspectFit
				smooth: true
				source:object.imgPath
				//source: "../../../../" + object.imgPath
				}
*/
			// zone de deplacement
			MouseArea {
				id:dragNdrop
				anchors.fill: parent
				drag.axis: "XAxis"
				drag.minimumX: 0
				drag.maximumX: tweedyTimelineData.maxtime * tweedyTimelineScale - tweedyTimelineScale
				drag.target: parent


				onEntered: {
					console.log("qml dragNdrop onEntered.")
					tweedyTimelineData.setTimeInDrag(parent.x / tweedyTimelineScale)
				}

				onReleased: {
					console.log("qml dragNdrop onReleased.")
					tweedyTimelineData.dragNdrop(parent.x / tweedyTimelineScale)
				}
			}

			// zone gauche pour l'agrandissement du clip
			MouseArea {
				id: areaScaleLeft
				width: 10
				height: tweedyClip.height
				hoverEnabled: true

				onEntered: {
					tweedyTimelineData.displayCursor("scale");
					console.log("qml areaScaleLeft onEntered.")
				}
				onExited: {
					tweedyTimelineData.displayCursor("none")
					console.log("qml areaScaleLeft onExited.")
				}

			}

			// zone droite pour l'agrandissement du clip
			MouseArea {
				id: areaScaleRight
				width: 10
				height: tweedyClip.height
				x:tweedyClip.width - areaScaleLeft.width
				hoverEnabled: true

				onEntered: {
					tweedyTimelineData.displayCursor("scale");
					console.log("qml areaScaleRight onEntered.")
				}
				onExited: {
					tweedyTimelineData.displayCursor("none")
					console.log("qml areaScaleRight onExited.")
				}
			}
		}
    }

    ListView {
        id: listClips
        width:  parent.width
        height:  parent.height
        anchors.fill: parent

        model : tweedyTimelineData.tweedyClips
        delegate : tweedyClipDelegate
    }

    Cursor {
        id: cursortweedyTimeline
    }

}


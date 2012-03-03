
import QtQuick 1.0

Rectangle {
    id: timeline
    width: 1000
    height: 200
    color: "#414042"

   Component {
        id: clipDelegate

            //clip represente
            Rectangle {

                id: clip
                x: object.timeIn * 100
                //y: clipDelegate.y
                width: (object.timeOut - object.timeIn) * 100
                height: 100
                border.color: "black"
                border.width: 2
                radius: 10
                color:"#e28a26"

				Text {
					text: object.timeIn
				}

/*
                //image du clip
                Image {
                    id:image
                    y: clip.y
                    width: 90
                    height: 70
                    fillMode: Image.PreserveAspectFit
                    smooth: true
                    source:object.imgPath
                    //source: "../../../../" + object.imgPath
                  }
*/
                // zone de translate
                MouseArea {
                    id:dragNdrop
                    anchors.fill: parent
                    drag.axis: "XAxis"
                    drag.minimumX: 0
                    drag.maximumX: timelineData.maxtime * 100 - 100
                    drag.target: parent


                    onEntered: {
                        timelineData.setTimeInDrag(parent.x / 100)
                    }

                    onReleased: {
                        timelineData.dragNdrop(parent.x / 100)
                    }
               }

                //zone gauche pour l'agrandissement du clip
                MouseArea {
                    id: areaScaleLeft
                    width: 10
                    height: clip.height
                    hoverEnabled: true

                    onEntered: {
                        timelineData.displayCursor("scale");
                    }
                    onExited: {
                        timelineData.displayCursor("none")
                      }

                }

                //zone droite pour l'agrandissement du clip
                MouseArea {
                    id: areaScaleRight
                    width: 10
                    height: clip.height
                    x:clip.width - areaScaleLeft.width
                    hoverEnabled: true

                    onEntered: {
                        timelineData.displayCursor("scale");
                    }
                    onExited: {
                        timelineData.displayCursor("none")
                    }
                }

            }//end Rectangle



    }//end Component

    ListView {
        id: listClips
        width:  parent.width
        height:  parent.height
        anchors.fill: parent

        model : timelineData.clips
        delegate : clipDelegate
    }

    Cursor {
        id: cursorTimeline
    }

}// end rectangle



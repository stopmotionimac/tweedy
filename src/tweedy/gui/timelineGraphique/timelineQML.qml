
import QtQuick 1.0

Rectangle {
    id: timeline
    width: 1000
    height: 200
    color: "#414042"



    ListView {
        id: listClips
        width:  parent.width
        height:  parent.height
        anchors.fill: parent
        orientation: "Horizontal"

        model : timelineData.clips
        delegate : componentDelegate


    }//end listview

    Component {
        id: componentDelegate


        Column {
            spacing: 10
            y:10
            width:100 * (model.modelData.timeOut - model.modelData.timeIn) + 20
            height: 80

            //texte du temps
            Text {
                horizontalAlignment: Text.AlignHLeft
                verticalAlignment: Text.AlignVCenter
                width: parent.width
                height: 10
                color: "#ffffff"
                font.bold: true
                text: model.modelData.timeIn
            }

            //clip represente
            Rectangle {

                id: clip
                width: (model.modelData.timeOut - model.modelData.timeIn) * 100
                height: 100
                radius: 1
                color:"#e28a26"

                //image du clip
                Image {
                    y: clip.y
                    width: 90
                    height: 70
                    fillMode: Image.PreserveAspectFit
                    smooth: true
                    source:model.modelData.imgPath

                }

                //zone de drag and drop
                MouseArea {
                    anchors.fill: parent
                    drag.target: clip
                    drag.axis: Drag.XAxis

                    onClicked: {
                        timelineData.setTimeInDepart(index)
                    }

                    onReleased: {
                        console.log(index)
                        var timeInArrive = parent.x / 100
                        timelineData.dragNdrop(timeInArrive)
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

        }// end Column

    }//end Component

    Cursor {
        id: cursorTimeline
    }

}// end rectangle




import QtQuick 1.0
import "fonction.js" as MyScript

Rectangle {
    id: timeline
    width: 800
    height: 100
    color: "#414042"

    ListView {
        id: listClips
        width:  parent.width
        height:  parent.height
        anchors.fill: parent
        orientation: "Horizontal"

        model : timelineData.clips
        delegate : componentDelegate

        Connections {
                  id:  test
                  target: timelineData
                  onClipsChanged:  {
                      console.log("hello")
                  }
        }

    }//end listview

    Component {
        id: componentDelegate


        Column {
            spacing: 10
            y:10

            //texte du temps
            Text {
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                width: 100
                height: 10
                color: "#ffffff"
                font.bold: true
                text: index


            }

            //clip represente
            Rectangle {

                id: clip
                //x: model.modelData.timeIn * 60
                width: (model.modelData.timeOut - model.modelData.timeIn) * 60
                height: 60
                radius: 5

                gradient: Gradient {
                    GradientStop {
                        position: 0.00;
                        color: "#ffffff";
                    }
                    GradientStop {
                        position: 1.00;
                        color: "#e28a26";
                    }
                }

                //image du clip
                Image {
                    width:55
                    height:55
                    fillMode: Image.PreserveAspectFit
                    smooth: true
                    source: "../../../../"+model.modelData.imgPath
                }

                //zone de drag and drop
                MouseArea {
                    anchors.fill: parent
                    drag.target: clip
                    drag.axis: Drag.XAxis

                    onEntered: {
                        var timeInDepart = parent.x / 60
                        timelineData.setTimeInDepart(timeInDepart)
                    }

                    onReleased: {
                        var timeInArrive = parent.x / 60
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

}// end rectangle



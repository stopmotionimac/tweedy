import QtQuick 1.1

Item {
        id: tw_clipContainer
        width: (object.timeOut - object.timeIn + object.blankDuration) * _tw_timelineData.timelineScale
        height: tw_track.height



        Rectangle {
                id: tw_blankClip

                width: object.blankDuration * _tw_timelineData.timelineScale // * 0.5
                height: tw_track.height

                y: 0
                z: -1

                border.color: "black"
                border.width: 2
                radius: 10
                color:"black"

                // zone de deplacement
                MouseArea {
                        id: tw_blankClipHandle

                        anchors.fill: tw_blankClip
                        hoverEnabled: true
                        //drag.minimumX: 0
                        //drag.maximumX: _tw_timelineData.maxTime * _tw_timelineData.timelineScale - _tw_timelineData.timelineScale
                        drag.target: tw_blankClip
                        drag.axis: "XAxis"


                        onPressed: {
                                console.log("qml tw_blankClipHandle onPressed.")
                                _tw_timelineData.setTimeInDrag(object.timeIn);
                                parent.z = 9999;
                                }

                        onEntered: {
                                //console.log("qml tw_blankClipHandle onEntered.")
                                //_tw_timelineData.setTimeInDrag(parent.x / _tw_timelineData.timelineScale)
                                }

                         onReleased: {
                                console.log("qml tw_blankClipHandle onReleased.")

                                _tw_timelineData.translate(mouseX)
                                parent.z = -1;
                        }
                }

                // zone gauche pour l'agrandissement du clip
                MouseArea {
                        id: tw_blankClipLeftHandle

                        width: tw_handleWidth
                        height: tw_clip.height
                        hoverEnabled: true

                        onEntered: {
                                _tw_timelineData.displayCursor("scale");
                                console.log("qml tw_blankClipLeftHandle onEntered.")
                        }
                        onExited: {
                                _tw_timelineData.displayCursor("none");
                                console.log("qml tw_blankClipLeftHandle onExited.")
                        }
                }

                // zone droite pour l'agrandissement du clip
                MouseArea {
                        id: tw_blankClipRightHandle

                        width: tw_handleWidth
                        height: tw_clip.height
                        anchors.right: parent.right
                        //x: tw_clip.width - width
                        hoverEnabled: true

                        onEntered: {
                                _tw_timelineData.displayCursor("scale");
                                console.log("qml tw_blankClipRightHandle onEntered.")
                        }
                        onExited: {
                                _tw_timelineData.displayCursor("none");
                                console.log("qml tw_blankClipRightHandle onExited.")
                        }
                }
        }//end blank clip

    Rectangle {
            id: tw_clip

            //anchors.fill: parent
            width: (object.timeOut - object.timeIn) * _tw_timelineData.timelineScale // * 0.5
            height: tw_track.height

            x: object.blankDuration * _tw_timelineData.timelineScale
            y: 0
            z: -1

            border.color: "black"
            border.width: 2
            radius: 10
            color:"#e28a26"

            Text {
                    text: object.timeIn
            }

            // image du Clip
            Image {
                    id:image
                    anchors.fill: parent
                    anchors.margins: 5
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

                    anchors.fill: tw_clip
                    hoverEnabled: true
                    //drag.minimumX: 0
                    //drag.maximumX: _tw_timelineData.maxTime * _tw_timelineData.timelineScale - _tw_timelineData.timelineScale
                    drag.target: tw_clip
                    drag.axis: "XAxis"


                    onPressed: {
                            console.log("qml tw_clipHandle onPressed.")
                            _tw_timelineData.setTimeInDrag(object.timeIn);
                            parent.z = 9999;
                            }

                    onEntered: {
                            //console.log("qml tw_clipHandle onEntered.")
                            //_tw_timelineData.setTimeInDrag(parent.x / _tw_timelineData.timelineScale)
                            }

                    onReleased: {
                            console.log("qml tw_clipHandle onReleased.")
                            _tw_timelineData.translate(parent.x / _tw_timelineData.timelineScale)
                            parent.z = -1;
                    }
            }

            // zone gauche pour l'agrandissement du clip
            MouseArea {
                    id: tw_clipLeftHandle

                    width: tw_handleWidth
                    height: tw_clip.height
                    hoverEnabled: true

                    onEntered: {
                            _tw_timelineData.displayCursor("scale");
                            console.log("qml tw_clipLeftHandle onEntered.")
                    }
                    onExited: {
                            _tw_timelineData.displayCursor("none");
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
                            _tw_timelineData.displayCursor("scale");
                            console.log("qml tw_clipRightHandle onEntered.")
                    }
                    onExited: {
                            _tw_timelineData.displayCursor("none");
                            console.log("qml tw_clipRightHandle onExited.")
                    }
            }
    }






}



/*
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

    // drag and drop horizontal
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
*/
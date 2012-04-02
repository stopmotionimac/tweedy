import QtQuick 1.1

Item {
        id: tw_clipContainer
        width: (object.timeOut - object.timeIn + object.blankDuration) * _tw_timelineData.timelineScale
        height: tw_track.height

        scale: tw_clipHandle.pressed ? 1.03 : 1.0

        property int timeInClipSelected : 0
        property int markerPosition : -1

        Rectangle {
                id: tw_blankClip

                width: object.blankDuration * _tw_timelineData.timelineScale // * 0.5
                height: tw_track.height

                y: 0
                z: -1

                border.color: (doubleClickedBlank != object.timeIn)?"black":"white"
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
                        //drag.target: tw_blankClip
                        //drag.axis: "XAxis"


                        onPressed: {
                                console.log("qml tw_blankClipHandle onPressed.")

                                //timeInBlankSelected = object.timeIn
                                parent.z = 9999;
                        }
                        onDoubleClicked:{
                            timeInDoubleClickedClip = -1
                            doubleClickedBlank = object.timeIn
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

            border.color: (timeInDoubleClickedClip != object.timeIn)?"black":"white"
            border.width: 2
            radius: 10
            color:"#e28a26"

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
                    acceptedButtons: Qt.LeftButton | Qt.RightButton

                    onClicked: {
                        if (mouse.button == Qt.RightButton)
                        {
                            console.log("Qt.RightButton")
                        }
                        parent.color= '#F47A00'
                    }

                    onEntered: {
                        parent.color= '#FDAE37'
                    }

                    onExited:  {
                        parent.color = '#e28a26'
                    }

                    onPressed: {
                            console.log("qml tw_clipHandle onPressed.")
                            timeInClipSelected = object.timeIn
                            parent.z = 9999;
                    }
                    onDoubleClicked:{
                        doubleClickedBlank = -1
                        timeInDoubleClickedClip = object.timeIn
                        _tw_timelineData.displayClip(timeInDoubleClickedClip)
                    }

                    onPositionChanged: {
                        if(parent.x / _tw_timelineData.timelineScale >= 1)
                            markerPosition = _tw_timelineData.getMarkerPosition(timeInClipSelected + parent.x / _tw_timelineData.timelineScale, 1)
                        else
                            markerPosition = -1
                        if(parent.x / _tw_timelineData.timelineScale < 0)
                            markerPosition = _tw_timelineData.getMarkerPosition(timeInClipSelected + parent.x / _tw_timelineData.timelineScale, 0)

                        if (markerPosition == -1)
                            tw_marker.width = 0
                        else
                        {
                            tw_marker.width = 400 / _tw_timelineData.timelineScale
                            tw_marker.x = markerPosition * _tw_timelineData.timelineScale - tw_marker.width / 2
                        }
                    }

                    onReleased: {
                            markerPosition = -1
                            _tw_timelineData.translate(timeInClipSelected, timeInClipSelected + parent.x / _tw_timelineData.timelineScale)
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

                    }
                    onExited: {
                            _tw_timelineData.displayCursor("none");

                    }
                    onPressed: {
                        console.log("qml tw_clipRightHandle onPressed.")
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
                    }
                    onExited: {
                            _tw_timelineData.displayCursor("none");
                    }
                    onPressed: {
                        console.log("qml tw_clipRightHandle onPressed.")
                    }
            }
    }

}

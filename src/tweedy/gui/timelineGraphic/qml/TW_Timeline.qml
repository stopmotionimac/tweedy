import QtQuick 1.1

Rectangle {
        id: tw_timeline
        anchors.margins: 20
        anchors.fill: parent
        width: 1000
        height: 200
        color: "#414042"

        property int tw_timelineScale: 50
        property int tw_handleWidth: 10

        Rectangle {
                id: tw_allTracks

                //anchors.top: parent.top
                //anchors.left: parent.left
                //anchors.bottom: parent.bottom
                color: '#0000ff'
                x: 0
                y: 0
                width: ( _tw_timelineData.maxTime + 10) * tw_timelineScale
                height: parent.height

                // zone de deplacement
                MouseArea {
                        id: tw_allTracksHandle

                        //property int tw_dragMargin: 10 * tw_timelineScale
                        anchors.fill: tw_allTracks
                        drag.axis: "XAxis"
                        //drag.minimumX: tw_allTracks.x - tw_dragMargin
                        //drag.maximumX: (tw_allTracks.x+tw_allTracks.width) + tw_dragMargin
                        drag.target: tw_allTracks

                        onClicked: {
                            tw_timeCursor.x = mouseX;
                            _tw_timelineData.play(tw_timeCursor.x / tw_timelineScale);
                        }

                        onEntered: {
                                console.log("qml tw_allTracksHandle onEntered.")
                        }

                        onReleased: {
                                console.log("qml tw_allTracksHandle onReleased.")
                        }
                }

                Rectangle {
                        id: tw_track

                        x: 0
                        y: 20
                        width: parent.width
                        height: parent.height - y
                        color: '#00ff00'

                        // delegate clip component
                        Component {
                                id: tw_clipDelegate

                                // the current clip
                                TW_Clip {
                                        id: tw_clip

                                        // for technical reason: delay the destruction allows an item to remove itself
                                        ListView.onRemove: SequentialAnimation {
                                                PropertyAction { target: tw_clip; property: "ListView.delayRemove"; value: true } // start delay remove
                                                // fake animation to delay the tw_clip destruction
                                                NumberAnimation { target: tw_clip; property: "height"; to: 0; duration: 100; easing.type: Easing.InOutQuad }
                                                // Make sure delayRemove is set back to false so that the item can be destroyed
                                                PropertyAction { target: tw_clip; property: "ListView.delayRemove"; value: false } // end delay remove
                                        }
                                }
                        }

                        // list of clips
                        ListView {
                                id: tw_clipsList

                                anchors.fill: parent
                                orientation: ListView.Horizontal

                                model : _tw_timelineData.clips
                                delegate : tw_clipDelegate

                                /*
                                MouseArea {
                                        id: tw_clipsListHandle
                                        drag.axis: "XAxis"
                                        anchors.fill: tw_clipsList
                                        drag.target: tw_allTracks
                                        //preventStealing: true

                                        onEntered: {
                                                console.log("qml tw_clipsListHandle onEntered.")
                                        }

                                        onReleased: {
                                                console.log("qml tw_clipsListHandle onReleased.")
                                        }
                                }*/

                        }


                }

                // time manipulator item
                TW_Cursor {
                        id: tw_timeCursor
                }
        }
}

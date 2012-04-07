import QtQuick 1.1

// Window container
Rectangle
{
    id: tw_timelineWindow
    anchors.fill: parent
    color: "#414042"
    //width: 800
    implicitHeight: 300
    focus: true

    //property int _tw_timelineData.timelineScale: 50
    property int tw_handleWidth: 10
    property int tw_widthChanged :0
    property int tw_xPositionChanged :0
    property int tw_scrollPositionChanged:0
    property int timeInDoubleClickedClip : -1
    property int doubleClickedBlank : -1
    property int timeInClipSelected : -1
    property int timeBlankSelected : -1

    Keys.onPressed:
    {
		// delete key is pressed
        if (event.key == Qt.Key_Delete)
		{
            console.log("Big background rectangle : delete key has been pressed")
            if (timeInClipSelected > -1 )
            {
                _tw_timelineData.deleteItem(timeInClipSelected);
                timeInClipSelected = -1;
            }
            if (timeBlankSelected > -1)
            {
                _tw_timelineData.deleteItem(timeBlankSelected - 1);
                timeBlankSelected = -1;
            }
        }
   }

    Rectangle
	{
        id: tw_multitrackContainer

        //color: "#ACB6B5"
        color: "red"
        width: _tw_timelineData.maxTime * _tw_timelineData.timelineScale
        height: parent.height

        // Graduation block
		TW_Graduation
		{
			id: tw_graduation
		}

        // scrollBar item
        TW_scrollBar
		{
            id: tw_scrollArea
        }

		function moveTimeTo( mouseX ) {
			tw_timeCursor.x = mouseX
			_tw_timelineData.displayCurrentClip( (tw_timeCursor.x-tw_track.x)/_tw_timelineData.timelineScale)
			doubleClickedBlank = -1
			timeInClipSelected = -1
			timeInDoubleClickedClip = -1
		}
		
        // zone de deplacement
        MouseArea
		{
            id: tw_allTracksHandle
            anchors.fill: parent
	
            onClicked: parent.moveTimeTo(mouseX)
            onEntered: parent.moveTimeTo(mouseX)
            onReleased: parent.moveTimeTo(mouseX)
			onPositionChanged: parent.moveTimeTo(mouseX)
        }


        Rectangle
		{
            id: tw_track

            x: 0
            y: 25
            width: parent.width
            height: parent.height - 2*y
            color: '#ACB6B5'

            // delegate clip component
            Component
			{
                id: tw_clipDelegate

                // the current clip
                TW_Clip
				{
                    id: tw_clip

                    // For technical reason: delay the destruction allows an item to remove itself
                    ListView.onRemove: SequentialAnimation
					{
						PropertyAction { target: tw_clip; property: "width"; value: 0 } // to not create an offset for the newly inserted items
						PropertyAction { target: tw_clip; property: "visible"; value: false }
						PropertyAction { target: tw_clip; property: "ListView.delayRemove"; value: true } // start delay remove
						// fake animation to delay the tw_clip destruction
						NumberAnimation { target: tw_clip; property: "height"; to: 0; duration: 1; easing.type: Easing.InOutQuad } // to force a time delay of one frame
						// Make sure delayRemove is set back to false so that the item can be destroyed
						PropertyAction { target: tw_clip; property: "ListView.delayRemove"; value: false } // end delay remove
                    }
                }
            }

            // List of clips
            ListView
			{
                id: tw_clipsList

                anchors.fill: parent
                orientation: ListView.Horizontal

                model : _tw_timelineData.clips
                delegate : tw_clipDelegate
            }

            HorizontalGradient
			{
                id: tw_insertMarker
                x: 0
                y: 0
                width : _tw_timelineData.timelineScale / 5
                visible: false
                height: tw_track.height
				
				gradient: Gradient {
					GradientStop { position: 0.0; color: Qt.rgba(1, 0, 0, 0) }
					GradientStop { position: 0.40; color: Qt.rgba(1, 0, 0, .4) }
					GradientStop { position: 0.41; color: Qt.rgba(1, 0, 0, 1) }
					GradientStop { position: 0.59; color: Qt.rgba(1, 0, 0, 1) }
					GradientStop { position: 0.60; color: Qt.rgba(1, 0, 0, .4) }
					GradientStop { position: 1.0; color: Qt.rgba(1, 0, 0, 0) }
				}
            }

            Connections
			{
                target: _tw_dropArea
                onDropPositionChanged:
				{
					console.log("onDropPositionChanged")
                    _tw_graphicTimeline.insertElement( (_tw_dropArea.dropPosition-tw_track.x) / _tw_timelineData.timelineScale )
                    timeInClipSelected = (_tw_dropArea.dropPosition-tw_track.x) / _tw_timelineData.timelineScale
                }
            }
        }

        // time manipulator item
        TW_TimeCursor
		{
            id: tw_timeCursor
        }


    }



}

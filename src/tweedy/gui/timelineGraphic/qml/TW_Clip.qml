import QtQuick 1.1

Item
{
	id:	tw_clipContainer
        width: ( object.timeOut - object.timeIn + object.blankDuration ) * ratio
	height: tw_track.height

	scale: tw_clipHandle.pressed ? 1.05: 1.0

	property int clipRightPressed: 0
	property int clipLeftPressed: 0
	property bool clipSelected: false

	Rectangle
	{
		id: tw_blankClip
                width: object.blankDuration * ratio // * 0.5
		height: tw_track.height
		y: 0
		z: -1

		border.color: ( doubleClickedBlank != object.timeIn ) ? "black" : "white"
                border.width: 1
		radius: 10
                color: ( timeBlankSelected != object.timeIn ) ? "black" : "#FF3300"

		// zone de deplacement
		MouseArea
		{
			id: tw_blankClipHandle

			anchors.fill: tw_blankClip
			hoverEnabled: true
			
			onPressed:
			{
				clipSelected = false
                                timeBlankSelected = object.timeIn
                                timeInClipSelected = -1
			}

			onDoubleClicked:
			{
				timeInDoubleClickedClip = -1
                                doubleClickedBlank = object.timeIn
			}


		}

		// zone gauche pour l'agrandissement du clip
		MouseArea
		{
			id: tw_blankClipLeftHandle

			width: tw_handleWidth
			height: tw_clip.height
			hoverEnabled: true

			onEntered:
			{
				_tw_timelineData.displayCursor( "scale" );
				console.log( "qml tw_blankClipLeftHandle onEntered." )
			}
			onExited:
			{
				_tw_timelineData.displayCursor( "none" );
				console.log( "qml tw_blankClipLeftHandle onExited." )
			}
		}

		// zone droite pour l'agrandissement du clip
		MouseArea
		{
			id: tw_blankClipRightHandle

			width: tw_handleWidth
			height: tw_clip.height
			anchors.right: parent.right
			//x: tw_clip.width - width
			hoverEnabled: true

			onEntered:
			{
				_tw_timelineData.displayCursor( "scale" );
				console.log( "qml tw_blankClipRightHandle onEntered." )
			}
			onExited:
			{
				_tw_timelineData.displayCursor( "none" );
				console.log( "qml tw_blankClipRightHandle onExited." )
			}
		}
	} // end blank clip

	Rectangle
	{
		id: tw_clip

		// anchors.fill: parent
                width: ( object.timeOut - object.timeIn ) * ratio // * 0.5
		height: tw_track.height

                x: object.blankDuration * ratio
		y: 0
		z: 0

		border.color: ( timeInDoubleClickedClip != object.timeIn ) ? "black": "white"
		border.width: 2
		radius: 10
                color: ( timeInClipSelected != object.timeIn ) ? "#e28a26": "#FF3300"

		// image du Clip (Vignette)
		Image
		{
			id: image
			anchors.fill: parent
			anchors.margins: 5
				width: parent.width
				height: parent.height
				fillMode: Image.PreserveAspectFit
				smooth: true // better visual quality but slower
				source: object.imgPath // image source file path
				asynchronous: true // enable asynchronous load
		}

		// zone de deplacement
		MouseArea
		{
			id: tw_clipHandle

			anchors.fill: tw_clip
			hoverEnabled: true
			//drag.minimumX: 0
                        //drag.maximumX: _tw_timelineData.maxTime * ratio - ratio
			drag.target: tw_clip
			drag.axis: "XAxis"
			acceptedButtons: Qt.LeftButton | Qt.RightButton

			onEntered:
			{
				if( timeInClipSelected != object.timeIn )
				{
					parent.color = '#FDAE37'
				}
			}

			onClicked:
			{
				/*
                                _tw_timelineData.displayCurrentClip(tw_timeCursor.x / ratio)

                                timeInClipSelected = tw_timeCursor.x / ratio

				console.log( " timeInClipSelected" + timeInClipSelected)

				parent.color = 'red'
				console.log("qml tw_clipHandle onPressed.")
				timeInClipSelected = object.timeIn
				*/
			}

			onExited:
			{
				if( timeInClipSelected != object.timeIn )
					parent.color = '#e28a26'
			}

			onPressed:
			{
				timeBlankSelected = -1

				clipSelected = true
				console.log( "qml tw_clipHandle onPressed." )
				timeInClipSelected = object.timeIn

                                parent.color = '#FF3300'
			}

			onDoubleClicked:
			{
				doubleClickedBlank = -1
				timeInDoubleClickedClip = object.timeIn
				_tw_timelineData.displayClip( timeInDoubleClickedClip )
			}

			onPositionChanged:
			{
				if( clipSelected )
				{
					//console.log( "z:", tw_clip.z )
					tw_clip.z = 9999;
                                        //z = 9999;
					var markerPosition = -1

                                        if( parent.x / ratio >= 1 )
                                                markerPosition = _tw_timelineData.getMarkerPosition( timeInClipSelected + parent.x / ratio - object.blankDuration, true )
                                        if( parent.x / ratio < 0 )
                                                markerPosition = _tw_timelineData.getMarkerPosition( timeInClipSelected + parent.x / ratio - object.blankDuration, false )

					if( markerPosition != -1 )
					{
						tw_insertMarker.visible = true
                                                tw_insertMarker.x = markerPosition * ratio - tw_insertMarker.width / 2
					}
				}
			}

			onReleased:
			{
				tw_clip.z = 0;
				//z = -1;
				tw_insertMarker.visible = false

				if( clipSelected )
				{
                                        print( "timeInClipSelected, timeInClipSelected + parent.x / ratio", timeInClipSelected, timeInClipSelected + parent.x / ratio )
					var selectedClip = -1
                                                selectedClip = _tw_timelineData.translate( timeInClipSelected, timeInClipSelected + parent.x / ratio - object.blankDuration )
					if( selectedClip != -1 )
						timeInClipSelected = selectedClip
				}
			}
		}

		// zone gauche pour l'agrandissement du clip
		MouseArea
		{
			id: tw_clipLeftHandle

			width: tw_handleWidth
			height: tw_clip.height
			hoverEnabled: true

			onEntered:
			{
                                _tw_timelineData.displayCursor( "scale" );
			}
			onExited:
			{
				_tw_timelineData.displayCursor( "none" );

			}
			onPressed:
                        {
                            clipLeftPressed = 1
                            //console.log( "qml tw_clipRightHandle onPressed." )
			}
                        onPositionChanged: {
                            if ( clipLeftPressed == 1 )
                            {
                                if( object.timeIn > 0 )
                                {
                                    //console.log("aaaaaaaeeeeeeeeeeeeeeezaezarezr")
                                    console.log("mouse X tw_clipLeftHandle onPositionChanged" + mouseX)
                                }

                            }
                        }

                        onReleased:
                        {
                            console.log( "mouse X clip Released" + mouseX );
                            clipLeftPressed = 0
                        }
                }

                /*// zone droite pour l'agrandissement du clip
                MouseArea
                {
                        id: tw_clipRightHandle

                        width: tw_handleWidth
                        height: tw_clip.height
                        //anchors.right: tw_clip.right
                        hoverEnabled: true

                        onEntered:
                        {
                                //_tw_timelineData.displayCursor( "scale" );
                            console.log("braaaaaaaaaaaaaaaaaaaaaaaaaaaaahh")
                        }
                        onExited:
                        {
                                _tw_timelineData.displayCursor( "none" );
                        }
                        onPressed:
                        {
                                clipRightPressed = 1
                                console.log( "mouse X clip Released" + mouseX );
                        }
                        onReleased:
                        {
                                clipRightPressed = 0

                                console.log( "mouse X clip Released" + mouseX );

                                if( tw_clip.width + mouseX * ratio > tw_clip.width )
                                {
                                        tw_clip.width = tw_clip.width + mouseX * ratio
                                }
                        }
                }*/
	}
}


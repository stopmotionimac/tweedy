import QtQuick 1.1

Item
{
    id:	tw_clipContainer

    scale: tw_clipHandle.pressed ? 1.05: 1.0

    property bool clipRightPressed: false
    property bool clipLeftPressed: false
    property bool clipSelected: false

    width: ( object.timeOut - object.timeIn ) * tw_scaleTimeToPix
    height: tw_track.height

	Rectangle
	{
            id: tw_clip

            anchors.fill: parent

            border.color: ( tw_timeInDoubleClickedClip != object.timeIn ) ? "black": "white"
            border.width: 2

            radius: 15
            color: ( tw_timeInClipSelected != object.timeIn ) ? "#e28a26": "#FF3300"


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
			drag.target: tw_clipContainer
			drag.axis: "XAxis"
                        drag.minimumX: -1
                        drag.maximumX: tw_realMaxTime * tw_scaleTimeToPix
			acceptedButtons: Qt.LeftButton | Qt.RightButton

                        //0 -> not pressed
                        //1 -> pressed and hold
                        //2 -> pressed and released

			onEntered:
/*
			{
                                if( timeInClipSelected != obje ct.timeIn &&  controlPosition == 0)
                                {
                                        parent.color = '#FDAE37'
                                }
                        }
*/
                        {
                            if( tw_timeInClipSelected != object.timeIn )
                            {
                                parent.color = '#FDAE37'
                            }
			}

            /*
			onClicked:
            {
                _tw_timelineData.displayCurrentClip(tw_timeCursor.x / tw_timelineScale)

                timeInClipSelected = tw_timeCursor.x / tw_timelineScale
>>>>>>> 53e9ed7c26ceb6fc88683acffeace29b6573d4fb

				console.log( " timeInClipSelected" + timeInClipSelected)

				parent.color = 'red'
				console.log("qml tw_clipHandle onPressed.")
                timeInClipSelected = object.timeIn
			}
            */

			onExited:
/*
			{
                            if( timeInClipSelected != object.timeIn &&  controlPosition == 0)
                                parent.color = '#e28a26'
*/
                        {
                            if( tw_timeInClipSelected != object.timeIn )
                                parent.color = '#e28a26'

			}

			onPressed:
                        {
                            tw_timeBlankSelected = -1

/*
                            if (controlPosition ! 2)
                            {
                                _tw_timelineData.unselectAll()
                                _tw_timelineData.selectClip(object.timeIn)
                                controlPosition = 0
                            }
                            else
                                _tw_timelineData.selectClip(object.timeIn)
*/
				clipSelected = true
                //console.log( "qml tw_clipHandle onPressed." )
				tw_timeInClipSelected = object.timeIn
                                tw_insertPos = tw_timeInClipSelected

				parent.color = '#FF3300'
			}

			onDoubleClicked:
            {
				tw_doubleClickedBlank = -1
				tw_timeInDoubleClickedClip = object.timeIn
				_tw_timelineData.displayClip( tw_timeInDoubleClickedClip )
			}

			onPositionChanged:
            {
                //console.log( "onPositionChanged A" )

                if( clipSelected )
				{
                    //console.log( "onPositionChanged B" )
                    tw_clipContainer.z = 9999
					var markerPosition = -1

                    var xTime = parent.x * tw_scalePixToTime
                    var positiveMove = ( xTime >= 1 )
                    var dstTime = Math.round( mapToItem( tw_track, mouseX, mouseY ).x * tw_scalePixToTime )
                    markerPosition = _tw_timelineData.getMarkerPosition( dstTime, positiveMove )
                    if( markerPosition != -1 )
                    {
                        //console.log( "onPositionChanged C" )
                        //console.log( "markerPosition:", markerPosition )
                        //console.log( "markerPosition * tw_scaleTimeToPix:", markerPosition * tw_scaleTimeToPix )
                        tw_inserting = true
                        tw_insertPos = markerPosition
					}
				}
                    }

			onReleased:
/*
			{
                            tw_clip.z = 0;
                            tw_insertMarker.visible = false

                            if( clipPressed )
                            {
                                var selectedClip = _tw_timelineData.translate( timeInClipSelected, timeInClipSelected + parent.x / ratio )
                                if( selectedClip != -1 )
                                timeInClipSelected = selectedClip
                            }
*/
                        {
                            tw_clipContainer.z = 0;
                            tw_inserting = false

                            if( clipSelected )
                            {
                                print("tw_insertPos", tw_insertPos)
                                var selectedClip = -1
                                selectedClip = _tw_timelineData.translate( tw_timeInClipSelected, tw_insertPos )
                                if( selectedClip != -1 )
                                    tw_timeInClipSelected = selectedClip
                                clipSelected = false
                            }

                        }
		}

        // zone gauche pour l'agrandissement du clip
        Rectangle
        {
            id: tw_clipLeftHandle

            width: tw_handleWidth
            height: tw_clip.height
            anchors.left: tw_clip.left

            color: "green"
            visible: false
        }

        MouseArea
        {
            id: tw_clipLeftHandleMA
            anchors.fill: tw_clipLeftHandle

            hoverEnabled: true

            onEntered:
            {
                _tw_timelineData.displayCursor( "scale" );
                tw_clipLeftHandle.visible = true
            }
            onExited:
            {
                _tw_timelineData.displayCursor( "none" );
                tw_clipLeftHandle.visible = false
            }
            onPressed:
            {
                clipLeftPressed = 1
                //console.log( "qml tw_clipRightHandle onPressed." )
            }
            onPositionChanged:
            {
                if ( clipLeftPressed == 1 )
                {
                    if( object.timeIn > 0 )
                    {
                        console.log("mouse X tw_clipLeftHandle onPositionChanged" + mouseX);
                        var diff = - mouseX / tw_scaleTimeToPix;
                        console.log("diff"+diff);
                        object.timeIn = diff;
                        console.log( "object.timeIn "+object.timeIn );
                        setDisplayIn(diff);
                    } else {
                        object.timeIn = 0
                    }

                }
            }

            onReleased:
            {
                console.log( "mouse X clip Released" + mouseX );
                clipLeftPressed = 0
            }
        }

        // zone droite pour l'agrandissement du clip
        Rectangle
        {
            id: tw_clipRightHandle

            width: tw_handleWidth
            height: tw_clip.height
            anchors.right: tw_clip.right

            color: "blue"
            visible: false
        }

        MouseArea
        {
            id: tw_clipRightHandleMA
            anchors.fill: tw_clipRightHandle
            hoverEnabled: true

            onEntered:
            {
                tw_clipRightHandle.visible = true
                console.log( "R onEntered" );
                _tw_timelineData.displayCursor( "scale" );
            }
            onExited:
            {
                _tw_timelineData.displayCursor( "none" );
                tw_clipRightHandle.visible = false
                console.log( "R onExited" );
            }
            onPressed:
            {
                clipRightPressed = 1
                console.log( "R mouse X clip Released" + mouseX );
            }
            onReleased:
            {
                clipRightPressed = 0
                console.log( "R mouse X clip Released" + mouseX );
            }
            onPositionChanged:
            {
                if ( clipRightPressed == 1 )
                {
                    if( object.timeIn > 0 )
                    {
                        console.log("mouse X tw_clipLeftHandle onPositionChanged" + mouseX);
                        var diff = - mouseX / tw_scaleTimeToPix;
                        console.log("diff"+diff);
                        object.timeIn = diff;
                        console.log( "object.timeIn "+object.timeIn );
                        setDisplayOut(diff);
                    } else {
                        object.timeIn = 0
                    }

                }
            }
        }
	}
}


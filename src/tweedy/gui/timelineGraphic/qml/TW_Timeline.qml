import QtQuick 1.1
import DragNDrop 1.0

// Window container
Rectangle
{
    id: tw_timelineWindow
    anchors.fill: parent
    color: "#414042"
    implicitWidth: 500 // default width
    implicitHeight: 300
    focus: true

    // some magick contants
    property int tw_handleWidth: 10
    property int tw_gradHeight: 20

    // need int or simply bool ?
    property int tw_widthChanged :0
    property int tw_xPositionChanged :0
    property int tw_scrollPositionChanged:0

    property int tw_controlPosition : 0
    //0 -> not pressed
    //1 -> pressed and hold
    //2 -> pressed and released

    property int tw_timeInDoubleClickedClip : -1
    property int tw_doubleClickedBlank : -1
    property int tw_timeInClipSelected : -1
    property int tw_timeBlankSelected : -1
    property bool tw_inserting : false

    property int tw_realMaxTime: _tw_timelineData.maxTime
    property int tw_displayMinLength: 10
    property int tw_zoomMinLength: 5
    property int tw_maxTime: tw_realMaxTime > tw_displayMinLength ? tw_realMaxTime : tw_displayMinLength

    // time coordinates are centralized here
    property double tw_currentTime: _tw_timelineData.currentTime
    property double tw_displayIn: 0
    property double tw_displayOut: tw_maxTime
    property double tw_displayLength: tw_displayOut - tw_displayIn
    property double tw_insertPos: 0

    property double tw_scaleTimeToPix: tw_timelineWindow.width / tw_displayLength
    property double tw_scalePixToTime: tw_displayLength / tw_timelineWindow.width
    property double tw_displayInPix: tw_displayIn * tw_scaleTimeToPix
    property double tw_displayOutPix: tw_displayOut * tw_scaleTimeToPix
    property double tw_displayLengthPix: tw_displayLength * tw_scaleTimeToPix
    property double tw_maxTimePix: tw_maxTime * tw_scaleTimeToPix
    property double tw_currentTimePix: tw_currentTime * tw_scaleTimeToPix

    function moveTimeTo( mouseX )
    {
        //console.log( "moveTimeTo" )
        //console.log( "mouseX:", mouseX )
        //console.log( "tw_scalePixToTime:", tw_scalePixToTime )
        //console.log( "( mouseX * tw_scalePixToTime ):", ( mouseX * tw_scalePixToTime ) )
        //console.log( "tw_displayIn:", tw_displayIn )
        tw_currentTime = tw_displayIn + ( mouseX * tw_scalePixToTime )
        //console.log( "tw_currentTime:", tw_currentTime )
        _tw_timelineData.displayCurrentClip( tw_currentTime )
        tw_doubleClickedBlank = -1
        tw_timeInClipSelected = -1
        tw_timeInDoubleClickedClip = -1
    }

    function clamp( val, min, max )
    {
        return Math.max(min, Math.min(max, val))
    }
    function setDisplayIn( timeIn )
    {
        var clampedTimeIn = clamp(timeIn, 0, tw_maxTime)
        tw_displayIn = Math.min( clampedTimeIn, tw_displayOut - tw_zoomMinLength )
    }
    function setDisplayOut( timeOut )
    {
        var clampedTimeOut = clamp(timeOut, 0, tw_maxTime)
        tw_displayOut = Math.max( clampedTimeOut, tw_displayIn + tw_zoomMinLength )
    }
    function setDisplayInOut( timeIn, timeOut )
    {
        var clampedTimeIn = timeIn
        var clampedTimeOut = timeOut
        var timeLength = ( timeOut - timeIn )
        if( timeIn < 0 )
        {
            clampedTimeIn = 0
            clampedTimeOut = timeLength
        }
        else if( timeOut > tw_maxTime )
        {
            clampedTimeOut = tw_maxTime
            clampedTimeIn = clampedTimeOut - timeLength
        }
        setDisplayIn( clampedTimeIn )
                setDisplayOut( clampedTimeOut )
     }

    signal currentTimeChanged
    onCurrentTimeChanged: {
        console.log("onCurrentTimeChanged")
    }
    Component.onCompleted:tw_timelineWindow.currentTimeChanged

        Column
            {
                anchors.fill: parent
                // Graduation block
                TW_Graduation
                {
                    id: tw_graduation

                    width: tw_timelineWindow.width
                    height: tw_gradHeight
                    color: "#414042"

                    //moving zone
                    MouseArea
                    {
                        id: tw_allTracksHandle
                        anchors.fill: parent

                        onClicked: moveTimeTo( mapToItem( tw_timelineWindow, mouseX, mouseY ).x )
                        onEntered: moveTimeTo( mapToItem( tw_timelineWindow, mouseX, mouseY ).x )
                        onReleased: moveTimeTo( mapToItem( tw_timelineWindow, mouseX, mouseY ).x )
                        onPositionChanged: moveTimeTo( mapToItem( tw_timelineWindow, mouseX, mouseY ).x )
                    }
                }

                Rectangle
                {
                    id: tw_track

                    x: -tw_displayInPix
                    width: tw_maxTimePix
                    height: parent.height - tw_graduation.height - tw_scrollArea.height
                    //color: '#ACB6B5'
                    color: '#414042'

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
                        interactive: false
                    }

                }

                // scrollBar item
                TW_scrollBar
                {
                    id: tw_scrollArea

                    x: 0
                    height: 25
                    width: tw_timelineWindow.width
                }
            }

            // time manipulator item
            TW_TimeCursor
            {
                id: tw_timeCursor

                gradHeight: tw_gradHeight
                x: tw_currentTimePix
            }

            HorizontalGradient
            {
                id: tw_insertMarker
                x: tw_insertPos * tw_scaleTimeToPix - tw_displayInPix - width * 0.5
                y: 0
                width : 20
                visible: tw_inserting
                height: tw_graduation.height + tw_track.height

                property double cr: 1
                property double cg: 1
                property double cb: 0

                gradient: Gradient
                {
                    GradientStop { position: 0.0; color: Qt.rgba(tw_insertMarker.cr, tw_insertMarker.cg, tw_insertMarker.cb, 0.0) }
                    GradientStop { position: 0.40; color: Qt.rgba(tw_insertMarker.cr, tw_insertMarker.cg, tw_insertMarker.cb, 0.4) }
                    GradientStop { position: 0.41; color: Qt.rgba(tw_insertMarker.cr, tw_insertMarker.cg, tw_insertMarker.cb, 1.0) }
                    GradientStop { position: 0.59; color: Qt.rgba(tw_insertMarker.cr, tw_insertMarker.cg, tw_insertMarker.cb, 1.0) }
                    GradientStop { position: 0.60; color: Qt.rgba(tw_insertMarker.cr, tw_insertMarker.cg, tw_insertMarker.cb, 0.4) }
                    GradientStop { position: 1.0; color: Qt.rgba(tw_insertMarker.cr, tw_insertMarker.cg, tw_insertMarker.cb, 0.0) }
                }
            }

            Keys.onPressed:
            {
                // delete key is pressed
                if (event.key == Qt.Key_Delete)
                {
                    if (tw_timeInClipSelected > -1)
                        _tw_timelineData.deleteItem()

                    if (tw_timeInClipSelected >= tw_maxTime )
                        tw_timeInClipSelected = -1

                }

                if (event.key == Qt.Key_Control)
                    tw_controlPosition = 1
            }

            Keys.onReleased:
            {
                if (event.key == Qt.Key_Control)
                    tw_controlPosition = 2
            }

            DropArea
            {
                id: dropArea
                anchors.fill: parent

                onDragMove:
                {
                    var markerPosition = -1
                    markerPosition = _tw_timelineData.getMarkerPosition( (position-tw_track.x) * tw_scalePixToTime, false )

                    if( markerPosition != -1 )
                    {
                        tw_inserting = true
                        tw_insertPos = markerPosition
                    }
                }

                onDragLeave:
                {
                    tw_inserting = false
                }

                onDrop:
                {
                    tw_inserting = false

                    _tw_dropArea.insertElement( (position-tw_track.x) * tw_scalePixToTime )

                    tw_timeInClipSelected = (position-tw_track.x) * tw_scalePixToTime
                    if( tw_timeInClipSelected > (position-tw_track.x) * tw_scalePixToTime )
                        tw_timeInClipSelected -= 1
                }
            }
        }

import QtQuick 1.1

Rectangle {
    id: tw_timeScrollbar

    property bool scrollRightPressed: false
    property bool scrollLeftPressed: false
    property double scrollBar_pixelToTime: tw_maxTime / width
    property double scrollBar_timeToPixel: width / tw_maxTime

    color: "#ACB6B5"

    Rectangle {
        id: tw_scrollBarItem

        x: tw_displayIn * scrollBar_timeToPixel
        width: tw_displayLength * scrollBar_timeToPixel
        height: parent.height

        color: ( tw_scrollBarItemHandle.containsMouse || tw_scrollBarItemHandle.pressed ) ? "#FFFF99" : "#FFCC66"

        MouseArea {
            id: tw_scrollBarItemHandle
            anchors.fill: parent

            property double origDisplayIn
            property double origDisplayOut
            property double origMouseX

            onPositionChanged: {
                var offsetTime = ( mapToItem( tw_timeScrollbar, mouseX, mouseY ).x -origMouseX) * scrollBar_pixelToTime
                setDisplayInOut( origDisplayIn + offsetTime, origDisplayOut + offsetTime )
            }
            onPressed:{
                origDisplayIn = tw_displayIn
                origDisplayOut = tw_displayOut
                origMouseX = mapToItem( tw_timeScrollbar, mouseX, mouseY ).x
            }
        }

        // zone gauche pour l'agrandissement du zoom
        MouseArea {
           id: tw_scrollBarItemLeftHandle
           anchors.left: parent.left
           width: tw_handleWidth
           height: parent.height
           hoverEnabled: true
           onEntered: {
              _tw_timelineData.displayCursor("scale");
           }
           onExited: {
               _tw_timelineData.displayCursor("none");
           }
           onPressed:{
               print( "tw_scrollBarItemLeftHandle pressed" )
               scrollLeftPressed = true
           }

           onPositionChanged:
           {
               if ( scrollLeftPressed )
               {
                   setDisplayIn( mapToItem( tw_timeScrollbar, mouseX, mouseY ).x * scrollBar_pixelToTime )
               }
           }
           onReleased:{
               scrollLeftPressed = false
            }
       }

       // zone droite pour l'agrandissement du zoom
       MouseArea {
            id: tw_scrollBarItemRightHandle
            width: tw_handleWidth
            height: tw_scrollBarItem.height
            anchors.right: parent.right
            hoverEnabled: true
            onEntered: {
                _tw_timelineData.displayCursor("scale");
            }
            onExited: {
                _tw_timelineData.displayCursor("none");
            }

            onPressed:{
                print( "tw_scrollBarItemRightHandle pressed" )
                scrollRightPressed = true
            }

            onPositionChanged: {
                if ( scrollRightPressed )
                {
                    setDisplayOut( mapToItem( tw_timeScrollbar, mouseX, mouseY ).x * scrollBar_pixelToTime )
                }
            }

            onReleased: {
                print( "tw_scrollBarItemRightHandle released" )
                scrollRightPressed = false
            }
        }
    }
}

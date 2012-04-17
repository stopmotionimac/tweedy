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

        //color: '#FFCC66'
        color: 'yellow'

        MouseArea {
            id: tw_scrollBarItemHandle
            anchors.fill: parent

            //drag.axis: "XAxis"
            //drag.target: parent
            //drag.minimumX: 0
            //drag.maximumX: tw_timeScrollbar.width - tw_scrollBarItem.width

            property double origDisplayIn
            property double origDisplayOut
            property double origMouseX

            onPositionChanged: {
                var offsetTime = ( mapToItem( tw_timeScrollbar, mouseX, mouseY ).x -origMouseX) * scrollBar_pixelToTime
                tw_displayIn = origDisplayIn + offsetTime
                tw_displayOut = origDisplayOut + offsetTime
            }
            onEntered: {
                parent.color = "#FFFF99"
            }
            onPressed:{
                origDisplayIn = tw_displayIn
                origDisplayOut = tw_displayOut
                origMouseX = mapToItem( tw_timeScrollbar, mouseX, mouseY ).x
                print( "tw_scrollBarItemHandle pressed" )
            }
            onExited: {
                parent.color = '#FFCC66'
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
                   print( "change displayIn" )
                   tw_displayIn = mouseX * scrollBar_pixelToTime
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
                    tw_displayOut = mouseX * scrollBar_pixelToTime
                }
            }

            onReleased: {
                print( "tw_scrollBarItemRightHandle released" )
                scrollRightPressed = false
            }
        }
    }
}

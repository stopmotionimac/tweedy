import QtQuick 1.0
import "tw_utility.js" as Tw_utility

Item{
    id:tw_scrollArea

    property int scrollRightPressed : 0
    property int scrollLeftPressed : 0


    Rectangle{
        id: tw_fullBar
        width:tw_timeline.width
        height:25
        y:25 + tw_track.height
        color: "#ACB6B5"

        //yellow rect
        Rectangle {
            id: tw_scrollBar
            height: 25
            x: tw_displayInPix
            width: tw_displayLengthPix
            color: '#FFCC66'

            MouseArea {
                id: tw_scrollBarHandle
                drag.axis: "XAxis"
                anchors.fill: parent
                drag.target: parent
                drag.minimumX: 0
                drag.maximumX: tw_fullBar.width - tw_scrollBar.width
                onPositionChanged: {
                    Tw_utility.setDisplayIn( tw_scrollBar.x * _tw_timelineData.maxTime / tw_fullBar.width )
                    Tw_utility.setDisplayOut( tw_scrollBar.x+tw_scrollBar.width * _tw_timelineData.maxTime / tw_fullBar.width )
                    //tw_track.x =
                    //tw_graduation.x =
                }
                onEntered: {
                    parent.color = "#FFFF99"
                }
                onExited: {
                    parent.color = '#FFCC66'
                }
             }
            // zone gauche pour l'agrandissement du zoom
            MouseArea {
               id: tw_scrollBarLeftHandle
               width: tw_handleWidth
               height: tw_scrollBar.height
               hoverEnabled: true
               onEntered: {
                  _tw_timelineData.displayCursor("scale");
               }
               onExited: {
                   _tw_timelineData.displayCursor("none");
               }
               onPressed:{
                   scrollLeftPressed = 1
               }

               onPositionChanged: {
                   if ( scrollLeftPressed == 1 )
                   {
                       print( "Tw_utility.setDisplayIn: ", tw_scrollBar.x );
                       print( "mouseX: ", mouseX);
                       print( "_tw_timelineData.maxTime:", _tw_timelineData.maxTime);
                       print( "tw_fullBar.width:", tw_fullBar.width );
                       Tw_utility.setDisplayIn( (tw_scrollBar.x + mouseX) * _tw_timelineData.maxTime / tw_fullBar.width );
                   }
               }
               onReleased:{
                   scrollLeftPressed = 0
               }


           }
           // zone droite pour l'agrandissement du zoom
           MouseArea {
                id: tw_scrollBarRightHandle
                width: tw_handleWidth
                height: tw_scrollBar.height
                anchors.right: parent.right
                hoverEnabled: true
                onEntered: {
                    _tw_timelineData.displayCursor("scale");
                }
                onExited: {
                    _tw_timelineData.displayCursor("none");
                }

                onPressed:{
                    scrollRightPressed = 1
                }

                onPositionChanged: {
                    if ( scrollRightPressed == 1 )
                    {
                        Tw_utility.setDisplayOut( (tw_scrollBar.x+tw_scrollBar.width + mouseX) * _tw_timelineData.maxTime / tw_fullBar.width )
                    }
                }

                onReleased:{
                    scrollRightPressed = 0
                }

            }//end rightMouseArea

        }//end yellow rect

    }//end purple rect

}//end item

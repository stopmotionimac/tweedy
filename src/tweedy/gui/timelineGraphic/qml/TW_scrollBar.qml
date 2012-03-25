import QtQuick 1.0

Item{
    id:tw_scrollArea

    Rectangle{
        id: tw_fullBar
        width:800
        height:25
        y:25 + tw_track.height
        color: 'purple'

        //yellow rect
        Rectangle {
            id: tw_scrollBar
            width: _tw_timelineData.maxTime<5 ? parent.width : parent.width*5/_tw_timelineData.maxTime
            height: 25
            color: 'yellow'

            MouseArea {
                id: tw_scrollBarHandle
                drag.axis: "XAxis"
                anchors.fill: parent
                drag.target: parent
                drag.minimumX: 0
                drag.maximumX: tw_fullBar.width - tw_scrollBar.width
                onReleased:{
                    tw_track.x = - tw_scrollBar.x * _tw_timelineData.maxTime * _tw_timelineData.timelineScale / tw_fullBar.width
                    tw_graduation.x = - tw_scrollBar.x * _tw_timelineData.maxTime * _tw_timelineData.timelineScale / tw_fullBar.width
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
               onReleased:{
                   console.log(mouseX)
                   if (tw_scrollBar.x + mouseX < 0)
                   {
                       tw_scrollBar.width += tw_scrollBar.x
                       tw_scrollBar.x = 0
                   }
                   else
                       if (tw_scrollBar.width - mouseX < tw_fullBar.width*5/_tw_timelineData.maxTime)
                       {
                           tw_scrollBar.x += tw_scrollBar.width - tw_fullBar.width*5/_tw_timelineData.maxTime
                           tw_scrollBar.width = tw_fullBar.width*5/_tw_timelineData.maxTime
                       }
                       else
                       {
                           tw_scrollBar.width += - mouseX
                           tw_scrollBar.x += mouseX
                       }


                   _tw_timelineData.timelineScale = tw_fullBar.width*tw_fullBar.width/(_tw_timelineData.maxTime*tw_scrollBar.width)
                   tw_track.x = - tw_scrollBar.x * _tw_timelineData.maxTime * _tw_timelineData.timelineScale / tw_fullBar.width
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
                onReleased:{
                    console.log(mouseX)
                    if (tw_scrollBar.x + tw_scrollBar.width +mouseX > tw_fullBar.width)
                        tw_scrollBar.width = tw_fullBar.width - tw_scrollBar.x
                    else
                    {
                        if (tw_scrollBar.width + mouseX < tw_fullBar.width*5/_tw_timelineData.maxTime)
                        {
                            console.log("oihsgr")
                            tw_scrollBar.width = tw_fullBar.width*5/_tw_timelineData.maxTime
                        }
                        else
                            tw_scrollBar.width += mouseX
                    }


                    _tw_timelineData.timelineScale = 800*tw_fullBar.width/(_tw_timelineData.maxTime*tw_scrollBar.width)

                }
            }

        }

    }

}

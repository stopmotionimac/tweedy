import QtQuick 1.1

Rectangle
{
	id: tw_graduation
	width: parent.width
        height: tw_multitrackContainer.height - tw_track.height - 25
	color: "#ACB6B5"
	Row
	{
		Repeater
		{
                        model : _tw_timelineData.maxTime  //Model (how many)
			Row
			{
				// Graduation top
				Rectangle
				{
                                        id: tw_graduation_top           //ID
                                        height: tw_graduation.height   //get height from tw_graduation
                                        border.width: 2
					border.color: "black"
                                        width: _tw_timelineData.timelineScale //define width from timelineScale
                                        color: '#ACB6B5'                          //color
					
					Text // display the frame number
					{
                                            id: tw_frame
                                            anchors.centerIn: parent
                                            text: index
					}
				}
			}
		}
	}
}

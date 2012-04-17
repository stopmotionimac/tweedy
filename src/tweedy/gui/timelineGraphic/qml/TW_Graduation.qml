import QtQuick 1.1

Rectangle
{
	id: tw_graduation

    property int nbFrames: tw_displayLength + 1

    x: - (tw_displayIn - Math.floor(tw_displayIn) ) * tw_scaleTimeToPix
    color: "#ACB6B5"

	Row
	{
        anchors.fill: parent
		Repeater
		{
            model: nbFrames // Model (how many)

            // Graduation top
            Rectangle
            {
                id: tw_graduationFrame

                height: tw_graduation.height
                width: tw_scaleTimeToPix //* 1000
                border.width: 2
                border.color: "black"
                color: "yellow"
                //color: '#ACB6B5'

                Text // display the frame number
                {
                    id: tw_frame
                    anchors.centerIn: parent
                    property int frameNumber: index + Math.floor(tw_displayIn)
                    text: frameNumber
                }
			}
		}
	}
}

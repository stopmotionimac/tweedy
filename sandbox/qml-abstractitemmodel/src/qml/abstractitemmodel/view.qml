
 import QtQuick 1.0

Rectangle {
    id: timeline
    width: 1000
    height: 500
    color: "#414042"

	
	Component {
		id: clipDelegate

		Rectangle {
			id: clip
			width: 100
			height: model.realSize * 10
			border.color: "black"
			border.width: 2
			radius: 10
			color:"red"

			Text { text: "Animal: " + model.type + ", " + model.size + "." }

		}//end Rectangle
	}//end Component

	ListView {
		width: 200; height: 250
		anchors.fill: parent

		model: myModel
		delegate: clipDelegate
	}

}
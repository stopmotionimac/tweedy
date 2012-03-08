
import QtQuick 1.0


Rectangle {
    id: base
    width: 500
    height: 360
    Repeater {
	model: dummyModel
	delegate: myDelegate
    }

    Component {
	id: myDelegate
	Rectangle {
	    x: 10
	    y: index*35+10
	    width: 200
	    height: 30
	    color: "yellow"
	    TextEdit {
		text: title
		font.pointSize: 18
	    }
	    MouseArea {
		anchors.fill:  parent
		onClicked: {
		    console.log("Clicked index:",index);
		    title="test"
		}
	    }
	}
    }
}


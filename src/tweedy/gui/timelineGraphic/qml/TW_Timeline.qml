import QtQuick 1.0

Rectangle {
	id: tw_timeline
	anchors.margins: 20
	anchors.fill: parent
	width: 1000
	height: 200
	color: "#414042"

	property int tw_timelineScale: 50
	property int tw_handleWidth: 10

	// delegate clip component
	Component {
		id: tw_clipDelegate

		Item {
			// use of an itermediate item allows to have hole between clips
			id: tw_clipContainer

			// the current clip
			TW_Clip { }

			// for technical reason: delay the destruction allows an item to remove itself
			ListView.onRemove: SequentialAnimation {
				PropertyAction { target: tw_clipContainer; property: "ListView.delayRemove"; value: true } // start delay remove
				// fake animation to delay the tw_clip destruction
				NumberAnimation { target: tw_clipContainer; property: "height"; to: tw_clipContainer.height; duration: 1; easing.type: Easing.InOutQuad }
				// Make sure delayRemove is set back to false so that the item can be destroyed
				PropertyAction { target: tw_clipContainer; property: "ListView.delayRemove"; value: false } // end delay remove
			}
		}
	}

	// list of clips
	ListView {
		id: tw_clipsList

		anchors.fill: parent
		orientation: ListView.Horizontal

		model : _tw_timelineData.tw_clips
		delegate : tw_clipDelegate
	}

	// time manipulator item
	TW_Cursor {
		id: tw_timeCursor
	}
}


import QtQuick 1.1


//grey rect
Rectangle {
	id: tw_timeline
	anchors.fill: parent
	color: "#414042"

	//property int _tw_timelineData.timelineScale: 50
	property int tw_handleWidth: 10
	property int tw_widthChanged :0
	property int tw_xPositionChanged :0
	property int tw_scrollPositionChanged:0
	
	//blue rect
	Rectangle {
		id: tw_allTracks
		
		//anchors.top: parent.top
		//anchors.left: parent.left
		//anchors.bottom: parent.bottom
		color: '#0000ff'
		x: 0
		y: 0
		//width: ( _tw_timelineData.maxTime + 10) * _tw_timelineData.timelineScale
		width: _tw_timelineData.maxTime * _tw_timelineData.timelineScale
		//width: parent.width
		height: parent.height
		
		// zone de deplacement
		MouseArea {
			id: tw_allTracksHandle

            //property int tw_dragMargin: 10 * _tw_timelineData.timelineScale
			anchors.fill: tw_allTracks
            //drag.axis: "XAxis"
            //drag.minimumX: tw_allTracks.x - tw_dragMargin
            //drag.maximumX: (tw_allTracks.x+tw_allTracks.width) + tw_dragMargin
			//drag.target: tw_allTracks

            onEntered: {
				console.log("qml tw_allTracksHandle onEntered.")
			}
			onReleased: {
                console.log("qml tw_allTracksHandle onReleased.")
			}
		}
		
		//yellow rect
		Rectangle {
			id: tw_scrollBar

			width: _tw_timelineData.maxTime < 10 ? _tw_timelineData.maxTime * _tw_timelineData.timelineScale : 10 * _tw_timelineData.timelineScale;
			height: 25
			y:25 + tw_track.height
			color: 'yellow'

			MouseArea {
				id: tw_scrollBarHandle
				drag.axis: "XAxis"
				anchors.fill: parent
				drag.target: parent
				drag.minimumX: 0
				drag.maximumX: tw_clipsList.width - parent.width

				onReleased:{
					tw_scrollPositionChanged = tw_scrollBar.x / _tw_timelineData.timelineScale
					tw_scrollBar.x = tw_scrollPositionChanged * _tw_timelineData.timelineScale
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
					tw_widthChanged = mouseX / _tw_timelineData.timelineScale

					//si on a relaché en dessous de 0
					if (tw_scrollBar.x + tw_widthChanged < 0)
					{
						//la taille s'agrandit de 0 à position left initiale
						tw_scrollBar.width = tw_scrollBar.width + tw_scrollBar.x
						//x devient 0
						tw_scrollBar.x = 0
					}
					else
					//si quand on relache la taille est inf à 5
						if (tw_scrollBar.width - tw_widthChanged * _tw_timelineData.timelineScale < 5 * _tw_timelineData.timelineScale)
					{
						//x devient position droite - 5
						tw_scrollBar.x = tw_scrollBar.x + tw_scrollBar.width - ( 5 * _tw_timelineData.timelineScale )
						//la taille devient 5
						tw_scrollBar.width = 5 * _tw_timelineData.timelineScale
					}
					//sinon
					else
					{
						//la largeur augmente de la valeur calculée
						tw_scrollBar.width = tw_scrollBar.width - tw_widthChanged * _tw_timelineData.timelineScale
						//x augmente ou diminue de cette meme valeur
						//tw_xPositionChanged = -tw_widthChanged
						tw_scrollBar.x = tw_scrollBar.x + tw_widthChanged * _tw_timelineData.timelineScale
					}

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
					tw_widthChanged = mouseX / _tw_timelineData.timelineScale

					//si on a relaché au dessus de maxtime
					if ( tw_scrollBar.x + tw_scrollBar.width + tw_widthChanged*_tw_timelineData.timelineScale > _tw_timelineData.maxTime *_tw_timelineData.timelineScale )
					{
						//la taille s'agrandit de position right initiale a maxtime
						tw_scrollBar.width = _tw_timelineData.maxTime * _tw_timelineData.timelineScale - tw_scrollBar.x
					}
					else
					//si quand on relache la taille est inf à 5
						if (tw_scrollBar.width + tw_widthChanged * _tw_timelineData.timelineScale < 5 * _tw_timelineData.timelineScale)
					{
						//la largeur devient 5
						tw_scrollBar.width = 5 * _tw_timelineData.timelineScale
					}
					//sinon
					else
					{
						//la largeur augmente de la valeur calculée
						tw_scrollBar.width = tw_scrollBar.width + tw_widthChanged * _tw_timelineData.timelineScale

					}
				}
			}
		}

		//green rect
		Rectangle {
			id: tw_track

			x: 0
			y: 25
			width: parent.width
			height: parent.height - 2*y
			color: '#00ff00'
			
			// delegate clip component
			Component {
				id: tw_clipDelegate

				// the current clip
				TW_Clip {
					id: tw_clip
                    
					// for technical reason: delay the destruction allows an item to remove itself
					ListView.onRemove: SequentialAnimation {
						PropertyAction { target: tw_clip; property: "ListView.delayRemove"; value: true } // start delay remove
						// fake animation to delay the tw_clip destruction
						NumberAnimation { target: tw_clip; property: "height"; to: height; duration: 1; easing.type: Easing.InOutQuad }
						// Make sure delayRemove is set back to false so that the item can be destroyed
						PropertyAction { target: tw_clip; property: "ListView.delayRemove"; value: false } // end delay remove
					}
				}
			}

			// list of clips
			ListView {
				id: tw_clipsList

				anchors.fill: parent
				orientation: ListView.Horizontal

				model : _tw_timelineData.clips
				delegate : tw_clipDelegate

				/*
				MouseArea {
					id: tw_clipsListHandle
					drag.axis: "XAxis"
					anchors.fill: tw_clipsList
					drag.target: tw_allTracks
					//preventStealing: true

					onEntered: {
						console.log("qml tw_clipsListHandle onEntered.")
					}

					onReleased: {
						console.log("qml tw_clipsListHandle onReleased.")
					}
                                }*/

			}


		}





		
		// time manipulator item
		TW_Cursor {
			id: tw_timeCursor
		}
	}
}


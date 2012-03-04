var component;
var sprite;

function createSpriteObjects( nbClip )
{
    component = Qt.createComponent("TW_Clip.qml");
    var i = 0;
    for( i=0; i<nbClip; ++i )
    {
        sprite = component.createObject( timeline, {"x": 100*i, "y": 10} );
    }

    if( sprite == null )
	{
        console.log("Error creating object");
    }
}

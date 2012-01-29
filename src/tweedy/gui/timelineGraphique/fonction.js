var component;
var sprite;

function createSpriteObjects() {
    component = Qt.createComponent("clip.qml");
    var i = 0;
    for (i=0;i<=800;i=i+100)
    {
        sprite = component.createObject(timeline, {"x": i, "y": 10});
        i++;
    }

    if (sprite == null) {
        console.log("Error creating object");
    }
}

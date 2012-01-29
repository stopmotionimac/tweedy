import QtQuick 1.0
import "fonction.js" as MyScript

Rectangle {
    id: timeline
    width: 800
    height: 200

    color: "#414042"

    Component.onCompleted: MyScript.createSpriteObjects();
}

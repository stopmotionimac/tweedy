import QtQuick 1.1

// QML doesn't support horizontal gradients, so we build our own.
//
Item {
    property alias gradient: horizGradient.gradient

    Rectangle {
        id: horizGradient
        width: parent.height
        height: parent.width
        anchors.centerIn: parent
        rotation: 270
    }
}

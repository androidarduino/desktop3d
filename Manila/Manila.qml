import Qt 4.7
import QtQuick 1.0
import Qt3D 1.0
import Qt3D.Shapes 1.0

Viewport{
    width: 800; height: 800
    property int xp
    property int yp
    picking: true
    camera: Camera{
        //eye: Qt.vector3d(1.5,3,3)
        center: Qt.vector3d(3,0,-1.5)
    }

    Quad{
        id: board
        x:3; z:-1.5
        transform: [Scale3D{scale: Qt.vector3d(6, 1, 3)}]
        effect: Effect{texture: "board.jpg";blending: true}
    }
    Sailor{state:"TargetC"}
    Sailor{state:"TargetB"}
    Sailor{state:"TargetA"}
    Sailor{state:"GarageC";color:"yellow"}
    Sailor{state:"GarageB";color:"yellow"}
    Sailor{state:"GarageA";color:"yellow"}
    Sailor{state:"Insurance";color:"blue";onClicked: {console.log("clicked on insurace.");state="TargetA";}}
    Sailor{state:"PirateA";color:"white"}
    Sailor{state:"PirateB";color:"white"}
    Sailor{state:"PilotA";color:"pink"}
    Sailor{state:"PilotB";color:"pink"}

}

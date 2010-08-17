#include <QtGui/QApplication>
#include "scene.h"
#include "fish.h"
#include "rod.h"

int main(int argc, char *argv[]) 
{
    QApplication a(argc, argv);
    Scene w;
    Thing tree1(":/tree.png", 0.4, 0.52);
    Thing tree2(":/tree.png", 0.3, 0.36);
    Thing tree3(":/tree.png", 0.3, 0.40);
    Thing flower(":/flower.png", 0.3, 0.35);
    Thing grass1(":/grass.png", 0.3, 0.1);
    Thing grass2(":/grass.png", 0.3, 0.1);
    Fish fish1(":/nibbler.png",0.2,0.17);
    Fish fish2(":/touchy.png",0.17,0.13);
    Fish fish3(":/plainol.png",0.19,0.12);
    Fish fish4(":/kingofthepond.png",0.5,0.21);
    Fish fish5(":/nibbler.png",0.25,0.20);
    Fish fish6(":/mystery.png",0.47,0.17);
    Fish fish7(":/plainol.png",0.19,0.12);
    Fish fish8(":/smallfry.png",0.14,0.10);
    Bait bait;
    //fish1.setBaitPos(0.2,-0.18);
    Thing ground(":/ground.png", 3, 3);
    Thing g1(":/blank.png",3,3);
    Thing g2(":/blank.png",3,3);
    Thing g3(":/blank.png",9,3);
    Thing sky(":/sky.png", 9, 9);
    tree1.putTo(1.35,0.26,1.3);
    tree1.rotate(0,45,0);
    tree2.putTo(-0.6,0.18,1.4);
    tree3.putTo(-0.95,0.2,1.35);
    flower.putTo(1,0.175,-0.8);
    flower.rotate(0,70,0);
    grass1.putTo(-0.9,0.05,-0.9);
    grass1.rotate(0,30,0);
    grass2.putTo(0.1,0.05,1.3);
    grass2.rotate(30,0,0);
    ground.rotate(90,0,0);
    g1.rotate(90,0,0);
    g2.rotate(90,0,0);
    g3.rotate(90,0,0);
    ground.putTo(0,0,0.1);
    g1.putTo(-3,0,0.1);
    g2.putTo(3,0,0.1);
    g3.putTo(0,0,-2.9);
    sky.putTo(0,4.45,1.5);
    fish1.putTo(0.1,-0.20,0.1);
    fish2.putTo(0.1,-0.199,0.1);
    fish3.putTo(0.1,-0.198,0.1);
    fish4.putTo(0.1,-0.197,0.1);
    fish5.putTo(0.1,-0.196,0.1);
    fish6.putTo(0.1,-0.195,0.1);
    fish7.putTo(0.1,-0.194,0.1);
    fish8.putTo(0.1,-0.193,0.1);
    bait.putTo(0.2,-0.18,0.2);
    w.add(&fish1);
    /*w.add(&fish2);
    w.add(&fish3);
    w.add(&fish4);
    w.add(&fish5);
    w.add(&fish6);
    w.add(&fish7);
    w.add(&fish8);
    w.add(&bait);
    */
    w.add(&sky);
    w.add(&ground);
    w.add(&g1);
    w.add(&g2);
    w.add(&g3);
    w.add(&tree3);
    w.add(&tree2);
    w.add(&tree1);
    w.add(&flower);
    w.add(&grass1);
    w.add(&grass2);
    w.resize(800,600);
    w.show();
    return a.exec();
}

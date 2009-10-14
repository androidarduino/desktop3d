#include "weatherwindow.h"

#define DEPTH 0.05


WeatherWindow::WeatherWindow()
{
     p=new QPixmap(200,200);
     p->fill(QColor(0,0,0,0));
     p_ori=*p;
     state=0;
     loadSettings();
     connect(&info, SIGNAL(updateComplete()), this, SLOT(update()));
     info.update(location,language);
}

void WeatherWindow::initializeGL()
{
    DesktopGadget::initializeGL();
    wood=bindTexture(QPixmap(":/pics/wood.png"), GL_TEXTURE_2D);
    darkwood=bindTexture(QPixmap(":/pics/waterlili.png"), GL_TEXTURE_2D);
    bgpic=bindTexture(QPixmap(background), GL_TEXTURE_2D);
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void WeatherWindow::createObjects()
{
    updatePicture();
    glScalef(2,2,2);
    glEnable(GL_TEXTURE_2D);
    GLuint winpicture=bindTexture(*p, GL_TEXTURE_2D);
    //draw borders
    //glColor3f(0.75,0.75,0);
    drawSide();
    glRotatef(90,0,0,1);
    drawSide();
    glRotatef(90,0,0,1);
    drawSide();
    glRotatef(90,0,0,1);
    drawSide();
    //draw background picture
    glBindTexture(GL_TEXTURE_2D, bgpic);
    glBegin(GL_QUADS);
    glTexCoord2d(1,0);
    glVertex3d(-0.4,0.4,-DEPTH);
    glTexCoord2d(0,0);
    glVertex3d(-0.4,-0.4,-DEPTH);
    glTexCoord2d(0,1);
    glVertex3d(0.4,-0.4,-DEPTH);
    glTexCoord2d(1,1);
    glVertex3d(0.4,0.4,-DEPTH);
    glEnd();
    //draw front transparent picture
    glBindTexture(GL_TEXTURE_2D, winpicture);
    glBegin(GL_QUADS);
    glTexCoord2d(1,1);
    glVertex3d(-0.4,0.4,0.03);
    glTexCoord2d(0,1);
    glVertex3d(-0.4,-0.4,0.03);
    glTexCoord2d(0,0);
    glVertex3d(0.4,-0.4,0.03);
    glTexCoord2d(1,0);
    glVertex3d(0.4,0.4,0.03);
    glEnd();
    //draw back cover
    glBindTexture(GL_TEXTURE_2D, wood);
    glBegin(GL_QUADS);
    glTexCoord2d(1,1);
    glVertex3d(0.5,0.5,-DEPTH);
    glTexCoord2d(1,0);
    glVertex3d(0.5,-0.5,-DEPTH);
    glTexCoord2d(0,0);
    glVertex3d(-0.5,-0.5,-DEPTH);
    glTexCoord2d(0,1);
    glVertex3d(-0.5,0.5,-DEPTH);
    glEnd();
    //deleteTexture(wood);
    //deleteTexture(darkwood);
    deleteTexture(winpicture);
}

void WeatherWindow::drawSide()
{
    glBindTexture(GL_TEXTURE_2D, wood);
    glBegin(GL_QUADS);
    //front side
    glTexCoord2d(0,1);
    glVertex3d(-0.5,0.5, DEPTH);
    glTexCoord2d(0.2,0.8);
    glVertex3d(-0.4,0.4, -DEPTH);
    glTexCoord2d(0.8,0.8);
    glVertex3d(0.4,0.4, -DEPTH);
    glTexCoord2d(1,1);
    glVertex3d(0.5,0.5,DEPTH);
    //border side
    //glBindTexture(GL_TEXTURE_2D,darkwood);
    glVertex3d(0.5,0.5, -DEPTH);
    glVertex3d(-0.5,0.5,-DEPTH);
    glVertex3d(-0.5,0.5, DEPTH);
    glVertex3d(0.5,0.5,DEPTH);
    glEnd();
}

WeatherWindow::~WeatherWindow()
{
    saveSettings();
    delete p;
}

void WeatherWindow::updatePicture()
{
    *p=p_ori;
    painter.begin(p);
    QFont oldFont=painter.font();
    QFont font;
    font.setPixelSize(22);
    font.setWeight(QFont::Black);
    painter.setFont(font);
    painter.setPen(QPen(QColor(255,255,0,255)));
    if(state==0)//state is 0-5
        currentTemp();
    if(state==1)currentOthers();
    if(state>1)
        nextDays(state-2);
    painter.setFont(oldFont);
    painter.end();
}
void WeatherWindow::drawWeatherIcon(QString weatherType)
{
    //TODO: select icon according to weather type
    QPixmap sun(":/pics/"+weatherType);
    if(sun.width()==0)
        sun.load(":/pics/undefined.png");
    painter.drawPixmap(20,64,96,96,sun);
}
void WeatherWindow::currentTemp()
{
    //draw weatherinfo.city, .curTemp, .curCondition
    painter.drawText(4,32,info.city);
    painter.drawText(144,64,info.curTemp);
    painter.drawText(QRect(4,80,200,200),
                     Qt::AlignRight|Qt::AlignVCenter|Qt::TextWordWrap,//TODO: not working
                     info.curCondition);
    drawWeatherIcon(info.curIcon);
}
void WeatherWindow::currentOthers()
{
    //draw weatherinfo.city, .curCondition, .curTemp, .curHumidity, .curWind;
    painter.drawText(4,32,info.city);
    painter.drawText(4,96,info.curCondition);
    painter.drawText(4,120,info.curTemp);
    painter.drawText(4,144,info.curHumidity);
    painter.drawText(4,168,info.curWind);
}
void WeatherWindow::nextDays(int days)
{
    //draw weatherinfo.city, day[days], low[days], high[days], condition[days]
    //drawWeatherIcon(weatherinfo.icon);
    painter.drawText(4,32,info.city+"  "+ info.day[days]);
    painter.drawText(96,64,info.low[days]+"-"+info.high[days]);
    painter.drawText(QRect(4,80,190,190),
                     Qt::AlignRight|Qt::AlignVCenter|Qt::TextWordWrap,//TODO: not working
                     info.condition[days]);
    drawWeatherIcon(info.icon[days]);
}

void WeatherWindow::keyPressEvent(QKeyEvent* event)
{
    if(event->key()==Qt::Key_Left)
    {
        state--;
        if(state<0)
            state=5;
    }
    if(event->key()==Qt::Key_Right)
    {
        state++;
        if(state>5)
            state=0;
    }
    update();
}

void WeatherWindow::loadSettings()
{
    QSettings settings("weather3d.ini", QSettings::IniFormat);
    location=settings.value("location","Beijing").toString();
    language=settings.value("language","zh-cn").toString();
    background=settings.value("background",":/pics/waterlili.png").toString();
}

void WeatherWindow::saveSettings()
{
    QSettings settings("weather3d.ini", QSettings::IniFormat);
    settings.setValue("location", location);
    settings.setValue("language", language);
    settings.setValue("background", background);
}

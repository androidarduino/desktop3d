#ifndef WEATHERWINDOW_H
#define WEATHERWINDOW_H
#include "widget.h"
#include "weatherinfo.h"
#include <QPixmap>
//«Á “ı ∂‡‘∆ …Ÿ‘∆ –°”Í ÷–”Í ¥Û”Í  ’Û”Í ¿◊’Û”Í ±©”Í
//ŒÌ£¨ˆ≤£¨À™∂≥£¨±©∑Á£¨Ã®∑Á£¨±©∑Á—©£¨¥Û—©£¨÷–—©£¨–°—©£¨”Íº–—© ±˘±¢
//∏°≥æ —Ô…≥
//http://www.google.com/ig/api?weather=Changchun&hl=zh-cn
//zh-cn, zh-tw, fr, en, ko, ja, es, de, ru
/*
/ig/images/weather/chance_of_rain.gif
images/weather/sunny.gif
images/weather/mostly_sunny.gif
images/weather/partly_cloudy.gif
images/weather/mostly_cloudy.gif
images/weather/chance_of_storm.gif
images/weather/rain.gif
images/weather/chance_of_rain.gif
images/weather/chance_of_snow.gif
images/weather/cloudy.gif
images/weather/mist.gif
images/weather/storm.gif
images/weather/thunderstorm.gif
images/weather/chance_of_tstorm.gif
images/weather/sleet.gif
images/weather/snow.gif
images/weather/icy.gif
images/weather/dust.gif
images/weather/fog.gif
images/weather/smoke.gif
images/weather/haze.gif
images/weather/flurries.gif
*/
class WeatherWindow : public DesktopGadget
{
public:
    WeatherWindow();
    ~WeatherWindow();
    //tmp put public for testing
    void updatePicture();//update the picture using weather info
protected:
    virtual void createObjects();
    virtual void initializeGL();
    void keyPressEvent(QKeyEvent* event);
private:
    void loadSettings();
    void saveSettings();
    void drawSide();
    void drawWeatherIcon(QString weatherType);
    void currentTemp();
    void currentOthers();
    void nextDays(int days);
    GLuint wood,darkwood,bgpic;
    QPixmap* p;
    QPixmap p_ori;
    WeatherInfo info;
    QPainter painter;
    int state;
    QString location, language, background;
};
#endif // WEATHERWINDOW_H

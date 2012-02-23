#ifndef CLIPDATAWRAPPER_HPP
#define CLIPDATAWRAPPER_HPP

#include <QtCore/QObject>

class ClipDataWrapper : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString imgPath READ getImgPath WRITE setImgPath NOTIFY imgPathChanged)
    Q_PROPERTY(int timeIn READ getTimeIn WRITE setTimeIn NOTIFY timeInChanged)
    Q_PROPERTY(int timeOut READ getTimeOut WRITE setTimeOut NOTIFY timeOutChanged)



public:
    explicit ClipDataWrapper(QObject *parent = 0);
    ClipDataWrapper(QString imgPath, int timeIn, int timeOut, QObject *parent = 0);
    ClipDataWrapper(const ClipDataWrapper& other)
    {
        *this = other;
    }
    ClipDataWrapper& operator =(const ClipDataWrapper& other)
    {
        _imgPath = other._imgPath;
        _timeIn = other._timeIn;
        _timeOut = other._timeOut;
        return *this;
    }

    QString getImgPath(){ return _imgPath;}
    int getTimeIn(){ return _timeIn;}
    int getTimeOut(){ return _timeOut;}
    void setImgPath(QString imgpath){_imgPath = imgpath; }
    void setTimeIn(int timeIn){_timeIn = timeIn; }
    void setTimeOut(int timeOut){_timeIn = timeOut; }


Q_SIGNALS:
    void imgPathChanged();
    void timeInChanged();
    void timeOutChanged();

private :
    QString _imgPath;
    int _timeIn;
    int _timeOut;


};

#endif // CLIPDATAWRAPPER_HPP

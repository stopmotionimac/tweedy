#ifndef CLIPDATAWRAPPER_HPP
#define CLIPDATAWRAPPER_HPP

#include <QtCore/QObject>
#include <tweedy/core/Clip.hpp>

class ClipDataWrapper : public QObject
{
	Q_OBJECT

	Q_PROPERTY( QString imgPath READ getImgPath WRITE setImgPath NOTIFY imgPathChanged )
	Q_PROPERTY( int timeIn READ getTimeIn WRITE setTimeIn NOTIFY timeInChanged )
	Q_PROPERTY( int timeOut READ getTimeOut WRITE setTimeOut NOTIFY timeOutChanged )
        Q_PROPERTY( int blankDuration READ getBlankDuration NOTIFY blankDurationChanged )

public:
	explicit ClipDataWrapper( QObject *parent = 0 );
        ClipDataWrapper(Clip* clip, QObject *parent = 0 );

	ClipDataWrapper( const ClipDataWrapper& other )
	{
		*this = other;
	}

	ClipDataWrapper& operator=(const ClipDataWrapper& other )
	{
		_imgPath = other._imgPath;
		_timeIn = other._timeIn;
		_timeOut = other._timeOut;
		return *this;
	}

        const QString& getImgPath() const{ return _imgPath; }
        int getTimeIn() const{ return _timeIn; }
        int getTimeOut() const{ return _timeOut; }
        int getBlankDuration() const{ return _blankDuration; }

        void setImgPath( QString imgpath ){ _imgPath = imgpath; }
        void setTimeIn( int timeIn ){ _timeIn = timeIn; }
        void setTimeOut( int timeOut ){ _timeIn = timeOut; }



Q_SIGNALS:
	void imgPathChanged();
	void timeInChanged();
	void timeOutChanged();
        void blankDurationChanged();

private:
	QString _imgPath;
	int _timeIn;
	int _timeOut;
        int _blankDuration;


};

#endif // CLIPDATAWRAPPER_HPP

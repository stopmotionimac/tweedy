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


public:
	explicit ClipDataWrapper( QObject *parent = 0 );
	ClipDataWrapper( Clip* clip, QObject *parent = 0 );

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


        const QString& getImgPath( ) const{ return _imgPath; }
        void setImgPath( QString imgpath ){ _imgPath = imgpath; }

        int getTimeIn( ) const{ return _timeIn; }
        void setTimeIn( int timeIn ){ _timeIn = timeIn; }

        int getTimeOut( ) const{ return _timeOut; }
        void setTimeOut( int timeOut ){ _timeIn = timeOut; }


Q_SIGNALS:
        void imgPathChanged();
        void timeInChanged();
        void timeOutChanged();

private:
	QString _imgPath;
	int _timeIn;
	int _timeOut;

};

#endif // CLIPDATAWRAPPER_HPP

#ifndef __TIMELINE_HPP__
#define __TIMELINE_HPP__

#include <tweedy/core/Clip.hpp>
#include <tweedy/core/Id.hpp>

#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
#include <boost/ptr_container/ptr_unordered_map.hpp>
#include <boost/ptr_container/ptr_map.hpp>
#include <boost/foreach.hpp>
#include <boost/signal.hpp>
#include <boost/ptr_container/serialize_ptr_unordered_map.hpp>

class Timeline : public Imedia
{

public:
	typedef boost::ptr_unordered_map<std::string, Clip> UOMapClip;
	typedef boost::ptr_map<unsigned int, Clip*> OMapClip;

	Timeline( const Id& idParent, const std::string& id );
	Timeline( const Timeline& );


	UOMapClip& mapClip()
	{
		return _mapClip;
	}

	unsigned int getMaxTime() const
	{
		return _maxTime;
	}
	void updateMaxTime();
	OMapClip getOrderedClips();
	const OMapClip getOrderedClips() const;

	void moveElement( std::string filename, int newPosition );
        //void addClip( const Clip& clip );
	void deleteClip( const std::string& clipName );


        /*void addBlank( const std::string& clipName, bool blankBefore = false );
        void deleteBlank( int time );
        void deleteBlank( Clip* clip );*/

	void insertClip( Clip& newClip, double currentTime );
	//void insertClip(const std::string& newClipName, double currentTime);
	void addTimeToClip( const std::string& clipName, double decalage );
        std::string findCurrentClip(int time) const;

        void selectClip(int timeIn);
        void unselectAll();

        //int getBlankDuration( Clip* clip );


	const Id& getId() const;

	/**
	 * @todo: Not the same than _mapClip.size()?
	 */
	unsigned int getNbClip() const
	{
		return _nbClip;
	}

	void setNbClip( unsigned int nbClips )
	{
		_nbClip = nbClips;
	}

	boost::signal0<void>& getSignalChanged();

        std::vector<std::string> getUrlList(){ return _urlList; }
        void setUrlList(std::string url){ _urlList.push_back(url); }
        void clearUrlList(){ _urlList.clear(); }
        std::string getIdRealTime() { return  _idRealTime; }

        std::string getIdRealTime(){ return _idRealTime; }

private:

	unsigned int _nbClip;
	unsigned int _maxTime;
	UOMapClip _mapClip;

	boost::signal0<void> _signalChanged;

	Id _id;

	friend class boost::serialization::access;

	template<class Archive>
	void serialize( Archive& ar, const unsigned int version )
	{
		ar & _nbClip;
		ar & _maxTime;
		ar & _mapClip;
		ar & _id;
		
		if( Archive::is_loading::value )
			_signalChanged();
	}

        std::vector<std::string> _urlList;
        std::string _idRealTime;

};

#endif

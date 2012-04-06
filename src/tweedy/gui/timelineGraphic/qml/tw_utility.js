
function setDisplayIn( vIn )
{
    var tIn = vIn;
    if( tIn < 0 )
        tIn = 0;
    if( tw_displayOut - tIn < tw_displayMinWidth )
        tIn = tw_displayOut - tw_displayMinWidth;

    tw_timeline.tw_displayIn = tIn;
    print("setDisplayIn:", tIn);
}

function setDisplayOut( vOut )
{
    var tOut = vOut;
    if( tOut > _tw_timelineData.maxTime )
        tOut = _tw_timelineData.maxTime;
    if( vOut - tw_displayIn < tw_displayMinWidth )
        tOut = tw_displayIn + tw_displayMinWidth;

    tw_timeline.tw_displayOut = tOut;
    print("setDisplayOut:", tOut);
}

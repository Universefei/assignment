#include "car.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>

/*---------------------------------------------------------------------------*/
/*                                Constructor                                */
/*---------------------------------------------------------------------------*/
Car::Car() : speed(0.1), genPlace(eBSN), dist(eBSS)
{
	setRotation( 0 );
	setStartPos();
}

Car::Car( EPlace gen, EPlace dis, qreal fast ) :
	genPlace(gen), dist(dis), speed(fast)
{
	setStartPos();
}

Car::~Car() {
}
	
/*---------------------------------------------------------------------------*/
/*                                setStartPos                                */
/*---------------------------------------------------------------------------*/
void Car::setStartPos()
{
	setPos( startPoint[genPlace] );
}

/*---------------------------------------------------------------------------*/
/*                                 shape                                     */
/*---------------------------------------------------------------------------*/
QPainterPath Car::shape() const
{
	QPainterPath path;
	path.addRect( -2.5, -5, 5, 10 );
	return path;
}

/*---------------------------------------------------------------------------*/
/*                                boundingRect                               */
/*---------------------------------------------------------------------------*/
QRectF Car::boundingRect() const
{
	qreal adjust = 0.5;
	return QRectF( -2.5, -5 - adjust,
			5, 13 + adjust);
}


/*---------------------------------------------------------------------------*/
/*                                 paint                                     */
/*---------------------------------------------------------------------------*/
void Car::paint( QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
	//  Car body
	painter->setBrush( pointColor[genPlace] );
	painter->drawRect( -3.5, -6, 7, 12 );

	//  Car front window
	painter->setBrush( pointColor[dist] );
	painter->drawRect( -3, 0.5, 6, 5 );

}

/*---------------------------------------------------------------------------*/
/*                                 ableToForward                             */
/*---------------------------------------------------------------------------*/
bool Car::ableToForward( TrafficLight* light, ELightDirct direct ) const
{
	QColor curColor = light->getLightStatus( direct );

	if ( curColor == trafficLightRed ) {
		return false;
	}
	else if ( curColor == trafficLightGreen ) {
		return true;
	}
}

/*---------------------------------------------------------------------------*/
/*                                 checkLightForward                         */
/*---------------------------------------------------------------------------*/
void Car::checkLightForward( ) 
{

    //  Tag if should go forward in this advance.
    bool bForward = true;

    //  Get this item's coordinate in Scene.
	QPointF curLoc = mapToScene( 0, 0 );

    //  If at Cr1 North-South direction
	if ( curLoc == lightCr1BSN || curLoc == lightCr1BSS ) {
		if ( !ableToForward( pLightAtCr1, eNS ) ) { // if not avalable in this direction
			bForward = false;
		}
		else { // if avalable in this direction
			bForward = true;
		}
	}
    //  If at Cr1 West-East direction
	else if ( curLoc == lightCr1RHW || curLoc == lightCr1RHE ) {
		if ( !ableToForward( pLightAtCr1, eWE ) ) {
			bForward = false;
		}
		else {
			bForward = true;
		}
	}
    //  If at Cr2 North-South direction
	else if ( curLoc == lightCr2TBN || curLoc == lightCr2TBS ) {
		if ( !ableToForward( pLightAtCr2, eNS ) ) {
			bForward = false;
		}
		else {
			bForward = true;
		}
	}
    //  If at Cr2 West-East direction
	else if ( curLoc == lightCr2RHW || curLoc == lightCr2RHE ) {
		if ( !ableToForward( pLightAtCr2, eWE ) ) {
			bForward = false;
		}
		else {
			bForward = true;
		}
	}
	else {
		QPointF curLocFront = mapToScene( 0, 15 );
		QGraphicsItem* pfront = scene()->itemAt( curLocFront );
		if (pfront != 0) {
			bForward = false;
		}
		else {
			bForward = true;
		}
	}

    //  Go forward if bForward is ture
    if ( bForward ) {
		setPos( mapToParent( 0, 0.5 ) );
    }

}

/*---------------------------------------------------------------------------*/
/*                               turnDirection                               */
/*---------------------------------------------------------------------------*/
void Car::turnDirection()
{
}

/*---------------------------------------------------------------------------*/
/*                               advance                                     */
/*---------------------------------------------------------------------------*/
void Car::advance( int step )
{
	if(!step)
		return;

    //  How to turn, every derived class need reimplement this function;
    turnDirection();

	//  Check if this advance should go bForward.
	checkLightForward();
}

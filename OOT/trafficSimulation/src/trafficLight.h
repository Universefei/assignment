#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include <QGraphicsItem>

//  Simulation speedup 
static const qreal speedUp = 15;
//  How many frames per sec.
static const int freq = 300;

//  Define constants of 2 trafficlight colors.
static const QColor trafficLightRed = Qt::red;
static const QColor trafficLightGreen = Qt::green;

//  Enum of Direction of Trafficlight
enum ELightDirct 
{
	eNS = 0,    //  North-South Direction
	eWE         //  West-East Direction
};

/******************************************************************************
 *                              Class TrafficLight                            *
 *****************************************************************************/
class TrafficLight : public QGraphicsItem
{
	public:
		//  param sec is real world second
		TrafficLight( int sec );
		QColor getLightStatus( ELightDirct ) volatile;
		//void setStartPos();

		QRectF boundingRect() const;
		void paint( QPainter* painter, const QStyleOptionGraphicsItem* option,
				QWidget* Widget );
		QPainterPath shape() const;


	protected:
		 void advance( int step );

	private:
		volatile int ticker;
};

#endif  //  TRAFFICLIGHT_H


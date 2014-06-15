#ifndef CAR_H
#define CAR_H

#include <QGraphicsItem>
#include "misc.h"

//  Using template Design pattern in this class,
//  \ derived classes need reimplement virtual function turnDirection()

/******************************************************************************
 *                                 Class Car                                  *
 *****************************************************************************/
class Car: public QGraphicsItem
{
    public:
        
        Car();

        /** Constructor: Create a new Car
         *  \param eStart   : Start point of car
         *  \param eEnd     : destination of car
         *  \param speed    : Speed of car
         */
        Car( EPlace, EPlace, qreal );

        virtual ~Car();

        /** QGraphicsItem's pure virtual public function 
         *  \returns an estimate of the area painted by the item
         */
        QRectF boundingRect() const;

        /** QGraphicsItem's pure virtual public function
         *  \do the actual painting
         */
        void paint( QPainter *painter, const QStyleOptionGraphicsItem *option,
                QWidget *widget );

        /** QGraphicsItem's virtuanl function
         *  \return the accurate shape of item
         */
        QPainterPath shape() const;

        /** Put this car to corresponding point in QGraphicsView
         *  \this operation was invoked in constructor
         */
        void setStartPos();

    protected:
        /** Handling the animation so it all happens on one update.
         *  \defining what to do in every frame.
         *  \defining process in this operation.
         */
        void advance( int step );

    public:
        /** Determining if it is need to turn or how to turn in this frame
         *  \or update
         *  This operation was invoked in advance. and every derived class
         *  \need to reimplement its details.
         */
        virtual void turnDirection();

        /** Check if it is access in certain direction.
         *  \param trafficLight*    : which traffic light to check
         *  \param ELightDirect     : which direction to check
         */
        bool ableToForward( TrafficLight*, ELightDirct ) const;

        /** Check if be able to go forward and how much to go
         *  \do the actual forward 
         *  This operation was invoked in advance. at every step forward.
         */
        void checkLightForward( ) ;

        /* The car generated place */
        EPlace genPlace;

        /* The car distination place */
        EPlace dist;

        /* The car speed */
        qreal speed;
};

#endif // CAR_H

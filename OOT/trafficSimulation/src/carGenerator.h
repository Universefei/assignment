#ifndef CARGENERATOR_H
#define CARGENERATOR_H

#include <QGraphicsItem>
#include "misc.h"
#include "car.h"
#include "carFrom.h"

/******************************************************************************
 *                              Class CarGenerator                            *
 *****************************************************************************/
class CarGenerator : public QGraphicsItem
{
	public:

		CarGenerator();

        /** Create a CarGenerator
         *  \param EPlace   :where to place this car generator
         *  \param int      :traffic heavy index
         */
        
		CarGenerator( EPlace, int );
		
        /** QGraphicsItem's pure virtual public function 
         *  \returns an estimate of the area painted by the item
         */
		QRectF boundingRect() const;

        /** QGraphicsItem's pure virtual public function
         *  \do the actual painting
         */
		void paint( QPainter* painter, const QStyleOptionGraphicsItem* option,
				QWidget* widget );

        /** QGraphicsItem's virtuanl function
         *  \return the accurate shape of item
         */
		QPainterPath shape() const;

        /** Put this car to corresponding point in QGraphicsView
         *  \this operation was invoked in constructor
         */
		void placeSet();

	protected:
        /** Handling the animation so it all happens on one update.
         *  \defining what to do in every frame.
         *  \defining process in this operation.
         */
		void advance( int step );

	private:
        /* car generated place */
		EPlace genPlace;

        /* counter */
		int ticker;

        /* traffic condition, car generating spped */
		int trafHeavy;  

};

#endif  // CARGENERATOR_H

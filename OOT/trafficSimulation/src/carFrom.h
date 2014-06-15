#ifndef CARFROM_H
#define CARFROM_H

#include "car.h"
#include <QGraphicsItem>

/******************************************************************************
 *                               Class CarBSN                                 *
 *****************************************************************************/
class CarBSN : public Car
{
	public:
		CarBSN( qreal speed );
		~CarBSN();

	private:
		void turnDirection();
};

/******************************************************************************
 *                               Class CarBSS                                 *
 *****************************************************************************/
class CarBSS : public Car
{
	public:
		CarBSS( qreal speed );
		~CarBSS();

	private:
		void turnDirection();
};

/******************************************************************************
 *                               Class CarTBN                                 *
 *****************************************************************************/
class CarTBN : public Car
{
	public:
		CarTBN( qreal speed );
		~CarTBN();

	private:
		void turnDirection();
};

/******************************************************************************
 *                               Class CarTBS                                 *
 *****************************************************************************/
class CarTBS : public Car
{
	public:
		CarTBS( qreal speed );
		~CarTBS();

	private:
		void turnDirection();
};

/******************************************************************************
 *                               Class CarRHW                                 *
 *****************************************************************************/
class CarRHW : public Car
{
	public:
		CarRHW( qreal speed );
		~CarRHW();

	private:
		void turnDirection();
};

/******************************************************************************
 *                               Class CarRHE                                 *
 *****************************************************************************/
class CarRHE : public Car
{
	public:
		CarRHE( qreal speed );
		~CarRHE();

	private:
		void turnDirection();
};

#endif // CARFROM_H

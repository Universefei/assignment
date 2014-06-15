#include "Wine.h"

pkg::pkg() {
				mnt=0;
				price=0;
}

pkg::~pkg() {
}

void pkg::setMnt(int m) {
				mnt=m;
}

void pkg::setPrice(float p) {
				price=p;
}

int pkg::getMnt() {
				return mnt;
}

float pkg::getPrice() {
				return price;
}

float pkg::totalCost() {
				return mnt*price;
}

seprate::seprate() {
				mnt=0;
				price=0;
}

seprate::~seprate() {
}

/**
 * 计算一共购买酒的重量和平均单价
 */
seprate operator +(const seprate& buy1,const pkg& buy2) {
				seprate temp;
				int tempmnt=buy2.getMnt();
				float tempprice=buy2.getPrice();
				temp.mnt=tempmnt+buy1.mnt;
				temp.price=(tempmnt*tempprice+buy1.mnt*buy1.price)/(tempmnt+buy1.mnt);
				return temp;
}

void seprate::setMnt(int m) {
				mnt=m;
}

void seprate::setPrice(float p) {
				price=p;
}

int seprate::getMnt() {
				return mnt;
}

float seprate::getPrice() {
				return price;
}

float seprate::totalCost() {
				return mnt*price;
}

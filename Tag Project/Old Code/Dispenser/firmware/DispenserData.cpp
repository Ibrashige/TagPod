/**
 *  Helper class to contain, access, and set the all
 *  dispenser-related data. 
 */ 
#include "Arduino.h"
#include "DispenserData.h"

DispenserData::DispenserData()
{
  // Constructor. Initialises default values.
  _productCost = 0.01;
  _productName = "Fictional Product"; // Max 17 characters
  _helperText = "Tap card to activate";
  _cupSize = 0.23659;
  _productWeight = 0;
  _productDensity = 410;
}

float DispenserData::getProductCost()
{
  return _productCost;
}

String DispenserData::getProductName()
{
  return _productName;
}

String DispenserData::getHelperText()
{
  return _helperText;
}

unsigned int DispenserData::getProductWeight()
{
  return _productWeight;
}

float DispenserData::weightToPrice(unsigned int weight)
{
  // rounds price to the nearest cent
  return roundf(weight * _productCost * 100) / 100;
}

float DispenserData::weightToCups(unsigned int weight)
{
  // cups = weight / (cup size * density)
  // Rounded to nearest hundredth
  return roundf((weight / (_cupSize * _productDensity)) * 100) / 100;
}

void DispenserData::setProductCost(float cost)
{
  _productCost = cost;
}

void DispenserData::setProductName(String name)
{
  _productName = name;
}

void DispenserData::setHelperText(String text)
{
  _helperText = text;
}

void DispenserData::setProductDensity(unsigned int density)
{
  _productDensity = density;
}

void DispenserData::updateProductAmt(unsigned int weight)
{
  _productWeight = weight;
}

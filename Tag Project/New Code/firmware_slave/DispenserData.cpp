/**
 *  Helper class to contain, access, and set the all
 *  dispenser-related data. 
 */ 
#include "Arduino.h"
#include "DispenserData.h"

DispenserData::DispenserData()
{
  // Constructor. Initialises default values.
  _productCost = 4.50; // Organic Almonds
//  _productCost = 0.45; // Fusilli Pasta
//  _productCost = 0.25; // Sugar
  _productName = "Organic Almonds"; // Max 17 characters 
//  _productName = "Fusilli Pasta"; // Max 17 characters 
//  _productName = "Brown Sugar"; // Max 17 characters 
  _helperText = "Tap card to activate";
  _cupSize = 0.23659; // L in cup
  _productWeight = 0; 
  _productDensity = 583.29; //Almonds density in kg/m3
//  _productDensity = 358.63; //Fusilli Pasta density in kg/m3
//  _productDensity = 929.89; //Sugar density in kg/m3
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

float DispenserData::getProductWeight()
{
  return _productWeight;
}

double DispenserData::weightToPrice(double weight_in_grams)
{
  // rounds price to the nearest cent
  return roundf(weight_in_grams * _productCost) / 100;
}

double DispenserData::weightToCups(double weight_in_grams)
{
  // cups = weight / (cup size * density)
  // Rounded to nearest hundredth
  return roundf((weight_in_grams) / (_cupSize * _productDensity));
}

float DispenserData::setProductCost(float cost)
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

float DispenserData::setProductDensity(float density)
{
  _productDensity = density;
}

void DispenserData::updateProductAmt(float weight)
{
  _productWeight = weight;
}

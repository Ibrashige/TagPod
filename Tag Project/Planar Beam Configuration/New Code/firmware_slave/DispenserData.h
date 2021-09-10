/**
 *  Helper class to contain, access, and set all
 *  dispenser-related data. 
 */ 
#ifndef DispenserData_h
#define DispenserData_h

#include "Arduino.h"

class DispenserData
{
  public:
    DispenserData();
    float getProductCost();
    String getProductName();
    String getHelperText();
    float getProductWeight();
    double weightToPrice(double weight_in_grams);
    double weightToCups(double weight_in_grams);
    float setProductCost(float cost);
    void setProductName(String name);
    void setHelperText(String text);
    float setProductDensity(float density);
    void updateProductAmt(float weight_in_grams);
  private:
    float _productCost;  // $ / 100g
    String _productName;
    String _helperText;
    float _cupSize; // Volume of US customary cup (recipes) in L
    float _productWeight;
    float _productDensity; // kg / m^3
};

#endif

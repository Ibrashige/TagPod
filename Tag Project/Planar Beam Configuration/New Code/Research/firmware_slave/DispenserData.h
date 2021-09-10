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
    float weightToPrice(float weight);
    float weightToCups(float weight);
    void setProductCost(float cost);
    void setProductName(String name);
    void setHelperText(String text);
    void setProductDensity(unsigned int density);
    void updateProductAmt(float weight);
  private:
    float _productCost;  // $ / 100g
    String _productName;
    String _helperText;
    float _cupSize; // Volume of US customary cup (recipes) in L
    unsigned int _productWeight;
    unsigned int _productDensity; // kg / m^3
};

#endif

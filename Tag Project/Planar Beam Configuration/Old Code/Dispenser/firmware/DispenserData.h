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
    unsigned int getProductWeight();
    float weightToPrice(unsigned int weight);
    float weightToCups(unsigned int weight);
    void setProductCost(float cost);
    void setProductName(String name);
    void setHelperText(String text);
    void setProductDensity(unsigned int density);
    void updateProductAmt(unsigned int weight);
  private:
    float _productCost;  // $ / 100g
    String _productName;
    String _helperText;
    float _cupSize; // Volume of US customary cup (recipes) in L
    unsigned int _productWeight;
    unsigned int _productDensity; // kg / m^3
};

#endif

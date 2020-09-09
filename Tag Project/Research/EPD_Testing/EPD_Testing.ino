// Testing  DispenserData
  
    DispenserData dpData;
   Serial.println(
     "default productCost: " + String(dpData.getProductCost()) + "\n"
     "default productName: " + String(dpData.getProductName()) + "\n"
     "default helperText: "  + String(dpData.getHelperText())  + "\n"
     "default productWeight: " + String(dpData.getProductWeight())  + "\n"
   );
   dpData.setProductCost(0.75);
   dpData.setProductName(String("CHEERIOS"));
   dpData.updateProductAmt(1500);
   Serial.println(
     "new productCost: " + String(dpData.getProductCost()) + "\n"
     "new productName: " + String(dpData.getProductName()) + "\n"
     "new productWeight: " + String(dpData.getProductWeight())    + "\n"
   );
   Serial.println(
     "Price of 250 g: " + String(dpData.weightToPrice(250)) + "\n"
     "250 g to cups: "  + String(dpData.weightToCups(250))  + "\n"
   );

   // Testing DispenserUI
  
   DispenserUI dpUI;
   dpUI.clearScreen();
   dpUI.displayProductInfo(
     dpData.getProductName(),
     dpData.getProductCost(),
     dpData.getHelperText()
   );
   delay(7000);
   uint16_t weight;
   float price, cups;
   for (int count = 1; count < 60; count++) {
     weight =  count * 5;
     price = dpData.weightToPrice(weight);
     cups =  dpData.weightToCups(weight);   
     dpUI.displaySaleInfo(price, weight, cups);      
   }
   delay(7000);
   dpUI.clearScreen();
   Serial.println("Done Testing");


   Testing Controller
   dp.showProductScreen();
   delay(1500);
   dp.showSaleScreen(500);
   delay(3000);
   dp.showSaleScren(100);
   delay(3000);
   dp.showSaleScreen(50);
   delay(3000);
   dp.showSaleScreen(1);
   delay(3000);

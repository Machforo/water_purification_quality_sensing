# water_purification_quality_sensing
In case of emergencies especially during hilly areas , people suffer from lack of clean potable water. Water is available but one cannot find whether it is suitable for drinking or not. Even such conditions arise that people don't even get water to wash their hands. Our product comes very useful in such conditions.

Our product primarily aims to provide a solution by providing potable water to the people suffering during calamity.

Basically our product contains two main functions Filtration and Quality Sensing.(there are no products available presently in the market which does both in a affordable price). First the water is sucked in through a pipe into our product(works for flowing water as well). Then it undergoes three stages of filtration removing dirt etc in the first stage, smaller particles upto the size of bacteria and viruses in the second stage and bad odour and other impurities like arsenic in the third stage.

Now the products that are available in the market currently do filtration (there are various other methods) but after a certain time the quality of filters starting to degrade without the consumer realising thus one coninues to drink that water having faith on filters but is under threat of diseases due to consumption of bad water. Here comes the Quality Sensing part of our product.

To do Quality Sensing we take data from two sensors TDS and pH sensor. The thing to note is that both the parameters are not sufficient alone to give the water quality at a good accuracy, thus we created a new parameter using both by creating a Machine learning model using SVM(Support Vector Machine) that will classify the water based on tds and ph values into three classes:
GREEN : the water is fit to drink and it is potable
YELLOW:  the water is potable but not fit to drink
RED: Filters are degraded, water is very much unhealthy ,unfit for any consumption

Due to small size the product is easily portable and could also be used for hikers/trekkers.

Though the main aim of our product was to provide potable water to the needy during any emergencies.

The repo contains a aurdino file and the ML model used.



 

#include "typewise-alert.h"
#include <stdio.h>

// Function to infer breach type based on temperature and limits
BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
    if (value < lowerLimit) return TOO_LOW;
    if (value > upperLimit) return TOO_HIGH;
    return NORMAL;
}
// status print
void Print_status(BreachType breachType)
{
            // Combine breach type handling into one block
        const char* message ;
    if (breachType == TOO_LOW)
        printf ("Hi, the temperature is too low\n");
    else if (breachType == TOO_HIGH) 
        printf("Hi, the temperature is too high\n" );
    else 
        printf ("");        
}

// Function to get upper limit based on cooling type
int getUpperLimit(CoolingType coolingType) {
    static const int upperLimits[] = { 35, 45, 40, 0 }; // 0 is default for unknown types
    return (coolingType >= PASSIVE_COOLING && coolingType <= MED_ACTIVE_COOLING) 
           ? upperLimits[coolingType] 
           : upperLimits[3];
} 


// Function to classify temperature breach based on cooling type and temperature
BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC) {
    int upperLimit = getUpperLimit(coolingType);
    return inferBreach(temperatureInC, 0, upperLimit);
}

// Function to send alert based on breach type
void sendAlert(AlertTarget alertTarget, BreachType breachType) {
    if (alertTarget == TO_CONTROLLER) {
        const unsigned short header = 0xfeed;
        printf("Header: %x, BreachType: %d\n", header, breachType);
    } else if (alertTarget == TO_EMAIL) {
        const char* recipient = "a.b@example.com";
        printf("To: %s\n", recipient);
        Print_status(breachType);
    }
} 



// Main function to check temperature and send alerts based on breach and target
void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {
    BreachType breachType = classifyTemperatureBreach(batteryChar.coolingType, temperatureInC);
    sendAlert(alertTarget, breachType);
} 



#include "typewise-alert.h"
#include <stdio.h>

// Function to infer breach type based on temperature and limits
BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
    if (value < lowerLimit) return TOO_LOW;
    if (value > upperLimit) return TOO_HIGH;
    return NORMAL;
}

// Function to get upper limit based on cooling type
int getUpperLimit(CoolingType coolingType) {
    switch (coolingType) {
        case PASSIVE_COOLING: return 35;
        case HI_ACTIVE_COOLING: return 45;
        case MED_ACTIVE_COOLING: return 40;
        default: return 0; // Default lower limit, no need to handle unknown types here
    }
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
        if (breachType == TOO_LOW) {
            printf("Hi, the temperature is too low\n");
        } else if (breachType == TOO_HIGH) {
            printf("Hi, the temperature is too high\n");
        }
    }
}

// Main function to check temperature and send alerts based on breach and target
void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {
    BreachType breachType = classifyTemperatureBreach(batteryChar.coolingType, temperatureInC);
    sendAlert(alertTarget, breachType);
} 



#include "typewise-alert.h"
#include <stdio.h>

// Function to infer breach type based on temperature and limits
BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
    if (value < lowerLimit) {
        return TOO_LOW;
    }
    if (value > upperLimit) {
        return TOO_HIGH;
    }
    return NORMAL;
}

// Function to classify temperature breach based on cooling type and temperature
BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC) {
    int lowerLimit = 0;
    int upperLimit = 0;

    switch (coolingType) {
        case PASSIVE_COOLING:
            upperLimit = 35;
            break;
        case HI_ACTIVE_COOLING:
            upperLimit = 45;
            break;
        case MED_ACTIVE_COOLING:
            upperLimit = 40;
            break;
        default:
            return NORMAL; // Default case for unknown cooling types
    }

    return inferBreach(temperatureInC, lowerLimit, upperLimit);
}

// Function to send alert based on breach type
void sendAlert(AlertTarget alertTarget, BreachType breachType) {
    switch (alertTarget) {
        case TO_CONTROLLER:
            {
                const unsigned short header = 0xfeed;
                printf("Header: %x, BreachType: %d\n", header, breachType);
            }
            break;
        case TO_EMAIL:
            {
                const char* recipient = "a.b@example.com";
                printf("To: %s\n", recipient);
                switch (breachType) {
                    case TOO_LOW:
                        printf("Hi, the temperature is too low\n");
                        break;
                    case TOO_HIGH:
                        printf("Hi, the temperature is too high\n");
                        break;
                    case NORMAL:
                        // No action needed for normal
                        break;
                }
            }
            break;
        default:
            // Handle unexpected alert target
            break;
    }
}

// Main function to check temperature and send alerts based on breach and target
void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {
    BreachType breachType = classifyTemperatureBreach(batteryChar.coolingType, temperatureInC);
    sendAlert(alertTarget, breachType);
} 


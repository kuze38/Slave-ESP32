#include <Arduino.h>
#include <SPI.h>
#include <LoRa.h>
#include "comms.h"
#include "Motor_handler.h" 

#define BAUD_RATE    9600
#define LORA_MHZ     433E6
#define MOTOR_A_PIN1 25
#define MOTOR_A_PIN2 26
#define MOTOR_B_PIN1 27
#define MOTOR_B_PIN2 14
#define ENCODER_A    34
#define ENCODER_B    35
#define LORA_SS      18
#define LORA_RST     14
#define LORA_DIO0    26
#define RESET_LORA   1

void setup()
{
    pinMode( MOTOR_A_PIN1, OUTPUT );
    pinMode( MOTOR_A_PIN2, OUTPUT );
    pinMode( MOTOR_B_PIN1, OUTPUT );
    pinMode( MOTOR_B_PIN2, OUTPUT );
    pinMode( ENCODER_A, INPUT );
    pinMode( ENCODER_B, INPUT );

    Serial.begin( BAUD_RATE );
    while ( !Serial );

    // Initialize LoRa
    LoRa.setPins( LORA_SS, LORA_RST, LORA_DIO0 );
    if ( !LoRa.begin( LORA_MHZ ) ) 
    {
        Serial.println( "LoRa fail" );
        while ( RESET_LORA );
    }
    Serial.println("LoRa success");
}

void loop()
{
    handle_LoRa_command();
}

#include <Arduino.h>
#include "LoRa.h"
#include "comms.h"
#include "Motor_handler.h"

#define MOTOR_A_PIN1 25
#define MOTOR_A_PIN2 26
#define MOTOR_B_PIN1 27
#define MOTOR_B_PIN2 14

void move_motor( tMovement command ) 
{
    switch( command ) 
    {
        case( MOVEMENT_FORWARD ):
        {
            digitalWrite( MOTOR_A_PIN1, HIGH );
            digitalWrite( MOTOR_A_PIN2, LOW );
            digitalWrite( MOTOR_B_PIN1, HIGH );
            digitalWrite( MOTOR_B_PIN2, LOW );
            break;
        }
        case( MOVEMENT_BACKWARD ):
        {
            digitalWrite( MOTOR_A_PIN1, LOW );
            digitalWrite( MOTOR_A_PIN2, HIGH );
            digitalWrite( MOTOR_B_PIN1, LOW );
            digitalWrite( MOTOR_B_PIN2, HIGH );
            break;
        }
        case( MOVEMENT_RIGHT ):
        {
            digitalWrite( MOTOR_A_PIN1, HIGH );
            digitalWrite( MOTOR_A_PIN2, LOW );
            digitalWrite( MOTOR_B_PIN1, LOW );
            digitalWrite( MOTOR_B_PIN2, HIGH );
            break;
        }
        case( MOVEMENT_LEFT ):
        {
            digitalWrite( MOTOR_A_PIN1, LOW );
            digitalWrite( MOTOR_A_PIN2, HIGH );
            digitalWrite( MOTOR_B_PIN1, HIGH );
            digitalWrite( MOTOR_B_PIN2, LOW );
            break;
        }
        default:
        {
            digitalWrite( MOTOR_A_PIN1, LOW );
            digitalWrite( MOTOR_A_PIN2, LOW );
            digitalWrite( MOTOR_B_PIN1, LOW );
            digitalWrite( MOTOR_B_PIN2, LOW );
            break;
        }
    }
}

String command_string( tMovement command )
{
    switch (command) 
    {
        case( MOVEMENT_FORWARD ):
        {
            return "MOVE_FORWARD";
        }
        case( MOVEMENT_BACKWARD ):
        {
            return "MOVE_BACKWARD";
        }
        case( MOVEMENT_RIGHT ):
        {
            return "MOVE_RIGHT";
        }
        case( MOVEMENT_LEFT ): 
        {
            return "MOVE_LEFT";
        }
        default: 
        {
            return "UNKNOWN_COMMAND";
        }
    }
}

void handle_LoRa_command() 
{
    int packet_size = LoRa.parsePacket();
    if( packet_size ) 
    {
        String received = "";
        while( LoRa.available () )
        {
            received += ( char )LoRa.read();
        }
        tMovement command = ( tMovement )received.toInt();
        String command_str = command_string( command );
        Serial.print( "Command Received: " );
        Serial.println( command_str );
        move_motor( command );
    }

}

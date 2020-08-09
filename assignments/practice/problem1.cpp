/** @file problem1.cpp
 *  @brief connects to thingers.io and sends data through MQTT protocol using Shunya Interfaces
 *  
 *  
 *  @author Dibyendu Biswas 
 *  @bug I didn't find any 
 */

/*
 *#####################################################################
 *  Initialization block
 *  ---------------------
 *  This block contains initialization code for this particular file.
 *  It typically contains Includes, constants or global variables used
 *  throughout the file.
 *#####################################################################
 */

/* Standard Includes */
#include <cstdio>
#include <iostream>
#include <errno.h>
#include <si/shunyaInterfaces.h>
/* RapidJSON Includes */

#include "include/rapidjson/document.h"
#include "include/rapidjson/writer.h"
#include "include/rapidjson/stringbuffer.h"
#include "include/rapidjson/filereadstream.h"
#include "include/rapidjson/filewritestream.h"
#include "include/rapidjson/prettywriter.h"

using namespace rapidjson;
using namespace std;

/*
 *#####################################################################
 *  Process block
 *  -------------
 *  Solve all your problems here 
 *#####################################################################
 */


/************************** 
 * Error-handling functions
 **************************/

/* $begin unixerror */

void unix_error(char *msg) /* unix-style error */
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(0);
}
/* $end unixerror */

void posix_error(int code, char *msg) /* posix-style error */
{
    fprintf(stderr, "%s: %s\n", msg, strerror(code));
    exit(0);
}

void app_error(char *msg) /* application error */
{
    fprintf(stderr, "%s\n", msg);
    exit(0);
}
/* $end errorfuns */

FILE *Fopen(const char *filename, const char *mode)
{
   FILE *fp;

   if ((fp = fopen(filename, mode)) == NULL)
   unix_error((char*)"Fopen error");

   return fp;
}

void Fclose(FILE *fp) 
{
    if (fclose(fp) != 0)
    unix_error((char*)"Fclose error");
}
 
/* -----------------------------------------*/


/** 
 *  @brief Description on main
 *  
 *  Connects to thingers.io and sends data through MQTT protocol using Shunya Interfaces
 *
 *  @return List all Function returns 
 */

int main ()
{
        /* Initialize the Library*/
        initLib();
        
        /* 1. Parse a JSON string into DOM. */
        /* Open the example.json file in read mode */
        FILE* fp = Fopen("MQTT.json", "rb"); 

        /* Declare read buffer */
        char readBuffer[65536];

        /* Declare stream for reading the example stream */
        FileReadStream is(fp, readBuffer, sizeof(readBuffer));

        /* Declare a JSON document. JSON document parsed will be stored in this variable */
        Document d;

        /* Parse example.json and store it in `d` */    
        d.ParseStream(is);

        /* Close the example.json file*/
        Fclose(fp);

        /* Create New Instance */
        mqttObj broker1 = newMqtt(is);
        /* Connect to broker */
        mqttConnect(&broker1) ;
        /* Publish to topic */
        mqttPublish(&broker1, "topic"," Data to be sent") ;                                     // publish to thingers.io and send the data that needs to be sent

        return 0;
        
}


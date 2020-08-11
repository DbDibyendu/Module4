/** @file problem2.cpp
 *  @brief Data Transfer from ADC to InfluxDB
 *  
 *  Reading Data from ADC using shunya interface and sending data to InfluxDB
 *  Writing config.json file and saving the data in a output file too with Unix Timestamp
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
 *  @brief Timestamp
 *  
 *  returns timestamp of linux system
 *
 *  @return integer valude of timestamp
 */

long Time_Stamp()
{       
          unsigned long timestamp=(unsigned long)time(NULL);                         //getting the value of timestamp
          return timestamp;
}

/** 
 *  @brief Data Transfer from ADC to InfluxDB
 * 
 *  Reading Data from ADC using shunya interface and sending data to InfluxDB
 *  Writing config.json file and saving the data in a output file too
 *
 *  @return 0
 */

int main ()
{
        /* Initialize the Library*/
        initLib();

        int time= Time_Stamp();                                                  // calling the Time_stamp function 

        /* Reads the data from adc */

        int16_t value = getAdc(1);                                              // Gets the status of any generic GPIO pin
        int16_t bpm = getBpm();                                                 // Gets the Heart rate from supported sensors.
        int16_t cm = getCm();                                                   // Gets the distance from supported sensors.
        int16_t lph = getLph();                                                 //  Gets the Flow from supported sensors.
        

        /* 1. Parse a JSON string into DOM. */
        /* Open the example.json file in read mode */
        FILE* fp = Fopen("InfluxDB.json", "rb"); 

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

        // Creates a new Influxdb Instance
        influxdbObj testdb = newInfluxdb(is);

        // Send data to InfluxDB        
        writeDbInflux (testdb,"Value: %d \n HeartRate: %d \n Distance: %d \n Flow: %d\n UNIX Timestamp: %d", value,bpm,cm,lph,time);

        /* Declare an object to store the JSON document in  */
        Document e;

        /* Declare the First JSON object */
        e.SetObject();

        /* Declare new JSON object called as wireless */
        Value ADC_data(kObjectType);

        /* Lets store the JSON object members for wireless */
        ADC_data.AddMember("Value", "%d",value, e.GetAllocator());
        ADC_data.AddMember("HeartRate", "%d",bpm, e.GetAllocator());
        ADC_data.AddMember("Distance", "%d",cm, e.GetAllocator());
        ADC_data.AddMember("Flow", "%d",lph, e.GetAllocator());
       
        /* Add this object as a member to the JSON  document `e`*/ 
        e.AddMember("UNIX Timestamp","%d", time, e.GetAllocator());

        /* Add this object as a member to the JSON  document `e`*/
        e.AddMember("ADC Data", ADC_data, e.GetAllocator());

        /* Open the output.json file in write mode */
        FILE *out = Fopen("problem2_output.json", "wb");

        /* Declare write buffer */      
        char writeBuffer[65536];

        /* Declare stream for writing the output stream */
        FileWriteStream os(out, writeBuffer, sizeof(writeBuffer));

        /* Make the output easier to read for Humans (Pretty) */
        PrettyWriter<FileWriteStream> writer(os);

        /* Write the JSON document `e` into the file `output.json`*/
        e.Accept(writer);

        /* Close the output.json file*/
        Fclose(out);


        
        /* Open the config.json file in write mode to configure it*/
        FILE *config = Fopen("/etc/shunya/interfaces/config.json", "wb");

        /* Declare write buffer */      
        char write[65536];

        /* Declare stream for writing the output stream */
        FileWriteStream os(config, writeBuffer, sizeof(write));

        /* Make the output easier to read for Humans (Pretty) */
        PrettyWriter<FileWriteStream> writer(os);

        /* Write the JSON document `e` into the file `config.json`*/
        e.Accept(writer);

        /* Close the output.json file*/
        Fclose(config);

        return 0;
        
}


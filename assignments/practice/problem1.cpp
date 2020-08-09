/** @file problem1.cpp
 *  @brief Give a description of the file 
 *  
 *  Give full description of the file 
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
 *  @brief Description on main
 *  
 *  Full description of the function
 *
 *  @return List all Function returns 
 */

int main ()
{
        /* Initialize the Library*/
        initLib();

        int time=Time_Stamp();
        cout<<time<<endl;


        int16_t value = getAdc(1);                                              // Gets the status of any generic GPIO pin
        int16_t bpm = getBpm();                                                 // Gets the Heart rate from supported sensors.
        int16_t cm = getCm();                                                   // Gets the distance from supported sensors.
        int16_t lph = getLph();                                                 //  Gets the Flow from supported sensors.
        return 0;
        
}


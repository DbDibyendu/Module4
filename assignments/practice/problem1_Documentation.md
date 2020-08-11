# Steps to Store data in *Buckets* and Show data in *DashBoard*


## 1.Storing data in Buckets

Configure a data bucket to store data from an specific MQTT topic just requires going to bucket section of the main menu and pressing the "**Add Bucket**" button to access the "**new bucket form**" in which introduce the topic configuration, as has been made in the image below:  

![](https://gblobscdn.gitbook.com/assets%2F-LpXqB3J1BMD5s4OpYSg%2F-M3Qp23pPytkxIF_F6FF%2F-M3SA7uYCEIiQQ9CDo7f%2Fimage.png?alt=media&token=6ae324cb-242e-4577-ba35-639130e0fe7f)

##### The next parameters needs to be configured: 

**Bucket Id:** Unique identifier for the bucket.                  
**Bucket name:** Use a representative name to remember the bucket scope, like WeatherData.        
**Bucket description:** Fill here any description with more details, like Temperature and humidity in house.          
**Enabled:** Data bucket recording can be enabled or disabled. Just switch it on to enable it.                                                                      
**Data Source:** Commonly this defines the Thinger.io device or resource that will be subscribed by the server. In this situation "From MQTT Topic" must be placed                
**MQTT Topic:** place here the MQTT topic that will be subscribed by the server                     
> Use JSON as the payload type for the device messages stored by buckets.

##### Review Bucket data

Once the data bucket has been configured and the data is sent in **JSON** format, and it started to record data from a device or from write calls, it will display the information inside a table. 



![](https://gblobscdn.gitbook.com/assets%2F-LpXqB3J1BMD5s4OpYSg%2F-LpXslUdklMPEtHLTfE2%2F-LpXt-oGEinfBoSgqHoe%2FIoTBucketData.png?alt=media)

## 2.Showing data to dashboard


Now that the MQTT data is being stored into the data bucket, it is possible to show it on dashboards, where multiple widgets can be used to create real-time or historical representations by selecting the bucket as the data source as it is shown in the image below: 
 
 
 ![](https://gblobscdn.gitbook.com/assets%2F-LpXqB3J1BMD5s4OpYSg%2F-M3elqHTZoxhzRy1glm5%2F-M3eoc2Y4YUh7VAiZvFj%2Fimage.png?alt=media&token=9254beef-cbd5-4be1-9e2f-55816a884deb)


Dashboard widgets can show data from different devices, and been configured to create flexible data representations as we have explained in the dashboard section of this documentation. 

![](https://gblobscdn.gitbook.com/assets%2F-LpXqB3J1BMD5s4OpYSg%2F-M3SCtOUKqTfXgoCQU2j%2F-M3SE8P19rEYMk6N3Ikr%2Fimage.png?alt=media&token=c7c955a7-1466-4090-ab72-a5577887f7dc)
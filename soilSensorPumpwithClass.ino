  //Soil detection pump
  // Jesus Gutierrez
  //jgutierrez@mail.csuchico.edu

  
  // RTC BLYNK DEFINITIONS ------
  #define BLYNK_PRINT Serial
  #include <ESP8266WiFi.h>
  #include <BlynkSimpleEsp8266.h>
  #include <TimeLib.h>
  #include <WidgetRTC.h>
  #include "header.h"
  char auth[] = ""; // Your auth given to you in the app
  // Your WiFi credentials
  char ssid[] = "";
  char pass[] = "";
  BlynkTimer timer; 
  WidgetRTC rtc;
  //----------------------------
  
  #define pumpPin 04
  int flag = 500; //soil too low, trigger pump
  int initiation_flag=0;
  int seconds_of_pumping =30;
  long start_time=80000;// default start time unless changed in app
  get_time t;
  

  BLYNK_WRITE(V2)
  {
  flag = param.asInt(); // assigning incoming value from pin V1 to a SENSITIVITY
  // You can also use:
  // String i = param.asStr();
  // double d = param.asDouble();
  Serial.print("SOIL LEVEL = ");
  Serial.println(flag);
  }

  BLYNK_WRITE(V3) {
  TimeInputParam t(param);

  // Process start time

  if (t.hasStartTime())
    {
      start_time=set_time(t.getStartHour(),t.getStartMinute());
       Serial.println(start_time);
//      Serial.println(String("Start: ") +
//                     t.getStartHour() + ":" +
//                     t.getStartMinute());
    }
  
  }
  void setup() {
    Serial.begin(9600); // opens serial port, sets data rate @9600
    pinMode(pumpPin,OUTPUT); //Configures the specified pin to behave either as an input or an output
    digitalWrite(pumpPin,LOW); //LOW = OFF
    pinMode(A0,INPUT);
    //RTC BLYNK -----------------
    Blynk.begin(auth, ssid, pass);
    rtc.begin();
    // Display digital clock every 1 seconds
    timer.setInterval(1000L, get_clock); //function call to get time and start timer, will send time to digital pin V1
    //---------------------------
    
  }
//  int start_time = 194300; // Example:  83055 = 8:30:55 am
  
  void loop() {
  //  RTC BLYNK -------
    Blynk.run();
    timer.run();
   // ------------------
   int cur_time_ = t.get_cur_time();
//   Serial.println(cur_time_);
//   Serial.println(start_time);
   if(cur_time_ == start_time  )
   {
      run_pump(); 
    }
    delay(1);
    int soil_level_for_graph=get_soil_reading();
    Blynk.virtualWrite(V4, soil_level_for_graph);
  }
  void run_pump()
  {
    int soil_level = get_soil_reading(); // function call to get AVG soil reading
//    Serial.println(soil_level);
//    Serial.println(flag);
    
    // in order to trigger pump, soil read must be accurate N times
    if(soil_level > flag){
      initiation_flag++;
      Serial.print("checked: "); Serial.print(initiation_flag); Serial.print(" times"); Serial.println(); // prints progress
    }
    else{
      initiation_flag =0;
    }
    
    if(initiation_flag == 10){
      
      digitalWrite(pumpPin,INPUT_PULLUP);
      int cur_time =t.get_cur_time();
      int finish_time = start_time+ seconds_of_pumping; // beware, do not set second to add more than 59 secs
      while(cur_time !=finish_time){
        cur_time =t.get_cur_time();
        delay(1000);
        //Serial.println(cur_time);
       // Serial.println(finish_time);
      }
      digitalWrite(pumpPin,LOW);
      initiation_flag=0;
    }
    
  }
  
  
  
  

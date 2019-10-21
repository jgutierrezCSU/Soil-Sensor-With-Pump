#ifndef _HEADER_H
#define _HEADER_H

int soil_level=0;

int get_soil_reading()
{
  for (int i=0; i<=100; i++)
  {
      soil_level = soil_level + analogRead(A0);
  }
    soil_level = soil_level/100;
    //Serial.println(soil_level); 
    return soil_level;  
}
int concateTime(int a,int b)
  {
    int x= a*100 + b;
    return x;
  }
  
  int concateTime_w_sec(int x,int c)
  {
    int w_secs=x*100+c;
    return w_secs;
  }
  class get_time{
    public:
  int get_cur_time()
    {
      int a=hour();
      int b=minute();
      int c=second();
      int no_sec_time = concateTime(a,b); // will concatenate Hours w/ Mins
      int time_=concateTime_w_sec(no_sec_time,c);// will conctanate Seconds
      return time_;
    }

  };
 
  
  void get_clock()
  {
    // You can call hour(), minute(), ... at any time
    
    String currentTime = String(hour()) + ":" + minute() + ":" + second();
//    String currentDate = String(day()) + " " + month() + " " + year();
     
    // Send time to the App
    Blynk.virtualWrite(V1, currentTime);
    // Send date to the App
//    Blynk.virtualWrite(V2, currentDate);
    
  /* DEBUGGING
  int a=hour();
  int b=minute();
  int c=second();
  int no_sec_time = concateTime(a,b); // will concatenate Hours w/ Mins
  int time_=concateTime_w_sec(no_sec_time,c);// will conctanate Seconds
  //Serial.println(time_);
  Blynk.virtualWrite(V1, time_);
  // Example:  83055 = 8:30:55 am
  */
  }
  int set_time(int a , int b)
  {
    int no_sec_time = concateTime(a,b);
    return no_sec_time*100;
  }
  
  
#endif

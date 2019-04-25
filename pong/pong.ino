//Authors: Hannah Seccia and Solomon Hatchett
//Date: 4/11/2019
//Description: LED Arduino Pong Game

int scoreCountP1 = 0;
int scoreCountP2 = 0;
bool p1Scored = false;     
bool p2Scored = false;

int speed = 100;
int speedVar;

int lightCount = 1;

int p1Pin = 5;
int p2Pin = 4;

bool successfulButton = false;
bool failButton = false;
unsigned long lastInterrupt;

bool lightMode = true;              //whether the lights are on
bool startUp = true;                //when a new round is starting

void setup() 
{
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(p1Pin, OUTPUT);
  pinMode(p2Pin, OUTPUT);
  pinMode(3, INPUT);
  pinMode(2, INPUT);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(3), p1ButtonClick, RISING);
  attachInterrupt(digitalPinToInterrupt(2), p2ButtonClick, RISING);
  
}

void loop() 
{
    
  functionRight();      //this only runs once even though it's in the loop (connected two-way "loop" with functionRight and functionLeft)
    
}


void functionRight()
{
  
  if (lightMode)
  { 
    speedVar = 1000 - speed;
  
    if (lightCount == 1)
    {
      if (startUp)  //first run of the round
      {
        digitalWrite(13, HIGH);
        delay(speedVar);
        digitalWrite(13, LOW);
        lightCount++;
      }
      
      else
      {
        if (successfulButton)
        {
          lightCount++;
        }
        else if (!successfulButton)
        {
          digitalWrite(13, HIGH);
          delay(speedVar);
          digitalWrite(13, LOW);
          pointScored();
          
        }
      }
    }
  
    if (lightCount == 2)
    {
       if (successfulButton)
       {
          lightCount++;
          successfulButton = false;
       }
       else if (!successfulButton)
       {
         digitalWrite(12, HIGH);
         delay(speedVar);
         digitalWrite(12, LOW);
         lightCount++;
       }
      
    }
    if (lightCount == 3)
    {
      if (startUp)  
      {
        startUp = false;
      }

      if (failButton)
      {
        failButton = false;
        pointScored();
      }
      else
      {
        digitalWrite(11, HIGH);
        delay(speedVar);
        digitalWrite(11, LOW);
        Serial.println("3 reached");
        lightCount++;
      }
    }
    if (lightCount == 4)
    {
      if (failButton)
      {
        failButton = false;
        pointScored();
      }
      else
      {
        digitalWrite(10, HIGH);
        delay(speedVar);
        digitalWrite(10, LOW);
        lightCount++;
      }
    }
    if (lightCount == 5)
    {
      if (failButton)
      {
        failButton = false;
        pointScored();
      }
      else
      {
        digitalWrite(9, HIGH);
        delay(speedVar);
        digitalWrite(9, LOW);
        lightCount++;
      }
    }
    if (lightCount == 6)
    {
      if (failButton)
      {
        failButton = false;
        pointScored();
      }
      else
      {
        digitalWrite(8, HIGH);
        delay(speedVar);
        digitalWrite(8, LOW);
        lightCount++;
      }
    }
    if (lightCount == 7)
    {
      digitalWrite(7, HIGH);
      delay(speedVar);
      digitalWrite(7, LOW);
      lightCount++;
    }
    if (lightCount == 8)
    {
       functionLeft();              //left to right
    }
  }
  
}

void functionLeft()
{
  
  speedVar = 1000 - speed;

  if (successfulButton)
  {
    lightCount--;
  }
  else if (!successfulButton)
  {
    if (lightCount == 8)
    {
      digitalWrite(6, HIGH);
      delay(speedVar);
      digitalWrite(6, LOW);
      pointScored();
      
    }
  }

  if (successfulButton)
  {
    lightCount--;
    successfulButton = false;
  }
  else if (!successfulButton)
  {
    if (lightCount == 7)
    {
      digitalWrite(7, HIGH);
      delay(speedVar);
      digitalWrite(7, LOW);
      lightCount--;
    }
  }
  if (lightCount == 6)
  {
    if (failButton)
    {
        failButton = false;
        pointScored();
    }
    else
    {
      digitalWrite(8, HIGH);
      delay(speedVar);
      digitalWrite(8, LOW);
      lightCount--;
    }
  }
  if (lightCount == 5)
  {
    if (failButton)
    {
        failButton = false;
        pointScored();
    }
    else
    {
      digitalWrite(9, HIGH);
      delay(speedVar);
      digitalWrite(9, LOW);
      lightCount--;
    }
  }
  if (lightCount == 4)
  {
    if (failButton)
    {
        failButton = false;
        pointScored();
    }
    else
    {
      digitalWrite(10, HIGH);
      delay(speedVar);
      digitalWrite(10, LOW);
      lightCount--;
    }
  }
  if (lightCount == 3)
  {
    if (failButton)
    {
        failButton = false;
        pointScored();
    }
    else
    {
      digitalWrite(11, HIGH);
      delay(speedVar);
      digitalWrite(11, LOW);
      lightCount--;
    }
  }
  if (lightCount == 2)
  {
    digitalWrite(12, HIGH);
    delay(speedVar);
    digitalWrite(12, LOW);
    lightCount--;
  }
  if (lightCount == 1)
  {
    functionRight();    
  }
  
}

void pointScored()
{
     digitalWrite(11, HIGH);
     delay(2000);
     digitalWrite(11, LOW);
     delay(2000);
     digitalWrite(11, HIGH);
     delay(2000);
     digitalWrite(11, LOW);
     
     if (lightCount == 1)
     {
        if (scoreCountP1 == 3)
        {
          
          digitalWrite(p1Pin, HIGH);
          delay(1000);
          digitalWrite(p1Pin, LOW);
          delay(1000);
          digitalWrite(p1Pin, HIGH);
          delay(1000);
          digitalWrite(p1Pin, LOW);
          
          lightMode = false;
          delay(5000);
          restart();
          
           
        }
        else if (scoreCountP2 == 3)
        {
          digitalWrite(p2Pin, HIGH);
          delay(1000);
          digitalWrite(p2Pin, LOW);
          delay(1000);
          digitalWrite(p2Pin, HIGH);
          delay(1000);
          digitalWrite(p2Pin, LOW);
          
          lightMode = false;
          delay(5000);
          restart();
        }
        else
        {
          digitalWrite(p2Pin, HIGH);
          delay(1000);
          digitalWrite(p2Pin, LOW);
          delay(1000);
          digitalWrite(p2Pin, HIGH);
          delay(1000);
          digitalWrite(p2Pin, LOW);
          scoreCountP2++;
          scoreIncrease();
          
        }
        
     }
     else if (lightCount == 8)
     {
        if (scoreCountP1 == 3)
        {
          digitalWrite(p1Pin, HIGH);
          delay(1000);
          digitalWrite(p1Pin, LOW);
          delay(1000);
          digitalWrite(p1Pin, HIGH);
          delay(1000);
          digitalWrite(p1Pin, LOW);
          
          lightMode = false;
          delay(5000);
          restart();
         
        }
        else if (scoreCountP2 == 3)
        {
          digitalWrite(p2Pin, HIGH);
          delay(1000);
          digitalWrite(p2Pin, LOW);
          delay(1000);
          digitalWrite(p2Pin, HIGH);
          delay(1000);
          digitalWrite(p2Pin, LOW);

          lightMode = false;
          delay(5000);
          restart();
          
        }
       else
       {
          digitalWrite(p1Pin, HIGH);
          delay(1000);
          digitalWrite(p1Pin, LOW);
          delay(1000);
          digitalWrite(p1Pin, HIGH);
          delay(1000);
          digitalWrite(p1Pin, LOW);
          scoreCountP1++;
          scoreIncrease();
       }
       
     
     }
     else if (lightCount != 1 && lightCount != 8 && p1Scored)
     {
        if (scoreCountP1 == 3)
        {
          digitalWrite(p1Pin, HIGH);
          delay(1000);
          digitalWrite(p1Pin, LOW);
          delay(1000);
          digitalWrite(p1Pin, HIGH);
          delay(1000);
          digitalWrite(p1Pin, LOW);
          
          lightMode = false;
          delay(5000);
          restart();
        }
        
        else if (scoreCountP2 == 3)
        {
          digitalWrite(p2Pin, HIGH);
          delay(1000);
          digitalWrite(p2Pin, LOW);
          delay(1000);
          digitalWrite(p2Pin, HIGH);
          delay(1000);
          digitalWrite(p2Pin, LOW);
         
          lightMode = false;
          delay(5000);
          restart();
          
        }
        else
        {
          digitalWrite(p1Pin, HIGH);
          delay(1000);
          digitalWrite(p1Pin, LOW);
          delay(1000);
          digitalWrite(p1Pin, HIGH);
          delay(1000);
          digitalWrite(p1Pin, LOW);
          scoreCountP1++;
          scoreIncrease();
        }
        
     }
     else if (lightCount != 1 && lightCount != 8 && p2Scored)
     {
        if (scoreCountP1 == 3)
        {
          digitalWrite(p1Pin, HIGH);
          delay(1000);
          digitalWrite(p1Pin, LOW);
          delay(1000);
          digitalWrite(p1Pin, HIGH);
          delay(1000);
          digitalWrite(p1Pin, LOW);
          
          lightMode = false;
          delay(5000);
          restart();
        }
        else if (scoreCountP2 == 3)
        {
          digitalWrite(p2Pin, HIGH);
          delay(1000);
          digitalWrite(p2Pin, LOW);
          delay(1000);
          digitalWrite(p2Pin, HIGH);
          delay(1000);
          digitalWrite(p2Pin, LOW);

          lightMode = false;
          delay(5000);
          restart();
          
        }
        else
        {
          digitalWrite(p2Pin, HIGH);
          delay(1000);
          digitalWrite(p2Pin, LOW);
          delay(1000);
          digitalWrite(p2Pin, HIGH);
          delay(1000);
          digitalWrite(p2Pin, LOW);
          scoreCountP2++;
          scoreIncrease();
          
        }
     }

}

void scoreIncrease()
{
    startUp = true;
    lightCount = 1;
    speed = 100;
    p1Scored = false;
    p2Scored = false;
    functionRight();
}

void p1ButtonClick()
{
  if(millis() - lastInterrupt > 200)
  {
    if(lightCount == 2 && !startUp)       //when button is pressed on the correct light for p1
    {
      successfulButton = true;
      speed += 200;
      lastInterrupt = millis();           //any other light besides the correct one and the point score lights
      
    }
    else if(lightCount != 2 && lightCount != 1 && lightCount != 8 && !startUp)
    {
      failButton = true;
      p2Scored = true;
      lastInterrupt = millis();  
    }
  }
}

void p2ButtonClick()
{
  if(millis() - lastInterrupt > 200)
  {
    if(lightCount == 7)                   //when button is pressed on the correct light for p2
    {
      successfulButton = true;
      speed += 200;
      lastInterrupt = millis();
    }
    else if(lightCount != 7 && lightCount != 1 && lightCount != 8 && !startUp)    //any other light besides the correct one and the point score lights
    {
      failButton = true;
      p1Scored = true;
      lastInterrupt = millis(); 
    }
  }
  
}
void restart()
{
  digitalWrite(13, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(11, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(7, HIGH);
  delay(1000);
  digitalWrite(13, LOW);
  digitalWrite(12, LOW);
  digitalWrite(11, LOW);
  digitalWrite(10, LOW);
  digitalWrite(9, LOW);
  digitalWrite(8, LOW);
  digitalWrite(7, LOW);
  delay(1000);
  
  startUp = true;
  lightMode = true;
  speed=100;
  lightCount = 1;
  scoreCountP1 = 0;
  scoreCountP2 = 0;
  p1Scored = false;
  p2Scored = false;
  functionRight();

}

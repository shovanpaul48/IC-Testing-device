

// the setup function runs once when you press reset or power the board
int arr[4] ={1 , 2, 3, 4};
int arr2[4]={9, 8, 7, 6};
int sum[];

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
//   digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
//   delay(1000);                       // wait for a second
//   digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
//   delay(1000);                       // wait for a second

  for(int i =0 ;i<= arr2.length();i++){
      sum[i] = (arr[i] + arr2[i]);
  }

  
  for(int i =0 ;i<= arr2.length();i++){
      Serial.println(sum[i]);
  }
}
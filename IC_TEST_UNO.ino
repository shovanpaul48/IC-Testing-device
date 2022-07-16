/* 


SL---->FUNCTION NAME  --------------------------------------------------> LINE NUMBER 
_______________________________________________________________________________________
1     setup()                                    38
2     loop()                                     48
3     get_IC_PIN_details()                       80
4     get_IC_PART_details()                      117
5     IC_Tester_switch                           153



*/


#include<Keypad.h>
const byte ROWS = 4;
const byte COLS = 3;

char Keys[ROWS][COLS] = {
    {'1','2','3'},
    {'4','5','6'},
    {'7','8','9'},
    {'*','0','#'},

};


// ---------- KEYPAD MAPPING --------------------------------------------------
byte rowPINS[ROWS]={2, 3, 4, 5};
byte colPINS[COLS]= {6, 7, 8};
Keypad customKeypad = Keypad(makeKeymap (Keys) , rowPINS, colPINS, ROWS, COLS);


// ---------- VARIABLE DEFINE------------------------------------------------
String inputString,IC_details;
int IC_pin_no, IC_part_no;



 void setup()
{
    Serial.begin(9600);  
    inputString.reserve(6); // maximum number of digit for a number is 10, change if needed
    Serial.println("This is a Samart IC testing device ");
    Serial.println("To Start the device please enter * ");
}


void loop(){   
    start();
}


void start(){
  String s1 = "The Number of pins  of the IC is : ",s2 ;
  String s3 = "The PART No. of the IC is : ",s4;
  char key = customKeypad.getKey();

    if (key) {
        Serial.println(key);
        
        if( key == '*'){
            Serial.println("The Device is now On ");
            inputString = get_IC_PIN_details();             // Getting the IC pin no from user 
            IC_pin_no = inputString.toInt();                // convert the string to integer 
            s2 = s1 + IC_pin_no;                             // IC_pin_no store the correct ic pin 
            Serial.println( s2 );

            inputString=""; 
            inputString= get_IC_PART_details();               // Getting the IC part no from the user 
            IC_part_no = inputString.toInt();                 // IC_pin_no store the correct ic pin 
            s4 = s3 + IC_part_no;                             
            Serial.println( s4 );

            IC_Tester_switch(IC_pin_no,IC_part_no);           // This function has a switch case to test the correct IC
        }
        else { Serial.println("Please enter * to turn on the device "); }
    }

}

// ------------------ THIS FUNCTION IS USED FOR GETTING THE PIN NUMBER OF THE IC -----------------------------------------
String get_IC_PIN_details(){
   
    int IC_pin_length = 2, IC_part_no,i = 0;             // Maximum 2 digit IC pin number availabe  like 14, 16, 24 ....

    Serial.println("Please Enter the Correct PIN no of the IC (After Enter the correct pin no please enter #  ) ");
    IC_details = "";
   
    // while( IC_pin != '#' || IC_pin != '*') {
    while (true){
        char IC_pin = customKeypad.getKey();
        // Serial.println("Enter : ");
        if( IC_pin ){ 
            if ( IC_pin >= '0' && IC_pin <= '9') {       // only act on numeric keys
                IC_details += IC_pin;                   // append new character to input string
                Serial.println(IC_details);
                i += 1;
            }
            else if( IC_pin == '#' || IC_pin == '*'){
                if(IC_details =="14" ||IC_details == "16" ){
                    // Serial.println(IC_details);
                    return IC_details;                   // return the IC pin  number
                }                      
                else{
                    Serial.println("Entered PIN no is not found !!! Please enter correct pin no ");
                    IC_details="";
                    IC_details=get_IC_PIN_details();
                    return IC_details;
                }
                  
            }
        }
    }
}


// ------------------ THIS FUNCTION IS USED FOR GETTING THE PART NUMBER OF THE IC -----------------------------------------
String get_IC_PART_details(){
   
    int IC_part_no,i = 0;                                       

    Serial.println("Please Enter the Correct Part no of the IC (After Enter the correct part no please Enter # ) ");
    IC_details = "";
    // while( IC_pin != '#' || IC_pin != '*') {
    while (true){
        char IC_part = customKeypad.getKey();
        // Serial.println("Enter : ");
        if( IC_part ){ 
            if ( IC_part >= '0' && IC_part <= '9') {       // only act on numeric keys
                IC_details += IC_part;                     // append new character to input string
                Serial.println(IC_details);
                i += 1;
            }
            else if( IC_part == '#' || IC_part == '*'){
                // if(IC_details =='14' ||IC_details == '16' ){
                    // Serial.println(IC_details);
                    return IC_details;                  // return the IC part  number
                  
            }
        }
    }
}

void display(bool arr[] , int size_arr ){
    String s1 = " GATE MATCHED",  s2 = " GATE NOT MATCHED";
    Serial.println("Inside DISPLAY ");
    for(int j=size_arr-1 ; j>=0 ;j-- ){
        if( arr[j] == true)
            Serial.println((j+1) + s1 );
        else
            Serial.println((j+1) + s2 );
    }
    start();
} 

// ------------------ THIS FUNCTION IS USED FOR CHOOSING COORCT IC FOR TEST -----------------------------------------


void IC_Tester_switch(int IC_pin, int IC_part){
    
    Serial.println("Inside SWITCH ");
    if( IC_pin == 14 ){
        switch (IC_part)
        {
        case 7400: TEST_7400();
            break;
        case 7401: TEST_7401();
            break;
        case 7402: TEST_7402();
            break;
        case 7404: TEST_7404();
            break;
        case 7405: TEST_7405();
            break;
        case 7406: TEST_7406();
            break;
        case 7407: TEST_7407();
            break;
        case 7408: TEST_7408();
            break;
        case 7409: TEST_7409();
            break;
        case 7410: TEST_7410();
            break;
        case 7411: TEST_7411();
            break;
        // case 7413: TEST_7404();
        //     break;
        
        
        default:
            break;
        }
    }
    
}

//----- This function used to check if the output properly match with actual outcome----------------------
void  IC_Output_Matching(String Actual_Outputs[] ,int Actual_Output_string_length, int total_gates,int combination, String Outputs[] ){
    
    String space= "     ";
    int temp1,temp2,bit1,bit2;
    bool  OUTPUT_match[total_gates]={};
    for(int i = 0 ;i < combination ;i++){
        temp1 = Outputs[i].toInt();                 // Outputs we get
        temp2 = Actual_Outputs[i].toInt();          // Actual Output
        Serial.println(temp1 + space + temp2);
        int len = Actual_Output_string_length -1 ;
        for(int m=0 ; m < Actual_Output_string_length ; m++){

            bit1 = temp1 % 10;
            bit2 = temp2 % 10;
            temp1 = temp1 / 10;
            temp2 = temp2 / 10;
            if( bit1 == bit2 ){
                Serial.println(bit1 + space + bit2);              
                if( OUTPUT_match[len] == false && i!=0){  
                    OUTPUT_match[len] = false;
                    Serial.println(" matched + ! false  ");
                }
                    
                else {
                    OUTPUT_match[len] = true;
                    Serial.println(" matched + true  ");
                }
                
                len--;
            }
            else{
                Serial.println(bit1 + space + bit2); 
                Serial.println(" not matched + false ");
                OUTPUT_match[len]=false;
                break;
                len --;
            }
        }
    }
    
    display(OUTPUT_match, total_gates);
    // return  OUTPUT_match;
}



//------ IC no match then use this function 
void default_TESTER(int OUTPUT_match, int size){
    TEST_7401();
}

//------ Input for 2 bit ---------------------------
String* Bit_2_input(int OUTPUT_pins[], int INPUT_pins[], int IN,int OUT,int TotG, int combination, int IN_pat[]){
    //IN=> No_inputs, OUT=>No_outputs, TotG=> Total_gates, combination=> Bit_combination , IN_pat=>Input_Pattern
    String OUTPUT_PATTERNS_gets[combination]={},Output_patterns="" , sk="OUTPUT----> ", sj="temp1----> ",sl="bit1----> ";
    int temp1 ,temp2, bit1, bit2 ;
    for( int i=0;i< combination ;i++){
        temp1 = IN_pat[i];
        Serial.println(sj + temp1);
        for(int j=0;j< IN;j++){
            bit1 = temp1%10;
            Serial.println(sl + bit1);
            temp1=temp1/10;
            if(j==0){
                Serial.println("j==0");
                for(int k=0; k< (IN*OUT);k++){
                    if(k%2 != 0){
                        digitalWrite(OUTPUT_pins[k],bit1);
                        Serial.println(OUTPUT_pins[k]); 
                    }
                }
            }
            else {
                Serial.println("j==1");
                for(int k=0; k< (IN*OUT);k++){
                    if(k%2 == 0){
                        digitalWrite(OUTPUT_pins[k],bit1);
                        Serial.println(OUTPUT_pins[k]); 
                    }
                }
            }
        }
        for(int l=0 ; l < OUT; l++) {                              // READING the value 
            Output_patterns +=  String( digitalRead(INPUT_pins[l]));
        }
        OUTPUT_PATTERNS_gets[i] = Output_patterns;
        Serial.println(sk + Output_patterns);
        Output_patterns = "";
    }
    return OUTPUT_PATTERNS_gets;
}




//------ INDIVIDUAL IC TESTING FUNCTION ------------------------------------
//==== 7400 ===========================
void TEST_7400(){
    // 14  2 4 7400  14  7 1,2,4,5,9,10,12,13  3,6,8,11  2-14-7-1,2,4,5,9,10,12,13-3,6,8,11  00,1111-01,1111-10,1111-11,0000 Quad 2-input NAND gate  00011011;1110 

    Serial.println("Testing 7400 .....");
    int No_inputs=2, No_outputs=4, Total_gates=4,Output_string_length=4,Bit_combination=4;
    int OUTPUT_pins[(No_inputs*Total_gates)] = {22, 23, 25, 26, 40, 41, 43, 44};   // Output Pin array 
    int INPUT_pins[No_outputs] = {24, 27, 39, 42};                    // Input Pin array
    int INPUT_PATTERNS_TO_OUTPUT_pins[Bit_combination] = {00,01,10,11};
    String OUTPUT_PATTERNS_FROM_INPUT_pins[Bit_combination] = {"1111","1111","1111","0000"};
    String* OUTPUT_PATTERNS_gets;
    bool OUTPUT_match[Total_gates]={};
    int k,l,m,n,temp,temp2,bit1,bit2;
    String Output_patterns="";

    // int GND_VCC_pins[2] ={28, 45};
    //---- Setting the Pin mode ---------------------------------------
    for( int i = 0; i< (No_inputs*Total_gates); i++ )
        pinMode(OUTPUT_pins[i], OUTPUT);

    for(int i = 0; i< No_outputs ; i++)
        pinMode(INPUT_pins[i], INPUT);
    
    //----(WARNING !!! DO NOT CHANGE ) Seting GND VCC ---------------
    pinMode(28, OUTPUT);// ------ GND
    digitalWrite(28,0);
    pinMode(45, OUTPUT);// ------ VCC
    digitalWrite(45,1);

   // ----- Seting the input value on the OUTPUT_pins 

/*
   //---- ALL gates are  00 ------------------------
    for(int i = 0 ; i < (No_inputs*Total_gates) ; i++)
        digitalWrite(OUTPUT_pins[i],0);
        
    for(int j =0 ; j < No_outputs; j++)                               // READING the value 
        Output_patterns +=  String( digitalRead(INPUT_pins[j]));
    
    //OUTPUT_PATTERNS_gets[0] = Output_patterns.toInt();        // convert the output pattern and add to the array 
    OUTPUT_PATTERNS_gets[0] = Output_patterns;
    Output_patterns = "";
    // ---- ALL gates are 01---------------------
    k=0;
    while (k < (No_inputs*Total_gates))
    {   l=k+1;
        digitalWrite(OUTPUT_pins[k],0);
        digitalWrite(OUTPUT_pins[l],1);
        k += 2;
    }

    for(int j =0 ; j < No_outputs; j++)                               // READING the value 
        Output_patterns +=  String( digitalRead(INPUT_pins[j]));
        // Output_patterns +=   digitalRead(INPUT_pins[j]);

    //OUTPUT_PATTERNS_gets[1] = Output_patterns.toInt();        // convert the output pattern and add to the array 
    OUTPUT_PATTERNS_gets[1] = Output_patterns;
    Output_patterns="";
    // ---- ALL gates are 10 ---------------------
    k=0;
    while (k<(No_inputs*Total_gates))
    {   l=k+1;
        digitalWrite(OUTPUT_pins[k],1);
        digitalWrite(OUTPUT_pins[l],0);
        k += 2;
    }

    for(int j =0 ; j < No_outputs; j++)                                // READING the value 
        Output_patterns +=  String( digitalRead(INPUT_pins[j]));
        // Output_patterns +=   digitalRead(INPUT_pins[j]);
    
   // OUTPUT_PATTERNS_gets[2] = Output_patterns.toInt();         // convert the output pattern and add to the array 
    OUTPUT_PATTERNS_gets[2] = Output_patterns;
    Output_patterns = "";

    //---- ALL gates are  11 ------------------------
    for(int i = 0 ; i <= 7; i++)
        digitalWrite(OUTPUT_pins[i],1);
        
    for(int j =0 ; j <= 3; j++)                                // READING the value 
        Output_patterns +=  String( digitalRead(INPUT_pins[j]));
        //Output_patterns +=   digitalRead(INPUT_pins[j]);
    
    //OUTPUT_PATTERNS_gets[3] = Output_patterns.toInt();        // convert the output pattern and add to the array 
    OUTPUT_PATTERNS_gets[3] = Output_patterns;
    Output_patterns = "";
*/

    OUTPUT_PATTERNS_gets = Bit_2_input(OUTPUT_pins, INPUT_pins,No_inputs, No_outputs, Total_gates, Bit_combination, INPUT_PATTERNS_TO_OUTPUT_pins);
    String ss1="Actual Output   : ",ss2="Output we gets : ";
    Serial.println("Outputs we gets ");
    for(int i = 0 ;i<= 3 ;i++){
        Serial.println(ss1 + OUTPUT_PATTERNS_FROM_INPUT_pins[i]);
        Serial.println(ss2 + OUTPUT_PATTERNS_gets[i]);
    }
    
    IC_Output_Matching(OUTPUT_PATTERNS_FROM_INPUT_pins,Output_string_length,Total_gates,Bit_combination, OUTPUT_PATTERNS_gets);

    // for(m=0 ; m<Total_gates ; m++){
    //     if( OUTPUT_match[m] == false){
    //         default_TESTER(OUTPUT_match,4);
    //     }
    // }
}

//===== 7401 ==========================

void TEST_7401(){
    // 14  2 4 7401  14  7 2,3,5,6,8,9,11,12 1,4,10,13 2-14-7-2,3,5,6,8,9,11,12-1,4,10,13  00,1111-01,1111-10,1111-11,0000 Quad 2-input NAND gate (O.C.)   
    
    Serial.println("Testing 7401 .....");
    int No_inputs=2, No_outputs=4, Total_gates=4, Output_string_length=4,Bit_combination=4;
    int OUTPUT_pins[8] = {23, 24, 26, 27, 39, 40, 42, 43};   // Output Pin array 
    int INPUT_pins[4] = {22, 25, 41, 44};                    // Input Pin array
    int INPUT_PATTERNS_TO_OUTPUT_pins[4] = {00,01,10,11};
    String OUTPUT_PATTERNS_FROM_INPUT_pins[4] = {"1111","1111","1111","0000"};
    String OUTPUT_PATTERNS_gets[4]={};
    bool OUTPUT_match[4]={};
    int k,l,m,n,temp,temp2,bit1,bit2;
    String Output_patterns="";
    // int GND_VCC_pins[2] ={28, 45};
    //---- Setting the Pin mode ---------------------------------------
    for( int i = 0; i<= 7; i++ )
        pinMode(OUTPUT_pins[i], OUTPUT);

    for(int i = 0; i<= 3 ; i++)
        pinMode(INPUT_pins[i], INPUT);
    
    //----(WARNING !!! DO NOT CHANGE ) Seting GND VCC ---------------
    pinMode(28, OUTPUT);// ------ GND
    digitalWrite(28,0);
    pinMode(45, OUTPUT);// ------ VCC
    digitalWrite(45,1);

   // ----- Seting the input value on the OUTPUT_pins 
   //---- ALL gates are  00 ------------------------
    for(int i = 0 ; i <= 7; i++)
        digitalWrite(OUTPUT_pins[i],0);
        
    for(int j =0 ; j <= 3; j++)                               // READING the value 
        Output_patterns +=  String( digitalRead(INPUT_pins[j]));
    
    //OUTPUT_PATTERNS_gets[0] = Output_patterns.toInt();        // convert the output pattern and add to the array 
    OUTPUT_PATTERNS_gets[0] = Output_patterns;
    Output_patterns = "";
    // ---- ALL gates are 01---------------------
    k=0;
    while (k<=7)
    {   l=k+1;
        digitalWrite(OUTPUT_pins[k],0);
        digitalWrite(OUTPUT_pins[l],1);
        k += 2;
    }

    for(int j =0 ; j <= 3; j++)                               // READING the value 
        Output_patterns +=  String( digitalRead(INPUT_pins[j]));
        // Output_patterns +=   digitalRead(INPUT_pins[j]);

    //OUTPUT_PATTERNS_gets[1] = Output_patterns.toInt();        // convert the output pattern and add to the array 
    OUTPUT_PATTERNS_gets[1] = Output_patterns;
    Output_patterns="";
    // ---- ALL gates are 10 ---------------------
    k=0;
    while (k<=7)
    {   l=k+1;
        digitalWrite(OUTPUT_pins[k],1);
        digitalWrite(OUTPUT_pins[l],0);
        k += 2;
    }

    for(int j =0 ; j <= 3; j++)                                // READING the value 
        Output_patterns +=  String( digitalRead(INPUT_pins[j]));
        // Output_patterns +=   digitalRead(INPUT_pins[j]);
    
   // OUTPUT_PATTERNS_gets[2] = Output_patterns.toInt();         // convert the output pattern and add to the array 
    OUTPUT_PATTERNS_gets[2] = Output_patterns;
    Output_patterns = "";

    //---- ALL gates are  11 ------------------------
    for(int i = 0 ; i <= 7; i++)
        digitalWrite(OUTPUT_pins[i],1);
        
    for(int j =0 ; j <= 3; j++)                                // READING the value 
        Output_patterns +=  String( digitalRead(INPUT_pins[j]));
        //Output_patterns +=   digitalRead(INPUT_pins[j]);
    
    //OUTPUT_PATTERNS_gets[3] = Output_patterns.toInt();        // convert the output pattern and add to the array 
    OUTPUT_PATTERNS_gets[3] = Output_patterns;
    Output_patterns = "";

    String ss1="Actual Output   : ",ss2="Output we gets : ";
    Serial.println("Outputs we gets ");
    for(int i = 0 ;i<= 3 ;i++){
        Serial.println(ss1 + OUTPUT_PATTERNS_FROM_INPUT_pins[i]);
        Serial.println(ss2 + OUTPUT_PATTERNS_gets[i]);
    }
    
    IC_Output_Matching(OUTPUT_PATTERNS_FROM_INPUT_pins,Output_string_length,Total_gates,Bit_combination, OUTPUT_PATTERNS_gets);

}

//===== 7402 ==========================
void TEST_7402(){
    // 14 2 4 7402  14  7 2,3,5,6,8,9,11,12 1,4,10,13 2-14-7-2,3,5,6,8,9,11,12-1,4,10,13  00,1111-01,0000-10,0000-11,0000 Quad 2-input NOR gate   
    
    Serial.println("Testing 7402 .....");
    int No_inputs=2, No_outputs=4, Total_gates=4,Output_string_length=4,Bit_combination=4;
    int OUTPUT_pins[8] = {23, 24, 26, 27, 39, 40, 42, 43};   // Output Pin array 
    int INPUT_pins[4] = {22, 25, 41, 44};                    // Input Pin array
    int INPUT_PATTERNS_TO_OUTPUT_pins[4] = {00,01,10,11};
    String OUTPUT_PATTERNS_FROM_INPUT_pins[4] = {"1111","0000","0000","0000"};
    String* OUTPUT_PATTERNS_gets;
    bool OUTPUT_match[4]={};
    int k,l,m,n,temp,temp2,bit1,bit2;
    String Output_patterns="";
    // int GND_VCC_pins[2] ={28, 45};
    //---- Setting the Pin mode ---------------------------------------
    for( int i = 0; i<= 7; i++ )
        pinMode(OUTPUT_pins[i], OUTPUT);

    for(int i = 0; i<= 3 ; i++)
        pinMode(INPUT_pins[i], INPUT);
    
    //----(WARNING !!! DO NOT CHANGE ) Seting GND VCC ---------------
    pinMode(28, OUTPUT);// ------ GND
    digitalWrite(28,0);
    pinMode(45, OUTPUT);// ------ VCC
    digitalWrite(45,1);

/*   // ----- Seting the input value on the OUTPUT_pins 
   //---- ALL gates are  00 ------------------------
    for(int i = 0 ; i <= 7; i++)
        digitalWrite(OUTPUT_pins[i],0);
        
    for(int j =0 ; j <= 3; j++)                               // READING the value 
        Output_patterns +=  String( digitalRead(INPUT_pins[j]));
    
    //OUTPUT_PATTERNS_gets[0] = Output_patterns.toInt();        // convert the output pattern and add to the array 
    OUTPUT_PATTERNS_gets[0] = Output_patterns;
    Output_patterns = "";
    // ---- ALL gates are 01---------------------
    k=0;
    while (k<=7)
    {   l=k+1;
        digitalWrite(OUTPUT_pins[k],0);
        digitalWrite(OUTPUT_pins[l],1);
        k += 2;
    }

    for(int j =0 ; j <= 3; j++)                               // READING the value 
        Output_patterns +=  String( digitalRead(INPUT_pins[j]));
        // Output_patterns +=   digitalRead(INPUT_pins[j]);

    //OUTPUT_PATTERNS_gets[1] = Output_patterns.toInt();        // convert the output pattern and add to the array 
    OUTPUT_PATTERNS_gets[1] = Output_patterns;
    Output_patterns="";
    // ---- ALL gates are 10 ---------------------
    k=0;
    while (k<=7)
    {   l=k+1;
        digitalWrite(OUTPUT_pins[k],1);
        digitalWrite(OUTPUT_pins[l],0);
        k += 2;
    }

    for(int j =0 ; j <= 3; j++)                                // READING the value 
        Output_patterns +=  String( digitalRead(INPUT_pins[j]));
        // Output_patterns +=   digitalRead(INPUT_pins[j]);
    
   // OUTPUT_PATTERNS_gets[2] = Output_patterns.toInt();         // convert the output pattern and add to the array 
    OUTPUT_PATTERNS_gets[2] = Output_patterns;
    Output_patterns = "";

    //---- ALL gates are  11 ------------------------
    for(int i = 0 ; i <= 7; i++)
        digitalWrite(OUTPUT_pins[i],1);
        
    for(int j =0 ; j <= 3; j++)                                // READING the value 
        Output_patterns +=  String( digitalRead(INPUT_pins[j]));
        //Output_patterns +=   digitalRead(INPUT_pins[j]);
    
    //OUTPUT_PATTERNS_gets[3] = Output_patterns.toInt();        // convert the output pattern and add to the array 
    OUTPUT_PATTERNS_gets[3] = Output_patterns;
    Output_patterns = "";
*/
    OUTPUT_PATTERNS_gets = Bit_2_input(OUTPUT_pins, INPUT_pins,No_inputs, No_outputs, Total_gates, Bit_combination, INPUT_PATTERNS_TO_OUTPUT_pins);
    
    String ss1="Actual Output   : ",ss2="Output we gets : ";
    Serial.println("Outputs we gets ");
    for(int i = 0 ;i<= 3 ;i++){
        Serial.println(ss1 + OUTPUT_PATTERNS_FROM_INPUT_pins[i]);
        Serial.println(ss2 + OUTPUT_PATTERNS_gets[i]);
    }

    IC_Output_Matching(OUTPUT_PATTERNS_FROM_INPUT_pins,Output_string_length,Total_gates,Bit_combination, OUTPUT_PATTERNS_gets);

}

//====== 7404 =========================
void TEST_7404(){
    // 14 1 6 7404  14  7 1,3,5,9,11,13 2,4,6,8,10,12 1-14-7-1,3,5,9,11,13-2,4,6,8,10,12  1,000000-0,111111 Hex inverter  01;10 

    Serial.println("Testing 7404 .....");
    int No_inputs=1, No_outputs=1, Total_gates=6,Output_string_length=6,Bit_combination=2;
    int OUTPUT_pins[6] = {22, 24, 26, 40, 41, 44};   // Output Pin array 
    int INPUT_pins[6] = {23, 25, 27, 39, 42, 43};                    // Input Pin array
    int INPUT_PATTERNS_TO_OUTPUT_pins[2] = {1,0};
    String OUTPUT_PATTERNS_FROM_INPUT_pins[2] = {"000000","111111"};
    String OUTPUT_PATTERNS_gets[2]={};
    bool OUTPUT_match[6]={};
    int k,l,m,n,temp,temp2,bit1,bit2;
    String Output_patterns="";
    // int GND_VCC_pins[2] ={28, 45};
    //---- Setting the Pin mode ---------------------------------------
    for( int i = 0; i<= 5; i++ )
        pinMode(OUTPUT_pins[i], OUTPUT);

    for(int i = 0; i<= 5 ; i++)
        pinMode(INPUT_pins[i], INPUT);
    
    //----(WARNING !!! DO NOT CHANGE ) Seting GND VCC ---------------
    pinMode(28, OUTPUT);// ------ GND
    digitalWrite(28,0);
    pinMode(45, OUTPUT);// ------ VCC
    digitalWrite(45,1);

   // ----- Seting the input value on the OUTPUT_pins 
   //---- ALL gates are  1 ------------------------
    for(int i = 0 ; i <= 5; i++)
        digitalWrite(OUTPUT_pins[i],1);
        
    for(int j =0 ; j <= 5; j++)                                // READING the value 
        Output_patterns +=  String( digitalRead(INPUT_pins[j]));

    OUTPUT_PATTERNS_gets[0] = Output_patterns;
    Output_patterns = "";
    
    //---- ALL gates are  0 ------------------------
    for(int i = 0 ; i <= 5; i++)
        digitalWrite(OUTPUT_pins[i],0);
        
    for(int j =0 ; j <= 5; j++)                                // READING the value 
        Output_patterns +=  String( digitalRead(INPUT_pins[j]));

    OUTPUT_PATTERNS_gets[1] = Output_patterns;
    Output_patterns = "";

    String ss1="Actual Output   : ",ss2="Output we gets : ";
    Serial.println("Outputs we gets ");
    for(int i = 0 ;i<= 3 ;i++){
        Serial.println(ss1 + OUTPUT_PATTERNS_FROM_INPUT_pins[i]);
        Serial.println(ss2 + OUTPUT_PATTERNS_gets[i]);
    }
    
    IC_Output_Matching(OUTPUT_PATTERNS_FROM_INPUT_pins,Output_string_length,Total_gates,Bit_combination, OUTPUT_PATTERNS_gets);
}

//====== 7405 =========================
void TEST_7405(){
    // 14 1 6 7404  14  7 1,3,5,9,11,13 2,4,6,8,10,12 1-14-7-1,3,5,9,11,13-2,4,6,8,10,12  1,000000-0,111111 Hex inverter  01;10 

    Serial.println("Testing 7404 .....");
    int No_inputs=1, No_outputs=1, Total_gates=6,Output_string_length=6,Bit_combination=2;
    int OUTPUT_pins[6] = {22, 24, 26, 40, 41, 44};   // Output Pin array 
    int INPUT_pins[6] = {23, 25, 27, 39, 42, 43};                    // Input Pin array
    int INPUT_PATTERNS_TO_OUTPUT_pins[2] = {1,0};
    String OUTPUT_PATTERNS_FROM_INPUT_pins[2] = {"000000","111111"};
    String OUTPUT_PATTERNS_gets[2]={};
    bool OUTPUT_match[6]={};
    int k,l,m,n,temp,temp2,bit1,bit2;
    String Output_patterns="";
    // int GND_VCC_pins[2] ={28, 45};
    //---- Setting the Pin mode ---------------------------------------
    for( int i = 0; i<= 5; i++ )
        pinMode(OUTPUT_pins[i], OUTPUT);

    for(int i = 0; i<= 5 ; i++)
        pinMode(INPUT_pins[i], INPUT);
    
    //----(WARNING !!! DO NOT CHANGE ) Seting GND VCC ---------------
    pinMode(28, OUTPUT);// ------ GND
    digitalWrite(28,0);
    pinMode(45, OUTPUT);// ------ VCC
    digitalWrite(45,1);

   // ----- Seting the input value on the OUTPUT_pins 
   //---- ALL gates are  1 ------------------------
    for(int i = 0 ; i <= 5; i++)
        digitalWrite(OUTPUT_pins[i],1);
        
    for(int j =0 ; j <= 5; j++)                                // READING the value 
        Output_patterns +=  String( digitalRead(INPUT_pins[j]));

    OUTPUT_PATTERNS_gets[0] = Output_patterns;
    Output_patterns = "";
    
    //---- ALL gates are  0 ------------------------
    for(int i = 0 ; i <= 5; i++)
        digitalWrite(OUTPUT_pins[i],0);
        
    for(int j =0 ; j <= 5; j++)                                // READING the value 
        Output_patterns +=  String( digitalRead(INPUT_pins[j]));

    OUTPUT_PATTERNS_gets[1] = Output_patterns;
    Output_patterns = "";

    String ss1="Actual Output   : ",ss2="Output we gets : ";
    Serial.println("Outputs we gets ");
    for(int i = 0 ;i<= 3 ;i++){
        Serial.println(ss1 + OUTPUT_PATTERNS_FROM_INPUT_pins[i]);
        Serial.println(ss2 + OUTPUT_PATTERNS_gets[i]);
    }
    
    IC_Output_Matching(OUTPUT_PATTERNS_FROM_INPUT_pins,Output_string_length,Total_gates,Bit_combination, OUTPUT_PATTERNS_gets);
}

//====== 7406 =========================
void TEST_7406(){
    // 14 1 6 7404  14  7 1,3,5,9,11,13 2,4,6,8,10,12 1-14-7-1,3,5,9,11,13-2,4,6,8,10,12  1,000000-0,111111 Hex inverter  01;10 

    Serial.println("Testing 7404 .....");
    int No_inputs=1, No_outputs=1, Total_gates=6,Output_string_length=6,Bit_combination=2;
    int OUTPUT_pins[6] = {22, 24, 26, 40, 41, 44};   // Output Pin array 
    int INPUT_pins[6] = {23, 25, 27, 39, 42, 43};                    // Input Pin array
    int INPUT_PATTERNS_TO_OUTPUT_pins[2] = {1,0};
    String OUTPUT_PATTERNS_FROM_INPUT_pins[2] = {"000000","111111"};
    String OUTPUT_PATTERNS_gets[2]={};
    bool OUTPUT_match[6]={};
    int k,l,m,n,temp,temp2,bit1,bit2;
    String Output_patterns="";
    // int GND_VCC_pins[2] ={28, 45};
    //---- Setting the Pin mode ---------------------------------------
    for( int i = 0; i<= 5; i++ )
        pinMode(OUTPUT_pins[i], OUTPUT);

    for(int i = 0; i<= 5 ; i++)
        pinMode(INPUT_pins[i], INPUT);
    
    //----(WARNING !!! DO NOT CHANGE ) Seting GND VCC ---------------
    pinMode(28, OUTPUT);// ------ GND
    digitalWrite(28,0);
    pinMode(45, OUTPUT);// ------ VCC
    digitalWrite(45,1);

   // ----- Seting the input value on the OUTPUT_pins 
   //---- ALL gates are  1 ------------------------
    for(int i = 0 ; i <= 5; i++)
        digitalWrite(OUTPUT_pins[i],1);
        
    for(int j =0 ; j <= 5; j++)                                // READING the value 
        Output_patterns +=  String( digitalRead(INPUT_pins[j]));

    OUTPUT_PATTERNS_gets[0] = Output_patterns;
    Output_patterns = "";
    
    //---- ALL gates are  0 ------------------------
    for(int i = 0 ; i <= 5; i++)
        digitalWrite(OUTPUT_pins[i],0);
        
    for(int j =0 ; j <= 5; j++)                                // READING the value 
        Output_patterns +=  String( digitalRead(INPUT_pins[j]));

    OUTPUT_PATTERNS_gets[1] = Output_patterns;
    Output_patterns = "";

    String ss1="Actual Output   : ",ss2="Output we gets : ";
    Serial.println("Outputs we gets ");
    for(int i = 0 ;i<= 3 ;i++){
        Serial.println(ss1 + OUTPUT_PATTERNS_FROM_INPUT_pins[i]);
        Serial.println(ss2 + OUTPUT_PATTERNS_gets[i]);
    }
    
    IC_Output_Matching(OUTPUT_PATTERNS_FROM_INPUT_pins,Output_string_length,Total_gates,Bit_combination, OUTPUT_PATTERNS_gets);
}

//====== 7407 =========================
void TEST_7407(){
    // 14 1 6 7404  14  7 1,3,5,9,11,13 2,4,6,8,10,12 1-14-7-1,3,5,9,11,13-2,4,6,8,10,12  1,000000-0,111111 Hex inverter  01;10 

    Serial.println("Testing 7404 .....");
    int No_inputs=1, No_outputs=1, Total_gates=6,Output_string_length=6,Bit_combination=2;
    int OUTPUT_pins[6] = {22, 24, 26, 40, 41, 44};   // Output Pin array 
    int INPUT_pins[6] = {23, 25, 27, 39, 42, 43};                    // Input Pin array
    int INPUT_PATTERNS_TO_OUTPUT_pins[2] = {1,0};
    String OUTPUT_PATTERNS_FROM_INPUT_pins[2] = {"000000","111111"};
    String OUTPUT_PATTERNS_gets[2]={};
    bool OUTPUT_match[6]={};
    int k,l,m,n,temp,temp2,bit1,bit2;
    String Output_patterns="";
    // int GND_VCC_pins[2] ={28, 45};
    //---- Setting the Pin mode ---------------------------------------
    for( int i = 0; i<= 5; i++ )
        pinMode(OUTPUT_pins[i], OUTPUT);

    for(int i = 0; i<= 5 ; i++)
        pinMode(INPUT_pins[i], INPUT);
    
    //----(WARNING !!! DO NOT CHANGE ) Seting GND VCC ---------------
    pinMode(28, OUTPUT);// ------ GND
    digitalWrite(28,0);
    pinMode(45, OUTPUT);// ------ VCC
    digitalWrite(45,1);

   // ----- Seting the input value on the OUTPUT_pins 
   //---- ALL gates are  1 ------------------------
    for(int i = 0 ; i <= 5; i++)
        digitalWrite(OUTPUT_pins[i],1);
        
    for(int j =0 ; j <= 5; j++)                                // READING the value 
        Output_patterns +=  String( digitalRead(INPUT_pins[j]));

    OUTPUT_PATTERNS_gets[0] = Output_patterns;
    Output_patterns = "";
    
    //---- ALL gates are  0 ------------------------
    for(int i = 0 ; i <= 5; i++)
        digitalWrite(OUTPUT_pins[i],0);
        
    for(int j =0 ; j <= 5; j++)                                // READING the value 
        Output_patterns +=  String( digitalRead(INPUT_pins[j]));

    OUTPUT_PATTERNS_gets[1] = Output_patterns;
    Output_patterns = "";

    String ss1="Actual Output   : ",ss2="Output we gets : ";
    Serial.println("Outputs we gets ");
    for(int i = 0 ;i<= 3 ;i++){
        Serial.println(ss1 + OUTPUT_PATTERNS_FROM_INPUT_pins[i]);
        Serial.println(ss2 + OUTPUT_PATTERNS_gets[i]);
    }
    
    IC_Output_Matching(OUTPUT_PATTERNS_FROM_INPUT_pins,Output_string_length,Total_gates,Bit_combination, OUTPUT_PATTERNS_gets);
}

//====== 7408 =========================
void TEST_7408(){
    // 14 2 4 7408  14  7 1,2,4,5,9,10,12,13  3,6,8,11  2-14-7-1,2,4,5,9,10,12,13-3,6,8,11  00,0000-01,0000-10,0000-11,1111 Quad 2-input AND gate     

    Serial.println("Testing 7408 .....");
    int No_inputs=2, No_outputs=4, Total_gates=4,Output_string_length=4,Bit_combination=4;
    int OUTPUT_pins[8] = {22, 23, 25, 26, 40, 41, 43, 44};   // Output Pin array 
    int INPUT_pins[4] = {24, 27, 39, 42};                    // Input Pin array
    int INPUT_PATTERNS_TO_OUTPUT_pins[4] = {00,01,10,11};
    String OUTPUT_PATTERNS_FROM_INPUT_pins[4] = {"0000","0000","0000","1111"};
    String OUTPUT_PATTERNS_gets[4]={};
    String OUTPUT_bits[4]={};
    String OUTPUT_bits2[4]={};
    bool OUTPUT_match[4]={};
    int k,l,m,n,temp,temp2,bit1,bit2;
    String Output_patterns="";
    // int GND_VCC_pins[2] ={28, 45};
    //---- Setting the Pin mode ---------------------------------------
    for( int i = 0; i<= 7; i++ )
        pinMode(OUTPUT_pins[i], OUTPUT);

    for(int i = 0; i<= 3 ; i++)
        pinMode(INPUT_pins[i], INPUT);
    
    //----(WARNING !!! DO NOT CHANGE ) Seting GND VCC ---------------
    pinMode(28, OUTPUT);// ------ GND
    digitalWrite(28,0);
    pinMode(45, OUTPUT);// ------ VCC
    digitalWrite(45,1);

   // ----- Seting the input value on the OUTPUT_pins 
   //---- ALL gates are  00 ------------------------
    for(int i = 0 ; i <= 7; i++)
        digitalWrite(OUTPUT_pins[i],0);
        
    for(int j =0 ; j <= 3; j++)                               // READING the value 
        Output_patterns +=  String( digitalRead(INPUT_pins[j]));
    
    //OUTPUT_PATTERNS_gets[0] = Output_patterns.toInt();        // convert the output pattern and add to the array 
    OUTPUT_PATTERNS_gets[0] = Output_patterns;
    Output_patterns = "";
    // ---- ALL gates are 01---------------------
    k=0;
    while (k<=7)
    {   l=k+1;
        digitalWrite(OUTPUT_pins[k],0);
        digitalWrite(OUTPUT_pins[l],1);
        k += 2;
    }

    for(int j =0 ; j <= 3; j++)                               // READING the value 
        Output_patterns +=  String( digitalRead(INPUT_pins[j]));
        // Output_patterns +=   digitalRead(INPUT_pins[j]);

    //OUTPUT_PATTERNS_gets[1] = Output_patterns.toInt();        // convert the output pattern and add to the array 
    OUTPUT_PATTERNS_gets[1] = Output_patterns;
    Output_patterns="";
    // ---- ALL gates are 10 ---------------------
    k=0;
    while (k<=7)
    {   l=k+1;
        digitalWrite(OUTPUT_pins[k],1);
        digitalWrite(OUTPUT_pins[l],0);
        k += 2;
    }

    for(int j =0 ; j <= 3; j++)                                // READING the value 
        Output_patterns +=  String( digitalRead(INPUT_pins[j]));
        // Output_patterns +=   digitalRead(INPUT_pins[j]);
    
   // OUTPUT_PATTERNS_gets[2] = Output_patterns.toInt();         // convert the output pattern and add to the array 
    OUTPUT_PATTERNS_gets[2] = Output_patterns;
    Output_patterns = "";

    //---- ALL gates are  11 ------------------------
    for(int i = 0 ; i <= 7; i++)
        digitalWrite(OUTPUT_pins[i],1);
        
    for(int j =0 ; j <= 3; j++)                                // READING the value 
        Output_patterns +=  String( digitalRead(INPUT_pins[j]));
        //Output_patterns +=   digitalRead(INPUT_pins[j]);
    
    //OUTPUT_PATTERNS_gets[3] = Output_patterns.toInt();        // convert the output pattern and add to the array 
    OUTPUT_PATTERNS_gets[3] = Output_patterns;
    Output_patterns = "";

    String ss1="Actual Output   : ",ss2="Output we gets : ";
    Serial.println("Outputs we gets ");
    for(int i = 0 ;i<= 3 ;i++){
        Serial.println(ss1 + OUTPUT_PATTERNS_FROM_INPUT_pins[i]);
        Serial.println(ss2 + OUTPUT_PATTERNS_gets[i]);
    }
    
    IC_Output_Matching(OUTPUT_PATTERNS_FROM_INPUT_pins,Output_string_length,Total_gates,Bit_combination, OUTPUT_PATTERNS_gets);
}

//====== 7409 =========================
void TEST_7409(){
    // 14 2 4 7409  14  7 1,2,4,5,9,10,12,13  3,6,8,11  2-14-7-1,2,4,5,9,10,12,13-3,6,8,11  00,0000-01,0000-10,0000-11,1111 Quad 2-input AND gate     

    Serial.println("Testing 7409 .....");
    int No_inputs=2, No_outputs=4, Total_gates=4,Output_string_length=4,Bit_combination=4;
    int OUTPUT_pins[8] = {22, 23, 25, 26, 40, 41, 43, 44};   // Output Pin array 
    int INPUT_pins[4] = {24, 27, 39, 42};                    // Input Pin array
    int INPUT_PATTERNS_TO_OUTPUT_pins[4] = {00,01,10,11};
    String OUTPUT_PATTERNS_FROM_INPUT_pins[4] = {"0000","0000","0000","1111"};
    String OUTPUT_PATTERNS_gets[4]={};
    String OUTPUT_bits[4]={};
    String OUTPUT_bits2[4]={};
    bool OUTPUT_match[4]={};
    int k,l,m,n,temp,temp2,bit1,bit2;
    String Output_patterns="";
    // int GND_VCC_pins[2] ={28, 45};
    //---- Setting the Pin mode ---------------------------------------
    for( int i = 0; i<= 7; i++ )
        pinMode(OUTPUT_pins[i], OUTPUT);

    for(int i = 0; i<= 3 ; i++)
        pinMode(INPUT_pins[i], INPUT);
    
    //----(WARNING !!! DO NOT CHANGE ) Seting GND VCC ---------------
    pinMode(28, OUTPUT);// ------ GND
    digitalWrite(28,0);
    pinMode(45, OUTPUT);// ------ VCC
    digitalWrite(45,1);

   // ----- Seting the input value on the OUTPUT_pins 
   //---- ALL gates are  00 ------------------------
    for(int i = 0 ; i <= 7; i++)
        digitalWrite(OUTPUT_pins[i],0);
        
    for(int j =0 ; j <= 3; j++)                               // READING the value 
        Output_patterns +=  String( digitalRead(INPUT_pins[j]));
    
    //OUTPUT_PATTERNS_gets[0] = Output_patterns.toInt();        // convert the output pattern and add to the array 
    OUTPUT_PATTERNS_gets[0] = Output_patterns;
    Output_patterns = "";
    // ---- ALL gates are 01---------------------
    k=0;
    while (k<=7)
    {   l=k+1;
        digitalWrite(OUTPUT_pins[k],0);
        digitalWrite(OUTPUT_pins[l],1);
        k += 2;
    }

    for(int j =0 ; j <= 3; j++)                               // READING the value 
        Output_patterns +=  String( digitalRead(INPUT_pins[j]));
        // Output_patterns +=   digitalRead(INPUT_pins[j]);

    //OUTPUT_PATTERNS_gets[1] = Output_patterns.toInt();        // convert the output pattern and add to the array 
    OUTPUT_PATTERNS_gets[1] = Output_patterns;
    Output_patterns="";
    // ---- ALL gates are 10 ---------------------
    k=0;
    while (k<=7)
    {   l=k+1;
        digitalWrite(OUTPUT_pins[k],1);
        digitalWrite(OUTPUT_pins[l],0);
        k += 2;
    }

    for(int j =0 ; j <= 3; j++)                                // READING the value 
        Output_patterns +=  String( digitalRead(INPUT_pins[j]));
        // Output_patterns +=   digitalRead(INPUT_pins[j]);
    
   // OUTPUT_PATTERNS_gets[2] = Output_patterns.toInt();         // convert the output pattern and add to the array 
    OUTPUT_PATTERNS_gets[2] = Output_patterns;
    Output_patterns = "";

    //---- ALL gates are  11 ------------------------
    for(int i = 0 ; i <= 7; i++)
        digitalWrite(OUTPUT_pins[i],1);
        
    for(int j =0 ; j <= 3; j++)                                // READING the value 
        Output_patterns +=  String( digitalRead(INPUT_pins[j]));
        //Output_patterns +=   digitalRead(INPUT_pins[j]);
    
    //OUTPUT_PATTERNS_gets[3] = Output_patterns.toInt();        // convert the output pattern and add to the array 
    OUTPUT_PATTERNS_gets[3] = Output_patterns;
    Output_patterns = "";

    String ss1="Actual Output   : ",ss2="Output we gets : ";
    Serial.println("Outputs we gets ");
    for(int i = 0 ;i<= 3 ;i++){
        Serial.println(ss1 + OUTPUT_PATTERNS_FROM_INPUT_pins[i]);
        Serial.println(ss2 + OUTPUT_PATTERNS_gets[i]);
    }
    
    IC_Output_Matching(OUTPUT_PATTERNS_FROM_INPUT_pins,Output_string_length,Total_gates,Bit_combination, OUTPUT_PATTERNS_gets);
}

//====== 7410 =========================
void TEST_7410(){
    // 14 3 3 7410  14  7 1,2,13,3,4,5,9,10,11  12,6,8  3-14-7-1,2,13,3,4,5,9,10,11-12,6,8  000,111-001,111-010,111-011,111-100,111-101,111-110,111-111,000 Triple 3-input NAND gate    

    Serial.println("Testing 7410 .....");
    int No_inputs=3, No_outputs=3, Total_gates=3, Output_string_length=3, Bit_combination=8;
    int OUTPUT_pins[9] = {22, 23, 44, 24, 25, 26, 40, 41, 42};   // Output Pin array 
    int INPUT_pins[3] = {43, 27, 39};                    // Input Pin array
    int INPUT_PATTERNS_TO_OUTPUT_pins[8] = {000,001,010,011,100,101,110,111};
    String OUTPUT_PATTERNS_FROM_INPUT_pins[8] = {"111","111","111","111","111","111","111","000"};
    String OUTPUT_PATTERNS_gets[8]={};
    bool OUTPUT_match[3]={};           //IT depens on total no of gates 
    int k,l,m,n,temp,temp2,bit1,bit2;
    String Output_patterns="";
    // int GND_VCC_pins[2] ={28, 45};
    //---- Setting the Pin mode ---------------------------------------
    for( int i = 0; i<= 7; i++ )
        pinMode(OUTPUT_pins[i], OUTPUT);

    for(int i = 0; i<= 3 ; i++)
        pinMode(INPUT_pins[i], INPUT);
    
    //----(WARNING !!! DO NOT CHANGE ) Seting GND VCC ---------------
    pinMode(28, OUTPUT);// ------ GND
    digitalWrite(28,0);
    pinMode(45, OUTPUT);// ------ VCC
    digitalWrite(45,1);

   // ----- Seting the input value on the OUTPUT_pins 
   //---- ALL gates are  000 ------------------------
    for(int i = 0 ; i <= 8; i++)
        digitalWrite(OUTPUT_pins[i],0);
        
    for(int j =0 ; j <= 2; j++)                               // READING the value 
        Output_patterns +=  String( digitalRead(INPUT_pins[j]));
    
    //OUTPUT_PATTERNS_gets[0] = Output_patterns.toInt();        // convert the output pattern and add to the array 
    OUTPUT_PATTERNS_gets[0] = Output_patterns;
    Output_patterns = "";
    // ---- ALL gates are 001---------------------
    k=0;
    while (k<=8)
    {   l=k+1;m=l+1;
        digitalWrite(OUTPUT_pins[k],0);
        digitalWrite(OUTPUT_pins[l],0);
        digitalWrite(OUTPUT_pins[m],1);
        k += 3;
    }

    for(int j =0 ; j <= 2; j++)                               // READING the value
        Output_patterns +=  String( digitalRead(INPUT_pins[j]));
        
    OUTPUT_PATTERNS_gets[1] = Output_patterns;
    Output_patterns="";
    // ---- ALL gates are 010---------------------
    k=0;
    while (k<=8)
    {   l=k+1;m=l+1;
        digitalWrite(OUTPUT_pins[k],0);
        digitalWrite(OUTPUT_pins[l],1);
        digitalWrite(OUTPUT_pins[m],0);
        k += 3;
    }

    for(int j =0 ; j <= 2; j++)                               // READING the value
        Output_patterns +=  String( digitalRead(INPUT_pins[j]));
        
    OUTPUT_PATTERNS_gets[2] = Output_patterns;
    Output_patterns="";
    // ---- ALL gates are 011---------------------
    k=0;
    while (k<=8)
    {   l=k+1;m=l+1;
        digitalWrite(OUTPUT_pins[k],0);
        digitalWrite(OUTPUT_pins[l],1);
        digitalWrite(OUTPUT_pins[m],1);
        k += 3;
    }

    for(int j =0 ; j <= 2; j++)                               // READING the value
        Output_patterns +=  String( digitalRead(INPUT_pins[j]));
        
    OUTPUT_PATTERNS_gets[3] = Output_patterns;
    Output_patterns="";
    // ---- ALL gates are 100---------------------
    k=0;
    while (k<=8)
    {   l=k+1;m=l+1;
        digitalWrite(OUTPUT_pins[k],1);
        digitalWrite(OUTPUT_pins[l],0);
        digitalWrite(OUTPUT_pins[m],0);
        k += 3;
    }

    for(int j =0 ; j <= 2; j++)                               // READING the value
        Output_patterns +=  String( digitalRead(INPUT_pins[j]));
        
    OUTPUT_PATTERNS_gets[4] = Output_patterns;
    Output_patterns="";
    // ---- ALL gates are 110---------------------
    k=0;
    while (k<=8)
    {   l=k+1;m=l+1;
        digitalWrite(OUTPUT_pins[k],1);
        digitalWrite(OUTPUT_pins[l],1);
        digitalWrite(OUTPUT_pins[m],0);
        k += 3;
    }

    for(int j =0 ; j <= 2; j++)                               // READING the value
        Output_patterns +=  String( digitalRead(INPUT_pins[j]));
        
    OUTPUT_PATTERNS_gets[5] = Output_patterns;
    Output_patterns="";
    // ---- ALL gates are 101---------------------
    k=0;
    while (k<=8)
    {   l=k+1;m=l+1;
        digitalWrite(OUTPUT_pins[k],1);
        digitalWrite(OUTPUT_pins[l],0);
        digitalWrite(OUTPUT_pins[m],1);
        k += 3;
    }

    for(int j =0 ; j <= 2; j++)                               // READING the value
        Output_patterns +=  String( digitalRead(INPUT_pins[j]));
        
    OUTPUT_PATTERNS_gets[6] = Output_patterns;
    Output_patterns="";
    // ---- ALL gates are 111---------------------
    k=0;
    while (k<=8)
    {   l=k+1;m=l+1;
        digitalWrite(OUTPUT_pins[k],1);
        digitalWrite(OUTPUT_pins[l],1);
        digitalWrite(OUTPUT_pins[m],1);
        k += 3;
    }

    for(int j =0 ; j <= 2; j++)                               // READING the value
        Output_patterns +=  String( digitalRead(INPUT_pins[j]));
        
    OUTPUT_PATTERNS_gets[7] = Output_patterns;
    Output_patterns="";

    String ss1="Actual Output  : ",ss2="Output we gets : ";
    Serial.println("Outputs we gets ");
    for(int i = 0 ;i<= 3 ;i++){
        Serial.println(ss1 + OUTPUT_PATTERNS_FROM_INPUT_pins[i]);
        Serial.println(ss2 + OUTPUT_PATTERNS_gets[i]);
    }
    
    IC_Output_Matching(OUTPUT_PATTERNS_FROM_INPUT_pins,Output_string_length,Total_gates,Bit_combination, OUTPUT_PATTERNS_gets);
    // // Check if the output properly match with actual outcome----------------------
    // String space= "        ";

    // for(int i = 0 ;i<= 7  ;i++){
    //     temp =  OUTPUT_PATTERNS_gets[i].toInt();
    //     temp2 = OUTPUT_PATTERNS_FROM_INPUT_pins[i].toInt();
    //     Serial.println(temp + space + temp2);
    //     for(m=0 ; m<Total_gates ; m++){
    //         bit1 = temp % 10;
    //         bit2 = temp2 % 10;
            
    //         temp = temp / 10;
    //         temp2 = temp2 / 10;
    //         if( bit1 == bit2 ){
    //             Serial.println(bit1 + space + bit2);
    //             Serial.println(" matched ");
    //             OUTPUT_match[i]=true;
    //         }
    //         else{
    //             Serial.println(bit1 + space + bit2); 
    //             Serial.println(" not matched ");
    //             OUTPUT_match[i]=false;
    //         }
    //     }
    // }
    // Serial.println("Outputs we gets ");
    // for(int i = 0 ;i<= 7 ;i++){
    //     Serial.println(OUTPUT_PATTERNS_gets[i]);
    // }
    // display(OUTPUT_match, 8);
}

//===== 7411 =================================

void TEST_7411(){
    // 14 3 3 7411  14  7 1,2,13,3,4,5,9,10,11  12,6,8  3-14-7-1,2,13,3,4,5,9,10,11-12,6,8  000,000-001,000-010,000-011,000-100,000-101,000-110,000-111,111 Triple 3-input AND gate   

    Serial.println("Testing 7411 .....");
    int No_inputs=3, No_outputs=3, Total_gates=3,Output_string_length=3, Bit_combination=8;
    int OUTPUT_pins[9] = {22, 23, 44, 24, 25, 26, 40, 41, 42};   // Output Pin array 
    int INPUT_pins[3] = {43, 27, 39};                    // Input Pin array
    int INPUT_PATTERNS_TO_OUTPUT_pins[8] = {000,001,010,011,100,101,110,111};
    String OUTPUT_PATTERNS_FROM_INPUT_pins[8] = {"000","000","000","000","000","000","000","111"};
    String OUTPUT_PATTERNS_gets[8]={};
    String OUTPUT_bits[3]={};
    String OUTPUT_bits2[3]={};
    bool OUTPUT_match[3]={};           //IT depens on total no of gates 
    int k,l,m,n,temp,temp2,bit1,bit2;
    String Output_patterns="";
    // int GND_VCC_pins[2] ={28, 45};
    //---- Setting the Pin mode ---------------------------------------
    for( int i = 0; i<= 7; i++ )
        pinMode(OUTPUT_pins[i], OUTPUT);

    for(int i = 0; i<= 3 ; i++)
        pinMode(INPUT_pins[i], INPUT);
    
    //----(WARNING !!! DO NOT CHANGE ) Seting GND VCC ---------------
    pinMode(28, OUTPUT);// ------ GND
    digitalWrite(28,0);
    pinMode(45, OUTPUT);// ------ VCC
    digitalWrite(45,1);

   // ----- Seting the input value on the OUTPUT_pins 
   //---- ALL gates are  000 ------------------------
    for(int i = 0 ; i <= 8; i++)
        digitalWrite(OUTPUT_pins[i],0);
        
    for(int j =0 ; j <= 2; j++)                               // READING the value 
        Output_patterns +=  String( digitalRead(INPUT_pins[j]));
    
    //OUTPUT_PATTERNS_gets[0] = Output_patterns.toInt();        // convert the output pattern and add to the array 
    OUTPUT_PATTERNS_gets[0] = Output_patterns;
    Output_patterns = "";
    // ---- ALL gates are 001---------------------
    k=0;
    while (k<=8)
    {   l=k+1;m=l+1;
        digitalWrite(OUTPUT_pins[k],0);
        digitalWrite(OUTPUT_pins[l],0);
        digitalWrite(OUTPUT_pins[m],1);
        k += 3;
    }

    for(int j =0 ; j <= 2; j++)                               // READING the value
        Output_patterns +=  String( digitalRead(INPUT_pins[j]));
        
    OUTPUT_PATTERNS_gets[1] = Output_patterns;
    Output_patterns="";
    // ---- ALL gates are 010---------------------
    k=0;
    while (k<=8)
    {   l=k+1;m=l+1;
        digitalWrite(OUTPUT_pins[k],0);
        digitalWrite(OUTPUT_pins[l],1);
        digitalWrite(OUTPUT_pins[m],0);
        k += 3;
    }

    for(int j =0 ; j <= 2; j++)                               // READING the value
        Output_patterns +=  String( digitalRead(INPUT_pins[j]));
        
    OUTPUT_PATTERNS_gets[2] = Output_patterns;
    Output_patterns="";
    // ---- ALL gates are 011---------------------
    k=0;
    while (k<=8)
    {   l=k+1;m=l+1;
        digitalWrite(OUTPUT_pins[k],0);
        digitalWrite(OUTPUT_pins[l],1);
        digitalWrite(OUTPUT_pins[m],1);
        k += 3;
    }

    for(int j =0 ; j <= 2; j++)                               // READING the value
        Output_patterns +=  String( digitalRead(INPUT_pins[j]));
        
    OUTPUT_PATTERNS_gets[3] = Output_patterns;
    Output_patterns="";
    // ---- ALL gates are 100---------------------
    k=0;
    while (k<=8)
    {   l=k+1;m=l+1;
        digitalWrite(OUTPUT_pins[k],1);
        digitalWrite(OUTPUT_pins[l],0);
        digitalWrite(OUTPUT_pins[m],0);
        k += 3;
    }

    for(int j =0 ; j <= 2; j++)                               // READING the value
        Output_patterns +=  String( digitalRead(INPUT_pins[j]));
        
    OUTPUT_PATTERNS_gets[4] = Output_patterns;
    Output_patterns="";
    // ---- ALL gates are 110---------------------
    k=0;
    while (k<=8)
    {   l=k+1;m=l+1;
        digitalWrite(OUTPUT_pins[k],1);
        digitalWrite(OUTPUT_pins[l],1);
        digitalWrite(OUTPUT_pins[m],0);
        k += 3;
    }

    for(int j =0 ; j <= 2; j++)                               // READING the value
        Output_patterns +=  String( digitalRead(INPUT_pins[j]));
        
    OUTPUT_PATTERNS_gets[5] = Output_patterns;
    Output_patterns="";
    // ---- ALL gates are 101---------------------
    k=0;
    while (k<=8)
    {   l=k+1;m=l+1;
        digitalWrite(OUTPUT_pins[k],1);
        digitalWrite(OUTPUT_pins[l],0);
        digitalWrite(OUTPUT_pins[m],1);
        k += 3;
    }

    for(int j =0 ; j <= 2; j++)                               // READING the value
        Output_patterns +=  String( digitalRead(INPUT_pins[j]));
        
    OUTPUT_PATTERNS_gets[6] = Output_patterns;
    Output_patterns="";
    // ---- ALL gates are 111---------------------
    k=0;
    while (k<=8)
    {   l=k+1;m=l+1;
        digitalWrite(OUTPUT_pins[k],1);
        digitalWrite(OUTPUT_pins[l],1);
        digitalWrite(OUTPUT_pins[m],1);
        k += 3;
    }

    for(int j =0 ; j <= 2; j++)                               // READING the value
        Output_patterns +=  String( digitalRead(INPUT_pins[j]));
        
    OUTPUT_PATTERNS_gets[7] = Output_patterns;
    Output_patterns="";

        String ss1="Actual Output   : ",ss2="Output we gets : ";
    Serial.println("Outputs we gets ");
    for(int i = 0 ;i<= 3 ;i++){
        Serial.println(ss1 + OUTPUT_PATTERNS_FROM_INPUT_pins[i]);
        Serial.println(ss2 + OUTPUT_PATTERNS_gets[i]);
    }
    
    IC_Output_Matching(OUTPUT_PATTERNS_FROM_INPUT_pins,Output_string_length,Total_gates,Bit_combination, OUTPUT_PATTERNS_gets);
    // // Check if the output properly match with actual outcome----------------------
    // String space= "          ";

    // for(int i = 0 ;i<= 7 ;i++){
    //     temp =  OUTPUT_PATTERNS_gets[i].toInt();
    //     temp2 = OUTPUT_PATTERNS_FROM_INPUT_pins[i].toInt();
    //     Serial.println(temp + space + temp2);
    //     for(m=0 ; m<Total_gates ; m++){
    //         bit1 = temp % 10;
    //         bit2 = temp2 % 10;
    //         temp = temp / 10;
    //         temp2 = temp2 / 10;
    //         if( bit1 == bit2 ){
    //             Serial.println(bit1 + space + bit2);
    //             Serial.println(" matched ");
    //             OUTPUT_match[i]=true;
    //         }
    //         else{
    //             Serial.println(bit1 + space + bit2); 
    //             Serial.println(" not matched ");
    //             OUTPUT_match[i]=false;
    //         }
    //     }
    // }
    // Serial.println("Outputs we gets ");
    // for(int i = 0 ;i<= 7 ;i++){
    //     Serial.println(OUTPUT_PATTERNS_gets[i]);
    // }
    // display(OUTPUT_match, 8);
}






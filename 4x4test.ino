/* 


SL---->FUNCTION NAME  -----------------------> LINE NUMBER 
_______________________________________________________________________________________
1     setup()                                    38
2     loop()                                     48
3     get_IC_PIN_details()                       80
4     get_IC_PART_details()                      117
5     IC_Tester_switch                           153

*/


#include<Keypad.h>
const byte ROWS = 4;
const byte COLS = 4;

char Keys[ROWS][COLS] = {
// 1    2   3   4     
  {'1','2','3','A'},   // A  5
  {'4','5','6','B'},   // B  
  {'7','8','9','C'},   // C 
  {'*','0','#','D'}    // D

};


// ---------- KEYPAD MAPPING --------------------------------------------------
byte rowPINS[ROWS]= {9, 8, 7, 6};
byte colPINS[COLS]= {5, 4, 3, 2};
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

//------- This Function set Pin modes ------------------------
void Set_PIN_modes(int OUTPUT_pins[], int INPUT_pins[], int GND,int VCC, int No_inputs, int No_outputs, int Total_gates  ){
    //---- Setting the Pin mode ---------------------------------------
    for( int i = 0; i<= (No_inputs*Total_gates); i++ )
        pinMode(OUTPUT_pins[i], OUTPUT);

    for(int i = 0; i<= No_outputs ; i++)
        pinMode(INPUT_pins[i], INPUT);
    
    //----(WARNING !!! DO NOT CHANGE ) Seting GND VCC ---------------
    pinMode(GND, OUTPUT);// ------ GND
    digitalWrite(GND,0);
    pinMode(VCC, OUTPUT);// ------ VCC
    digitalWrite(VCC,1);
}

//----- Switch case ------------------------------
void IC_Tester_switch(int IC_pin, int IC_part){
    
    Serial.println("Inside SWITCH ");
    if( IC_pin == 14 ){
        switch (IC_part){
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
        case 7413: TEST_7413();
            break;
        case 7414: TEST_7414();
            break;
        case 7416: TEST_7416();
            break;
        case 7417: TEST_7417();
            break;
        case 7420: TEST_7420();
            break;
        case 7421: TEST_7421();
            break;
        case 7425: TEST_7425();
            break;
        case 7427: TEST_7427();
            break;
        case 7428: TEST_7428();
            break;
        case 7430: TEST_7430();
            break;
        case 7432: TEST_7432();
            break;
        case 7437: TEST_7437();
            break;
        case 7438: TEST_7438();
            break;
        case 7440: TEST_7440();
            break;
        // case 7414: TEST_7414();
        //     break;
        // case 7416: TEST_7416();
        //     break;
        // case 7417: TEST_7417();
        //     break;
        // case 7413: TEST_7404();
        //     break;
        
        
        
        
        default:
            break;
        }
    }
    
}

//----- This function used to check if the output properly match with actual outcome----------------------
void  IC_Output_Matching(String Actual_Outputs[] ,int Actual_Output_string_length, int total_gates,int combination, String Outputs[] ){
    
    String space= "     ", space2= "    temp    ";
    int temp1,temp2,bit1,bit2;
    bool  OUTPUT_match[total_gates]={};
    for(int i = 0 ;i < combination ;i++){
        int len = Actual_Output_string_length -1 ;
            if(Outputs[i] == Actual_Outputs[i] ){
                Serial.println("Total Matched");
                for(int n =0 ; n<= len ;n++)
                    OUTPUT_match[n]=true;
            }
            else{
                temp1 = Outputs[i].toInt();                 // Outputs we get
                temp2 = Actual_Outputs[i].toInt();          // Actual Output
                Serial.println(temp1 + space2 + temp2);
                for(int m=0 ; m < Actual_Output_string_length ; m++){

                bit1 = temp1 % 10;
                bit2 = temp2 % 10;
                temp1 = temp1 / 10;
                temp2 = temp2 / 10;
                Serial.println(len);
                Serial.println(bit1 + space + bit2);
                Serial.println(temp1 + space + temp2);
                if( bit1 == bit2 ){              
                    if( OUTPUT_match[len] == false && i!=0){  
                        OUTPUT_match[len] = false;
                        Serial.println("matched + previous false  ");
                    }
                        
                    else {
                        OUTPUT_match[len] = true;
                        Serial.println("matched + true  ");
                    }
                    
                    len--;
                }
                else{
                    Serial.println("not matched + false ");
                    OUTPUT_match[len]=false;
                    len --;
                }
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

//----- SET Input for 2 bit ---------------------------
String Bit_2_input(int OUTPUT_pins[], int INPUT_pins[], int IN,int OUT,int TotG, int combination, int IN_pat[]){
    //IN=> No_inputs, OUT=>No_outputs, TotG=> Total_gates, combination=> Bit_combination , IN_pat=>Input_Pattern
    String OUTPUT_PATTERNS_gets[combination]={},Output_patterns="" , sk="OUTPUT----> ", sj="temp1----> ",sl="bit1----> ";
    int temp1 , bit1,k;
    for( int i=0;i< combination ;i++){
        temp1 = IN_pat[i];
        Serial.println(sj + temp1);
        for(int j=0;j< IN;j++){
            bit1 = temp1%10;
            Serial.println(sl + bit1);
            temp1 = temp1/10;
            Serial.println("j==0");
            if(j == 0){                // LSB
                Serial.println("j==0");
                for(int k=1; k <= (IN*OUT); k=k+2){
                    digitalWrite(OUTPUT_pins[k],bit1);
                    Serial.println(OUTPUT_pins[k]); 
                }
            }
            else if(j==1) {
                Serial.println("j==1");
                for(k=0; k < (IN*OUT);k+=2){
                    digitalWrite(OUTPUT_pins[k],bit1);
                    Serial.println(OUTPUT_pins[k]); 
                }
            }
        }
        for(int l=0 ; l < OUT; l++) {                              // READING the value 
            Output_patterns +=  String( digitalRead(INPUT_pins[l]));
        }
        OUTPUT_PATTERNS_gets[i] = Output_patterns;
        Serial.println(sk + Output_patterns);
        // Output_patterns = "";
        if(i == combination-1)
            Output_patterns+="";
        else Output_patterns+="-";
    }
    // return OUTPUT_PATTERNS_gets;
    Serial.println("IN BIT_2 INPUT");
    Serial.println( Output_patterns);
    return Output_patterns;
}

//----- SET Input for 3 bit ----------------------------
String Bit_3_input(int OUTPUT_pins[], int INPUT_pins[], int IN,int OUT,int TotG, int combination, String IN_pat[]){
    //IN=> No_inputs, OUT=>No_outputs, TotG=> Total_gates, combination=> Bit_combination , IN_pat=>Input_Pattern
    String OUTPUT_PATTERNS_gets[combination]={},Output_patterns="" , sk="OUTPUT----> ", sj="temp1----> ",sl="bit1----> ", r="pat----> " ,sp="  --->  ";
    int temp1 , bit1,k;
    for( int i=0;i< combination ;i++){
        temp1 = IN_pat[i].toInt();
        Serial.println(r + IN_pat[i]);
        Serial.println(sj + temp1);
        for(int j=0;j< IN;j++){
            bit1 = temp1%10;
            Serial.println(sl + bit1);
            temp1 = temp1/10;
            if(j == 0){
                Serial.println("j==0");
                for(int k=2; k <= (IN*OUT); k=k+3){
                    digitalWrite(OUTPUT_pins[k],bit1);
                    Serial.println(OUTPUT_pins[k]); 
                }
            }
            else if(j==1) {
                Serial.println("j==1");
                for(k=1; k < (IN*OUT);k=k+3){
                    digitalWrite(OUTPUT_pins[k],bit1);
                    Serial.println(OUTPUT_pins[k]); 
                }
            }
            else if(j==2) {
                Serial.println("j==2");
                for(k=0; k< (IN*OUT);k=k+3){
                    digitalWrite(OUTPUT_pins[k],bit1);
                    Serial.println(OUTPUT_pins[k]); 
                }
            }
        }
        for(int l=0 ; l < OUT; l++) {                              // READING the value 
            Output_patterns +=  String( digitalRead(INPUT_pins[l]));
            Serial.println(l + sp +  digitalRead(INPUT_pins[l]));
        }
        OUTPUT_PATTERNS_gets[i] = Output_patterns;
        Serial.println(sk + Output_patterns);
        // Output_patterns = "";
        if(i == combination-1)
            Output_patterns+="";
        else Output_patterns+="-";
    }
    // return OUTPUT_PATTERNS_gets;
    Serial.println("IN BIT_3_INPUT");
    Serial.println( Output_patterns);
    return Output_patterns;
}


//---- SET Input for 4 bit ----------------------------
String Bit_4_input(int OUTPUT_pins[], int INPUT_pins[], int IN,int OUT,int TotG, int combination, String IN_pat[]){
    //IN=> No_inputs, OUT=>No_outputs, TotG=> Total_gates, combination=> Bit_combination , IN_pat=>Input_Pattern
    String OUTPUT_PATTERNS_gets[combination]={},Output_patterns="" , sk="OUTPUT----> ", sj="temp1----> ",sl="bit1----> ", r="pat----> " ,sp="  --->  ";
    int temp1 , bit1,k;
    for( int i=0;i< combination ;i++){
        temp1 = IN_pat[i].toInt();
        Serial.println(r + IN_pat[i]);
        Serial.println(sj + temp1);
        for(int j=0;j< IN;j++){
            bit1 = temp1%10;
            Serial.println(sl + bit1);
            temp1 = temp1/10;
            if(j == 0){           // LSB
                Serial.println("j==0");
                for(int k=3; k <= (IN*OUT); k=k+4){
                    digitalWrite(OUTPUT_pins[k],bit1);
                    Serial.println(OUTPUT_pins[k]); 
                }
            }
            else if(j==1) {
                Serial.println("j==1");
                for(k=2; k < (IN*OUT);k=k+4){
                    digitalWrite(OUTPUT_pins[k],bit1);
                    Serial.println(OUTPUT_pins[k]); 
                }
            }
            else if(j==2) {
                Serial.println("j==2");
                for(k=1; k< (IN*OUT);k=k+4){
                    digitalWrite(OUTPUT_pins[k],bit1);
                    Serial.println(OUTPUT_pins[k]); 
                }
            }
            else if(j==3) {           //MSB
                Serial.println("j==2");
                for(k=0; k< (IN*OUT);k=k+4){
                    digitalWrite(OUTPUT_pins[k],bit1);
                    Serial.println(OUTPUT_pins[k]); 
                }
            }
        }
        for(int l=0 ; l < OUT; l++) {                              // READING the value 
            Output_patterns +=  String( digitalRead(INPUT_pins[l]));
            Serial.println(l + sp +  digitalRead(INPUT_pins[l]));
        }
        OUTPUT_PATTERNS_gets[i] = Output_patterns;
        Serial.println(sk + Output_patterns);
        // Output_patterns = "";
        if(i == combination-1)
            Output_patterns+="";
        else Output_patterns+="-";
    }
    // return OUTPUT_PATTERNS_gets;
    Serial.println("IN BIT_3_INPUT");
    Serial.println( Output_patterns);
    return Output_patterns;
}


//---- SET Input for 8 bit ----------------------------
String Bit_8_input(int OUTPUT_pins[], int INPUT_pins[], int IN,int OUT,int TotG, int combination, String IN_pat[]){
    //IN=> No_inputs, OUT=>No_outputs, TotG=> Total_gates, combination=> Bit_combination , IN_pat=>Input_Pattern
    String OUTPUT_PATTERNS_gets[combination]={},Output_patterns="" , sk="OUTPUT----> ", sj="temp1----> ",sl="bit1----> ", r="pat----> " ,sp="  --->  ";
    int temp1 , bit1,k;
    for( int i=0;i< combination ;i++){
        temp1 = IN_pat[i].toInt();
        Serial.println(r + IN_pat[i]);
        Serial.println(sj + temp1);
        for(int j=0;j< IN;j++){
            bit1 = temp1%10;
            Serial.println(sl + bit1);
            temp1 = temp1/10;
            if(j == 0){           // LSB
                Serial.println("j==0");
                for(int k=7; k <= (IN*OUT); k=k+8){
                    digitalWrite(OUTPUT_pins[k],bit1);
                    Serial.println(OUTPUT_pins[k]); 
                }
            }
            else if(j==1) {
                Serial.println("j==1");
                for(k=6; k < (IN*OUT);k=k+8){
                    digitalWrite(OUTPUT_pins[k],bit1);
                    Serial.println(OUTPUT_pins[k]); 
                }
            }
            else if(j==2) {
                Serial.println("j==2");
                for(k=5; k< (IN*OUT);k=k+8){
                    digitalWrite(OUTPUT_pins[k],bit1);
                    Serial.println(OUTPUT_pins[k]); 
                }
            }
            else if(j==3) {           
                Serial.println("j==3");
                for(k=4; k< (IN*OUT);k=k+8){
                    digitalWrite(OUTPUT_pins[k],bit1);
                    Serial.println(OUTPUT_pins[k]); 
                }
            }
            else if(j==4) {
                Serial.println("j==1");
                for(k=3; k < (IN*OUT);k=k+8){
                    digitalWrite(OUTPUT_pins[k],bit1);
                    Serial.println(OUTPUT_pins[k]); 
                }
            }
            else if(j==5) {
                Serial.println("j==2");
                for(k=2; k< (IN*OUT);k=k+8){
                    digitalWrite(OUTPUT_pins[k],bit1);
                    Serial.println(OUTPUT_pins[k]); 
                }
            }
            else if(j==6) {           
                Serial.println("j==3");
                for(k=1; k< (IN*OUT);k=k+8){
                    digitalWrite(OUTPUT_pins[k],bit1);
                    Serial.println(OUTPUT_pins[k]); 
                }
            }
            else if(j==7) {                   // MSB
                Serial.println("j==1");
                for(k=0; k < (IN*OUT);k=k+8){
                    digitalWrite(OUTPUT_pins[k],bit1);
                    Serial.println(OUTPUT_pins[k]); 
                }
            }
            
        }
        for(int l=0 ; l < OUT; l++) {                              // READING the value 
            Output_patterns +=  String( digitalRead(INPUT_pins[l]));
            Serial.println(l + sp +  digitalRead(INPUT_pins[l]));
        }
        OUTPUT_PATTERNS_gets[i] = Output_patterns;
        Serial.println(sk + Output_patterns);
        // Output_patterns = "";
        if(i == combination-1)
            Output_patterns+="";
        else Output_patterns+="-";
    }
    // return OUTPUT_PATTERNS_gets;
    Serial.println("IN BIT_3_INPUT");
    Serial.println( Output_patterns);
    return Output_patterns;
}



//------ This function split the string --------------------------
String String_Splitter(String data , char separetor ,int index){
    int found=0;
    int strIndex[] = {0,-1};
    int maxIndex = data.length() -1;
    for(int i = 0;i<=maxIndex && found <= index; i++ ){
        if( data.charAt(i) == separetor || i == maxIndex){
            found++ ;
            strIndex[0] = strIndex[1] +1;
            strIndex[1] = (i == maxIndex ) ? i+1 : i;
         }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]): "";
}

//------ INDIVIDUAL IC TESTING FUNCTION ------------------------------------
//==== 7400 ===========================
void TEST_7400(){
    // 14  2 4 7400  14  7 1,2,4,5,9,10,12,13  3,6,8,11  2-14-7-1,2,4,5,9,10,12,13-3,6,8,11  00,1111-01,1111-10,1111-11,0000 Quad 2-input NAND gate  00011011;1110 

    Serial.println("Testing 7400 .....");
    int GND=28, VCC=45, No_inputs=2, No_outputs=4, Total_gates=4,Output_string_length=4,Bit_combination=4;
    int OUTPUT_pins[(No_inputs*Total_gates)] = {22, 23, 25, 26, 40, 41, 43, 44};   // Output Pin array 
    int INPUT_pins[No_outputs] = {24, 27, 39, 42};                    // Input Pin array
    int INPUT_PATTERNS_TO_OUTPUT_pins[Bit_combination] = {00,01,10,11};
    String OUTPUT_PATTERNS_FROM_INPUT_pins[Bit_combination] = {"1111","1111","1111","0000"};
    String OUTPUT_PATTERNS_gets[Bit_combination]={}, out_pat="";
    bool OUTPUT_match[Total_gates]={};
    
    Set_PIN_modes(OUTPUT_pins,INPUT_pins,GND,VCC,No_inputs, No_outputs, Total_gates);


    out_pat = Bit_2_input(OUTPUT_pins, INPUT_pins,No_inputs, No_outputs, Total_gates, Bit_combination, INPUT_PATTERNS_TO_OUTPUT_pins);
    
    for(int i = 0 ;i< Total_gates ;i++){
       OUTPUT_PATTERNS_gets[i] = String_Splitter(out_pat,'-',i);
    }

    Serial.println("Outputs we gets ");
    for(int i = 0 ;i< Total_gates ;i++){
        Serial.println(OUTPUT_PATTERNS_gets[i]);
    }
    
    String ss1="Actual Output   : ",ss2="Output we gets : " ,ss3= "        ";
    Serial.println("Outputs we gets ");
    for(int i = 0 ;i< Total_gates ;i++)
        Serial.println(ss1 + OUTPUT_PATTERNS_FROM_INPUT_pins[i]+ ss3 + ss2 + OUTPUT_PATTERNS_gets[i]);
    
    IC_Output_Matching(OUTPUT_PATTERNS_FROM_INPUT_pins,Output_string_length,Total_gates,Bit_combination, OUTPUT_PATTERNS_gets);

}

//===== 7401 ==========================
void TEST_7401(){
    // 14  2 4 7401  14  7 2,3,5,6,8,9,11,12 1,4,10,13 2-14-7-2,3,5,6,8,9,11,12-1,4,10,13  00,1111-01,1111-10,1111-11,0000 Quad 2-input NAND gate (O.C.)   
    
    Serial.println("Testing 7401 .....");
    int GND=28, VCC=45, No_inputs=2, No_outputs=4, Total_gates=4, Output_string_length=4,Bit_combination=4;
    int OUTPUT_pins[(No_inputs*Total_gates)] = {23, 24, 26, 27, 39, 40, 42, 43};   // Output Pin array 
    int INPUT_pins[No_outputs] = {22, 25, 41, 44};                    // Input Pin array
    int INPUT_PATTERNS_TO_OUTPUT_pins[Bit_combination] = {00,01,10,11};
    String OUTPUT_PATTERNS_FROM_INPUT_pins[Bit_combination] = {"1111","1111","1111","0000"};
    String OUTPUT_PATTERNS_gets[Bit_combination]={}, out_pat="" ;
    bool OUTPUT_match[Total_gates]={};
 
    Set_PIN_modes(OUTPUT_pins,INPUT_pins,GND,VCC,No_inputs, No_outputs, Total_gates);

    out_pat = Bit_2_input(OUTPUT_pins, INPUT_pins,No_inputs, No_outputs, Total_gates, Bit_combination, INPUT_PATTERNS_TO_OUTPUT_pins);
    
    for(int i = 0 ;i< Total_gates ;i++){
       OUTPUT_PATTERNS_gets[i] = String_Splitter(out_pat,'-',i);
    }

    Serial.println("Outputs we gets ");
    for(int i = 0 ;i< Total_gates ;i++){
        Serial.println(OUTPUT_PATTERNS_gets[i]);
    }
    
    String ss1="Actual Output   : ",ss2="Output we gets : " ,ss3= "        ";
    Serial.println("Outputs we gets ");
    for(int i = 0 ;i< Total_gates ;i++)
        Serial.println(ss1 + OUTPUT_PATTERNS_FROM_INPUT_pins[i]+ ss3 + ss2 + OUTPUT_PATTERNS_gets[i]);
    
    IC_Output_Matching(OUTPUT_PATTERNS_FROM_INPUT_pins,Output_string_length,Total_gates,Bit_combination, OUTPUT_PATTERNS_gets);

}

//===== 7402 ==========================
void TEST_7402(){
    // 14 2 4 7402  14  7 2,3,5,6,8,9,11,12 1,4,10,13 2-14-7-2,3,5,6,8,9,11,12-1,4,10,13  00,1111-01,0000-10,0000-11,0000 Quad 2-input NOR gate   
    
    Serial.println("Testing 7402 .....");
    int GND=28, VCC=45, No_inputs=2, No_outputs=4, Total_gates=4,Output_string_length=4,Bit_combination=4;
    int OUTPUT_pins[(No_inputs * Total_gates)] = {23, 24, 26, 27, 39, 40, 42, 43};   // Output Pin array 
    int INPUT_pins[No_outputs] = {22, 25, 41, 44};                  // Input Pin array
    int INPUT_PATTERNS_TO_OUTPUT_pins[Bit_combination] =  {00,01,10,11};
    String OUTPUT_PATTERNS_FROM_INPUT_pins[Bit_combination] = {"1111","0000","0000","0000"};
    String OUTPUT_PATTERNS_gets[Bit_combination]={} , out_pat="";
    bool OUTPUT_match[Total_gates]={};
    
    Set_PIN_modes(OUTPUT_pins,INPUT_pins,GND,VCC,No_inputs, No_outputs, Total_gates);

    out_pat = Bit_2_input(OUTPUT_pins, INPUT_pins,No_inputs, No_outputs, Total_gates, Bit_combination, INPUT_PATTERNS_TO_OUTPUT_pins);
    
    for(int i = 0 ;i< Total_gates ;i++){
       OUTPUT_PATTERNS_gets[i] = String_Splitter(out_pat,'-',i);
    }

    Serial.println("Outputs we gets ");
    for(int i = 0 ;i< Total_gates ;i++){
        Serial.println(OUTPUT_PATTERNS_gets[i]);
    }
    
    String ss1="Actual Output   : ",ss2="Output we gets : " ,ss3= "        ";
    Serial.println("Outputs we gets ");
    for(int i = 0 ;i< Total_gates ;i++)
        Serial.println(ss1 + OUTPUT_PATTERNS_FROM_INPUT_pins[i]+ ss3 + ss2 + OUTPUT_PATTERNS_gets[i]);
    
    IC_Output_Matching(OUTPUT_PATTERNS_FROM_INPUT_pins,Output_string_length,Total_gates,Bit_combination, OUTPUT_PATTERNS_gets);

}

//====== 7404 =========================
void TEST_7404(){
    // 14 1 6 7404  14  7 1,3,5,9,11,13 2,4,6,8,10,12 1-14-7-1,3,5,9,11,13-2,4,6,8,10,12  1,000000-0,111111 Hex inverter  01;10 

    Serial.println("Testing 7404 .....");
    int GND=28, VCC=45, No_inputs=1, No_outputs=1, Total_gates=6,Output_string_length=6,Bit_combination=2;
    int OUTPUT_pins[(No_inputs * Total_gates)] = {22, 24, 26, 40, 41, 44};   // Output Pin array 
    int INPUT_pins[No_outputs] = {23, 25, 27, 39, 42, 43};                    // Input Pin array
    int INPUT_PATTERNS_TO_OUTPUT_pins[Bit_combination] = {1,0};
    String OUTPUT_PATTERNS_FROM_INPUT_pins[Bit_combination] = {"000000","111111"};
    String OUTPUT_PATTERNS_gets[Bit_combination]={} , out_pat="";
    bool OUTPUT_match[Total_gates]={};
    
    Set_PIN_modes(OUTPUT_pins,INPUT_pins,GND,VCC,No_inputs, No_outputs, Total_gates);

    out_pat = Bit_2_input(OUTPUT_pins, INPUT_pins,No_inputs, No_outputs, Total_gates, Bit_combination, INPUT_PATTERNS_TO_OUTPUT_pins);
    
    for(int i = 0 ;i< Total_gates ;i++){
       OUTPUT_PATTERNS_gets[i] = String_Splitter(out_pat,'-',i);
    }

    Serial.println("Outputs we gets ");
    for(int i = 0 ;i< Total_gates ;i++){
        Serial.println(OUTPUT_PATTERNS_gets[i]);
    }
    
    String ss1="Actual Output   : ",ss2="Output we gets : " ,ss3= "        ";
    Serial.println("Outputs we gets ");
    for(int i = 0 ;i< Total_gates ;i++)
        Serial.println(ss1 + OUTPUT_PATTERNS_FROM_INPUT_pins[i]+ ss3 + ss2 + OUTPUT_PATTERNS_gets[i]);
    
    IC_Output_Matching(OUTPUT_PATTERNS_FROM_INPUT_pins,Output_string_length,Total_gates,Bit_combination, OUTPUT_PATTERNS_gets);
}

//====== 7405 =========================
void TEST_7405(){
    // 14 1 6 7404  14  7 1,3,5,9,11,13 2,4,6,8,10,12 1-14-7-1,3,5,9,11,13-2,4,6,8,10,12  1,000000-0,111111 Hex inverter  01;10 
    Serial.println("Testing 7405 .....");
    TEST_7404();
}

//====== 7406 =========================
void TEST_7406(){
    // 14 1 6 7404  14  7 1,3,5,9,11,13 2,4,6,8,10,12 1-14-7-1,3,5,9,11,13-2,4,6,8,10,12  1,000000-0,111111 Hex inverter  01;10 

    Serial.println("Testing 7406 .....");
    TEST_7404();
}

//====== 7407 =========================
void TEST_7407(){
    // 14 1 6 7404  14  7 1,3,5,9,11,13 2,4,6,8,10,12 1-14-7-1,3,5,9,11,13-2,4,6,8,10,12  1,000000-0,111111 Hex inverter  01;10 

    Serial.println("Testing 7407 .....");
    TEST_7404();
}

//====== 7408 =========================
void TEST_7408(){
    // 14 2 4 7408  14  7 1,2,4,5,9,10,12,13  3,6,8,11  2-14-7-1,2,4,5,9,10,12,13-3,6,8,11  00,0000-01,0000-10,0000-11,1111 Quad 2-input AND gate     

    Serial.println("Testing 7408 .....");
    int GND=28, VCC=45,No_inputs=2, No_outputs=4, Total_gates=4,Output_string_length=4,Bit_combination=4;
    int OUTPUT_pins[(No_inputs* Total_gates)] = {22, 23, 25, 26, 40, 41, 43, 44};   // Output Pin array 
    int INPUT_pins[No_outputs] = {24, 27, 39, 42};                    // Input Pin array
    int INPUT_PATTERNS_TO_OUTPUT_pins[Bit_combination] = {00,01,10,11};
    String OUTPUT_PATTERNS_FROM_INPUT_pins[Bit_combination] = {"0000","0000","0000","1111"};
    String OUTPUT_PATTERNS_gets[Bit_combination]={},out_pat="";
    bool OUTPUT_match[Total_gates]={};

    Set_PIN_modes(OUTPUT_pins,INPUT_pins,GND,VCC,No_inputs, No_outputs, Total_gates);

    out_pat = Bit_2_input(OUTPUT_pins, INPUT_pins,No_inputs, No_outputs, Total_gates, Bit_combination, INPUT_PATTERNS_TO_OUTPUT_pins);
    
    for(int i = 0 ;i< Total_gates ;i++){
       OUTPUT_PATTERNS_gets[i] = String_Splitter(out_pat,'-',i);
    }

    Serial.println("Outputs we gets ");
    for(int i = 0 ;i< Total_gates ;i++){
        Serial.println(OUTPUT_PATTERNS_gets[i]);
    }
    
    String ss1="Actual Output   : ",ss2="Output we gets : " ,ss3= "        ";
    Serial.println("Outputs we gets ");
    for(int i = 0 ;i< Total_gates ;i++)
        Serial.println(ss1 + OUTPUT_PATTERNS_FROM_INPUT_pins[i]+ ss3 + ss2 + OUTPUT_PATTERNS_gets[i]);
    
    IC_Output_Matching(OUTPUT_PATTERNS_FROM_INPUT_pins,Output_string_length,Total_gates,Bit_combination, OUTPUT_PATTERNS_gets);
}

//====== 7409 =========================
void TEST_7409(){
    // 14 2 4 7409  14  7 1,2,4,5,9,10,12,13  3,6,8,11  2-14-7-1,2,4,5,9,10,12,13-3,6,8,11  00,0000-01,0000-10,0000-11,1111 Quad 2-input AND gate     

    Serial.println("Testing 7409 .....");
    int GND=28, VCC=45,No_inputs=2, No_outputs=4, Total_gates=4,Output_string_length=4,Bit_combination=4;
    int OUTPUT_pins[(No_inputs* Total_gates)] = {22, 23, 25, 26, 40, 41, 43, 44};   // Output Pin array 
    int INPUT_pins[No_outputs] = {24, 27, 39, 42};                    // Input Pin array
    int INPUT_PATTERNS_TO_OUTPUT_pins[Bit_combination] = {00,01,10,11};
    String OUTPUT_PATTERNS_FROM_INPUT_pins[Bit_combination] = {"0000","0000","0000","1111"};
    String OUTPUT_PATTERNS_gets[Bit_combination]={},out_pat="";
    bool OUTPUT_match[Total_gates]={};

    Set_PIN_modes(OUTPUT_pins,INPUT_pins,GND,VCC,No_inputs, No_outputs, Total_gates);

   out_pat = Bit_2_input(OUTPUT_pins, INPUT_pins,No_inputs, No_outputs, Total_gates, Bit_combination, INPUT_PATTERNS_TO_OUTPUT_pins);
    
    for(int i = 0 ;i< Total_gates ;i++){
       OUTPUT_PATTERNS_gets[i] = String_Splitter(out_pat,'-',i);
    }

    Serial.println("Outputs we gets ");
    for(int i = 0 ;i< Total_gates ;i++){
        Serial.println(OUTPUT_PATTERNS_gets[i]);
    }
    
    String ss1="Actual Output   : ",ss2="Output we gets : " ,ss3= "        ";
    Serial.println("Outputs we gets ");
    for(int i = 0 ;i< Total_gates ;i++)
        Serial.println(ss1 + OUTPUT_PATTERNS_FROM_INPUT_pins[i]+ ss3 + ss2 + OUTPUT_PATTERNS_gets[i]);
    
    IC_Output_Matching(OUTPUT_PATTERNS_FROM_INPUT_pins,Output_string_length,Total_gates,Bit_combination, OUTPUT_PATTERNS_gets);
}

//====== 7410 =========================
void TEST_7410(){
    // 14 3 3 7410  14  7 1,2,13,3,4,5,9,10,11  12,6,8  3-14-7-1,2,13,3,4,5,9,10,11-12,6,8  000,111-001,111-010,111-011,111-100,111-101,111-110,111-111,000 Triple 3-input NAND gate    

    Serial.println("Testing 7410 .....");
    int GND=28, VCC=45, No_inputs=3, No_outputs=3, Total_gates=3, Output_string_length=3, Bit_combination=8;
    int OUTPUT_pins[(No_inputs*Total_gates)] = {22, 23, 44, 24, 25, 26, 40, 41, 42};   // Output Pin array 
    int INPUT_pins[No_outputs] = {43, 27, 39};                    // Input Pin array
    String INPUT_PATTERNS_TO_OUTPUT_pins[Bit_combination] = {"000","001","010","011","100","101","110","111"};
    String OUTPUT_PATTERNS_FROM_INPUT_pins[Bit_combination] = {"111","111","111","111","111","111","111","000"};
    String OUTPUT_PATTERNS_gets[Bit_combination]={}, out_pat="";
    bool OUTPUT_match[Total_gates]={};           //IT depens on total no of gates 

    Set_PIN_modes(OUTPUT_pins,INPUT_pins,GND,VCC,No_inputs, No_outputs, Total_gates);

    out_pat = Bit_3_input(OUTPUT_pins, INPUT_pins,No_inputs, No_outputs, Total_gates, Bit_combination, INPUT_PATTERNS_TO_OUTPUT_pins);
    
    for(int i = 0 ;i< Bit_combination ;i++){
       OUTPUT_PATTERNS_gets[i] = String_Splitter(out_pat,'-',i);
    }

    Serial.println("Outputs we gets ");
    for(int i = 0 ;i< Bit_combination ;i++){
        Serial.println(OUTPUT_PATTERNS_gets[i]);
    }
    
    String ss1="Actual Output   : ",ss2="Output we gets : " ,ss3= "        ";
    Serial.println("Outputs we gets ");
    for(int i = 0 ;i< Bit_combination ;i++)
        Serial.println(ss1 + OUTPUT_PATTERNS_FROM_INPUT_pins[i]+ ss3 + ss2 + OUTPUT_PATTERNS_gets[i]);
    
    IC_Output_Matching(OUTPUT_PATTERNS_FROM_INPUT_pins,Output_string_length,Total_gates,Bit_combination, OUTPUT_PATTERNS_gets);

}

//===== 7411 ==========================
void TEST_7411(){
    // 14 3 3 7411  14  7 1,2,13,3,4,5,9,10,11  12,6,8  3-14-7-1,2,13,3,4,5,9,10,11-12,6,8  000,000-001,000-010,000-011,000-100,000-101,000-110,000-111,111 Triple 3-input AND gate   

    Serial.println("Testing 7411 .....");
    int GND=28, VCC=45, No_inputs=3, No_outputs=3, Total_gates=3,Output_string_length=3, Bit_combination=8;
    int OUTPUT_pins[(No_inputs*Total_gates)] = {22, 23, 44, 24, 25, 26, 40, 41, 42};   // Output Pin array 
    int INPUT_pins[No_outputs] = {43, 27, 39};                    // Input Pin array
    String INPUT_PATTERNS_TO_OUTPUT_pins[Bit_combination] = {"000","001","010","011","100","101","110","111"};
    String OUTPUT_PATTERNS_FROM_INPUT_pins[Bit_combination] = {"000","000","000","000","000","000","000","111"};
    String OUTPUT_PATTERNS_gets[Bit_combination]={}, out_pat="";
    bool OUTPUT_match[Total_gates]={};                     // Input Pin array

    Set_PIN_modes(OUTPUT_pins,INPUT_pins,GND,VCC,No_inputs, No_outputs, Total_gates);

    out_pat = Bit_3_input(OUTPUT_pins, INPUT_pins,No_inputs, No_outputs, Total_gates, Bit_combination, INPUT_PATTERNS_TO_OUTPUT_pins);
    
    for(int i = 0 ;i< Bit_combination ;i++){
       OUTPUT_PATTERNS_gets[i] = String_Splitter(out_pat,'-',i);
    }

    Serial.println("Outputs we gets ");
    for(int i = 0 ;i< Bit_combination ;i++){
        Serial.println(OUTPUT_PATTERNS_gets[i]);
    }
    
    String ss1="Actual Output   : ",ss2="Output we gets : " ,ss3= "        ";
    Serial.println("Outputs we gets ");
    for(int i = 0 ;i< Bit_combination ;i++)
        Serial.println(ss1 + OUTPUT_PATTERNS_FROM_INPUT_pins[i]+ ss3 + ss2 + OUTPUT_PATTERNS_gets[i]);
     
    IC_Output_Matching(OUTPUT_PATTERNS_FROM_INPUT_pins,Output_string_length,Total_gates,Bit_combination, OUTPUT_PATTERNS_gets);
 
}

//===== 7413 ==========================
void TEST_7413(){
    // 14	4	2	7413	14	7	1,2,4,5,9,10,12,13	6,8	   4-14-7-1,2,4,5,9,10,12,13-6,8	0000,11-0001,11-0010,11-0011,11-0010,11-0011,11-0110,11-0111,11-1000,11-1001,11-1010,11-1011,11-1010,11-1011,11-1110,11-1111,11	Dual 4-input NAND gate Schmitt trigger	 randomly check 10 condition 	
    Serial.println("Testing 7413 .....");
    int GND=28, VCC=45, No_inputs=4, No_outputs=2, Total_gates=2,Output_string_length=2, Bit_combination=16;
    int OUTPUT_pins[(No_inputs*Total_gates)] = {22, 23, 25, 26, 38, 39, 41, 42 };   // Output Pin array 
    int INPUT_pins[No_outputs] = {27, 29};                    // Input Pin array
    String INPUT_PATTERNS_TO_OUTPUT_pins[Bit_combination] = {"0000","0001","0010","0011","0100","0101","0110","0111","1000","1001","1010","1011","1100","1101","1110","1111"};
    String OUTPUT_PATTERNS_FROM_INPUT_pins[Bit_combination] = {"11","11","11","11","11","11","11","11","11","11","11","11","11","11","11","00"};
    String OUTPUT_PATTERNS_gets[Bit_combination]={}, out_pat="";
    bool OUTPUT_match[Total_gates]={};                     // Input Pin array

    Set_PIN_modes(OUTPUT_pins,INPUT_pins,GND,VCC,No_inputs, No_outputs, Total_gates);

    out_pat = Bit_4_input(OUTPUT_pins, INPUT_pins,No_inputs, No_outputs, Total_gates, Bit_combination, INPUT_PATTERNS_TO_OUTPUT_pins);
    
    for(int i = 0 ;i< Bit_combination ;i++){
       OUTPUT_PATTERNS_gets[i] = String_Splitter(out_pat,'-',i);
    }

    Serial.println("Outputs we gets ");
    for(int i = 0 ;i< Bit_combination ;i++){
        Serial.println(OUTPUT_PATTERNS_gets[i]);
    }
    
    String ss1="Actual Output   : ",ss2="Output we gets : " ,ss3= "        ";
    Serial.println("Outputs we gets ");
    for(int i = 0 ;i< Bit_combination ;i++)
        Serial.println(ss1 + OUTPUT_PATTERNS_FROM_INPUT_pins[i]+ ss3 + ss2 + OUTPUT_PATTERNS_gets[i]);
     
    IC_Output_Matching(OUTPUT_PATTERNS_FROM_INPUT_pins,Output_string_length,Total_gates,Bit_combination, OUTPUT_PATTERNS_gets);

}

//====== 7414 =========================
void TEST_7414(){
    // 14	1	6	7414	14	7	1,3,5,9,11,13	2,4,6,8,10,12	1-14-7-1,3,5,9,11,13-2,4,6,8,10,12	1,000000-0,111111	Hex inverter Schmitt inverter 	01;10	

    Serial.println("Testing 7414 .....");
    TEST_7404();
}

//====== 7416 =========================
void TEST_7416(){
    // 14	1	6	7416	14	7	1,3,5,9,11,13	2,4,6,8,10,12	1-14-7-1,3,5,9,11,13-2,4,6,8,10,12	1,000000-0,111111	Hex inverter Schmitt inverter 	01;10	

    Serial.println("Testing 7416 .....");
    TEST_7404();
}

//====== 7417 =========================
void TEST_7417(){
   //14	1	6	7417	14	7	1,3,5,9,11,13	2,4,6,8,10,12	1-14-7-1,3,5,9,11,13-2,4,6,8,10,12	1,000000-0,111111	Hex inverter Schmitt inverter 	01;10	

    Serial.println("Testing 7417 .....");
    TEST_7404();
}

//====== 7420 =========================
void TEST_7420(){
    // 14	4	2	7420	14	7	1,2,4,5,9,10,12,13	6,8	4-14-7-1,2,4,5,9,10,12,13-6,8	0000,11-0001,11-0010,11-0011,11-0010,11-0011,11-0110,11-0111,11-1000,11-1001,11-1010,11-1011,11-1010,11-1011,11-1110,11-1111,00	Dual 4-input NAND gate Schmitt trigger	 randomly check 10 condition 	
    
    Serial.println("Testing 7420 .....");
    TEST_7413();
}

//====== 7421 =========================
void TEST_7421(){
    // 14	4	2	7421	14	7	1,2,4,5,9,10,12,13	6,8	4-14-7-1,2,4,5,9,10,12,13-6,8	0000,00-0001,00-0010,00-0011,00-0010,00-0011,00-0110,00-0111,00-1000,00-1001,00-1010,00-1011,00-1010,00-1011,00-1110,00-1111,11	Dual 4-input AND gate	 randomly check 10 condition 	

    Serial.println("Testing 7421 .....");
    int GND=28, VCC=45, No_inputs=4, No_outputs=2, Total_gates=2,Output_string_length=2, Bit_combination=16;
    int OUTPUT_pins[(No_inputs*Total_gates)] = {22, 23, 25, 26, 38, 39, 41, 42 };   // Output Pin array 
    int INPUT_pins[No_outputs] = {27, 29};                    // Input Pin array
    String INPUT_PATTERNS_TO_OUTPUT_pins[Bit_combination] = {"0000","0001","0010","0011","0100","0101","0110","0111","1000","1001","1010","1011","1100","1101","1110","1111"};
    String OUTPUT_PATTERNS_FROM_INPUT_pins[Bit_combination] = {"00","00","00","00","00","00","00","00","00","00","00","00","00","00","00","11",};
    String OUTPUT_PATTERNS_gets[Bit_combination]={}, out_pat="";
    bool OUTPUT_match[Total_gates]={};                     // Input Pin array

    Set_PIN_modes(OUTPUT_pins,INPUT_pins,GND,VCC,No_inputs, No_outputs, Total_gates);

    out_pat = Bit_4_input(OUTPUT_pins, INPUT_pins,No_inputs, No_outputs, Total_gates, Bit_combination, INPUT_PATTERNS_TO_OUTPUT_pins);
    
    for(int i = 0 ;i< Bit_combination ;i++){
       OUTPUT_PATTERNS_gets[i] = String_Splitter(out_pat,'-',i);
    }

    Serial.println("Outputs we gets ");
    for(int i = 0 ;i< Bit_combination ;i++){
        Serial.println(OUTPUT_PATTERNS_gets[i]);
    }
    
    String ss1="Actual Output   : ",ss2="Output we gets : " ,ss3= "        ";
    Serial.println("Outputs we gets ");
    for(int i = 0 ;i< Bit_combination ;i++)
        Serial.println(ss1 + OUTPUT_PATTERNS_FROM_INPUT_pins[i]+ ss3 + ss2 + OUTPUT_PATTERNS_gets[i]);
     
    IC_Output_Matching(OUTPUT_PATTERNS_FROM_INPUT_pins,Output_string_length,Total_gates,Bit_combination, OUTPUT_PATTERNS_gets);

}

//====== 7425 =========================
void TEST_7425(){
   // 14	4	2	7425	14	7	1,2,4,5,9,10,12,13	6,8	4-14-7-1,2,4,5,9,10,12,13-6,8	0000,00-0001,00-0010,00-0011,00-0010,00-0011,00-0110,00-0111,00-1000,00-1001,00-1010,00-1011,00-1010,00-1011,00-1110,00-1111,11	Dual 4-input AND gate	 randomly check 10 condition 	

    Serial.println("Testing 7425 .....");
    TEST_7421();
}

//====== 7427 =========================
void TEST_7427(){
//    14	3	3	7427	14	7	1,2,13,3,4,5,9,10,11	12,6,8	3-14-7-1,2,13,3,4,5,9,10,11-12,6,8	000,111-001,000-010,000-011,000-100,000-101,000-110,000-111,000	Triple 3-input NOR gate	
    Serial.println("Testing 7427 .....");
    int GND=28, VCC=45, No_inputs=3, No_outputs=3, Total_gates=3, Output_string_length=3, Bit_combination=8;
    int OUTPUT_pins[(No_inputs*Total_gates)] = {22, 23, 44, 24, 25, 26, 40, 41, 42};   // Output Pin array 
    int INPUT_pins[No_outputs] = {43, 27, 39};                    // Input Pin array
    String INPUT_PATTERNS_TO_OUTPUT_pins[Bit_combination] = {"000","001","010","011","100","101","110","111"};
    String OUTPUT_PATTERNS_FROM_INPUT_pins[Bit_combination] = {"111","000","000","000","000","000","000","000"};
    String OUTPUT_PATTERNS_gets[Bit_combination]={}, out_pat="";
    bool OUTPUT_match[Total_gates]={};           //IT depens on total no of gates 

    Set_PIN_modes(OUTPUT_pins,INPUT_pins,GND,VCC,No_inputs, No_outputs, Total_gates);

    out_pat = Bit_3_input(OUTPUT_pins, INPUT_pins,No_inputs, No_outputs, Total_gates, Bit_combination, INPUT_PATTERNS_TO_OUTPUT_pins);
    
    for(int i = 0 ;i< Bit_combination ;i++){
       OUTPUT_PATTERNS_gets[i] = String_Splitter(out_pat,'-',i);
    }

    Serial.println("Outputs we gets ");
    for(int i = 0 ;i< Bit_combination ;i++){
        Serial.println(OUTPUT_PATTERNS_gets[i]);
    }
    
    String ss1="Actual Output   : ",ss2="Output we gets : " ,ss3= "        ";
    Serial.println("Outputs we gets ");
    for(int i = 0 ;i< Bit_combination ;i++)
        Serial.println(ss1 + OUTPUT_PATTERNS_FROM_INPUT_pins[i]+ ss3 + ss2 + OUTPUT_PATTERNS_gets[i]);
    
    IC_Output_Matching(OUTPUT_PATTERNS_FROM_INPUT_pins,Output_string_length,Total_gates,Bit_combination, OUTPUT_PATTERNS_gets);

    
}


//====== 7428 =========================
void TEST_7428(){
    // 14	2	4	7428	14	7	2,3,5,6,8,9,11,12	1,4,10,13	2-14-7-2,3,5,6,8,9,11,12-1,4,10,13	00,1111-01,0000-10,0000-11,0000	Quad 2-input NOR gate 		

    Serial.println("Testing 7428 .....");
    TEST_7402();
}


//===== 7430 ==========================
void TEST_7430(){
    // 14	8	1	7430	14	7	1,2,3,4,5,6,11,12	8	8-14-7-1,2,3,4,5,6,11,12-8	00000000,1-00000011,1-00001100,1-00001101,1-00001111,1-10010010,1-10110100,1-11100101,1-11101001,1-11111111,0	8-input NAND gate 	 randomly check 10 condition 	
    Serial.println("Testing 7430 .....");
    // Here we randomly check 10 condition  
    int GND=28, VCC=45, No_inputs=8, No_outputs=1, Total_gates=1,Output_string_length=1, Bit_combination=10;
    int OUTPUT_pins[(No_inputs*Total_gates)] = {22, 23, 25, 26, 38, 39, 41, 42 };   // Output Pin array 
    int INPUT_pins[No_outputs] = {29};                    // Input Pin array
    String INPUT_PATTERNS_TO_OUTPUT_pins[Bit_combination] = {"00000000","00000011","00001100","00001101","00001111","10010010","10110100","11100101","11101001","11111111"};
    String OUTPUT_PATTERNS_FROM_INPUT_pins[Bit_combination] = {"1","1","1","1","1","1","1","1","1","0"};
    String OUTPUT_PATTERNS_gets[Bit_combination]={}, out_pat="";
    bool OUTPUT_match[Total_gates]={};                     // Input Pin array


    Set_PIN_modes(OUTPUT_pins,INPUT_pins,GND,VCC,No_inputs, No_outputs, Total_gates);

    out_pat = Bit_4_input(OUTPUT_pins, INPUT_pins,No_inputs, No_outputs, Total_gates, Bit_combination, INPUT_PATTERNS_TO_OUTPUT_pins);
    
    for(int i = 0 ;i< Bit_combination ;i++){
       OUTPUT_PATTERNS_gets[i] = String_Splitter(out_pat,'-',i);
    }

    Serial.println("Outputs we gets ");
    for(int i = 0 ;i< Bit_combination ;i++){
        Serial.println(OUTPUT_PATTERNS_gets[i]);
    }
    
    String ss1="Actual Output   : ",ss2="Output we gets : " ,ss3= "        ";
    Serial.println("Outputs we gets ");
    for(int i = 0 ;i< Bit_combination ;i++)
        Serial.println(ss1 + OUTPUT_PATTERNS_FROM_INPUT_pins[i]+ ss3 + ss2 + OUTPUT_PATTERNS_gets[i]);
     
    IC_Output_Matching(OUTPUT_PATTERNS_FROM_INPUT_pins,Output_string_length,Total_gates,Bit_combination, OUTPUT_PATTERNS_gets);

}



//==== 7432 ===========================
void TEST_7432(){
    // 14	2	4	7432	14	7	1,2,4,5,9,10,12,13	3,6,8,11	2-14-7-1,2,4,5,9,10,12,13-3,6,8,11	00,0000-01,1111-10,1111-11,1111	Quad 2-input OR gate (o.c)		

    Serial.println("Testing 7432 .....");
    int GND=28, VCC=45, No_inputs=2, No_outputs=4, Total_gates=4,Output_string_length=4,Bit_combination=4;
    int OUTPUT_pins[(No_inputs*Total_gates)] = {22, 23, 25, 26, 40, 41, 43, 44};   // Output Pin array 
    int INPUT_pins[No_outputs] = {24, 27, 39, 42};                    // Input Pin array
    int INPUT_PATTERNS_TO_OUTPUT_pins[Bit_combination] = {00,01,10,11};
    String OUTPUT_PATTERNS_FROM_INPUT_pins[Bit_combination] = {"0000","1111","1111","1111"};
    String OUTPUT_PATTERNS_gets[Bit_combination]={}, out_pat="";
    bool OUTPUT_match[Total_gates]={};
    
    Set_PIN_modes(OUTPUT_pins,INPUT_pins,GND,VCC,No_inputs, No_outputs, Total_gates);


    out_pat = Bit_2_input(OUTPUT_pins, INPUT_pins,No_inputs, No_outputs, Total_gates, Bit_combination, INPUT_PATTERNS_TO_OUTPUT_pins);
    
    for(int i = 0 ;i< Total_gates ;i++){
       OUTPUT_PATTERNS_gets[i] = String_Splitter(out_pat,'-',i);
    }

    Serial.println("Outputs we gets ");
    for(int i = 0 ;i< Total_gates ;i++){
        Serial.println(OUTPUT_PATTERNS_gets[i]);
    }
    
    String ss1="Actual Output   : ",ss2="Output we gets : " ,ss3= "        ";
    Serial.println("Outputs we gets ");
    for(int i = 0 ;i< Total_gates ;i++)
        Serial.println(ss1 + OUTPUT_PATTERNS_FROM_INPUT_pins[i]+ ss3 + ss2 + OUTPUT_PATTERNS_gets[i]);
    
    IC_Output_Matching(OUTPUT_PATTERNS_FROM_INPUT_pins,Output_string_length,Total_gates,Bit_combination, OUTPUT_PATTERNS_gets);

}



//==== 7437 ===========================
void TEST_7437(){
    // 14	2	4	7437	14	7	1,2,4,5,9,10,12,13	3,6,8,11	2-14-7-1,2,4,5,9,10,12,13-3,6,8,11	00,1111-01,1111-10,1111-11,0000	Quad 2-input NAND gate 		
    TEST_7400();

}


//==== 7438 ===========================
void TEST_7438(){
    // 14	2	4	7438	14	7	1,2,4,5,9,10,12,13	3,6,8,11	2-14-7-1,2,4,5,9,10,12,13-3,6,8,11	00,1111-01,1111-10,1111-11,0000	Quad 2-input NAND gate  		

    Serial.println("Testing 7438 .....");
    TEST_7400();

}

//==== 7440 ===========================
void TEST_7440(){
    // 14	4	2	7440	14	7	1,2,4,5,9,10,12,13	6,8	        4-14-7-1,2,4,5,9,10,12,13-6,8	    0000,11-0001,11-0010,11-0011,11-0010,11-0011,11-0110,11-0111,11-1000,11-1001,11-1010,11-1011,11-1010,11-1011,11-1110,11-1111,00	Dual 4-input NAND gate	 randomly check 10 condition 	

    Serial.println("Testing 7440 .....");
    TEST_7413();
}

//===== 7442 ==========================
void TEST_7442(){
    // 16	4	10	7442	16	8	15,14,13,12	    1,2,3,4,5,6,7,9,10,11	    4 -16-8-15,14,13,12-1,2,3,4,5,6,7,9,10,11	    0000-1000000000,0001-0100000000,0010-0010000000,0011-0001000000,0100-0000100000,0101-0000010000,0110-0000001000,0111-0000000100,1000-0000000010,1001-0000000001	BCD to decimal decoder		
    
    Serial.println("Testing 7442 .....");
    // Here we randomly check 10 condition  
    int GND=29, VCC=45, No_inputs=4, No_outputs=10, Total_gates=1,Output_string_length=10, Bit_combination=10;
    int OUTPUT_pins[(No_inputs*Total_gates)] = {44, 43, 42, 41};   // Output Pin array 
    int INPUT_pins[No_outputs] = {22, 23, 24, 25, 26, 27, 28, 38, 39, 40};                    // Input Pin array
    String INPUT_PATTERNS_TO_OUTPUT_pins[Bit_combination] = {"0000","0001","0010","0011","0100","0101","0110","0111","1000","1001"};
    String OUTPUT_PATTERNS_FROM_INPUT_pins[Bit_combination] = {"1000000000","0100000000","0010000000","0001000000","0000100000","0000010000","0000001000","0000000100","0000000010","0000000001"};
    String OUTPUT_PATTERNS_gets[Bit_combination]={}, out_pat="";
    bool OUTPUT_match[Total_gates]={};                     // Input Pin array


    Set_PIN_modes(OUTPUT_pins,INPUT_pins,GND,VCC,No_inputs, No_outputs, Total_gates);

    out_pat = Bit_4_input(OUTPUT_pins, INPUT_pins,No_inputs, No_outputs, Total_gates, Bit_combination, INPUT_PATTERNS_TO_OUTPUT_pins);
    
    for(int i = 0 ;i< Bit_combination ;i++){
       OUTPUT_PATTERNS_gets[i] = String_Splitter(out_pat,'-',i);
    }

    Serial.println("Outputs we gets ");
    for(int i = 0 ;i< Bit_combination ;i++){
        Serial.println(OUTPUT_PATTERNS_gets[i]);
    }
    
    String ss1="Actual Output   : ",ss2="Output we gets : " ,ss3= "        ";
    Serial.println("Outputs we gets ");
    for(int i = 0 ;i< Bit_combination ;i++)
        Serial.println(ss1 + OUTPUT_PATTERNS_FROM_INPUT_pins[i]+ ss3 + ss2 + OUTPUT_PATTERNS_gets[i]);
     
    IC_Output_Matching(OUTPUT_PATTERNS_FROM_INPUT_pins,Output_string_length,Total_gates,Bit_combination, OUTPUT_PATTERNS_gets);

}



//==== 7445 ===========================
void TEST_7445(){
    // 16	4	10	7445	16	8	15,14,13,12 	1,2,3,4,5,6,7,9,10,11	4 -16-8-15,14,13,12-1,2,3,4,5,6,7,9,10,11	0000-1000000000,0001-0100000000,0010-0010000000,0011-0001000000,0100-0000100000,0101-0000010000,0110-0000001000,0111-0000000100,1000-0000000010,1001-0000000001	BCD to decimal decoder driver 	
    Serial.println("Testing 7445 .....");
    TEST_7442();
}


/*
//===== 7446 ==========================
void TEST_7446(){
    // 16	4	10	7446	16	8	15,14,13,12 	1,2,3,4,5,6,7,9,10,11	    4 -16-8-15,14,13,12-1,2,3,4,5,6,7,9,10,11	0000-0000001,0001-1001111,0010-0010010,0011-0000110,0100-1001100,0101-0100100,0110-1100000,0111-0000000,1000-0001100	BCD to7 seg decoder driver (o.c.)		

    Serial.println("Testing 7446 .....");
    // Here we randomly check 10 condition  
    int GND=29, VCC=45, No_inputs=4, No_outputs=10, Total_gates=1,Output_string_length=7, Bit_combination=9;
    int OUTPUT_pins[(No_inputs*Total_gates)] = {44, 43, 42, 41};   // Output Pin array 
    int INPUT_pins[No_outputs] = {22, 23, 24, 25, 26, 27, 28, 38, 39, 40};                    // Input Pin array
    String INPUT_PATTERNS_TO_OUTPUT_pins[Bit_combination] = {"0000","0001","0010","0011","0100","0101","0110","0111","1000"};
    String OUTPUT_PATTERNS_FROM_INPUT_pins[Bit_combination] = {"0000001",0001-1001111,0010-0010010,0011-0000110,0100-1001100,0101-0100100,0110-1100000,0111-0000000,1000-0001100};
    String OUTPUT_PATTERNS_gets[Bit_combination]={}, out_pat="";
    bool OUTPUT_match[Total_gates]={};                     // Input Pin array


    Set_PIN_modes(OUTPUT_pins,INPUT_pins,GND,VCC,No_inputs, No_outputs, Total_gates);

    out_pat = Bit_4_input(OUTPUT_pins, INPUT_pins,No_inputs, No_outputs, Total_gates, Bit_combination, INPUT_PATTERNS_TO_OUTPUT_pins);
    
    for(int i = 0 ;i< Bit_combination ;i++){
       OUTPUT_PATTERNS_gets[i] = String_Splitter(out_pat,'-',i);
    }

    Serial.println("Outputs we gets ");
    for(int i = 0 ;i< Bit_combination ;i++){
        Serial.println(OUTPUT_PATTERNS_gets[i]);
    }
    
    String ss1="Actual Output   : ",ss2="Output we gets : " ,ss3= "        ";
    Serial.println("Outputs we gets ");
    for(int i = 0 ;i< Bit_combination ;i++)
        Serial.println(ss1 + OUTPUT_PATTERNS_FROM_INPUT_pins[i]+ ss3 + ss2 + OUTPUT_PATTERNS_gets[i]);
     
    IC_Output_Matching(OUTPUT_PATTERNS_FROM_INPUT_pins,Output_string_length,Total_gates,Bit_combination, OUTPUT_PATTERNS_gets);

}

*/


//==== 7486 ===========================
void TEST_7486(){
    // 14	2	4	7486	14	7	1,2,4,5,9,10,12,13	3,6,8,11	2-14-7-1,2,4,5,9,10,12,13-3,6,8,11	00,0000-01,1111-10,1111-11,0000	Quad 2-input XOR gate 	00011011;1110	

    Serial.println("Testing 7486 .....");
    int GND=28, VCC=45, No_inputs=2, No_outputs=4, Total_gates=4,Output_string_length=4,Bit_combination=4;
    int OUTPUT_pins[(No_inputs*Total_gates)] = {22, 23, 25, 26, 40, 41, 43, 44};   // Output Pin array 
    int INPUT_pins[No_outputs] = {24, 27, 39, 42};                    // Input Pin array
    int INPUT_PATTERNS_TO_OUTPUT_pins[Bit_combination] = {00,01,10,11};
    String OUTPUT_PATTERNS_FROM_INPUT_pins[Bit_combination] = {"0000","1111","1111","0000"};
    String OUTPUT_PATTERNS_gets[Bit_combination]={}, out_pat="";
    bool OUTPUT_match[Total_gates]={};
    
    Set_PIN_modes(OUTPUT_pins,INPUT_pins,GND,VCC,No_inputs, No_outputs, Total_gates);


    out_pat = Bit_2_input(OUTPUT_pins, INPUT_pins,No_inputs, No_outputs, Total_gates, Bit_combination, INPUT_PATTERNS_TO_OUTPUT_pins);
    
    for(int i = 0 ;i< Total_gates ;i++){
       OUTPUT_PATTERNS_gets[i] = String_Splitter(out_pat,'-',i);
    }

    Serial.println("Outputs we gets ");
    for(int i = 0 ;i< Total_gates ;i++){
        Serial.println(OUTPUT_PATTERNS_gets[i]);
    }
    
    String ss1="Actual Output   : ",ss2="Output we gets : " ,ss3= "        ";
    Serial.println("Outputs we gets ");
    for(int i = 0 ;i< Total_gates ;i++)
        Serial.println(ss1 + OUTPUT_PATTERNS_FROM_INPUT_pins[i]+ ss3 + ss2 + OUTPUT_PATTERNS_gets[i]);
    
    IC_Output_Matching(OUTPUT_PATTERNS_FROM_INPUT_pins,Output_string_length,Total_gates,Bit_combination, OUTPUT_PATTERNS_gets);

}





// 16	4	10	7446	16	8	15,14,13,12	1,2,3,4,5,6,7,8,9,10,11	4 -16-8-15,14,13,12-1,2,3,4,5,6,7,8,9,10,11	0000-0000001,0001-1001111,0010-0010010,0011-0000110,0100-1001100,0101-0100100,0110-1100000,0111-0000000,1000-0001100	BCD to7 seg decoder driver (o.c.)		
// 16	4	10	7447	16	8	15,14,13,12	1,2,3,4,5,6,7,8,9,10,11	4 -16-8-15,14,13,12-1,2,3,4,5,6,7,8,9,10,11	0000-0000001,0001-1001111,0010-0010010,0011-0000110,0100-1001100,0101-0100100,0110-1100000,0111-0000000,1000-0001100	BCD to7 seg decoder driver		

#include<Keypad.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display\

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
    lcd.init();                      // initialize the lcd 
    lcd.backlight();
    lcd.setCursor(0,0);
    lcd.print("IC test device!");
    lcd.setCursor(0,1);
    lcd.print("Enter * to start");
    // Serial2.begin(9600);  
    inputString.reserve(6); // maximum number of digit for a number is 10, change if needed
}


void loop(){   
    start();
}


void start(){
  String s3 = "IC No.:",s4;
  char key = customKeypad.getKey();

    if (key) {
        // Serial2.println(key);
        
        if( key == '*'){
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Device is On");

            inputString=""; 
            inputString= get_IC_PART_details();               // Getting the IC part no from the user 
            IC_part_no = inputString.toInt();                 // IC_pin_no store the correct ic pin 
            s4 = s3 + IC_part_no;                             
            lcd.setCursor(0,1);
            lcd.print(s4);
            if(IC_part_no == 0000)
                Selftest_switch(1);

            else if(IC_part_no != 0000)
                IC_Tester_switch(IC_part_no);           // This function has a switch case to test the correct IC
        }
        else {lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Enter * to start"); 
        }
    }

}

void show_test(String IC){
    String  s="Test IC: ";
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(s + IC);

}
// -------THIS FUNCTION IS USED FOR GETTING THE PART NUMBER OF THE IC -----------------------------------------
String get_IC_PART_details(){

   
    int IC_part_no,i = 0;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Enter 00# ");    
    lcd.setCursor(0,1);
    lcd.print("for SelfTest ");
    delay(3000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Enter IC No.# ");
    lcd.setCursor(0,1);
    lcd.print("for Manual test ");
    IC_details = "";
    delay(3000);
    while (true){ 
        char IC_part = customKeypad.getKey();
        if( IC_part ){ 
            if ( IC_part >= '0' && IC_part <= '9') {       // only act on numeric keys
                IC_details += IC_part;                     // append new character to input string
                show_test(IC_details);
            }
            else if( IC_part == '#'){
                    return IC_details;                  // return the IC part  number
                  
            }
        }
    }
}

// ------- SCROLLING TEXT FOR LCD   -------------------
void Scrolling_text(String IC_name,int col,int row){
    int i,j=0;
    for( i=0; i<IC_name.length(); i++){
        if(i<15){
            lcd.setCursor(i,row);
            lcd.print(IC_name.charAt(i));
            delay(100);
        }
        else{
            for(i=16;i<IC_name.length(); i++){
                j++;
                lcd.setCursor(col,row);
                lcd.print(IC_name.substring(j, j+16));
                delay(410);
            }
        }
    }
}

void display_testing(int Part_no){
    String s1="Testing ", s2= " ...", s3="";
    lcd.clear();
    lcd.setCursor(0,0);
    s3=s1+ String(Part_no) + s2;
    lcd.print(s3);
          
}

//------ this function Display the matching gate name and not working pin numbers 
void display(bool arr[] ,int Output_pin[] ,int total_gates,int No_inputs ,String IC_name ,bool selftest ,int index ,String ORIGINAL_gate_pin[]){
    String s1 = "GATE " , s2=" OK        ", s4=" DAMAGE     ",s44=" DAMAGE", s5 = " PINS are : ",s6="IC is :", s7="";
    int k = (total_gates*No_inputs) - 1;
    // // Serial2.println("Inside DISPLAY ");
    int possiblity=0;

    lcd.clear();
    lcd.setCursor(0,0);
    if(IC_name.length() <= 16)
        lcd.print(IC_name);
    else
        Scrolling_text(IC_name,0,0);

    for(int m=total_gates-1; m>= 0 ; m-- ){

    }
    
    for(int j=total_gates-1 ; j>=0 , k>= 0;j-- , k-= No_inputs){
        if( arr[j] == true){
            s7= s1+ String(j+1) + s2;
            Scrolling_text(s7,0,1);
            delay(2000);
        }
        else{
            s7= s1+ String(j+1) + s4;
            Scrolling_text(s7,0,1);
            delay(3000);
            s7= s44 + s5 + ORIGINAL_gate_pin[j];
            Scrolling_text(s7,0,1);
            delay(3000);
        }
    }
    if(possiblity !=1 && selftest== true){
        Selftest_switch( index+1);
    }
    else if (possiblity == 1 && selftest== true){
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Matching IC ");
        Scrolling_text(IC_name,0,1);
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

//----- Set pin value to low --------------------
void Set_PIN_low(){
    for(int i =22; i<= 45;i++){
        pinMode(i, INPUT);
        digitalWrite(i, 0);
    }
}

/*
//----- This function used to check if the output properly match with actual outcome----------------------
void  IC_Output_Matching(String Actual_Outputs[] ,int Actual_Output_string_length, int total_gates,int combination, String Outputs[] ,String IC_name ,int No_inputs, int OUTPUT_pins[], bool selftest, int index){


    String space= "     ", space2= "    temp    ", te1,te2;
    int temp1,temp2,bit1,bit2, len ;
    bool  OUTPUT_match[total_gates]={};
    for(int i = 0 ;i < combination ;i++){
        // Serial2.println("Hello");
        // Serial2.println(Actual_Outputs[i].toInt() + space + Outputs[i].toInt());
    }

    for(int i = 0 ;i < combination ;i++){
            len = Actual_Output_string_length - 1 ;
            if(Outputs[i] == Actual_Outputs[i] ){
                if( i != 0 && OUTPUT_match[len-1] == true ){
                    // Serial2.println("Total Matched");
                    for(int n =0 ; n<= len ;n++)
                        OUTPUT_match[n]=true;
                }
                else if( i != 0 && OUTPUT_match[len-1] == false ){
                    // Serial2.println("Total Matched but as previous false ");
                    for(int n =0 ; n<= len ;n++)
                        OUTPUT_match[n]=false;
                }
            }
            else{
                // temp2 = Actual_Outputs[i].toInt();
                te2= Actual_Outputs[i];
                temp2 = te2.toInt();
                // temp1 = Outputs[i].toInt();  
                te1 =   Outputs[i];             // Outputs we get
                temp1 = te1.toInt();        // Actual Output
                // Serial2.println(temp1 + space2 + temp2 + space2 + te1.toInt() + space2 + te2.toInt());
                for(int m=0 ; m < Actual_Output_string_length ; m++){

                bit1 = temp1 % 10;
                bit2 = temp2 % 10;
                temp1 = temp1 / 10;
                temp2 = temp2 / 10;
                // Serial2.println(len);
                // Serial2.println(bit1 + space + bit2);
                // Serial2.println(temp1 + space + temp2);
                if( bit1 == bit2 ){              
                    if( OUTPUT_match[len] == false && i!=0){  
                        OUTPUT_match[len] = false;
                        // Serial2.println("matched + previous false  ");
                    }
                        
                    else {
                        OUTPUT_match[len] = true;
                        // Serial2.println("matched + true  ");
                    }
                    
                    len--;
                }
                else{
                    // Serial2.println("not matched + false ");
                    OUTPUT_match[len]=false;
                    len --;
                }
            }

        }

    }
    
    display(OUTPUT_match, OUTPUT_pins, total_gates, No_inputs, IC_name, selftest, index);
    // return  OUTPUT_match;
}

*/

void  IC_Output_Matching(String Actual_Outputs[] ,int Actual_Output_string_length, int total_gates,int combination, String Outputs[] ,String IC_name ,int No_inputs, int OUTPUT_pins[], bool selftest, int index,String ORIGINAL_gate_pin[]){


    String space= "     ", space2= "    temp    ", te1,te2;
    int temp1,temp2,bit1,bit2, len , p=0,q;
    bool  OUTPUT_match[total_gates]={};
    len = Actual_Output_string_length - 1 ;
    // Serial2.println(len);
    for(int i = 0 ;i < combination ;i++){
            
            if(Outputs[i] == Actual_Outputs[i] ){   
                if( i != 0  ) {
                    for(int a=0;a< total_gates;a++){
                        if(OUTPUT_match[a] ==  true)
                            OUTPUT_match[a]=true;
                            
                        else if(OUTPUT_match[a] ==  false )
                            OUTPUT_match[a]=false;
                    }
                }
                else if(i == 0){
                    for(int a=0;a< total_gates;a++)
                        OUTPUT_match[a]=true;
                }
                
            }
            else{
                // temp2 = Actual_Outputs[i].toInt();
                te2 = Actual_Outputs[i];
                te1 = Outputs[i];             
                // Serial2.println(te1 + space2 + te2 );

                for(int m=0 ; m <= len ; m++){
                    q = m+1;
                    if ( te1.substring(m,q) == ( te2.substring(m,q))){
                        // // Serial2.println("matched ");
                        if( i != 0){
                            if ( OUTPUT_match[m] == false)
                                OUTPUT_match[m]=false;
                            else
                                OUTPUT_match[m]=true;
                        }
                        else if(i == 0){
                            OUTPUT_match[m]=true;
                        }

                    }
                    else{
                        // // Serial2.println("not matched ");
                        OUTPUT_match[m]=false;
                    }  
                }
            }

        // // Serial2.println("");
        // // Serial2.print("{");
        // for(int a=0; a<= len ;a++){
        //     // Serial2.print(OUTPUT_match[a] + space);
        // }
        // // Serial2.print("}");
    }
    
    display(OUTPUT_match, OUTPUT_pins, total_gates, No_inputs, IC_name, selftest, index, ORIGINAL_gate_pin);

}



void  IC_Output_Matching_7442(String Actual_Outputs[] ,int Actual_Output_string_length, int total_gates,int combination, String Outputs[] ,String IC_name ,int No_inputs, int OUTPUT_pins[], bool selftest,int index,String ORIGINAL_gate_pin[]){
    String space= "     ", space2= "    temp    ", te1,te2;
    int temp1,temp2,bit1,bit2, len , p=0,q;
    bool  OUTPUT_match[total_gates]={};
    len = Actual_Output_string_length - 1 ;
    // Serial2.println(len);
    for(int i = 0 ;i < combination ;i++){
            
            if(Outputs[i] == Actual_Outputs[i] ){
                for(int n =0 ; n<= len ;n++){ 
                    if( i != 0  )  {
                        for(int a=0;a< total_gates;a++){
                            if(OUTPUT_match[a] ==  true)
                                OUTPUT_match[a]=true;
                            else if(OUTPUT_match[a] ==  false )
                                OUTPUT_match[a]=false;
                        }
                    }
                    else if(i==0){
                        for(int a=0;a< total_gates;a++)
                            OUTPUT_match[a]=true;
                    }
                }
            }
            else{
                // temp2 = Actual_Outputs[i].toInt();
                te2 = Actual_Outputs[i];
                te1 = Outputs[i];             
                // Serial2.println(te1 + space2 + te2 );

                for(int m=0 ; m <= len ; m++){
                    q = m+1;
                    if ( te1.substring(p,q) == ( te2.substring(p,q))){
                        // Serial2.println("matched ");
                        for(int a=0;a< total_gates;a++){
                            if(OUTPUT_match[a] ==  true)
                                OUTPUT_match[a]=true;
                            else if(OUTPUT_match[a] ==  false )
                                OUTPUT_match[a]=false;
                        }
                    }
                    else{
                        // Serial2.println("not matched ");
                        for(int a=0;a< total_gates;a++)
                            OUTPUT_match[a]=false;
                    
                    }  
                    p+=1;
                }
            }

        // Serial2.println("");
        // Serial2.print("{");
        for(int a=0; a<= len ;a++){
            // Serial2.print(OUTPUT_match[a] + space);
        }
        // Serial2.print("}");
    }
    
    display(OUTPUT_match, OUTPUT_pins, total_gates, No_inputs, IC_name, selftest, index,ORIGINAL_gate_pin);
    // return  OUTPUT_match;
}



/*-------- IC OUTPUT --- MATCH  -------------
void  IC_Output_Matching_7404(String Actual_Outputs[] ,int Actual_Output_string_length, int total_gates,int combination, String Outputs[] ,String IC_name ,int No_inputs, int OUTPUT_pins[], bool selftest, int index){


    String space= "     ", space2= "    temp    ", te1,te2;
    int temp1,temp2,bit1,bit2, len , p=0,q;
    bool  OUTPUT_match[total_gates]={};
    for(int i = 0 ;i < combination ;i++){
        // Serial2.println("Hello");
        // Serial2.println(Actual_Outputs[i] + space + Outputs[i]);
    }

    for(int i = 0 ;i < combination ;i++){
            len = Actual_Output_string_length - 1 ;
            if(Outputs[i] == Actual_Outputs[i] ){
                for(int n =0 ; n<= len ;n++){ 
                    if( i != 0  )  {
                        if(OUTPUT_match[n] ==  true)
                            OUTPUT_match[n]=true;
                        else
                            OUTPUT_match[n]=false;
                    }
                    else if(i==0){
                        OUTPUT_match[n]=true;
                    }
                }
            }
            else{
                // temp2 = Actual_Outputs[i].toInt();
                te2 = Actual_Outputs[i];
                te1 = Outputs[i];             
                // Serial2.println(te1 + space2 + te2 );

                for(int m=0 ; m <= len ; m++){
                    q = m+1;
                    if ( te1.substring(p,q) == ( te2.substring(p,q))){
                        // Serial2.println("matched  ");
                        if ( OUTPUT_match[m] == false)
                            OUTPUT_match[m]=false;
                        else
                            OUTPUT_match[m]=true;
                    }
                    else{
                        // Serial2.println("not matched + false ");
                        OUTPUT_match[m]=false;

                    }  
                    p+=1;
                }
            }
        // Serial2.println("");
        for(int a=0; a<= len ;a++){
            // Serial2.print(OUTPUT_match[a] + space);
        }
    }

    
    display(OUTPUT_match, OUTPUT_pins, total_gates, No_inputs, IC_name, selftest, index);
    // return  OUTPUT_match;
}

*/



//----- SET Input for 1 bit ---------------------------
String Bit_1_input(int OUTPUT_pins[],int INPUT_pins[], int IN,int OUT,int TotG, int combination, int IN_pat[]){
    //IN=> No_inputs, OUT=>No_outputs, TotG=> Total_gates, combination=> Bit_combination , IN_pat=>Input_Pattern
    String OUTPUT_PATTERNS_gets[combination]={},Output_patterns="" , sk="OUTPUT----> ", sj="temp1----> ",sl="bit1----> ";
    int temp1 , bit1,k;  
    for( int i=0;i< combination ;i++){
        temp1 = IN_pat[i];
        // // Serial2.println(sj + temp1);
        for(int j=0;j< IN*TotG;j++){
            
            // // Serial2.println( OUTPUT_pins[j] );
            pinMode(OUTPUT_pins[j], OUTPUT); 
            digitalWrite( OUTPUT_pins[j],temp1 );
            // // Serial2.println( INPUT_pins[j] ); 
            pinMode(INPUT_pins[j], INPUT);
            Output_patterns +=  String( digitalRead(INPUT_pins[j]));
            // // Serial2.println(sk + Output_patterns);
        }
        OUTPUT_PATTERNS_gets[i] = Output_patterns;
        // // Serial2.println(sk + Output_patterns);
        // Output_patterns = "";
        if(i == combination - 1)
            Output_patterns+="";
        else Output_patterns+="-";
    // // Serial2.println( Output_patterns);
    }
    return Output_patterns;
}

//----- SET Input for 2 bit ---------------------------
String Bit_2_input(int OUTPUT_pins[], int INPUT_pins[], int IN,int OUT,int TotG, int combination, int IN_pat[]){
    //IN=> No_inputs, OUT=>No_outputs, TotG=> Total_gates, combination=> Bit_combination , IN_pat=>Input_Pattern
    String OUTPUT_PATTERNS_gets[combination]={},Output_patterns="" , sk="OUTPUT----> ", sj="temp1----> ",sl="bit1----> ";
    int temp1 , bit1,k;
    for( int i=0;i< combination ;i++){
        temp1 = IN_pat[i];
        // Serial2.println(sj + temp1);
        for(int j=0;j< IN;j++){
            bit1 = temp1%10;
            // Serial2.println(sl + bit1);
            temp1 = temp1/10;
            // // Serial2.println("j==0");
            if(j == 0){                // LSB
                // // Serial2.println("j==0");
                for(int k=1; k <= (IN*OUT); k=k+2){
                    digitalWrite(OUTPUT_pins[k],bit1);
                    // delayMicroseconds(5);
                    // // Serial2.println(OUTPUT_pins[k]); 
                }
            }
            else if(j==1) {
                // // Serial2.println("j==1");
                for(k=0; k < (IN*OUT);k+=2){
                    digitalWrite(OUTPUT_pins[k],bit1);
                    // // Serial2.println(OUTPUT_pins[k]); 
                }
            }
        }
        for(int l=0 ; l < OUT; l++) {                              // READING the value 
            Output_patterns +=  String( digitalRead(INPUT_pins[l]));
        }
        OUTPUT_PATTERNS_gets[i] = Output_patterns;
        // Serial2.println(sk + Output_patterns);
        // Output_patterns = "";
        if(i == combination-1)
            Output_patterns+="";
        else Output_patterns+="-";
    }
    // return OUTPUT_PATTERNS_gets;
    // Serial2.println("IN BIT_2 INPUT");
    // Serial2.println( Output_patterns);
    return Output_patterns;
}

//----- SET Input for 3 bit ----------------------------
String Bit_3_input(int OUTPUT_pins[], int INPUT_pins[], int IN,int OUT,int TotG, int combination, String IN_pat[]){
    //IN=> No_inputs, OUT=>No_outputs, TotG=> Total_gates, combination=> Bit_combination , IN_pat=>Input_Pattern
    String OUTPUT_PATTERNS_gets[combination]={},Output_patterns="" , sk="OUTPUT----> ", sj="temp1----> ",sl="bit1----> ", r="pat----> " ,sp="  --->  ";
    int temp1 , bit1,k;
    for( int i=0;i< combination ;i++){
        temp1 = IN_pat[i].toInt();
        for(int j=0;j< IN;j++){
            bit1 = temp1%10;
            temp1 = temp1/10;
            if(j == 0){
                // Serial2.println("j==0");
                for(int k=2; k <= (IN*OUT); k=k+3){
                    digitalWrite(OUTPUT_pins[k],bit1);
                    // Serial2.println(OUTPUT_pins[k]); 
                }
            }
            else if(j==1) {
                // Serial2.println("j==1");
                for(k=1; k < (IN*OUT);k=k+3){
                    digitalWrite(OUTPUT_pins[k],bit1);
                    // Serial2.println(OUTPUT_pins[k]); 
                }
            }
            else if(j==2) {
                for(k=0; k< (IN*OUT);k=k+3){
                    digitalWrite(OUTPUT_pins[k],bit1);
                }
            }
        }
        for(int l=0 ; l < OUT; l++) {                              // READING the value 
            Output_patterns +=  String( digitalRead(INPUT_pins[l]));
        }
        OUTPUT_PATTERNS_gets[i] = Output_patterns;
        if(i == combination-1)
            Output_patterns+="";
        else Output_patterns+="-";
    }
    return Output_patterns;
}


//---- SET Input for 4 bit ----------------------------
String Bit_4_input(int OUTPUT_pins[], int INPUT_pins[], int IN,int OUT,int TotG, int combination, String IN_pat[]){
    //IN=> No_inputs, OUT=>No_outputs, TotG=> Total_gates, combination=> Bit_combination , IN_pat=>Input_Pattern
    String OUTPUT_PATTERNS_gets[combination]={},Output_patterns="" , sk="OUTPUT----> ", sj="temp1----> ",sl="bit1----> ", r="pat----> " ,sp="  --->  ";
    int temp1 , bit1,k;

    for( int i=0;i< combination ;i++){
        temp1 = IN_pat[i].toInt();
        // Serial2.println(r + IN_pat[i]);
        // Serial2.println(sj + temp1);
        for(int j=0;j< IN;j++){
            bit1 = temp1%10;
            // Serial2.println(sl + bit1);
            temp1 = temp1/10;
            if(j == 0){           // LSB
                // Serial2.println("j==0");
                for(int k=3; k <= (IN*OUT); k=k+4){
                    digitalWrite(OUTPUT_pins[k],bit1);
                    // Serial2.println(OUTPUT_pins[k]); 
                }
            }
            else if(j==1) {
                // Serial2.println("j==1");
                for(k=2; k < (IN*OUT);k=k+4){
                    digitalWrite(OUTPUT_pins[k],bit1);
                    // Serial2.println(OUTPUT_pins[k]); 
                }
            }
            else if(j==2) {
                // Serial2.println("j==2");
                for(k=1; k< (IN*OUT);k=k+4){
                    digitalWrite(OUTPUT_pins[k],bit1);
                    // Serial2.println(OUTPUT_pins[k]); 
                }
            }
            else if(j==3) {           //MSB
                // Serial2.println("j==2");
                for(k=0; k< (IN*OUT);k=k+4){
                    digitalWrite(OUTPUT_pins[k],bit1);
                    // Serial2.println(OUTPUT_pins[k]); 
                }
            }
        }
        for(int l=0 ; l < OUT; l++) {                              // READING the value 
            Output_patterns +=  String( digitalRead(INPUT_pins[l]));
            // Serial2.println(l + sp +  digitalRead(INPUT_pins[l]));
        }
        OUTPUT_PATTERNS_gets[i] = Output_patterns;
        // Serial2.println(sk + Output_patterns);
        // Output_patterns = "";
        if(i == combination-1)
            Output_patterns+="";
        else Output_patterns+="-";
    }
    // return OUTPUT_PATTERNS_gets;
    // Serial2.println("IN BIT_3_INPUT");
    // Serial2.println( Output_patterns);
    return Output_patterns;
}


//---- SET Input for 8 bit ----------------------------
String Bit_8_input(int OUTPUT_pins[], int INPUT_pins[], int IN,int OUT,int TotG, int combination, String IN_pat[]){
    //IN=> No_inputs, OUT=>No_outputs, TotG=> Total_gates, combination=> Bit_combination , IN_pat=>Input_Pattern
    String OUTPUT_PATTERNS_gets[combination]={},Output_patterns="" , sk="OUTPUT----> ", sj="temp1----> ",sl="bit1----> ", r="pat----> " ,sp="  --->  ";
    int temp1 , bit1,k;
    for( int i=0;i< combination ;i++){
        temp1 = IN_pat[i].toInt();
        // Serial2.println(r + IN_pat[i]);
        // Serial2.println(sj + temp1);
        for(int j=0;j< IN;j++){
            bit1 = temp1%10;
            // Serial2.println(sl + bit1);
            temp1 = temp1/10;
            if(j == 0){           // LSB
                // Serial2.println("j==0");
                for(int k=7; k <= (IN*OUT); k=k+8){
                    digitalWrite(OUTPUT_pins[k],bit1);
                    // Serial2.println(OUTPUT_pins[k]); 
                }
            }
            else if(j==1) {
                // Serial2.println("j==1");
                for(k=6; k < (IN*OUT);k=k+8){
                    digitalWrite(OUTPUT_pins[k],bit1);
                    // Serial2.println(OUTPUT_pins[k]); 
                }
            }
            else if(j==2) {
                // Serial2.println("j==2");
                for(k=5; k< (IN*OUT);k=k+8){
                    digitalWrite(OUTPUT_pins[k],bit1);
                    // Serial2.println(OUTPUT_pins[k]); 
                }
            }
            else if(j==3) {           
                // Serial2.println("j==3");
                for(k=4; k< (IN*OUT);k=k+8){
                    digitalWrite(OUTPUT_pins[k],bit1);
                    // Serial2.println(OUTPUT_pins[k]); 
                }
            }
            else if(j==4) {
                // Serial2.println("j==1");
                for(k=3; k < (IN*OUT);k=k+8){
                    digitalWrite(OUTPUT_pins[k],bit1);
                    // Serial2.println(OUTPUT_pins[k]); 
                }
            }
            else if(j==5) {
                // Serial2.println("j==2");
                for(k=2; k< (IN*OUT);k=k+8){
                    digitalWrite(OUTPUT_pins[k],bit1);
                    // Serial2.println(OUTPUT_pins[k]); 
                }
            }
            else if(j==6) {           
                // Serial2.println("j==3");
                for(k=1; k< (IN*OUT);k=k+8){
                    digitalWrite(OUTPUT_pins[k],bit1);
                    // Serial2.println(OUTPUT_pins[k]); 
                }
            }
            else if(j==7) {                   // MSB
                // Serial2.println("j==1");
                for(k=0; k < (IN*OUT);k=k+8){
                    digitalWrite(OUTPUT_pins[k],bit1);
                    // Serial2.println(OUTPUT_pins[k]); 
                }
            }
            
        }
        for(int l=0 ; l < OUT; l++) {                              // READING the value 
            Output_patterns +=  String( digitalRead(INPUT_pins[l]));
            // Serial2.println(l + sp +  digitalRead(INPUT_pins[l]));
        }
        OUTPUT_PATTERNS_gets[i] = Output_patterns;
        // Serial2.println(sk + Output_patterns);
        // Output_patterns = "";
        if(i == combination-1)
            Output_patterns+="";
        else Output_patterns+="-";
    }
    // return OUTPUT_PATTERNS_gets;
    // Serial2.println("IN BIT_3_INPUT");
    // Serial2.println( Output_patterns);
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

//----- Switch case ------------------------------
void IC_Tester_switch(int IC_part){
    String IC_name="";
    // Serial2.println("Inside SWITCH ");
    // if( IC_pin == 14 ){
    switch (IC_part){
        case 7400: 
            IC_name=" 7400 (Quad 2-input NAND gate) "; 
            // Serial2.println("Testing 7400 .....");
            TEST_7400(IC_name,false,-1);
            break;
        case 7401:
            IC_name=" 7401 (Quad 2-input NAND gate (O.C.)) ";
            display_testing(7401);
            TEST_7401(IC_name,false,-1);
            break;
        case 7402:
            IC_name=" 7402 (Quad 2-input NOR gate) ";
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Testing 7402 ...");  
            // Serial2.println("Testing 7402 .....");
            TEST_7402(IC_name,false,-1);
            break;
        case 7404: 
            IC_name=" 7404 (Hex inverter) ";
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Testing 7404 ...");
            // Serial2.println("Testing 7404 .....");
            TEST_7404(IC_name,false,-1);
            break;
        case 7405:
            IC_name=" 7405 (Hex inverter) ";
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Testing 7405 ..."); 
            // Serial2.println("Testing 7405 .....");
            TEST_7405(IC_name,false,-1);
            break;
        case 7406:
            IC_name=" 7406 (Hex inverter) ";
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Testing 7406 ..."); 
            // Serial2.println("Testing 7406 .....");
            TEST_7406(IC_name,false,-1);
            break;
        case 7407:
            IC_name=" 7407 (Hex inverter) ";
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Testing 7407 ...");  
            // Serial2.println("Testing 7407 .....");
            TEST_7407(IC_name,false,-1);
            break;
        case 7408:
            IC_name=" 7408 (Quad 2-input AND gate ) ";
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Testing 7408 ..."); 
            // Serial2.println("Testing 7408 .....");
            TEST_7408(IC_name,false,-1);
            break;
        case 7409:
            IC_name=" 7409 (Quad 2-input AND gate) ";
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Testing 7409 ...");
            // Serial2.println("Testing 7409 .....");
            TEST_7409(IC_name,false,-1);
            break;
        case 7410:
            IC_name=" 7410 (Triple 3-input NAND gate )";
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Testing 7410 ..."); 
            // Serial2.println("Testing 7410 .....");
            TEST_7410(IC_name,false,-1);
            break;
        case 7411: 
            IC_name=" 7411 (Triple 3-input AND gate) ";
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Testing 7411 ...");
            // Serial2.println("Testing 7411 .....");
            TEST_7411(IC_name,false,-1);
            break;
        case 7413: 
            IC_name=" 7413 (Dual 4-input NAND gate Schmitt trigger ) ";
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Testing 7413 ...");
            // Serial2.println("Testing 7413 .....");
            TEST_7413(IC_name,false,-1);
            break;
        case 7414: 
            IC_name=" 7414 (Hex inverter Schmitt inverter ) ";
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Testing 7414 ..."); 
            // Serial2.println("Testing 7414 .....");
            TEST_7414(IC_name,false,-1);
            break;
        case 7416:
            IC_name=" 7416 (Hex inverter Schmitt inverter ) ";
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Testing 7416 ..."); 
            // Serial2.println("Testing 7416 .....");
            TEST_7416(IC_name,false,-1);
            break;
        case 7417:
            IC_name=" 7417 (Hex inverter Schmitt inverter ) ";
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Testing 7417 ...");  
            // Serial2.println("Testing 7417 .....");
            TEST_7417(IC_name,false,-1);
            break;
        case 7420:
            IC_name=" 7420 (Dual 4-input NAND gate Schmitt trigger ) ";
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Testing 7420 ..."); 
            // Serial2.println("Testing 7420 .....");
            TEST_7420(IC_name,false,-1);
            break;
        case 7421:
            IC_name=" 7421 ( Dual 4-input AND gate ) ";
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Testing 7421 ...");  
            // Serial2.println("Testing 7421 .....");
            TEST_7421(IC_name,false,-1);
            break;
        case 7425: 
            IC_name=" 7425 ( Dual 4-input AND gate ) "; 
            // Serial2.println("Testing 7425 .....");
            TEST_7425(IC_name,false,-1);
            break;
        case 7427:
            IC_name=" 7427 ( Triple 3-input NOR gater ) ";
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Testing 7427 ..."); 
            // Serial2.println("Testing 7427 .....");
            TEST_7427(IC_name,false,-1);
            break;
        case 7428:
            IC_name=" 7428 ( Quad 2-input NOR gate  ) ";
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Testing 7428 ..."); 
            // Serial2.println("Testing 7428 .....");
            TEST_7428(IC_name,false,-1);
            break;
        case 7430:
            IC_name=" 7430 ( 8-input NAND gate ) ";
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Testing 7430 ...");  
            // Serial2.println("Testing 7430 .....");
            TEST_7430(IC_name,false,-1);
            break;
        case 7432: 
            IC_name=" 7432 ( Quad 2-input OR gate (o.c)) ";
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Testing 7432 ..."); 
            // Serial2.println("Testing 7432 .....");
            TEST_7432(IC_name,false,-1);
            break;
        case 7437: 
            IC_name=" 7437 ( Quad 2-input NAND gate ) ";
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Testing 7437 ...");
            // Serial2.println("Testing 7437 .....");
            TEST_7437(IC_name,false,-1);
            break;
        case 7438:
            IC_name=" 7438 ( Quad 2-input NAND gate ) ";
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Testing 7438 ...");  
            // Serial2.println("Testing 7438 .....");
            TEST_7438(IC_name,false,-1);
            break;
        case 7440: 
            IC_name=" 7440 ( Dual 4-input NAND gate ) ";
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Testing 7440 ..."); 
            // Serial2.println("Testing 7440 .....");
            TEST_7440(IC_name,false,-1);
            break;
        case 7442:
            IC_name=" 7442 ( BCD to decimal decoder ) ";
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Testing 7442 ..."); 
            // Serial2.println("Testing 7442 .....");
            TEST_7442(IC_name,false,-1);
            break;
        case 7445: 
            IC_name=" 7445 ( BCD to decimal decoder driver ) ";
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Testing 7445 ..."); 
            // Serial2.println("Testing 7445 .....");
            TEST_7445(IC_name,false,-1);
            break;
        case 7446: 
            IC_name=" 7446 ( BCD to7 seg decoder driver (o.c.) ) ";
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Testing 7446 ..."); 
            // Serial2.println("Testing 7446 .....");
            TEST_7445(IC_name,false,-1);
            break;
       case 7486:
            IC_name=" 7486 ( Quad 2-input XOR gate  ) ";
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Testing 7486 ..."); 
            // Serial2.println("Testing 7486 .....");
            TEST_7486(IC_name,false,-1);
            break;
        
        
        
        
        default:
            break;
        }
    // }
    
}


//----- Self test Switch case ------------------------------
void Selftest_switch(int index){
    String IC_name="";
    // Serial2.println("SWITCH ");
    // Serial2.println(index);
    // if( IC_pin == 14 ){
        switch (index){
        case 1: 
            IC_name=" 7400 (Quad 2-input NAND gate) ";
            display_testing(7400);
            TEST_7400(IC_name,true,index);
            break;
        case 2:
            IC_name=" 7401 (Quad 2-input NAND gate (O.C.)) ";
            display_testing(7401);
            TEST_7401(IC_name,true,index);
            break;
        case 3:
            IC_name=" 7402 (Quad 2-input NOR gate) ";
            display_testing(7402);
            TEST_7402(IC_name,true,index);
            break;
        case 4: 
            IC_name=" 7404 (Hex inverter) ";
            display_testing(7404);
            TEST_7404(IC_name,true,index);
            break;
        case 5:
            IC_name=" 7405 (Hex inverter) ";
            display_testing(7405);
            TEST_7405(IC_name,true,index);
            break;
        case 6:
            IC_name=" 7406 (Hex inverter) ";
            display_testing(7406);
            TEST_7406(IC_name,true,index);
            break;
        case 7:
            IC_name=" 7407 (Hex inverter) ";
            display_testing(7407);
            TEST_7407(IC_name,true,index);
            break;
        case 8:
            IC_name=" 7408 (Quad 2-input AND gate ) ";
            display_testing(7408);
            TEST_7408(IC_name,true,index);
            break;
        case 9:
            IC_name=" 7409 (Quad 2-input AND gate) ";
            display_testing(7409);
            TEST_7409(IC_name,true,index);
            break;
        case 10:
            IC_name=" 7410 (Triple 3-input NAND gate )";
            display_testing(7410);
            TEST_7410(IC_name,true,index);
            break;
        case 11: 
            IC_name=" 7411 (Triple 3-input AND gate) ";
            display_testing(7411);
            TEST_7411(IC_name,true,index);
            break;
        case 12: 
            IC_name=" 7413 (Dual 4-input NAND gate Schmitt trigger ) ";
            display_testing(7413);
            TEST_7413(IC_name,true,index);
            break;
        case 13: 
            IC_name=" 7414 (Hex inverter Schmitt inverter ) ";
            display_testing(7414);
            TEST_7414(IC_name,true,index);
            break;
        case 14:
            IC_name=" 7416 (Hex inverter Schmitt inverter ) ";
            display_testing(7416);
            TEST_7416(IC_name,true,index);
            break;
        case 15:
            IC_name=" 7417 (Hex inverter Schmitt inverter ) ";
            display_testing(7417);
            TEST_7417(IC_name,true,index);
            break;
        case 16:
            IC_name=" 7420 (Dual 4-input NAND gate Schmitt trigger ) ";
            display_testing(7420);
            TEST_7420(IC_name,true,index);
            break;
        case 17:
            IC_name=" 7421 ( Dual 4-input AND gate ) ";
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Testing 7421 ...");  
            // Serial2.println("Testing 7421 .....");
            TEST_7421(IC_name,true,index);
            break;
        case 18: 
            IC_name=" 7425 ( Dual 4-input AND gate ) "; 
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Testing 7425 ...");
            // Serial2.println("Testing 7425 .....");
            TEST_7425(IC_name,true,index);
            break;
        case 19:
            IC_name=" 7427 ( Triple 3-input NOR gater ) ";
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Testing 7427 ..."); 
            // Serial2.println("Testing 7427 .....");
            TEST_7427(IC_name,true,index);
            break;
        case 20:
            IC_name=" 7428 ( Quad 2-input NOR gate) ";
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Testing 7428 ..."); 
            // Serial2.println("Testing 7428 .....");
            TEST_7428(IC_name,true,index);
            break;
        case 21:
            IC_name=" 7430 ( 8-input NAND gate ) ";  
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Testing 7430 ...");
            // Serial2.println("Testing 7430 .....");
            TEST_7430(IC_name,true,index);
            break;
        case 22: 
            IC_name=" 7432 ( Quad 2-input OR gate (o.c)) "; 
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Testing 7432 ...");
            // Serial2.println("Testing 7432 .....");
            TEST_7432(IC_name,true,index);
            break;
        case 23: 
            IC_name=" 7437 ( Quad 2-input NAND gate ) ";
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Testing 7437 ..."); 
            // Serial2.println("Testing 7437 .....");
            TEST_7437(IC_name,true,index);
            break;
        case 24:
            IC_name=" 7438 ( Quad 2-input NAND gate ) ";
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Testing 7438 ...");  
            // Serial2.println("Testing 7438 .....");
            TEST_7438(IC_name,true,index);
            break;
        case 25: 
            IC_name=" 7440 ( Dual 4-input NAND gate ) "; 
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Testing 7440 ...");
            // Serial2.println("Testing 7440 .....");
            TEST_7440(IC_name,true,index);
            break;
        case 26:
            IC_name=" 7442 ( BCD to decimal decoder ) ";
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Testing 7442 ..."); 
            // Serial2.println("Testing 7442 .....");
            TEST_7442(IC_name,true,index);
            break;
        case 27: 
            IC_name=" 7445 ( BCD to decimal decoder driver ) ";
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Testing 7445 ..."); 
            // Serial2.println("Testing 7445 .....");
            TEST_7445(IC_name,true,index);
            break;
        case 28: 
            IC_name=" 7446 ( BCD to7 seg decoder driver (o.c.))";
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Testing 7446 ..."); 
            // Serial2.println("Testing 7446 .....");
            TEST_7445(IC_name,true,index);
            break;
       case 29:
           IC_name=" 7486 ( Quad 2-input XOR gate  ) "; 
           lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Testing 7486 ...");
           // Serial2.println("Testing 7486 .....");
           TEST_7486(IC_name,true,index);
           break;
        // case 7413: 
        //     IC_name=" 7440 ( Dual 4-input NAND gate ) "; 
        //     // Serial2.println("Testing 7440 .....");
        //     TEST_7440(IC_name);
        //     break;
        
        
        
        
        default:
            break;
        }
    // }
    
}

//------ INDIVIDUAL IC TESTING FUNCTION --------------------
//==== 7400 ===========================
void TEST_7400(String IC_name, bool Selftest, int index){
    // 14  2 4 7400  14  7 1,2,4,5,9,10,12,13  3,6,8,11  2-14-7-1,2,4,5,9,10,12,13-3,6,8,11  00,1111-01,1111-10,1111-11,0000 Quad 2-input NAND gate  00011011;1110 
    
    int GND=28, VCC=45, No_inputs=2, No_outputs=4, Total_gates=4,Output_string_length=4,Bit_combination=4;
    int OUTPUT_pins[(No_inputs*Total_gates)] = {22, 23, 25, 26, 40, 41, 43, 44};   // Output Pin array 
    int INPUT_pins[No_outputs] = {24, 27, 39, 42};                    // Input Pin array
    int INPUT_PATTERNS_TO_OUTPUT_pins[Bit_combination] = {00,01,10,11};
    String OUTPUT_PATTERNS_FROM_INPUT_pins[Bit_combination] = {"1111","1111","1111","0000"};
    String ORIGINAL_gate_pin[Total_gates]={"1,2-3","4,5-6","9,10-8","12,13-11"};
    String OUTPUT_PATTERNS_gets[Bit_combination]={}, out_pat="";
    bool OUTPUT_match[Total_gates]={};
    
    Set_PIN_modes(OUTPUT_pins,INPUT_pins,GND,VCC,No_inputs, No_outputs, Total_gates);


    out_pat = Bit_2_input(OUTPUT_pins, INPUT_pins,No_inputs, No_outputs, Total_gates, Bit_combination, INPUT_PATTERNS_TO_OUTPUT_pins);
    
    for(int i = 0 ;i< Total_gates ;i++){
       OUTPUT_PATTERNS_gets[i] = String_Splitter(out_pat,'-',i);
    }

    // Serial2.println("Outputs we gets ");
    for(int i = 0 ;i< Total_gates ;i++){
        // Serial2.println(OUTPUT_PATTERNS_gets[i]);
    }
    
    String ss1="Actual Output   : ",ss2="Output we gets : " ,ss3= "        ";
    // Serial2.println("Outputs we gets ");
    for(int i = 0 ;i< Total_gates ;i++)
        // Serial2.println(ss1 + OUTPUT_PATTERNS_FROM_INPUT_pins[i]+ ss3 + ss2 + OUTPUT_PATTERNS_gets[i]);
    
    IC_Output_Matching(OUTPUT_PATTERNS_FROM_INPUT_pins,Output_string_length,Total_gates,Bit_combination,OUTPUT_PATTERNS_gets,IC_name,No_inputs,OUTPUT_pins,Selftest,index,ORIGINAL_gate_pin);

}

//===== 7401 ==========================
void TEST_7401(String IC_name, bool Selftest, int index){
    // 14  2 4 7401  14  7 2,3,5,6,8,9,11,12 1,4,10,13 2-14-7-2,3,5,6,8,9,11,12-1,4,10,13  00,1111-01,1111-10,1111-11,0000 Quad 2-input NAND gate (O.C.)      
    int GND=28, VCC=45, No_inputs=2, No_outputs=4, Total_gates=4, Output_string_length=4,Bit_combination=4;
    int OUTPUT_pins[(No_inputs*Total_gates)] = {23, 24, 26, 27, 39, 40, 42, 43};   // Output Pin array 
    int INPUT_pins[No_outputs] = {22, 25, 41, 44};                    // Input Pin array
    int INPUT_PATTERNS_TO_OUTPUT_pins[Bit_combination] = {00,01,10,11};
    String OUTPUT_PATTERNS_FROM_INPUT_pins[Bit_combination] = {"1111","1111","1111","0000"};
    String ORIGINAL_gate_pin[Total_gates]={"2,3-1","5,6-4","8,9-10","11,12-13"};
    String OUTPUT_PATTERNS_gets[Bit_combination]={}, out_pat="" ;
    bool OUTPUT_match[Total_gates]={};
 
    Set_PIN_modes(OUTPUT_pins,INPUT_pins,GND,VCC,No_inputs, No_outputs, Total_gates);

    out_pat = Bit_2_input(OUTPUT_pins, INPUT_pins,No_inputs, No_outputs, Total_gates, Bit_combination, INPUT_PATTERNS_TO_OUTPUT_pins);
    
    for(int i = 0 ;i< Total_gates ;i++){
       OUTPUT_PATTERNS_gets[i] = String_Splitter(out_pat,'-',i);
    }
    
    IC_Output_Matching(OUTPUT_PATTERNS_FROM_INPUT_pins,Output_string_length,Total_gates,Bit_combination, OUTPUT_PATTERNS_gets, IC_name,No_inputs, OUTPUT_pins , Selftest, index,ORIGINAL_gate_pin);

}

//===== 7402 ==========================
void TEST_7402(String IC_name, bool Selftest, int index){
    // 14 2 4 7402  14  7 2,3,5,6,8,9,11,12 1,4,10,13 2-14-7-2,3,5,6,8,9,11,12-1,4,10,13  00,1111-01,0000-10,0000-11,0000 Quad 2-input NOR gate   
    
    int GND=28, VCC=45, No_inputs=2, No_outputs=4, Total_gates=4,Output_string_length=4,Bit_combination=4;
    int OUTPUT_pins[(No_inputs * Total_gates)] = {23, 24, 26, 27, 39, 40, 42, 43};   // Output Pin array 
    int INPUT_pins[No_outputs] = {22, 25, 41, 44};                  // Input Pin array
    int INPUT_PATTERNS_TO_OUTPUT_pins[Bit_combination] =  {00,01,10,11};
    String OUTPUT_PATTERNS_FROM_INPUT_pins[Bit_combination] = {"1111","0000","0000","0000"};
    String ORIGINAL_gate_pin[Total_gates]={"2,3-1","5,6-4","8,9-10","11,12-13"};
    String OUTPUT_PATTERNS_gets[Bit_combination]={} , out_pat="";
    bool OUTPUT_match[Total_gates]={};
    
    Set_PIN_modes(OUTPUT_pins,INPUT_pins,GND,VCC,No_inputs, No_outputs, Total_gates);

    out_pat = Bit_2_input(OUTPUT_pins, INPUT_pins,No_inputs, No_outputs, Total_gates, Bit_combination, INPUT_PATTERNS_TO_OUTPUT_pins);
    
    for(int i = 0 ;i< Total_gates ;i++){
       OUTPUT_PATTERNS_gets[i] = String_Splitter(out_pat,'-',i);
    }
    IC_Output_Matching(OUTPUT_PATTERNS_FROM_INPUT_pins,Output_string_length,Total_gates,Bit_combination, OUTPUT_PATTERNS_gets, IC_name,No_inputs, OUTPUT_pins , Selftest, index,ORIGINAL_gate_pin);

}


//====== 7404 =========================
void TEST_7404(String IC_name, bool Selftest, int index){
    // 14 1 6 7404  14  7 1,3,5,9,11,13 2,4,6,8,10,12 1-14-7-1,3,5,9,11,13-2,4,6,8,10,12  1,000000-0,111111 Hex inverter  01;10 
    
    int GND=28, VCC=45, No_inputs=1, No_outputs=6, Total_gates=6,Output_string_length=6,Bit_combination=2;
    int OUTPUT_pins[(No_inputs * Total_gates)] = {22, 24, 26, 40, 42, 44};   // Output Pin array 
    int INPUT_pins[No_outputs] ={23, 25, 27, 39, 41, 43}; 
    int INPUT_PATTERNS_TO_OUTPUT_pins[Bit_combination] = {0,1};
    String OUTPUT_PATTERNS_FROM_INPUT_pins[Bit_combination] = {"111111","000000"};
    String ORIGINAL_gate_pin[Total_gates]={"1-2","3-4","5-6","9-8","11-10","13-12"};
    String OUTPUT_PATTERNS_gets[Bit_combination]={} , out_pat="";
    bool OUTPUT_match[Total_gates]={};
    
    Set_PIN_modes(OUTPUT_pins,INPUT_pins,GND,VCC,No_inputs, No_outputs, Total_gates);
        
    out_pat = Bit_1_input(OUTPUT_pins,INPUT_pins , No_inputs, No_outputs, Total_gates, Bit_combination, INPUT_PATTERNS_TO_OUTPUT_pins);
    

    for(int i = 0 ;i< Bit_combination ;i++){
       OUTPUT_PATTERNS_gets[i] = String_Splitter(out_pat,'-',i);
    }
    
    String ss1="Actual Output   : ",ss2="Output we gets : " ,ss3= "        ";
    IC_Output_Matching(OUTPUT_PATTERNS_FROM_INPUT_pins,Output_string_length,Total_gates,Bit_combination, OUTPUT_PATTERNS_gets, IC_name,No_inputs, OUTPUT_pins , Selftest, index,ORIGINAL_gate_pin);

}


//====== 7405 =========================
void TEST_7405(String IC_name ,bool Selftest, int index){
    // 14 1 6 7404  14  7 1,3,5,9,11,13 2,4,6,8,10,12 1-14-7-1,3,5,9,11,13-2,4,6,8,10,12  1,000000-0,111111 Hex inverter  01;10 
    TEST_7404(IC_name, Selftest, index);
}

//====== 7406 =========================
void TEST_7406(String IC_name, bool Selftest, int index){
    // 14 1 6 7404  14  7 1,3,5,9,11,13 2,4,6,8,10,12 1-14-7-1,3,5,9,11,13-2,4,6,8,10,12  1,000000-0,111111 Hex inverter  01;10 
    TEST_7404(IC_name, Selftest, index);
}

//====== 7407 =========================
void TEST_7407(String IC_name, bool Selftest, int index){
    // 14 1 6 7404  14  7 1,3,5,9,11,13 2,4,6,8,10,12 1-14-7-1,3,5,9,11,13-2,4,6,8,10,12  1,000000-0,111111 Hex inverter  01;10 

    int GND=28, VCC=45, No_inputs=1, No_outputs=6, Total_gates=6,Output_string_length=6,Bit_combination=2;
    int OUTPUT_pins[(No_inputs * Total_gates)] = {22, 24, 26, 40, 42, 44};   // Output Pin array 
    int INPUT_pins[No_outputs] ={23, 25, 27, 39, 41, 43}; 
    int INPUT_PATTERNS_TO_OUTPUT_pins[Bit_combination] = {0,1};
    String OUTPUT_PATTERNS_FROM_INPUT_pins[Bit_combination] = {"000000","111111"};
    String ORIGINAL_gate_pin[Total_gates]={"1-2","3-4","5-6","9-8","11-10","13-12"};
    String OUTPUT_PATTERNS_gets[Bit_combination]={} , out_pat="";
    bool OUTPUT_match[Total_gates]={};
    
    Set_PIN_modes(OUTPUT_pins,INPUT_pins,GND,VCC,No_inputs, No_outputs, Total_gates);
        
    out_pat = Bit_1_input(OUTPUT_pins,INPUT_pins , No_inputs, No_outputs, Total_gates, Bit_combination, INPUT_PATTERNS_TO_OUTPUT_pins);
    

    for(int i = 0 ;i< Bit_combination ;i++){
       OUTPUT_PATTERNS_gets[i] = String_Splitter(out_pat,'-',i);
    }
    IC_Output_Matching(OUTPUT_PATTERNS_FROM_INPUT_pins,Output_string_length,Total_gates,Bit_combination, OUTPUT_PATTERNS_gets, IC_name,No_inputs, OUTPUT_pins , Selftest, index,ORIGINAL_gate_pin);

}

//====== 7408 =========================
void TEST_7408(String IC_name, bool Selftest, int index){
    // 14 2 4 7408  14  7 1,2,4,5,9,10,12,13  3,6,8,11  2-14-7-1,2,4,5,9,10,12,13-3,6,8,11  00,0000-01,0000-10,0000-11,1111 Quad 2-input AND gate     
    
    int GND=28, VCC=45,No_inputs=2, No_outputs=4, Total_gates=4,Output_string_length=4,Bit_combination=4;
    int OUTPUT_pins[(No_inputs* Total_gates)] = {22, 23, 25, 26, 40, 41, 43, 44};   // Output Pin array 
    int INPUT_pins[No_outputs] = {24, 27, 39, 42};                    // Input Pin array
    int INPUT_PATTERNS_TO_OUTPUT_pins[Bit_combination] = {00,01,10,11};
    String OUTPUT_PATTERNS_FROM_INPUT_pins[Bit_combination] = {"0000","0000","0000","1111"};
    String ORIGINAL_gate_pin[Total_gates]={"1,2-3","4,5-6","9,10-8","12,13-11"};
    String OUTPUT_PATTERNS_gets[Bit_combination]={},out_pat="";
    bool OUTPUT_match[Total_gates]={};

    Set_PIN_modes(OUTPUT_pins,INPUT_pins,GND,VCC,No_inputs, No_outputs, Total_gates);

    out_pat = Bit_2_input(OUTPUT_pins, INPUT_pins,No_inputs, No_outputs, Total_gates, Bit_combination, INPUT_PATTERNS_TO_OUTPUT_pins);
    
    for(int i = 0 ;i< Total_gates ;i++){
       OUTPUT_PATTERNS_gets[i] = String_Splitter(out_pat,'-',i);
    }
    
    IC_Output_Matching(OUTPUT_PATTERNS_FROM_INPUT_pins,Output_string_length,Total_gates,Bit_combination, OUTPUT_PATTERNS_gets, IC_name,No_inputs, OUTPUT_pins , Selftest, index,ORIGINAL_gate_pin);

}

//====== 7409 =========================
void TEST_7409(String IC_name ,bool Selftest, int index){
    // 14 2 4 7409  14  7 1,2,4,5,9,10,12,13  3,6,8,11  2-14-7-1,2,4,5,9,10,12,13-3,6,8,11  00,0000-01,0000-10,0000-11,1111 Quad 2-input AND gate     
    
    int GND=28, VCC=45,No_inputs=2, No_outputs=4, Total_gates=4,Output_string_length=4,Bit_combination=4;
    int OUTPUT_pins[(No_inputs* Total_gates)] = {22, 23, 25, 26, 40, 41, 43, 44};   // Output Pin array 
    int INPUT_pins[No_outputs] = {24, 27, 39, 42};                    // Input Pin array
    int INPUT_PATTERNS_TO_OUTPUT_pins[Bit_combination] = {00,01,10,11};
    String OUTPUT_PATTERNS_FROM_INPUT_pins[Bit_combination] = {"0000","0000","0000","1111"};
    String ORIGINAL_gate_pin[Total_gates]={"1,2-3","4,5-6","9,10-8","12,13-11"};
    String OUTPUT_PATTERNS_gets[Bit_combination]={},out_pat="";
    bool OUTPUT_match[Total_gates]={};

    Set_PIN_modes(OUTPUT_pins,INPUT_pins,GND,VCC,No_inputs, No_outputs, Total_gates);

    out_pat = Bit_2_input(OUTPUT_pins, INPUT_pins,No_inputs, No_outputs, Total_gates, Bit_combination, INPUT_PATTERNS_TO_OUTPUT_pins);
    
    for(int i = 0 ;i< Total_gates ;i++){
       OUTPUT_PATTERNS_gets[i] = String_Splitter(out_pat,'-',i);
    }
    IC_Output_Matching(OUTPUT_PATTERNS_FROM_INPUT_pins,Output_string_length,Total_gates,Bit_combination, OUTPUT_PATTERNS_gets, IC_name,No_inputs, OUTPUT_pins , Selftest, index,ORIGINAL_gate_pin);

}

//====== 7410 =========================
void TEST_7410(String IC_name, bool Selftest, int index){
    // 14 3 3 7410  14  7 1,2,13,3,4,5,9,10,11  12,6,8  3-14-7-1,2,13,3,4,5,9,10,11-12,6,8  000,111-001,111-010,111-011,111-100,111-101,111-110,111-111,000 Triple 3-input NAND gate    
    
    int GND=28, VCC=45, No_inputs=3, No_outputs=3, Total_gates=3, Output_string_length=3, Bit_combination=8;
    int OUTPUT_pins[(No_inputs*Total_gates)] = {22, 23, 44, 24, 25, 26, 40, 41, 42};   // Output Pin array 
    int INPUT_pins[No_outputs] = {43, 27, 39};                    // Input Pin array
    String INPUT_PATTERNS_TO_OUTPUT_pins[Bit_combination] = {"000","001","010","011","100","101","110","111"};
    String OUTPUT_PATTERNS_FROM_INPUT_pins[Bit_combination] = {"111","111","111","111","111","111","111","000"};
    String ORIGINAL_gate_pin[Total_gates]={"1,2,13-12","3,4,5-6","9,10,11-8"};
    String OUTPUT_PATTERNS_gets[Bit_combination]={}, out_pat="";
    bool OUTPUT_match[Total_gates]={};           //IT depens on total no of gates 

    Set_PIN_modes(OUTPUT_pins,INPUT_pins,GND,VCC,No_inputs, No_outputs, Total_gates);

    out_pat = Bit_3_input(OUTPUT_pins, INPUT_pins,No_inputs, No_outputs, Total_gates, Bit_combination, INPUT_PATTERNS_TO_OUTPUT_pins);
    
    for(int i = 0 ;i< Bit_combination ;i++){
       OUTPUT_PATTERNS_gets[i] = String_Splitter(out_pat,'-',i);
    }
    IC_Output_Matching(OUTPUT_PATTERNS_FROM_INPUT_pins,Output_string_length,Total_gates,Bit_combination, OUTPUT_PATTERNS_gets, IC_name,No_inputs, OUTPUT_pins , Selftest, index,ORIGINAL_gate_pin);

}

//===== 7411 ==========================
void TEST_7411(String IC_name, bool Selftest, int index){
    // 14 3 3 7411  14  7 1,2,13,3,4,5,9,10,11  12,6,8  3-14-7-1,2,13,3,4,5,9,10,11-12,6,8  000,000-001,000-010,000-011,000-100,000-101,000-110,000-111,111 Triple 3-input AND gate   
   
    int GND=28, VCC=45, No_inputs=3, No_outputs=3, Total_gates=3,Output_string_length=3, Bit_combination=8;
    int OUTPUT_pins[(No_inputs*Total_gates)] = {22, 23, 44, 24, 25, 26, 40, 41, 42};   // Output Pin array 
    int INPUT_pins[No_outputs] = {43, 27, 39};                    // Input Pin array
    String INPUT_PATTERNS_TO_OUTPUT_pins[Bit_combination] = {"000","001","010","011","100","101","110","111"};
    String OUTPUT_PATTERNS_FROM_INPUT_pins[Bit_combination] = {"000","000","000","000","000","000","000","111"};
    String ORIGINAL_gate_pin[Total_gates]={"1,2,13-12","3,4,5-6","9,10,11-8"};
    String OUTPUT_PATTERNS_gets[Bit_combination]={}, out_pat="";
    bool OUTPUT_match[Total_gates]={};                     // Input Pin array

    Set_PIN_modes(OUTPUT_pins,INPUT_pins,GND,VCC,No_inputs, No_outputs, Total_gates);

    out_pat = Bit_3_input(OUTPUT_pins, INPUT_pins,No_inputs, No_outputs, Total_gates, Bit_combination, INPUT_PATTERNS_TO_OUTPUT_pins);
    
    for(int i = 0 ;i< Bit_combination ;i++){
       OUTPUT_PATTERNS_gets[i] = String_Splitter(out_pat,'-',i);
    }
    IC_Output_Matching(OUTPUT_PATTERNS_FROM_INPUT_pins,Output_string_length,Total_gates,Bit_combination, OUTPUT_PATTERNS_gets, IC_name,No_inputs, OUTPUT_pins , Selftest, index,ORIGINAL_gate_pin);

}

//===== 7413 ==========================
void TEST_7413(String IC_name, bool Selftest, int index){
    // 14  4 2 7413  14  7 1,2,4,5,9,10,12,13  6,8    4-14-7-1,2,4,5,9,10,12,13-6,8  0000,11-0001,11-0010,11-0011,11-0010,11-0011,11-0110,11-0111,11-1000,11-1001,11-1010,11-1011,11-1010,11-1011,11-1110,11-1111,11 Dual 4-input NAND gate Schmitt trigger   randomly check 10 condition  
    
    int GND=28, VCC=45, No_inputs=4, No_outputs=2, Total_gates=2,Output_string_length=2, Bit_combination=16;
    int OUTPUT_pins[(No_inputs*Total_gates)] = {22, 23, 25, 26, 38, 39, 41, 42 };   // Output Pin array 
    int INPUT_pins[No_outputs] = {27, 29};                    // Input Pin array
    String INPUT_PATTERNS_TO_OUTPUT_pins[Bit_combination] = {"0000","0001","0010","0011","0100","0101","0110","0111","1000","1001","1010","1011","1100","1101","1110","1111"};
    String OUTPUT_PATTERNS_FROM_INPUT_pins[Bit_combination] = {"11","11","11","11","11","11","11","11","11","11","11","11","11","11","11","00"};
    String ORIGINAL_gate_pin[Total_gates]={"1,2,4,5-6","9,10,12,13-8"};
    String OUTPUT_PATTERNS_gets[Bit_combination]={}, out_pat="";
    bool OUTPUT_match[Total_gates]={};                     // Input Pin array

    Set_PIN_modes(OUTPUT_pins,INPUT_pins,GND,VCC,No_inputs, No_outputs, Total_gates);

    out_pat = Bit_4_input(OUTPUT_pins, INPUT_pins,No_inputs, No_outputs, Total_gates, Bit_combination, INPUT_PATTERNS_TO_OUTPUT_pins);
    
    for(int i = 0 ;i< Bit_combination ;i++){
       OUTPUT_PATTERNS_gets[i] = String_Splitter(out_pat,'-',i);
    }
    IC_Output_Matching(OUTPUT_PATTERNS_FROM_INPUT_pins,Output_string_length,Total_gates,Bit_combination,OUTPUT_PATTERNS_gets,IC_name,No_inputs,OUTPUT_pins,Selftest,index,ORIGINAL_gate_pin);

}

//====== 7414 =========================
void TEST_7414(String IC_name, bool Selftest, int index){
    // 14 1 6 7414  14  7 1,3,5,9,11,13 2,4,6,8,10,12 1-14-7-1,3,5,9,11,13-2,4,6,8,10,12  1,000000-0,111111 Hex inverter Schmitt inverter   01;10 

    TEST_7404(IC_name, Selftest, index);
}

//====== 7416 =========================
void TEST_7416(String IC_name, bool Selftest, int index){
    // 14 1 6 7416  14  7 1,3,5,9,11,13 2,4,6,8,10,12 1-14-7-1,3,5,9,11,13-2,4,6,8,10,12  1,000000-0,111111 Hex inverter Schmitt inverter   01;10 

    TEST_7404(IC_name, Selftest, index);
}

//====== 7417 =========================
void TEST_7417(String IC_name ,bool Selftest, int index){
   //14 1 6 7417  14  7 1,3,5,9,11,13 2,4,6,8,10,12 1-14-7-1,3,5,9,11,13-2,4,6,8,10,12  1,000000-0,111111 Hex inverter Schmitt inverter   01;10 

    TEST_7404(IC_name, Selftest, index);
}

//====== 7420 =========================
void TEST_7420(String IC_name ,bool Selftest, int index){
    // 14 4 2 7420  14  7 1,2,4,5,9,10,12,13  6,8 4-14-7-1,2,4,5,9,10,12,13-6,8 0000,11-0001,11-0010,11-0011,11-0010,11-0011,11-0110,11-0111,11-1000,11-1001,11-1010,11-1011,11-1010,11-1011,11-1110,11-1111,00 Dual 4-input NAND gate Schmitt trigger   randomly check 10 condition  
    TEST_7413(IC_name, Selftest, index);
}

//====== 7421 =========================
void TEST_7421(String IC_name ,bool Selftest, int index){
    // 14 4 2 7421  14  7 1,2,4,5,9,10,12,13  6,8 4-14-7-1,2,4,5,9,10,12,13-6,8 0000,00-0001,00-0010,00-0011,00-0010,00-0011,00-0110,00-0111,00-1000,00-1001,00-1010,00-1011,00-1010,00-1011,00-1110,00-1111,11 Dual 4-input AND gate  randomly check 10 condition  

    int GND=28, VCC=45, No_inputs=4, No_outputs=2, Total_gates=2,Output_string_length=2, Bit_combination=16;
    int OUTPUT_pins[(No_inputs*Total_gates)] = {22, 23, 25, 26, 38, 39, 41, 42 };   // Output Pin array 
    int INPUT_pins[No_outputs] = {27, 29};                    // Input Pin array
    String INPUT_PATTERNS_TO_OUTPUT_pins[Bit_combination] = {"0000","0001","0010","0011","0100","0101","0110","0111","1000","1001","1010","1011","1100","1101","1110","1111"};
    String OUTPUT_PATTERNS_FROM_INPUT_pins[Bit_combination] = {"00","00","00","00","00","00","00","00","00","00","00","00","00","00","00","11",};
    String ORIGINAL_gate_pin[Total_gates]={"1,2,4,5-6","9,10,12,13-8"};
    String OUTPUT_PATTERNS_gets[Bit_combination]={}, out_pat="";
    bool OUTPUT_match[Total_gates]={};                     // Input Pin array

    Set_PIN_modes(OUTPUT_pins,INPUT_pins,GND,VCC,No_inputs, No_outputs, Total_gates);

    out_pat = Bit_4_input(OUTPUT_pins, INPUT_pins,No_inputs, No_outputs, Total_gates, Bit_combination, INPUT_PATTERNS_TO_OUTPUT_pins);
    
    for(int i = 0 ;i< Bit_combination ;i++){
       OUTPUT_PATTERNS_gets[i] = String_Splitter(out_pat,'-',i);
    }

    IC_Output_Matching(OUTPUT_PATTERNS_FROM_INPUT_pins,Output_string_length,Total_gates,Bit_combination,OUTPUT_PATTERNS_gets,IC_name,No_inputs,OUTPUT_pins,Selftest, index,ORIGINAL_gate_pin);

}

//====== 7425 =========================
void TEST_7425(String IC_name ,bool Selftest, int index){
   // 14  4 2 7425  14  7 1,2,4,5,9,10,12,13  6,8 4-14-7-1,2,4,5,9,10,12,13-6,8 0000,00-0001,00-0010,00-0011,00-0010,00-0011,00-0110,00-0111,00-1000,00-1001,00-1010,00-1011,00-1010,00-1011,00-1110,00-1111,11 Dual 4-input AND gate  randomly check 10 condition  

    TEST_7421(IC_name, Selftest, index);
}

//====== 7427 =========================
void TEST_7427(String IC_name ,bool Selftest, int index){
//    14  3 3 7427  14  7 1,2,13,3,4,5,9,10,11  12,6,8  3-14-7-1,2,13,3,4,5,9,10,11-12,6,8  000,111-001,000-010,000-011,000-100,000-101,000-110,000-111,000 Triple 3-input NOR gate 

    int GND=28, VCC=45, No_inputs=3, No_outputs=3, Total_gates=3, Output_string_length=3, Bit_combination=8;
    int OUTPUT_pins[(No_inputs*Total_gates)] = {22, 23, 44, 24, 25, 26, 40, 41, 42};   // Output Pin array 
    int INPUT_pins[No_outputs] = {43, 27, 39};                    // Input Pin array
    String INPUT_PATTERNS_TO_OUTPUT_pins[Bit_combination] = {"000","001","010","011","100","101","110","111"};
    String OUTPUT_PATTERNS_FROM_INPUT_pins[Bit_combination] = {"111","000","000","000","000","000","000","000"};
    String ORIGINAL_gate_pin[Total_gates]={"1,2,13-12","3,4,5-6","9,10,11-8"};
    String OUTPUT_PATTERNS_gets[Bit_combination]={}, out_pat="";
    bool OUTPUT_match[Total_gates]={};           //IT depens on total no of gates 

    Set_PIN_modes(OUTPUT_pins,INPUT_pins,GND,VCC,No_inputs, No_outputs, Total_gates);

    out_pat = Bit_3_input(OUTPUT_pins, INPUT_pins,No_inputs, No_outputs, Total_gates, Bit_combination, INPUT_PATTERNS_TO_OUTPUT_pins);
    
    for(int i = 0 ;i< Bit_combination ;i++){
       OUTPUT_PATTERNS_gets[i] = String_Splitter(out_pat,'-',i);
    }
    IC_Output_Matching(OUTPUT_PATTERNS_FROM_INPUT_pins,Output_string_length,Total_gates,Bit_combination, OUTPUT_PATTERNS_gets, IC_name,No_inputs, OUTPUT_pins , Selftest, index,ORIGINAL_gate_pin);

}

//====== 7428 =========================
void TEST_7428(String IC_name ,bool Selftest, int index){
    // 14 2 4 7428  14  7 2,3,5,6,8,9,11,12 1,4,10,13 2-14-7-2,3,5,6,8,9,11,12-1,4,10,13  00,1111-01,0000-10,0000-11,0000 Quad 2-input NOR gate     

    TEST_7402(IC_name, Selftest, index);
}


//===== 7430 ==========================
void TEST_7430(String IC_name ,bool Selftest, int index){
    // 14 8 1 7430  14  7 1,2,3,4,5,6,11,12 8 8-14-7-1,2,3,4,5,6,11,12-8  00000000,1-00000011,1-00001100,1-00001101,1-00001111,1-10010010,1-10110100,1-11100101,1-11101001,1-11111111,0 8-input NAND gate    randomly check 10 condition  

    // Here we randomly check 10 condition  
    int GND=28, VCC=45, No_inputs=8, No_outputs=1, Total_gates=1,Output_string_length=1, Bit_combination=10;
    int OUTPUT_pins[(No_inputs*Total_gates)] = {22, 23, 25, 26, 38, 39, 41, 42 };   // Output Pin array 
    int INPUT_pins[No_outputs] = {29};                    // Input Pin array
    String INPUT_PATTERNS_TO_OUTPUT_pins[Bit_combination] = {"00000000","00000011","00001100","00001101","00001111","10010010","10110100","11100101","11101001","11111111"};
    String OUTPUT_PATTERNS_FROM_INPUT_pins[Bit_combination] = {"1","1","1","1","1","1","1","1","1","0"};
    String ORIGINAL_gate_pin[Total_gates]={"1,2,3,4,5,6,11,12-8"};
    String OUTPUT_PATTERNS_gets[Bit_combination]={}, out_pat="";
    bool OUTPUT_match[Total_gates]={};                     // Input Pin array


    Set_PIN_modes(OUTPUT_pins,INPUT_pins,GND,VCC,No_inputs, No_outputs, Total_gates);

    out_pat = Bit_4_input(OUTPUT_pins, INPUT_pins,No_inputs, No_outputs, Total_gates, Bit_combination, INPUT_PATTERNS_TO_OUTPUT_pins);
    
    for(int i = 0 ;i< Bit_combination ;i++){
       OUTPUT_PATTERNS_gets[i] = String_Splitter(out_pat,'-',i);
    }
    IC_Output_Matching(OUTPUT_PATTERNS_FROM_INPUT_pins,Output_string_length,Total_gates,Bit_combination, OUTPUT_PATTERNS_gets, IC_name,No_inputs, OUTPUT_pins , Selftest, index,ORIGINAL_gate_pin);

}


//==== 7432 ===========================
void TEST_7432(String IC_name ,bool Selftest, int index){
    // 14 2 4 7432  14  7 1,2,4,5,9,10,12,13  3,6,8,11  2-14-7-1,2,4,5,9,10,12,13-3,6,8,11  00,0000-01,1111-10,1111-11,1111 Quad 2-input OR gate (o.c)    

    int GND=28, VCC=45, No_inputs=2, No_outputs=4, Total_gates=4,Output_string_length=4,Bit_combination=4;
    int OUTPUT_pins[(No_inputs*Total_gates)] = {22, 23, 25, 26, 40, 41, 43, 44};   // Output Pin array 
    int INPUT_pins[No_outputs] = {24, 27, 39, 42};                    // Input Pin array
    int INPUT_PATTERNS_TO_OUTPUT_pins[Bit_combination] = {00,01,10,11};
    String OUTPUT_PATTERNS_FROM_INPUT_pins[Bit_combination] = {"0000","1111","1111","1111"};
    String ORIGINAL_gate_pin[Total_gates]={"1,2-3","4,5-6","9,10-8","12,13-11"};
    String OUTPUT_PATTERNS_gets[Bit_combination]={}, out_pat="";
    bool OUTPUT_match[Total_gates]={};
    
    Set_PIN_modes(OUTPUT_pins,INPUT_pins,GND,VCC,No_inputs, No_outputs, Total_gates);


    out_pat = Bit_2_input(OUTPUT_pins, INPUT_pins,No_inputs, No_outputs, Total_gates, Bit_combination, INPUT_PATTERNS_TO_OUTPUT_pins);
    
    for(int i = 0 ;i< Total_gates ;i++){
       OUTPUT_PATTERNS_gets[i] = String_Splitter(out_pat,'-',i);
    }

    IC_Output_Matching(OUTPUT_PATTERNS_FROM_INPUT_pins,Output_string_length,Total_gates,Bit_combination,OUTPUT_PATTERNS_gets,IC_name,No_inputs,OUTPUT_pins,Selftest,index,ORIGINAL_gate_pin);

}


//==== 7437 ===========================
void TEST_7437(String IC_name ,bool Selftest, int index){
    // 14 2 4 7437  14  7 1,2,4,5,9,10,12,13  3,6,8,11  2-14-7-1,2,4,5,9,10,12,13-3,6,8,11  00,1111-01,1111-10,1111-11,0000 Quad 2-input NAND gate    
    
    TEST_7400(IC_name, Selftest, index);

}

//==== 7438 ===========================
void TEST_7438(String IC_name ,bool Selftest, int index){
    // 14 2 4 7438  14  7 1,2,4,5,9,10,12,13  3,6,8,11  2-14-7-1,2,4,5,9,10,12,13-3,6,8,11  00,1111-01,1111-10,1111-11,0000 Quad 2-input NAND gate      

    TEST_7400(IC_name, Selftest, index);

}

//==== 7440 ===========================
void TEST_7440(String IC_name ,bool Selftest, int index){
    // 14 4 2 7440  14  7 1,2,4,5,9,10,12,13  6,8         4-14-7-1,2,4,5,9,10,12,13-6,8     0000,11-0001,11-0010,11-0011,11-0010,11-0011,11-0110,11-0111,11-1000,11-1001,11-1010,11-1011,11-1010,11-1011,11-1110,11-1111,00 Dual 4-input NAND gate   randomly check 10 condition  

    TEST_7413(IC_name, Selftest, index);
}



String Set_input_7442(int OUTPUT_pins[], int INPUT_pins[], int IN,int OUT,int TotG, int combination, String IN_pat[]){
    //IN=> No_inputs, OUT=>No_outputs, TotG=> Total_gates, combination=> Bit_combination , IN_pat=>Input_Pattern
    String OUTPUT_PATTERNS_gets[combination]={},Output_patterns="" , sk="OUTPUT----> ", sj="temp1----> ",sl="bit1----> ", r="pat----> " ,sp="  --->  ";
    int temp1 , bit1,k;

    for( int i=0;i< combination ;i++){
        temp1 = IN_pat[i].toInt();
        bit1 = temp1%10;
        temp1 = temp1/10;
        pinMode(OUTPUT_pins[3], OUTPUT);
        digitalWrite(OUTPUT_pins[3],bit1);
        bit1 = temp1%10;
        temp1 = temp1/10;
        pinMode(OUTPUT_pins[2], OUTPUT);
        digitalWrite(OUTPUT_pins[2],bit1);
        bit1 = temp1%10;
        temp1 = temp1/10;
        pinMode(OUTPUT_pins[1], OUTPUT);
        digitalWrite(OUTPUT_pins[1],bit1);
        bit1 = temp1%10;
        temp1 = temp1/10;
        pinMode(OUTPUT_pins[0], OUTPUT);
        digitalWrite(OUTPUT_pins[0],bit1);
        for(int l=0 ; l < OUT; l++) {   
            pinMode(INPUT_pins[l], INPUT);                           // READING the value 
            Output_patterns +=  String( digitalRead(INPUT_pins[l]));
    
        }
        OUTPUT_PATTERNS_gets[i] = Output_patterns;
        if(i == combination-1)
            Output_patterns+="";
        else Output_patterns+="-";
    }

    return Output_patterns;

}


//===== 7442 ==========================
void TEST_7442(String IC_name ,bool Selftest, int index){
    // 16 4 10  7442  16  8 15,14,13,12     1,2,3,4,5,6,7,9,10,11     4 -16-8-15,14,13,12-1,2,3,4,5,6,7,9,10,11     0000-1000000000,0001-0100000000,0010-0010000000,0011-0001000000,0100-0000100000,0101-0000010000,0110-0000001000,0111-0000000100,1000-0000000010,1001-0000000001 BCD to decimal decoder    

    // Here we randomly check 10 condition  
    int GND=29, VCC=45, No_inputs=4, No_outputs=10, Total_gates=1,Output_string_length=10, Bit_combination=10;
    int OUTPUT_pins[(No_inputs*Total_gates)] = {44, 43, 42, 41};   // Output Pin array 
    // int OUTPUT_pins[(No_inputs*Total_gates)] = {41, 42, 43, 44}; 
    int INPUT_pins[No_outputs] = {22, 23, 24, 25, 26, 27, 28, 38, 39, 40} ;                   // Input Pin array
    String INPUT_PATTERNS_TO_OUTPUT_pins[Bit_combination] =   {"0000","0001","0010","0011","0100","0101","0110","0111","1000","1001"};
    String OUTPUT_PATTERNS_FROM_INPUT_pins[Bit_combination] = {"0111111111","1011111111","1101111111","1110111111","1111011111","1111101111","1111110111","1111111011","1111111101","1111111110"};
    String ORIGINAL_gate_pin[Total_gates]={"15,14,13,12-1,2,3,4,5,6,7,9,10,11"};
    String OUTPUT_PATTERNS_gets[Bit_combination]={}, out_pat="";
    bool OUTPUT_match[Total_gates]={};                     // Input Pin array


    Set_PIN_modes(OUTPUT_pins,INPUT_pins,GND,VCC,No_inputs, No_outputs, Total_gates);

    out_pat = Set_input_7442(OUTPUT_pins, INPUT_pins,No_inputs, No_outputs, Total_gates, Bit_combination, INPUT_PATTERNS_TO_OUTPUT_pins);
    
    for(int i = 0 ;i< Bit_combination ;i++){
       OUTPUT_PATTERNS_gets[i] = String_Splitter(out_pat,'-',i);
    } 

    IC_Output_Matching(OUTPUT_PATTERNS_FROM_INPUT_pins,Output_string_length,Total_gates,Bit_combination, OUTPUT_PATTERNS_gets, IC_name,No_inputs, OUTPUT_pins , Selftest, index,ORIGINAL_gate_pin);

}


//==== 7445 ===========================
void TEST_7445(String IC_name ,bool Selftest, int index){
    // 16 4 10  7445  16  8 15,14,13,12   1,2,3,4,5,6,7,9,10,11 4 -16-8-15,14,13,12-1,2,3,4,5,6,7,9,10,11 0000-1000000000,0001-0100000000,0010-0010000000,0011-0001000000,0100-0000100000,0101-0000010000,0110-0000001000,0111-0000000100,1000-0000000010,1001-0000000001 BCD to decimal decoder driver   

    TEST_7442(IC_name, Selftest, index);
}



//===== 7446 ==========================
void TEST_7446(String IC_name ,bool Selftest, int index){
    // 16 4 10  7446  16  8 15,14,13,12   1,2,3,4,5,6,7,9,10,11     4 -16-8-15,14,13,12-1,2,3,4,5,6,7,9,10,11 0000-0000001,0001-1001111,0010-0010010,0011-0000110,0100-1001100,0101-0100100,0110-1100000,0111-0000000,1000-0001100  BCD to7 seg decoder driver (o.c.)   

    // Serial2.println("Testing 7446 .....");
    // Here we randomly check 10 condition  
    int GND=29, VCC=45, No_inputs=4, No_outputs=10, Total_gates=1,Output_string_length=7, Bit_combination=9;
    int OUTPUT_pins[(No_inputs*Total_gates)] = {44, 43, 42, 41};   // Output Pin array 
    int INPUT_pins[No_outputs] = {22, 23, 24, 25, 26, 27, 28, 38, 39, 40};                    // Input Pin array
    String INPUT_PATTERNS_TO_OUTPUT_pins[Bit_combination] = {"0000","0001","0010","0011","0100","0101","0110","0111","1000"};
    String OUTPUT_PATTERNS_FROM_INPUT_pins[Bit_combination] = {"0000001","1001111","0010010","0000110","1001100","0100100","1100000","0000000","0001100"};
    String ORIGINAL_gate_pin[Total_gates]={"15,14,13,12-1,2,3,4,5,6,7,9,10,11"};
    String OUTPUT_PATTERNS_gets[Bit_combination]={}, out_pat="";
    bool OUTPUT_match[Total_gates]={};                     // Input Pin array

    Set_PIN_modes(OUTPUT_pins,INPUT_pins,GND,VCC,No_inputs, No_outputs, Total_gates);

    out_pat = Bit_4_input(OUTPUT_pins, INPUT_pins,No_inputs, No_outputs, Total_gates, Bit_combination, INPUT_PATTERNS_TO_OUTPUT_pins);
    
    for(int i = 0 ;i< Bit_combination ;i++){
       OUTPUT_PATTERNS_gets[i] = String_Splitter(out_pat,'-',i);
    }

    IC_Output_Matching(OUTPUT_PATTERNS_FROM_INPUT_pins,Output_string_length,Total_gates,Bit_combination, OUTPUT_PATTERNS_gets, IC_name,No_inputs, OUTPUT_pins , Selftest, index,ORIGINAL_gate_pin);

}



//===== 7447 ==========================
void TEST_7447(String IC_name ,bool Selftest, int index){
    // 16  4 10  7447  16  8 15,14,13,12     1,2,3,4,5,6,7,8,9,10,11 4 -16-8-15,14,13,12-1,2,3,4,5,6,7,8,9,10,11 0000-0000001,0001-1001111,0010-0010010,0011-0000110,0100-1001100,0101-0100100,0110-1100000,0111-0000000,1000-0001100  BCD to7 seg decoder driver                

    TEST_7446(IC_name ,Selftest, index);

}


//===== 7483 ==========================
void TEST_7483(String IC_name ,bool Selftest, int index){
    // 16 9 5 7483  5 12  1,3,4,7,8,10,11,13,16 2,6,9,15  9-5-12-1,3,4,7,8,10,11,13,16-2,6,9,15 000000000-00000,0000100001-00100,000100010-01000,000110011-01100,001000100-10000-001010101-10100,001100110-11000,001110111-11100,010001000-00001,010011001-00101,11011101-10101,011101110-11001011111111-11101,111111111-11111  4 bit binary full adder               

    // Here we randomly check 10 condition  
    int GND=41, VCC=26, No_inputs = 9, No_outputs = 5 , Total_gates=1,Output_string_length=7, Bit_combination=9;
    int OUTPUT_pins[(No_inputs*Total_gates)] = {22, 24, 25, 28, 29, 39, 40, 42, 45};   // Output Pin array 
    int INPUT_pins[No_outputs] = {23, 27, 38, 44};                    // Input Pin array
    String INPUT_PATTERNS_TO_OUTPUT_pins[Bit_combination] = {"000000000","0000100001","000100010","000110011","001000100","001010101","001100110","001110111","010001000","010011001","11011101","011101110","1100101111","111111111"};
    String OUTPUT_PATTERNS_FROM_INPUT_pins[Bit_combination] = {"0000001","1001111","0010010","0000110","1001100","0100100","1100000","0000000","0001100"};
    String ORIGINAL_gate_pin[Total_gates]={"1,3,4,7,8,10,11,13,16-2,6,9,13"};
    String OUTPUT_PATTERNS_gets[Bit_combination]={}, out_pat="";
    bool OUTPUT_match[Total_gates]={};                     // Input Pin array

    Set_PIN_modes(OUTPUT_pins,INPUT_pins,GND,VCC,No_inputs, No_outputs, Total_gates);

    out_pat = Bit_4_input(OUTPUT_pins, INPUT_pins,No_inputs, No_outputs, Total_gates, Bit_combination, INPUT_PATTERNS_TO_OUTPUT_pins);
    
    for(int i = 0 ;i< Bit_combination ;i++){
       OUTPUT_PATTERNS_gets[i] = String_Splitter(out_pat,'-',i);
    }     
    IC_Output_Matching(OUTPUT_PATTERNS_FROM_INPUT_pins,Output_string_length,Total_gates,Bit_combination, OUTPUT_PATTERNS_gets, IC_name,No_inputs, OUTPUT_pins , Selftest, index,ORIGINAL_gate_pin);


}



//==== 7472 ===========================
void TEST_7472(String IC_name ,bool Selftest, int index){
    // 14  9 2 7472  14  7 C2,3,4,5,9,10,11,c12,P13  8,6 9-14-7-C2,3,4,5,9,10,11,c12,P13-8,6 0111000c1-01,1000111c0-10,1000000c1-10,1000100c1-10,1000110c1-10,1000111c1-01,1000000c1-01,1100000c1-01,1110000c1-01,1111000c1-10,1111111c1-01,1111111c1-10,1011011c1-10  AND gate JK master/slave flip-flop    

    int GND=28, VCC=45, No_inputs=9, No_outputs=2, Total_gates=1,Output_string_length=4,Bit_combination=8;
    int OUTPUT_pins[(No_inputs*Total_gates)] = {22, 23, 25, 26, 40, 41, 43, 44};   // Output Pin array 
    int INPUT_pins[No_outputs] = {24, 27, 39, 42};                    // Input Pin array
    int INPUT_PATTERNS_TO_OUTPUT_pins[Bit_combination] = {"000","001","010","011","100","101","110","111"};
    String OUTPUT_PATTERNS_FROM_INPUT_pins[Bit_combination] = {"01","01","10","10","01","01","10","10"};
    String ORIGINAL_gate_pin[Total_gates]={"1,2,4,5,11,12,13,14-3,6,10,13"};
    String OUTPUT_PATTERNS_gets[Bit_combination]={}, out_pat="";
    bool OUTPUT_match[Total_gates]={};
    
    Set_PIN_modes(OUTPUT_pins,INPUT_pins,GND,VCC,No_inputs, No_outputs, Total_gates);

    out_pat = Bit_2_input(OUTPUT_pins, INPUT_pins,No_inputs, No_outputs, Total_gates, Bit_combination, INPUT_PATTERNS_TO_OUTPUT_pins);
    
    for(int i = 0 ;i< Total_gates ;i++){
       OUTPUT_PATTERNS_gets[i] = String_Splitter(out_pat,'-',i);
    }
    
    IC_Output_Matching(OUTPUT_PATTERNS_FROM_INPUT_pins,Output_string_length,Total_gates,Bit_combination, OUTPUT_PATTERNS_gets, IC_name,No_inputs, OUTPUT_pins , Selftest, index,ORIGINAL_gate_pin);
}



/*
void FlipFlop_input_and_test(int OUTPUT_pins[], int INPUT_pins[],int CLOCK[], int CLEAR[], int clk, int clr, int IN, int OUT, int TotG, int combination, String IN_pat[],String OUT_pat[],String IC_name){
    //IN=> No_inputs, OUT=>No_outputs, TotG=> Total_gates, combination=> Bit_combination , IN_pat=>Input_Pattern
    String OUTPUT_PATTERNS_gets[combination]={},Output_patterns="" , sk="OUTPUT----> ", sj="temp1----> ",sl="bit1----> ", r="pat----> " ,sp="  --->  ";
    int i=0, j=0, lim=IN* TotG, increase= OUT/TotG;
    int in1,in2,out1,out2,temp1,temp2,Previ_q1[TotG],Previ_q2[TotG],Next_q1[TotG],Next_q2[TotG];
    int input, output,bit1,bit2;
    int k=0,l=0; 
    bool Gate_match[TotG] = {}; 

    for( int i=0;i< combination ;i++){
            temp1 = IN_pat[i].toInt();
            // Serial2.println(sj + temp1);
            out1 = INPUT_pins[j];     // q1
            out2 = INPUT_pins[j+1];   // q1'

            for(j=0;j< IN;j++){
                bit1 = temp1%10;
                // Serial2.println(sl + bit1);
                temp1 = temp1/10;
                // Serial2.println("j==0");
                if(j == 0){                // LSB === K
                    // Serial2.println("j==0");
                    Previ_q1[j] = digitalRead(OUTPUT_pins[i]);
                    Previ_q2[j] = digitalRead(OUTPUT_pins[i+1]);
                    for(int k=1; k <= (IN*OUT); k=k+2){
                        digitalWrite(OUTPUT_pins[k],bit1);
                        // Serial2.println(OUTPUT_pins[k]);
                    }
                    Next_q1[j]= digitalRead(out1);
                    Next_q2[j] = digitalRead(out2);
                }
                else if(j==1) {            ///MSB === J
                    // Serial2.println("j==1");
                    Previ_q1[j] = digitalRead(OUTPUT_pins[i]);
                    Previ_q2[j] = digitalRead(OUTPUT_pins[i+1]);
                    for(k=0; k < (IN*OUT);k+=2){
                        digitalWrite(OUTPUT_pins[k],bit1);
                        // Serial2.println(OUTPUT_pins[k]);
                    }
                    Next_q1[j]= digitalRead(out1);
                    Next_q2[j] = digitalRead(out2);
                }

                if(i=0){
                    for( int a=0;a<TotG ;a++){
                        if(Previ_q1[a] == Next_q1[a] && Previ_q2[a] == Next_q2[a] )
                            Gate_match[a] = true;
                        else    Gate_match[a]=false;
                    }
                }
                if(i=1){
                    for( int a=0;a<TotG ;a++){
                        if(Next_q1[a] == 0 && Next_q2[a] == 1)
                            Gate_match[a] = true;
                        else    Gate_match[a]=false;
                    }
                }
                if(i=2){
                    for( int a=0;a<TotG ;a++){
                        if(Next_q1[a] == 1 && Next_q2[a] == 0)
                            Gate_match[a] = true;
                        else    Gate_match[a]=false;
                    }
                }
                
                if(i=3){
                    for( int a=0;a<TotG ;a++){
                        if(Previ_q2[a] == Next_q1[a] && Previ_q1[a] == Next_q2[a] )
                            Gate_match[a] = true;
                        else    Gate_match[a]=false;
                    }
                }
            }

    }
    display(Gate_match,  OUTPUT_pins, TotG, IN, IC_name);
 
    
}



//==== 7473 ===========================
void TEST_7473(String IC_name){
    // 14 9 2 7472  14  7 C2,3,4,5,9,10,11,c12,P13  8,6 9-14-7-C2,3,4,5,9,10,11,c12,P13-8,6 0111000c1-01,1000111c0-10,1000000c1-10,1000100c1-10,1000110c1-10,1000111c1-01,1000000c1-01,1100000c1-01,1110000c1-01,1111000c1-10,1111111c1-01,1111111c1-10,1011011c1-10  AND gate JK master/slave flip-flop    
//     14     7473  4 11              Dual JK flip-flop with clear    

// JK 1 


    int GND=42, VCC=25, No_inputs=2 , No_outputs=4,clr=2, clk=2, Total_gates=2, Output_string_length=2, Bit_combination=4;
    int OUTPUT_pins[(No_inputs*Total_gates)] = {45, 24, 28, 41};   // Output Pin array 
                                            //  j1   k1  j2  k2
    int INPUT_pins[No_outputs] = {43, 44 , 40, 39 };                    // Input Pin array
                                // q1 q1'  q2  q2'
                //  1    2
    int Clock[clk]={22, 26};
    int Clear[clr]={23, 27};
    String INPUT_PATTERNS_TO_OUTPUT_pins[Bit_combination] = {"00","01","10","11"};
    String OUTPUT_PATTERNS_FROM_INPUT_pins[Bit_combination] = {"pp","01","10","tt"};
    String NextState[Bit_combination]={}, out_pat="";
    bool OUTPUT_match[Total_gates]={};
    
    Set_PIN_modes(OUTPUT_pins,INPUT_pins,GND,VCC,No_inputs, No_outputs, Total_gates);

    FlipFlop_input_and_test(OUTPUT_pins,INPUT_pins,Clock,Clear,clk,clr,No_outputs, Total_gates, Bit_combination,INPUT_PATTERNS_TO_OUTPUT_pins,OUTPUT_PATTERNS_FROM_INPUT_pins,IC_name);

}

*/


//==== 7486 ===========================
void TEST_7486(String IC_name,bool Selftest,int index ){
    // 14 2 4 7486  14  7 1,2,4,5,9,10,12,13  3,6,8,11  2-14-7-1,2,4,5,9,10,12,13-3,6,8,11  00,0000-01,1111-10,1111-11,0000 Quad 2-input XOR gate   00011011;1110 

    int GND=28, VCC=45, No_inputs=2, No_outputs=4, Total_gates=4,Output_string_length=4,Bit_combination=4;
    int OUTPUT_pins[(No_inputs*Total_gates)] = {22, 23, 25, 26, 40, 41, 43, 44};   // Output Pin array 
    int INPUT_pins[No_outputs] = {24, 27, 39, 42};                    // Input Pin array
    int INPUT_PATTERNS_TO_OUTPUT_pins[Bit_combination] = {00,01,10,11};
    String OUTPUT_PATTERNS_FROM_INPUT_pins[Bit_combination] = {"0000","1111","1111","0000"};
    String ORIGINAL_gate_pin[Total_gates]={"1,2-3","4,5-6","9,10-8","12,13-11"};
    String OUTPUT_PATTERNS_gets[Bit_combination]={}, out_pat="";
    bool OUTPUT_match[Total_gates]={};
    
    Set_PIN_modes(OUTPUT_pins,INPUT_pins,GND,VCC,No_inputs, No_outputs, Total_gates);


    out_pat = Bit_2_input(OUTPUT_pins, INPUT_pins,No_inputs, No_outputs, Total_gates, Bit_combination, INPUT_PATTERNS_TO_OUTPUT_pins);
    
    for(int i = 0 ;i< Total_gates ;i++){
       OUTPUT_PATTERNS_gets[i] = String_Splitter(out_pat,'-',i);
    }
    
    IC_Output_Matching(OUTPUT_PATTERNS_FROM_INPUT_pins,Output_string_length,Total_gates,Bit_combination, OUTPUT_PATTERNS_gets, IC_name,No_inputs, OUTPUT_pins , Selftest, index ,ORIGINAL_gate_pin);

}

// 16 4 10  7446  16  8 15,14,13,12 1,2,3,4,5,6,7,8,9,10,11 4 -16-8-15,14,13,12-1,2,3,4,5,6,7,8,9,10,11 0000-0000001,0001-1001111,0010-0010010,0011-0000110,0100-1001100,0101-0100100,0110-1100000,0111-0000000,1000-0001100  BCD to7 seg decoder driver (o.c.)   
// 16 4 10  7447  16  8 15,14,13,12 1,2,3,4,5,6,7,8,9,10,11 4 -16-8-15,14,13,12-1,2,3,4,5,6,7,8,9,10,11 0000-0000001,0001-1001111,0010-0010010,0011-0000110,0100-1001100,0101-0100100,0110-1100000,0111-0000000,1000-0001100  BCD to7 seg decoder driver    




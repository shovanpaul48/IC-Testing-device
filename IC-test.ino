void setup() {
  Serial.begin(9600);
  Serial2.println("Testing 7442");
}




void  IC_Output_Matching(String Actual_Outputs[] ,int Actual_Output_string_length, int total_gates,int combination, String Outputs[] ,String IC_name ,int No_inputs, int OUTPUT_pins[], bool selftest, int index){


    String space= "     ", space2= "    temp    ", te1,te2;
    int temp1,temp2,bit1,bit2, len , p=0,q;
    bool  OUTPUT_match[total_gates]={};
    for(int i = 0 ;i < combination ;i++){
        Serial2.println("Hello");
        Serial2.println(Actual_Outputs[i] + space + Outputs[i]);
    }

    for(int i = 0 ;i < combination ;i++){
            len = Actual_Output_string_length - 1 ;
            if(Outputs[i] == Actual_Outputs[i] ){
                for(int n =0 ; n<= len ;n++){ 
                    if( i != 0  )  {
                        if(OUTPUT_match[n] ==  true)
                            OUTPUT_match[n]=true;
                        else if(OUTPUT_match[n] ==  false )
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
                Serial2.println(te1 + space2 + te2 );

                for(int m=0 ; m <= len ; m++){
                    q = m+1;
                    if ( te1.substring(p,q) == ( te2.substring(p,q))){
                        Serial2.println("matched ");
                        if ( OUTPUT_match[m] == false)
                            OUTPUT_match[m]=false;
                        else
                            OUTPUT_match[m]=true;
                    }
                    else{
                        Serial2.println("not matched ");
                        OUTPUT_match[m]=false;
                    }  
                    p+=1;
                }
            }

        Serial2.println("{");
        for(int a=0; a<= len ;a++){
            Serial2.print(OUTPUT_match[a] + space);
        }
        Serial2.print("}");
    }
    
    display(OUTPUT_match, OUTPUT_pins, total_gates, No_inputs, IC_name, selftest, index);
    // return  OUTPUT_match;
}


//------ this function Display the matching gate name and not working pin numbers 
void display(bool arr[] ,int Output_pin[] ,int total_gates,int No_inputs ,String IC_name ,bool selftest ,int index ){
    String s1 = "GATE " , s2=" MATCHED",  s3 = "GATE ",  s4=" NOT MATCHED", s5 = " Not working gate's pin numbers are : ";
    int k = (total_gates*No_inputs) - 1;
    Serial2.println("Inside DISPLAY ");
    int possiblity=0;
    Serial2.println("The IC is : " + IC_name);
    
    for(int j=total_gates-1 ; j>=0 , k>= 0;j-- , k-= No_inputs){
        if( arr[j] == true){
            Serial2.println(s1 + (j+1) + s2 );
            possiblity = 1 ;
        }


        else{
            Serial2.print(s3 + (j+1) + s4 );
            Serial2.print(s5);
            for( int l = k; l > k - No_inputs ; l-- ){
                Serial2.print(Output_pin[l]);
                if( l != k - No_inputs -1)
                    Serial2.print(" ,");
            }
            Serial2.println("");
        }
    }
//    if(possiblity !=1 && selftest== true){
//        Selftest_switch( index+1);
//    }
    if (possiblity == 1 && selftest== true){
        Serial2.print("IC matched with : ");
        Serial2.print(IC_name);
    }


//    start();
} 



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


String Set_input(int OUTPUT_pins[], int INPUT_pins[], int IN,int OUT,int TotG, int combination, String IN_pat[]){
    //IN=> No_inputs, OUT=>No_outputs, TotG=> Total_gates, combination=> Bit_combination , IN_pat=>Input_Pattern
    String OUTPUT_PATTERNS_gets[combination]={},Output_patterns="" , sk="OUTPUT----> ", sj="temp1----> ",sl="bit1----> ", r="pat----> " ,sp="  --->  ";
    int temp1 , bit1,k;
    for( int i=0;i< combination ;i++){
        temp1 = IN_pat[i].toInt();
        Serial2.println(r + IN_pat[i]);
        Serial2.println(sj + temp1);
        // for(int j=0;j< IN;j++){
            bit1 = temp1%10;
            Serial2.println(sl + bit1);
            temp1 = temp1/10;
            // if(j == 0){               // LSB
                Serial2.println("j==0, LSB");
                // for(int k=3; k <=IN; k=k+4){
                    digitalWrite(OUTPUT_pins[3],bit1);
                    Serial2.println(OUTPUT_pins[3]); 
                // }
            // }
            // else if(j==1) {
                bit1 = temp1%10;
                Serial2.println(sl + bit1);
                temp1 = temp1/10;
                Serial2.println("j==1");
                // for(k=2; k < (IN*OUT);k=k+4){
                    digitalWrite(OUTPUT_pins[2],bit1);
                    Serial2.println(OUTPUT_pins[2]); 
                // }
            // }
            // else if(j==2) {
            bit1 = temp1%10;
            Serial2.println(sl + bit1);
            temp1 = temp1/10;
                Serial2.println("j==2");
                // for(k=1; k< (IN*OUT);k=k+4){
                    digitalWrite(OUTPUT_pins[1],bit1);
                    Serial2.println(OUTPUT_pins[1]); 
                // }
            // }
            // else if(j==3) {           //MSB
            bit1 = temp1%10;
            Serial2.println(sl + bit1);
            temp1 = temp1/10;
                Serial2.println("j==3,MSB");
                // for(k=0; k< (IN*OUT);k=k+4){
                    digitalWrite(OUTPUT_pins[0],bit1);
                    Serial2.println(OUTPUT_pins[0]); 
                // }
            // }
        // }
        delay(1000);
        for(int l=0 ; l < OUT; l++) {                              // READING the value 
            Output_patterns +=  String( digitalRead(INPUT_pins[l]));
            Serial2.println(INPUT_pins[l] + sp +  digitalRead(INPUT_pins[l]));
        }
        OUTPUT_PATTERNS_gets[i] = Output_patterns;
        Serial2.println(sk + Output_patterns);
        // Output_patterns = "";
        if(i == combination-1)
            Output_patterns+="";
        else Output_patterns+="-";
    }
    // return OUTPUT_PATTERNS_gets;
    Serial2.println("IN BIT_3_INPUT");
    Serial2.println( Output_patterns);
    return Output_patterns;



}


//===== 7442 ==========================
void TEST_7442(String IC_name ,bool Selftest, int index){
    // 16 4 10  7442  16  8 15,14,13,12     1,2,3,4,5,6,7,9,10,11     4 -16-8-15,14,13,12-1,2,3,4,5,6,7,9,10,11     0000-1000000000,0001-0100000000,0010-0010000000,0011-0001000000,0100-0000100000,0101-0000010000,0110-0000001000,0111-0000000100,1000-0000000010,1001-0000000001 BCD to decimal decoder    

    // Here we randomly check 10 condition  
    int GND=29, VCC=45, No_inputs=4, No_outputs=10, Total_gates=1,Output_string_length=10, Bit_combination=10;
    int OUTPUT_pins[(No_inputs*Total_gates)] = {44, 43, 42, 41};   // Output Pin array 
    int INPUT_pins[No_outputs] = {22, 23, 24, 25, 26, 27, 28, 38, 39, 40} ;                   // Input Pin array
    String INPUT_PATTERNS_TO_OUTPUT_pins[Bit_combination] =   {"0000","0001","0010","0011","0100","0101","0110","0111","1000","1001"};
    String OUTPUT_PATTERNS_FROM_INPUT_pins[Bit_combination] = {"1000000000","0100000000","0010000000","0001000000","0000100000","0000010000","0000001000","0000000100","0000000010","0000000001"};
    String OUTPUT_PATTERNS_gets[Bit_combination]={}, out_pat="";
    bool OUTPUT_match[Total_gates]={};                     // Input Pin array


    Set_PIN_modes(OUTPUT_pins,INPUT_pins,GND,VCC,No_inputs, No_outputs, Total_gates);

    out_pat = Set_input(OUTPUT_pins, INPUT_pins,No_inputs, No_outputs, Total_gates, Bit_combination, INPUT_PATTERNS_TO_OUTPUT_pins);
    
    for(int i = 0 ;i< Bit_combination ;i++){
       OUTPUT_PATTERNS_gets[i] = String_Splitter(out_pat,'-',i);
    } 

    Serial2.println("Outputs we gets ");
    for(int i = 0 ;i< Bit_combination ;i++){
        Serial2.println(OUTPUT_PATTERNS_gets[i]);
    }
    
    String ss1="Actual Output   : ",ss2="Output we gets : " ,ss3= "        ";
    Serial2.println("Outputs we gets ");
    for(int i = 0 ;i< Bit_combination ;i++)
        Serial2.println(ss1 + OUTPUT_PATTERNS_FROM_INPUT_pins[i]+ ss3 + ss2 + OUTPUT_PATTERNS_gets[i]);
     
    IC_Output_Matching(OUTPUT_PATTERNS_FROM_INPUT_pins,Output_string_length,Total_gates,Bit_combination, OUTPUT_PATTERNS_gets, IC_name,No_inputs, OUTPUT_pins , Selftest, index);

}



void loop() {
  // put your main code here, to run repeatedly:
    String IC_name=" 7442 ( BCD to decimal decoder ) "; 
    Serial2.println("Testing 7442 .....");
    TEST_7442(IC_name,false,-1);
  
}


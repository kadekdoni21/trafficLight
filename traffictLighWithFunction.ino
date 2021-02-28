int merah = 21, kuning = 22, biru = 23;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(merah, OUTPUT);
  pinMode(kuning, OUTPUT);
  pinMode(biru, OUTPUT);
}

void trafficLight(int count){
  int milSec = 1000 * count; // ini hitungannya perdetik 

  clock_t start = clock();
  while(clock() < start + milSec);
}

void loop() {
  // put your main code here, to run repeatedly:
  int lMerah = 10;
  int lBiru = 5;
  for(int i = 1; i <= 19; i++){
    trafficLight(1);
    if(i <= 10){
      digitalWrite(merah, HIGH);
      digitalWrite(kuning, LOW);
      digitalWrite(biru, LOW);
      printf("MERAH => %d detik \n", lMerah);
      lMerah--;
    }
    if(i >10 && i <= 12){
      digitalWrite(merah, LOW);
      digitalWrite(kuning, HIGH);
      digitalWrite(biru, LOW);      
      Serial.println("KUNING");
    }
    if(i >12 && i<= 17){      
      digitalWrite(merah, LOW);
      digitalWrite(kuning, LOW);
      digitalWrite(biru, HIGH);
      printf("BIRU => %d detik \n", lBiru);
      lBiru--;   
    }
    if(i > 17 && i <= 19){      
      digitalWrite(merah, LOW);
      digitalWrite(kuning, HIGH);
      digitalWrite(biru, LOW);
      Serial.println("KUNING");
    }
    if(i == 19){
      break;
    }
    
  }
}

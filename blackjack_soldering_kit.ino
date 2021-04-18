//Blackjack Soldering Kit
//Version 1.1, December 2020
//Jim Heaney
//CC-BY-SA-NC 4.0

const int seg1 = 0;
const int seg2 = 1;
const int seg3 = 13;
const int seg4 = 2;
const int a = 3;
const int b = 4;
const int c = 5;
const int d = 6;
const int e = 7;
const int f = 8;
const int g = 9;
const int p1 = A5;
const int p2 = A2;
const int p3 = A0;
const int d1 = A1;
const int d2 = A4;
const int d3 = A3;
const int hit = 11;
const int stay = 10;

int player = 0;
int dealer = 0;

int dscore = 0;
int pscore = 0;

bool dealerturn = 0;
bool finish = 0;
bool start = 1;

int dim = 0;

int hitpress = 0;

long delaytime = 0;

void setup() {
  // put your setup code here, to run once:

  //Seed the RNG
  pinMode(p1, INPUT);
  randomSeed(analogRead(p1));

  //Set the LED pins as outputs
  pinMode(seg1, OUTPUT);
  pinMode(seg2, OUTPUT);
  pinMode(seg3, OUTPUT);
  pinMode(seg4, OUTPUT);
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(p1, OUTPUT);
  pinMode(p2, OUTPUT);
  pinMode(p3, OUTPUT);
  pinMode(d1, OUTPUT);
  pinMode(d2, OUTPUT);
  pinMode(d3, OUTPUT);

  //Set the buttons as inputs
  pinMode(hit, INPUT);
  pinMode(stay, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  //Screen update
  screen();

  //Start the game by dealing 2 cards to each the dealer and the player
  if (start == 1){
    player = card(random(1, 14)) + card(random(1, 14));
    dealer = card(random(1, 14)) + card(random(1, 14));
    start = 0;
  }
  
  //Check for hit press
  if ((digitalRead(hit) == 0) && (hitpress == 0)){
    hitpress = 1;
    player = player + card(random(1, 14));
  }
  if (digitalRead(hit) == 1){
    hitpress = 0;
  }

 //Check if player busts or stays
 if ((player > 21) || (digitalRead(stay) == 0)){
  dealerturn = 1;
 }

 //Dealer takes his turn now
  while(dealerturn == 1){
    screen();
    while(dealer <= 17){
      delaytime = millis() + 500;
      while(delaytime >= millis()){
        screen();
      }
      dealer = dealer + card(random(1, 14));
    }
    if (dealer > 17){
      finish = 1;
      dealerturn = 0;
    }
  }

 //Once the game is concluded, score a point to the winner, see if anyone won, and reset the counts.
  while (finish == 1){
    if ((player <= 21) && ((player > dealer) || (dealer > 21))){
      pscore = pscore + 1;
    }
    if ((dealer <= 21) && ((dealer > player) || (player > 21))){
      dscore = dscore + 1;
    }
    //Make sure that the scores match the board's current display
    screen();
    //Display the winner's score for a second
    delaytime = millis() + 1000;
    while(delaytime >= millis()){
      screen();
    }

    //Reset the hands
    player = 0;
    dealer = 0;
    
    //Check if anyone has won, and if so play their winning code;
    if (pscore == 3){
      pwin();
    }
    if (dscore == 3){
      dwin();
    }
    finish = 0;
    start = 1;
  }
}

void disp(int x){
  //display a 7-segment common-cathode display. Write "10" to clear. 

  if (x == 0){
    digitalWrite(a, HIGH);
    digitalWrite(b, HIGH);
    digitalWrite(c, HIGH);
    digitalWrite(d, HIGH);
    digitalWrite(e, HIGH);
    digitalWrite(f, HIGH);
  }
  if (x == 1){
    digitalWrite(b, HIGH);
    digitalWrite(c, HIGH);
  }
  if (x == 2){
    digitalWrite(a, HIGH);
    digitalWrite(b, HIGH);
    digitalWrite(g, HIGH);
    digitalWrite(e, HIGH);
    digitalWrite(d, HIGH);
  }
  if (x == 3){
    digitalWrite(a, HIGH);
    digitalWrite(b, HIGH);
    digitalWrite(g, HIGH);
    digitalWrite(c, HIGH);
    digitalWrite(d, HIGH);
  }
  if (x == 4){
    digitalWrite(f, HIGH);
    digitalWrite(b, HIGH);
    digitalWrite(g, HIGH);
    digitalWrite(c, HIGH);
  }
  if (x == 5){
    digitalWrite(a, HIGH);
    digitalWrite(f, HIGH);
    digitalWrite(g, HIGH);
    digitalWrite(c, HIGH);
    digitalWrite(d, HIGH);
  }
  if (x == 6){
    digitalWrite(a, HIGH);
    digitalWrite(f, HIGH);
    digitalWrite(g, HIGH);
    digitalWrite(e, HIGH);
    digitalWrite(c, HIGH);
    digitalWrite(d, HIGH);
  }
  if (x == 7){
    digitalWrite(a, HIGH);
    digitalWrite(b, HIGH);
    digitalWrite(c, HIGH);
  }
  if (x == 8){
    digitalWrite(a, HIGH);
    digitalWrite(b, HIGH);
    digitalWrite(c, HIGH);
    digitalWrite(d, HIGH);
    digitalWrite(e, HIGH);
    digitalWrite(f, HIGH);
    digitalWrite(g, HIGH);
  }
  if (x == 9){
    digitalWrite(a, HIGH);
    digitalWrite(b, HIGH);
    digitalWrite(c, HIGH);
    digitalWrite(d, HIGH);
    digitalWrite(f, HIGH);
    digitalWrite(g, HIGH);    
  }
  if (x == 10){
    digitalWrite(a, LOW);
    digitalWrite(b, LOW);
    digitalWrite(c, LOW);
    digitalWrite(d, LOW);
    digitalWrite(e, LOW);
    digitalWrite(f, LOW);
    digitalWrite(g, LOW);  
  }
}

int card(int x){
  //Returns a card's face value based on the input card number
  if (x <= 10){
    return x;
  }
  else{
    return 10;
  }
}

void pwin(){
  //called when the player wins
  disp(10);
  for(int i = 0; i < 5; i++){
    pscore = 0;
    delaytime = millis() + 250;
    while(delaytime >= millis()){
      screen();
    }
    pscore = 3;
    delaytime = millis() + 250;
    while(delaytime >= millis()){
      screen();
    }
  }
  while(true){
    screen();
  }
}

void dwin(){
  //called when the dealer wins
    disp(10);
  for(int i = 0; i < 5; i++){
    dscore = 0;
    delaytime = millis() + 250;
    while(delaytime >= millis()){
      screen();
    }
    dscore = 3;
    delaytime = millis() + 250;
    while(delaytime >= millis()){
      screen();
    }
  }
  while(true){
    screen();
  }
}

void screen(){
  //Write the current scores to the screens
  disp((dealer / 10) % 10);
  digitalWrite(seg1, LOW);
  digitalWrite(seg1, HIGH);
  disp(10);
  disp(dealer % 10);
  digitalWrite(seg2, LOW);
  digitalWrite(seg2, HIGH);
  disp(10);
  disp((player / 10) % 10);
  digitalWrite(seg3, LOW);
  digitalWrite(seg3, HIGH);
  disp(10);
  disp(player % 10);
  digitalWrite(seg4, LOW);
  digitalWrite(seg4, HIGH);
  disp(10);
  //Also write the score LEDs
  if (dim == 3){
    if (pscore > 0){
      digitalWrite(p1, HIGH);
    }
    if (pscore > 1){
      digitalWrite(p2, HIGH);
    }
    if (pscore > 2){
      digitalWrite(p3, HIGH);
    }
    if (dscore > 0){
      digitalWrite(d1, HIGH);
    }
    if (dscore > 1){
      digitalWrite(d2, HIGH);
    }
    if (dscore > 2){
      digitalWrite(d3, HIGH);
    }
    dim = 0;
  }
  if (dim < 3){
    digitalWrite(p1, LOW);
    digitalWrite(p2, LOW);
    digitalWrite(p3, LOW);
    digitalWrite(d1, LOW);
    digitalWrite(d2, LOW);
    digitalWrite(d3, LOW);
    dim = dim + 1;
  }
}

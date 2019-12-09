const int sampleWindow = 200; // Amostras de largura de 20Hz
unsigned int sample;
 
void setup()
{
   Serial.begin(9600);
}
 
 
void loop()
{
 
   static char count = 0;
   static double medidas = 0;
   unsigned long startMillis= millis();  // início da janela de amostras
   unsigned int peakToPeak = 0;   // nivel de pico a pico
 
   unsigned int signalMax = 0;
   unsigned int signalMin = 1024;
 
   // coleta de dados
   while (millis() - startMillis < sampleWindow)
   {
      sample = analogRead(36);
      if (sample < 1024)  // 
      {
         if (sample > signalMax)
         {
            signalMax = sample;  // pegando os maximos
         }
         else if (sample < signalMin)
         {
            signalMin = sample;  // pegando os minimos
         }
      }
   }
   peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude
   double volts = (peakToPeak * 3.3) / 1024;  // convertendo para volts
   double decibels = 64 + 20*log(volts/3.3);

   if(count < 40)
   {
      count = count + 1; 
      medidas = medidas + decibels;
   }
   else
   {
      count = 0;
      medidas = medidas/40;
      Serial.println(medidas); // printando intensidade do som
      medidas = 0;

   }
}
   

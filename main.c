
void Readings()
{
    unsigned long phas_a_v,phas_b_v,phas_c_v,phas_a_c,phas_b_c,phas_c_c,phas_a_pwr,phas_b_pwr,phas_c_pwr,phas_a_wh,phas_b_wh,phas_c_wh=0;
    int i;
    unsigned long VRMS[10], VA;
    
  while(1)
  
  {
      phas_a_v=read24bits(AVRMS);
      phas_b_v=read24bits(BVRMS);
      phas_c_v=read24bits(CVRMS);
      phas_a_c=read24bits(AIRMS);
      phas_b_c=read24bits(BIRMS);
      phas_c_c=read24bits(CIRMS);
      phas_a_wh=read16bits(AWATTHR);
      phas_b_wh=read16bits(BWATTHR);
      phas_c_wh=read16bits(CWATTHR);
   
                 for(i=0;i<=8;i++)
               {      
                  VRMS[i] = phas_a_v / VRMS_DIV;
               }
          
          phas_a_v = (VRMS[0] + VRMS[1] + VRMS[2] + VRMS[3] + VRMS[4] + VRMS[5] + VRMS[6] + VRMS[7]) / 8; 
          
                for(i=0;i<=8;i++)
               {      
                  VRMS[i] = phas_b_v / VRMS_DIV;
               }
          
          phas_b_v = (VRMS[0] + VRMS[1] + VRMS[2] + VRMS[3] + VRMS[4] + VRMS[5] + VRMS[6] + VRMS[7]) / 8; 
          
                for(i=0;i<=8;i++)
               {      
                  VRMS[i] = phas_c_v / VRMS_DIV;
               }
          
          phas_c_v = (VRMS[0] + VRMS[1] + VRMS[2] + VRMS[3] + VRMS[4] + VRMS[5] + VRMS[6] + VRMS[7]) / 8; 



void main(void)
{     
      init();     
         
//******************************WRITE CODE HERE********************************
         while(1)
            {
                                  
                  Readings();
           
            }         
      

}

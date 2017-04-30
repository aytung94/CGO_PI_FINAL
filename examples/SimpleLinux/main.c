//
//  main.c
//  DeepBeliefSDK
//
//  Created by Peter Warden on 4/28/14.
//  Copyright (c) 2014 Jetpac, Inc. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <libjpcnn.h>

#define NETWORK_FILE_NAME "ccv2012.ntwk" // "jetpac.ntwk"
#define PRINT 0
#define TEST 1
#define WATING 0

int comp (const void * elem1, const void * elem2)
{
    int e1 = *((float*)elem1);
    int e2 = *((float*)elem2);
    if(e1 > e2) return 1;
    if(e1 < e2) return -1;
    return 0;
}

volatile int dum = 0;
void waiting(void);

void waiting(){
	int i ;
	for (i = 0; i < 1000000000; i++){
		dum += 1;
	}
}

int main(int argc, char * argv[]) {
#if WAITING
  waiting();
#endif

  const char* imageFileName;
  void* imageHandle;
  void* networkHandle;

  float* predictions;
  int predictionsLength;
  char** predictionsLabels;
  int predictionsLabelsLength;
  int index;

  if (argc < 2) {
    imageFileName = "lena.png";
  } else {
    imageFileName = argv[1];
  }
  
#if TEST
  const char* category = argv[3];
#endif

  const char* networkFileName;
  if (argc < 3) {
    networkFileName = NETWORK_FILE_NAME;
  } else {
    networkFileName = argv[2];
  }

  networkHandle = jpcnn_create_network(networkFileName);
#if PRINT
  if (networkHandle == NULL) {
    fprintf(stderr, "DeepBeliefSDK: Couldn't load network file '%s'\n", networkFileName);
    return 1;
  }
#endif

  imageHandle = jpcnn_create_image_buffer_from_file(imageFileName);
#if PRINT
  if (imageHandle == NULL) {
    fprintf(stderr, "DeepBeliefSDK: Couldn't load image file '%s'\n", imageFileName);
    return 1;
  }
#endif

#if TEST
unsigned long start = clock(), diff;
#endif
  jpcnn_classify_image(networkHandle, imageHandle, 0, 0, &predictions, &predictionsLength, &predictionsLabels, &predictionsLabelsLength);
#if TEST
diff = clock() - start;
float msec = diff * 1000 / CLOCKS_PER_SEC;
#endif

  jpcnn_destroy_image_buffer(imageHandle);

#if PRINT
  for (index = 0; index < predictionsLength; index += 1) {
    float predictionValue;
    char* label = predictionsLabels[index];
    predictionValue = predictions[index];
    fprintf(stdout, "%d\t%f\t%s\n", index, predictionValue, label);
  }

  float pV = predictions[0];
  char* pL = 0;
  for(index = 1; index < predictionsLength; index++)
  {
    if(pV < predictions[index])
    {
        pV = predictions[index];
        pL = predictionsLabels[index];
    }
  }
  fprintf(stdout, "MAX: \t%f\t%s\n", pV, pL);
#endif 

#if TEST
  float pV = predictions[0];
  char* pL = 0;
  for(index = 1; index < predictionsLength; index++)
  {
    if(strcmp(predictionsLabels[index],category) == 0)
    {
        pV = predictions[index];
        pL = predictionsLabels[index];
    }
  }

  // hack image name
  char* file = argv[1];
  while(*file != 0)
  {
    file++;
  }
  file = file - 14;
    
  // output to csv file  
  FILE *output;
  output=fopen("deepbelief_predictions.csv", "a");      
  fprintf(output,"%s,%s,%f,%f\n", pL, file, pV, msec); 
  fclose(output);
  
#endif
//  qsort(predictions, sizeof(predictions)/sizeof(*predictions), sizeof(*predictions), comp);
//  for(index = 0; index < predictionsLength; index++)
//  {
//     fprintf(stdout, "%d\t%f\t%s\n", index, predictions[index], predictionsLabels[index]);     
//  }

//  jpcnn_destroy_network(networkHandle);

  return 0;
}

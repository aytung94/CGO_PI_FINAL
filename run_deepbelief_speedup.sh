#!/bin/bash

categorylist=(
    "accordion"  
    "beaver" 
    "binoculars"     
    "cannon"  
    "crayfish" 
    "dalmatian" 
    "dragonfly"    
    "pitcher" 
    "flamingo"     
    "wallaby"     
    "laptop"
    "llama"
    "pizza" 
    "platypus" 
    "revolver" 
    "sax"
    "schooner" 
    "scorpion" 
    "strawberry"  
    "trilobite" 
    "umbrella" 
)

echo "TESTING DEEPBELIEFSDK SPEEDUP ON CALTECH101 BENCHMARK"
echo "-----------------------------------------------------------"

for category in "${categorylist[@]}"
do    
    echo "Begin DeepBeliefSDK -optimized with OMP- for $category"
    FILES="examples/SimpleLinux/101_ObjectCategories/$category/*"

    for f in $FILES
    do
      #echo "Processing $f file..."
      # take action on each file. $f store current file name
      #echo $
      ./examples/SimpleLinux/deepbeliefOMP.out $f ./examples/SimpleLinux/ccv2012.ntwk $category
      echo "-Processing $f"
    done
done
    mv deepbelief_predictions.csv deepbelief_predictions_optimized_omp.csv

for category in "${categorylist[@]}"
do
    echo "Begin DeepBeliefSDK -non-optimized- for $category"
    FILES="examples/SimpleLinux/101_ObjectCategories/$category/*"
    for f in $FILES
    do
      ./examples/SimpleLinux/deepbelief.out $f ./examples/SimpleLinux/ccv2012.ntwk $category
      echo "-Processing $f"     
    done    
done
    mv deepbelief_predictions.csv deepbelief_predictions_non_optimized.csv


#for((i=1; i <= 5; i++))
#do
  
#done

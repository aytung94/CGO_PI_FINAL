#!/bin/bash

categorylist=(
    "accordion" 
    "ant" 
    "barrel" 
    "beaver" 
    "binoculars"     
    "cannon" 
    "cougar" 
    "crayfish" 
    "cup"
    "dalmatian" 
    "dragonfly"    
    "pitcher" 
    "flamingo"     
    "wallaby"     
    "laptop"
    "leopard"
    "llama"
    "pizza" 
    "platypus" 
    "revolver" 
    "sax"
    "schooner" 
    "scorpion" 
    "strawberry" 
    "tick" 
    "trilobite" 
    "umbrella" 
)

for category in "${categorylist[@]}"
do
    #category=i

    FILES="examples/SimpleLinux/101_ObjectCategories/$category/*"

    #for f in $FILES
    #do
    #  python  tensorflow/models/tutorials/image/imagenet/classify_image.py --image_file $f 
    #done

    echo "--------------------"

    for f in $FILES
    do
      #echo "Processing $f file..."
      # take action on each file. $f store current file name
      #echo $f
      ./examples/SimpleLinux/deepbelief.out $f ./examples/SimpleLinux/ccv2012.ntwk $category
    done
done

#for((i=1; i <= 5; i++))
#do
  
#done
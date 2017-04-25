#!/bin/bash

category="accordion"

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


#for((i=1; i <= 5; i++))
#do
  
#done
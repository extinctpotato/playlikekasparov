#!/bin/bash

for model in models/*.obj; do
	echo "Processing $model"
	./obj2opengl.sif -noMove "$model"
	python3 obj2opengl-fixup.py "${model%.*}.h"
done

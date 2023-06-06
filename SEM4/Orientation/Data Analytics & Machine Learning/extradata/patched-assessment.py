# Taken from node-red-contrib-machine-learning-v2. 
# Literal find and replace on getargspec to getfullargspec to make it work in image. 
# Also see Dockerfile for more about why.

import sklearn.metrics as m
import json
import sys
import numpy
from inspect import getfullargspec # Drop in replacement for getargspec https://docs.python.org/3/library/inspect.html which fixes some magical things

#read configurations
config = json.loads(input())

while True:
	#read request
	data = json.loads(input())
	
	get_score = getattr(m, config['score'])
	kwargs = {}
	if 'average' in getfullargspec(get_score).args:
		kwargs['average'] = 'micro'
	if 'beta' in getfullargspec(get_score).args:
		kwargs['beta'] = 1
	score = get_score(data['real'], data['predicted'], **kwargs)
	if type(score) is numpy.ndarray:
		score = json.dumps(score.tolist())
	print(score)

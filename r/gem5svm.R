trainingDataToMatrix <- function(listx, length) {
	i <- 1
	minlength <- length()

	while(i < length(listx)) {
		if(minlength < length(unlist(listx[i]))){
			minlength <- length(unlist(listx[i]))
		}
		i <- i + 1
	}
	
	featureMatrix = matrix(unlist(listx[1]), minlength)

	i <- 2
	while(i < length(listx)) {
		featureMatrix <- cbind(featureMatrix, unlist(listx[i]))
		i <- i + 1
	}

	t(featureMatrix)
}



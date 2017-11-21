sampleRate = 1000000000

readdata <- function(filename) {
  fmlog <- filename
  datatable <- read.csv(fmlog, header=FALSE, sep=" ",as.is = TRUE, stringsAsFactors=FALSE)
  x <- datatable[, 1]
  y <- datatable[, 4]
  # plot(x, y)
  x <- tail(x, length(x) - 3)
  y <- tail(y, length(y) - 3)
  
  list(x, y)
}

sampledata <- function(freq, x, y, interval) {
  newx = c()
  newy = c()
  
  i <- 0
  
  xstart = x[1]
  currenty = y[1]
  currentidx = 1
  
  while(i < length(x)) {
    samplex <- xstart + interval * (currentidx - 1)
    
    if(samplex >= x[i + 1])
    {
      newx[currentidx] = x[i + 1]
      newy[currentidx] = y[i + 1]
      i <- i + 1
      
      currentidx <- currentidx + 1
      next
    } 
    
    newx[currentidx] <- samplex
    newy[currentidx] <- (y[i + 1]  - y[i]) / (x[i + 1] - x[i]) * (samplex - x[i]) + y[i]

    currentidx <- currentidx + 1
  }
  
  c(newx, newy)
}

tovector1 <- function(intp) {
  i <- 1
  vec <- c()
  while(i < length(intp)){
    vec[i] <- intp[i]
    i<-i+1
  }
  
  vec
}

generateFeatureData <- function(x, y, sampleintval, maxastraining, numberoftraining, tag) {
  interval = maxastraining / numberoftraining
  
  i <- 0
  minlengh = 100000000000000
  
  ret = list()
  
  while(i < numberoftraining) {
    
    subsetx = x[(i * interval) : ((i + 1) * interval)]
    subsety = y[(i * interval) : ((i + 1) * interval)]
  
    sdata <- sampledata(0, subsetx, subsety, sampleintval)
    
    samplex <- head(sdata, length(sdata)/2)
    sampley <- tail(sdata, length(sdata)/2)
    
    yfft <- fft(sampley)
    yCoef = abs(yfft)
    
    if(minlengh >= length(yCoef))
      minlengh = length(yCoef)
    
    ret[i + 1] <-list(list(yCoef)) 
    
    i <- i + 1
    
  }
  
  i <- 0
  
  while( i < length(ret)) {
    ret[i] <- list(head(unlist(ret[i]), minlengh))
    i <- i + 1
  }
  
  ret
  
}

data1GHz = readdata("/home/cisco/mcpat/mcpat/1GHz.log")
data1MHz = readdata("/home/cisco/mcpat/mcpat/500MHz.log")

x1GHz = as.numeric(unlist(data1GHz[1]))
y1GHz = as.numeric(unlist(data1GHz[2]))

x1MHz = as.numeric(unlist(data1MHz[1]))
y1MHz = as.numeric(unlist(data1MHz[2]))

plot(head(x1GHz, 100), head(y1GHz, 100))
plot(head(x1MHz, 200), head(y1MHz, 200))



afft <- fft(y1GHz)
aCoef1G =  abs(afft)

plot(x1GHz, aCoef1G)

bfft <- fft(y1MHz)
bCoef <- abs(bfft)


plot(x1MHz, bCoef)

mfft <- fft(y1MHz)
mCoef = abs(mfft)

plot(x1MHz, mCoef)

featuredata <-generateFeatureData(x1GHz, y1GHz, 500, 160000, 40, "1GHz")

i = 1  

while (i < 6) {
  plot(seq(500, 500 * length(unlist(featuredata[i])), 500), unlist(featuredata[i]))
  
  i <- i + 1
}

featuredata500M <-generateFeatureData(x1MHz, y1MHz, 500, 40000, 40, "1GHz")

i = 1  

while (i < 6) {
  plot(seq(500, 500 * length(unlist(featuredata500M[i])), 500), unlist(featuredata500M[i]))
  
  i <- i + 1
}

a = head(x1GHz, 500)
b = head(y1GHz, 500)

sample100 <- sampledata(0, a, b, 500)

x=head(sample100, length(sample100)/2)
y=tail(sample100, length(sample100)/2)

yfft <- fft(y)
yCoef = abs(yfft)

plot(x, yCoef)


a = head(x1MHz, 500)
b = head(y1MHz, 500)

sample100 <- sampledata(0, a, b, 500)

x=head(sample100, length(sample100)/2)
y=tail(sample100, length(sample100)/2)

yfft <- fft(y)
yCoef = abs(yfft)

plot(x, yCoef)


#sampled1GHz <- sampledata(0, x1GHz, y1GHz, 500)
#sampled1MHz <- sampledata(0, x1MHz, y1MHz, 500)




trainingDataToMatrix <- function(listx, l) {
  i <- 1
  minlength <- l
  
  a=list()
  
  while(i < length(listx)) {
    if(minlength > length(unlist(listx[i]))){
      minlength <- length(unlist(listx[i]))
    }
    i <- i + 1
    
    a=append(a, length(unlist(listx[i])))
  }
  

  featureMatrix = matrix(head(unlist(listx[1]), minlength), minlength)
  
  i <- 2
  while(i <= length(listx)) {
    featureMatrix <- cbind(featureMatrix, head(unlist(listx[i]), minlength))
    i <- i + 1
  }
  
  t(featureMatrix)
}



# verification set

numberOfFeatures = 100

combineData=append(featuredata, featuredata500M)

freq = c(rep("1G", 20), rep("500M", 20))

vdata1GHz = featuredata[21:40]
vdata500Mhz = featuredata500M[21:40]

vcombined = append(vdata1GHz, vdata500Mhz)

vData = trainingDataToMatrix(vcombined, numberOfFeatures)

# SVM starts here

tdata1GHz = featuredata[1:20]
tdata500MHz = featuredata500M[1:20]

tcombineData = append(tdata1GHz, tdata500MHz)

fData = trainingDataToMatrix(tcombineData, numberOfFeatures)

#View(fData)

training.data.frame <- as.data.frame(fData)

model <- svm(freq ~ .,data = fData, type = "C")

fd = cbind(vData, freq)
verification.data.frame <- as.data.frame(fd)

pred <- predict (model, vData)

table(predict=pred, result=freq)





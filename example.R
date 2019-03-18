devtools::install_github("vrunge/fpopChallenge", force = TRUE)

library(fpopChallenge)
library(fpop)

n <- 10^6
beta = 2 * (log(length(n)))
s1 <- NULL
s2 <- NULL
s3 <- NULL
for(i in 1:10)
{
  y = rnorm(n)
  s1 <- c(s1, system.time(fpopRunge(vectData = y, penalty = beta, algoType = 1))[1])
  s2 <- c(s2, system.time(fpopRunge(vectData = y, penalty = beta, algoType = 2))[1])
  s3 <- c(s3, system.time(Fpop(x = y, lambda = beta))[1])
}

mean(s1)
mean(s2)
mean(s3)

####################################################################################"

dataNoPruning <- function(n, beta = 1)
{
  v <- rep(0,n)
  for(i in 2:n){v[i] <- sqrt(beta/n)*(sqrt(n-1) - sqrt(i*(n-i)) + sqrt((i-1)*(n-i+1)))}
  return(v)
}


n <- 10^3
s1 <- NULL
s2 <- NULL
s3 <- NULL
for(i in 1:10)
{
  y = dataNoPruning(n, beta)
  s1 <- c(s1, system.time(fpopRunge(vectData = y, penalty = beta, algoType = 1))[1])
  s2 <- c(s2, system.time(fpopRunge(vectData = y, penalty = beta, algoType = 2))[1])
  s3 <- c(s3, system.time(Fpop(x = y, lambda = beta))[1])
}

mean(s1)
mean(s2)
mean(s3)
